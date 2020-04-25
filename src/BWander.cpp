#include "BWander.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <cmath>

using Eigen::Vector2f;

BWander::BWander(float max_force, float max_speed, float dt, Eigen::Vector2f p,
                 Eigen::Vector2f v, float mass)
    : max_force_(max_force), max_speed_(max_speed), dt_(dt), p_(std::move(p)),
      v_(std::move(v)), mass_(mass){};

auto BWander::get_wander_force() -> Eigen::Vector2f {
    // based on wander description in https://www.red3d.com/cwr/steer/gdc99/

    Vector2f circle_p = get_wander_circle_p();

    Vector2f target_p = circle_p + wander_r_ * Vector2f(cosf(wander_theta_),
                                                        sinf(wander_theta_));

    float scale = max_force_ / (wander_r_ + wander_k_);

    return scale * (target_p - p_);
};

auto BWander::get_wander_circle_p() -> Vector2f {
    Vector2f heading = v_.normalized();

    if (heading.norm() == 0)
        heading = Vector2f(1, 0);

    Vector2f circle_offset = heading * (wander_k_ + wander_r_);
    return p_ + circle_offset;
}

auto BWander::get_force() -> Vector2f {
    // loosely based on wander description in
    // https://www.red3d.com/cwr/steer/gdc99/

    const float pi = 3.141592653589793238462643383279502884f;

    std::bernoulli_distribution trial(0.5);

    if (trial(rnd_generator_)) {
        wander_theta_ += pi / wander_segments_;
    } else {
        wander_theta_ -= pi / wander_segments_;
    };

    Vector2f wander_force = get_wander_force();

    // keep in speed bounds
    Vector2f next_v = v_ + dt_ * wander_force;
    float speed = next_v.norm();
    if (speed > max_speed_) {
        Vector2f impulse = next_v.normalized() * max_speed_ - next_v;
        Vector2f accel = impulse / dt_;
        wander_force += accel * mass_;
    }

    return wander_force;
};

void BWander::draw(Draw &draw) {
    draw.circle(get_wander_circle_p(), wander_r_);
    draw.segment(p_, p_ + get_wander_force());
};

void BWander::set_p(Vector2f p) { p_ = p; };

void BWander::set_v(Vector2f v) { v_ = v; };
