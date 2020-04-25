#ifndef PATHFOLLOWWORLD_H
#define PATHFOLLOWWORLD_H

#include "BPathFollow.h"
#include "boid.h"
#include "draw.h"
#include "world.h"
#include <Eigen/Dense>

class PathFollowWorld : public World {
  private:
    BPathFollow path_follow_;
    Boid boid_;
    void reset(Eigen::Vector2f start);
    float dt_ = 10;

  public:
    PathFollowWorld();
    void render(Draw &draw) override;
    void click(float x, float y) override;
    void step() override;
    float get_step_milliseconds() override;
};

#endif
