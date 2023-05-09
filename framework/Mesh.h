#pragma once

#include "ImageTexture2DArray.h"
#include "Buffer.h"
#include "Program.h"
#include "math3d.h"
#include "Triangle.h"
#include "glfuncs.h"
#include <cassert>
#include <memory>

class Mesh{
public:
    
    std::shared_ptr<Buffer> pbuff;
    std::shared_ptr<Buffer> nbuff;
    std::shared_ptr<Buffer> tbuff;
        
    GLuint vao;

    unsigned numverts;
    float alpha;
    float refl;
    std::unique_ptr<ImageTexture2DArray> tex;
    
    vec3 bbox_min, bbox_max;
    
    std::vector<Triangle> triangles;
    
    /** Load OBJ file*/
    Mesh(std::string filename, float tx, float ty, float tz, float scale, vec3 color, float a, float R){
        alpha=a;
        refl=R;
        using namespace std;
        
        std::ifstream in(filename.c_str());
        if(!in.good() )
            throw std::runtime_error("Cannot open file '"+filename+"'");
            
        std::vector<vec3> FP;
        std::vector<vec3> FN;
        std::vector<vec2> FT;
        std::vector<vec3> P;
        std::vector<vec3> N;
        std::vector<vec2> T;
        
        bbox_min = vec3(1E99,1E99,1E99);
        bbox_max = vec3(-1E99,-1E99,-1E99);
        
        while(true){
            std::string line;
            std::getline(in,line);
            if(in.fail() )
                break;
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            if( word == "v" ){
                float x,y,z;
                iss >> x >> y >> z;
                FP.push_back(vec3(x,y,z));
            }
            else if( word == "vn" ){
                float x,y,z;
                iss >> x >> y >> z;
                FN.push_back(vec3(x,y,z));
            }
            else if( word == "vt" ){
                float x,y;
                iss >> x >> y;
                FT.push_back(vec2(x,y));
            }
            else if( word == "f" ){
                std::vector< std::array<uint32_t,3> > I;
                while(true){
                    iss >> word;
                    if( iss.fail() )
                        break;
                    char slash;
                    unsigned vi,ti,ni;
                    istringstream iss2(word);
                    iss2 >> vi >> slash >> ti >> slash >> ni;
                    if( iss2.fail() )
                        throw std::runtime_error("Bad mesh: Needs normals and textures: "+line);
                    I.push_back( std::array<uint32_t,3>{vi-1,ti-1,ni-1} );
                }
                for(unsigned i=2;i<I.size();++i){
                    P.push_back(FP[I[0][0]]);
                    T.push_back(FT[I[0][1]]);
                    N.push_back(FN[I[0][2]]);
                    
                    P.push_back(FP[I[i-1][0]]);
                    T.push_back(FT[I[i-1][1]]);
                    N.push_back(FN[I[i-1][2]]);
                     
                    P.push_back(FP[I[i][0]]);
                    T.push_back(FT[I[i][1]]);
                    N.push_back(FN[I[i][2]]);
                    
                    vec3 p[3] = {
                        FP[I[0][0]],
                        FP[I[i-1][0]],
                        FP[I[i][0]]
                    };
                    
                    for(int j=0;j<3;++j){
                        bbox_min.x = min( p[j].x, bbox_min.x );
                        bbox_min.y = min( p[j].y, bbox_min.y );
                        bbox_min.z = min( p[j].z, bbox_min.z );
                        bbox_max.x = max( p[j].x, bbox_max.x );
                        bbox_max.y = max( p[j].y, bbox_max.y );
                        bbox_max.z = max( p[j].z, bbox_max.z );
                    }
                    
                    Triangle tr(p[0],p[1],p[2]);
                    this->triangles.push_back(tr);
                }
            }
            else if( word == "mtllib" ){
                iss >> word;
                ifstream in2(word);
                while(true){
                    string line;
                    getline(in2,line);
                    istringstream iss(line);
                    iss >> word;
                    if( word == "map_Kd" ){
                        iss >> word;
                        tex = std::make_unique<ImageTexture2DArray>(word);
                        break;
                    }
                }
            }
        }
        
        this->numverts = P.size();
        
        pbuff = Buffer::create( P );
        nbuff = Buffer::create( N );
        tbuff = Buffer::create( T );
    
        GLuint tmp[1];
        glGenVertexArrays(1,tmp);
        vao = tmp[0];
        glBindVertexArray(vao);
        
        pbuff->bind(GL_ARRAY_BUFFER);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer( 0, 3, GL_FLOAT, false, 3*4, 0 );
        
        nbuff->bind(GL_ARRAY_BUFFER);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer( 1, 3, GL_FLOAT, false, 3*4, 0 );

        tbuff->bind(GL_ARRAY_BUFFER);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer( 2, 2, GL_FLOAT, false, 2*4, 0 );

        glBindVertexArray(0);
        this->vao = vao;
    }
    
    void draw(){
        tex->bind(0);
        glBindVertexArray(this->vao);
        Program::updateUniforms();
        glDrawArrays( GL_PATCHES, 0, numverts );
    }
};
