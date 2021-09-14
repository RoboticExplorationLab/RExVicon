#include <iostream>

#include "src/pose.hpp"

namespace rexlab {

void PoseTest() {
  Pose<int32_t> pint;
  std::cout << pint << std::endl;
  Pose<float> pfloat = ConvertPoseIntToFloat<float>(pint);
  std::cout << pfloat << std::endl;
  Pose<int32_t> pint2 = ConvertPoseFloatToInt<int32_t>(pfloat);
  std::cout << pint2 << std::endl;
  float one = 1.0;
  float max = one * std::numeric_limits<int>::max();
}

}  // namespace rexlab


int main() {
  rexlab::PoseTest();
  return 0;
}