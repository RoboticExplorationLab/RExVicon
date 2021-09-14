#pragma once

#include <atomic>
#include <functional>
#include <string>

#include "DataStreamClient.h"
#include "src/pose.hpp"

namespace rexlab {

namespace ViconSDK = ViconDataStreamSDK::CPP;

struct ViconDriverOptions {
  std::string server_id = "localhost";
  ViconSDK::StreamMode::Enum stream_mode = ViconSDK::StreamMode::ServerPush;
};

class ViconDriver {
  using CallbackFunction = std::function<void(const Pose<float>& pose)>;

 public:
  ViconDriver();
  ~ViconDriver();

  bool Initialize(const ViconDriverOptions& opts, CallbackFunction callback);
  void RunLoop();
  void Stop();

 private:
  ViconSDK::Client client_;
  std::atomic<bool> is_running_;
  double timecode_offset_ = 0.0;
  double network_lag_estimate_;
  CallbackFunction callback_;
};

}  // namespace rexlab