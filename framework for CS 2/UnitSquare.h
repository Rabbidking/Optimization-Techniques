#pragma once

#include "ImageTexture2DArray.h"
#include "Buffer.h"
#include "Program.h"
#include "math3d.h"
#include "glfuncs.h"
#include <cassert>

class UnitSquare{
    GLuint vao;
    std::shared_ptr<Buffer> pbuff;
    std::shared_ptr<Buffer> tbuff;
    std::shared_ptr<Buffer> nbuff;
    std::shared_ptr<Buffer> ibuff;
    static UnitSquare* usq;
    UnitSquare(){
        std::vector<float> pos( {-1,1,-1,  -1,-1,-1,  1,1,-1,  1,-1,-1 } );
        std::vector<float> tex( {0,1,  0,0,   1,1,  1,0} );
        std::vector<float> nor( {0,0,1, 0,0,1, 0,0,1, 0,0,1} );
        std::vector<std::uint32_t> ind( {0,1,2,  2,1,3} );
        
        pbuff = Buffer::create(pos);
        tbuff = Buffer::create(tex);
        nbuff = Buffer::create(nor);
        ibuff = Buffer::create(ind);
        
        GLuint tmp[1];
        glGenVertexArrays(1,tmp);
        vao = tmp[0];
        glBindVertexArray(vao);
        ibuff->bind(GL_ELEMENT_ARRAY_BUFFER);
        
        pbuff->bind(GL_ARRAY_BUFFER);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer( 0, 3, GL_FLOAT, false, 3*4, 0 );
        
        nbuff->bind(GL_ARRAY_BUFFER);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer( 1, 3, GL_FLOAT, false, 3*4, 0 );

        tbuff->bind(GL_ARRAY_BUFFER);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer( 2, 2, GL_FLOAT, false, 2*4, 0 );

        glBindVertexArray(0);
    }
    public:
    static void draw(){
        if( !usq )
            usq = new UnitSquare();
        glBindVertexArray(usq->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, ((char*)0) );
        glBindVertexArray(0);
    }
};
