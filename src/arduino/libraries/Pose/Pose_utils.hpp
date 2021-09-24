#include "Pose.hpp"

namespace rexlab {

template <class T>
void PrintPose(const Pose<T>& pose) {
  Serial.print(" x = ");
  Serial.print(pose.position_x);
  Serial.print(" y = ");
  Serial.print(pose.position_y);
  Serial.print(" z = ");
  Serial.print(pose.position_z);
  Serial.print(" qw = ");
  Serial.print(pose.quaternion_w);
  Serial.print(" qx = ");
  Serial.print(pose.quaternion_x);
  Serial.print(" qy = ");
  Serial.print(pose.quaternion_y);
  Serial.print(" qz = ");
  Serial.print(pose.quaternion_z);
  Serial.print(" t = ");
  Serial.print(pose.time_us);
  Serial.println();
}

} // namespace rexlab
