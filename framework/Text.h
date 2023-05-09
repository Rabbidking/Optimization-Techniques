#pragma once

#include "utils.h"

class Text{
  public:   
    static std::shared_ptr<Program> prog;
    static std::shared_ptr<ImageTexture2DArray> fontsheet;
    static int vao;
    int numChars;
    vec2 pos;
    std::shared_ptr<DataTexture2DArray> datatex;
    vec3 color;
    
    Text(vec2 p, std::string s){
        if( !prog ){
            prog = std::make_shared<Program>("textvs.txt","textgs.txt","textfs.txt");
            fontsheet = std::make_shared<ImageTexture2DArray>("consolefont14.png");
             GLuint tmp[1];
            glGenVertexArrays(1,tmp);
            vao = tmp[0];
            glBindVertexArray(vao);
            auto P = Buffer::create(std::vector<float>{ 0,0,0 } );
            P->bind(GL_ARRAY_BUFFER);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer( 0, 3, GL_FLOAT, false, 3*4, 0 );
            glBindVertexArray(0);
        }
        
        this->pos = p;
        this->color = vec3(1,1,1);
        datatex = std::make_shared<DataTexture2DArray>(1,1,1, GL_R32F, GL_RGBA, GL_UNSIGNED_BYTE );
        setText(s);
    }

    void setText(std::string s){
        std::vector<float> v;
        v.reserve(s.length());
        for(unsigned i=0;i<s.length();++i){
            v.push_back(s[i]);
        }
        datatex->setData(s.length(),1,1, GL_R32F, GL_RED, GL_FLOAT, v.data() );
        numChars = s.length();
    }
    
    void draw(){
        glDisable(GL_DEPTH_TEST);
        auto curr = Program::current;
        glBindVertexArray(vao);
        prog->use();
        Program::setUniform("textColor", color);
        Program::setUniform("textOrigin",pos);
        Program::setUniform("charCellSize",vec2(10,20));
        Program::setUniform("numCharCells", vec2(25,6));
        Program::updateUniforms();
        fontsheet->bind(0);
        datatex->bind(1);
        glDrawArraysInstanced( GL_POINTS, 0,1, numChars );
        glEnable(GL_DEPTH_TEST);
        if( curr )
            curr->use();
    }
};
