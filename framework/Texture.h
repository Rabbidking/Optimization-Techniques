#pragma once
#include "glfuncs.h"

class Texture{
public:
    GLenum type;
    GLuint tex=0;
    int w=0;
    int h=0;
    int slices=0;
    
    Texture(GLenum typ) : type(typ){
    }
    void bind(int unit){
        assert(tex != 0);
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(type,tex);  
    }
    
    void unbind(int unit){
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(type,0);
    }
    void generateMipmap(){
        this->bind(0);
        glGenerateMipmap(this->type);
        this->unbind(0);
    }
        
    void bindImage(int unit, GLenum fmt=GL_RGBA8){
        //unit, texture, mip level, layered, layer, access, format
        glBindImageTexture(unit,tex,0,GL_TRUE,0,GL_READ_WRITE,fmt);
    }

    static
    void unbindImage(int unit){
        //unit, texture, mip level, layered, layer, access, format
        glBindImageTexture(unit,0,0,false,0,GL_READ_WRITE,GL_RGBA8);
    }


};
