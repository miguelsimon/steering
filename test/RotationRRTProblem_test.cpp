
#include "RotationRRTProblem.h"

#include "catch2/catch.hpp"

using Eigen::Vector2f;
using Eigen::Vector3f;

TEST_CASE("RotationRRTProblem") {

    SECTION("Instantiate") {
        auto problem = RotationRRTProblem();
        problem.random_state();
    };

    SECTION("segments_intersect") {
        auto a = Vector2f(0, 0);
        auto b = Vector2f(0, 10);
        auto c = Vector2f(-5, 5);
        auto d = Vector2f(5, 5);
        bool res = segments_intersect(a, b, c, d);
        REQUIRE(res);
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
};
