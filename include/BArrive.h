#ifndef BARRIVE_H
#define BARRIVE_H

#include <Eigen/Dense>

class BArrive {
  public:
    BArrive(float max_force, float desired_speed, float dt,
            Eigen::Vector2f target, Eigen::Vector2f p, Eigen::Vector2f v,
            float mass, float slow_radius);
    Eigen::Vector2f get_force();

    float max_force_;
    float desired_speed_;
    float dt_;
    Eigen::Vector2f target_;
    Eigen::Vector2f p_;
    Eigen::Vector2f v_;
    float mass_;
    float slow_radius_;
};

#endif
