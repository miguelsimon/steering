#include "BSeek.h"
#include <Eigen/Dense>
#include <utility>

using Eigen::Vector2f;

BSeek::BSeek(float max_force, float desired_speed, float dt, Vector2f target,
             Vector2f p, Vector2f v, float mass)
    : max_force_(max_force), desired_speed_(desired_speed), dt_(dt),
      target_(std::move(target)), p_(std::move(p)), v_(std::move(v)),
      mass_(mass){};

auto BSeek::get_force() -> Vector2f {
    Vector2f desired_heading = (target_ - p_).normalized();
    Vector2f desired_v = desired_heading * desired_speed_;
    Vector2f desired_impulse = desired_v - v_;
    Vector2f desired_accel = desired_impulse / dt_;
    float accel_norm = desired_accel.norm();
    float max_accel = mass_ * max_force_;

    Vector2f accel = desired_accel;
    if (accel_norm > max_accel) {
        accel = max_accel * (desired_accel / accel_norm);
    }
    return accel * mass_;
}

void BSeek::set_p(Eigen::Vector2f p) { p_ = p; };

void BSeek::set_v(Eigen::Vector2f v) { v_ = v; };
