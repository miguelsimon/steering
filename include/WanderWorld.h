#ifndef WANDERWORLD_H
#define WANDERWORLD_H

#include "BWander.h"
#include "boid.h"
#include "draw.h"
#include "world.h"
#include <Eigen/Dense>

class WanderWorld : public World {
  private:
    BWander wander_;
    Boid boid_;
    void reset();

  public:
    WanderWorld();
    void render(Draw &draw) override;
    void click(float x, float y) override;
    void step() override;
    float get_step_milliseconds() override;
    float dt_ = 10;
};

#endif
