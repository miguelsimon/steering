#ifndef SEEKWORLD_H
#define SEEKWORLD_H

#include "boid.h"
#include "draw.h"
#include "world.h"
#include <Eigen/Dense>

class SeekWorld : public World {
  private:
    Eigen::Vector2f target_;
    Boid boid_;

  public:
    SeekWorld();
    void render(Draw &draw) override;
    void click(float x, float y) override;
    void step() override;
    auto get_step_milliseconds() -> float override;
};

#endif
