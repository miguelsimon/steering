
#include "RRT.h"
#include <Eigen/Dense>

#include "catch2/catch.hpp"

using Eigen::Vector2f;

namespace {
class Problem : RRTProblem<Vector2f, Vector2f> {
  public:
    auto random_state() -> Vector2f override;
    auto plan(Vector2f src, Vector2f dst)
        -> std::tuple<bool, Vector2f, Vector2f> override;
};

auto Problem::random_state() -> Vector2f { return Vector2f(0, 0); };

auto Problem::plan(Vector2f src, Vector2f dst)
    -> std::tuple<bool, Vector2f, Vector2f> {
    return std::make_tuple(false, Vector2f(0, 0), Vector2f(0, 0));
};
}; // namespace

TEST_CASE("RRTProblem instantiation test") {
    SECTION("random_state") {
        auto problem = Problem();
        problem.random_state();
    };

    SECTION("plan") {
        auto problem = Problem();
        problem.plan(Vector2f(0, 0), Vector2f(0, 0));
    };
};

TEST_CASE("RRT") {
    SECTION("Add and check nearest") {
        RRT<Vector2f, Vector2f> rrt({0, 0});
        auto p = Vector2f(1, 1);
        auto action = Vector2f(0, 0);
        rrt.add_vertex(0, p, action);
        int nearest = rrt.nearest(p);
        REQUIRE(nearest == 1);
    };
    SECTION("Add 2 and check nearest") {
        RRT<Vector2f, Vector2f> rrt({0, 0});
        auto p1 = Vector2f(1, 1);
        auto p2 = Vector2f(2, 2);
        auto action = Vector2f(0, 0);
        int idx1 = rrt.add_vertex(0, p1, action);
        int idx2 = rrt.add_vertex(0, p2, action);

        int nearest1 = rrt.nearest(p1);
        REQUIRE(nearest1 == idx1);

        int nearest2 = rrt.nearest(p2);
        REQUIRE(nearest2 == idx2);
    };
};
