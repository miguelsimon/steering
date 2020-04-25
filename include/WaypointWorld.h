#ifndef WaypointWorld_H
#define WaypointWorld_H

#include "BWaypoint.h"
#include "boid.h"
#include "draw.h"
#include "world.h"
#include <Eigen/Dense>

class WaypointWorld : public World {
  private:
    BWaypoint path_follow_;
    Boid boid_;
    void reset(Eigen::Vector2f start);
    float dt_ = 10;

  public:
    WaypointWorld();
    void render(Draw &draw) override;
    void click(float x, float y) override;
    void step() override;
    auto get_step_milliseconds() -> float override;
};

#endif
