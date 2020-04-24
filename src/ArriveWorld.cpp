#include "ArriveWorld.h"
#include "BArrive.h"
#include "boid.h"
#include "draw.h"
#include <Eigen/Dense>

using Eigen::Vector2f;

ArriveWorld::ArriveWorld() : target_({0, 0}), boid_({0, 0}){};

void ArriveWorld::render(Draw &draw) {
    draw.target(target_);
    draw.boid(boid_.p_);
};

void ArriveWorld::click(float x, float y) { target_ = {x, y}; };

void ArriveWorld::step() {
    float max_force = 1;
    float desired_speed = 0.2;
    float slow_radius = 10;
    float dt = get_step_milliseconds();

    auto arrive = BArrive(max_force, desired_speed, dt, target_, boid_.p_,
                          boid_.v_, boid_.m_, slow_radius);
    Vector2f force = arrive.get_force();
    boid_.f_ = force;
    boid_.step(dt);
};

auto ArriveWorld::get_step_milliseconds() -> float {
    const float step_milliseconds = 10;
    return step_milliseconds;
};
