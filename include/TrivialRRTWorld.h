#ifndef TRIVIALRRTWORLD_H
#define TRIVIALRRTWORLD_H

#include "RRT.h"
#include "draw.h"
#include "world.h"
#include <Eigen/Dense>

class TrivialRRTProblem : public RRTProblem<Eigen::Vector2f, Eigen::Vector2f> {
  public:
    auto random_state() -> Eigen::Vector2f override;
    auto plan(Eigen::Vector2f src, Eigen::Vector2f dst)
        -> std::tuple<bool, Eigen::Vector2f, Eigen::Vector2f> override;

    float max_norm_ = 2;
    Eigen::Vector2f ll_ = Eigen::Vector2f(0, 0);
    Eigen::Vector2f ur_ = Eigen::Vector2f(200, 200);

  private:
    std::default_random_engine rnd_generator_;
};

class TrivialRRTWorld : public World {
  private:
    Eigen::Vector2f target_;
    RRT<Eigen::Vector2f, Eigen::Vector2f> rrt_;
    TrivialRRTProblem problem_;
    float dt_ = 100;

  public:
    TrivialRRTWorld();
    void render(Draw &draw) override;
    void click(float x, float y) override;
    void step() override;
    auto get_step_milliseconds() -> float override;
    void reset(Eigen::Vector2f);
};

#endif
