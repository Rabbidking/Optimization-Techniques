#include "utils.h"
#include "Mesh.h"
#include "Program.h"
#include "Text.h"
#include "Framebuffer.h" 


std::map<std::string,std::array<int,4> >    Program::           uniforms;
Program*                                    Program::           current;
std::shared_ptr<Buffer>                     Program::           uboBuffer;
std::vector<char>                           Program::           uboBackingMemory;
std::shared_ptr<Program>                    Text::              prog;
Framebuffer*                                Framebuffer::       current;
int                                         Framebuffer::       saved_viewport[4];
std::map<std::array<int,3>, std::shared_ptr<Framebuffer> >      Framebuffer::blurHelpers;
std::map<int, std::vector<vec4> >           Framebuffer::       blurWeights;
std::shared_ptr<Program>                    Framebuffer::       blurProgram;
std::shared_ptr<ImageTexture2DArray>        Text::              fontsheet;
int                                         Text::              vao; 
UnitSquare*                                 UnitSquare::        usq;
