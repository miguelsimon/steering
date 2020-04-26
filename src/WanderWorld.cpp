#include "WanderWorld.h"
#include "boid.h"
#include "draw.h"
#include <Eigen/Dense>

using Eigen::Vector2f;

WanderWorld::WanderWorld() { reset(); };

void WanderWorld::reset() {
    boid_ = Boid({150, 150}, 10);
    float max_force = 1;
    float desired_speed = 0.1;

    wander_ =
        BWander(max_force, desired_speed, dt_, boid_.p_, boid_.v_, boid_.m_);

    wander_.rnd_generator_ = std::default_random_engine(time(0));
};

void WanderWorld::render(Draw &draw) {
    draw.circle(boid_.p_, boid_.r_);
    wander_.draw(draw);
};

void WanderWorld::click(float x, float y) { reset(); };

void WanderWorld::step() {
    wander_.set_p(boid_.p_);
    wander_.set_v(boid_.v_);

    Vector2f force = wander_.get_force();
    boid_.f_ = force;

    float dt = get_step_milliseconds();
    boid_.step(dt);
};

auto WanderWorld::get_step_milliseconds() -> float { return dt_; };
