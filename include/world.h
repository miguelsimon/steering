#ifndef SRC_WORLD_H
#define SRC_WORLD_H

#include "draw.h"
#include <SDL.h>

class World {

  public:
    virtual void render(Draw &draw) = 0;
    virtual void click(float x, float y) = 0;
    virtual void step() = 0;
    virtual float get_step_milliseconds() = 0;
};

#endif
