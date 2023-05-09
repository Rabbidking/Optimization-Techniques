#include <set>
#include <map>
#include <vector>
#include <memory>
#include <array>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cassert>
#include <SDL.h>

void APIENTRY debugCallback(GLenum source, GLenum msgType, GLuint msgId, GLenum severity,
    GLsizei length, const GLchar* message, const void* param ){
    std::cerr << msgId << ": " << message << "\n";
    if(severity == GL_DEBUG_SEVERITY_HIGH){
        assert(0);
    }
}

SDL_Window* winsetup(){
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
    
    int WIN_WIDTH=512;
    int WIN_HEIGHT=512;
    auto win = SDL_CreateWindow( "ETGG",20,20, WIN_WIDTH,WIN_HEIGHT, SDL_WINDOW_OPENGL);
    if(!win){
        throw std::runtime_error("Cannot create window\n");
    }

    auto rc = SDL_GL_CreateContext(win);
    if( !rc ){
        throw std::runtime_error("Cannot create GL context\n");
    }
    
    glDebugMessageCallback( debugCallback, nullptr );
    
    // Source, type, severity, count, ids, enabled
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
        0, 0, true );
        
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_DEBUG_OUTPUT);

    //~ //turn off the buffer messages that nVidia drivers like to give
    //~ GLuint tmp[1] = {131185} ;
    //~ glDebugMessageControl( 
        //~ GL_DEBUG_SOURCE_API, 
        //~ GL_DEBUG_TYPE_OTHER, 
        //~ GL_DONT_CARE,
        //~ 1, tmp, 0 );

    //turn off nVidia's spurious mipmap warning
    GLuint tmp[1] = {131204};
    glDebugMessageControl( 
        GL_DEBUG_SOURCE_API, 
        GL_DEBUG_TYPE_OTHER, 
        GL_DONT_CARE,
        1, tmp, 0 );
        
        
    SDL_GL_SetSwapInterval(0);
    
    return win;
}

