#pragma once

#include "glfuncs.h"
#include "Texture.h"

class Texture2DArray : public Texture {
public:
    Texture2DArray(int w, int h, int slices) : Texture(GL_TEXTURE_2D_ARRAY) {
        this->w=w;
        this->h=h;
        this->slices=slices;
    }
};
