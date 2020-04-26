#ifndef COLLISIONRRTWORLD_H
#define COLLISIONRRTWORLD_H

#include "RRT.h"
#include "draw.h"
#include "world.h"
#include <Eigen/Dense>

class CollisionRRTProblem
    : public RRTProblem<Eigen::Vector2f, Eigen::Vector2f> {
  public:
    CollisionRRTProblem();
    auto random_state() -> Eigen::Vector2f override;
    auto plan(Eigen::Vector2f src, Eigen::Vector2f dst)
        -> std::tuple<bool, Eigen::Vector2f, Eigen::Vector2f> override;
    auto is_free(Eigen::Vector2f p, float radius) -> bool;
    auto goal_reached(Eigen::Vector2f p) -> bool;

    float max_norm_ = 2;

    Eigen::Vector2f ll_ = Eigen::Vector2f(0, 0);
    Eigen::Vector2f ur_ = Eigen::Vector2f(400, 400);

    Eigen::Vector2f goal_ = Eigen::Vector2f(200, 200);

    float actor_radius_ = 10;
    std::vector<Eigen::Vector2f> obstacle_center_;
    std::vector<float> obstacle_radius_;

  private:
    std::default_random_engine rnd_generator_;
};

class CollisionRRTWorld : public World {
  private:
    Eigen::Vector2f target_;
    RRT<Eigen::Vector2f, Eigen::Vector2f> rrt_;
    CollisionRRTProblem problem_;
    float dt_ = 100;
    bool solved_;
    auto attempt() -> bool;

  public:
    CollisionRRTWorld();
    void render(Draw &draw) override;
    void click(float x, float y) override;
    void step() override;
    auto get_step_milliseconds() -> float override;
    void reset(Eigen::Vector2f);
};

#endif
