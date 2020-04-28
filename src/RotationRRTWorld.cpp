#include "RotationRRTWorld.h"
#include "draw.h"
#include <Eigen/Dense>
#include <iostream>

using Eigen::Vector2f;
using Eigen::Vector3f;

static auto project(Vector3f p) -> Vector2f { return Vector2f(p[0], p[1]); };

static void draw_action(Draw &draw, Vector3f src, Vector3f dst,
                        Vector3f action) {
    draw.segment(project(src), project(dst));
};

static void draw_problem(Draw &draw, RotationRRTProblem &problem) {
    Vector2f ll = project(problem.ll_);
    Vector2f ur = project(problem.ur_);

    for (int i = 0; i < problem.obstacle_a_.size(); i++) {
        draw.segment(problem.obstacle_a_[i], problem.obstacle_b_[i]);
    };

    draw.target(project(problem.goal_));
};

static void draw_rrt(Draw &draw, RRT<Vector3f, Vector3f> &rrt,
                     RotationRRTProblem &problem) {
    draw_problem(draw, problem);

    auto draw_lambda = [draw](Vector3f src, Vector3f dst,
                              Vector3f action) mutable {
        draw_action(draw, src, dst, action);
    };

    rrt.visit(draw_lambda);
};

static void draw_solution(Draw &draw, RRT<Vector3f, Vector3f> &rrt,
                          RotationRRTProblem &problem) {

    // start at solution
    int solution_idx = rrt.nearest(problem.goal_);

    auto draw_lambda = [draw, problem](Vector3f src, Vector3f dst,
                                       Vector3f action) mutable {
        auto [a, b] =
            problem.to_segment_endpoints(dst, problem.segment_length_);
        draw.segment(a, b);
    };

    rrt.visit_path(solution_idx, draw_lambda);
};

RotationRRTWorld::RotationRRTWorld() : rrt_({0, 0, 0}), solved_(false) {
    problem_.obstacle_a_.push_back(Vector2f(100, 100));
    problem_.obstacle_b_.push_back(Vector2f(100, 300));

    problem_.obstacle_a_.push_back(Vector2f(0, 300));
    problem_.obstacle_b_.push_back(Vector2f(300, 300));

    problem_.obstacle_a_.push_back(Vector2f(300, 300));
    problem_.obstacle_b_.push_back(Vector2f(300, 0));
    reset(Vector2f());
};

void RotationRRTWorld::reset(Vector2f p) {
    rrt_ = RRT<Vector3f, Vector3f>(Vector3f(p[0], p[1], 0));
    solved_ = false;
};

void RotationRRTWorld::render(Draw &draw) {
    draw_rrt(draw, rrt_, problem_);
    if (solved_) {
        draw_solution(draw, rrt_, problem_);
    };
};

void RotationRRTWorld::click(float x, float y) {
    Vector2f p(x, y);
    reset(p);
};

auto RotationRRTWorld::attempt() -> bool {
    rrt_.step(problem_);
    size_t last_idx = rrt_.size() - 1;
    Vector3f last = rrt_.get_vertex(last_idx);
    return problem_.goal_reached(last);
};

void RotationRRTWorld::step() {
    const int max_tree_size = 10000;
    const int attempts_per_step = 10;

    int tree_size = rrt_.size();

    if (!solved_ && tree_size < max_tree_size) {
        for (int i = 0; i < attempts_per_step; i++) {
            solved_ = attempt();
            if (solved_)
                break;
        };
    };
};

auto RotationRRTWorld::get_step_milliseconds() -> float { return dt_; };
