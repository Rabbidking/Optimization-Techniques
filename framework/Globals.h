#pragma once 

#include "utils.h"
#include "Mesh.h"
#include "Text.h"
#include "Framebuffer.h"
#include "UnitSquare.h" 
#include "Scene.h"
#include "ImageTexture2DArray.h"

class Globals {
    public:
    Program mainProg{"vs.txt", "tcs.txt", "tes.txt", "fs.txt"};
    Sampler mipsampler{true};
    Sampler linearsampler{false};
    Text text1{ vec2(10,35), ""};
    Text text2{ vec2(10,10), ""};
    Scene scene{"scene1.txt"};
    std::set<int> keyset;
    bool paused=false;
    ImageTexture2DArray heightmap{"heightmap.png"};
	float scale = 1.0f;
};