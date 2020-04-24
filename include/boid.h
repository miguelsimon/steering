#ifndef BOID_H
#define BOID_H

#include <Eigen/Dense>

class Boid {

  public:
    Eigen::Vector2f p_;
    Eigen::Vector2f v_;
    Eigen::Vector2f f_;
    float m_;

    Boid(Eigen::Vector2f pos);
    Eigen::Vector2f get_heading();
    void step(float dt);
};

#endif
