#pragma once

#include "glfuncs.h"
#include "utils.h"
#include "math3d.h"
#include "Buffer.h"
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <array>
#include <cmath>

class Program{
    public:
    static std::map<std::string,std::array<int,4> >uniforms;
    static Program* current;
    static std::shared_ptr<Buffer> uboBuffer;
    static std::vector<char> uboBackingMemory;
    GLuint prog;
    
    
    Program(std::string vsfname,  std::string fsfname) : Program(vsfname,"",fsfname) {}
    
    Program(std::string vsfname, std::string gsfname, std::string fsfname) : 
            Program(vsfname, "", "", gsfname, fsfname)  {}
    
    Program(std::string vsfname, std::string tcsfname, std::string tesfname, std::string fsfname) :
        Program(vsfname,tcsfname,tesfname,"",fsfname) {}
                
    Program(std::string vsfname, std::string tcsfname, std::string tesfname,
            std::string gsfname, std::string fsfname){

        this->prog = glCreateProgram();
                
        if( !vsfname.empty() )
            glAttachShader(this->prog, this->compile(vsfname, GL_VERTEX_SHADER) );
        if( !tcsfname.empty() )
            glAttachShader(this->prog, this->compile(tcsfname, GL_TESS_CONTROL_SHADER) );
        if( !tesfname.empty() )
            glAttachShader(this->prog, this->compile(tesfname, GL_TESS_EVALUATION_SHADER) );
        if( !gsfname.empty() )
            glAttachShader(this->prog, this->compile(gsfname, GL_GEOMETRY_SHADER) );
        if( !fsfname.empty() )
            glAttachShader(this->prog, this->compile(fsfname, GL_FRAGMENT_SHADER) );
       
        glLinkProgram(this->prog);
        this->getLog("Linking "+vsfname+" "+tcsfname+" "+tesfname+" "+gsfname+" "+fsfname,glGetProgramInfoLog, this->prog);
        GLint tmp[1];
        glGetProgramiv( this->prog, GL_LINK_STATUS, tmp );
        if(! tmp[0] )
            throw std::runtime_error("Cannot link");
        if( !Program::uboBuffer )
            Program::setupUniforms(this->prog);
    }
          
    Program(std::string csfname){
        auto cs = this->compile(csfname, GL_COMPUTE_SHADER );
        this->prog = glCreateProgram();
        glAttachShader(this->prog, cs);
        glLinkProgram(this->prog);
        this->getLog("Linking "+csfname,glGetProgramInfoLog, this->prog);
        GLint tmp[1];
        glGetProgramiv( this->prog, GL_LINK_STATUS, tmp );
        if(! tmp[0] )
            throw std::runtime_error("Cannot link");
        if( !Program::uboBuffer )
            Program::setupUniforms(this->prog);
    }
    
    void dispatch(int xs, int ys, int zs){
        if( current != this )
            this->use();
        glDispatchCompute(xs,ys,zs);
    }

    static void setupUniforms(GLuint prog){
        GLint tmp[1];
        glGetProgramiv(prog,GL_ACTIVE_UNIFORMS,tmp);
        GLint numuniforms = tmp[0];
        std::vector<GLuint> uniformsToQuery(numuniforms);
        for(GLint i=0;i<numuniforms;++i)
            uniformsToQuery[i]=i;
        std::vector<GLint> offsets(numuniforms);
        std::vector<GLint> sizes(numuniforms);
        std::vector<GLint> types(numuniforms);
        glGetActiveUniformsiv(prog, numuniforms,
            uniformsToQuery.data(), GL_UNIFORM_OFFSET, offsets.data());
        glGetActiveUniformsiv(prog, numuniforms,
            uniformsToQuery.data(), GL_UNIFORM_SIZE, sizes.data());
        glGetActiveUniformsiv(prog, numuniforms,
            uniformsToQuery.data(), GL_UNIFORM_TYPE, types.data());

        std::map<GLenum, int> sizeForType( {
            {GL_FLOAT_VEC4, 4*4},
            {GL_FLOAT_VEC3, 3*4},
            {GL_FLOAT_VEC2, 2*4},
            {GL_FLOAT,      1*4},
            {GL_INT,        1*4},
            {GL_FLOAT_MAT2, 2*16},
            {GL_FLOAT_MAT3, 3*16},
            {GL_FLOAT_MAT4, 4*16}
        });

        std::vector<char> nameBytes(256);
        int totalUniformBytes = 0;
        for(int i=0;i<numuniforms;++i){
            glGetActiveUniformName(prog, i,nameBytes.size(),
                tmp, nameBytes.data());
            auto nameLen = tmp[0];
            std::string name(nameBytes.data(),nameLen);
            if(offsets[i] != GLint(-1) ){
                assert(sizes[i] == 1 || types[i] == GL_FLOAT_VEC4);
                int numBytes = sizeForType[types[i]] * sizes[i];
                Program::uniforms[name] = {offsets[i], numBytes, types[i], sizes[i] };
                int end = offsets[i] + numBytes;
                if(end > totalUniformBytes){
                    totalUniformBytes = end;
                }
            }
        }
        
        uboBackingMemory.resize(totalUniformBytes);
        Program::uboBuffer = Buffer::create(uboBackingMemory.size(), GL_DYNAMIC_DRAW);
        Program::uboBuffer->bindBase(GL_UNIFORM_BUFFER,0);
    }
    
