#include "draw.h"
#include <cassert>
#include <cmath>

using Eigen::Vector2f;
using Eigen::Vector2i;

Draw::Draw(SDL_Renderer *renderer) {
    renderer_ = renderer;
    scale_ = 1;
    origin_ = {0, 0};
};

void Draw::set_scale(float scale) { scale_ = scale; };

void Draw::set_origin(Eigen::Vector2f origin) { origin_ = origin; };

void Draw::clear() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);
};

void Draw::segment(Eigen::Vector2f a, Eigen::Vector2f b) {
    const int c = 255;

    Vector2i ai = to_screen(a);
    Vector2i bi = to_screen(b);

    SDL_SetRenderDrawColor(renderer_, c, c, c, SDL_ALPHA_OPAQUE);
    int res = SDL_RenderDrawLine(renderer_, ai[0], ai[1], bi[0], bi[1]);
    assert(res == 0);
}

void Draw::circle(Vector2f center, float radius) {
    // adapted this from box2d

    const int k_segments = 16;
    const float pi = 3.141592653589793238462643383279502884f;
    const float k_increment = 2.0f * pi / k_segments;
    float sinInc = sinf(k_increment);
    float cosInc = cosf(k_increment);
    Vector2f r1(1.0f, 0.0f);
    Vector2f v1 = center + radius * r1;
    for (int i = 0; i < k_segments; ++i) {
        // Perform rotation to avoid additional trigonometry.
        Vector2f r2;
        r2[0] = cosInc * r1[0] - sinInc * r1[1];
        r2[1] = sinInc * r1[0] + cosInc * r1[1];
        Vector2f v2 = center + radius * r2;
        segment(v1, v2);
        r1 = r2;
        v1 = v2;
    }
};

void Draw::target(Vector2f pos) {
    Vector2f x({5, 0});
    Vector2f y({0, 5});
    segment(pos - x, pos + x);
    segment(pos - y, pos + y);
};

auto Draw::to_screen(Vector2f p) -> Vector2i {
    Vector2f res = ((p - origin_) * scale_).array().round();
    return res.cast<int>();
};

auto Draw::from_screen(Vector2i p) -> Vector2f {
    return (p.cast<float>() / scale_) + origin_;
};
