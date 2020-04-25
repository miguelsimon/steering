#ifndef ARRIVEWORLD_H
#define ARRIVEWORLD_H

#include "boid.h"
#include "draw.h"
#include "world.h"
#include <Eigen/Dense>

class ArriveWorld : public World {
  private:
    Eigen::Vector2f target_;
    Boid boid_;

  public:
    ArriveWorld();
    void render(Draw &draw) override;
    void click(float x, float y) override;
    void step() override;
    auto get_step_milliseconds() -> float override;
};

#endif
