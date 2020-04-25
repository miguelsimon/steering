#ifndef BOID_H
#define BOID_H

#include <Eigen/Dense>

class Boid {

  public:
    Eigen::Vector2f p_;
    Eigen::Vector2f v_;
    Eigen::Vector2f f_;
    float m_;
    float r_;

    Boid() = default;
    Boid(Eigen::Vector2f pos, float r);
    auto get_heading() -> Eigen::Vector2f;
    void step(float dt);
};

#endif
