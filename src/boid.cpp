#include "boid.h"
#include <Eigen/Dense>

Boid::Boid(Eigen::Vector2f pos, float r) {
    p_ = pos;
    v_ = {0, 0};
    f_ = {0, 0};
    m_ = 1;
    r_ = r;
};

void Boid::step(float dt) {
    p_ += v_ * dt;
    v_ += (f_ / m_) * dt;
    f_ = {0, 0};
};

auto Boid::get_heading() -> Eigen::Vector2f {
    Eigen::Vector2f res = {0, 0};

    float norm = v_.squaredNorm();
    if (norm > 0) {
        res = v_ / norm;
    };

    return res;
};
