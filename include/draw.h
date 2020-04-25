#ifndef SRC_DRAW_H
#define SRC_DRAW_H

#include <Eigen/Dense>
#include <SDL.h>

class Draw {
  public:
    Draw(SDL_Renderer *renderer);
    void set_scale(float scale);
    void set_origin(Eigen::Vector2f origin);
    void clear();
    void segment(Eigen::Vector2f a, Eigen::Vector2f b);
    void circle(Eigen::Vector2f center, float r);
    void target(Eigen::Vector2f pos);

    auto to_screen(Eigen::Vector2f p) -> Eigen::Vector2i;
    auto from_screen(Eigen::Vector2i p) -> Eigen::Vector2f;

  private:
    SDL_Renderer *renderer_;
    float scale_;
    Eigen::Vector2f origin_;
};

#endif
