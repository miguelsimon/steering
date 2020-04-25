#include "BWaypoint.h"
#include <Eigen/Dense>
#include <utility>
#include <vector>

using Eigen::Vector2f;

BWaypoint::BWaypoint(float max_force, float desired_speed, float dt, Vector2f p,
                     Vector2f v, float mass, std::vector<Eigen::Vector2f> path)
    : path_(path), path_idx_(0),
      seek_(max_force, desired_speed, dt, {0, 0}, p, v, mass) {
    assert(path.size() > 0);
    seek_.target_ = path[0];
};

auto BWaypoint::get_force() -> Vector2f {
    const float min_goal_distance = 5;
    float distance = (seek_.target_ - seek_.p_).norm();
    if (distance < min_goal_distance) {
        path_idx_ += 1;
    };

    if (path_idx_ < path_.size()) {
        seek_.target_ = path_[path_idx_];
    };

    return seek_.get_force();
};

void BWaypoint::set_p(Eigen::Vector2f p) { seek_.set_p(p); };

void BWaypoint::set_v(Eigen::Vector2f v) { seek_.set_v(v); };
