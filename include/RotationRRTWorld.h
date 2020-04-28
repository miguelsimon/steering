#ifndef ROTATIONRRTWORLD_H
#define ROTATIONRRTWORLD_H

#include "RRT.h"
#include "RotationRRTProblem.h"
#include "draw.h"
#include "world.h"
#include <Eigen/Dense>

class RotationRRTWorld : public World {
  private:
    Eigen::Vector2f target_;
    RRT<Eigen::Vector3f, Eigen::Vector3f> rrt_;
    RotationRRTProblem problem_;
    float dt_ = 1;
    bool solved_;
    auto attempt() -> bool;

  public:
    RotationRRTWorld();
    void render(Draw &draw) override;
    void click(float x, float y) override;
    void step() override;
    auto get_step_milliseconds() -> float override;
    void reset(Eigen::Vector2f);
};

#endif
