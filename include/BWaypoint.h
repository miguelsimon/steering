#ifndef BWAYPOINT_H
#define BWAYPOINT_H

#include <Eigen/Dense>
#include <vector>

#include "BSeek.h"

class BWaypoint {
  public:
    BWaypoint() = default;

    BWaypoint(float max_force, float desired_speed, float dt,
                Eigen::Vector2f p, Eigen::Vector2f v, float mass,
                std::vector<Eigen::Vector2f> path);
    Eigen::Vector2f get_force();

    std::vector<Eigen::Vector2f> path_;
    int path_idx_;

    void set_p(Eigen::Vector2f p);
    void set_v(Eigen::Vector2f v);

  private:
    BSeek seek_;
};

#endif
