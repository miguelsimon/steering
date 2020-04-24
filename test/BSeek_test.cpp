
#include "BSeek.h"
#include <Eigen/Dense>

#include "catch2/catch.hpp"

using Eigen::Vector2f;

TEST_CASE("BSeek") {
    float max_force = 1;
    float desired_speed = 1;
    float dt = 1;
    Vector2f target = Vector2f({0, 0});
    Vector2f v = Vector2f({0, 0});
    float mass = 1.;

    SECTION("Already there") {
        Vector2f p = target;
        auto seek = BSeek(max_force, desired_speed, dt, target, p, v, mass);

        Vector2f force = seek.get_force();
        REQUIRE(force.norm() == Approx(0));
    }
    SECTION("Not there") {
        Vector2f p = Vector2f({1, 0});
        auto seek = BSeek(max_force, desired_speed, dt, target, p, v, mass);

        Vector2f force = seek.get_force();
        Vector2f expected = Vector2f({-1, 0});
        Vector2f difference = (force - expected);

        REQUIRE(difference.norm() == Approx(0));
    }

    SECTION("Respect max force") {
        Vector2f p = Vector2f({1, 0});
        float max_force = 0.5;
        auto seek = BSeek(max_force, desired_speed, dt, target, p, v, mass);

        Vector2f force = seek.get_force();
        Vector2f expected = Vector2f({-.5, 0});
        Vector2f difference = (force - expected);

        REQUIRE(difference.norm() == Approx(0));
    }
};
