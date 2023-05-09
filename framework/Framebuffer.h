#pragma once

#include "DataTexture2DArray.h"
#include "utils.h"
#include "UnitSquare.h"

class Framebuffer{
    public:

    static Framebuffer* current;
    
    //saved viewport
    static int saved_viewport[4];

    std::vector<GLenum> drawbuffers;
    std::shared_ptr<DataTexture2DArray> texture;
    std::shared_ptr<DataTexture2DArray> depthtexture;
    GLuint fbo;
    
    GLenum format;
    
    static std::map<std::array<int,3>, std::shared_ptr<Framebuffer> > blurHelpers;
    static std::map<int, std::vector<vec4> > blurWeights;
    static const int MAX_BLUR_RADIUS = 30;
    static std::shared_ptr<Program> blurProgram;
    int w,h;
    
    Framebuffer(int width, int height,  int slices, GLenum format){
        this->w=width;
        this->h=height;
        this->format = format;
        texture = std::make_shared<DataTexture2DArray>(width,height,slices,format,GL_RGBA,GL_UNSIGNED_BYTE);
        depthtexture = std::make_shared<DataTexture2DArray>(width,height,1,GL_DEPTH24_STENCIL8,GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8);
        GLuint tmp[1];
        glGenFramebuffers(1,tmp);
        this->fbo = tmp[0];
        glBindFramebuffer(GL_FRAMEBUFFER, fbo );
        for(int i=0;i<slices;++i){
            //target, attachment, texture, mip level, layer
            glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0+i, texture->tex, 0, i);
        }
        glFramebufferTextureLayer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT, depthtexture->tex, 0, 0 );
            
        int complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if( complete != GL_FRAMEBUFFER_COMPLETE ){
            throw std::runtime_error("Framebuffer is not complete");
        }
        drawbuffers.resize(slices);
        for(int i=0;i<slices;++i)
            drawbuffers[i] = GL_COLOR_ATTACHMENT0+i;
        glBindFramebuffer(GL_FRAMEBUFFER,0);
    }
    
    void setAsRenderTarget(bool clear){
        if( current )
            current->unsetAsRenderTarget();
        glGetIntegerv(GL_VIEWPORT,saved_viewport);
        current = this;
        glBindFramebuffer(GL_FRAMEBUFFER,fbo);
        glDrawBuffers(drawbuffers.size(),drawbuffers.data());
        glViewport(0,0,texture->w,texture->h);
        if( clear )
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      
    }
    
    void unsetAsRenderTarget(){
        current = nullptr;
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glViewport(
            saved_viewport[0],saved_viewport[1],
            saved_viewport[2],saved_viewport[3]);
        this->texture->generateMipmap();
    }
    
    void dump(std::string filename){
        std::vector<char> B(texture->w*texture->h*4*texture->slices)    ;
        texture->bind(0);
        glGetTexImage(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, GL_UNSIGNED_BYTE, B.data());
        texture->unbind(0);
        char* p = B.data();
        for(int i=0;i<texture->slices;++i){
            Image img(texture->w,texture->h,"RGBA8");
            std::memcpy( img.pixels(), p, texture->w*texture->h*4);
            p += texture->w*texture->h*4;
            std::string fn = filename+"-layer"+std::to_string(i)+".png";
            img.writePng(fn);
            std::cout << "Wrote " << fn << "\n";
        }
    }
       
    std::vector<vec4>& computeBlurWeights(int radius){
        if( blurWeights.find(radius) == blurWeights.end() ){
            std::vector<vec4> F(MAX_BLUR_RADIUS);
            float sigma = radius / 3.0f;
            float sum = 0.0f;
            for (int i = 0; i <= radius; ++i) {
                float Q = i * i / (-2 * sigma * sigma);
                F[i].x = (float) (exp(Q) / (sigma * sqrt(2.0f * 3.14159265358979323f)));
                if (i == 0) {
                    sum += F[i].x;
                } else {
                    sum += 2.0f * F[i].x;
                }
            }
            for (int i = 0; i <= radius; ++i)
                F[i].x /= sum;
            blurWeights[radius] = F;
        }
        return blurWeights[radius];
    }

    /*std::shared_ptr<Framebuffer> getBlurHelper(){
        std::array<int,3> T({(int)texture->w,(int)texture->h,(int)format});
        if( blurHelpers.find(T) == blurHelpers.end() )
            blurHelpers[T] = std::make_shared<Framebuffer>(texture->w,texture->h,1,format);
        return blurHelpers[T];
    }*/
    
    void blur(int radius, float multiplier=1.0f){
        if( radius <= 0 )
            return;
            
        
        if( blurProgram == nullptr )
            blurProgram = std::make_shared<Program>("blurvs.txt","","blurfs.txt");

        //auto helper = getBlurHelper();


        auto oldProg = Program::current;
        blurProgram->use();
        Program::setUniform("blurMultiplier",  multiplier );
        Program::setUniform("blurWeights[0]", computeBlurWeights(radius) );
        Program::setUniform("blurRadius", radius );
        Program::setUniform("blurDeltas",vec2(1.0f/texture->w,0));
        Program::updateUniforms();
        this->texture->bind(0);
        //helper->setAsRenderTarget(true);
        UnitSquare::draw();
        this->texture->unbind(0);
        //helper->unsetAsRenderTarget();
        //helper->texture->bind(0);
        this->setAsRenderTarget(true);
        Program::setUniform("blurMultiplier",  1.0f );
        Program::setUniform("blurDeltas",vec2(0,1.0f/texture->h));
        Program::updateUniforms();
        UnitSquare::draw();
        this->unsetAsRenderTarget();
        //helper->texture->unbind(0);
        if( oldProg )
            oldProg->use();
    }
};

