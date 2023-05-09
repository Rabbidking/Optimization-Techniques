#pragma once

#include "glfuncs.h"
#include <vector>

class Buffer{
    
  private:
  
    Buffer( int size, bool mappable, GLenum usage){
        init( size, usage, mappable );
    }
    
  public:
  
    GLuint buffID;
    unsigned size;
    GLenum usage;
    void* ptr;  //only for mappable
    
    static std::shared_ptr<Buffer> create(unsigned size, GLenum usage=GL_STATIC_DRAW){
        Buffer* p = new Buffer(size,false,usage);
        return std::shared_ptr<Buffer>(p);
    }
    
    template<typename T>
    static std::shared_ptr<Buffer> create(const std::vector<T>& initialData, GLenum usage = GL_STATIC_DRAW){
        Buffer* p = new Buffer(initialData.size()*sizeof(T),false,usage);
        p->setData(initialData);
        return std::shared_ptr<Buffer>(p);
    }

    static std::shared_ptr<Buffer> createMappable(unsigned size){
        Buffer* p = new Buffer(size,true,0);
        return std::shared_ptr<Buffer>(p);
    }
    
    template<typename T>
    static std::shared_ptr<Buffer> createMappable(const std::vector<T>& initialData){
        Buffer* p = new Buffer(initialData.size()*sizeof(T),true,0);
        p->setData(initialData);
        return std::shared_ptr<Buffer>(p);
    }
    
    ~Buffer(){
        if( ptr ){
            bind(GL_ARRAY_BUFFER);
            glUnmapBuffer(GL_ARRAY_BUFFER);
            ptr=nullptr;
        }
        glDeleteBuffers(1, &buffID);
        buffID=0;
    }
    
    void bind(GLenum bindingPoint){
        glBindBuffer(bindingPoint, buffID);
    }

    void bindBase(GLenum bindingPoint, int index){
        glBindBufferBase(bindingPoint,index,buffID);
    }
    
    template<typename T>
    void setData(const std::vector<T>& newData ){
        setData(newData.data(), newData.size()*sizeof(T));
    }
    
    void setData(const void* p, size_t size){
        glBindBuffer(GL_ARRAY_BUFFER, buffID);
        if( size == this->size ){
            if( ptr )
                memcpy(ptr,p,size);
            else
                glBufferSubData(GL_ARRAY_BUFFER, 0, size, p );
        } else {
            if(ptr)
                throw std::runtime_error("Cannot change size of mappable buffer");
            glBufferData(GL_ARRAY_BUFFER, size, p, usage);
            this->size = size;
        }
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
    }
    
private:
    void init(size_t size, GLenum usage, bool mappable){
        GLuint tmp[1];
        glGenBuffers(1,tmp);
        this->buffID = tmp[0];
        this->size=size;
        glBindBuffer(GL_ARRAY_BUFFER, buffID);
        if( mappable ){
            glBufferStorage( GL_ARRAY_BUFFER, size, nullptr, 
                GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | 
                GL_MAP_READ_BIT | GL_MAP_WRITE_BIT );
            ptr = glMapBufferRange(GL_ARRAY_BUFFER, 
                0, size, 
                GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT | 
                GL_MAP_READ_BIT | GL_MAP_WRITE_BIT 
            );
        } else {
            glBufferData(GL_ARRAY_BUFFER,size,nullptr,usage);
            this->usage = usage;
            ptr=nullptr;
        }
    }
};
        
