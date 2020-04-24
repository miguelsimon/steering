#ifndef BOID_WORLD_H
#define BOID_WORLD_H

#include "boid.h"
#include "world.h"
#include <Eigen/Dense>
#include <SDL.h>
#include <vector>

class BoidWorld : public World {
  private:
    Eigen::Vector2f target_;
    std::vector<Boid> boids_;

  public:
    BoidWorld();
    void render(Draw &draw) override;
    void click(float x, float y) override;
    void step() override;
    float get_step_milliseconds() override;
};

#endif
