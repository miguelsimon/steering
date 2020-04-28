
#include "RotationRRTProblem.h"

#include "catch2/catch.hpp"

using Eigen::Rotation2D;
using Eigen::Vector2f;
using Eigen::Vector3f;

TEST_CASE("RotationRRTProblem") {

    SECTION("to_segment_endpoints") {
        auto p = Vector3f(1, 1, 0);
        auto expected_a = Vector2f(1, 1);
        auto expected_b = Vector2f(11, 1);

        auto [a, b] = RotationRRTProblem::to_segment_endpoints(p, 10);

        REQUIRE((a - expected_a).norm() == 0);
        REQUIRE((b - expected_b).norm() == 0);
    };

    SECTION("segments_intersect") {
        auto a = Vector2f(0, 0);
        auto b = Vector2f(0, 10);
        auto c = Vector2f(-5, 5);
        auto d = Vector2f(5, 5);
        bool res = RotationRRTProblem::segments_intersect(a, b, c, d);
        REQUIRE(res);

        auto o = Vector2f(29, 44);
        Rotation2D<float> rot(1);

        res = RotationRRTProblem::segments_intersect(
            o + (rot * a), o + (rot * b), o + (rot * c), o + (rot * d));
        REQUIRE(res);

        res = RotationRRTProblem::segments_intersect(a, b, o + a, o + b);
        REQUIRE(!res);
    };

    SECTION("instantiate") {
        auto problem = RotationRRTProblem();
        problem.random_state();
    };

    SECTION("is_free test") {
        auto problem = RotationRRTProblem();

        problem.obstacle_a_.push_back(Vector2f(0, 0));
        problem.obstacle_b_.push_back(Vector2f(0, 10));

        float half_length = problem.segment_length_ / 2;

        // should intersect
        auto p = Vector3f(-half_length, 5, 0);
        REQUIRE(!problem.is_free(p));

        // should not intersect
        p = Vector3f(half_length, 0, 0);
        REQUIRE(problem.is_free(p));
    };

    SECTION("plan") {
        auto problem = RotationRRTProblem();

        auto p = Vector3f(0, 0, 0);
        auto goal = Vector3f(1, 0, 0);

        auto [success, dst, action] = problem.plan(p, goal);
        REQUIRE(success);
    };
};
