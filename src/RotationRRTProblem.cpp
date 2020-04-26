#include "RotationRRTProblem.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>

using Eigen::Matrix2f;
using Eigen::Rotation2D;
using Eigen::Vector2f;
using Eigen::Vector3f;

auto segments_intersect(Vector2f a, Vector2f b, Vector2f c, Vector2f d)
    -> bool {

    Vector2f vba = b - a;
    Vector2f vdc = d - c;

    Matrix2f A;
    A << vba[0], -vdc[0], vba[1], -vdc[1];

    Vector2f k = -a + c;

    Vector2f x = A.colPivHouseholderQr().solve(k);

    float error = ((A * x) - k).norm();

    // std::cout << A << std::endl;
    // std::cout << x << std::endl;
    // std::cout << k << std::endl;

    const float max_err = 0.0001;
    // parallel

    if (error > max_err) {
        return false;
    } else {
        return x[0] >= 0 && x[0] <= 1 && x[1] >= 0 && x[1] <= 1;
    };
};

static auto to_segment_endpoints(Vector3f p, float length)
    -> std::tuple<Vector2f, Vector2f> {
    Vector2f a = Vector2f(p[0], p[1]);
    Vector2f delta = Vector2f(length, 0);
    Rotation2D<float> rot(p[2]);
    Vector2f b = a + (rot * delta);

    return std::make_tuple(a, b);
};

auto RotationRRTProblem::random_state() -> Vector3f {
    std::uniform_real_distribution<float> x(ll_[0], ur_[0]);
    std::uniform_real_distribution<float> y(ll_[1], ur_[1]);
    std::uniform_real_distribution<float> rot(ll_[2], ur_[2]);

    const int max_retries = 1000;

    for (int i = 0; i < max_retries; i++) {
        auto p =
            Vector3f(x(rnd_generator_), y(rnd_generator_), rot(rnd_generator_));
        if (is_free(p)) {
            return p;
        };
    };
    std::cout << "Max retries exceeded when attempting to sample." << std::endl;
    exit(1);
};

auto RotationRRTProblem::plan(Vector3f src, Vector3f dst)
    -> std::tuple<bool, Vector3f, Vector3f> {

    return std::make_tuple(false, Vector3f(), Vector3f());
};

auto RotationRRTProblem::is_free(Eigen::Vector3f p) -> bool {
    for (int i = 0; i < obstacle_a_.size(); i++) {
        Vector2f a = obstacle_a_[i];
        Vector2f b = obstacle_b_[i];

        auto [c, d] = to_segment_endpoints(p, segment_length_);

        if (segments_intersect(a, b, c, d)) {
            return false;
        };
    };
    return true;
};

auto RotationRRTProblem::goal_reached(Eigen::Vector3f p) -> bool {
    float distance = (p - goal_).norm();
    return distance < goal_radius_;
};
