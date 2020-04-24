#ifndef BSEEK_H
#define BSEEK_H

#include <Eigen/Dense>

class BSeek {
  public:
    BSeek(float max_force, float desired_speed, float dt,
          Eigen::Vector2f target, Eigen::Vector2f p, Eigen::Vector2f v,
          float mass);
    Eigen::Vector2f get_force();

    float max_force_;
    float desired_speed_;
    float dt_;
    Eigen::Vector2f target_;
    Eigen::Vector2f p_;
    Eigen::Vector2f v_;
    float mass_;
};

#endif
