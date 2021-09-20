#include <array>
#include <iostream>
#include <limits>

#include <fmt/core.h>
#include <gtest/gtest.h>

#include "src/arduino/teensy_receiver/pose.hpp"
#include "src/callbacks.hpp"

namespace rexlab {
using CallbackFunction = std::function<void(const Pose<float>& pose)>;

void TestFunctor(const CallbackFunction& callback, Pose<float>& pose) {
  callback(pose);
}

bool IsFile(const std::string& filename) {
  struct stat buffer;
  return (stat(filename.c_str(), &buffer) == 0);
}

TEST(CallbacksTest, SerialCallbackTest) {
  SerialCallback serial_callback("/dev/tty0", 57600);
  EXPECT_FALSE(serial_callback.IsOpen());

  Pose<float> pose;
  TestFunctor(std::ref(serial_callback), pose);
}

TEST(CallbacksTest, PrintCallback) {
  PrintCallback callback;
  Pose<float> pose;
  pose.position_x = 10;
  TestFunctor(std::ref(callback), pose);
}

TEST(CallbacksTest, FilePrintCallback) {
  EXPECT_FALSE(IsFile("testout.txt"));
  const std::string filename = "testout.txt";
  {
    PrintCallback callback(filename);
    Pose<float> pose;
    pose.position_x = 10;
    TestFunctor(std::ref(callback), pose);
  }
  
  // Check if file was created, and delete it
  // TODO(bjack205): Read it to verify the contents
  EXPECT_TRUE(IsFile(filename));
  std::remove("testout.txt");
  EXPECT_FALSE(IsFile(filename));
}

}  // namespace rexlab