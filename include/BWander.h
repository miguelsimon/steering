#ifndef BWANDER_H
#define BWANDER_H

#include "draw.h"
#include <Eigen/Dense>
#include <random>

class BWander {
  public:
    BWander() = default;

    BWander(float max_force, float max_speed, float dt, Eigen::Vector2f p,
            Eigen::Vector2f v, float mass);

    auto get_force() -> Eigen::Vector2f;

    void set_p(Eigen::Vector2f p);
    void set_v(Eigen::Vector2f v);
    void draw(Draw &draw);

    float max_force_;
    float max_speed_;
    float dt_;
    Eigen::Vector2f p_;
    Eigen::Vector2f v_;
    float mass_;
    float wander_theta_ = 0;
    float wander_r_ = 20;
    float wander_k_ = 15;
    float wander_segments_ = 32;
    std::default_random_engine rnd_generator_;

  private:
    Eigen::Vector2f get_wander_force();
    Eigen::Vector2f get_wander_circle_p();
};

#endif
