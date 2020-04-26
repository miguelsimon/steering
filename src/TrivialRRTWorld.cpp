#include "TrivialRRTWorld.h"
#include "draw.h"
#include <Eigen/Dense>
#include <iostream>

using Eigen::Vector2f;

auto TrivialRRTProblem::random_state() -> Vector2f {
    std::uniform_real_distribution<float> x(ll_[0], ur_[0]);
    std::uniform_real_distribution<float> y(ll_[1], ur_[1]);
    return Vector2f(x(rnd_generator_), y(rnd_generator_));
};

auto TrivialRRTProblem::plan(Vector2f src, Vector2f dst)
    -> std::tuple<bool, Vector2f, Vector2f> {
    Vector2f delta = dst - src;
    float delta_norm = delta.norm();

    if (delta_norm > max_norm_) {
        delta = max_norm_ * delta.normalized();
    };
    return std::make_tuple(true, src + delta, delta);
};

static void draw_action(Draw &draw, Vector2f src, Vector2f dst,
                        Vector2f action) {
    draw.segment(src, dst);
};

static void draw_problem(Draw &draw, TrivialRRTProblem &problem) {
    Vector2f ll = problem.ll_;
    Vector2f ur = problem.ur_;
    draw.segment(ll, Vector2f(ll[0], ur[1]));
    draw.segment(Vector2f(ll[0], ur[1]), ur);
    draw.segment(ur, Vector2f(ur[0], ll[1]));
    draw.segment(Vector2f(ur[0], ll[1]), ll);
};

static void draw_rrt(Draw &draw, RRT<Vector2f, Vector2f> &rrt,
                     TrivialRRTProblem &problem) {
    draw_problem(draw, problem);

    for (int i = 0; i < rrt.parents_.size(); i++) {
        Vector2f dst = rrt.vertices_[i + 1];
        Vector2f action = rrt.actions_[i];
        Vector2f src = rrt.vertices_[rrt.parents_[i]];
        draw_action(draw, src, dst, action);
    };
};

TrivialRRTWorld::TrivialRRTWorld() : rrt_({0, 0}) { reset(Vector2f()); };

void TrivialRRTWorld::reset(Vector2f p) {
    rrt_ = RRT<Vector2f, Vector2f>(p);

    for (int i = 0; i < 200; i++) {
        rrt_.step(problem_);
    };
};

void TrivialRRTWorld::render(Draw &draw) { draw_rrt(draw, rrt_, problem_); };

void TrivialRRTWorld::click(float x, float y) {
    Vector2f p(x, y);
    reset(p);
};

void TrivialRRTWorld::step(){};

auto TrivialRRTWorld::get_step_milliseconds() -> float { return dt_; };
