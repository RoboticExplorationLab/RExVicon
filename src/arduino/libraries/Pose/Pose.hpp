#pragma once

#include <cstdint>
#include <ostream>
#include <limits>
#include <cmath>
#include <type_traits>

namespace rexlab {

namespace {

template <class T>
T GetUnitQuaternionScalar() {
  if (std::is_integral<T>::value) {
    return std::numeric_limits<T>::max();
  } else if (std::is_floating_point<T>::value) {
    return static_cast<T>(1.0);
  }
}

} // namespace

constexpr int kQuatScaling = 2;

template <class T>
struct Pose {
 public:
  static constexpr uint8_t MsgID() { return 11; }

  static_assert(std::is_signed<T>::value || std::is_floating_point<T>::value, "Invalid data type, must be a float or a signed integer");

  Pose() = default;
  Pose(int32_t scale_mm) : position_scale(scale_mm) {}
  Pose(T px, T py, T pz, T qw, T qx, T qy, T qz, int32_t scale, bool occluded)
      : is_occluded(occluded),
        position_scale(scale),
        position_x(px),
        position_y(py),
        position_z(pz),
        quaternion_w(qw),
        quaternion_x(qx),
        quaternion_y(qy),
        quaternion_z(qz) {}
  
  Pose(const Pose& other)
      : is_occluded(other.is_occluded),
        position_scale(other.position_scale),
        position_x(other.position_x),
        position_y(other.position_y),
        position_z(other.position_z),
        quaternion_w(other.quaternion_w),
        quaternion_x(other.quaternion_x),
        quaternion_y(other.quaternion_y),
        quaternion_z(other.quaternion_z),
        time_us(other.time_us) {}

  Pose& operator=(const Pose& other) {
    is_occluded = other.is_occluded;
    position_scale = other.position_scale;
    position_x = other.position_x;
    position_y = other.position_y;
    position_z = other.position_z;
    quaternion_w = other.quaternion_w;
    quaternion_x = other.quaternion_x;
    quaternion_y = other.quaternion_y;
    quaternion_z = other.quaternion_z;
    time_us = other.time_us;
    return *this;
  }

  char* GetData() { return reinterpret_cast<char*>(this); }
  const char* GetData() const { return reinterpret_cast<const char*>(this); }
  static constexpr int NumBytes() { return 7 * sizeof(T) + 4 + 4; }

  const uint8_t msgid = MsgID();
  bool is_occluded = false;
  uint16_t position_scale = 10000;  // in millimeters (max ~65m)
  T position_x = 0;
  T position_y = 0;
  T position_z = 0;
  T quaternion_w = GetUnitQuaternionScalar<T>();
  T quaternion_x = 0;
  T quaternion_y = 0;
  T quaternion_z = 0;