    static void setUniform(std::string name, float value ){
        setUniform(name,&value,sizeof(value), GL_FLOAT, 1);
    }
    static void setUniform(std::string name, int value ){
        setUniform(name,&value,sizeof(value), GL_INT, 1);
    }
    static void setUniform(std::string name, unsigned value ){
        setUniform(name,&value,sizeof(value), GL_INT, 1);
    }
    static void setUniform(std::string name, vec2 value ){
        setUniform(name,&value,sizeof(value), GL_FLOAT_VEC2, 1);
    }
    static void setUniform(std::string name, vec3 value ){
        setUniform(name,&value,sizeof(value), GL_FLOAT_VEC3, 1);
    }
    static void setUniform(std::string name, vec4 value ){
        setUniform(name,&value,sizeof(value), GL_FLOAT_VEC4, 1);
    }
    static void setUniform(std::string name, mat4 value ){
        setUniform(name,&value,sizeof(value), GL_FLOAT_MAT4, 1);
    }
    static void setUniform(std::string name, mat3 value ){
        setUniform(name,&value,sizeof(value), GL_FLOAT_MAT3, 1);
    }
    static void setUniform(std::string name, const std::vector<vec4>& value ){
        setUniform(name,value.data(),value.size()*sizeof(value[0]), GL_FLOAT_VEC4, value.size());
    }

    static std::string getTypeName(int t){
        std::map<GLenum, std::string> M( {
            {GL_FLOAT_VEC4, "GL_FLOAT_VEC4"},
            {GL_FLOAT_VEC3, "GL_FLOAT_VEC3"},
            {GL_FLOAT_VEC2, "GL_FLOAT_VEC2"},
            {GL_FLOAT,      "GL_FLOAT"},
            {GL_INT,        "GL_INT"},
            {GL_FLOAT_MAT2, "GL_FLOAT_MAT2"},
            {GL_FLOAT_MAT3, "GL_FLOAT_MAT3"},
            {GL_FLOAT_MAT4, "GL_FLOAT_MAT4"}
        });
        if( M.find(t) != M.end() )
            return M[t];
        return "<unknown type>";
    }
    
    static void setUniform(std::string name, const void* p, size_t sizeAsSizeT, 
                            GLenum typeAsEnum, size_t numElements ){
                                
        if( uniforms.find(name) == uniforms.end() )
            throw std::runtime_error("No such uniform "+name);

        auto A = uniforms[name];
        int _offs = A[0];
        int _numBytes = A[1];
        int _type = A[2];
        int _size = A[3];

        int bytesize = (int)sizeAsSizeT;
        int type = (int)typeAsEnum;

        
        if( _type != type || _numBytes != bytesize ){
            std::cout << "Error when setting uniform " << name << "\n";
            std::cout << "Expected " << _numBytes << " bytes; got " << bytesize << "\n";
            std::cout << "Expected type " << getTypeName(_type) << "; got " << getTypeName(type) << "\n";
            std::cout << "Expected array size " << _size << "; got " << numElements << "\n";
            throw std::runtime_error("Mismatch when setting uniform '"+name+"'");
        }
        
        void* dst = uboBackingMemory.data() + _offs;
        memmove( dst, p, bytesize );
    }
        
    static void updateUniforms(){
        glBufferSubData(GL_UNIFORM_BUFFER,0,
            Program::uboBackingMemory.size(),
            Program::uboBackingMemory.data()
        );
    }

    void use(){
        glUseProgram(this->prog);
        Program::current = this;
    }
        
    GLuint compile(std::string fname, GLenum shaderType){
        auto s = glCreateShader(shaderType);
        
        std::string shaderdata;
        std::ifstream in("shaders/"+fname);
        if(!in.good() )
            throw std::runtime_error("Cannot open "+fname);
        std::getline(in,shaderdata,'\0');
        
        std::string uniformdata;
        std::ifstream in2("shaders/uniforms.txt");
        if( !in2.good() )
            throw std::runtime_error("Cannot open shaders/uniforms.txt");
            
        std::getline(in2,uniformdata,'\0');

        std::string txt = "#version 430\n"
                        "layout( std140, row_major ) uniform Uniforms {\n"
                        "#line 1\n" +
                        uniformdata +
                        "};\n"
                        "#line 1\n" +
                        shaderdata;
                        
        const char* X[1];
        X[0] = txt.c_str();
        glShaderSource(s, 1, X, nullptr );
        glCompileShader(s);
        this->getLog("Compiling "+fname, glGetShaderInfoLog, s);
        GLint tmp[1];
        glGetShaderiv( s, GL_COMPILE_STATUS, tmp );
        if(! tmp[0] )
            throw std::runtime_error("Cannot compile "+fname);
        return s;
    }
        
    template<typename T>
    void getLog( std::string description, const T& func, GLuint identifier ){
        std::vector<char> blob(4096);
        GLint tmp[1];
        func( identifier, blob.size(), tmp, blob.data());
        auto length = tmp[0];
        if(length > 0){
            std::string str(blob.data(),length);
            std::cout << description << ":\n";
            std::cout << str << "\n";
        }
    }
};
             
