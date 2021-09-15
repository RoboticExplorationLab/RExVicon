#pragma once

#include <cstdint>
#include <ostream>
#include <limits>
#include <cmath>
#include <type_traits>

namespace rexlab {

namespace {

template <class T>
constexpr T GetUnitQuaternionScalar() {
  if (std::is_integral<T>::value) {
    return std::numeric_limits<T>::max();
  } else if (std::is_floating_point<T>::value) {
    return static_cast<T>(1.0);
  }
}

} // namespace

template <class T>
struct Pose {
 public:
  static_assert(std::is_signed<T>::value || std::is_floating_point<T>::value, "Invalid data type, must be a float or a signed integer");

  Pose() = default;
  Pose(int32_t scale_mm) : position_scale(scale_mm) {}
  Pose(T px, T py, T pz, T qw, T qx, T qy, T qz, int32_t scale, bool occluded)
      : position_x(px),
        position_y(py),
        position_z(pz),
        quaternion_w(qw),
        quaternion_x(qx),
        quaternion_y(qy),
        quaternion_z(qz),
        position_scale(scale),
        is_occluded(occluded) {}
  char* GetData() { return reinterpret_cast<char*>(this); }
  const char* GetData() const { return reinterpret_cast<const char*>(this); }
  static constexpr int NumBytes() { return 7 * sizeof(T) + 9; }

  T position_x = 0;
  T position_y = 0;
  T position_z = 0;
  T quaternion_w = GetUnitQuaternionScalar<T>();
  T quaternion_x = 0;
  T quaternion_y = 0;
  T quaternion_z = 0;

  int32_t position_scale = 1000;  // in millimeters 
  int32_t time_us = 0.0;          // timestamp (microseconds)
  bool is_occluded = false;
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
    static_cast<Tfloat>(pint.quaternion_w / static_cast<Tfloat>(Tmax)),
    static_cast<Tfloat>(pint.quaternion_x / static_cast<Tfloat>(Tmax)),
    static_cast<Tfloat>(pint.quaternion_y / static_cast<Tfloat>(Tmax)),
    static_cast<Tfloat>(pint.quaternion_z / static_cast<Tfloat>(Tmax)),
    pint.position_scale, pint.is_occluded
  );
  return pfloat;
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
    ClampToInt<Tint>(pfloat.quaternion_w * Tmax), 
    ClampToInt<Tint>(pfloat.quaternion_x * Tmax), 
    ClampToInt<Tint>(pfloat.quaternion_y * Tmax), 
    ClampToInt<Tint>(pfloat.quaternion_z * Tmax), 
    pfloat.position_scale, pfloat.is_occluded
  );
  return pint;
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