  uint32_t time_us = 0.0;          // timestamp (microseconds)
 private:
};

template <class Tfloat, class Tint>
Pose<Tfloat> ConvertPoseIntToFloat(const Pose<Tint>& pint) {
  static_assert(std::is_signed<Tint>::value, "Must provide a signed integer type");
  static_assert(std::is_floating_point<Tfloat>::value, "Must provide a floating-base type");

  constexpr Tint Tmax = std::numeric_limits<Tint>::max();
  Pose<Tfloat> pfloat(
    static_cast<Tfloat>((pint.position_x / static_cast<Tfloat>(Tmax)) * (pint.position_scale / 1000.0)),
    static_cast<Tfloat>((pint.position_y / static_cast<Tfloat>(Tmax)) * (pint.position_scale / 1000.0)),
    static_cast<Tfloat>((pint.position_z / static_cast<Tfloat>(Tmax)) * (pint.position_scale / 1000.0)),
    static_cast<Tfloat>(pint.quaternion_w / static_cast<Tfloat>(Tmax) * kQuatScaling),
    static_cast<Tfloat>(pint.quaternion_x / static_cast<Tfloat>(Tmax) * kQuatScaling),
    static_cast<Tfloat>(pint.quaternion_y / static_cast<Tfloat>(Tmax) * kQuatScaling),
    static_cast<Tfloat>(pint.quaternion_z / static_cast<Tfloat>(Tmax) * kQuatScaling),
    pint.position_scale, pint.is_occluded
  );
  pfloat.time_us = pint.time_us;
  return pfloat;
}

template <class Tfloat, class Tint>
void ConvertPoseIntToFloat(const Pose<Tint>& pint, Pose<Tfloat>* pfloat) {
  static_assert(std::is_signed<Tint>::value, "Must provide a signed integer type");
  static_assert(std::is_floating_point<Tfloat>::value, "Must provide a floating-base type");

  constexpr Tint Tmax = std::numeric_limits<Tint>::max();
  pfloat->position_x   = static_cast<Tfloat>((pint.position_x / static_cast<Tfloat>(Tmax)) * (pint.position_scale / 1000.0));
  pfloat->position_y   = static_cast<Tfloat>((pint.position_y / static_cast<Tfloat>(Tmax)) * (pint.position_scale / 1000.0));
  pfloat->position_z   = static_cast<Tfloat>((pint.position_z / static_cast<Tfloat>(Tmax)) * (pint.position_scale / 1000.0));
  pfloat->quaternion_w = static_cast<Tfloat>(pint.quaternion_w / static_cast<Tfloat>(Tmax) * kQuatScaling);
  pfloat->quaternion_x = static_cast<Tfloat>(pint.quaternion_x / static_cast<Tfloat>(Tmax) * kQuatScaling);
  pfloat->quaternion_y = static_cast<Tfloat>(pint.quaternion_y / static_cast<Tfloat>(Tmax) * kQuatScaling);
  pfloat->quaternion_z = static_cast<Tfloat>(pint.quaternion_z / static_cast<Tfloat>(Tmax) * kQuatScaling);
  pfloat->position_scale = pint.position_scale;
  pfloat->is_occluded = pint.is_occluded;
  pfloat->time_us = pint.time_us;
}

template <class Tint, class Tfloat>
Tint ClampToInt(Tfloat f) {
  static_assert(std::is_signed<Tint>::value, "Can only clamp to signed integers");

  constexpr Tint imin = std::numeric_limits<Tint>::min();
  constexpr Tint imax = std::numeric_limits<Tint>::max();

  constexpr Tfloat fmin = static_cast<Tfloat>(imin);
  constexpr Tfloat fmax = static_cast<Tfloat>(imax);

  if (f <= fmin) return imin;
  if (f >= fmax) return imax;
  return static_cast<Tint>(f);
}

template <class Tint, class Tfloat>
Pose<Tint> ConvertPoseFloatToInt(const Pose<Tfloat>& pfloat) {
  static_assert(std::is_signed<Tint>::value, "Must provide a signed integer type");
  static_assert(std::is_floating_point<Tfloat>::value, "Must provide a floating-base type");

  constexpr Tint Tmax = std::numeric_limits<Tint>::max();
  Pose<Tint> pint(
    ClampToInt<Tint>(pfloat.position_x * (1000.0 / static_cast<Tfloat>(pfloat.position_scale))  * Tmax),
    ClampToInt<Tint>(pfloat.position_y * (1000.0 / static_cast<Tfloat>(pfloat.position_scale))  * Tmax),
    ClampToInt<Tint>(pfloat.position_z * (1000.0 / static_cast<Tfloat>(pfloat.position_scale))  * Tmax),
    ClampToInt<Tint>(pfloat.quaternion_w * Tmax / kQuatScaling), 
    ClampToInt<Tint>(pfloat.quaternion_x * Tmax / kQuatScaling), 
    ClampToInt<Tint>(pfloat.quaternion_y * Tmax / kQuatScaling), 
    ClampToInt<Tint>(pfloat.quaternion_z * Tmax / kQuatScaling), 
    pfloat.position_scale, pfloat.is_occluded
  );
  pint.time_us = pfloat.time_us;
  return pint;
}

template <class Tint, class Tfloat>
void ConvertPoseFloatToInt(const Pose<Tfloat>& pfloat, Pose<Tint>* pint) {
  static_assert(std::is_signed<Tint>::value, "Must provide a signed integer type");
  static_assert(std::is_floating_point<Tfloat>::value, "Must provide a floating-base type");

  constexpr Tint Tmax = std::numeric_limits<Tint>::max();
  pint->position_x   = ClampToInt<Tint>(pfloat.position_x * (1000.0 / static_cast<Tfloat>(pfloat.position_scale))  * Tmax);
  pint->position_y   = ClampToInt<Tint>(pfloat.position_y * (1000.0 / static_cast<Tfloat>(pfloat.position_scale))  * Tmax);
  pint->position_z   = ClampToInt<Tint>(pfloat.position_z * (1000.0 / static_cast<Tfloat>(pfloat.position_scale))  * Tmax);
  pint->quaternion_w = ClampToInt<Tint>(pfloat.quaternion_w * Tmax / kQuatScaling); 
  pint->quaternion_x = ClampToInt<Tint>(pfloat.quaternion_x * Tmax / kQuatScaling); 
  pint->quaternion_y = ClampToInt<Tint>(pfloat.quaternion_y * Tmax / kQuatScaling); 
  pint->quaternion_z = ClampToInt<Tint>(pfloat.quaternion_z * Tmax / kQuatScaling); 
  pint->position_scale = pfloat.position_scale; 
  pint->is_occluded = pfloat.is_occluded;
  pint->time_us = pfloat.time_us;
}

template <class T>
std::ostream& operator<<(std::ostream& io, const Pose<T>& pose) {
  io << "Position: " 
     << pose.position_x << " " << pose.position_y << " " << pose.position_z 
     << " Rotation: "
     << pose.quaternion_w << " " << pose.quaternion_x << " " << pose.quaternion_y << " " 
     << pose.quaternion_z << 
     " Occluded? " << pose.is_occluded ;
  return io;
}


// template<>
// Pose<double>(const Pose<int16_t>& pint);

}  // namespace rexlab
