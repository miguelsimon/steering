#include "WaypointWorld.h"
#include "BWaypoint.h"
#include "boid.h"
#include "draw.h"
#include <Eigen/Dense>

using Eigen::Vector2f;

WaypointWorld::WaypointWorld() { reset({0, 0}); };

void WaypointWorld::reset(Eigen::Vector2f start) {
    boid_ = Boid(start, 10);

    auto path = std::vector<Vector2f>();

    path.emplace_back(50, 50);
    path.emplace_back(100, 100);
    path.emplace_back(200, 100);
    path.emplace_back(200, 200);

    float max_force = 1;
    float desired_speed = 0.1;

    path_follow_ = BWaypoint(max_force, desired_speed, dt_, boid_.p_, boid_.v_,
                             boid_.m_, path);
};

void WaypointWorld::render(Draw &draw) {
    draw.circle(boid_.p_, boid_.r_);

    auto path = path_follow_.path_;

    for (int i = 0; i < path.size() - 1; i++) {
        draw.segment(path[i], path[i + 1]);
    };
};

void WaypointWorld::click(float x, float y) { reset({x, y}); };

void WaypointWorld::step() {
    path_follow_.set_p(boid_.p_);
    path_follow_.set_v(boid_.v_);

    Vector2f force = path_follow_.get_force();
    boid_.f_ = force;

    float dt = get_step_milliseconds();
    boid_.step(dt);
};

auto WaypointWorld::get_step_milliseconds() -> float { return dt_; };
