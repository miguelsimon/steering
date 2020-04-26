#ifndef RotationRRTProblem_H
#define RotationRRTProblem_H

#include "RRT.h"
#include "draw.h"
#include "world.h"
#include <Eigen/Dense>
#include <cmath>

auto segments_intersect(Eigen::Vector2f a, Eigen::Vector2f b, Eigen::Vector2f c,
                        Eigen::Vector2f d) -> bool;

class RotationRRTProblem : public RRTProblem<Eigen::Vector3f, Eigen::Vector3f> {
  public:
    RotationRRTProblem();
    auto random_state() -> Eigen::Vector3f override;
    auto plan(Eigen::Vector3f src, Eigen::Vector3f dst)
        -> std::tuple<bool, Eigen::Vector3f, Eigen::Vector3f> override;
    auto is_free(Eigen::Vector3f p) -> bool;
    auto goal_reached(Eigen::Vector3f p) -> bool;

    float max_norm_ = 2;

    Eigen::Vector3f ll_ = Eigen::Vector3f(0, 0, 0);
    Eigen::Vector3f ur_ = Eigen::Vector3f(400, 400, 2 * M_PI);

    Eigen::Vector3f goal_ = Eigen::Vector3f(200, 200, M_PI);

    float segment_length_ = 20;
    float goal_radius_ = 2;

    // segment obstacle endpoints
    std::vector<Eigen::Vector2f> obstacle_a_;
    std::vector<Eigen::Vector2f> obstacle_b_;

  private:
    std::default_random_engine rnd_generator_;
};

#endif
