#include "SeekWorld.h"
#include "BSeek.h"
#include "boid.h"
#include "draw.h"
#include <Eigen/Dense>

using Eigen::Vector2f;

SeekWorld::SeekWorld() : target_({0, 0}), boid_({0, 0}){};

void SeekWorld::render(Draw &draw) {
    draw.target(target_);
    draw.boid(boid_.p_);
};

void SeekWorld::click(float x, float y) { target_ = {x, y}; };

void SeekWorld::step() {
    float max_force = 1;
    float desired_speed = 0.2;
    float dt = get_step_milliseconds();

    auto seek = BSeek(max_force, desired_speed, dt, target_, boid_.p_, boid_.v_,
                      boid_.m_);
    Vector2f force = seek.get_force();
    boid_.f_ = force;
    boid_.step(dt);
};

auto SeekWorld::get_step_milliseconds() -> float {
    const float step_milliseconds = 10;
    return step_milliseconds;
};
