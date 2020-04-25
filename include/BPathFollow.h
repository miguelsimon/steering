#ifndef BPATHFOLLOW_H
#define BPATHFOLLOW_H

#include <Eigen/Dense>
#include <vector>

#include "BSeek.h"

class BPathFollow {
  public:
    BPathFollow() = default;

    BPathFollow(float max_force, float desired_speed, float dt,
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
