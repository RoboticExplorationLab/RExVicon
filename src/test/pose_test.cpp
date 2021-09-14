#include <iostream>
#include <gtest/gtest.h>
#include <limits>
#include <fmt/core.h>

#include "src/pose.hpp"

namespace rexlab {

TEST(PoseTest, Conversion) {
  Pose<int32_t> pint;
  EXPECT_EQ(pint.quaternion_w, std::numeric_limits<int32_t>::max());
  EXPECT_EQ(pint.position_x, 0);
  Pose<float> pfloat = ConvertPoseIntToFloat<float>(pint);
  EXPECT_FLOAT_EQ(pfloat.quaternion_w, 1.0);
  Pose<int32_t> pint32 = ConvertPoseFloatToInt<int32_t>(pfloat);
  EXPECT_EQ(pint32.quaternion_w, std::numeric_limits<int32_t>::max());
  pfloat.position_x = 0.5;
  Pose<int64_t> pint64 = ConvertPoseFloatToInt<int64_t>(pfloat);
  EXPECT_EQ(pint64.quaternion_w, std::numeric_limits<int64_t>::max());
  EXPECT_LE(std::abs(pint64.position_x - std::numeric_limits<int64_t>::max() / 2), 1);


  Pose<double> pfloat64 = ConvertPoseIntToFloat<double>(pint64);
  fmt::print("{}, scale = {}\n", 
    pint64.position_x / static_cast<double>(std::numeric_limits<int64_t>::max()) * (pint64.position_scale / 1000.0), 
    pint64.position_scale);
  EXPECT_DOUBLE_EQ(pfloat64.position_x, 0.5);
  EXPECT_DOUBLE_EQ(pfloat64.position_y, 0.0);
  EXPECT_DOUBLE_EQ(pfloat64.quaternion_w, 1.0);
  EXPECT_DOUBLE_EQ(pfloat64.quaternion_x, 0.0);
}

}  // namespace rexlab