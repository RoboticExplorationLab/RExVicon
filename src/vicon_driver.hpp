#pragma once

#include <atomic>
#include <functional>
#include <string>
#include <map>

#include "DataStreamClient.h"
#include "src/pose.hpp"

namespace rexlab {

namespace ViconSDK = ViconDataStreamSDK::CPP;

struct ViconDriverOptions {
  std::string server_id = "localhost";
  ViconSDK::StreamMode::Enum stream_mode = ViconSDK::StreamMode::ServerPush;
  int32_t position_scale = 1000; // in mm
};

/**
 * @brief A class that processes the Vicon data stream and calls user-defined functions
 * on each object.
 * 
 * REFERENCE: This code is largely based off of the implementation here:
 * https://github.com/alspitz/simple_vicon
 */
class ViconDriver {
  using CallbackFunction = std::function<void(const Pose<float>& pose)>;

 public:
  ViconDriver();
  ~ViconDriver();

  bool Initialize(const ViconDriverOptions& opts);
  bool AddCallback(const std::string& subject_name, const CallbackFunction& callback);
  void ClearCallbacks() { callbacks_.clear(); }
  void RunLoop();
  void Stop();

 private:
  ViconSDK::Client client_;
  std::atomic<bool> is_running_;
  double timecode_offset_ = 0.0;
  double network_lag_estimate_;
  std::map<std::string, CallbackFunction> callbacks_;
  ViconDriverOptions opts_;
};

}  // namespace rexlab