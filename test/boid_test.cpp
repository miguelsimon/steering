
#include "boid.h"
#include "catch2/catch.hpp"

TEST_CASE("Boid") {
    Boid b = Boid({0, 0}, 10);
    b.step(1);
    CHECK(b.p_[0] == Approx(0));
    CHECK(b.p_[1] == Approx(0));

    b.v_ = {1, 0};
    b.f_ = {0, 1};
    b.step(1);
    CHECK(b.p_[0] == Approx(1));
    CHECK(b.p_[1] == Approx(0));

    CHECK(b.v_[0] == Approx(1));
    CHECK(b.v_[1] == Approx(1));
};
