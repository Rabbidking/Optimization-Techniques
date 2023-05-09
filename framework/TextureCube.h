#pragma once

#include "Texture.h"

class TextureCube : public Texture {
    public:
    TextureCube(unsigned size) : Texture( GL_TEXTURE_CUBE_MAP ){
        this->w=size;
        this->h=size;
    }
};
