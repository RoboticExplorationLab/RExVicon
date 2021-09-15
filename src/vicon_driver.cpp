#include "src/vicon_driver.hpp"

#include <chrono>
#include <iostream>

namespace rexlab {

bool ViconDriver::Initialize(const ViconDriverOptions& opts) {
  opts_ = opts;

  client_.Connect(opts.server_id);
  if (!client_.IsConnected().Connected) {
    std::cerr << "Failed to connect to Vicon server at " << opts.server_id << std::endl;
    return false;
  }

  client_.SetStreamMode(opts.stream_mode);
  client_.SetAxisMapping(ViconSDK::Direction::Forward, ViconSDK::Direction::Left, 
                         ViconSDK::Direction::Up);
  return true;
}

bool ViconDriver::AddCallback(const std::string& subject_name, const CallbackFunction& callback) {
  auto pair = callbacks_.emplace(std::make_pair(subject_name, callback));
  return pair.second;
}

void ViconDriver::RunLoop() {
  client_.EnableSegmentData();
  int wait_for_buffer_counter = 0;
  bool ready_for_init = false;

  Pose<float> pose;
  pose.position_scale = opts_.position_scale;

  std::map<std::string, CallbackFunction>::iterator callback_iterator;

  is_running_.store(true);
  while (is_running_.load()) {
    auto result = client_.GetFrame().Result;

    ViconSDK::Result::Enum getframe_result = client_.GetFrame().Result;

    if (getframe_result != ViconSDK::Result::Success) {
      std::cerr << "ViconSDK GetFrame did not return success: " << result << std::endl;
      continue;
    }

    // Wait 1 second to flush the buffer in ServerPush mode
    double framerate = client_.GetFrameRate().FrameRateHz;
    if (!ready_for_init)
    {
      if (++wait_for_buffer_counter > framerate)
      {
        ready_for_init = true;
      }
      else
      {
        continue;
      }
    }

    // We assume that the client and the server clocks are time-synced using NTP
    // Proposed strategy: subtract latency from timecode
    ViconSDK::Output_GetTimecode timecode = client_.GetTimecode();
    if (timecode.Result != ViconSDK::Result::Success) {
      std::cerr << "ViconSDK GetTimeCode did not return success: " << result << std::endl;
      continue;
    }

    // Convert Timecode to seconds
    double timecode_time = timecode.Hours * 3600.0 + timecode.Minutes * 60.0 + timecode.Seconds + (timecode.Frames * timecode.SubFramesPerFrame + timecode.SubFrame) / framerate;

    // Is this the first time we're seeing data? If so, initialise timecode_offset_
    // TODO: Determine average round trip network delay in a separate slower thread and save in network_lag_estimate_?
    // TODO: Also add jump logic here since timecode rotates every 24 hours...
    if (timecode_offset_ == 0.0)
    {
      auto time_now_sys = std::chrono::high_resolution_clock::now().time_since_epoch();
      double time_now = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(time_now_sys).count();
      timecode_offset_ = time_now - network_lag_estimate_ - timecode_time;
      printf("Timecode offset :: %.8f Time:: %.8f Timecode %.8f lag :: %f\n", timecode_offset_, time_now, timecode_time, network_lag_estimate_);
    }
    // Move the timecode to the client (our) clock, and subtract the vicon system estimated latency from it.
    double time_s = timecode_time + timecode_offset_ - client_.GetLatencyTotal().Total;

    // Loop over all of the subjects
    int n_subjects = client_.GetSubjectCount().SubjectCount;
    for (int i = 0; i < n_subjects; i++) {
      std::string subject_name = client_.GetSubjectName(i).SubjectName;

      // Check if the subject name matches one of the callbacks
      callback_iterator = callbacks_.find(subject_name);
      if (callback_iterator != callbacks_.end()) {
        // Get the VICON translation and rotation data
        std::string segment_name = client_.GetSegmentName(subject_name, 0).SegmentName;
        auto trans = client_.GetSegmentGlobalTranslation(subject_name, segment_name);
        auto rot = client_.GetSegmentGlobalRotationQuaternion(subject_name, segment_name);

        if (trans.Result != ViconSDK::Result::Success) {
          std::cerr << "Translation get failed for " << subject_name << "::" << segment_name << std::endl;
        }
        if (rot.Result != ViconSDK::Result::Success) {
          std::cerr << "Rotation get failed for " << subject_name << "::" << segment_name << std::endl;
        }

        // Convert to Pose type

        // Convert mm translation to meters
        pose.position_x = trans.Translation[0] * 0.001; 
        pose.position_y = trans.Translation[1] * 0.001; 
        pose.position_z = trans.Translation[2] * 0.001; 

        // Convert scalar last to scalar first
        pose.quaternion_w = rot.Rotation[3];
        pose.quaternion_x = rot.Rotation[0];
        pose.quaternion_y = rot.Rotation[1];
        pose.quaternion_z = rot.Rotation[2];
        pose.is_occluded = trans.Occluded || rot.Occluded;
        pose.time_us = static_cast<int32_t>(time_s * 1000000);

        // Pass pose to callback
        const CallbackFunction& callback = callback_iterator->second;
        callback(pose);
      }
  }
}


}
 
}  // namespace rexlab
