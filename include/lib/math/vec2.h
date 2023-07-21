#ifndef INCLUDE_LIB_MATH_VEC2_H_
#define INCLUDE_LIB_MATH_VEC2_H_

#include <cmath>
#include <tuple>
#include <utility>

class Vec2 {
 public:
  float x_;
  float y_;

  constexpr Vec2() noexcept : x_(0.0f), y_(0.0f) {}
  constexpr Vec2(float x, float y) noexcept : x_(x), y_(y) {}
  constexpr Vec2(int x, int y) noexcept : x_(static_cast<float>(x)), y_(static_cast<float>(y)) {}

  bool operator==(const Vec2 &rhs) const {
    return std::tie(x_, y_) == std::tie(rhs.x_, rhs.y_);
  }
  bool operator!=(const Vec2 &rhs) const {
    return !(rhs == *this);
  }

  Vec2 operator+(const Vec2 &rhs) const {
    return {x_ + rhs.x_, y_ + rhs.y_};
  }
  Vec2 operator+=(const Vec2 &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
  }
  Vec2 operator-(const Vec2 &rhs) const {
    return {x_ - rhs.x_, y_ - rhs.y_};
  }

  Vec2 operator*(float c) const {
    return {x_ * c, y_ * c};
  }

  Vec2 operator*=(float c) {
    x_ *= c;
    y_ *= c;
    return *this;
  }

  Vec2 operator*(const Vec2 &rhs) const {
    return {x_ * rhs.x_, y_ * rhs.y_};
  }

  Vec2 operator*=(const Vec2 &rhs) {
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    return *this;
  }

  double DotProd(const Vec2 &rhs) const {
    return x_ * rhs.x_ + y_ * rhs.y_;
  }

  double CrossProd(const Vec2 &rhs) const {
    return x_ * rhs.y_ - y_ * rhs.x_;
  }

  Vec2 Abs() const {
    return Vec2(std::abs(x_), std::abs(y_));
  }

  double Magnitude() const {
    return std::sqrt(x_ * x_ + y_ * y_);
  }

  Vec2 Normalize() {
    auto m = Magnitude();
    if (m <= 0.000000001) {
      x_ = 0;
      y_ = 0;
    } else {
      x_ /= m;
      y_ /= m;
    }
    return *this;
  }
};

const Vec2 ZeroVec2(0, 0);
const Vec2 UpVec2(0, -1);
const Vec2 DownVec2(0, 1);
const Vec2 RightVec2(1, 0);
const Vec2 LeftVec2(-1, 0);
const Vec2 OnesVec2(1, 1);

#endif  // INCLUDE_LIB_MATH_VEC2_H_
