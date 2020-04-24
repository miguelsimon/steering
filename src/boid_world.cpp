#include "boid_world.h"
#include "boid.h"
#include "draw.h"
#include <Eigen/Dense>

void draw_boid(Draw &draw, Eigen::Vector2f pos) { draw.circle(pos, 10); };

BoidWorld::BoidWorld() {

    const float target = 100;
    const float speed = 10.;

    target_ = {target, target};

    auto boid = Boid({target, target});
    boid.v_ = {speed, speed};

    boids_.push_back(boid);
};

void BoidWorld::render(Draw &draw) {
    draw_boid(draw, target_);

    for (auto const &boid : boids_) {
        draw_boid(draw, boid.p_);
    };
};

void BoidWorld::click(float x, float y) { target_ = {x, y}; };

void BoidWorld::step() {
    const float dt = 0.01;
    for (auto &boid : boids_) {
        boid.step(dt);
    };
};

auto BoidWorld::get_step_milliseconds() -> float {
    const float step_milliseconds = 10;
    return step_milliseconds;
};
