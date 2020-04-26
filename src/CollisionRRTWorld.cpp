#include "CollisionRRTWorld.h"
#include "draw.h"
#include <Eigen/Dense>
#include <iostream>

using Eigen::Vector2f;

static auto circles_intersect(Vector2f p1, float r1, Vector2f p2, float r2)
    -> bool {
    float distance = (p1 - p2).norm();
    return distance < r1 + r2;
}

CollisionRRTProblem::CollisionRRTProblem() {
    obstacle_center_.emplace_back(Vector2f(50, 50));
    obstacle_radius_.push_back(15);

    obstacle_center_.emplace_back(Vector2f(50, 100));
    obstacle_radius_.push_back(10);

    obstacle_center_.emplace_back(Vector2f(300, 300));
    obstacle_radius_.push_back(60);
};

auto CollisionRRTProblem::random_state() -> Vector2f {
    std::uniform_real_distribution<float> x(ll_[0], ur_[0]);
    std::uniform_real_distribution<float> y(ll_[1], ur_[1]);

    const int max_retries = 1000;

    for (int i = 0; i < max_retries; i++) {
        auto p = Vector2f(x(rnd_generator_), y(rnd_generator_));
        if (is_free(p, actor_radius_)) {
            return p;
        };
    };
    std::cout << "Max retries exceeded when attempting to sample." << std::endl;
    exit(1);
};

auto CollisionRRTProblem::plan(Vector2f src, Vector2f dst)
    -> std::tuple<bool, Vector2f, Vector2f> {
    Vector2f delta = dst - src;
    float delta_norm = delta.norm();

    if (delta_norm > max_norm_) {
        delta = max_norm_ * delta.normalized();
    };

    Vector2f new_p = src + delta;

    if (!is_free(new_p, actor_radius_)) {
        // failed
        return std::make_tuple(false, new_p, delta);
    } else {
        return std::make_tuple(true, new_p, delta);
    };
};

auto CollisionRRTProblem::is_free(Eigen::Vector2f p, float radius) -> bool {
    for (int i = 0; i < obstacle_center_.size(); i++) {
        Vector2f o_p = obstacle_center_[i];
        float o_radius = obstacle_radius_[i];
        if (circles_intersect(p, radius, o_p, o_radius)) {
            return false;
        };
    };
    return true;
};

auto CollisionRRTProblem::goal_reached(Eigen::Vector2f p) -> bool {
    float distance = (p - goal_).norm();
    return distance < actor_radius_;
};

static void draw_action(Draw &draw, Vector2f src, Vector2f dst,
                        Vector2f action) {
    draw.segment(src, dst);
};

static void draw_problem(Draw &draw, CollisionRRTProblem &problem) {
    Vector2f ll = problem.ll_;
    Vector2f ur = problem.ur_;
    draw.segment(ll, Vector2f(ll[0], ur[1]));
    draw.segment(Vector2f(ll[0], ur[1]), ur);
    draw.segment(ur, Vector2f(ur[0], ll[1]));
    draw.segment(Vector2f(ur[0], ll[1]), ll);

    for (int i = 0; i < problem.obstacle_center_.size(); i++) {
        Vector2f o_p = problem.obstacle_center_[i];
        float o_radius = problem.obstacle_radius_[i];
        draw.circle(o_p, o_radius);
    };

    draw.target(problem.goal_);
};

static void draw_rrt(Draw &draw, RRT<Vector2f, Vector2f> &rrt,
                     CollisionRRTProblem &problem) {
    draw_problem(draw, problem);

    for (int i = 0; i < rrt.parents_.size(); i++) {
        Vector2f dst = rrt.vertices_[i + 1];
        Vector2f action = rrt.actions_[i];
        Vector2f src = rrt.vertices_[rrt.parents_[i]];
        draw_action(draw, src, dst, action);
    };
};

static void draw_solution(Draw &draw, RRT<Vector2f, Vector2f> &rrt,
                          CollisionRRTProblem &problem) {

    // start at solution
    int current_idx = rrt.nearest(problem.goal_);

    // backtrack to start
    while (current_idx != 0) {
        Vector2f current = rrt.vertices_.at(current_idx);
        draw.circle(current, problem.actor_radius_);
        current_idx = rrt.parents_.at(current_idx - 1);
    };
};

CollisionRRTWorld::CollisionRRTWorld() : rrt_({0, 0}), solved_(false) {
    reset(Vector2f());
};

auto CollisionRRTWorld::solve() -> bool {
    const int max_steps = 4000;
    for (int i = 0; i < max_steps; i++) {
        rrt_.step(problem_);
        size_t last_idx = rrt_.vertices_.size() - 1;
        Vector2f last = rrt_.vertices_[last_idx];
        if (problem_.goal_reached(last)) {
            return true;
        };
    };
    return false;
};

void CollisionRRTWorld::reset(Vector2f p) {
    rrt_ = RRT<Vector2f, Vector2f>(p);
    solved_ = false;

    if (solve()) {
        solved_ = true;
        std::cout << "Goal reached!" << std::endl;
    } else {
        std::cout << "Failed to reach goal" << std::endl;
    };
};

void CollisionRRTWorld::render(Draw &draw) {
    draw_rrt(draw, rrt_, problem_);
    if (solved_) {
        draw_solution(draw, rrt_, problem_);
    };
};

void CollisionRRTWorld::click(float x, float y) {
    Vector2f p(x, y);
    reset(p);
};

void CollisionRRTWorld::step(){};

auto CollisionRRTWorld::get_step_milliseconds() -> float { return dt_; };
