/*Data from gl.xml, which has this copyright:

#Copyright (c) 2013-2016 The Khronos Group Inc.
#
#Permission is hereby granted, free of charge, to any person obtaining a
#copy of this software and/or associated documentation files (the
#"Materials"), to deal in the Materials without restriction, including
#without limitation the rights to use, copy, modify, merge, publish,
#distribute, sublicense, and/or sell copies of the Materials, and to
#permit persons to whom the Materials are furnished to do so, subject to
#the following conditions:
#
#The above copyright notice and this permission notice shall be included
#in all copies or substantial portions of the Materials.
#
#THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
#CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
#TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
#MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
#
#------------------------------------------------------------------------
#
#This file, gl.xml, is the OpenGL and OpenGL API Registry. The older
#".spec" file format has been retired and will no longer be updated with
#new extensions and API versions. The canonical version of the registry,
#together with documentation, schema, and Python generator scripts used
#to generate C header files for OpenGL and OpenGL ES, can always be found
#in the Khronos Registry at
#        http://www.opengl.org/registry/
#    
*/
#include "glfuncs.h"

#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif
#include "glcorearb.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdexcept>
#include <cstdio>

using namespace std;

static void* mygetprocaddr(const char* funcname){
    void* x = 0;
    
#ifdef WIN32
    static HMODULE gllib = 0;
    if (!gllib) {
        gllib = LoadLibraryA("opengl32.dll");
        if (!gllib)
            throw runtime_error("Cannot load GL library");
    }
    typedef void* (__stdcall *GLT)(LPCSTR);
    static GLT wglgpa;    
    if( !wglgpa ){
        wglgpa = (GLT) GetProcAddress(gllib,"wglGetProcAddress");
        if(!wglgpa)
            throw runtime_error("Cannot find wglGetProcAddress");
    }
    
    x = (void*) wglgpa(funcname);
    
    if (!x || x == (void*)1 || x == (void*)2 || x == (void*)3 || x == (void*)-1)
        x = 0;
        
    if(!x)
        x = (void*)GetProcAddress(gllib, funcname);
        
#else   
    static void* gllib = 0;
    if(!gllib){
        gllib = dlopen("libGL.so", RTLD_NOW);
        if (!gllib)
            throw runtime_error("Cannot load GL library");
    }
    x = dlsym(gllib, funcname);
#endif

    if (!x)
        throw runtime_error(string("Could not load function ")+funcname);
        
    return x;
  
}


static glActiveShaderProgram_hook_t glActiveShaderProgram_hook = 0;
glActiveShaderProgram_hook_t getHook_glActiveShaderProgram (){
    return glActiveShaderProgram_hook ;
}
void setHook_glActiveShaderProgram ( glActiveShaderProgram_hook_t hook ){
    glActiveShaderProgram_hook = hook;
}
void glActiveShaderProgram ( GLuint pipeline_, GLuint program_ ){
    static PFNGLACTIVESHADERPROGRAMPROC F;
    if(!F)
        F = ( PFNGLACTIVESHADERPROGRAMPROC ) mygetprocaddr("glActiveShaderProgram");
    if( glActiveShaderProgram_hook )
        glActiveShaderProgram_hook( pipeline_, program_ );
    F(pipeline_, program_);
}
static glActiveTexture_hook_t glActiveTexture_hook = 0;
glActiveTexture_hook_t getHook_glActiveTexture (){
    return glActiveTexture_hook ;
}
void setHook_glActiveTexture ( glActiveTexture_hook_t hook ){
    glActiveTexture_hook = hook;
}
void glActiveTexture ( GLenum texture_ ){
    static PFNGLACTIVETEXTUREPROC F;
    if(!F)
        F = ( PFNGLACTIVETEXTUREPROC ) mygetprocaddr("glActiveTexture");
    if( glActiveTexture_hook )
        glActiveTexture_hook( texture_ );
    F(texture_);
}
static glAttachShader_hook_t glAttachShader_hook = 0;
glAttachShader_hook_t getHook_glAttachShader (){
    return glAttachShader_hook ;
}
void setHook_glAttachShader ( glAttachShader_hook_t hook ){
    glAttachShader_hook = hook;
}
void glAttachShader ( GLuint program_, GLuint shader_ ){
    static PFNGLATTACHSHADERPROC F;
    if(!F)
        F = ( PFNGLATTACHSHADERPROC ) mygetprocaddr("glAttachShader");
    if( glAttachShader_hook )
        glAttachShader_hook( program_, shader_ );
    F(program_, shader_);
}
static glBeginConditionalRender_hook_t glBeginConditionalRender_hook = 0;
glBeginConditionalRender_hook_t getHook_glBeginConditionalRender (){
    return glBeginConditionalRender_hook ;
}
void setHook_glBeginConditionalRender ( glBeginConditionalRender_hook_t hook ){
    glBeginConditionalRender_hook = hook;
}
void glBeginConditionalRender ( GLuint id_, GLenum mode_ ){
    static PFNGLBEGINCONDITIONALRENDERPROC F;
    if(!F)
        F = ( PFNGLBEGINCONDITIONALRENDERPROC ) mygetprocaddr("glBeginConditionalRender");
    if( glBeginConditionalRender_hook )
        glBeginConditionalRender_hook( id_, mode_ );
    F(id_, mode_);
}
static glBeginQuery_hook_t glBeginQuery_hook = 0;
glBeginQuery_hook_t getHook_glBeginQuery (){
    return glBeginQuery_hook ;
}
void setHook_glBeginQuery ( glBeginQuery_hook_t hook ){
    glBeginQuery_hook = hook;
}
void glBeginQuery ( GLenum target_, GLuint id_ ){
    static PFNGLBEGINQUERYPROC F;
    if(!F)
        F = ( PFNGLBEGINQUERYPROC ) mygetprocaddr("glBeginQuery");
    if( glBeginQuery_hook )
        glBeginQuery_hook( target_, id_ );
    F(target_, id_);
}
static glBeginQueryIndexed_hook_t glBeginQueryIndexed_hook = 0;
glBeginQueryIndexed_hook_t getHook_glBeginQueryIndexed (){
    return glBeginQueryIndexed_hook ;
}
void setHook_glBeginQueryIndexed ( glBeginQueryIndexed_hook_t hook ){
    glBeginQueryIndexed_hook = hook;
}
void glBeginQueryIndexed ( GLenum target_, GLuint index_, GLuint id_ ){
    static PFNGLBEGINQUERYINDEXEDPROC F;
    if(!F)
        F = ( PFNGLBEGINQUERYINDEXEDPROC ) mygetprocaddr("glBeginQueryIndexed");
    if( glBeginQueryIndexed_hook )
        glBeginQueryIndexed_hook( target_, index_, id_ );
    F(target_, index_, id_);
}
static glBeginTransformFeedback_hook_t glBeginTransformFeedback_hook = 0;
glBeginTransformFeedback_hook_t getHook_glBeginTransformFeedback (){
    return glBeginTransformFeedback_hook ;
}
void setHook_glBeginTransformFeedback ( glBeginTransformFeedback_hook_t hook ){
    glBeginTransformFeedback_hook = hook;
}
void glBeginTransformFeedback ( GLenum primitiveMode_ ){
    static PFNGLBEGINTRANSFORMFEEDBACKPROC F;
    if(!F)
        F = ( PFNGLBEGINTRANSFORMFEEDBACKPROC ) mygetprocaddr("glBeginTransformFeedback");
    if( glBeginTransformFeedback_hook )
        glBeginTransformFeedback_hook( primitiveMode_ );
    F(primitiveMode_);
}
static glBindAttribLocation_hook_t glBindAttribLocation_hook = 0;
glBindAttribLocation_hook_t getHook_glBindAttribLocation (){
    return glBindAttribLocation_hook ;
}
void setHook_glBindAttribLocation ( glBindAttribLocation_hook_t hook ){
    glBindAttribLocation_hook = hook;
}
void glBindAttribLocation ( GLuint program_, GLuint index_, const GLchar * name_ ){
    static PFNGLBINDATTRIBLOCATIONPROC F;
    if(!F)
        F = ( PFNGLBINDATTRIBLOCATIONPROC ) mygetprocaddr("glBindAttribLocation");
    if( glBindAttribLocation_hook )
        glBindAttribLocation_hook( program_, index_, name_ );
    F(program_, index_, name_);
}
static glBindBuffer_hook_t glBindBuffer_hook = 0;
glBindBuffer_hook_t getHook_glBindBuffer (){
    return glBindBuffer_hook ;
}
void setHook_glBindBuffer ( glBindBuffer_hook_t hook ){
    glBindBuffer_hook = hook;
}
void glBindBuffer ( GLenum target_, GLuint buffer_ ){
    static PFNGLBINDBUFFERPROC F;
    if(!F)
        F = ( PFNGLBINDBUFFERPROC ) mygetprocaddr("glBindBuffer");
    if( glBindBuffer_hook )
        glBindBuffer_hook( target_, buffer_ );
    F(target_, buffer_);
}
static glBindBufferBase_hook_t glBindBufferBase_hook = 0;
glBindBufferBase_hook_t getHook_glBindBufferBase (){
    return glBindBufferBase_hook ;
}
void setHook_glBindBufferBase ( glBindBufferBase_hook_t hook ){
    glBindBufferBase_hook = hook;
}
void glBindBufferBase ( GLenum target_, GLuint index_, GLuint buffer_ ){
    static PFNGLBINDBUFFERBASEPROC F;
    if(!F)
        F = ( PFNGLBINDBUFFERBASEPROC ) mygetprocaddr("glBindBufferBase");
    if( glBindBufferBase_hook )
        glBindBufferBase_hook( target_, index_, buffer_ );
    F(target_, index_, buffer_);
}
static glBindBufferRange_hook_t glBindBufferRange_hook = 0;
glBindBufferRange_hook_t getHook_glBindBufferRange (){
    return glBindBufferRange_hook ;
}
void setHook_glBindBufferRange ( glBindBufferRange_hook_t hook ){
    glBindBufferRange_hook = hook;
}
void glBindBufferRange ( GLenum target_, GLuint index_, GLuint buffer_, GLintptr offset_, GLsizeiptr size_ ){
    static PFNGLBINDBUFFERRANGEPROC F;
    if(!F)
        F = ( PFNGLBINDBUFFERRANGEPROC ) mygetprocaddr("glBindBufferRange");
    if( glBindBufferRange_hook )
        glBindBufferRange_hook( target_, index_, buffer_, offset_, size_ );
    F(target_, index_, buffer_, offset_, size_);
}
static glBindBuffersBase_hook_t glBindBuffersBase_hook = 0;
glBindBuffersBase_hook_t getHook_glBindBuffersBase (){
    return glBindBuffersBase_hook ;
}
void setHook_glBindBuffersBase ( glBindBuffersBase_hook_t hook ){
    glBindBuffersBase_hook = hook;
}
void glBindBuffersBase ( GLenum target_, GLuint first_, GLsizei count_, const GLuint * buffers_ ){
    static PFNGLBINDBUFFERSBASEPROC F;
    if(!F)
        F = ( PFNGLBINDBUFFERSBASEPROC ) mygetprocaddr("glBindBuffersBase");
    if( glBindBuffersBase_hook )
        glBindBuffersBase_hook( target_, first_, count_, buffers_ );
    F(target_, first_, count_, buffers_);
}
static glBindBuffersRange_hook_t glBindBuffersRange_hook = 0;
glBindBuffersRange_hook_t getHook_glBindBuffersRange (){
    return glBindBuffersRange_hook ;
}
void setHook_glBindBuffersRange ( glBindBuffersRange_hook_t hook ){
    glBindBuffersRange_hook = hook;
}
void glBindBuffersRange ( GLenum target_, GLuint first_, GLsizei count_, const GLuint * buffers_, const GLintptr * offsets_, const GLsizeiptr * sizes_ ){
    static PFNGLBINDBUFFERSRANGEPROC F;
    if(!F)
        F = ( PFNGLBINDBUFFERSRANGEPROC ) mygetprocaddr("glBindBuffersRange");
    if( glBindBuffersRange_hook )
        glBindBuffersRange_hook( target_, first_, count_, buffers_, offsets_, sizes_ );
    F(target_, first_, count_, buffers_, offsets_, sizes_);
}
static glBindFragDataLocation_hook_t glBindFragDataLocation_hook = 0;
glBindFragDataLocation_hook_t getHook_glBindFragDataLocation (){
    return glBindFragDataLocation_hook ;
}
void setHook_glBindFragDataLocation ( glBindFragDataLocation_hook_t hook ){
    glBindFragDataLocation_hook = hook;
}
void glBindFragDataLocation ( GLuint program_, GLuint color_, const GLchar * name_ ){
    static PFNGLBINDFRAGDATALOCATIONPROC F;
    if(!F)
        F = ( PFNGLBINDFRAGDATALOCATIONPROC ) mygetprocaddr("glBindFragDataLocation");
    if( glBindFragDataLocation_hook )
        glBindFragDataLocation_hook( program_, color_, name_ );
    F(program_, color_, name_);
}
static glBindFragDataLocationIndexed_hook_t glBindFragDataLocationIndexed_hook = 0;
glBindFragDataLocationIndexed_hook_t getHook_glBindFragDataLocationIndexed (){
    return glBindFragDataLocationIndexed_hook ;
}
void setHook_glBindFragDataLocationIndexed ( glBindFragDataLocationIndexed_hook_t hook ){
    glBindFragDataLocationIndexed_hook = hook;
}
void glBindFragDataLocationIndexed ( GLuint program_, GLuint colorNumber_, GLuint index_, const GLchar * name_ ){
    static PFNGLBINDFRAGDATALOCATIONINDEXEDPROC F;
    if(!F)
        F = ( PFNGLBINDFRAGDATALOCATIONINDEXEDPROC ) mygetprocaddr("glBindFragDataLocationIndexed");
    if( glBindFragDataLocationIndexed_hook )
        glBindFragDataLocationIndexed_hook( program_, colorNumber_, index_, name_ );
    F(program_, colorNumber_, index_, name_);
}
static glBindFramebuffer_hook_t glBindFramebuffer_hook = 0;
glBindFramebuffer_hook_t getHook_glBindFramebuffer (){
    return glBindFramebuffer_hook ;
}
void setHook_glBindFramebuffer ( glBindFramebuffer_hook_t hook ){
    glBindFramebuffer_hook = hook;
}
void glBindFramebuffer ( GLenum target_, GLuint framebuffer_ ){
    static PFNGLBINDFRAMEBUFFERPROC F;
    if(!F)
        F = ( PFNGLBINDFRAMEBUFFERPROC ) mygetprocaddr("glBindFramebuffer");
    if( glBindFramebuffer_hook )
        glBindFramebuffer_hook( target_, framebuffer_ );
    F(target_, framebuffer_);
}
static glBindImageTexture_hook_t glBindImageTexture_hook = 0;
glBindImageTexture_hook_t getHook_glBindImageTexture (){
    return glBindImageTexture_hook ;
}
void setHook_glBindImageTexture ( glBindImageTexture_hook_t hook ){
    glBindImageTexture_hook = hook;
}
void glBindImageTexture ( GLuint unit_, GLuint texture_, GLint level_, GLboolean layered_, GLint layer_, GLenum access_, GLenum format_ ){
    static PFNGLBINDIMAGETEXTUREPROC F;
    if(!F)
        F = ( PFNGLBINDIMAGETEXTUREPROC ) mygetprocaddr("glBindImageTexture");
    if( glBindImageTexture_hook )
        glBindImageTexture_hook( unit_, texture_, level_, layered_, layer_, access_, format_ );
    F(unit_, texture_, level_, layered_, layer_, access_, format_);
}
static glBindImageTextures_hook_t glBindImageTextures_hook = 0;
glBindImageTextures_hook_t getHook_glBindImageTextures (){
    return glBindImageTextures_hook ;
}
void setHook_glBindImageTextures ( glBindImageTextures_hook_t hook ){
    glBindImageTextures_hook = hook;
}
void glBindImageTextures ( GLuint first_, GLsizei count_, const GLuint * textures_ ){
    static PFNGLBINDIMAGETEXTURESPROC F;
    if(!F)
        F = ( PFNGLBINDIMAGETEXTURESPROC ) mygetprocaddr("glBindImageTextures");
    if( glBindImageTextures_hook )
        glBindImageTextures_hook( first_, count_, textures_ );
    F(first_, count_, textures_);
}
static glBindProgramPipeline_hook_t glBindProgramPipeline_hook = 0;
glBindProgramPipeline_hook_t getHook_glBindProgramPipeline (){
    return glBindProgramPipeline_hook ;
}
void setHook_glBindProgramPipeline ( glBindProgramPipeline_hook_t hook ){
    glBindProgramPipeline_hook = hook;
}
void glBindProgramPipeline ( GLuint pipeline_ ){
    static PFNGLBINDPROGRAMPIPELINEPROC F;
    if(!F)
        F = ( PFNGLBINDPROGRAMPIPELINEPROC ) mygetprocaddr("glBindProgramPipeline");
    if( glBindProgramPipeline_hook )
        glBindProgramPipeline_hook( pipeline_ );
    F(pipeline_);
}
static glBindRenderbuffer_hook_t glBindRenderbuffer_hook = 0;
glBindRenderbuffer_hook_t getHook_glBindRenderbuffer (){
    return glBindRenderbuffer_hook ;
}
void setHook_glBindRenderbuffer ( glBindRenderbuffer_hook_t hook ){
    glBindRenderbuffer_hook = hook;
}
void glBindRenderbuffer ( GLenum target_, GLuint renderbuffer_ ){
    static PFNGLBINDRENDERBUFFERPROC F;
    if(!F)
        F = ( PFNGLBINDRENDERBUFFERPROC ) mygetprocaddr("glBindRenderbuffer");
    if( glBindRenderbuffer_hook )
        glBindRenderbuffer_hook( target_, renderbuffer_ );
    F(target_, renderbuffer_);
}
static glBindSampler_hook_t glBindSampler_hook = 0;
glBindSampler_hook_t getHook_glBindSampler (){
    return glBindSampler_hook ;
}
void setHook_glBindSampler ( glBindSampler_hook_t hook ){
    glBindSampler_hook = hook;
}
void glBindSampler ( GLuint unit_, GLuint sampler_ ){
    static PFNGLBINDSAMPLERPROC F;
    if(!F)
        F = ( PFNGLBINDSAMPLERPROC ) mygetprocaddr("glBindSampler");
    if( glBindSampler_hook )
        glBindSampler_hook( unit_, sampler_ );
    F(unit_, sampler_);
}
static glBindSamplers_hook_t glBindSamplers_hook = 0;
glBindSamplers_hook_t getHook_glBindSamplers (){
    return glBindSamplers_hook ;
}
void setHook_glBindSamplers ( glBindSamplers_hook_t hook ){
    glBindSamplers_hook = hook;
}
void glBindSamplers ( GLuint first_, GLsizei count_, const GLuint * samplers_ ){
    static PFNGLBINDSAMPLERSPROC F;
    if(!F)
        F = ( PFNGLBINDSAMPLERSPROC ) mygetprocaddr("glBindSamplers");
    if( glBindSamplers_hook )
        glBindSamplers_hook( first_, count_, samplers_ );
    F(first_, count_, samplers_);
}
static glBindTexture_hook_t glBindTexture_hook = 0;
glBindTexture_hook_t getHook_glBindTexture (){
    return glBindTexture_hook ;
}
void setHook_glBindTexture ( glBindTexture_hook_t hook ){
    glBindTexture_hook = hook;
}
void glBindTexture ( GLenum target_, GLuint texture_ ){
    static PFNGLBINDTEXTUREPROC F;
    if(!F)
        F = ( PFNGLBINDTEXTUREPROC ) mygetprocaddr("glBindTexture");
    if( glBindTexture_hook )
        glBindTexture_hook( target_, texture_ );
    F(target_, texture_);
}
static glBindTextureUnit_hook_t glBindTextureUnit_hook = 0;
glBindTextureUnit_hook_t getHook_glBindTextureUnit (){
    return glBindTextureUnit_hook ;
}
void setHook_glBindTextureUnit ( glBindTextureUnit_hook_t hook ){
    glBindTextureUnit_hook = hook;
}
void glBindTextureUnit ( GLuint unit_, GLuint texture_ ){
    static PFNGLBINDTEXTUREUNITPROC F;
    if(!F)
        F = ( PFNGLBINDTEXTUREUNITPROC ) mygetprocaddr("glBindTextureUnit");
    if( glBindTextureUnit_hook )
        glBindTextureUnit_hook( unit_, texture_ );
    F(unit_, texture_);
}
static glBindTextures_hook_t glBindTextures_hook = 0;
glBindTextures_hook_t getHook_glBindTextures (){
    return glBindTextures_hook ;
}
void setHook_glBindTextures ( glBindTextures_hook_t hook ){
    glBindTextures_hook = hook;
}
void glBindTextures ( GLuint first_, GLsizei count_, const GLuint * textures_ ){
    static PFNGLBINDTEXTURESPROC F;
    if(!F)
        F = ( PFNGLBINDTEXTURESPROC ) mygetprocaddr("glBindTextures");
    if( glBindTextures_hook )
        glBindTextures_hook( first_, count_, textures_ );
    F(first_, count_, textures_);
}
static glBindTransformFeedback_hook_t glBindTransformFeedback_hook = 0;
glBindTransformFeedback_hook_t getHook_glBindTransformFeedback (){
    return glBindTransformFeedback_hook ;
}
void setHook_glBindTransformFeedback ( glBindTransformFeedback_hook_t hook ){
    glBindTransformFeedback_hook = hook;
}
void glBindTransformFeedback ( GLenum target_, GLuint id_ ){
    static PFNGLBINDTRANSFORMFEEDBACKPROC F;
    if(!F)
        F = ( PFNGLBINDTRANSFORMFEEDBACKPROC ) mygetprocaddr("glBindTransformFeedback");
    if( glBindTransformFeedback_hook )
        glBindTransformFeedback_hook( target_, id_ );
    F(target_, id_);
}
static glBindVertexArray_hook_t glBindVertexArray_hook = 0;
glBindVertexArray_hook_t getHook_glBindVertexArray (){
    return glBindVertexArray_hook ;
}
void setHook_glBindVertexArray ( glBindVertexArray_hook_t hook ){
    glBindVertexArray_hook = hook;
}
void glBindVertexArray ( GLuint array_ ){
    static PFNGLBINDVERTEXARRAYPROC F;
    if(!F)
        F = ( PFNGLBINDVERTEXARRAYPROC ) mygetprocaddr("glBindVertexArray");
    if( glBindVertexArray_hook )
        glBindVertexArray_hook( array_ );
    F(array_);
}
static glBindVertexBuffer_hook_t glBindVertexBuffer_hook = 0;
glBindVertexBuffer_hook_t getHook_glBindVertexBuffer (){
    return glBindVertexBuffer_hook ;
}
void setHook_glBindVertexBuffer ( glBindVertexBuffer_hook_t hook ){
    glBindVertexBuffer_hook = hook;
}
void glBindVertexBuffer ( GLuint bindingindex_, GLuint buffer_, GLintptr offset_, GLsizei stride_ ){
    static PFNGLBINDVERTEXBUFFERPROC F;
    if(!F)
        F = ( PFNGLBINDVERTEXBUFFERPROC ) mygetprocaddr("glBindVertexBuffer");
    if( glBindVertexBuffer_hook )
        glBindVertexBuffer_hook( bindingindex_, buffer_, offset_, stride_ );
    F(bindingindex_, buffer_, offset_, stride_);
}
static glBindVertexBuffers_hook_t glBindVertexBuffers_hook = 0;
glBindVertexBuffers_hook_t getHook_glBindVertexBuffers (){
    return glBindVertexBuffers_hook ;
}
void setHook_glBindVertexBuffers ( glBindVertexBuffers_hook_t hook ){
    glBindVertexBuffers_hook = hook;
}
void glBindVertexBuffers ( GLuint first_, GLsizei count_, const GLuint * buffers_, const GLintptr * offsets_, const GLsizei * strides_ ){
    static PFNGLBINDVERTEXBUFFERSPROC F;
    if(!F)
        F = ( PFNGLBINDVERTEXBUFFERSPROC ) mygetprocaddr("glBindVertexBuffers");
    if( glBindVertexBuffers_hook )
        glBindVertexBuffers_hook( first_, count_, buffers_, offsets_, strides_ );
    F(first_, count_, buffers_, offsets_, strides_);
}
static glBlendColor_hook_t glBlendColor_hook = 0;
glBlendColor_hook_t getHook_glBlendColor (){
    return glBlendColor_hook ;
}
void setHook_glBlendColor ( glBlendColor_hook_t hook ){
    glBlendColor_hook = hook;
}
void glBlendColor ( GLfloat red_, GLfloat green_, GLfloat blue_, GLfloat alpha_ ){
    static PFNGLBLENDCOLORPROC F;
    if(!F)
        F = ( PFNGLBLENDCOLORPROC ) mygetprocaddr("glBlendColor");
    if( glBlendColor_hook )
        glBlendColor_hook( red_, green_, blue_, alpha_ );
    F(red_, green_, blue_, alpha_);
}
static glBlendEquation_hook_t glBlendEquation_hook = 0;
glBlendEquation_hook_t getHook_glBlendEquation (){
    return glBlendEquation_hook ;
}
void setHook_glBlendEquation ( glBlendEquation_hook_t hook ){
    glBlendEquation_hook = hook;
}
void glBlendEquation ( GLenum mode_ ){
    static PFNGLBLENDEQUATIONPROC F;
    if(!F)
        F = ( PFNGLBLENDEQUATIONPROC ) mygetprocaddr("glBlendEquation");
    if( glBlendEquation_hook )
        glBlendEquation_hook( mode_ );
    F(mode_);
}
static glBlendEquationSeparate_hook_t glBlendEquationSeparate_hook = 0;
glBlendEquationSeparate_hook_t getHook_glBlendEquationSeparate (){
    return glBlendEquationSeparate_hook ;
}
void setHook_glBlendEquationSeparate ( glBlendEquationSeparate_hook_t hook ){
    glBlendEquationSeparate_hook = hook;
}
void glBlendEquationSeparate ( GLenum modeRGB_, GLenum modeAlpha_ ){
    static PFNGLBLENDEQUATIONSEPARATEPROC F;
    if(!F)
        F = ( PFNGLBLENDEQUATIONSEPARATEPROC ) mygetprocaddr("glBlendEquationSeparate");
    if( glBlendEquationSeparate_hook )
        glBlendEquationSeparate_hook( modeRGB_, modeAlpha_ );
    F(modeRGB_, modeAlpha_);
}
static glBlendEquationSeparatei_hook_t glBlendEquationSeparatei_hook = 0;
glBlendEquationSeparatei_hook_t getHook_glBlendEquationSeparatei (){
    return glBlendEquationSeparatei_hook ;
}
void setHook_glBlendEquationSeparatei ( glBlendEquationSeparatei_hook_t hook ){
    glBlendEquationSeparatei_hook = hook;
}
void glBlendEquationSeparatei ( GLuint buf_, GLenum modeRGB_, GLenum modeAlpha_ ){
    static PFNGLBLENDEQUATIONSEPARATEIPROC F;
    if(!F)
        F = ( PFNGLBLENDEQUATIONSEPARATEIPROC ) mygetprocaddr("glBlendEquationSeparatei");
    if( glBlendEquationSeparatei_hook )
        glBlendEquationSeparatei_hook( buf_, modeRGB_, modeAlpha_ );
    F(buf_, modeRGB_, modeAlpha_);
}
static glBlendEquationi_hook_t glBlendEquationi_hook = 0;
glBlendEquationi_hook_t getHook_glBlendEquationi (){
    return glBlendEquationi_hook ;
}
void setHook_glBlendEquationi ( glBlendEquationi_hook_t hook ){
    glBlendEquationi_hook = hook;
}
void glBlendEquationi ( GLuint buf_, GLenum mode_ ){
    static PFNGLBLENDEQUATIONIPROC F;
    if(!F)
        F = ( PFNGLBLENDEQUATIONIPROC ) mygetprocaddr("glBlendEquationi");
    if( glBlendEquationi_hook )
        glBlendEquationi_hook( buf_, mode_ );
    F(buf_, mode_);
}
static glBlendFunc_hook_t glBlendFunc_hook = 0;
glBlendFunc_hook_t getHook_glBlendFunc (){
    return glBlendFunc_hook ;
}
void setHook_glBlendFunc ( glBlendFunc_hook_t hook ){
    glBlendFunc_hook = hook;
}
void glBlendFunc ( GLenum sfactor_, GLenum dfactor_ ){
    static PFNGLBLENDFUNCPROC F;
    if(!F)
        F = ( PFNGLBLENDFUNCPROC ) mygetprocaddr("glBlendFunc");
    if( glBlendFunc_hook )
        glBlendFunc_hook( sfactor_, dfactor_ );
    F(sfactor_, dfactor_);
}
static glBlendFuncSeparate_hook_t glBlendFuncSeparate_hook = 0;
glBlendFuncSeparate_hook_t getHook_glBlendFuncSeparate (){
    return glBlendFuncSeparate_hook ;
}
void setHook_glBlendFuncSeparate ( glBlendFuncSeparate_hook_t hook ){
    glBlendFuncSeparate_hook = hook;
}
void glBlendFuncSeparate ( GLenum sfactorRGB_, GLenum dfactorRGB_, GLenum sfactorAlpha_, GLenum dfactorAlpha_ ){
    static PFNGLBLENDFUNCSEPARATEPROC F;
    if(!F)
        F = ( PFNGLBLENDFUNCSEPARATEPROC ) mygetprocaddr("glBlendFuncSeparate");
    if( glBlendFuncSeparate_hook )
        glBlendFuncSeparate_hook( sfactorRGB_, dfactorRGB_, sfactorAlpha_, dfactorAlpha_ );
    F(sfactorRGB_, dfactorRGB_, sfactorAlpha_, dfactorAlpha_);
}
static glBlendFuncSeparatei_hook_t glBlendFuncSeparatei_hook = 0;
glBlendFuncSeparatei_hook_t getHook_glBlendFuncSeparatei (){
    return glBlendFuncSeparatei_hook ;
}
void setHook_glBlendFuncSeparatei ( glBlendFuncSeparatei_hook_t hook ){
    glBlendFuncSeparatei_hook = hook;
}
void glBlendFuncSeparatei ( GLuint buf_, GLenum srcRGB_, GLenum dstRGB_, GLenum srcAlpha_, GLenum dstAlpha_ ){
    static PFNGLBLENDFUNCSEPARATEIPROC F;
    if(!F)
        F = ( PFNGLBLENDFUNCSEPARATEIPROC ) mygetprocaddr("glBlendFuncSeparatei");
    if( glBlendFuncSeparatei_hook )
        glBlendFuncSeparatei_hook( buf_, srcRGB_, dstRGB_, srcAlpha_, dstAlpha_ );
    F(buf_, srcRGB_, dstRGB_, srcAlpha_, dstAlpha_);
}
static glBlendFunci_hook_t glBlendFunci_hook = 0;
glBlendFunci_hook_t getHook_glBlendFunci (){
    return glBlendFunci_hook ;
}
void setHook_glBlendFunci ( glBlendFunci_hook_t hook ){
    glBlendFunci_hook = hook;
}
void glBlendFunci ( GLuint buf_, GLenum src_, GLenum dst_ ){
    static PFNGLBLENDFUNCIPROC F;
    if(!F)
        F = ( PFNGLBLENDFUNCIPROC ) mygetprocaddr("glBlendFunci");
    if( glBlendFunci_hook )
        glBlendFunci_hook( buf_, src_, dst_ );
    F(buf_, src_, dst_);
}
static glBlitFramebuffer_hook_t glBlitFramebuffer_hook = 0;
glBlitFramebuffer_hook_t getHook_glBlitFramebuffer (){
    return glBlitFramebuffer_hook ;
}
void setHook_glBlitFramebuffer ( glBlitFramebuffer_hook_t hook ){
    glBlitFramebuffer_hook = hook;
}
void glBlitFramebuffer ( GLint srcX0_, GLint srcY0_, GLint srcX1_, GLint srcY1_, GLint dstX0_, GLint dstY0_, GLint dstX1_, GLint dstY1_, GLbitfield mask_, GLenum filter_ ){
    static PFNGLBLITFRAMEBUFFERPROC F;
    if(!F)
        F = ( PFNGLBLITFRAMEBUFFERPROC ) mygetprocaddr("glBlitFramebuffer");
    if( glBlitFramebuffer_hook )
        glBlitFramebuffer_hook( srcX0_, srcY0_, srcX1_, srcY1_, dstX0_, dstY0_, dstX1_, dstY1_, mask_, filter_ );
    F(srcX0_, srcY0_, srcX1_, srcY1_, dstX0_, dstY0_, dstX1_, dstY1_, mask_, filter_);
}
static glBlitNamedFramebuffer_hook_t glBlitNamedFramebuffer_hook = 0;
glBlitNamedFramebuffer_hook_t getHook_glBlitNamedFramebuffer (){
    return glBlitNamedFramebuffer_hook ;
}
void setHook_glBlitNamedFramebuffer ( glBlitNamedFramebuffer_hook_t hook ){
    glBlitNamedFramebuffer_hook = hook;
}
void glBlitNamedFramebuffer ( GLuint readFramebuffer_, GLuint drawFramebuffer_, GLint srcX0_, GLint srcY0_, GLint srcX1_, GLint srcY1_, GLint dstX0_, GLint dstY0_, GLint dstX1_, GLint dstY1_, GLbitfield mask_, GLenum filter_ ){
    static PFNGLBLITNAMEDFRAMEBUFFERPROC F;
    if(!F)
        F = ( PFNGLBLITNAMEDFRAMEBUFFERPROC ) mygetprocaddr("glBlitNamedFramebuffer");
    if( glBlitNamedFramebuffer_hook )
        glBlitNamedFramebuffer_hook( readFramebuffer_, drawFramebuffer_, srcX0_, srcY0_, srcX1_, srcY1_, dstX0_, dstY0_, dstX1_, dstY1_, mask_, filter_ );
    F(readFramebuffer_, drawFramebuffer_, srcX0_, srcY0_, srcX1_, srcY1_, dstX0_, dstY0_, dstX1_, dstY1_, mask_, filter_);
}
static glBufferData_hook_t glBufferData_hook = 0;
glBufferData_hook_t getHook_glBufferData (){
    return glBufferData_hook ;
}
void setHook_glBufferData ( glBufferData_hook_t hook ){
    glBufferData_hook = hook;
}
void glBufferData ( GLenum target_, GLsizeiptr size_, const void * data_, GLenum usage_ ){
    static PFNGLBUFFERDATAPROC F;
    if(!F)
        F = ( PFNGLBUFFERDATAPROC ) mygetprocaddr("glBufferData");
    if( glBufferData_hook )
        glBufferData_hook( target_, size_, data_, usage_ );
    F(target_, size_, data_, usage_);
}
static glBufferStorage_hook_t glBufferStorage_hook = 0;
glBufferStorage_hook_t getHook_glBufferStorage (){
    return glBufferStorage_hook ;
}
void setHook_glBufferStorage ( glBufferStorage_hook_t hook ){
    glBufferStorage_hook = hook;
}
void glBufferStorage ( GLenum target_, GLsizeiptr size_, const void * data_, GLbitfield flags_ ){
    static PFNGLBUFFERSTORAGEPROC F;
    if(!F)
        F = ( PFNGLBUFFERSTORAGEPROC ) mygetprocaddr("glBufferStorage");
    if( glBufferStorage_hook )
        glBufferStorage_hook( target_, size_, data_, flags_ );
    F(target_, size_, data_, flags_);
}
static glBufferSubData_hook_t glBufferSubData_hook = 0;
glBufferSubData_hook_t getHook_glBufferSubData (){
    return glBufferSubData_hook ;
}
void setHook_glBufferSubData ( glBufferSubData_hook_t hook ){
    glBufferSubData_hook = hook;
}
void glBufferSubData ( GLenum target_, GLintptr offset_, GLsizeiptr size_, const void * data_ ){
    static PFNGLBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLBUFFERSUBDATAPROC ) mygetprocaddr("glBufferSubData");
    if( glBufferSubData_hook )
        glBufferSubData_hook( target_, offset_, size_, data_ );
    F(target_, offset_, size_, data_);
}
static glCheckFramebufferStatus_hook_t glCheckFramebufferStatus_hook = 0;
glCheckFramebufferStatus_hook_t getHook_glCheckFramebufferStatus (){
    return glCheckFramebufferStatus_hook ;
}
void setHook_glCheckFramebufferStatus ( glCheckFramebufferStatus_hook_t hook ){
    glCheckFramebufferStatus_hook = hook;
}
GLenum glCheckFramebufferStatus ( GLenum target_ ){
    static PFNGLCHECKFRAMEBUFFERSTATUSPROC F;
    if(!F)
        F = ( PFNGLCHECKFRAMEBUFFERSTATUSPROC ) mygetprocaddr("glCheckFramebufferStatus");
    if( glCheckFramebufferStatus_hook )
        glCheckFramebufferStatus_hook( target_ );
    GLenum retval = F(target_);
    return retval;
}
static glCheckNamedFramebufferStatus_hook_t glCheckNamedFramebufferStatus_hook = 0;
glCheckNamedFramebufferStatus_hook_t getHook_glCheckNamedFramebufferStatus (){
    return glCheckNamedFramebufferStatus_hook ;
}
void setHook_glCheckNamedFramebufferStatus ( glCheckNamedFramebufferStatus_hook_t hook ){
    glCheckNamedFramebufferStatus_hook = hook;
}
GLenum glCheckNamedFramebufferStatus ( GLuint framebuffer_, GLenum target_ ){
    static PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC F;
    if(!F)
        F = ( PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC ) mygetprocaddr("glCheckNamedFramebufferStatus");
    if( glCheckNamedFramebufferStatus_hook )
        glCheckNamedFramebufferStatus_hook( framebuffer_, target_ );
    GLenum retval = F(framebuffer_, target_);
    return retval;
}
static glClampColor_hook_t glClampColor_hook = 0;
glClampColor_hook_t getHook_glClampColor (){
    return glClampColor_hook ;
}
void setHook_glClampColor ( glClampColor_hook_t hook ){
    glClampColor_hook = hook;
}
void glClampColor ( GLenum target_, GLenum clamp_ ){
    static PFNGLCLAMPCOLORPROC F;
    if(!F)
        F = ( PFNGLCLAMPCOLORPROC ) mygetprocaddr("glClampColor");
    if( glClampColor_hook )
        glClampColor_hook( target_, clamp_ );
    F(target_, clamp_);
}
static glClear_hook_t glClear_hook = 0;
glClear_hook_t getHook_glClear (){
    return glClear_hook ;
}
void setHook_glClear ( glClear_hook_t hook ){
    glClear_hook = hook;
}
void glClear ( GLbitfield mask_ ){
    static PFNGLCLEARPROC F;
    if(!F)
        F = ( PFNGLCLEARPROC ) mygetprocaddr("glClear");
    if( glClear_hook )
        glClear_hook( mask_ );
    F(mask_);
}
static glClearBufferData_hook_t glClearBufferData_hook = 0;
glClearBufferData_hook_t getHook_glClearBufferData (){
    return glClearBufferData_hook ;
}
void setHook_glClearBufferData ( glClearBufferData_hook_t hook ){
    glClearBufferData_hook = hook;
}
void glClearBufferData ( GLenum target_, GLenum internalformat_, GLenum format_, GLenum type_, const void * data_ ){
    static PFNGLCLEARBUFFERDATAPROC F;
    if(!F)
        F = ( PFNGLCLEARBUFFERDATAPROC ) mygetprocaddr("glClearBufferData");
    if( glClearBufferData_hook )
        glClearBufferData_hook( target_, internalformat_, format_, type_, data_ );
    F(target_, internalformat_, format_, type_, data_);
}
static glClearBufferSubData_hook_t glClearBufferSubData_hook = 0;
glClearBufferSubData_hook_t getHook_glClearBufferSubData (){
    return glClearBufferSubData_hook ;
}
void setHook_glClearBufferSubData ( glClearBufferSubData_hook_t hook ){
    glClearBufferSubData_hook = hook;
}
void glClearBufferSubData ( GLenum target_, GLenum internalformat_, GLintptr offset_, GLsizeiptr size_, GLenum format_, GLenum type_, const void * data_ ){
    static PFNGLCLEARBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLCLEARBUFFERSUBDATAPROC ) mygetprocaddr("glClearBufferSubData");
    if( glClearBufferSubData_hook )
        glClearBufferSubData_hook( target_, internalformat_, offset_, size_, format_, type_, data_ );
    F(target_, internalformat_, offset_, size_, format_, type_, data_);
}
static glClearBufferfi_hook_t glClearBufferfi_hook = 0;
glClearBufferfi_hook_t getHook_glClearBufferfi (){
    return glClearBufferfi_hook ;
}
void setHook_glClearBufferfi ( glClearBufferfi_hook_t hook ){
    glClearBufferfi_hook = hook;
}
void glClearBufferfi ( GLenum buffer_, GLint drawbuffer_, GLfloat depth_, GLint stencil_ ){
    static PFNGLCLEARBUFFERFIPROC F;
    if(!F)
        F = ( PFNGLCLEARBUFFERFIPROC ) mygetprocaddr("glClearBufferfi");
    if( glClearBufferfi_hook )
        glClearBufferfi_hook( buffer_, drawbuffer_, depth_, stencil_ );
    F(buffer_, drawbuffer_, depth_, stencil_);
}
static glClearBufferfv_hook_t glClearBufferfv_hook = 0;
glClearBufferfv_hook_t getHook_glClearBufferfv (){
    return glClearBufferfv_hook ;
}
void setHook_glClearBufferfv ( glClearBufferfv_hook_t hook ){
    glClearBufferfv_hook = hook;
}
void glClearBufferfv ( GLenum buffer_, GLint drawbuffer_, const GLfloat * value_ ){
    static PFNGLCLEARBUFFERFVPROC F;
    if(!F)
        F = ( PFNGLCLEARBUFFERFVPROC ) mygetprocaddr("glClearBufferfv");
    if( glClearBufferfv_hook )
        glClearBufferfv_hook( buffer_, drawbuffer_, value_ );
    F(buffer_, drawbuffer_, value_);
}
static glClearBufferiv_hook_t glClearBufferiv_hook = 0;
glClearBufferiv_hook_t getHook_glClearBufferiv (){
    return glClearBufferiv_hook ;
}
void setHook_glClearBufferiv ( glClearBufferiv_hook_t hook ){
    glClearBufferiv_hook = hook;
}
void glClearBufferiv ( GLenum buffer_, GLint drawbuffer_, const GLint * value_ ){
    static PFNGLCLEARBUFFERIVPROC F;
    if(!F)
        F = ( PFNGLCLEARBUFFERIVPROC ) mygetprocaddr("glClearBufferiv");
    if( glClearBufferiv_hook )
        glClearBufferiv_hook( buffer_, drawbuffer_, value_ );
    F(buffer_, drawbuffer_, value_);
}
static glClearBufferuiv_hook_t glClearBufferuiv_hook = 0;
glClearBufferuiv_hook_t getHook_glClearBufferuiv (){
    return glClearBufferuiv_hook ;
}
void setHook_glClearBufferuiv ( glClearBufferuiv_hook_t hook ){
    glClearBufferuiv_hook = hook;
}
void glClearBufferuiv ( GLenum buffer_, GLint drawbuffer_, const GLuint * value_ ){
    static PFNGLCLEARBUFFERUIVPROC F;
    if(!F)
        F = ( PFNGLCLEARBUFFERUIVPROC ) mygetprocaddr("glClearBufferuiv");
    if( glClearBufferuiv_hook )
        glClearBufferuiv_hook( buffer_, drawbuffer_, value_ );
    F(buffer_, drawbuffer_, value_);
}
static glClearColor_hook_t glClearColor_hook = 0;
glClearColor_hook_t getHook_glClearColor (){
    return glClearColor_hook ;
}
void setHook_glClearColor ( glClearColor_hook_t hook ){
    glClearColor_hook = hook;
}
void glClearColor ( GLfloat red_, GLfloat green_, GLfloat blue_, GLfloat alpha_ ){
    static PFNGLCLEARCOLORPROC F;
    if(!F)
        F = ( PFNGLCLEARCOLORPROC ) mygetprocaddr("glClearColor");
    if( glClearColor_hook )
        glClearColor_hook( red_, green_, blue_, alpha_ );
    F(red_, green_, blue_, alpha_);
}
static glClearDepth_hook_t glClearDepth_hook = 0;
glClearDepth_hook_t getHook_glClearDepth (){
    return glClearDepth_hook ;
}
void setHook_glClearDepth ( glClearDepth_hook_t hook ){
    glClearDepth_hook = hook;
}
void glClearDepth ( GLdouble depth_ ){
    static PFNGLCLEARDEPTHPROC F;
    if(!F)
        F = ( PFNGLCLEARDEPTHPROC ) mygetprocaddr("glClearDepth");
    if( glClearDepth_hook )
        glClearDepth_hook( depth_ );
    F(depth_);
}
static glClearDepthf_hook_t glClearDepthf_hook = 0;
glClearDepthf_hook_t getHook_glClearDepthf (){
    return glClearDepthf_hook ;
}
void setHook_glClearDepthf ( glClearDepthf_hook_t hook ){
    glClearDepthf_hook = hook;
}
void glClearDepthf ( GLfloat d_ ){
    static PFNGLCLEARDEPTHFPROC F;
    if(!F)
        F = ( PFNGLCLEARDEPTHFPROC ) mygetprocaddr("glClearDepthf");
    if( glClearDepthf_hook )
        glClearDepthf_hook( d_ );
    F(d_);
}
static glClearNamedBufferData_hook_t glClearNamedBufferData_hook = 0;
glClearNamedBufferData_hook_t getHook_glClearNamedBufferData (){
    return glClearNamedBufferData_hook ;
}
void setHook_glClearNamedBufferData ( glClearNamedBufferData_hook_t hook ){
    glClearNamedBufferData_hook = hook;
}
void glClearNamedBufferData ( GLuint buffer_, GLenum internalformat_, GLenum format_, GLenum type_, const void * data_ ){
    static PFNGLCLEARNAMEDBUFFERDATAPROC F;
    if(!F)
        F = ( PFNGLCLEARNAMEDBUFFERDATAPROC ) mygetprocaddr("glClearNamedBufferData");
    if( glClearNamedBufferData_hook )
        glClearNamedBufferData_hook( buffer_, internalformat_, format_, type_, data_ );
    F(buffer_, internalformat_, format_, type_, data_);
}
static glClearNamedBufferSubData_hook_t glClearNamedBufferSubData_hook = 0;
glClearNamedBufferSubData_hook_t getHook_glClearNamedBufferSubData (){
    return glClearNamedBufferSubData_hook ;
}
void setHook_glClearNamedBufferSubData ( glClearNamedBufferSubData_hook_t hook ){
    glClearNamedBufferSubData_hook = hook;
}
void glClearNamedBufferSubData ( GLuint buffer_, GLenum internalformat_, GLintptr offset_, GLsizeiptr size_, GLenum format_, GLenum type_, const void * data_ ){
    static PFNGLCLEARNAMEDBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLCLEARNAMEDBUFFERSUBDATAPROC ) mygetprocaddr("glClearNamedBufferSubData");
    if( glClearNamedBufferSubData_hook )
        glClearNamedBufferSubData_hook( buffer_, internalformat_, offset_, size_, format_, type_, data_ );
    F(buffer_, internalformat_, offset_, size_, format_, type_, data_);
}
static glClearNamedFramebufferfi_hook_t glClearNamedFramebufferfi_hook = 0;
glClearNamedFramebufferfi_hook_t getHook_glClearNamedFramebufferfi (){
    return glClearNamedFramebufferfi_hook ;
}
void setHook_glClearNamedFramebufferfi ( glClearNamedFramebufferfi_hook_t hook ){
    glClearNamedFramebufferfi_hook = hook;
}
void glClearNamedFramebufferfi ( GLuint framebuffer_, GLenum buffer_, GLint drawbuffer_, GLfloat depth_, GLint stencil_ ){
    static PFNGLCLEARNAMEDFRAMEBUFFERFIPROC F;
    if(!F)
        F = ( PFNGLCLEARNAMEDFRAMEBUFFERFIPROC ) mygetprocaddr("glClearNamedFramebufferfi");
    if( glClearNamedFramebufferfi_hook )
        glClearNamedFramebufferfi_hook( framebuffer_, buffer_, drawbuffer_, depth_, stencil_ );
    F(framebuffer_, buffer_, drawbuffer_, depth_, stencil_);
}
static glClearNamedFramebufferfv_hook_t glClearNamedFramebufferfv_hook = 0;
glClearNamedFramebufferfv_hook_t getHook_glClearNamedFramebufferfv (){
    return glClearNamedFramebufferfv_hook ;
}
void setHook_glClearNamedFramebufferfv ( glClearNamedFramebufferfv_hook_t hook ){
    glClearNamedFramebufferfv_hook = hook;
}
void glClearNamedFramebufferfv ( GLuint framebuffer_, GLenum buffer_, GLint drawbuffer_, const GLfloat * value_ ){
    static PFNGLCLEARNAMEDFRAMEBUFFERFVPROC F;
    if(!F)
        F = ( PFNGLCLEARNAMEDFRAMEBUFFERFVPROC ) mygetprocaddr("glClearNamedFramebufferfv");
    if( glClearNamedFramebufferfv_hook )
        glClearNamedFramebufferfv_hook( framebuffer_, buffer_, drawbuffer_, value_ );
    F(framebuffer_, buffer_, drawbuffer_, value_);
}
static glClearNamedFramebufferiv_hook_t glClearNamedFramebufferiv_hook = 0;
glClearNamedFramebufferiv_hook_t getHook_glClearNamedFramebufferiv (){
    return glClearNamedFramebufferiv_hook ;
}
void setHook_glClearNamedFramebufferiv ( glClearNamedFramebufferiv_hook_t hook ){
    glClearNamedFramebufferiv_hook = hook;
}
void glClearNamedFramebufferiv ( GLuint framebuffer_, GLenum buffer_, GLint drawbuffer_, const GLint * value_ ){
    static PFNGLCLEARNAMEDFRAMEBUFFERIVPROC F;
    if(!F)
        F = ( PFNGLCLEARNAMEDFRAMEBUFFERIVPROC ) mygetprocaddr("glClearNamedFramebufferiv");
    if( glClearNamedFramebufferiv_hook )
        glClearNamedFramebufferiv_hook( framebuffer_, buffer_, drawbuffer_, value_ );
    F(framebuffer_, buffer_, drawbuffer_, value_);
}
static glClearNamedFramebufferuiv_hook_t glClearNamedFramebufferuiv_hook = 0;
glClearNamedFramebufferuiv_hook_t getHook_glClearNamedFramebufferuiv (){
    return glClearNamedFramebufferuiv_hook ;
}
void setHook_glClearNamedFramebufferuiv ( glClearNamedFramebufferuiv_hook_t hook ){
    glClearNamedFramebufferuiv_hook = hook;
}
void glClearNamedFramebufferuiv ( GLuint framebuffer_, GLenum buffer_, GLint drawbuffer_, const GLuint * value_ ){
    static PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC F;
    if(!F)
        F = ( PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC ) mygetprocaddr("glClearNamedFramebufferuiv");
    if( glClearNamedFramebufferuiv_hook )
        glClearNamedFramebufferuiv_hook( framebuffer_, buffer_, drawbuffer_, value_ );
    F(framebuffer_, buffer_, drawbuffer_, value_);
}
static glClearStencil_hook_t glClearStencil_hook = 0;
glClearStencil_hook_t getHook_glClearStencil (){
    return glClearStencil_hook ;
}
void setHook_glClearStencil ( glClearStencil_hook_t hook ){
    glClearStencil_hook = hook;
}
void glClearStencil ( GLint s_ ){
    static PFNGLCLEARSTENCILPROC F;
    if(!F)
        F = ( PFNGLCLEARSTENCILPROC ) mygetprocaddr("glClearStencil");
    if( glClearStencil_hook )
        glClearStencil_hook( s_ );
    F(s_);
}
static glClearTexImage_hook_t glClearTexImage_hook = 0;
glClearTexImage_hook_t getHook_glClearTexImage (){
    return glClearTexImage_hook ;
}
void setHook_glClearTexImage ( glClearTexImage_hook_t hook ){
    glClearTexImage_hook = hook;
}
void glClearTexImage ( GLuint texture_, GLint level_, GLenum format_, GLenum type_, const void * data_ ){
    static PFNGLCLEARTEXIMAGEPROC F;
    if(!F)
        F = ( PFNGLCLEARTEXIMAGEPROC ) mygetprocaddr("glClearTexImage");
    if( glClearTexImage_hook )
        glClearTexImage_hook( texture_, level_, format_, type_, data_ );
    F(texture_, level_, format_, type_, data_);
}
static glClearTexSubImage_hook_t glClearTexSubImage_hook = 0;
glClearTexSubImage_hook_t getHook_glClearTexSubImage (){
    return glClearTexSubImage_hook ;
}
void setHook_glClearTexSubImage ( glClearTexSubImage_hook_t hook ){
    glClearTexSubImage_hook = hook;
}
void glClearTexSubImage ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLsizei width_, GLsizei height_, GLsizei depth_, GLenum format_, GLenum type_, const void * data_ ){
    static PFNGLCLEARTEXSUBIMAGEPROC F;
    if(!F)
        F = ( PFNGLCLEARTEXSUBIMAGEPROC ) mygetprocaddr("glClearTexSubImage");
    if( glClearTexSubImage_hook )
        glClearTexSubImage_hook( texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, type_, data_ );
    F(texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, type_, data_);
}
static glClientWaitSync_hook_t glClientWaitSync_hook = 0;
glClientWaitSync_hook_t getHook_glClientWaitSync (){
    return glClientWaitSync_hook ;
}
void setHook_glClientWaitSync ( glClientWaitSync_hook_t hook ){
    glClientWaitSync_hook = hook;
}
GLenum glClientWaitSync ( GLsync sync_, GLbitfield flags_, GLuint64 timeout_ ){
    static PFNGLCLIENTWAITSYNCPROC F;
    if(!F)
        F = ( PFNGLCLIENTWAITSYNCPROC ) mygetprocaddr("glClientWaitSync");
    if( glClientWaitSync_hook )
        glClientWaitSync_hook( sync_, flags_, timeout_ );
    GLenum retval = F(sync_, flags_, timeout_);
    return retval;
}
static glClipControl_hook_t glClipControl_hook = 0;
glClipControl_hook_t getHook_glClipControl (){
    return glClipControl_hook ;
}
void setHook_glClipControl ( glClipControl_hook_t hook ){
    glClipControl_hook = hook;
}
void glClipControl ( GLenum origin_, GLenum depth_ ){
    static PFNGLCLIPCONTROLPROC F;
    if(!F)
        F = ( PFNGLCLIPCONTROLPROC ) mygetprocaddr("glClipControl");
    if( glClipControl_hook )
        glClipControl_hook( origin_, depth_ );
    F(origin_, depth_);
}
static glColorMask_hook_t glColorMask_hook = 0;
glColorMask_hook_t getHook_glColorMask (){
    return glColorMask_hook ;
}
void setHook_glColorMask ( glColorMask_hook_t hook ){
    glColorMask_hook = hook;
}
void glColorMask ( GLboolean red_, GLboolean green_, GLboolean blue_, GLboolean alpha_ ){
    static PFNGLCOLORMASKPROC F;
    if(!F)
        F = ( PFNGLCOLORMASKPROC ) mygetprocaddr("glColorMask");
    if( glColorMask_hook )
        glColorMask_hook( red_, green_, blue_, alpha_ );
    F(red_, green_, blue_, alpha_);
}
static glColorMaski_hook_t glColorMaski_hook = 0;
glColorMaski_hook_t getHook_glColorMaski (){
    return glColorMaski_hook ;
}
void setHook_glColorMaski ( glColorMaski_hook_t hook ){
    glColorMaski_hook = hook;
}
void glColorMaski ( GLuint index_, GLboolean r_, GLboolean g_, GLboolean b_, GLboolean a_ ){
    static PFNGLCOLORMASKIPROC F;
    if(!F)
        F = ( PFNGLCOLORMASKIPROC ) mygetprocaddr("glColorMaski");
    if( glColorMaski_hook )
        glColorMaski_hook( index_, r_, g_, b_, a_ );
    F(index_, r_, g_, b_, a_);
}
static glCompileShader_hook_t glCompileShader_hook = 0;
glCompileShader_hook_t getHook_glCompileShader (){
    return glCompileShader_hook ;
}
void setHook_glCompileShader ( glCompileShader_hook_t hook ){
    glCompileShader_hook = hook;
}
void glCompileShader ( GLuint shader_ ){
    static PFNGLCOMPILESHADERPROC F;
    if(!F)
        F = ( PFNGLCOMPILESHADERPROC ) mygetprocaddr("glCompileShader");
    if( glCompileShader_hook )
        glCompileShader_hook( shader_ );
    F(shader_);
}
static glCompressedTexImage1D_hook_t glCompressedTexImage1D_hook = 0;
glCompressedTexImage1D_hook_t getHook_glCompressedTexImage1D (){
    return glCompressedTexImage1D_hook ;
}
void setHook_glCompressedTexImage1D ( glCompressedTexImage1D_hook_t hook ){
    glCompressedTexImage1D_hook = hook;
}
void glCompressedTexImage1D ( GLenum target_, GLint level_, GLenum internalformat_, GLsizei width_, GLint border_, GLsizei imageSize_, const void * data_ ){
    static PFNGLCOMPRESSEDTEXIMAGE1DPROC F;
    if(!F)
        F = ( PFNGLCOMPRESSEDTEXIMAGE1DPROC ) mygetprocaddr("glCompressedTexImage1D");
    if( glCompressedTexImage1D_hook )
        glCompressedTexImage1D_hook( target_, level_, internalformat_, width_, border_, imageSize_, data_ );
    F(target_, level_, internalformat_, width_, border_, imageSize_, data_);
}
static glCompressedTexImage2D_hook_t glCompressedTexImage2D_hook = 0;
glCompressedTexImage2D_hook_t getHook_glCompressedTexImage2D (){
    return glCompressedTexImage2D_hook ;
}
void setHook_glCompressedTexImage2D ( glCompressedTexImage2D_hook_t hook ){
    glCompressedTexImage2D_hook = hook;
}
void glCompressedTexImage2D ( GLenum target_, GLint level_, GLenum internalformat_, GLsizei width_, GLsizei height_, GLint border_, GLsizei imageSize_, const void * data_ ){
    static PFNGLCOMPRESSEDTEXIMAGE2DPROC F;
    if(!F)
        F = ( PFNGLCOMPRESSEDTEXIMAGE2DPROC ) mygetprocaddr("glCompressedTexImage2D");
    if( glCompressedTexImage2D_hook )
        glCompressedTexImage2D_hook( target_, level_, internalformat_, width_, height_, border_, imageSize_, data_ );
    F(target_, level_, internalformat_, width_, height_, border_, imageSize_, data_);
}
static glCompressedTexImage3D_hook_t glCompressedTexImage3D_hook = 0;
glCompressedTexImage3D_hook_t getHook_glCompressedTexImage3D (){
    return glCompressedTexImage3D_hook ;
}
void setHook_glCompressedTexImage3D ( glCompressedTexImage3D_hook_t hook ){
    glCompressedTexImage3D_hook = hook;
}
void glCompressedTexImage3D ( GLenum target_, GLint level_, GLenum internalformat_, GLsizei width_, GLsizei height_, GLsizei depth_, GLint border_, GLsizei imageSize_, const void * data_ ){
    static PFNGLCOMPRESSEDTEXIMAGE3DPROC F;
    if(!F)
        F = ( PFNGLCOMPRESSEDTEXIMAGE3DPROC ) mygetprocaddr("glCompressedTexImage3D");
    if( glCompressedTexImage3D_hook )
        glCompressedTexImage3D_hook( target_, level_, internalformat_, width_, height_, depth_, border_, imageSize_, data_ );
    F(target_, level_, internalformat_, width_, height_, depth_, border_, imageSize_, data_);
}
static glCompressedTexSubImage1D_hook_t glCompressedTexSubImage1D_hook = 0;
glCompressedTexSubImage1D_hook_t getHook_glCompressedTexSubImage1D (){
    return glCompressedTexSubImage1D_hook ;
}
void setHook_glCompressedTexSubImage1D ( glCompressedTexSubImage1D_hook_t hook ){
    glCompressedTexSubImage1D_hook = hook;
}
void glCompressedTexSubImage1D ( GLenum target_, GLint level_, GLint xoffset_, GLsizei width_, GLenum format_, GLsizei imageSize_, const void * data_ ){
    static PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC F;
    if(!F)
        F = ( PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC ) mygetprocaddr("glCompressedTexSubImage1D");
    if( glCompressedTexSubImage1D_hook )
        glCompressedTexSubImage1D_hook( target_, level_, xoffset_, width_, format_, imageSize_, data_ );
    F(target_, level_, xoffset_, width_, format_, imageSize_, data_);
}
static glCompressedTexSubImage2D_hook_t glCompressedTexSubImage2D_hook = 0;
glCompressedTexSubImage2D_hook_t getHook_glCompressedTexSubImage2D (){
    return glCompressedTexSubImage2D_hook ;
}
void setHook_glCompressedTexSubImage2D ( glCompressedTexSubImage2D_hook_t hook ){
    glCompressedTexSubImage2D_hook = hook;
}
void glCompressedTexSubImage2D ( GLenum target_, GLint level_, GLint xoffset_, GLint yoffset_, GLsizei width_, GLsizei height_, GLenum format_, GLsizei imageSize_, const void * data_ ){
    static PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC F;
    if(!F)
        F = ( PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC ) mygetprocaddr("glCompressedTexSubImage2D");
    if( glCompressedTexSubImage2D_hook )
        glCompressedTexSubImage2D_hook( target_, level_, xoffset_, yoffset_, width_, height_, format_, imageSize_, data_ );
    F(target_, level_, xoffset_, yoffset_, width_, height_, format_, imageSize_, data_);
}
static glCompressedTexSubImage3D_hook_t glCompressedTexSubImage3D_hook = 0;
glCompressedTexSubImage3D_hook_t getHook_glCompressedTexSubImage3D (){
    return glCompressedTexSubImage3D_hook ;
}
void setHook_glCompressedTexSubImage3D ( glCompressedTexSubImage3D_hook_t hook ){
    glCompressedTexSubImage3D_hook = hook;
}
void glCompressedTexSubImage3D ( GLenum target_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLsizei width_, GLsizei height_, GLsizei depth_, GLenum format_, GLsizei imageSize_, const void * data_ ){
    static PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC F;
    if(!F)
        F = ( PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC ) mygetprocaddr("glCompressedTexSubImage3D");
    if( glCompressedTexSubImage3D_hook )
        glCompressedTexSubImage3D_hook( target_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, imageSize_, data_ );
    F(target_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, imageSize_, data_);
}
static glCompressedTextureSubImage1D_hook_t glCompressedTextureSubImage1D_hook = 0;
glCompressedTextureSubImage1D_hook_t getHook_glCompressedTextureSubImage1D (){
    return glCompressedTextureSubImage1D_hook ;
}
void setHook_glCompressedTextureSubImage1D ( glCompressedTextureSubImage1D_hook_t hook ){
    glCompressedTextureSubImage1D_hook = hook;
}
void glCompressedTextureSubImage1D ( GLuint texture_, GLint level_, GLint xoffset_, GLsizei width_, GLenum format_, GLsizei imageSize_, const void * data_ ){
    static PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC F;
    if(!F)
        F = ( PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC ) mygetprocaddr("glCompressedTextureSubImage1D");
    if( glCompressedTextureSubImage1D_hook )
        glCompressedTextureSubImage1D_hook( texture_, level_, xoffset_, width_, format_, imageSize_, data_ );
    F(texture_, level_, xoffset_, width_, format_, imageSize_, data_);
}
static glCompressedTextureSubImage2D_hook_t glCompressedTextureSubImage2D_hook = 0;
glCompressedTextureSubImage2D_hook_t getHook_glCompressedTextureSubImage2D (){
    return glCompressedTextureSubImage2D_hook ;
}
void setHook_glCompressedTextureSubImage2D ( glCompressedTextureSubImage2D_hook_t hook ){
    glCompressedTextureSubImage2D_hook = hook;
}
void glCompressedTextureSubImage2D ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLsizei width_, GLsizei height_, GLenum format_, GLsizei imageSize_, const void * data_ ){
    static PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC F;
    if(!F)
        F = ( PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC ) mygetprocaddr("glCompressedTextureSubImage2D");
    if( glCompressedTextureSubImage2D_hook )
        glCompressedTextureSubImage2D_hook( texture_, level_, xoffset_, yoffset_, width_, height_, format_, imageSize_, data_ );
    F(texture_, level_, xoffset_, yoffset_, width_, height_, format_, imageSize_, data_);
}
static glCompressedTextureSubImage3D_hook_t glCompressedTextureSubImage3D_hook = 0;
glCompressedTextureSubImage3D_hook_t getHook_glCompressedTextureSubImage3D (){
    return glCompressedTextureSubImage3D_hook ;
}
void setHook_glCompressedTextureSubImage3D ( glCompressedTextureSubImage3D_hook_t hook ){
    glCompressedTextureSubImage3D_hook = hook;
}
void glCompressedTextureSubImage3D ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLsizei width_, GLsizei height_, GLsizei depth_, GLenum format_, GLsizei imageSize_, const void * data_ ){
    static PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC F;
    if(!F)
        F = ( PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC ) mygetprocaddr("glCompressedTextureSubImage3D");
    if( glCompressedTextureSubImage3D_hook )
        glCompressedTextureSubImage3D_hook( texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, imageSize_, data_ );
    F(texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, imageSize_, data_);
}
static glCopyBufferSubData_hook_t glCopyBufferSubData_hook = 0;
glCopyBufferSubData_hook_t getHook_glCopyBufferSubData (){
    return glCopyBufferSubData_hook ;
}
void setHook_glCopyBufferSubData ( glCopyBufferSubData_hook_t hook ){
    glCopyBufferSubData_hook = hook;
}
void glCopyBufferSubData ( GLenum readTarget_, GLenum writeTarget_, GLintptr readOffset_, GLintptr writeOffset_, GLsizeiptr size_ ){
    static PFNGLCOPYBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLCOPYBUFFERSUBDATAPROC ) mygetprocaddr("glCopyBufferSubData");
    if( glCopyBufferSubData_hook )
        glCopyBufferSubData_hook( readTarget_, writeTarget_, readOffset_, writeOffset_, size_ );
    F(readTarget_, writeTarget_, readOffset_, writeOffset_, size_);
}
static glCopyImageSubData_hook_t glCopyImageSubData_hook = 0;
glCopyImageSubData_hook_t getHook_glCopyImageSubData (){
    return glCopyImageSubData_hook ;
}
void setHook_glCopyImageSubData ( glCopyImageSubData_hook_t hook ){
    glCopyImageSubData_hook = hook;
}
void glCopyImageSubData ( GLuint srcName_, GLenum srcTarget_, GLint srcLevel_, GLint srcX_, GLint srcY_, GLint srcZ_, GLuint dstName_, GLenum dstTarget_, GLint dstLevel_, GLint dstX_, GLint dstY_, GLint dstZ_, GLsizei srcWidth_, GLsizei srcHeight_, GLsizei srcDepth_ ){
    static PFNGLCOPYIMAGESUBDATAPROC F;
    if(!F)
        F = ( PFNGLCOPYIMAGESUBDATAPROC ) mygetprocaddr("glCopyImageSubData");
    if( glCopyImageSubData_hook )
        glCopyImageSubData_hook( srcName_, srcTarget_, srcLevel_, srcX_, srcY_, srcZ_, dstName_, dstTarget_, dstLevel_, dstX_, dstY_, dstZ_, srcWidth_, srcHeight_, srcDepth_ );
    F(srcName_, srcTarget_, srcLevel_, srcX_, srcY_, srcZ_, dstName_, dstTarget_, dstLevel_, dstX_, dstY_, dstZ_, srcWidth_, srcHeight_, srcDepth_);
}
static glCopyNamedBufferSubData_hook_t glCopyNamedBufferSubData_hook = 0;
glCopyNamedBufferSubData_hook_t getHook_glCopyNamedBufferSubData (){
    return glCopyNamedBufferSubData_hook ;
}
void setHook_glCopyNamedBufferSubData ( glCopyNamedBufferSubData_hook_t hook ){
    glCopyNamedBufferSubData_hook = hook;
}
void glCopyNamedBufferSubData ( GLuint readBuffer_, GLuint writeBuffer_, GLintptr readOffset_, GLintptr writeOffset_, GLsizeiptr size_ ){
    static PFNGLCOPYNAMEDBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLCOPYNAMEDBUFFERSUBDATAPROC ) mygetprocaddr("glCopyNamedBufferSubData");
    if( glCopyNamedBufferSubData_hook )
        glCopyNamedBufferSubData_hook( readBuffer_, writeBuffer_, readOffset_, writeOffset_, size_ );
    F(readBuffer_, writeBuffer_, readOffset_, writeOffset_, size_);
}
static glCopyTexImage1D_hook_t glCopyTexImage1D_hook = 0;
glCopyTexImage1D_hook_t getHook_glCopyTexImage1D (){
    return glCopyTexImage1D_hook ;
}
void setHook_glCopyTexImage1D ( glCopyTexImage1D_hook_t hook ){
    glCopyTexImage1D_hook = hook;
}
void glCopyTexImage1D ( GLenum target_, GLint level_, GLenum internalformat_, GLint x_, GLint y_, GLsizei width_, GLint border_ ){
    static PFNGLCOPYTEXIMAGE1DPROC F;
    if(!F)
        F = ( PFNGLCOPYTEXIMAGE1DPROC ) mygetprocaddr("glCopyTexImage1D");
    if( glCopyTexImage1D_hook )
        glCopyTexImage1D_hook( target_, level_, internalformat_, x_, y_, width_, border_ );
    F(target_, level_, internalformat_, x_, y_, width_, border_);
}
static glCopyTexImage2D_hook_t glCopyTexImage2D_hook = 0;
glCopyTexImage2D_hook_t getHook_glCopyTexImage2D (){
    return glCopyTexImage2D_hook ;
}
void setHook_glCopyTexImage2D ( glCopyTexImage2D_hook_t hook ){
    glCopyTexImage2D_hook = hook;
}
void glCopyTexImage2D ( GLenum target_, GLint level_, GLenum internalformat_, GLint x_, GLint y_, GLsizei width_, GLsizei height_, GLint border_ ){
    static PFNGLCOPYTEXIMAGE2DPROC F;
    if(!F)
        F = ( PFNGLCOPYTEXIMAGE2DPROC ) mygetprocaddr("glCopyTexImage2D");
    if( glCopyTexImage2D_hook )
        glCopyTexImage2D_hook( target_, level_, internalformat_, x_, y_, width_, height_, border_ );
    F(target_, level_, internalformat_, x_, y_, width_, height_, border_);
}
static glCopyTexSubImage1D_hook_t glCopyTexSubImage1D_hook = 0;
glCopyTexSubImage1D_hook_t getHook_glCopyTexSubImage1D (){
    return glCopyTexSubImage1D_hook ;
}
void setHook_glCopyTexSubImage1D ( glCopyTexSubImage1D_hook_t hook ){
    glCopyTexSubImage1D_hook = hook;
}
void glCopyTexSubImage1D ( GLenum target_, GLint level_, GLint xoffset_, GLint x_, GLint y_, GLsizei width_ ){
    static PFNGLCOPYTEXSUBIMAGE1DPROC F;
    if(!F)
        F = ( PFNGLCOPYTEXSUBIMAGE1DPROC ) mygetprocaddr("glCopyTexSubImage1D");
    if( glCopyTexSubImage1D_hook )
        glCopyTexSubImage1D_hook( target_, level_, xoffset_, x_, y_, width_ );
    F(target_, level_, xoffset_, x_, y_, width_);
}
static glCopyTexSubImage2D_hook_t glCopyTexSubImage2D_hook = 0;
glCopyTexSubImage2D_hook_t getHook_glCopyTexSubImage2D (){
    return glCopyTexSubImage2D_hook ;
}
void setHook_glCopyTexSubImage2D ( glCopyTexSubImage2D_hook_t hook ){
    glCopyTexSubImage2D_hook = hook;
}
void glCopyTexSubImage2D ( GLenum target_, GLint level_, GLint xoffset_, GLint yoffset_, GLint x_, GLint y_, GLsizei width_, GLsizei height_ ){
    static PFNGLCOPYTEXSUBIMAGE2DPROC F;
    if(!F)
        F = ( PFNGLCOPYTEXSUBIMAGE2DPROC ) mygetprocaddr("glCopyTexSubImage2D");
    if( glCopyTexSubImage2D_hook )
        glCopyTexSubImage2D_hook( target_, level_, xoffset_, yoffset_, x_, y_, width_, height_ );
    F(target_, level_, xoffset_, yoffset_, x_, y_, width_, height_);
}
static glCopyTexSubImage3D_hook_t glCopyTexSubImage3D_hook = 0;
glCopyTexSubImage3D_hook_t getHook_glCopyTexSubImage3D (){
    return glCopyTexSubImage3D_hook ;
}
void setHook_glCopyTexSubImage3D ( glCopyTexSubImage3D_hook_t hook ){
    glCopyTexSubImage3D_hook = hook;
}
void glCopyTexSubImage3D ( GLenum target_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLint x_, GLint y_, GLsizei width_, GLsizei height_ ){
    static PFNGLCOPYTEXSUBIMAGE3DPROC F;
    if(!F)
        F = ( PFNGLCOPYTEXSUBIMAGE3DPROC ) mygetprocaddr("glCopyTexSubImage3D");
    if( glCopyTexSubImage3D_hook )
        glCopyTexSubImage3D_hook( target_, level_, xoffset_, yoffset_, zoffset_, x_, y_, width_, height_ );
    F(target_, level_, xoffset_, yoffset_, zoffset_, x_, y_, width_, height_);
}
static glCopyTextureSubImage1D_hook_t glCopyTextureSubImage1D_hook = 0;
glCopyTextureSubImage1D_hook_t getHook_glCopyTextureSubImage1D (){
    return glCopyTextureSubImage1D_hook ;
}
void setHook_glCopyTextureSubImage1D ( glCopyTextureSubImage1D_hook_t hook ){
    glCopyTextureSubImage1D_hook = hook;
}
void glCopyTextureSubImage1D ( GLuint texture_, GLint level_, GLint xoffset_, GLint x_, GLint y_, GLsizei width_ ){
    static PFNGLCOPYTEXTURESUBIMAGE1DPROC F;
    if(!F)
        F = ( PFNGLCOPYTEXTURESUBIMAGE1DPROC ) mygetprocaddr("glCopyTextureSubImage1D");
    if( glCopyTextureSubImage1D_hook )
        glCopyTextureSubImage1D_hook( texture_, level_, xoffset_, x_, y_, width_ );
    F(texture_, level_, xoffset_, x_, y_, width_);
}
static glCopyTextureSubImage2D_hook_t glCopyTextureSubImage2D_hook = 0;
glCopyTextureSubImage2D_hook_t getHook_glCopyTextureSubImage2D (){
    return glCopyTextureSubImage2D_hook ;
}
void setHook_glCopyTextureSubImage2D ( glCopyTextureSubImage2D_hook_t hook ){
    glCopyTextureSubImage2D_hook = hook;
}
void glCopyTextureSubImage2D ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLint x_, GLint y_, GLsizei width_, GLsizei height_ ){
    static PFNGLCOPYTEXTURESUBIMAGE2DPROC F;
    if(!F)
        F = ( PFNGLCOPYTEXTURESUBIMAGE2DPROC ) mygetprocaddr("glCopyTextureSubImage2D");
    if( glCopyTextureSubImage2D_hook )
        glCopyTextureSubImage2D_hook( texture_, level_, xoffset_, yoffset_, x_, y_, width_, height_ );
    F(texture_, level_, xoffset_, yoffset_, x_, y_, width_, height_);
}
static glCopyTextureSubImage3D_hook_t glCopyTextureSubImage3D_hook = 0;
glCopyTextureSubImage3D_hook_t getHook_glCopyTextureSubImage3D (){
    return glCopyTextureSubImage3D_hook ;
}
void setHook_glCopyTextureSubImage3D ( glCopyTextureSubImage3D_hook_t hook ){
    glCopyTextureSubImage3D_hook = hook;
}
void glCopyTextureSubImage3D ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLint x_, GLint y_, GLsizei width_, GLsizei height_ ){
    static PFNGLCOPYTEXTURESUBIMAGE3DPROC F;
    if(!F)
        F = ( PFNGLCOPYTEXTURESUBIMAGE3DPROC ) mygetprocaddr("glCopyTextureSubImage3D");
    if( glCopyTextureSubImage3D_hook )
        glCopyTextureSubImage3D_hook( texture_, level_, xoffset_, yoffset_, zoffset_, x_, y_, width_, height_ );
    F(texture_, level_, xoffset_, yoffset_, zoffset_, x_, y_, width_, height_);
}
static glCreateBuffers_hook_t glCreateBuffers_hook = 0;
glCreateBuffers_hook_t getHook_glCreateBuffers (){
    return glCreateBuffers_hook ;
}
void setHook_glCreateBuffers ( glCreateBuffers_hook_t hook ){
    glCreateBuffers_hook = hook;
}
void glCreateBuffers ( GLsizei n_, GLuint * buffers_ ){
    static PFNGLCREATEBUFFERSPROC F;
    if(!F)
        F = ( PFNGLCREATEBUFFERSPROC ) mygetprocaddr("glCreateBuffers");
    if( glCreateBuffers_hook )
        glCreateBuffers_hook( n_, buffers_ );
    F(n_, buffers_);
}
static glCreateFramebuffers_hook_t glCreateFramebuffers_hook = 0;
glCreateFramebuffers_hook_t getHook_glCreateFramebuffers (){
    return glCreateFramebuffers_hook ;
}
void setHook_glCreateFramebuffers ( glCreateFramebuffers_hook_t hook ){
    glCreateFramebuffers_hook = hook;
}
void glCreateFramebuffers ( GLsizei n_, GLuint * framebuffers_ ){
    static PFNGLCREATEFRAMEBUFFERSPROC F;
    if(!F)
        F = ( PFNGLCREATEFRAMEBUFFERSPROC ) mygetprocaddr("glCreateFramebuffers");
    if( glCreateFramebuffers_hook )
        glCreateFramebuffers_hook( n_, framebuffers_ );
    F(n_, framebuffers_);
}
static glCreateProgram_hook_t glCreateProgram_hook = 0;
glCreateProgram_hook_t getHook_glCreateProgram (){
    return glCreateProgram_hook ;
}
void setHook_glCreateProgram ( glCreateProgram_hook_t hook ){
    glCreateProgram_hook = hook;
}
GLuint glCreateProgram (  ){
    static PFNGLCREATEPROGRAMPROC F;
    if(!F)
        F = ( PFNGLCREATEPROGRAMPROC ) mygetprocaddr("glCreateProgram");
    if( glCreateProgram_hook )
        glCreateProgram_hook(  );
    GLuint retval = F();
    return retval;
}
static glCreateProgramPipelines_hook_t glCreateProgramPipelines_hook = 0;
glCreateProgramPipelines_hook_t getHook_glCreateProgramPipelines (){
    return glCreateProgramPipelines_hook ;
}
void setHook_glCreateProgramPipelines ( glCreateProgramPipelines_hook_t hook ){
    glCreateProgramPipelines_hook = hook;
}
void glCreateProgramPipelines ( GLsizei n_, GLuint * pipelines_ ){
    static PFNGLCREATEPROGRAMPIPELINESPROC F;
    if(!F)
        F = ( PFNGLCREATEPROGRAMPIPELINESPROC ) mygetprocaddr("glCreateProgramPipelines");
    if( glCreateProgramPipelines_hook )
        glCreateProgramPipelines_hook( n_, pipelines_ );
    F(n_, pipelines_);
}
static glCreateQueries_hook_t glCreateQueries_hook = 0;
glCreateQueries_hook_t getHook_glCreateQueries (){
    return glCreateQueries_hook ;
}
void setHook_glCreateQueries ( glCreateQueries_hook_t hook ){
    glCreateQueries_hook = hook;
}
void glCreateQueries ( GLenum target_, GLsizei n_, GLuint * ids_ ){
    static PFNGLCREATEQUERIESPROC F;
    if(!F)
        F = ( PFNGLCREATEQUERIESPROC ) mygetprocaddr("glCreateQueries");
    if( glCreateQueries_hook )
        glCreateQueries_hook( target_, n_, ids_ );
    F(target_, n_, ids_);
}
static glCreateRenderbuffers_hook_t glCreateRenderbuffers_hook = 0;
glCreateRenderbuffers_hook_t getHook_glCreateRenderbuffers (){
    return glCreateRenderbuffers_hook ;
}
void setHook_glCreateRenderbuffers ( glCreateRenderbuffers_hook_t hook ){
    glCreateRenderbuffers_hook = hook;
}
void glCreateRenderbuffers ( GLsizei n_, GLuint * renderbuffers_ ){
    static PFNGLCREATERENDERBUFFERSPROC F;
    if(!F)
        F = ( PFNGLCREATERENDERBUFFERSPROC ) mygetprocaddr("glCreateRenderbuffers");
    if( glCreateRenderbuffers_hook )
        glCreateRenderbuffers_hook( n_, renderbuffers_ );
    F(n_, renderbuffers_);
}
static glCreateSamplers_hook_t glCreateSamplers_hook = 0;
glCreateSamplers_hook_t getHook_glCreateSamplers (){
    return glCreateSamplers_hook ;
}
void setHook_glCreateSamplers ( glCreateSamplers_hook_t hook ){
    glCreateSamplers_hook = hook;
}
void glCreateSamplers ( GLsizei n_, GLuint * samplers_ ){
    static PFNGLCREATESAMPLERSPROC F;
    if(!F)
        F = ( PFNGLCREATESAMPLERSPROC ) mygetprocaddr("glCreateSamplers");
    if( glCreateSamplers_hook )
        glCreateSamplers_hook( n_, samplers_ );
    F(n_, samplers_);
}
static glCreateShader_hook_t glCreateShader_hook = 0;
glCreateShader_hook_t getHook_glCreateShader (){
    return glCreateShader_hook ;
}
void setHook_glCreateShader ( glCreateShader_hook_t hook ){
    glCreateShader_hook = hook;
}
GLuint glCreateShader ( GLenum type_ ){
    static PFNGLCREATESHADERPROC F;
    if(!F)
        F = ( PFNGLCREATESHADERPROC ) mygetprocaddr("glCreateShader");
    if( glCreateShader_hook )
        glCreateShader_hook( type_ );
    GLuint retval = F(type_);
    return retval;
}
static glCreateShaderProgramv_hook_t glCreateShaderProgramv_hook = 0;
glCreateShaderProgramv_hook_t getHook_glCreateShaderProgramv (){
    return glCreateShaderProgramv_hook ;
}
void setHook_glCreateShaderProgramv ( glCreateShaderProgramv_hook_t hook ){
    glCreateShaderProgramv_hook = hook;
}
GLuint glCreateShaderProgramv ( GLenum type_, GLsizei count_, const GLchar ** strings_ ){
    static PFNGLCREATESHADERPROGRAMVPROC F;
    if(!F)
        F = ( PFNGLCREATESHADERPROGRAMVPROC ) mygetprocaddr("glCreateShaderProgramv");
    if( glCreateShaderProgramv_hook )
        glCreateShaderProgramv_hook( type_, count_, strings_ );
    GLuint retval = F(type_, count_, strings_);
    return retval;
}
static glCreateTextures_hook_t glCreateTextures_hook = 0;
glCreateTextures_hook_t getHook_glCreateTextures (){
    return glCreateTextures_hook ;
}
void setHook_glCreateTextures ( glCreateTextures_hook_t hook ){
    glCreateTextures_hook = hook;
}
void glCreateTextures ( GLenum target_, GLsizei n_, GLuint * textures_ ){
    static PFNGLCREATETEXTURESPROC F;
    if(!F)
        F = ( PFNGLCREATETEXTURESPROC ) mygetprocaddr("glCreateTextures");
    if( glCreateTextures_hook )
        glCreateTextures_hook( target_, n_, textures_ );
    F(target_, n_, textures_);
}
static glCreateTransformFeedbacks_hook_t glCreateTransformFeedbacks_hook = 0;
glCreateTransformFeedbacks_hook_t getHook_glCreateTransformFeedbacks (){
    return glCreateTransformFeedbacks_hook ;
}
void setHook_glCreateTransformFeedbacks ( glCreateTransformFeedbacks_hook_t hook ){
    glCreateTransformFeedbacks_hook = hook;
}
void glCreateTransformFeedbacks ( GLsizei n_, GLuint * ids_ ){
    static PFNGLCREATETRANSFORMFEEDBACKSPROC F;
    if(!F)
        F = ( PFNGLCREATETRANSFORMFEEDBACKSPROC ) mygetprocaddr("glCreateTransformFeedbacks");
    if( glCreateTransformFeedbacks_hook )
        glCreateTransformFeedbacks_hook( n_, ids_ );
    F(n_, ids_);
}
static glCreateVertexArrays_hook_t glCreateVertexArrays_hook = 0;
glCreateVertexArrays_hook_t getHook_glCreateVertexArrays (){
    return glCreateVertexArrays_hook ;
}
void setHook_glCreateVertexArrays ( glCreateVertexArrays_hook_t hook ){
    glCreateVertexArrays_hook = hook;
}
void glCreateVertexArrays ( GLsizei n_, GLuint * arrays_ ){
    static PFNGLCREATEVERTEXARRAYSPROC F;
    if(!F)
        F = ( PFNGLCREATEVERTEXARRAYSPROC ) mygetprocaddr("glCreateVertexArrays");
    if( glCreateVertexArrays_hook )
        glCreateVertexArrays_hook( n_, arrays_ );
    F(n_, arrays_);
}
static glCullFace_hook_t glCullFace_hook = 0;
glCullFace_hook_t getHook_glCullFace (){
    return glCullFace_hook ;
}
void setHook_glCullFace ( glCullFace_hook_t hook ){
    glCullFace_hook = hook;
}
void glCullFace ( GLenum mode_ ){
    static PFNGLCULLFACEPROC F;
    if(!F)
        F = ( PFNGLCULLFACEPROC ) mygetprocaddr("glCullFace");
    if( glCullFace_hook )
        glCullFace_hook( mode_ );
    F(mode_);
}
static glDebugMessageCallback_hook_t glDebugMessageCallback_hook = 0;
glDebugMessageCallback_hook_t getHook_glDebugMessageCallback (){
    return glDebugMessageCallback_hook ;
}
void setHook_glDebugMessageCallback ( glDebugMessageCallback_hook_t hook ){
    glDebugMessageCallback_hook = hook;
}
void glDebugMessageCallback ( GLDEBUGPROC callback_, const void * userParam_ ){
    static PFNGLDEBUGMESSAGECALLBACKPROC F;
    if(!F)
        F = ( PFNGLDEBUGMESSAGECALLBACKPROC ) mygetprocaddr("glDebugMessageCallback");
    if( glDebugMessageCallback_hook )
        glDebugMessageCallback_hook( callback_, userParam_ );
    F(callback_, userParam_);
}
static glDebugMessageControl_hook_t glDebugMessageControl_hook = 0;
glDebugMessageControl_hook_t getHook_glDebugMessageControl (){
    return glDebugMessageControl_hook ;
}
void setHook_glDebugMessageControl ( glDebugMessageControl_hook_t hook ){
    glDebugMessageControl_hook = hook;
}
void glDebugMessageControl ( GLenum source_, GLenum type_, GLenum severity_, GLsizei count_, const GLuint * ids_, GLboolean enabled_ ){
    static PFNGLDEBUGMESSAGECONTROLPROC F;
    if(!F)
        F = ( PFNGLDEBUGMESSAGECONTROLPROC ) mygetprocaddr("glDebugMessageControl");
    if( glDebugMessageControl_hook )
        glDebugMessageControl_hook( source_, type_, severity_, count_, ids_, enabled_ );
    F(source_, type_, severity_, count_, ids_, enabled_);
}
static glDebugMessageInsert_hook_t glDebugMessageInsert_hook = 0;
glDebugMessageInsert_hook_t getHook_glDebugMessageInsert (){
    return glDebugMessageInsert_hook ;
}
void setHook_glDebugMessageInsert ( glDebugMessageInsert_hook_t hook ){
    glDebugMessageInsert_hook = hook;
}
void glDebugMessageInsert ( GLenum source_, GLenum type_, GLuint id_, GLenum severity_, GLsizei length_, const GLchar * buf_ ){
    static PFNGLDEBUGMESSAGEINSERTPROC F;
    if(!F)
        F = ( PFNGLDEBUGMESSAGEINSERTPROC ) mygetprocaddr("glDebugMessageInsert");
    if( glDebugMessageInsert_hook )
        glDebugMessageInsert_hook( source_, type_, id_, severity_, length_, buf_ );
    F(source_, type_, id_, severity_, length_, buf_);
}
static glDeleteBuffers_hook_t glDeleteBuffers_hook = 0;
glDeleteBuffers_hook_t getHook_glDeleteBuffers (){
    return glDeleteBuffers_hook ;
}
void setHook_glDeleteBuffers ( glDeleteBuffers_hook_t hook ){
    glDeleteBuffers_hook = hook;
}
void glDeleteBuffers ( GLsizei n_, const GLuint * buffers_ ){
    static PFNGLDELETEBUFFERSPROC F;
    if(!F)
        F = ( PFNGLDELETEBUFFERSPROC ) mygetprocaddr("glDeleteBuffers");
    if( glDeleteBuffers_hook )
        glDeleteBuffers_hook( n_, buffers_ );
    F(n_, buffers_);
}
static glDeleteFramebuffers_hook_t glDeleteFramebuffers_hook = 0;
glDeleteFramebuffers_hook_t getHook_glDeleteFramebuffers (){
    return glDeleteFramebuffers_hook ;
}
void setHook_glDeleteFramebuffers ( glDeleteFramebuffers_hook_t hook ){
    glDeleteFramebuffers_hook = hook;
}
void glDeleteFramebuffers ( GLsizei n_, const GLuint * framebuffers_ ){
    static PFNGLDELETEFRAMEBUFFERSPROC F;
    if(!F)
        F = ( PFNGLDELETEFRAMEBUFFERSPROC ) mygetprocaddr("glDeleteFramebuffers");
    if( glDeleteFramebuffers_hook )
        glDeleteFramebuffers_hook( n_, framebuffers_ );
    F(n_, framebuffers_);
}
static glDeleteProgram_hook_t glDeleteProgram_hook = 0;
glDeleteProgram_hook_t getHook_glDeleteProgram (){
    return glDeleteProgram_hook ;
}
void setHook_glDeleteProgram ( glDeleteProgram_hook_t hook ){
    glDeleteProgram_hook = hook;
}
void glDeleteProgram ( GLuint program_ ){
    static PFNGLDELETEPROGRAMPROC F;
    if(!F)
        F = ( PFNGLDELETEPROGRAMPROC ) mygetprocaddr("glDeleteProgram");
    if( glDeleteProgram_hook )
        glDeleteProgram_hook( program_ );
    F(program_);
}
static glDeleteProgramPipelines_hook_t glDeleteProgramPipelines_hook = 0;
glDeleteProgramPipelines_hook_t getHook_glDeleteProgramPipelines (){
    return glDeleteProgramPipelines_hook ;
}
void setHook_glDeleteProgramPipelines ( glDeleteProgramPipelines_hook_t hook ){
    glDeleteProgramPipelines_hook = hook;
}
void glDeleteProgramPipelines ( GLsizei n_, const GLuint * pipelines_ ){
    static PFNGLDELETEPROGRAMPIPELINESPROC F;
    if(!F)
        F = ( PFNGLDELETEPROGRAMPIPELINESPROC ) mygetprocaddr("glDeleteProgramPipelines");
    if( glDeleteProgramPipelines_hook )
        glDeleteProgramPipelines_hook( n_, pipelines_ );
    F(n_, pipelines_);
}
static glDeleteQueries_hook_t glDeleteQueries_hook = 0;
glDeleteQueries_hook_t getHook_glDeleteQueries (){
    return glDeleteQueries_hook ;
}
void setHook_glDeleteQueries ( glDeleteQueries_hook_t hook ){
    glDeleteQueries_hook = hook;
}
void glDeleteQueries ( GLsizei n_, const GLuint * ids_ ){
    static PFNGLDELETEQUERIESPROC F;
    if(!F)
        F = ( PFNGLDELETEQUERIESPROC ) mygetprocaddr("glDeleteQueries");
    if( glDeleteQueries_hook )
        glDeleteQueries_hook( n_, ids_ );
    F(n_, ids_);
}
static glDeleteRenderbuffers_hook_t glDeleteRenderbuffers_hook = 0;
glDeleteRenderbuffers_hook_t getHook_glDeleteRenderbuffers (){
    return glDeleteRenderbuffers_hook ;
}
void setHook_glDeleteRenderbuffers ( glDeleteRenderbuffers_hook_t hook ){
    glDeleteRenderbuffers_hook = hook;
}
void glDeleteRenderbuffers ( GLsizei n_, const GLuint * renderbuffers_ ){
    static PFNGLDELETERENDERBUFFERSPROC F;
    if(!F)
        F = ( PFNGLDELETERENDERBUFFERSPROC ) mygetprocaddr("glDeleteRenderbuffers");
    if( glDeleteRenderbuffers_hook )
        glDeleteRenderbuffers_hook( n_, renderbuffers_ );
    F(n_, renderbuffers_);
}
static glDeleteSamplers_hook_t glDeleteSamplers_hook = 0;
glDeleteSamplers_hook_t getHook_glDeleteSamplers (){
    return glDeleteSamplers_hook ;
}
void setHook_glDeleteSamplers ( glDeleteSamplers_hook_t hook ){
    glDeleteSamplers_hook = hook;
}
void glDeleteSamplers ( GLsizei count_, const GLuint * samplers_ ){
    static PFNGLDELETESAMPLERSPROC F;
    if(!F)
        F = ( PFNGLDELETESAMPLERSPROC ) mygetprocaddr("glDeleteSamplers");
    if( glDeleteSamplers_hook )
        glDeleteSamplers_hook( count_, samplers_ );
    F(count_, samplers_);
}
static glDeleteShader_hook_t glDeleteShader_hook = 0;
glDeleteShader_hook_t getHook_glDeleteShader (){
    return glDeleteShader_hook ;
}
void setHook_glDeleteShader ( glDeleteShader_hook_t hook ){
    glDeleteShader_hook = hook;
}
void glDeleteShader ( GLuint shader_ ){
    static PFNGLDELETESHADERPROC F;
    if(!F)
        F = ( PFNGLDELETESHADERPROC ) mygetprocaddr("glDeleteShader");
    if( glDeleteShader_hook )
        glDeleteShader_hook( shader_ );
    F(shader_);
}
static glDeleteSync_hook_t glDeleteSync_hook = 0;
glDeleteSync_hook_t getHook_glDeleteSync (){
    return glDeleteSync_hook ;
}
void setHook_glDeleteSync ( glDeleteSync_hook_t hook ){
    glDeleteSync_hook = hook;
}
void glDeleteSync ( GLsync sync_ ){
    static PFNGLDELETESYNCPROC F;
    if(!F)
        F = ( PFNGLDELETESYNCPROC ) mygetprocaddr("glDeleteSync");
    if( glDeleteSync_hook )
        glDeleteSync_hook( sync_ );
    F(sync_);
}
static glDeleteTextures_hook_t glDeleteTextures_hook = 0;
glDeleteTextures_hook_t getHook_glDeleteTextures (){
    return glDeleteTextures_hook ;
}
void setHook_glDeleteTextures ( glDeleteTextures_hook_t hook ){
    glDeleteTextures_hook = hook;
}
void glDeleteTextures ( GLsizei n_, const GLuint * textures_ ){
    static PFNGLDELETETEXTURESPROC F;
    if(!F)
        F = ( PFNGLDELETETEXTURESPROC ) mygetprocaddr("glDeleteTextures");
    if( glDeleteTextures_hook )
        glDeleteTextures_hook( n_, textures_ );
    F(n_, textures_);
}
static glDeleteTransformFeedbacks_hook_t glDeleteTransformFeedbacks_hook = 0;
glDeleteTransformFeedbacks_hook_t getHook_glDeleteTransformFeedbacks (){
    return glDeleteTransformFeedbacks_hook ;
}
void setHook_glDeleteTransformFeedbacks ( glDeleteTransformFeedbacks_hook_t hook ){
    glDeleteTransformFeedbacks_hook = hook;
}
void glDeleteTransformFeedbacks ( GLsizei n_, const GLuint * ids_ ){
    static PFNGLDELETETRANSFORMFEEDBACKSPROC F;
    if(!F)
        F = ( PFNGLDELETETRANSFORMFEEDBACKSPROC ) mygetprocaddr("glDeleteTransformFeedbacks");
    if( glDeleteTransformFeedbacks_hook )
        glDeleteTransformFeedbacks_hook( n_, ids_ );
    F(n_, ids_);
}
static glDeleteVertexArrays_hook_t glDeleteVertexArrays_hook = 0;
glDeleteVertexArrays_hook_t getHook_glDeleteVertexArrays (){
    return glDeleteVertexArrays_hook ;
}
void setHook_glDeleteVertexArrays ( glDeleteVertexArrays_hook_t hook ){
    glDeleteVertexArrays_hook = hook;
}
void glDeleteVertexArrays ( GLsizei n_, const GLuint * arrays_ ){
    static PFNGLDELETEVERTEXARRAYSPROC F;
    if(!F)
        F = ( PFNGLDELETEVERTEXARRAYSPROC ) mygetprocaddr("glDeleteVertexArrays");
    if( glDeleteVertexArrays_hook )
        glDeleteVertexArrays_hook( n_, arrays_ );
    F(n_, arrays_);
}
static glDepthFunc_hook_t glDepthFunc_hook = 0;
glDepthFunc_hook_t getHook_glDepthFunc (){
    return glDepthFunc_hook ;
}
void setHook_glDepthFunc ( glDepthFunc_hook_t hook ){
    glDepthFunc_hook = hook;
}
void glDepthFunc ( GLenum func_ ){
    static PFNGLDEPTHFUNCPROC F;
    if(!F)
        F = ( PFNGLDEPTHFUNCPROC ) mygetprocaddr("glDepthFunc");
    if( glDepthFunc_hook )
        glDepthFunc_hook( func_ );
    F(func_);
}
static glDepthMask_hook_t glDepthMask_hook = 0;
glDepthMask_hook_t getHook_glDepthMask (){
    return glDepthMask_hook ;
}
void setHook_glDepthMask ( glDepthMask_hook_t hook ){
    glDepthMask_hook = hook;
}
void glDepthMask ( GLboolean flag_ ){
    static PFNGLDEPTHMASKPROC F;
    if(!F)
        F = ( PFNGLDEPTHMASKPROC ) mygetprocaddr("glDepthMask");
    if( glDepthMask_hook )
        glDepthMask_hook( flag_ );
    F(flag_);
}
static glDepthRange_hook_t glDepthRange_hook = 0;
glDepthRange_hook_t getHook_glDepthRange (){
    return glDepthRange_hook ;
}
void setHook_glDepthRange ( glDepthRange_hook_t hook ){
    glDepthRange_hook = hook;
}
void glDepthRange ( GLdouble near_, GLdouble far_ ){
    static PFNGLDEPTHRANGEPROC F;
    if(!F)
        F = ( PFNGLDEPTHRANGEPROC ) mygetprocaddr("glDepthRange");
    if( glDepthRange_hook )
        glDepthRange_hook( near_, far_ );
    F(near_, far_);
}
static glDepthRangeArrayv_hook_t glDepthRangeArrayv_hook = 0;
glDepthRangeArrayv_hook_t getHook_glDepthRangeArrayv (){
    return glDepthRangeArrayv_hook ;
}
void setHook_glDepthRangeArrayv ( glDepthRangeArrayv_hook_t hook ){
    glDepthRangeArrayv_hook = hook;
}
void glDepthRangeArrayv ( GLuint first_, GLsizei count_, const GLdouble * v_ ){
    static PFNGLDEPTHRANGEARRAYVPROC F;
    if(!F)
        F = ( PFNGLDEPTHRANGEARRAYVPROC ) mygetprocaddr("glDepthRangeArrayv");
    if( glDepthRangeArrayv_hook )
        glDepthRangeArrayv_hook( first_, count_, v_ );
    F(first_, count_, v_);
}
static glDepthRangeIndexed_hook_t glDepthRangeIndexed_hook = 0;
glDepthRangeIndexed_hook_t getHook_glDepthRangeIndexed (){
    return glDepthRangeIndexed_hook ;
}
void setHook_glDepthRangeIndexed ( glDepthRangeIndexed_hook_t hook ){
    glDepthRangeIndexed_hook = hook;
}
void glDepthRangeIndexed ( GLuint index_, GLdouble n_, GLdouble f_ ){
    static PFNGLDEPTHRANGEINDEXEDPROC F;
    if(!F)
        F = ( PFNGLDEPTHRANGEINDEXEDPROC ) mygetprocaddr("glDepthRangeIndexed");
    if( glDepthRangeIndexed_hook )
        glDepthRangeIndexed_hook( index_, n_, f_ );
    F(index_, n_, f_);
}
static glDepthRangef_hook_t glDepthRangef_hook = 0;
glDepthRangef_hook_t getHook_glDepthRangef (){
    return glDepthRangef_hook ;
}
void setHook_glDepthRangef ( glDepthRangef_hook_t hook ){
    glDepthRangef_hook = hook;
}
void glDepthRangef ( GLfloat n_, GLfloat f_ ){
    static PFNGLDEPTHRANGEFPROC F;
    if(!F)
        F = ( PFNGLDEPTHRANGEFPROC ) mygetprocaddr("glDepthRangef");
    if( glDepthRangef_hook )
        glDepthRangef_hook( n_, f_ );
    F(n_, f_);
}
static glDetachShader_hook_t glDetachShader_hook = 0;
glDetachShader_hook_t getHook_glDetachShader (){
    return glDetachShader_hook ;
}
void setHook_glDetachShader ( glDetachShader_hook_t hook ){
    glDetachShader_hook = hook;
}
void glDetachShader ( GLuint program_, GLuint shader_ ){
    static PFNGLDETACHSHADERPROC F;
    if(!F)
        F = ( PFNGLDETACHSHADERPROC ) mygetprocaddr("glDetachShader");
    if( glDetachShader_hook )
        glDetachShader_hook( program_, shader_ );
    F(program_, shader_);
}
static glDisable_hook_t glDisable_hook = 0;
glDisable_hook_t getHook_glDisable (){
    return glDisable_hook ;
}
void setHook_glDisable ( glDisable_hook_t hook ){
    glDisable_hook = hook;
}
void glDisable ( GLenum cap_ ){
    static PFNGLDISABLEPROC F;
    if(!F)
        F = ( PFNGLDISABLEPROC ) mygetprocaddr("glDisable");
    if( glDisable_hook )
        glDisable_hook( cap_ );
    F(cap_);
}
static glDisableVertexArrayAttrib_hook_t glDisableVertexArrayAttrib_hook = 0;
glDisableVertexArrayAttrib_hook_t getHook_glDisableVertexArrayAttrib (){
    return glDisableVertexArrayAttrib_hook ;
}
void setHook_glDisableVertexArrayAttrib ( glDisableVertexArrayAttrib_hook_t hook ){
    glDisableVertexArrayAttrib_hook = hook;
}
void glDisableVertexArrayAttrib ( GLuint vaobj_, GLuint index_ ){
    static PFNGLDISABLEVERTEXARRAYATTRIBPROC F;
    if(!F)
        F = ( PFNGLDISABLEVERTEXARRAYATTRIBPROC ) mygetprocaddr("glDisableVertexArrayAttrib");
    if( glDisableVertexArrayAttrib_hook )
        glDisableVertexArrayAttrib_hook( vaobj_, index_ );
    F(vaobj_, index_);
}
static glDisableVertexAttribArray_hook_t glDisableVertexAttribArray_hook = 0;
glDisableVertexAttribArray_hook_t getHook_glDisableVertexAttribArray (){
    return glDisableVertexAttribArray_hook ;
}
void setHook_glDisableVertexAttribArray ( glDisableVertexAttribArray_hook_t hook ){
    glDisableVertexAttribArray_hook = hook;
}
void glDisableVertexAttribArray ( GLuint index_ ){
    static PFNGLDISABLEVERTEXATTRIBARRAYPROC F;
    if(!F)
        F = ( PFNGLDISABLEVERTEXATTRIBARRAYPROC ) mygetprocaddr("glDisableVertexAttribArray");
    if( glDisableVertexAttribArray_hook )
        glDisableVertexAttribArray_hook( index_ );
    F(index_);
}
static glDisablei_hook_t glDisablei_hook = 0;
glDisablei_hook_t getHook_glDisablei (){
    return glDisablei_hook ;
}
void setHook_glDisablei ( glDisablei_hook_t hook ){
    glDisablei_hook = hook;
}
void glDisablei ( GLenum target_, GLuint index_ ){
    static PFNGLDISABLEIPROC F;
    if(!F)
        F = ( PFNGLDISABLEIPROC ) mygetprocaddr("glDisablei");
    if( glDisablei_hook )
        glDisablei_hook( target_, index_ );
    F(target_, index_);
}
static glDispatchCompute_hook_t glDispatchCompute_hook = 0;
glDispatchCompute_hook_t getHook_glDispatchCompute (){
    return glDispatchCompute_hook ;
}
void setHook_glDispatchCompute ( glDispatchCompute_hook_t hook ){
    glDispatchCompute_hook = hook;
}
void glDispatchCompute ( GLuint num_groups_x_, GLuint num_groups_y_, GLuint num_groups_z_ ){
    static PFNGLDISPATCHCOMPUTEPROC F;
    if(!F)
        F = ( PFNGLDISPATCHCOMPUTEPROC ) mygetprocaddr("glDispatchCompute");
    if( glDispatchCompute_hook )
        glDispatchCompute_hook( num_groups_x_, num_groups_y_, num_groups_z_ );
    F(num_groups_x_, num_groups_y_, num_groups_z_);
}
static glDispatchComputeIndirect_hook_t glDispatchComputeIndirect_hook = 0;
glDispatchComputeIndirect_hook_t getHook_glDispatchComputeIndirect (){
    return glDispatchComputeIndirect_hook ;
}
void setHook_glDispatchComputeIndirect ( glDispatchComputeIndirect_hook_t hook ){
    glDispatchComputeIndirect_hook = hook;
}
void glDispatchComputeIndirect ( GLintptr indirect_ ){
    static PFNGLDISPATCHCOMPUTEINDIRECTPROC F;
    if(!F)
        F = ( PFNGLDISPATCHCOMPUTEINDIRECTPROC ) mygetprocaddr("glDispatchComputeIndirect");
    if( glDispatchComputeIndirect_hook )
        glDispatchComputeIndirect_hook( indirect_ );
    F(indirect_);
}
static glDrawArrays_hook_t glDrawArrays_hook = 0;
glDrawArrays_hook_t getHook_glDrawArrays (){
    return glDrawArrays_hook ;
}
void setHook_glDrawArrays ( glDrawArrays_hook_t hook ){
    glDrawArrays_hook = hook;
}
void glDrawArrays ( GLenum mode_, GLint first_, GLsizei count_ ){
    static PFNGLDRAWARRAYSPROC F;
    if(!F)
        F = ( PFNGLDRAWARRAYSPROC ) mygetprocaddr("glDrawArrays");
    if( glDrawArrays_hook )
        glDrawArrays_hook( mode_, first_, count_ );
    F(mode_, first_, count_);
}
static glDrawArraysIndirect_hook_t glDrawArraysIndirect_hook = 0;
glDrawArraysIndirect_hook_t getHook_glDrawArraysIndirect (){
    return glDrawArraysIndirect_hook ;
}
void setHook_glDrawArraysIndirect ( glDrawArraysIndirect_hook_t hook ){
    glDrawArraysIndirect_hook = hook;
}
void glDrawArraysIndirect ( GLenum mode_, const void * indirect_ ){
    static PFNGLDRAWARRAYSINDIRECTPROC F;
    if(!F)
        F = ( PFNGLDRAWARRAYSINDIRECTPROC ) mygetprocaddr("glDrawArraysIndirect");
    if( glDrawArraysIndirect_hook )
        glDrawArraysIndirect_hook( mode_, indirect_ );
    F(mode_, indirect_);
}
static glDrawArraysInstanced_hook_t glDrawArraysInstanced_hook = 0;
glDrawArraysInstanced_hook_t getHook_glDrawArraysInstanced (){
    return glDrawArraysInstanced_hook ;
}
void setHook_glDrawArraysInstanced ( glDrawArraysInstanced_hook_t hook ){
    glDrawArraysInstanced_hook = hook;
}
void glDrawArraysInstanced ( GLenum mode_, GLint first_, GLsizei count_, GLsizei instancecount_ ){
    static PFNGLDRAWARRAYSINSTANCEDPROC F;
    if(!F)
        F = ( PFNGLDRAWARRAYSINSTANCEDPROC ) mygetprocaddr("glDrawArraysInstanced");
    if( glDrawArraysInstanced_hook )
        glDrawArraysInstanced_hook( mode_, first_, count_, instancecount_ );
    F(mode_, first_, count_, instancecount_);
}
static glDrawArraysInstancedBaseInstance_hook_t glDrawArraysInstancedBaseInstance_hook = 0;
glDrawArraysInstancedBaseInstance_hook_t getHook_glDrawArraysInstancedBaseInstance (){
    return glDrawArraysInstancedBaseInstance_hook ;
}
void setHook_glDrawArraysInstancedBaseInstance ( glDrawArraysInstancedBaseInstance_hook_t hook ){
    glDrawArraysInstancedBaseInstance_hook = hook;
}
void glDrawArraysInstancedBaseInstance ( GLenum mode_, GLint first_, GLsizei count_, GLsizei instancecount_, GLuint baseinstance_ ){
    static PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC F;
    if(!F)
        F = ( PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC ) mygetprocaddr("glDrawArraysInstancedBaseInstance");
    if( glDrawArraysInstancedBaseInstance_hook )
        glDrawArraysInstancedBaseInstance_hook( mode_, first_, count_, instancecount_, baseinstance_ );
    F(mode_, first_, count_, instancecount_, baseinstance_);
}
static glDrawBuffer_hook_t glDrawBuffer_hook = 0;
glDrawBuffer_hook_t getHook_glDrawBuffer (){
    return glDrawBuffer_hook ;
}
void setHook_glDrawBuffer ( glDrawBuffer_hook_t hook ){
    glDrawBuffer_hook = hook;
}
void glDrawBuffer ( GLenum buf_ ){
    static PFNGLDRAWBUFFERPROC F;
    if(!F)
        F = ( PFNGLDRAWBUFFERPROC ) mygetprocaddr("glDrawBuffer");
    if( glDrawBuffer_hook )
        glDrawBuffer_hook( buf_ );
    F(buf_);
}
static glDrawBuffers_hook_t glDrawBuffers_hook = 0;
glDrawBuffers_hook_t getHook_glDrawBuffers (){
    return glDrawBuffers_hook ;
}
void setHook_glDrawBuffers ( glDrawBuffers_hook_t hook ){
    glDrawBuffers_hook = hook;
}
void glDrawBuffers ( GLsizei n_, const GLenum * bufs_ ){
    static PFNGLDRAWBUFFERSPROC F;
    if(!F)
        F = ( PFNGLDRAWBUFFERSPROC ) mygetprocaddr("glDrawBuffers");
    if( glDrawBuffers_hook )
        glDrawBuffers_hook( n_, bufs_ );
    F(n_, bufs_);
}
static glDrawElements_hook_t glDrawElements_hook = 0;
glDrawElements_hook_t getHook_glDrawElements (){
    return glDrawElements_hook ;
}
void setHook_glDrawElements ( glDrawElements_hook_t hook ){
    glDrawElements_hook = hook;
}
void glDrawElements ( GLenum mode_, GLsizei count_, GLenum type_, const void * indices_ ){
    static PFNGLDRAWELEMENTSPROC F;
    if(!F)
        F = ( PFNGLDRAWELEMENTSPROC ) mygetprocaddr("glDrawElements");
    if( glDrawElements_hook )
        glDrawElements_hook( mode_, count_, type_, indices_ );
    F(mode_, count_, type_, indices_);
}
static glDrawElementsBaseVertex_hook_t glDrawElementsBaseVertex_hook = 0;
glDrawElementsBaseVertex_hook_t getHook_glDrawElementsBaseVertex (){
    return glDrawElementsBaseVertex_hook ;
}
void setHook_glDrawElementsBaseVertex ( glDrawElementsBaseVertex_hook_t hook ){
    glDrawElementsBaseVertex_hook = hook;
}
void glDrawElementsBaseVertex ( GLenum mode_, GLsizei count_, GLenum type_, const void * indices_, GLint basevertex_ ){
    static PFNGLDRAWELEMENTSBASEVERTEXPROC F;
    if(!F)
        F = ( PFNGLDRAWELEMENTSBASEVERTEXPROC ) mygetprocaddr("glDrawElementsBaseVertex");
    if( glDrawElementsBaseVertex_hook )
        glDrawElementsBaseVertex_hook( mode_, count_, type_, indices_, basevertex_ );
    F(mode_, count_, type_, indices_, basevertex_);
}
static glDrawElementsIndirect_hook_t glDrawElementsIndirect_hook = 0;
glDrawElementsIndirect_hook_t getHook_glDrawElementsIndirect (){
    return glDrawElementsIndirect_hook ;
}
void setHook_glDrawElementsIndirect ( glDrawElementsIndirect_hook_t hook ){
    glDrawElementsIndirect_hook = hook;
}
void glDrawElementsIndirect ( GLenum mode_, GLenum type_, const void * indirect_ ){
    static PFNGLDRAWELEMENTSINDIRECTPROC F;
    if(!F)
        F = ( PFNGLDRAWELEMENTSINDIRECTPROC ) mygetprocaddr("glDrawElementsIndirect");
    if( glDrawElementsIndirect_hook )
        glDrawElementsIndirect_hook( mode_, type_, indirect_ );
    F(mode_, type_, indirect_);
}
static glDrawElementsInstanced_hook_t glDrawElementsInstanced_hook = 0;
glDrawElementsInstanced_hook_t getHook_glDrawElementsInstanced (){
    return glDrawElementsInstanced_hook ;
}
void setHook_glDrawElementsInstanced ( glDrawElementsInstanced_hook_t hook ){
    glDrawElementsInstanced_hook = hook;
}
void glDrawElementsInstanced ( GLenum mode_, GLsizei count_, GLenum type_, const void * indices_, GLsizei instancecount_ ){
    static PFNGLDRAWELEMENTSINSTANCEDPROC F;
    if(!F)
        F = ( PFNGLDRAWELEMENTSINSTANCEDPROC ) mygetprocaddr("glDrawElementsInstanced");
    if( glDrawElementsInstanced_hook )
        glDrawElementsInstanced_hook( mode_, count_, type_, indices_, instancecount_ );
    F(mode_, count_, type_, indices_, instancecount_);
}
static glDrawElementsInstancedBaseInstance_hook_t glDrawElementsInstancedBaseInstance_hook = 0;
glDrawElementsInstancedBaseInstance_hook_t getHook_glDrawElementsInstancedBaseInstance (){
    return glDrawElementsInstancedBaseInstance_hook ;
}
void setHook_glDrawElementsInstancedBaseInstance ( glDrawElementsInstancedBaseInstance_hook_t hook ){
    glDrawElementsInstancedBaseInstance_hook = hook;
}
void glDrawElementsInstancedBaseInstance ( GLenum mode_, GLsizei count_, GLenum type_, const void * indices_, GLsizei instancecount_, GLuint baseinstance_ ){
    static PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC F;
    if(!F)
        F = ( PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC ) mygetprocaddr("glDrawElementsInstancedBaseInstance");
    if( glDrawElementsInstancedBaseInstance_hook )
        glDrawElementsInstancedBaseInstance_hook( mode_, count_, type_, indices_, instancecount_, baseinstance_ );
    F(mode_, count_, type_, indices_, instancecount_, baseinstance_);
}
static glDrawElementsInstancedBaseVertex_hook_t glDrawElementsInstancedBaseVertex_hook = 0;
glDrawElementsInstancedBaseVertex_hook_t getHook_glDrawElementsInstancedBaseVertex (){
    return glDrawElementsInstancedBaseVertex_hook ;
}
void setHook_glDrawElementsInstancedBaseVertex ( glDrawElementsInstancedBaseVertex_hook_t hook ){
    glDrawElementsInstancedBaseVertex_hook = hook;
}
void glDrawElementsInstancedBaseVertex ( GLenum mode_, GLsizei count_, GLenum type_, const void * indices_, GLsizei instancecount_, GLint basevertex_ ){
    static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC F;
    if(!F)
        F = ( PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC ) mygetprocaddr("glDrawElementsInstancedBaseVertex");
    if( glDrawElementsInstancedBaseVertex_hook )
        glDrawElementsInstancedBaseVertex_hook( mode_, count_, type_, indices_, instancecount_, basevertex_ );
    F(mode_, count_, type_, indices_, instancecount_, basevertex_);
}
static glDrawElementsInstancedBaseVertexBaseInstance_hook_t glDrawElementsInstancedBaseVertexBaseInstance_hook = 0;
glDrawElementsInstancedBaseVertexBaseInstance_hook_t getHook_glDrawElementsInstancedBaseVertexBaseInstance (){
    return glDrawElementsInstancedBaseVertexBaseInstance_hook ;
}
void setHook_glDrawElementsInstancedBaseVertexBaseInstance ( glDrawElementsInstancedBaseVertexBaseInstance_hook_t hook ){
    glDrawElementsInstancedBaseVertexBaseInstance_hook = hook;
}
void glDrawElementsInstancedBaseVertexBaseInstance ( GLenum mode_, GLsizei count_, GLenum type_, const void * indices_, GLsizei instancecount_, GLint basevertex_, GLuint baseinstance_ ){
    static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC F;
    if(!F)
        F = ( PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC ) mygetprocaddr("glDrawElementsInstancedBaseVertexBaseInstance");
    if( glDrawElementsInstancedBaseVertexBaseInstance_hook )
        glDrawElementsInstancedBaseVertexBaseInstance_hook( mode_, count_, type_, indices_, instancecount_, basevertex_, baseinstance_ );
    F(mode_, count_, type_, indices_, instancecount_, basevertex_, baseinstance_);
}
static glDrawRangeElements_hook_t glDrawRangeElements_hook = 0;
glDrawRangeElements_hook_t getHook_glDrawRangeElements (){
    return glDrawRangeElements_hook ;
}
void setHook_glDrawRangeElements ( glDrawRangeElements_hook_t hook ){
    glDrawRangeElements_hook = hook;
}
void glDrawRangeElements ( GLenum mode_, GLuint start_, GLuint end_, GLsizei count_, GLenum type_, const void * indices_ ){
    static PFNGLDRAWRANGEELEMENTSPROC F;
    if(!F)
        F = ( PFNGLDRAWRANGEELEMENTSPROC ) mygetprocaddr("glDrawRangeElements");
    if( glDrawRangeElements_hook )
        glDrawRangeElements_hook( mode_, start_, end_, count_, type_, indices_ );
    F(mode_, start_, end_, count_, type_, indices_);
}
static glDrawRangeElementsBaseVertex_hook_t glDrawRangeElementsBaseVertex_hook = 0;
glDrawRangeElementsBaseVertex_hook_t getHook_glDrawRangeElementsBaseVertex (){
    return glDrawRangeElementsBaseVertex_hook ;
}
void setHook_glDrawRangeElementsBaseVertex ( glDrawRangeElementsBaseVertex_hook_t hook ){
    glDrawRangeElementsBaseVertex_hook = hook;
}
void glDrawRangeElementsBaseVertex ( GLenum mode_, GLuint start_, GLuint end_, GLsizei count_, GLenum type_, const void * indices_, GLint basevertex_ ){
    static PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC F;
    if(!F)
        F = ( PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC ) mygetprocaddr("glDrawRangeElementsBaseVertex");
    if( glDrawRangeElementsBaseVertex_hook )
        glDrawRangeElementsBaseVertex_hook( mode_, start_, end_, count_, type_, indices_, basevertex_ );
    F(mode_, start_, end_, count_, type_, indices_, basevertex_);
}
static glDrawTransformFeedback_hook_t glDrawTransformFeedback_hook = 0;
glDrawTransformFeedback_hook_t getHook_glDrawTransformFeedback (){
    return glDrawTransformFeedback_hook ;
}
void setHook_glDrawTransformFeedback ( glDrawTransformFeedback_hook_t hook ){
    glDrawTransformFeedback_hook = hook;
}
void glDrawTransformFeedback ( GLenum mode_, GLuint id_ ){
    static PFNGLDRAWTRANSFORMFEEDBACKPROC F;
    if(!F)
        F = ( PFNGLDRAWTRANSFORMFEEDBACKPROC ) mygetprocaddr("glDrawTransformFeedback");
    if( glDrawTransformFeedback_hook )
        glDrawTransformFeedback_hook( mode_, id_ );
    F(mode_, id_);
}
static glDrawTransformFeedbackInstanced_hook_t glDrawTransformFeedbackInstanced_hook = 0;
glDrawTransformFeedbackInstanced_hook_t getHook_glDrawTransformFeedbackInstanced (){
    return glDrawTransformFeedbackInstanced_hook ;
}
void setHook_glDrawTransformFeedbackInstanced ( glDrawTransformFeedbackInstanced_hook_t hook ){
    glDrawTransformFeedbackInstanced_hook = hook;
}
void glDrawTransformFeedbackInstanced ( GLenum mode_, GLuint id_, GLsizei instancecount_ ){
    static PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC F;
    if(!F)
        F = ( PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC ) mygetprocaddr("glDrawTransformFeedbackInstanced");
    if( glDrawTransformFeedbackInstanced_hook )
        glDrawTransformFeedbackInstanced_hook( mode_, id_, instancecount_ );
    F(mode_, id_, instancecount_);
}
static glDrawTransformFeedbackStream_hook_t glDrawTransformFeedbackStream_hook = 0;
glDrawTransformFeedbackStream_hook_t getHook_glDrawTransformFeedbackStream (){
    return glDrawTransformFeedbackStream_hook ;
}
void setHook_glDrawTransformFeedbackStream ( glDrawTransformFeedbackStream_hook_t hook ){
    glDrawTransformFeedbackStream_hook = hook;
}
void glDrawTransformFeedbackStream ( GLenum mode_, GLuint id_, GLuint stream_ ){
    static PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC F;
    if(!F)
        F = ( PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC ) mygetprocaddr("glDrawTransformFeedbackStream");
    if( glDrawTransformFeedbackStream_hook )
        glDrawTransformFeedbackStream_hook( mode_, id_, stream_ );
    F(mode_, id_, stream_);
}
static glDrawTransformFeedbackStreamInstanced_hook_t glDrawTransformFeedbackStreamInstanced_hook = 0;
glDrawTransformFeedbackStreamInstanced_hook_t getHook_glDrawTransformFeedbackStreamInstanced (){
    return glDrawTransformFeedbackStreamInstanced_hook ;
}
void setHook_glDrawTransformFeedbackStreamInstanced ( glDrawTransformFeedbackStreamInstanced_hook_t hook ){
    glDrawTransformFeedbackStreamInstanced_hook = hook;
}
void glDrawTransformFeedbackStreamInstanced ( GLenum mode_, GLuint id_, GLuint stream_, GLsizei instancecount_ ){
    static PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC F;
    if(!F)
        F = ( PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC ) mygetprocaddr("glDrawTransformFeedbackStreamInstanced");
    if( glDrawTransformFeedbackStreamInstanced_hook )
        glDrawTransformFeedbackStreamInstanced_hook( mode_, id_, stream_, instancecount_ );
    F(mode_, id_, stream_, instancecount_);
}
static glEnable_hook_t glEnable_hook = 0;
glEnable_hook_t getHook_glEnable (){
    return glEnable_hook ;
}
void setHook_glEnable ( glEnable_hook_t hook ){
    glEnable_hook = hook;
}
void glEnable ( GLenum cap_ ){
    static PFNGLENABLEPROC F;
    if(!F)
        F = ( PFNGLENABLEPROC ) mygetprocaddr("glEnable");
    if( glEnable_hook )
        glEnable_hook( cap_ );
    F(cap_);
}
static glEnableVertexArrayAttrib_hook_t glEnableVertexArrayAttrib_hook = 0;
glEnableVertexArrayAttrib_hook_t getHook_glEnableVertexArrayAttrib (){
    return glEnableVertexArrayAttrib_hook ;
}
void setHook_glEnableVertexArrayAttrib ( glEnableVertexArrayAttrib_hook_t hook ){
    glEnableVertexArrayAttrib_hook = hook;
}
void glEnableVertexArrayAttrib ( GLuint vaobj_, GLuint index_ ){
    static PFNGLENABLEVERTEXARRAYATTRIBPROC F;
    if(!F)
        F = ( PFNGLENABLEVERTEXARRAYATTRIBPROC ) mygetprocaddr("glEnableVertexArrayAttrib");
    if( glEnableVertexArrayAttrib_hook )
        glEnableVertexArrayAttrib_hook( vaobj_, index_ );
    F(vaobj_, index_);
}
static glEnableVertexAttribArray_hook_t glEnableVertexAttribArray_hook = 0;
glEnableVertexAttribArray_hook_t getHook_glEnableVertexAttribArray (){
    return glEnableVertexAttribArray_hook ;
}
void setHook_glEnableVertexAttribArray ( glEnableVertexAttribArray_hook_t hook ){
    glEnableVertexAttribArray_hook = hook;
}
void glEnableVertexAttribArray ( GLuint index_ ){
    static PFNGLENABLEVERTEXATTRIBARRAYPROC F;
    if(!F)
        F = ( PFNGLENABLEVERTEXATTRIBARRAYPROC ) mygetprocaddr("glEnableVertexAttribArray");
    if( glEnableVertexAttribArray_hook )
        glEnableVertexAttribArray_hook( index_ );
    F(index_);
}
static glEnablei_hook_t glEnablei_hook = 0;
glEnablei_hook_t getHook_glEnablei (){
    return glEnablei_hook ;
}
void setHook_glEnablei ( glEnablei_hook_t hook ){
    glEnablei_hook = hook;
}
void glEnablei ( GLenum target_, GLuint index_ ){
    static PFNGLENABLEIPROC F;
    if(!F)
        F = ( PFNGLENABLEIPROC ) mygetprocaddr("glEnablei");
    if( glEnablei_hook )
        glEnablei_hook( target_, index_ );
    F(target_, index_);
}
static glEndConditionalRender_hook_t glEndConditionalRender_hook = 0;
glEndConditionalRender_hook_t getHook_glEndConditionalRender (){
    return glEndConditionalRender_hook ;
}
void setHook_glEndConditionalRender ( glEndConditionalRender_hook_t hook ){
    glEndConditionalRender_hook = hook;
}
void glEndConditionalRender (  ){
    static PFNGLENDCONDITIONALRENDERPROC F;
    if(!F)
        F = ( PFNGLENDCONDITIONALRENDERPROC ) mygetprocaddr("glEndConditionalRender");
    if( glEndConditionalRender_hook )
        glEndConditionalRender_hook(  );
    F();
}
static glEndQuery_hook_t glEndQuery_hook = 0;
glEndQuery_hook_t getHook_glEndQuery (){
    return glEndQuery_hook ;
}
void setHook_glEndQuery ( glEndQuery_hook_t hook ){
    glEndQuery_hook = hook;
}
void glEndQuery ( GLenum target_ ){
    static PFNGLENDQUERYPROC F;
    if(!F)
        F = ( PFNGLENDQUERYPROC ) mygetprocaddr("glEndQuery");
    if( glEndQuery_hook )
        glEndQuery_hook( target_ );
    F(target_);
}
static glEndQueryIndexed_hook_t glEndQueryIndexed_hook = 0;
glEndQueryIndexed_hook_t getHook_glEndQueryIndexed (){
    return glEndQueryIndexed_hook ;
}
void setHook_glEndQueryIndexed ( glEndQueryIndexed_hook_t hook ){
    glEndQueryIndexed_hook = hook;
}
void glEndQueryIndexed ( GLenum target_, GLuint index_ ){
    static PFNGLENDQUERYINDEXEDPROC F;
    if(!F)
        F = ( PFNGLENDQUERYINDEXEDPROC ) mygetprocaddr("glEndQueryIndexed");
    if( glEndQueryIndexed_hook )
        glEndQueryIndexed_hook( target_, index_ );
    F(target_, index_);
}
static glEndTransformFeedback_hook_t glEndTransformFeedback_hook = 0;
glEndTransformFeedback_hook_t getHook_glEndTransformFeedback (){
    return glEndTransformFeedback_hook ;
}
void setHook_glEndTransformFeedback ( glEndTransformFeedback_hook_t hook ){
    glEndTransformFeedback_hook = hook;
}
void glEndTransformFeedback (  ){
    static PFNGLENDTRANSFORMFEEDBACKPROC F;
    if(!F)
        F = ( PFNGLENDTRANSFORMFEEDBACKPROC ) mygetprocaddr("glEndTransformFeedback");
    if( glEndTransformFeedback_hook )
        glEndTransformFeedback_hook(  );
    F();
}
static glFenceSync_hook_t glFenceSync_hook = 0;
glFenceSync_hook_t getHook_glFenceSync (){
    return glFenceSync_hook ;
}
void setHook_glFenceSync ( glFenceSync_hook_t hook ){
    glFenceSync_hook = hook;
}
GLsync glFenceSync ( GLenum condition_, GLbitfield flags_ ){
    static PFNGLFENCESYNCPROC F;
    if(!F)
        F = ( PFNGLFENCESYNCPROC ) mygetprocaddr("glFenceSync");
    if( glFenceSync_hook )
        glFenceSync_hook( condition_, flags_ );
    GLsync retval = F(condition_, flags_);
    return retval;
}
static glFinish_hook_t glFinish_hook = 0;
glFinish_hook_t getHook_glFinish (){
    return glFinish_hook ;
}
void setHook_glFinish ( glFinish_hook_t hook ){
    glFinish_hook = hook;
}
void glFinish (  ){
    static PFNGLFINISHPROC F;
    if(!F)
        F = ( PFNGLFINISHPROC ) mygetprocaddr("glFinish");
    if( glFinish_hook )
        glFinish_hook(  );
    F();
}
static glFlush_hook_t glFlush_hook = 0;
glFlush_hook_t getHook_glFlush (){
    return glFlush_hook ;
}
void setHook_glFlush ( glFlush_hook_t hook ){
    glFlush_hook = hook;
}
void glFlush (  ){
    static PFNGLFLUSHPROC F;
    if(!F)
        F = ( PFNGLFLUSHPROC ) mygetprocaddr("glFlush");
    if( glFlush_hook )
        glFlush_hook(  );
    F();
}
static glFlushMappedBufferRange_hook_t glFlushMappedBufferRange_hook = 0;
glFlushMappedBufferRange_hook_t getHook_glFlushMappedBufferRange (){
    return glFlushMappedBufferRange_hook ;
}
void setHook_glFlushMappedBufferRange ( glFlushMappedBufferRange_hook_t hook ){
    glFlushMappedBufferRange_hook = hook;
}
void glFlushMappedBufferRange ( GLenum target_, GLintptr offset_, GLsizeiptr length_ ){
    static PFNGLFLUSHMAPPEDBUFFERRANGEPROC F;
    if(!F)
        F = ( PFNGLFLUSHMAPPEDBUFFERRANGEPROC ) mygetprocaddr("glFlushMappedBufferRange");
    if( glFlushMappedBufferRange_hook )
        glFlushMappedBufferRange_hook( target_, offset_, length_ );
    F(target_, offset_, length_);
}
static glFlushMappedNamedBufferRange_hook_t glFlushMappedNamedBufferRange_hook = 0;
glFlushMappedNamedBufferRange_hook_t getHook_glFlushMappedNamedBufferRange (){
    return glFlushMappedNamedBufferRange_hook ;
}
void setHook_glFlushMappedNamedBufferRange ( glFlushMappedNamedBufferRange_hook_t hook ){
    glFlushMappedNamedBufferRange_hook = hook;
}
void glFlushMappedNamedBufferRange ( GLuint buffer_, GLintptr offset_, GLsizeiptr length_ ){
    static PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC F;
    if(!F)
        F = ( PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC ) mygetprocaddr("glFlushMappedNamedBufferRange");
    if( glFlushMappedNamedBufferRange_hook )
        glFlushMappedNamedBufferRange_hook( buffer_, offset_, length_ );
    F(buffer_, offset_, length_);
}
static glFramebufferParameteri_hook_t glFramebufferParameteri_hook = 0;
glFramebufferParameteri_hook_t getHook_glFramebufferParameteri (){
    return glFramebufferParameteri_hook ;
}
void setHook_glFramebufferParameteri ( glFramebufferParameteri_hook_t hook ){
    glFramebufferParameteri_hook = hook;
}
void glFramebufferParameteri ( GLenum target_, GLenum pname_, GLint param_ ){
    static PFNGLFRAMEBUFFERPARAMETERIPROC F;
    if(!F)
        F = ( PFNGLFRAMEBUFFERPARAMETERIPROC ) mygetprocaddr("glFramebufferParameteri");
    if( glFramebufferParameteri_hook )
        glFramebufferParameteri_hook( target_, pname_, param_ );
    F(target_, pname_, param_);
}
static glFramebufferRenderbuffer_hook_t glFramebufferRenderbuffer_hook = 0;
glFramebufferRenderbuffer_hook_t getHook_glFramebufferRenderbuffer (){
    return glFramebufferRenderbuffer_hook ;
}
void setHook_glFramebufferRenderbuffer ( glFramebufferRenderbuffer_hook_t hook ){
    glFramebufferRenderbuffer_hook = hook;
}
void glFramebufferRenderbuffer ( GLenum target_, GLenum attachment_, GLenum renderbuffertarget_, GLuint renderbuffer_ ){
    static PFNGLFRAMEBUFFERRENDERBUFFERPROC F;
    if(!F)
        F = ( PFNGLFRAMEBUFFERRENDERBUFFERPROC ) mygetprocaddr("glFramebufferRenderbuffer");
    if( glFramebufferRenderbuffer_hook )
        glFramebufferRenderbuffer_hook( target_, attachment_, renderbuffertarget_, renderbuffer_ );
    F(target_, attachment_, renderbuffertarget_, renderbuffer_);
}
static glFramebufferTexture_hook_t glFramebufferTexture_hook = 0;
glFramebufferTexture_hook_t getHook_glFramebufferTexture (){
    return glFramebufferTexture_hook ;
}
void setHook_glFramebufferTexture ( glFramebufferTexture_hook_t hook ){
    glFramebufferTexture_hook = hook;
}
void glFramebufferTexture ( GLenum target_, GLenum attachment_, GLuint texture_, GLint level_ ){
    static PFNGLFRAMEBUFFERTEXTUREPROC F;
    if(!F)
        F = ( PFNGLFRAMEBUFFERTEXTUREPROC ) mygetprocaddr("glFramebufferTexture");
    if( glFramebufferTexture_hook )
        glFramebufferTexture_hook( target_, attachment_, texture_, level_ );
    F(target_, attachment_, texture_, level_);
}
static glFramebufferTexture1D_hook_t glFramebufferTexture1D_hook = 0;
glFramebufferTexture1D_hook_t getHook_glFramebufferTexture1D (){
    return glFramebufferTexture1D_hook ;
}
void setHook_glFramebufferTexture1D ( glFramebufferTexture1D_hook_t hook ){
    glFramebufferTexture1D_hook = hook;
}
void glFramebufferTexture1D ( GLenum target_, GLenum attachment_, GLenum textarget_, GLuint texture_, GLint level_ ){
    static PFNGLFRAMEBUFFERTEXTURE1DPROC F;
    if(!F)
        F = ( PFNGLFRAMEBUFFERTEXTURE1DPROC ) mygetprocaddr("glFramebufferTexture1D");
    if( glFramebufferTexture1D_hook )
        glFramebufferTexture1D_hook( target_, attachment_, textarget_, texture_, level_ );
    F(target_, attachment_, textarget_, texture_, level_);
}
static glFramebufferTexture2D_hook_t glFramebufferTexture2D_hook = 0;
glFramebufferTexture2D_hook_t getHook_glFramebufferTexture2D (){
    return glFramebufferTexture2D_hook ;
}
void setHook_glFramebufferTexture2D ( glFramebufferTexture2D_hook_t hook ){
    glFramebufferTexture2D_hook = hook;
}
void glFramebufferTexture2D ( GLenum target_, GLenum attachment_, GLenum textarget_, GLuint texture_, GLint level_ ){
    static PFNGLFRAMEBUFFERTEXTURE2DPROC F;
    if(!F)
        F = ( PFNGLFRAMEBUFFERTEXTURE2DPROC ) mygetprocaddr("glFramebufferTexture2D");
    if( glFramebufferTexture2D_hook )
        glFramebufferTexture2D_hook( target_, attachment_, textarget_, texture_, level_ );
    F(target_, attachment_, textarget_, texture_, level_);
}
static glFramebufferTexture3D_hook_t glFramebufferTexture3D_hook = 0;
glFramebufferTexture3D_hook_t getHook_glFramebufferTexture3D (){
    return glFramebufferTexture3D_hook ;
}
void setHook_glFramebufferTexture3D ( glFramebufferTexture3D_hook_t hook ){
    glFramebufferTexture3D_hook = hook;
}
void glFramebufferTexture3D ( GLenum target_, GLenum attachment_, GLenum textarget_, GLuint texture_, GLint level_, GLint zoffset_ ){
    static PFNGLFRAMEBUFFERTEXTURE3DPROC F;
    if(!F)
        F = ( PFNGLFRAMEBUFFERTEXTURE3DPROC ) mygetprocaddr("glFramebufferTexture3D");
    if( glFramebufferTexture3D_hook )
        glFramebufferTexture3D_hook( target_, attachment_, textarget_, texture_, level_, zoffset_ );
    F(target_, attachment_, textarget_, texture_, level_, zoffset_);
}
static glFramebufferTextureLayer_hook_t glFramebufferTextureLayer_hook = 0;
glFramebufferTextureLayer_hook_t getHook_glFramebufferTextureLayer (){
    return glFramebufferTextureLayer_hook ;
}
void setHook_glFramebufferTextureLayer ( glFramebufferTextureLayer_hook_t hook ){
    glFramebufferTextureLayer_hook = hook;
}
void glFramebufferTextureLayer ( GLenum target_, GLenum attachment_, GLuint texture_, GLint level_, GLint layer_ ){
    static PFNGLFRAMEBUFFERTEXTURELAYERPROC F;
    if(!F)
        F = ( PFNGLFRAMEBUFFERTEXTURELAYERPROC ) mygetprocaddr("glFramebufferTextureLayer");
    if( glFramebufferTextureLayer_hook )
        glFramebufferTextureLayer_hook( target_, attachment_, texture_, level_, layer_ );
    F(target_, attachment_, texture_, level_, layer_);
}
static glFrontFace_hook_t glFrontFace_hook = 0;
glFrontFace_hook_t getHook_glFrontFace (){
    return glFrontFace_hook ;
}
void setHook_glFrontFace ( glFrontFace_hook_t hook ){
    glFrontFace_hook = hook;
}
void glFrontFace ( GLenum mode_ ){
    static PFNGLFRONTFACEPROC F;
    if(!F)
        F = ( PFNGLFRONTFACEPROC ) mygetprocaddr("glFrontFace");
    if( glFrontFace_hook )
        glFrontFace_hook( mode_ );
    F(mode_);
}
static glGenBuffers_hook_t glGenBuffers_hook = 0;
glGenBuffers_hook_t getHook_glGenBuffers (){
    return glGenBuffers_hook ;
}
void setHook_glGenBuffers ( glGenBuffers_hook_t hook ){
    glGenBuffers_hook = hook;
}
void glGenBuffers ( GLsizei n_, GLuint * buffers_ ){
    static PFNGLGENBUFFERSPROC F;
    if(!F)
        F = ( PFNGLGENBUFFERSPROC ) mygetprocaddr("glGenBuffers");
    if( glGenBuffers_hook )
        glGenBuffers_hook( n_, buffers_ );
    F(n_, buffers_);
}
static glGenFramebuffers_hook_t glGenFramebuffers_hook = 0;
glGenFramebuffers_hook_t getHook_glGenFramebuffers (){
    return glGenFramebuffers_hook ;
}
void setHook_glGenFramebuffers ( glGenFramebuffers_hook_t hook ){
    glGenFramebuffers_hook = hook;
}
void glGenFramebuffers ( GLsizei n_, GLuint * framebuffers_ ){
    static PFNGLGENFRAMEBUFFERSPROC F;
    if(!F)
        F = ( PFNGLGENFRAMEBUFFERSPROC ) mygetprocaddr("glGenFramebuffers");
    if( glGenFramebuffers_hook )
        glGenFramebuffers_hook( n_, framebuffers_ );
    F(n_, framebuffers_);
}
static glGenProgramPipelines_hook_t glGenProgramPipelines_hook = 0;
glGenProgramPipelines_hook_t getHook_glGenProgramPipelines (){
    return glGenProgramPipelines_hook ;
}
void setHook_glGenProgramPipelines ( glGenProgramPipelines_hook_t hook ){
    glGenProgramPipelines_hook = hook;
}
void glGenProgramPipelines ( GLsizei n_, GLuint * pipelines_ ){
    static PFNGLGENPROGRAMPIPELINESPROC F;
    if(!F)
        F = ( PFNGLGENPROGRAMPIPELINESPROC ) mygetprocaddr("glGenProgramPipelines");
    if( glGenProgramPipelines_hook )
        glGenProgramPipelines_hook( n_, pipelines_ );
    F(n_, pipelines_);
}
static glGenQueries_hook_t glGenQueries_hook = 0;
glGenQueries_hook_t getHook_glGenQueries (){
    return glGenQueries_hook ;
}
void setHook_glGenQueries ( glGenQueries_hook_t hook ){
    glGenQueries_hook = hook;
}
void glGenQueries ( GLsizei n_, GLuint * ids_ ){
    static PFNGLGENQUERIESPROC F;
    if(!F)
        F = ( PFNGLGENQUERIESPROC ) mygetprocaddr("glGenQueries");
    if( glGenQueries_hook )
        glGenQueries_hook( n_, ids_ );
    F(n_, ids_);
}
static glGenRenderbuffers_hook_t glGenRenderbuffers_hook = 0;
glGenRenderbuffers_hook_t getHook_glGenRenderbuffers (){
    return glGenRenderbuffers_hook ;
}
void setHook_glGenRenderbuffers ( glGenRenderbuffers_hook_t hook ){
    glGenRenderbuffers_hook = hook;
}
void glGenRenderbuffers ( GLsizei n_, GLuint * renderbuffers_ ){
    static PFNGLGENRENDERBUFFERSPROC F;
    if(!F)
        F = ( PFNGLGENRENDERBUFFERSPROC ) mygetprocaddr("glGenRenderbuffers");
    if( glGenRenderbuffers_hook )
        glGenRenderbuffers_hook( n_, renderbuffers_ );
    F(n_, renderbuffers_);
}
static glGenSamplers_hook_t glGenSamplers_hook = 0;
glGenSamplers_hook_t getHook_glGenSamplers (){
    return glGenSamplers_hook ;
}
void setHook_glGenSamplers ( glGenSamplers_hook_t hook ){
    glGenSamplers_hook = hook;
}
void glGenSamplers ( GLsizei count_, GLuint * samplers_ ){
    static PFNGLGENSAMPLERSPROC F;
    if(!F)
        F = ( PFNGLGENSAMPLERSPROC ) mygetprocaddr("glGenSamplers");
    if( glGenSamplers_hook )
        glGenSamplers_hook( count_, samplers_ );
    F(count_, samplers_);
}
static glGenTextures_hook_t glGenTextures_hook = 0;
glGenTextures_hook_t getHook_glGenTextures (){
    return glGenTextures_hook ;
}
void setHook_glGenTextures ( glGenTextures_hook_t hook ){
    glGenTextures_hook = hook;
}
void glGenTextures ( GLsizei n_, GLuint * textures_ ){
    static PFNGLGENTEXTURESPROC F;
    if(!F)
        F = ( PFNGLGENTEXTURESPROC ) mygetprocaddr("glGenTextures");
    if( glGenTextures_hook )
        glGenTextures_hook( n_, textures_ );
    F(n_, textures_);
}
static glGenTransformFeedbacks_hook_t glGenTransformFeedbacks_hook = 0;
glGenTransformFeedbacks_hook_t getHook_glGenTransformFeedbacks (){
    return glGenTransformFeedbacks_hook ;
}
void setHook_glGenTransformFeedbacks ( glGenTransformFeedbacks_hook_t hook ){
    glGenTransformFeedbacks_hook = hook;
}
void glGenTransformFeedbacks ( GLsizei n_, GLuint * ids_ ){
    static PFNGLGENTRANSFORMFEEDBACKSPROC F;
    if(!F)
        F = ( PFNGLGENTRANSFORMFEEDBACKSPROC ) mygetprocaddr("glGenTransformFeedbacks");
    if( glGenTransformFeedbacks_hook )
        glGenTransformFeedbacks_hook( n_, ids_ );
    F(n_, ids_);
}
static glGenVertexArrays_hook_t glGenVertexArrays_hook = 0;
glGenVertexArrays_hook_t getHook_glGenVertexArrays (){
    return glGenVertexArrays_hook ;
}
void setHook_glGenVertexArrays ( glGenVertexArrays_hook_t hook ){
    glGenVertexArrays_hook = hook;
}
void glGenVertexArrays ( GLsizei n_, GLuint * arrays_ ){
    static PFNGLGENVERTEXARRAYSPROC F;
    if(!F)
        F = ( PFNGLGENVERTEXARRAYSPROC ) mygetprocaddr("glGenVertexArrays");
    if( glGenVertexArrays_hook )
        glGenVertexArrays_hook( n_, arrays_ );
    F(n_, arrays_);
}
static glGenerateMipmap_hook_t glGenerateMipmap_hook = 0;
glGenerateMipmap_hook_t getHook_glGenerateMipmap (){
    return glGenerateMipmap_hook ;
}
void setHook_glGenerateMipmap ( glGenerateMipmap_hook_t hook ){
    glGenerateMipmap_hook = hook;
}
void glGenerateMipmap ( GLenum target_ ){
    static PFNGLGENERATEMIPMAPPROC F;
    if(!F)
        F = ( PFNGLGENERATEMIPMAPPROC ) mygetprocaddr("glGenerateMipmap");
    if( glGenerateMipmap_hook )
        glGenerateMipmap_hook( target_ );
    F(target_);
}
static glGenerateTextureMipmap_hook_t glGenerateTextureMipmap_hook = 0;
glGenerateTextureMipmap_hook_t getHook_glGenerateTextureMipmap (){
    return glGenerateTextureMipmap_hook ;
}
void setHook_glGenerateTextureMipmap ( glGenerateTextureMipmap_hook_t hook ){
    glGenerateTextureMipmap_hook = hook;
}
void glGenerateTextureMipmap ( GLuint texture_ ){
    static PFNGLGENERATETEXTUREMIPMAPPROC F;
    if(!F)
        F = ( PFNGLGENERATETEXTUREMIPMAPPROC ) mygetprocaddr("glGenerateTextureMipmap");
    if( glGenerateTextureMipmap_hook )
        glGenerateTextureMipmap_hook( texture_ );
    F(texture_);
}
static glGetActiveAtomicCounterBufferiv_hook_t glGetActiveAtomicCounterBufferiv_hook = 0;
glGetActiveAtomicCounterBufferiv_hook_t getHook_glGetActiveAtomicCounterBufferiv (){
    return glGetActiveAtomicCounterBufferiv_hook ;
}
void setHook_glGetActiveAtomicCounterBufferiv ( glGetActiveAtomicCounterBufferiv_hook_t hook ){
    glGetActiveAtomicCounterBufferiv_hook = hook;
}
void glGetActiveAtomicCounterBufferiv ( GLuint program_, GLuint bufferIndex_, GLenum pname_, GLint * params_ ){
    static PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC F;
    if(!F)
        F = ( PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC ) mygetprocaddr("glGetActiveAtomicCounterBufferiv");
    if( glGetActiveAtomicCounterBufferiv_hook )
        glGetActiveAtomicCounterBufferiv_hook( program_, bufferIndex_, pname_, params_ );
    F(program_, bufferIndex_, pname_, params_);
}
static glGetActiveAttrib_hook_t glGetActiveAttrib_hook = 0;
glGetActiveAttrib_hook_t getHook_glGetActiveAttrib (){
    return glGetActiveAttrib_hook ;
}
void setHook_glGetActiveAttrib ( glGetActiveAttrib_hook_t hook ){
    glGetActiveAttrib_hook = hook;
}
void glGetActiveAttrib ( GLuint program_, GLuint index_, GLsizei bufSize_, GLsizei * length_, GLint * size_, GLenum * type_, GLchar * name_ ){
    static PFNGLGETACTIVEATTRIBPROC F;
    if(!F)
        F = ( PFNGLGETACTIVEATTRIBPROC ) mygetprocaddr("glGetActiveAttrib");
    if( glGetActiveAttrib_hook )
        glGetActiveAttrib_hook( program_, index_, bufSize_, length_, size_, type_, name_ );
    F(program_, index_, bufSize_, length_, size_, type_, name_);
}
static glGetActiveSubroutineName_hook_t glGetActiveSubroutineName_hook = 0;
glGetActiveSubroutineName_hook_t getHook_glGetActiveSubroutineName (){
    return glGetActiveSubroutineName_hook ;
}
void setHook_glGetActiveSubroutineName ( glGetActiveSubroutineName_hook_t hook ){
    glGetActiveSubroutineName_hook = hook;
}
void glGetActiveSubroutineName ( GLuint program_, GLenum shadertype_, GLuint index_, GLsizei bufsize_, GLsizei * length_, GLchar * name_ ){
    static PFNGLGETACTIVESUBROUTINENAMEPROC F;
    if(!F)
        F = ( PFNGLGETACTIVESUBROUTINENAMEPROC ) mygetprocaddr("glGetActiveSubroutineName");
    if( glGetActiveSubroutineName_hook )
        glGetActiveSubroutineName_hook( program_, shadertype_, index_, bufsize_, length_, name_ );
    F(program_, shadertype_, index_, bufsize_, length_, name_);
}
static glGetActiveSubroutineUniformName_hook_t glGetActiveSubroutineUniformName_hook = 0;
glGetActiveSubroutineUniformName_hook_t getHook_glGetActiveSubroutineUniformName (){
    return glGetActiveSubroutineUniformName_hook ;
}
void setHook_glGetActiveSubroutineUniformName ( glGetActiveSubroutineUniformName_hook_t hook ){
    glGetActiveSubroutineUniformName_hook = hook;
}
void glGetActiveSubroutineUniformName ( GLuint program_, GLenum shadertype_, GLuint index_, GLsizei bufsize_, GLsizei * length_, GLchar * name_ ){
    static PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC F;
    if(!F)
        F = ( PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC ) mygetprocaddr("glGetActiveSubroutineUniformName");
    if( glGetActiveSubroutineUniformName_hook )
        glGetActiveSubroutineUniformName_hook( program_, shadertype_, index_, bufsize_, length_, name_ );
    F(program_, shadertype_, index_, bufsize_, length_, name_);
}
static glGetActiveSubroutineUniformiv_hook_t glGetActiveSubroutineUniformiv_hook = 0;
glGetActiveSubroutineUniformiv_hook_t getHook_glGetActiveSubroutineUniformiv (){
    return glGetActiveSubroutineUniformiv_hook ;
}
void setHook_glGetActiveSubroutineUniformiv ( glGetActiveSubroutineUniformiv_hook_t hook ){
    glGetActiveSubroutineUniformiv_hook = hook;
}
void glGetActiveSubroutineUniformiv ( GLuint program_, GLenum shadertype_, GLuint index_, GLenum pname_, GLint * values_ ){
    static PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC F;
    if(!F)
        F = ( PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC ) mygetprocaddr("glGetActiveSubroutineUniformiv");
    if( glGetActiveSubroutineUniformiv_hook )
        glGetActiveSubroutineUniformiv_hook( program_, shadertype_, index_, pname_, values_ );
    F(program_, shadertype_, index_, pname_, values_);
}
static glGetActiveUniform_hook_t glGetActiveUniform_hook = 0;
glGetActiveUniform_hook_t getHook_glGetActiveUniform (){
    return glGetActiveUniform_hook ;
}
void setHook_glGetActiveUniform ( glGetActiveUniform_hook_t hook ){
    glGetActiveUniform_hook = hook;
}
void glGetActiveUniform ( GLuint program_, GLuint index_, GLsizei bufSize_, GLsizei * length_, GLint * size_, GLenum * type_, GLchar * name_ ){
    static PFNGLGETACTIVEUNIFORMPROC F;
    if(!F)
        F = ( PFNGLGETACTIVEUNIFORMPROC ) mygetprocaddr("glGetActiveUniform");
    if( glGetActiveUniform_hook )
        glGetActiveUniform_hook( program_, index_, bufSize_, length_, size_, type_, name_ );
    F(program_, index_, bufSize_, length_, size_, type_, name_);
}
static glGetActiveUniformBlockName_hook_t glGetActiveUniformBlockName_hook = 0;
glGetActiveUniformBlockName_hook_t getHook_glGetActiveUniformBlockName (){
    return glGetActiveUniformBlockName_hook ;
}
void setHook_glGetActiveUniformBlockName ( glGetActiveUniformBlockName_hook_t hook ){
    glGetActiveUniformBlockName_hook = hook;
}
void glGetActiveUniformBlockName ( GLuint program_, GLuint uniformBlockIndex_, GLsizei bufSize_, GLsizei * length_, GLchar * uniformBlockName_ ){
    static PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC F;
    if(!F)
        F = ( PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC ) mygetprocaddr("glGetActiveUniformBlockName");
    if( glGetActiveUniformBlockName_hook )
        glGetActiveUniformBlockName_hook( program_, uniformBlockIndex_, bufSize_, length_, uniformBlockName_ );
    F(program_, uniformBlockIndex_, bufSize_, length_, uniformBlockName_);
}
static glGetActiveUniformBlockiv_hook_t glGetActiveUniformBlockiv_hook = 0;
glGetActiveUniformBlockiv_hook_t getHook_glGetActiveUniformBlockiv (){
    return glGetActiveUniformBlockiv_hook ;
}
void setHook_glGetActiveUniformBlockiv ( glGetActiveUniformBlockiv_hook_t hook ){
    glGetActiveUniformBlockiv_hook = hook;
}
void glGetActiveUniformBlockiv ( GLuint program_, GLuint uniformBlockIndex_, GLenum pname_, GLint * params_ ){
    static PFNGLGETACTIVEUNIFORMBLOCKIVPROC F;
    if(!F)
        F = ( PFNGLGETACTIVEUNIFORMBLOCKIVPROC ) mygetprocaddr("glGetActiveUniformBlockiv");
    if( glGetActiveUniformBlockiv_hook )
        glGetActiveUniformBlockiv_hook( program_, uniformBlockIndex_, pname_, params_ );
    F(program_, uniformBlockIndex_, pname_, params_);
}
static glGetActiveUniformName_hook_t glGetActiveUniformName_hook = 0;
glGetActiveUniformName_hook_t getHook_glGetActiveUniformName (){
    return glGetActiveUniformName_hook ;
}
void setHook_glGetActiveUniformName ( glGetActiveUniformName_hook_t hook ){
    glGetActiveUniformName_hook = hook;
}
void glGetActiveUniformName ( GLuint program_, GLuint uniformIndex_, GLsizei bufSize_, GLsizei * length_, GLchar * uniformName_ ){
    static PFNGLGETACTIVEUNIFORMNAMEPROC F;
    if(!F)
        F = ( PFNGLGETACTIVEUNIFORMNAMEPROC ) mygetprocaddr("glGetActiveUniformName");
    if( glGetActiveUniformName_hook )
        glGetActiveUniformName_hook( program_, uniformIndex_, bufSize_, length_, uniformName_ );
    F(program_, uniformIndex_, bufSize_, length_, uniformName_);
}
static glGetActiveUniformsiv_hook_t glGetActiveUniformsiv_hook = 0;
glGetActiveUniformsiv_hook_t getHook_glGetActiveUniformsiv (){
    return glGetActiveUniformsiv_hook ;
}
void setHook_glGetActiveUniformsiv ( glGetActiveUniformsiv_hook_t hook ){
    glGetActiveUniformsiv_hook = hook;
}
void glGetActiveUniformsiv ( GLuint program_, GLsizei uniformCount_, const GLuint * uniformIndices_, GLenum pname_, GLint * params_ ){
    static PFNGLGETACTIVEUNIFORMSIVPROC F;
    if(!F)
        F = ( PFNGLGETACTIVEUNIFORMSIVPROC ) mygetprocaddr("glGetActiveUniformsiv");
    if( glGetActiveUniformsiv_hook )
        glGetActiveUniformsiv_hook( program_, uniformCount_, uniformIndices_, pname_, params_ );
    F(program_, uniformCount_, uniformIndices_, pname_, params_);
}
static glGetAttachedShaders_hook_t glGetAttachedShaders_hook = 0;
glGetAttachedShaders_hook_t getHook_glGetAttachedShaders (){
    return glGetAttachedShaders_hook ;
}
void setHook_glGetAttachedShaders ( glGetAttachedShaders_hook_t hook ){
    glGetAttachedShaders_hook = hook;
}
void glGetAttachedShaders ( GLuint program_, GLsizei maxCount_, GLsizei * count_, GLuint * shaders_ ){
    static PFNGLGETATTACHEDSHADERSPROC F;
    if(!F)
        F = ( PFNGLGETATTACHEDSHADERSPROC ) mygetprocaddr("glGetAttachedShaders");
    if( glGetAttachedShaders_hook )
        glGetAttachedShaders_hook( program_, maxCount_, count_, shaders_ );
    F(program_, maxCount_, count_, shaders_);
}
static glGetAttribLocation_hook_t glGetAttribLocation_hook = 0;
glGetAttribLocation_hook_t getHook_glGetAttribLocation (){
    return glGetAttribLocation_hook ;
}
void setHook_glGetAttribLocation ( glGetAttribLocation_hook_t hook ){
    glGetAttribLocation_hook = hook;
}
GLint glGetAttribLocation ( GLuint program_, const GLchar * name_ ){
    static PFNGLGETATTRIBLOCATIONPROC F;
    if(!F)
        F = ( PFNGLGETATTRIBLOCATIONPROC ) mygetprocaddr("glGetAttribLocation");
    if( glGetAttribLocation_hook )
        glGetAttribLocation_hook( program_, name_ );
    GLint retval = F(program_, name_);
    return retval;
}
static glGetBooleani_v_hook_t glGetBooleani_v_hook = 0;
glGetBooleani_v_hook_t getHook_glGetBooleani_v (){
    return glGetBooleani_v_hook ;
}
void setHook_glGetBooleani_v ( glGetBooleani_v_hook_t hook ){
    glGetBooleani_v_hook = hook;
}
void glGetBooleani_v ( GLenum target_, GLuint index_, GLboolean * data_ ){
    static PFNGLGETBOOLEANI_VPROC F;
    if(!F)
        F = ( PFNGLGETBOOLEANI_VPROC ) mygetprocaddr("glGetBooleani_v");
    if( glGetBooleani_v_hook )
        glGetBooleani_v_hook( target_, index_, data_ );
    F(target_, index_, data_);
}
static glGetBooleanv_hook_t glGetBooleanv_hook = 0;
glGetBooleanv_hook_t getHook_glGetBooleanv (){
    return glGetBooleanv_hook ;
}
void setHook_glGetBooleanv ( glGetBooleanv_hook_t hook ){
    glGetBooleanv_hook = hook;
}
void glGetBooleanv ( GLenum pname_, GLboolean * data_ ){
    static PFNGLGETBOOLEANVPROC F;
    if(!F)
        F = ( PFNGLGETBOOLEANVPROC ) mygetprocaddr("glGetBooleanv");
    if( glGetBooleanv_hook )
        glGetBooleanv_hook( pname_, data_ );
    F(pname_, data_);
}
static glGetBufferParameteri64v_hook_t glGetBufferParameteri64v_hook = 0;
glGetBufferParameteri64v_hook_t getHook_glGetBufferParameteri64v (){
    return glGetBufferParameteri64v_hook ;
}
void setHook_glGetBufferParameteri64v ( glGetBufferParameteri64v_hook_t hook ){
    glGetBufferParameteri64v_hook = hook;
}
void glGetBufferParameteri64v ( GLenum target_, GLenum pname_, GLint64 * params_ ){
    static PFNGLGETBUFFERPARAMETERI64VPROC F;
    if(!F)
        F = ( PFNGLGETBUFFERPARAMETERI64VPROC ) mygetprocaddr("glGetBufferParameteri64v");
    if( glGetBufferParameteri64v_hook )
        glGetBufferParameteri64v_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetBufferParameteriv_hook_t glGetBufferParameteriv_hook = 0;
glGetBufferParameteriv_hook_t getHook_glGetBufferParameteriv (){
    return glGetBufferParameteriv_hook ;
}
void setHook_glGetBufferParameteriv ( glGetBufferParameteriv_hook_t hook ){
    glGetBufferParameteriv_hook = hook;
}
void glGetBufferParameteriv ( GLenum target_, GLenum pname_, GLint * params_ ){
    static PFNGLGETBUFFERPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETBUFFERPARAMETERIVPROC ) mygetprocaddr("glGetBufferParameteriv");
    if( glGetBufferParameteriv_hook )
        glGetBufferParameteriv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetBufferPointerv_hook_t glGetBufferPointerv_hook = 0;
glGetBufferPointerv_hook_t getHook_glGetBufferPointerv (){
    return glGetBufferPointerv_hook ;
}
void setHook_glGetBufferPointerv ( glGetBufferPointerv_hook_t hook ){
    glGetBufferPointerv_hook = hook;
}
void glGetBufferPointerv ( GLenum target_, GLenum pname_, void ** params_ ){
    static PFNGLGETBUFFERPOINTERVPROC F;
    if(!F)
        F = ( PFNGLGETBUFFERPOINTERVPROC ) mygetprocaddr("glGetBufferPointerv");
    if( glGetBufferPointerv_hook )
        glGetBufferPointerv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetBufferSubData_hook_t glGetBufferSubData_hook = 0;
glGetBufferSubData_hook_t getHook_glGetBufferSubData (){
    return glGetBufferSubData_hook ;
}
void setHook_glGetBufferSubData ( glGetBufferSubData_hook_t hook ){
    glGetBufferSubData_hook = hook;
}
void glGetBufferSubData ( GLenum target_, GLintptr offset_, GLsizeiptr size_, void * data_ ){
    static PFNGLGETBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLGETBUFFERSUBDATAPROC ) mygetprocaddr("glGetBufferSubData");
    if( glGetBufferSubData_hook )
        glGetBufferSubData_hook( target_, offset_, size_, data_ );
    F(target_, offset_, size_, data_);
}
static glGetCompressedTexImage_hook_t glGetCompressedTexImage_hook = 0;
glGetCompressedTexImage_hook_t getHook_glGetCompressedTexImage (){
    return glGetCompressedTexImage_hook ;
}
void setHook_glGetCompressedTexImage ( glGetCompressedTexImage_hook_t hook ){
    glGetCompressedTexImage_hook = hook;
}
void glGetCompressedTexImage ( GLenum target_, GLint level_, void * img_ ){
    static PFNGLGETCOMPRESSEDTEXIMAGEPROC F;
    if(!F)
        F = ( PFNGLGETCOMPRESSEDTEXIMAGEPROC ) mygetprocaddr("glGetCompressedTexImage");
    if( glGetCompressedTexImage_hook )
        glGetCompressedTexImage_hook( target_, level_, img_ );
    F(target_, level_, img_);
}
static glGetCompressedTextureImage_hook_t glGetCompressedTextureImage_hook = 0;
glGetCompressedTextureImage_hook_t getHook_glGetCompressedTextureImage (){
    return glGetCompressedTextureImage_hook ;
}
void setHook_glGetCompressedTextureImage ( glGetCompressedTextureImage_hook_t hook ){
    glGetCompressedTextureImage_hook = hook;
}
void glGetCompressedTextureImage ( GLuint texture_, GLint level_, GLsizei bufSize_, void * pixels_ ){
    static PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC F;
    if(!F)
        F = ( PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC ) mygetprocaddr("glGetCompressedTextureImage");
    if( glGetCompressedTextureImage_hook )
        glGetCompressedTextureImage_hook( texture_, level_, bufSize_, pixels_ );
    F(texture_, level_, bufSize_, pixels_);
}
static glGetCompressedTextureSubImage_hook_t glGetCompressedTextureSubImage_hook = 0;
glGetCompressedTextureSubImage_hook_t getHook_glGetCompressedTextureSubImage (){
    return glGetCompressedTextureSubImage_hook ;
}
void setHook_glGetCompressedTextureSubImage ( glGetCompressedTextureSubImage_hook_t hook ){
    glGetCompressedTextureSubImage_hook = hook;
}
void glGetCompressedTextureSubImage ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLsizei width_, GLsizei height_, GLsizei depth_, GLsizei bufSize_, void * pixels_ ){
    static PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC F;
    if(!F)
        F = ( PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC ) mygetprocaddr("glGetCompressedTextureSubImage");
    if( glGetCompressedTextureSubImage_hook )
        glGetCompressedTextureSubImage_hook( texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, bufSize_, pixels_ );
    F(texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, bufSize_, pixels_);
}
static glGetDebugMessageLog_hook_t glGetDebugMessageLog_hook = 0;
glGetDebugMessageLog_hook_t getHook_glGetDebugMessageLog (){
    return glGetDebugMessageLog_hook ;
}
void setHook_glGetDebugMessageLog ( glGetDebugMessageLog_hook_t hook ){
    glGetDebugMessageLog_hook = hook;
}
GLuint glGetDebugMessageLog ( GLuint count_, GLsizei bufSize_, GLenum * sources_, GLenum * types_, GLuint * ids_, GLenum * severities_, GLsizei * lengths_, GLchar * messageLog_ ){
    static PFNGLGETDEBUGMESSAGELOGPROC F;
    if(!F)
        F = ( PFNGLGETDEBUGMESSAGELOGPROC ) mygetprocaddr("glGetDebugMessageLog");
    if( glGetDebugMessageLog_hook )
        glGetDebugMessageLog_hook( count_, bufSize_, sources_, types_, ids_, severities_, lengths_, messageLog_ );
    GLuint retval = F(count_, bufSize_, sources_, types_, ids_, severities_, lengths_, messageLog_);
    return retval;
}
static glGetDoublei_v_hook_t glGetDoublei_v_hook = 0;
glGetDoublei_v_hook_t getHook_glGetDoublei_v (){
    return glGetDoublei_v_hook ;
}
void setHook_glGetDoublei_v ( glGetDoublei_v_hook_t hook ){
    glGetDoublei_v_hook = hook;
}
void glGetDoublei_v ( GLenum target_, GLuint index_, GLdouble * data_ ){
    static PFNGLGETDOUBLEI_VPROC F;
    if(!F)
        F = ( PFNGLGETDOUBLEI_VPROC ) mygetprocaddr("glGetDoublei_v");
    if( glGetDoublei_v_hook )
        glGetDoublei_v_hook( target_, index_, data_ );
    F(target_, index_, data_);
}
static glGetDoublev_hook_t glGetDoublev_hook = 0;
glGetDoublev_hook_t getHook_glGetDoublev (){
    return glGetDoublev_hook ;
}
void setHook_glGetDoublev ( glGetDoublev_hook_t hook ){
    glGetDoublev_hook = hook;
}
void glGetDoublev ( GLenum pname_, GLdouble * data_ ){
    static PFNGLGETDOUBLEVPROC F;
    if(!F)
        F = ( PFNGLGETDOUBLEVPROC ) mygetprocaddr("glGetDoublev");
    if( glGetDoublev_hook )
        glGetDoublev_hook( pname_, data_ );
    F(pname_, data_);
}
static glGetError_hook_t glGetError_hook = 0;
glGetError_hook_t getHook_glGetError (){
    return glGetError_hook ;
}
void setHook_glGetError ( glGetError_hook_t hook ){
    glGetError_hook = hook;
}
GLenum glGetError (  ){
    static PFNGLGETERRORPROC F;
    if(!F)
        F = ( PFNGLGETERRORPROC ) mygetprocaddr("glGetError");
    if( glGetError_hook )
        glGetError_hook(  );
    GLenum retval = F();
    return retval;
}
static glGetFloati_v_hook_t glGetFloati_v_hook = 0;
glGetFloati_v_hook_t getHook_glGetFloati_v (){
    return glGetFloati_v_hook ;
}
void setHook_glGetFloati_v ( glGetFloati_v_hook_t hook ){
    glGetFloati_v_hook = hook;
}
void glGetFloati_v ( GLenum target_, GLuint index_, GLfloat * data_ ){
    static PFNGLGETFLOATI_VPROC F;
    if(!F)
        F = ( PFNGLGETFLOATI_VPROC ) mygetprocaddr("glGetFloati_v");
    if( glGetFloati_v_hook )
        glGetFloati_v_hook( target_, index_, data_ );
    F(target_, index_, data_);
}
static glGetFloatv_hook_t glGetFloatv_hook = 0;
glGetFloatv_hook_t getHook_glGetFloatv (){
    return glGetFloatv_hook ;
}
void setHook_glGetFloatv ( glGetFloatv_hook_t hook ){
    glGetFloatv_hook = hook;
}
void glGetFloatv ( GLenum pname_, GLfloat * data_ ){
    static PFNGLGETFLOATVPROC F;
    if(!F)
        F = ( PFNGLGETFLOATVPROC ) mygetprocaddr("glGetFloatv");
    if( glGetFloatv_hook )
        glGetFloatv_hook( pname_, data_ );
    F(pname_, data_);
}
static glGetFragDataIndex_hook_t glGetFragDataIndex_hook = 0;
glGetFragDataIndex_hook_t getHook_glGetFragDataIndex (){
    return glGetFragDataIndex_hook ;
}
void setHook_glGetFragDataIndex ( glGetFragDataIndex_hook_t hook ){
    glGetFragDataIndex_hook = hook;
}
GLint glGetFragDataIndex ( GLuint program_, const GLchar * name_ ){
    static PFNGLGETFRAGDATAINDEXPROC F;
    if(!F)
        F = ( PFNGLGETFRAGDATAINDEXPROC ) mygetprocaddr("glGetFragDataIndex");
    if( glGetFragDataIndex_hook )
        glGetFragDataIndex_hook( program_, name_ );
    GLint retval = F(program_, name_);
    return retval;
}
static glGetFragDataLocation_hook_t glGetFragDataLocation_hook = 0;
glGetFragDataLocation_hook_t getHook_glGetFragDataLocation (){
    return glGetFragDataLocation_hook ;
}
void setHook_glGetFragDataLocation ( glGetFragDataLocation_hook_t hook ){
    glGetFragDataLocation_hook = hook;
}
GLint glGetFragDataLocation ( GLuint program_, const GLchar * name_ ){
    static PFNGLGETFRAGDATALOCATIONPROC F;
    if(!F)
        F = ( PFNGLGETFRAGDATALOCATIONPROC ) mygetprocaddr("glGetFragDataLocation");
    if( glGetFragDataLocation_hook )
        glGetFragDataLocation_hook( program_, name_ );
    GLint retval = F(program_, name_);
    return retval;
}
static glGetFramebufferAttachmentParameteriv_hook_t glGetFramebufferAttachmentParameteriv_hook = 0;
glGetFramebufferAttachmentParameteriv_hook_t getHook_glGetFramebufferAttachmentParameteriv (){
    return glGetFramebufferAttachmentParameteriv_hook ;
}
void setHook_glGetFramebufferAttachmentParameteriv ( glGetFramebufferAttachmentParameteriv_hook_t hook ){
    glGetFramebufferAttachmentParameteriv_hook = hook;
}
void glGetFramebufferAttachmentParameteriv ( GLenum target_, GLenum attachment_, GLenum pname_, GLint * params_ ){
    static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC ) mygetprocaddr("glGetFramebufferAttachmentParameteriv");
    if( glGetFramebufferAttachmentParameteriv_hook )
        glGetFramebufferAttachmentParameteriv_hook( target_, attachment_, pname_, params_ );
    F(target_, attachment_, pname_, params_);
}
static glGetFramebufferParameteriv_hook_t glGetFramebufferParameteriv_hook = 0;
glGetFramebufferParameteriv_hook_t getHook_glGetFramebufferParameteriv (){
    return glGetFramebufferParameteriv_hook ;
}
void setHook_glGetFramebufferParameteriv ( glGetFramebufferParameteriv_hook_t hook ){
    glGetFramebufferParameteriv_hook = hook;
}
void glGetFramebufferParameteriv ( GLenum target_, GLenum pname_, GLint * params_ ){
    static PFNGLGETFRAMEBUFFERPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETFRAMEBUFFERPARAMETERIVPROC ) mygetprocaddr("glGetFramebufferParameteriv");
    if( glGetFramebufferParameteriv_hook )
        glGetFramebufferParameteriv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetGraphicsResetStatus_hook_t glGetGraphicsResetStatus_hook = 0;
glGetGraphicsResetStatus_hook_t getHook_glGetGraphicsResetStatus (){
    return glGetGraphicsResetStatus_hook ;
}
void setHook_glGetGraphicsResetStatus ( glGetGraphicsResetStatus_hook_t hook ){
    glGetGraphicsResetStatus_hook = hook;
}
GLenum glGetGraphicsResetStatus (  ){
    static PFNGLGETGRAPHICSRESETSTATUSPROC F;
    if(!F)
        F = ( PFNGLGETGRAPHICSRESETSTATUSPROC ) mygetprocaddr("glGetGraphicsResetStatus");
    if( glGetGraphicsResetStatus_hook )
        glGetGraphicsResetStatus_hook(  );
    GLenum retval = F();
    return retval;
}
static glGetInteger64i_v_hook_t glGetInteger64i_v_hook = 0;
glGetInteger64i_v_hook_t getHook_glGetInteger64i_v (){
    return glGetInteger64i_v_hook ;
}
void setHook_glGetInteger64i_v ( glGetInteger64i_v_hook_t hook ){
    glGetInteger64i_v_hook = hook;
}
void glGetInteger64i_v ( GLenum target_, GLuint index_, GLint64 * data_ ){
    static PFNGLGETINTEGER64I_VPROC F;
    if(!F)
        F = ( PFNGLGETINTEGER64I_VPROC ) mygetprocaddr("glGetInteger64i_v");
    if( glGetInteger64i_v_hook )
        glGetInteger64i_v_hook( target_, index_, data_ );
    F(target_, index_, data_);
}
static glGetInteger64v_hook_t glGetInteger64v_hook = 0;
glGetInteger64v_hook_t getHook_glGetInteger64v (){
    return glGetInteger64v_hook ;
}
void setHook_glGetInteger64v ( glGetInteger64v_hook_t hook ){
    glGetInteger64v_hook = hook;
}
void glGetInteger64v ( GLenum pname_, GLint64 * data_ ){
    static PFNGLGETINTEGER64VPROC F;
    if(!F)
        F = ( PFNGLGETINTEGER64VPROC ) mygetprocaddr("glGetInteger64v");
    if( glGetInteger64v_hook )
        glGetInteger64v_hook( pname_, data_ );
    F(pname_, data_);
}
static glGetIntegeri_v_hook_t glGetIntegeri_v_hook = 0;
glGetIntegeri_v_hook_t getHook_glGetIntegeri_v (){
    return glGetIntegeri_v_hook ;
}
void setHook_glGetIntegeri_v ( glGetIntegeri_v_hook_t hook ){
    glGetIntegeri_v_hook = hook;
}
void glGetIntegeri_v ( GLenum target_, GLuint index_, GLint * data_ ){
    static PFNGLGETINTEGERI_VPROC F;
    if(!F)
        F = ( PFNGLGETINTEGERI_VPROC ) mygetprocaddr("glGetIntegeri_v");
    if( glGetIntegeri_v_hook )
        glGetIntegeri_v_hook( target_, index_, data_ );
    F(target_, index_, data_);
}
static glGetIntegerv_hook_t glGetIntegerv_hook = 0;
glGetIntegerv_hook_t getHook_glGetIntegerv (){
    return glGetIntegerv_hook ;
}
void setHook_glGetIntegerv ( glGetIntegerv_hook_t hook ){
    glGetIntegerv_hook = hook;
}
void glGetIntegerv ( GLenum pname_, GLint * data_ ){
    static PFNGLGETINTEGERVPROC F;
    if(!F)
        F = ( PFNGLGETINTEGERVPROC ) mygetprocaddr("glGetIntegerv");
    if( glGetIntegerv_hook )
        glGetIntegerv_hook( pname_, data_ );
    F(pname_, data_);
}
static glGetInternalformati64v_hook_t glGetInternalformati64v_hook = 0;
glGetInternalformati64v_hook_t getHook_glGetInternalformati64v (){
    return glGetInternalformati64v_hook ;
}
void setHook_glGetInternalformati64v ( glGetInternalformati64v_hook_t hook ){
    glGetInternalformati64v_hook = hook;
}
void glGetInternalformati64v ( GLenum target_, GLenum internalformat_, GLenum pname_, GLsizei bufSize_, GLint64 * params_ ){
    static PFNGLGETINTERNALFORMATI64VPROC F;
    if(!F)
        F = ( PFNGLGETINTERNALFORMATI64VPROC ) mygetprocaddr("glGetInternalformati64v");
    if( glGetInternalformati64v_hook )
        glGetInternalformati64v_hook( target_, internalformat_, pname_, bufSize_, params_ );
    F(target_, internalformat_, pname_, bufSize_, params_);
}
static glGetInternalformativ_hook_t glGetInternalformativ_hook = 0;
glGetInternalformativ_hook_t getHook_glGetInternalformativ (){
    return glGetInternalformativ_hook ;
}
void setHook_glGetInternalformativ ( glGetInternalformativ_hook_t hook ){
    glGetInternalformativ_hook = hook;
}
void glGetInternalformativ ( GLenum target_, GLenum internalformat_, GLenum pname_, GLsizei bufSize_, GLint * params_ ){
    static PFNGLGETINTERNALFORMATIVPROC F;
    if(!F)
        F = ( PFNGLGETINTERNALFORMATIVPROC ) mygetprocaddr("glGetInternalformativ");
    if( glGetInternalformativ_hook )
        glGetInternalformativ_hook( target_, internalformat_, pname_, bufSize_, params_ );
    F(target_, internalformat_, pname_, bufSize_, params_);
}
static glGetMultisamplefv_hook_t glGetMultisamplefv_hook = 0;
glGetMultisamplefv_hook_t getHook_glGetMultisamplefv (){
    return glGetMultisamplefv_hook ;
}
void setHook_glGetMultisamplefv ( glGetMultisamplefv_hook_t hook ){
    glGetMultisamplefv_hook = hook;
}
void glGetMultisamplefv ( GLenum pname_, GLuint index_, GLfloat * val_ ){
    static PFNGLGETMULTISAMPLEFVPROC F;
    if(!F)
        F = ( PFNGLGETMULTISAMPLEFVPROC ) mygetprocaddr("glGetMultisamplefv");
    if( glGetMultisamplefv_hook )
        glGetMultisamplefv_hook( pname_, index_, val_ );
    F(pname_, index_, val_);
}
static glGetNamedBufferParameteri64v_hook_t glGetNamedBufferParameteri64v_hook = 0;
glGetNamedBufferParameteri64v_hook_t getHook_glGetNamedBufferParameteri64v (){
    return glGetNamedBufferParameteri64v_hook ;
}
void setHook_glGetNamedBufferParameteri64v ( glGetNamedBufferParameteri64v_hook_t hook ){
    glGetNamedBufferParameteri64v_hook = hook;
}
void glGetNamedBufferParameteri64v ( GLuint buffer_, GLenum pname_, GLint64 * params_ ){
    static PFNGLGETNAMEDBUFFERPARAMETERI64VPROC F;
    if(!F)
        F = ( PFNGLGETNAMEDBUFFERPARAMETERI64VPROC ) mygetprocaddr("glGetNamedBufferParameteri64v");
    if( glGetNamedBufferParameteri64v_hook )
        glGetNamedBufferParameteri64v_hook( buffer_, pname_, params_ );
    F(buffer_, pname_, params_);
}
static glGetNamedBufferParameteriv_hook_t glGetNamedBufferParameteriv_hook = 0;
glGetNamedBufferParameteriv_hook_t getHook_glGetNamedBufferParameteriv (){
    return glGetNamedBufferParameteriv_hook ;
}
void setHook_glGetNamedBufferParameteriv ( glGetNamedBufferParameteriv_hook_t hook ){
    glGetNamedBufferParameteriv_hook = hook;
}
void glGetNamedBufferParameteriv ( GLuint buffer_, GLenum pname_, GLint * params_ ){
    static PFNGLGETNAMEDBUFFERPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETNAMEDBUFFERPARAMETERIVPROC ) mygetprocaddr("glGetNamedBufferParameteriv");
    if( glGetNamedBufferParameteriv_hook )
        glGetNamedBufferParameteriv_hook( buffer_, pname_, params_ );
    F(buffer_, pname_, params_);
}
static glGetNamedBufferPointerv_hook_t glGetNamedBufferPointerv_hook = 0;
glGetNamedBufferPointerv_hook_t getHook_glGetNamedBufferPointerv (){
    return glGetNamedBufferPointerv_hook ;
}
void setHook_glGetNamedBufferPointerv ( glGetNamedBufferPointerv_hook_t hook ){
    glGetNamedBufferPointerv_hook = hook;
}
void glGetNamedBufferPointerv ( GLuint buffer_, GLenum pname_, void ** params_ ){
    static PFNGLGETNAMEDBUFFERPOINTERVPROC F;
    if(!F)
        F = ( PFNGLGETNAMEDBUFFERPOINTERVPROC ) mygetprocaddr("glGetNamedBufferPointerv");
    if( glGetNamedBufferPointerv_hook )
        glGetNamedBufferPointerv_hook( buffer_, pname_, params_ );
    F(buffer_, pname_, params_);
}
static glGetNamedBufferSubData_hook_t glGetNamedBufferSubData_hook = 0;
glGetNamedBufferSubData_hook_t getHook_glGetNamedBufferSubData (){
    return glGetNamedBufferSubData_hook ;
}
void setHook_glGetNamedBufferSubData ( glGetNamedBufferSubData_hook_t hook ){
    glGetNamedBufferSubData_hook = hook;
}
void glGetNamedBufferSubData ( GLuint buffer_, GLintptr offset_, GLsizeiptr size_, void * data_ ){
    static PFNGLGETNAMEDBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLGETNAMEDBUFFERSUBDATAPROC ) mygetprocaddr("glGetNamedBufferSubData");
    if( glGetNamedBufferSubData_hook )
        glGetNamedBufferSubData_hook( buffer_, offset_, size_, data_ );
    F(buffer_, offset_, size_, data_);
}
static glGetNamedFramebufferAttachmentParameteriv_hook_t glGetNamedFramebufferAttachmentParameteriv_hook = 0;
glGetNamedFramebufferAttachmentParameteriv_hook_t getHook_glGetNamedFramebufferAttachmentParameteriv (){
    return glGetNamedFramebufferAttachmentParameteriv_hook ;
}
void setHook_glGetNamedFramebufferAttachmentParameteriv ( glGetNamedFramebufferAttachmentParameteriv_hook_t hook ){
    glGetNamedFramebufferAttachmentParameteriv_hook = hook;
}
void glGetNamedFramebufferAttachmentParameteriv ( GLuint framebuffer_, GLenum attachment_, GLenum pname_, GLint * params_ ){
    static PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC ) mygetprocaddr("glGetNamedFramebufferAttachmentParameteriv");
    if( glGetNamedFramebufferAttachmentParameteriv_hook )
        glGetNamedFramebufferAttachmentParameteriv_hook( framebuffer_, attachment_, pname_, params_ );
    F(framebuffer_, attachment_, pname_, params_);
}
static glGetNamedFramebufferParameteriv_hook_t glGetNamedFramebufferParameteriv_hook = 0;
glGetNamedFramebufferParameteriv_hook_t getHook_glGetNamedFramebufferParameteriv (){
    return glGetNamedFramebufferParameteriv_hook ;
}
void setHook_glGetNamedFramebufferParameteriv ( glGetNamedFramebufferParameteriv_hook_t hook ){
    glGetNamedFramebufferParameteriv_hook = hook;
}
void glGetNamedFramebufferParameteriv ( GLuint framebuffer_, GLenum pname_, GLint * param_ ){
    static PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC ) mygetprocaddr("glGetNamedFramebufferParameteriv");
    if( glGetNamedFramebufferParameteriv_hook )
        glGetNamedFramebufferParameteriv_hook( framebuffer_, pname_, param_ );
    F(framebuffer_, pname_, param_);
}
static glGetNamedRenderbufferParameteriv_hook_t glGetNamedRenderbufferParameteriv_hook = 0;
glGetNamedRenderbufferParameteriv_hook_t getHook_glGetNamedRenderbufferParameteriv (){
    return glGetNamedRenderbufferParameteriv_hook ;
}
void setHook_glGetNamedRenderbufferParameteriv ( glGetNamedRenderbufferParameteriv_hook_t hook ){
    glGetNamedRenderbufferParameteriv_hook = hook;
}
void glGetNamedRenderbufferParameteriv ( GLuint renderbuffer_, GLenum pname_, GLint * params_ ){
    static PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC ) mygetprocaddr("glGetNamedRenderbufferParameteriv");
    if( glGetNamedRenderbufferParameteriv_hook )
        glGetNamedRenderbufferParameteriv_hook( renderbuffer_, pname_, params_ );
    F(renderbuffer_, pname_, params_);
}
static glGetObjectLabel_hook_t glGetObjectLabel_hook = 0;
glGetObjectLabel_hook_t getHook_glGetObjectLabel (){
    return glGetObjectLabel_hook ;
}
void setHook_glGetObjectLabel ( glGetObjectLabel_hook_t hook ){
    glGetObjectLabel_hook = hook;
}
void glGetObjectLabel ( GLenum identifier_, GLuint name_, GLsizei bufSize_, GLsizei * length_, GLchar * label_ ){
    static PFNGLGETOBJECTLABELPROC F;
    if(!F)
        F = ( PFNGLGETOBJECTLABELPROC ) mygetprocaddr("glGetObjectLabel");
    if( glGetObjectLabel_hook )
        glGetObjectLabel_hook( identifier_, name_, bufSize_, length_, label_ );
    F(identifier_, name_, bufSize_, length_, label_);
}
static glGetObjectPtrLabel_hook_t glGetObjectPtrLabel_hook = 0;
glGetObjectPtrLabel_hook_t getHook_glGetObjectPtrLabel (){
    return glGetObjectPtrLabel_hook ;
}
void setHook_glGetObjectPtrLabel ( glGetObjectPtrLabel_hook_t hook ){
    glGetObjectPtrLabel_hook = hook;
}
void glGetObjectPtrLabel ( const void * ptr_, GLsizei bufSize_, GLsizei * length_, GLchar * label_ ){
    static PFNGLGETOBJECTPTRLABELPROC F;
    if(!F)
        F = ( PFNGLGETOBJECTPTRLABELPROC ) mygetprocaddr("glGetObjectPtrLabel");
    if( glGetObjectPtrLabel_hook )
        glGetObjectPtrLabel_hook( ptr_, bufSize_, length_, label_ );
    F(ptr_, bufSize_, length_, label_);
}
static glGetProgramBinary_hook_t glGetProgramBinary_hook = 0;
glGetProgramBinary_hook_t getHook_glGetProgramBinary (){
    return glGetProgramBinary_hook ;
}
void setHook_glGetProgramBinary ( glGetProgramBinary_hook_t hook ){
    glGetProgramBinary_hook = hook;
}
void glGetProgramBinary ( GLuint program_, GLsizei bufSize_, GLsizei * length_, GLenum * binaryFormat_, void * binary_ ){
    static PFNGLGETPROGRAMBINARYPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMBINARYPROC ) mygetprocaddr("glGetProgramBinary");
    if( glGetProgramBinary_hook )
        glGetProgramBinary_hook( program_, bufSize_, length_, binaryFormat_, binary_ );
    F(program_, bufSize_, length_, binaryFormat_, binary_);
}
static glGetProgramInfoLog_hook_t glGetProgramInfoLog_hook = 0;
glGetProgramInfoLog_hook_t getHook_glGetProgramInfoLog (){
    return glGetProgramInfoLog_hook ;
}
void setHook_glGetProgramInfoLog ( glGetProgramInfoLog_hook_t hook ){
    glGetProgramInfoLog_hook = hook;
}
void glGetProgramInfoLog ( GLuint program_, GLsizei bufSize_, GLsizei * length_, GLchar * infoLog_ ){
    static PFNGLGETPROGRAMINFOLOGPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMINFOLOGPROC ) mygetprocaddr("glGetProgramInfoLog");
    if( glGetProgramInfoLog_hook )
        glGetProgramInfoLog_hook( program_, bufSize_, length_, infoLog_ );
    F(program_, bufSize_, length_, infoLog_);
}
static glGetProgramInterfaceiv_hook_t glGetProgramInterfaceiv_hook = 0;
glGetProgramInterfaceiv_hook_t getHook_glGetProgramInterfaceiv (){
    return glGetProgramInterfaceiv_hook ;
}
void setHook_glGetProgramInterfaceiv ( glGetProgramInterfaceiv_hook_t hook ){
    glGetProgramInterfaceiv_hook = hook;
}
void glGetProgramInterfaceiv ( GLuint program_, GLenum programInterface_, GLenum pname_, GLint * params_ ){
    static PFNGLGETPROGRAMINTERFACEIVPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMINTERFACEIVPROC ) mygetprocaddr("glGetProgramInterfaceiv");
    if( glGetProgramInterfaceiv_hook )
        glGetProgramInterfaceiv_hook( program_, programInterface_, pname_, params_ );
    F(program_, programInterface_, pname_, params_);
}
static glGetProgramPipelineInfoLog_hook_t glGetProgramPipelineInfoLog_hook = 0;
glGetProgramPipelineInfoLog_hook_t getHook_glGetProgramPipelineInfoLog (){
    return glGetProgramPipelineInfoLog_hook ;
}
void setHook_glGetProgramPipelineInfoLog ( glGetProgramPipelineInfoLog_hook_t hook ){
    glGetProgramPipelineInfoLog_hook = hook;
}
void glGetProgramPipelineInfoLog ( GLuint pipeline_, GLsizei bufSize_, GLsizei * length_, GLchar * infoLog_ ){
    static PFNGLGETPROGRAMPIPELINEINFOLOGPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMPIPELINEINFOLOGPROC ) mygetprocaddr("glGetProgramPipelineInfoLog");
    if( glGetProgramPipelineInfoLog_hook )
        glGetProgramPipelineInfoLog_hook( pipeline_, bufSize_, length_, infoLog_ );
    F(pipeline_, bufSize_, length_, infoLog_);
}
static glGetProgramPipelineiv_hook_t glGetProgramPipelineiv_hook = 0;
glGetProgramPipelineiv_hook_t getHook_glGetProgramPipelineiv (){
    return glGetProgramPipelineiv_hook ;
}
void setHook_glGetProgramPipelineiv ( glGetProgramPipelineiv_hook_t hook ){
    glGetProgramPipelineiv_hook = hook;
}
void glGetProgramPipelineiv ( GLuint pipeline_, GLenum pname_, GLint * params_ ){
    static PFNGLGETPROGRAMPIPELINEIVPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMPIPELINEIVPROC ) mygetprocaddr("glGetProgramPipelineiv");
    if( glGetProgramPipelineiv_hook )
        glGetProgramPipelineiv_hook( pipeline_, pname_, params_ );
    F(pipeline_, pname_, params_);
}
static glGetProgramResourceIndex_hook_t glGetProgramResourceIndex_hook = 0;
glGetProgramResourceIndex_hook_t getHook_glGetProgramResourceIndex (){
    return glGetProgramResourceIndex_hook ;
}
void setHook_glGetProgramResourceIndex ( glGetProgramResourceIndex_hook_t hook ){
    glGetProgramResourceIndex_hook = hook;
}
GLuint glGetProgramResourceIndex ( GLuint program_, GLenum programInterface_, const GLchar * name_ ){
    static PFNGLGETPROGRAMRESOURCEINDEXPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMRESOURCEINDEXPROC ) mygetprocaddr("glGetProgramResourceIndex");
    if( glGetProgramResourceIndex_hook )
        glGetProgramResourceIndex_hook( program_, programInterface_, name_ );
    GLuint retval = F(program_, programInterface_, name_);
    return retval;
}
static glGetProgramResourceLocation_hook_t glGetProgramResourceLocation_hook = 0;
glGetProgramResourceLocation_hook_t getHook_glGetProgramResourceLocation (){
    return glGetProgramResourceLocation_hook ;
}
void setHook_glGetProgramResourceLocation ( glGetProgramResourceLocation_hook_t hook ){
    glGetProgramResourceLocation_hook = hook;
}
GLint glGetProgramResourceLocation ( GLuint program_, GLenum programInterface_, const GLchar * name_ ){
    static PFNGLGETPROGRAMRESOURCELOCATIONPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMRESOURCELOCATIONPROC ) mygetprocaddr("glGetProgramResourceLocation");
    if( glGetProgramResourceLocation_hook )
        glGetProgramResourceLocation_hook( program_, programInterface_, name_ );
    GLint retval = F(program_, programInterface_, name_);
    return retval;
}
static glGetProgramResourceLocationIndex_hook_t glGetProgramResourceLocationIndex_hook = 0;
glGetProgramResourceLocationIndex_hook_t getHook_glGetProgramResourceLocationIndex (){
    return glGetProgramResourceLocationIndex_hook ;
}
void setHook_glGetProgramResourceLocationIndex ( glGetProgramResourceLocationIndex_hook_t hook ){
    glGetProgramResourceLocationIndex_hook = hook;
}
GLint glGetProgramResourceLocationIndex ( GLuint program_, GLenum programInterface_, const GLchar * name_ ){
    static PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC ) mygetprocaddr("glGetProgramResourceLocationIndex");
    if( glGetProgramResourceLocationIndex_hook )
        glGetProgramResourceLocationIndex_hook( program_, programInterface_, name_ );
    GLint retval = F(program_, programInterface_, name_);
    return retval;
}
static glGetProgramResourceName_hook_t glGetProgramResourceName_hook = 0;
glGetProgramResourceName_hook_t getHook_glGetProgramResourceName (){
    return glGetProgramResourceName_hook ;
}
void setHook_glGetProgramResourceName ( glGetProgramResourceName_hook_t hook ){
    glGetProgramResourceName_hook = hook;
}
void glGetProgramResourceName ( GLuint program_, GLenum programInterface_, GLuint index_, GLsizei bufSize_, GLsizei * length_, GLchar * name_ ){
    static PFNGLGETPROGRAMRESOURCENAMEPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMRESOURCENAMEPROC ) mygetprocaddr("glGetProgramResourceName");
    if( glGetProgramResourceName_hook )
        glGetProgramResourceName_hook( program_, programInterface_, index_, bufSize_, length_, name_ );
    F(program_, programInterface_, index_, bufSize_, length_, name_);
}
static glGetProgramResourceiv_hook_t glGetProgramResourceiv_hook = 0;
glGetProgramResourceiv_hook_t getHook_glGetProgramResourceiv (){
    return glGetProgramResourceiv_hook ;
}
void setHook_glGetProgramResourceiv ( glGetProgramResourceiv_hook_t hook ){
    glGetProgramResourceiv_hook = hook;
}
void glGetProgramResourceiv ( GLuint program_, GLenum programInterface_, GLuint index_, GLsizei propCount_, const GLenum * props_, GLsizei bufSize_, GLsizei * length_, GLint * params_ ){
    static PFNGLGETPROGRAMRESOURCEIVPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMRESOURCEIVPROC ) mygetprocaddr("glGetProgramResourceiv");
    if( glGetProgramResourceiv_hook )
        glGetProgramResourceiv_hook( program_, programInterface_, index_, propCount_, props_, bufSize_, length_, params_ );
    F(program_, programInterface_, index_, propCount_, props_, bufSize_, length_, params_);
}
static glGetProgramStageiv_hook_t glGetProgramStageiv_hook = 0;
glGetProgramStageiv_hook_t getHook_glGetProgramStageiv (){
    return glGetProgramStageiv_hook ;
}
void setHook_glGetProgramStageiv ( glGetProgramStageiv_hook_t hook ){
    glGetProgramStageiv_hook = hook;
}
void glGetProgramStageiv ( GLuint program_, GLenum shadertype_, GLenum pname_, GLint * values_ ){
    static PFNGLGETPROGRAMSTAGEIVPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMSTAGEIVPROC ) mygetprocaddr("glGetProgramStageiv");
    if( glGetProgramStageiv_hook )
        glGetProgramStageiv_hook( program_, shadertype_, pname_, values_ );
    F(program_, shadertype_, pname_, values_);
}
static glGetProgramiv_hook_t glGetProgramiv_hook = 0;
glGetProgramiv_hook_t getHook_glGetProgramiv (){
    return glGetProgramiv_hook ;
}
void setHook_glGetProgramiv ( glGetProgramiv_hook_t hook ){
    glGetProgramiv_hook = hook;
}
void glGetProgramiv ( GLuint program_, GLenum pname_, GLint * params_ ){
    static PFNGLGETPROGRAMIVPROC F;
    if(!F)
        F = ( PFNGLGETPROGRAMIVPROC ) mygetprocaddr("glGetProgramiv");
    if( glGetProgramiv_hook )
        glGetProgramiv_hook( program_, pname_, params_ );
    F(program_, pname_, params_);
}
static glGetQueryBufferObjecti64v_hook_t glGetQueryBufferObjecti64v_hook = 0;
glGetQueryBufferObjecti64v_hook_t getHook_glGetQueryBufferObjecti64v (){
    return glGetQueryBufferObjecti64v_hook ;
}
void setHook_glGetQueryBufferObjecti64v ( glGetQueryBufferObjecti64v_hook_t hook ){
    glGetQueryBufferObjecti64v_hook = hook;
}
void glGetQueryBufferObjecti64v ( GLuint id_, GLuint buffer_, GLenum pname_, GLintptr offset_ ){
    static PFNGLGETQUERYBUFFEROBJECTI64VPROC F;
    if(!F)
        F = ( PFNGLGETQUERYBUFFEROBJECTI64VPROC ) mygetprocaddr("glGetQueryBufferObjecti64v");
    if( glGetQueryBufferObjecti64v_hook )
        glGetQueryBufferObjecti64v_hook( id_, buffer_, pname_, offset_ );
    F(id_, buffer_, pname_, offset_);
}
static glGetQueryBufferObjectiv_hook_t glGetQueryBufferObjectiv_hook = 0;
glGetQueryBufferObjectiv_hook_t getHook_glGetQueryBufferObjectiv (){
    return glGetQueryBufferObjectiv_hook ;
}
void setHook_glGetQueryBufferObjectiv ( glGetQueryBufferObjectiv_hook_t hook ){
    glGetQueryBufferObjectiv_hook = hook;
}
void glGetQueryBufferObjectiv ( GLuint id_, GLuint buffer_, GLenum pname_, GLintptr offset_ ){
    static PFNGLGETQUERYBUFFEROBJECTIVPROC F;
    if(!F)
        F = ( PFNGLGETQUERYBUFFEROBJECTIVPROC ) mygetprocaddr("glGetQueryBufferObjectiv");
    if( glGetQueryBufferObjectiv_hook )
        glGetQueryBufferObjectiv_hook( id_, buffer_, pname_, offset_ );
    F(id_, buffer_, pname_, offset_);
}
static glGetQueryBufferObjectui64v_hook_t glGetQueryBufferObjectui64v_hook = 0;
glGetQueryBufferObjectui64v_hook_t getHook_glGetQueryBufferObjectui64v (){
    return glGetQueryBufferObjectui64v_hook ;
}
void setHook_glGetQueryBufferObjectui64v ( glGetQueryBufferObjectui64v_hook_t hook ){
    glGetQueryBufferObjectui64v_hook = hook;
}
void glGetQueryBufferObjectui64v ( GLuint id_, GLuint buffer_, GLenum pname_, GLintptr offset_ ){
    static PFNGLGETQUERYBUFFEROBJECTUI64VPROC F;
    if(!F)
        F = ( PFNGLGETQUERYBUFFEROBJECTUI64VPROC ) mygetprocaddr("glGetQueryBufferObjectui64v");
    if( glGetQueryBufferObjectui64v_hook )
        glGetQueryBufferObjectui64v_hook( id_, buffer_, pname_, offset_ );
    F(id_, buffer_, pname_, offset_);
}
static glGetQueryBufferObjectuiv_hook_t glGetQueryBufferObjectuiv_hook = 0;
glGetQueryBufferObjectuiv_hook_t getHook_glGetQueryBufferObjectuiv (){
    return glGetQueryBufferObjectuiv_hook ;
}
void setHook_glGetQueryBufferObjectuiv ( glGetQueryBufferObjectuiv_hook_t hook ){
    glGetQueryBufferObjectuiv_hook = hook;
}
void glGetQueryBufferObjectuiv ( GLuint id_, GLuint buffer_, GLenum pname_, GLintptr offset_ ){
    static PFNGLGETQUERYBUFFEROBJECTUIVPROC F;
    if(!F)
        F = ( PFNGLGETQUERYBUFFEROBJECTUIVPROC ) mygetprocaddr("glGetQueryBufferObjectuiv");
    if( glGetQueryBufferObjectuiv_hook )
        glGetQueryBufferObjectuiv_hook( id_, buffer_, pname_, offset_ );
    F(id_, buffer_, pname_, offset_);
}
static glGetQueryIndexediv_hook_t glGetQueryIndexediv_hook = 0;
glGetQueryIndexediv_hook_t getHook_glGetQueryIndexediv (){
    return glGetQueryIndexediv_hook ;
}
void setHook_glGetQueryIndexediv ( glGetQueryIndexediv_hook_t hook ){
    glGetQueryIndexediv_hook = hook;
}
void glGetQueryIndexediv ( GLenum target_, GLuint index_, GLenum pname_, GLint * params_ ){
    static PFNGLGETQUERYINDEXEDIVPROC F;
    if(!F)
        F = ( PFNGLGETQUERYINDEXEDIVPROC ) mygetprocaddr("glGetQueryIndexediv");
    if( glGetQueryIndexediv_hook )
        glGetQueryIndexediv_hook( target_, index_, pname_, params_ );
    F(target_, index_, pname_, params_);
}
static glGetQueryObjecti64v_hook_t glGetQueryObjecti64v_hook = 0;
glGetQueryObjecti64v_hook_t getHook_glGetQueryObjecti64v (){
    return glGetQueryObjecti64v_hook ;
}
void setHook_glGetQueryObjecti64v ( glGetQueryObjecti64v_hook_t hook ){
    glGetQueryObjecti64v_hook = hook;
}
void glGetQueryObjecti64v ( GLuint id_, GLenum pname_, GLint64 * params_ ){
    static PFNGLGETQUERYOBJECTI64VPROC F;
    if(!F)
        F = ( PFNGLGETQUERYOBJECTI64VPROC ) mygetprocaddr("glGetQueryObjecti64v");
    if( glGetQueryObjecti64v_hook )
        glGetQueryObjecti64v_hook( id_, pname_, params_ );
    F(id_, pname_, params_);
}
static glGetQueryObjectiv_hook_t glGetQueryObjectiv_hook = 0;
glGetQueryObjectiv_hook_t getHook_glGetQueryObjectiv (){
    return glGetQueryObjectiv_hook ;
}
void setHook_glGetQueryObjectiv ( glGetQueryObjectiv_hook_t hook ){
    glGetQueryObjectiv_hook = hook;
}
void glGetQueryObjectiv ( GLuint id_, GLenum pname_, GLint * params_ ){
    static PFNGLGETQUERYOBJECTIVPROC F;
    if(!F)
        F = ( PFNGLGETQUERYOBJECTIVPROC ) mygetprocaddr("glGetQueryObjectiv");
    if( glGetQueryObjectiv_hook )
        glGetQueryObjectiv_hook( id_, pname_, params_ );
    F(id_, pname_, params_);
}
static glGetQueryObjectui64v_hook_t glGetQueryObjectui64v_hook = 0;
glGetQueryObjectui64v_hook_t getHook_glGetQueryObjectui64v (){
    return glGetQueryObjectui64v_hook ;
}
void setHook_glGetQueryObjectui64v ( glGetQueryObjectui64v_hook_t hook ){
    glGetQueryObjectui64v_hook = hook;
}
void glGetQueryObjectui64v ( GLuint id_, GLenum pname_, GLuint64 * params_ ){
    static PFNGLGETQUERYOBJECTUI64VPROC F;
    if(!F)
        F = ( PFNGLGETQUERYOBJECTUI64VPROC ) mygetprocaddr("glGetQueryObjectui64v");
    if( glGetQueryObjectui64v_hook )
        glGetQueryObjectui64v_hook( id_, pname_, params_ );
    F(id_, pname_, params_);
}
static glGetQueryObjectuiv_hook_t glGetQueryObjectuiv_hook = 0;
glGetQueryObjectuiv_hook_t getHook_glGetQueryObjectuiv (){
    return glGetQueryObjectuiv_hook ;
}
void setHook_glGetQueryObjectuiv ( glGetQueryObjectuiv_hook_t hook ){
    glGetQueryObjectuiv_hook = hook;
}
void glGetQueryObjectuiv ( GLuint id_, GLenum pname_, GLuint * params_ ){
    static PFNGLGETQUERYOBJECTUIVPROC F;
    if(!F)
        F = ( PFNGLGETQUERYOBJECTUIVPROC ) mygetprocaddr("glGetQueryObjectuiv");
    if( glGetQueryObjectuiv_hook )
        glGetQueryObjectuiv_hook( id_, pname_, params_ );
    F(id_, pname_, params_);
}
static glGetQueryiv_hook_t glGetQueryiv_hook = 0;
glGetQueryiv_hook_t getHook_glGetQueryiv (){
    return glGetQueryiv_hook ;
}
void setHook_glGetQueryiv ( glGetQueryiv_hook_t hook ){
    glGetQueryiv_hook = hook;
}
void glGetQueryiv ( GLenum target_, GLenum pname_, GLint * params_ ){
    static PFNGLGETQUERYIVPROC F;
    if(!F)
        F = ( PFNGLGETQUERYIVPROC ) mygetprocaddr("glGetQueryiv");
    if( glGetQueryiv_hook )
        glGetQueryiv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetRenderbufferParameteriv_hook_t glGetRenderbufferParameteriv_hook = 0;
glGetRenderbufferParameteriv_hook_t getHook_glGetRenderbufferParameteriv (){
    return glGetRenderbufferParameteriv_hook ;
}
void setHook_glGetRenderbufferParameteriv ( glGetRenderbufferParameteriv_hook_t hook ){
    glGetRenderbufferParameteriv_hook = hook;
}
void glGetRenderbufferParameteriv ( GLenum target_, GLenum pname_, GLint * params_ ){
    static PFNGLGETRENDERBUFFERPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETRENDERBUFFERPARAMETERIVPROC ) mygetprocaddr("glGetRenderbufferParameteriv");
    if( glGetRenderbufferParameteriv_hook )
        glGetRenderbufferParameteriv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetSamplerParameterIiv_hook_t glGetSamplerParameterIiv_hook = 0;
glGetSamplerParameterIiv_hook_t getHook_glGetSamplerParameterIiv (){
    return glGetSamplerParameterIiv_hook ;
}
void setHook_glGetSamplerParameterIiv ( glGetSamplerParameterIiv_hook_t hook ){
    glGetSamplerParameterIiv_hook = hook;
}
void glGetSamplerParameterIiv ( GLuint sampler_, GLenum pname_, GLint * params_ ){
    static PFNGLGETSAMPLERPARAMETERIIVPROC F;
    if(!F)
        F = ( PFNGLGETSAMPLERPARAMETERIIVPROC ) mygetprocaddr("glGetSamplerParameterIiv");
    if( glGetSamplerParameterIiv_hook )
        glGetSamplerParameterIiv_hook( sampler_, pname_, params_ );
    F(sampler_, pname_, params_);
}
static glGetSamplerParameterIuiv_hook_t glGetSamplerParameterIuiv_hook = 0;
glGetSamplerParameterIuiv_hook_t getHook_glGetSamplerParameterIuiv (){
    return glGetSamplerParameterIuiv_hook ;
}
void setHook_glGetSamplerParameterIuiv ( glGetSamplerParameterIuiv_hook_t hook ){
    glGetSamplerParameterIuiv_hook = hook;
}
void glGetSamplerParameterIuiv ( GLuint sampler_, GLenum pname_, GLuint * params_ ){
    static PFNGLGETSAMPLERPARAMETERIUIVPROC F;
    if(!F)
        F = ( PFNGLGETSAMPLERPARAMETERIUIVPROC ) mygetprocaddr("glGetSamplerParameterIuiv");
    if( glGetSamplerParameterIuiv_hook )
        glGetSamplerParameterIuiv_hook( sampler_, pname_, params_ );
    F(sampler_, pname_, params_);
}
static glGetSamplerParameterfv_hook_t glGetSamplerParameterfv_hook = 0;
glGetSamplerParameterfv_hook_t getHook_glGetSamplerParameterfv (){
    return glGetSamplerParameterfv_hook ;
}
void setHook_glGetSamplerParameterfv ( glGetSamplerParameterfv_hook_t hook ){
    glGetSamplerParameterfv_hook = hook;
}
void glGetSamplerParameterfv ( GLuint sampler_, GLenum pname_, GLfloat * params_ ){
    static PFNGLGETSAMPLERPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLGETSAMPLERPARAMETERFVPROC ) mygetprocaddr("glGetSamplerParameterfv");
    if( glGetSamplerParameterfv_hook )
        glGetSamplerParameterfv_hook( sampler_, pname_, params_ );
    F(sampler_, pname_, params_);
}
static glGetSamplerParameteriv_hook_t glGetSamplerParameteriv_hook = 0;
glGetSamplerParameteriv_hook_t getHook_glGetSamplerParameteriv (){
    return glGetSamplerParameteriv_hook ;
}
void setHook_glGetSamplerParameteriv ( glGetSamplerParameteriv_hook_t hook ){
    glGetSamplerParameteriv_hook = hook;
}
void glGetSamplerParameteriv ( GLuint sampler_, GLenum pname_, GLint * params_ ){
    static PFNGLGETSAMPLERPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETSAMPLERPARAMETERIVPROC ) mygetprocaddr("glGetSamplerParameteriv");
    if( glGetSamplerParameteriv_hook )
        glGetSamplerParameteriv_hook( sampler_, pname_, params_ );
    F(sampler_, pname_, params_);
}
static glGetShaderInfoLog_hook_t glGetShaderInfoLog_hook = 0;
glGetShaderInfoLog_hook_t getHook_glGetShaderInfoLog (){
    return glGetShaderInfoLog_hook ;
}
void setHook_glGetShaderInfoLog ( glGetShaderInfoLog_hook_t hook ){
    glGetShaderInfoLog_hook = hook;
}
void glGetShaderInfoLog ( GLuint shader_, GLsizei bufSize_, GLsizei * length_, GLchar * infoLog_ ){
    static PFNGLGETSHADERINFOLOGPROC F;
    if(!F)
        F = ( PFNGLGETSHADERINFOLOGPROC ) mygetprocaddr("glGetShaderInfoLog");
    if( glGetShaderInfoLog_hook )
        glGetShaderInfoLog_hook( shader_, bufSize_, length_, infoLog_ );
    F(shader_, bufSize_, length_, infoLog_);
}
static glGetShaderPrecisionFormat_hook_t glGetShaderPrecisionFormat_hook = 0;
glGetShaderPrecisionFormat_hook_t getHook_glGetShaderPrecisionFormat (){
    return glGetShaderPrecisionFormat_hook ;
}
void setHook_glGetShaderPrecisionFormat ( glGetShaderPrecisionFormat_hook_t hook ){
    glGetShaderPrecisionFormat_hook = hook;
}
void glGetShaderPrecisionFormat ( GLenum shadertype_, GLenum precisiontype_, GLint * range_, GLint * precision_ ){
    static PFNGLGETSHADERPRECISIONFORMATPROC F;
    if(!F)
        F = ( PFNGLGETSHADERPRECISIONFORMATPROC ) mygetprocaddr("glGetShaderPrecisionFormat");
    if( glGetShaderPrecisionFormat_hook )
        glGetShaderPrecisionFormat_hook( shadertype_, precisiontype_, range_, precision_ );
    F(shadertype_, precisiontype_, range_, precision_);
}
static glGetShaderSource_hook_t glGetShaderSource_hook = 0;
glGetShaderSource_hook_t getHook_glGetShaderSource (){
    return glGetShaderSource_hook ;
}
void setHook_glGetShaderSource ( glGetShaderSource_hook_t hook ){
    glGetShaderSource_hook = hook;
}
void glGetShaderSource ( GLuint shader_, GLsizei bufSize_, GLsizei * length_, GLchar * source_ ){
    static PFNGLGETSHADERSOURCEPROC F;
    if(!F)
        F = ( PFNGLGETSHADERSOURCEPROC ) mygetprocaddr("glGetShaderSource");
    if( glGetShaderSource_hook )
        glGetShaderSource_hook( shader_, bufSize_, length_, source_ );
    F(shader_, bufSize_, length_, source_);
}
static glGetShaderiv_hook_t glGetShaderiv_hook = 0;
glGetShaderiv_hook_t getHook_glGetShaderiv (){
    return glGetShaderiv_hook ;
}
void setHook_glGetShaderiv ( glGetShaderiv_hook_t hook ){
    glGetShaderiv_hook = hook;
}
void glGetShaderiv ( GLuint shader_, GLenum pname_, GLint * params_ ){
    static PFNGLGETSHADERIVPROC F;
    if(!F)
        F = ( PFNGLGETSHADERIVPROC ) mygetprocaddr("glGetShaderiv");
    if( glGetShaderiv_hook )
        glGetShaderiv_hook( shader_, pname_, params_ );
    F(shader_, pname_, params_);
}
static glGetString_hook_t glGetString_hook = 0;
glGetString_hook_t getHook_glGetString (){
    return glGetString_hook ;
}
void setHook_glGetString ( glGetString_hook_t hook ){
    glGetString_hook = hook;
}
const GLubyte * glGetString ( GLenum name_ ){
    static PFNGLGETSTRINGPROC F;
    if(!F)
        F = ( PFNGLGETSTRINGPROC ) mygetprocaddr("glGetString");
    if( glGetString_hook )
        glGetString_hook( name_ );
    const GLubyte * retval = F(name_);
    return retval;
}
static glGetStringi_hook_t glGetStringi_hook = 0;
glGetStringi_hook_t getHook_glGetStringi (){
    return glGetStringi_hook ;
}
void setHook_glGetStringi ( glGetStringi_hook_t hook ){
    glGetStringi_hook = hook;
}
const GLubyte * glGetStringi ( GLenum name_, GLuint index_ ){
    static PFNGLGETSTRINGIPROC F;
    if(!F)
        F = ( PFNGLGETSTRINGIPROC ) mygetprocaddr("glGetStringi");
    if( glGetStringi_hook )
        glGetStringi_hook( name_, index_ );
    const GLubyte * retval = F(name_, index_);
    return retval;
}
static glGetSubroutineIndex_hook_t glGetSubroutineIndex_hook = 0;
glGetSubroutineIndex_hook_t getHook_glGetSubroutineIndex (){
    return glGetSubroutineIndex_hook ;
}
void setHook_glGetSubroutineIndex ( glGetSubroutineIndex_hook_t hook ){
    glGetSubroutineIndex_hook = hook;
}
GLuint glGetSubroutineIndex ( GLuint program_, GLenum shadertype_, const GLchar * name_ ){
    static PFNGLGETSUBROUTINEINDEXPROC F;
    if(!F)
        F = ( PFNGLGETSUBROUTINEINDEXPROC ) mygetprocaddr("glGetSubroutineIndex");
    if( glGetSubroutineIndex_hook )
        glGetSubroutineIndex_hook( program_, shadertype_, name_ );
    GLuint retval = F(program_, shadertype_, name_);
    return retval;
}
static glGetSubroutineUniformLocation_hook_t glGetSubroutineUniformLocation_hook = 0;
glGetSubroutineUniformLocation_hook_t getHook_glGetSubroutineUniformLocation (){
    return glGetSubroutineUniformLocation_hook ;
}
void setHook_glGetSubroutineUniformLocation ( glGetSubroutineUniformLocation_hook_t hook ){
    glGetSubroutineUniformLocation_hook = hook;
}
GLint glGetSubroutineUniformLocation ( GLuint program_, GLenum shadertype_, const GLchar * name_ ){
    static PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC F;
    if(!F)
        F = ( PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC ) mygetprocaddr("glGetSubroutineUniformLocation");
    if( glGetSubroutineUniformLocation_hook )
        glGetSubroutineUniformLocation_hook( program_, shadertype_, name_ );
    GLint retval = F(program_, shadertype_, name_);
    return retval;
}
static glGetSynciv_hook_t glGetSynciv_hook = 0;
glGetSynciv_hook_t getHook_glGetSynciv (){
    return glGetSynciv_hook ;
}
void setHook_glGetSynciv ( glGetSynciv_hook_t hook ){
    glGetSynciv_hook = hook;
}
void glGetSynciv ( GLsync sync_, GLenum pname_, GLsizei bufSize_, GLsizei * length_, GLint * values_ ){
    static PFNGLGETSYNCIVPROC F;
    if(!F)
        F = ( PFNGLGETSYNCIVPROC ) mygetprocaddr("glGetSynciv");
    if( glGetSynciv_hook )
        glGetSynciv_hook( sync_, pname_, bufSize_, length_, values_ );
    F(sync_, pname_, bufSize_, length_, values_);
}
static glGetTexImage_hook_t glGetTexImage_hook = 0;
glGetTexImage_hook_t getHook_glGetTexImage (){
    return glGetTexImage_hook ;
}
void setHook_glGetTexImage ( glGetTexImage_hook_t hook ){
    glGetTexImage_hook = hook;
}
void glGetTexImage ( GLenum target_, GLint level_, GLenum format_, GLenum type_, void * pixels_ ){
    static PFNGLGETTEXIMAGEPROC F;
    if(!F)
        F = ( PFNGLGETTEXIMAGEPROC ) mygetprocaddr("glGetTexImage");
    if( glGetTexImage_hook )
        glGetTexImage_hook( target_, level_, format_, type_, pixels_ );
    F(target_, level_, format_, type_, pixels_);
}
static glGetTexLevelParameterfv_hook_t glGetTexLevelParameterfv_hook = 0;
glGetTexLevelParameterfv_hook_t getHook_glGetTexLevelParameterfv (){
    return glGetTexLevelParameterfv_hook ;
}
void setHook_glGetTexLevelParameterfv ( glGetTexLevelParameterfv_hook_t hook ){
    glGetTexLevelParameterfv_hook = hook;
}
void glGetTexLevelParameterfv ( GLenum target_, GLint level_, GLenum pname_, GLfloat * params_ ){
    static PFNGLGETTEXLEVELPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLGETTEXLEVELPARAMETERFVPROC ) mygetprocaddr("glGetTexLevelParameterfv");
    if( glGetTexLevelParameterfv_hook )
        glGetTexLevelParameterfv_hook( target_, level_, pname_, params_ );
    F(target_, level_, pname_, params_);
}
static glGetTexLevelParameteriv_hook_t glGetTexLevelParameteriv_hook = 0;
glGetTexLevelParameteriv_hook_t getHook_glGetTexLevelParameteriv (){
    return glGetTexLevelParameteriv_hook ;
}
void setHook_glGetTexLevelParameteriv ( glGetTexLevelParameteriv_hook_t hook ){
    glGetTexLevelParameteriv_hook = hook;
}
void glGetTexLevelParameteriv ( GLenum target_, GLint level_, GLenum pname_, GLint * params_ ){
    static PFNGLGETTEXLEVELPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETTEXLEVELPARAMETERIVPROC ) mygetprocaddr("glGetTexLevelParameteriv");
    if( glGetTexLevelParameteriv_hook )
        glGetTexLevelParameteriv_hook( target_, level_, pname_, params_ );
    F(target_, level_, pname_, params_);
}
static glGetTexParameterIiv_hook_t glGetTexParameterIiv_hook = 0;
glGetTexParameterIiv_hook_t getHook_glGetTexParameterIiv (){
    return glGetTexParameterIiv_hook ;
}
void setHook_glGetTexParameterIiv ( glGetTexParameterIiv_hook_t hook ){
    glGetTexParameterIiv_hook = hook;
}
void glGetTexParameterIiv ( GLenum target_, GLenum pname_, GLint * params_ ){
    static PFNGLGETTEXPARAMETERIIVPROC F;
    if(!F)
        F = ( PFNGLGETTEXPARAMETERIIVPROC ) mygetprocaddr("glGetTexParameterIiv");
    if( glGetTexParameterIiv_hook )
        glGetTexParameterIiv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetTexParameterIuiv_hook_t glGetTexParameterIuiv_hook = 0;
glGetTexParameterIuiv_hook_t getHook_glGetTexParameterIuiv (){
    return glGetTexParameterIuiv_hook ;
}
void setHook_glGetTexParameterIuiv ( glGetTexParameterIuiv_hook_t hook ){
    glGetTexParameterIuiv_hook = hook;
}
void glGetTexParameterIuiv ( GLenum target_, GLenum pname_, GLuint * params_ ){
    static PFNGLGETTEXPARAMETERIUIVPROC F;
    if(!F)
        F = ( PFNGLGETTEXPARAMETERIUIVPROC ) mygetprocaddr("glGetTexParameterIuiv");
    if( glGetTexParameterIuiv_hook )
        glGetTexParameterIuiv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetTexParameterfv_hook_t glGetTexParameterfv_hook = 0;
glGetTexParameterfv_hook_t getHook_glGetTexParameterfv (){
    return glGetTexParameterfv_hook ;
}
void setHook_glGetTexParameterfv ( glGetTexParameterfv_hook_t hook ){
    glGetTexParameterfv_hook = hook;
}
void glGetTexParameterfv ( GLenum target_, GLenum pname_, GLfloat * params_ ){
    static PFNGLGETTEXPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLGETTEXPARAMETERFVPROC ) mygetprocaddr("glGetTexParameterfv");
    if( glGetTexParameterfv_hook )
        glGetTexParameterfv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetTexParameteriv_hook_t glGetTexParameteriv_hook = 0;
glGetTexParameteriv_hook_t getHook_glGetTexParameteriv (){
    return glGetTexParameteriv_hook ;
}
void setHook_glGetTexParameteriv ( glGetTexParameteriv_hook_t hook ){
    glGetTexParameteriv_hook = hook;
}
void glGetTexParameteriv ( GLenum target_, GLenum pname_, GLint * params_ ){
    static PFNGLGETTEXPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETTEXPARAMETERIVPROC ) mygetprocaddr("glGetTexParameteriv");
    if( glGetTexParameteriv_hook )
        glGetTexParameteriv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glGetTextureImage_hook_t glGetTextureImage_hook = 0;
glGetTextureImage_hook_t getHook_glGetTextureImage (){
    return glGetTextureImage_hook ;
}
void setHook_glGetTextureImage ( glGetTextureImage_hook_t hook ){
    glGetTextureImage_hook = hook;
}
void glGetTextureImage ( GLuint texture_, GLint level_, GLenum format_, GLenum type_, GLsizei bufSize_, void * pixels_ ){
    static PFNGLGETTEXTUREIMAGEPROC F;
    if(!F)
        F = ( PFNGLGETTEXTUREIMAGEPROC ) mygetprocaddr("glGetTextureImage");
    if( glGetTextureImage_hook )
        glGetTextureImage_hook( texture_, level_, format_, type_, bufSize_, pixels_ );
    F(texture_, level_, format_, type_, bufSize_, pixels_);
}
static glGetTextureLevelParameterfv_hook_t glGetTextureLevelParameterfv_hook = 0;
glGetTextureLevelParameterfv_hook_t getHook_glGetTextureLevelParameterfv (){
    return glGetTextureLevelParameterfv_hook ;
}
void setHook_glGetTextureLevelParameterfv ( glGetTextureLevelParameterfv_hook_t hook ){
    glGetTextureLevelParameterfv_hook = hook;
}
void glGetTextureLevelParameterfv ( GLuint texture_, GLint level_, GLenum pname_, GLfloat * params_ ){
    static PFNGLGETTEXTURELEVELPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLGETTEXTURELEVELPARAMETERFVPROC ) mygetprocaddr("glGetTextureLevelParameterfv");
    if( glGetTextureLevelParameterfv_hook )
        glGetTextureLevelParameterfv_hook( texture_, level_, pname_, params_ );
    F(texture_, level_, pname_, params_);
}
static glGetTextureLevelParameteriv_hook_t glGetTextureLevelParameteriv_hook = 0;
glGetTextureLevelParameteriv_hook_t getHook_glGetTextureLevelParameteriv (){
    return glGetTextureLevelParameteriv_hook ;
}
void setHook_glGetTextureLevelParameteriv ( glGetTextureLevelParameteriv_hook_t hook ){
    glGetTextureLevelParameteriv_hook = hook;
}
void glGetTextureLevelParameteriv ( GLuint texture_, GLint level_, GLenum pname_, GLint * params_ ){
    static PFNGLGETTEXTURELEVELPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETTEXTURELEVELPARAMETERIVPROC ) mygetprocaddr("glGetTextureLevelParameteriv");
    if( glGetTextureLevelParameteriv_hook )
        glGetTextureLevelParameteriv_hook( texture_, level_, pname_, params_ );
    F(texture_, level_, pname_, params_);
}
static glGetTextureParameterIiv_hook_t glGetTextureParameterIiv_hook = 0;
glGetTextureParameterIiv_hook_t getHook_glGetTextureParameterIiv (){
    return glGetTextureParameterIiv_hook ;
}
void setHook_glGetTextureParameterIiv ( glGetTextureParameterIiv_hook_t hook ){
    glGetTextureParameterIiv_hook = hook;
}
void glGetTextureParameterIiv ( GLuint texture_, GLenum pname_, GLint * params_ ){
    static PFNGLGETTEXTUREPARAMETERIIVPROC F;
    if(!F)
        F = ( PFNGLGETTEXTUREPARAMETERIIVPROC ) mygetprocaddr("glGetTextureParameterIiv");
    if( glGetTextureParameterIiv_hook )
        glGetTextureParameterIiv_hook( texture_, pname_, params_ );
    F(texture_, pname_, params_);
}
static glGetTextureParameterIuiv_hook_t glGetTextureParameterIuiv_hook = 0;
glGetTextureParameterIuiv_hook_t getHook_glGetTextureParameterIuiv (){
    return glGetTextureParameterIuiv_hook ;
}
void setHook_glGetTextureParameterIuiv ( glGetTextureParameterIuiv_hook_t hook ){
    glGetTextureParameterIuiv_hook = hook;
}
void glGetTextureParameterIuiv ( GLuint texture_, GLenum pname_, GLuint * params_ ){
    static PFNGLGETTEXTUREPARAMETERIUIVPROC F;
    if(!F)
        F = ( PFNGLGETTEXTUREPARAMETERIUIVPROC ) mygetprocaddr("glGetTextureParameterIuiv");
    if( glGetTextureParameterIuiv_hook )
        glGetTextureParameterIuiv_hook( texture_, pname_, params_ );
    F(texture_, pname_, params_);
}
static glGetTextureParameterfv_hook_t glGetTextureParameterfv_hook = 0;
glGetTextureParameterfv_hook_t getHook_glGetTextureParameterfv (){
    return glGetTextureParameterfv_hook ;
}
void setHook_glGetTextureParameterfv ( glGetTextureParameterfv_hook_t hook ){
    glGetTextureParameterfv_hook = hook;
}
void glGetTextureParameterfv ( GLuint texture_, GLenum pname_, GLfloat * params_ ){
    static PFNGLGETTEXTUREPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLGETTEXTUREPARAMETERFVPROC ) mygetprocaddr("glGetTextureParameterfv");
    if( glGetTextureParameterfv_hook )
        glGetTextureParameterfv_hook( texture_, pname_, params_ );
    F(texture_, pname_, params_);
}
static glGetTextureParameteriv_hook_t glGetTextureParameteriv_hook = 0;
glGetTextureParameteriv_hook_t getHook_glGetTextureParameteriv (){
    return glGetTextureParameteriv_hook ;
}
void setHook_glGetTextureParameteriv ( glGetTextureParameteriv_hook_t hook ){
    glGetTextureParameteriv_hook = hook;
}
void glGetTextureParameteriv ( GLuint texture_, GLenum pname_, GLint * params_ ){
    static PFNGLGETTEXTUREPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLGETTEXTUREPARAMETERIVPROC ) mygetprocaddr("glGetTextureParameteriv");
    if( glGetTextureParameteriv_hook )
        glGetTextureParameteriv_hook( texture_, pname_, params_ );
    F(texture_, pname_, params_);
}
static glGetTextureSubImage_hook_t glGetTextureSubImage_hook = 0;
glGetTextureSubImage_hook_t getHook_glGetTextureSubImage (){
    return glGetTextureSubImage_hook ;
}
void setHook_glGetTextureSubImage ( glGetTextureSubImage_hook_t hook ){
    glGetTextureSubImage_hook = hook;
}
void glGetTextureSubImage ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLsizei width_, GLsizei height_, GLsizei depth_, GLenum format_, GLenum type_, GLsizei bufSize_, void * pixels_ ){
    static PFNGLGETTEXTURESUBIMAGEPROC F;
    if(!F)
        F = ( PFNGLGETTEXTURESUBIMAGEPROC ) mygetprocaddr("glGetTextureSubImage");
    if( glGetTextureSubImage_hook )
        glGetTextureSubImage_hook( texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, type_, bufSize_, pixels_ );
    F(texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, type_, bufSize_, pixels_);
}
static glGetTransformFeedbackVarying_hook_t glGetTransformFeedbackVarying_hook = 0;
glGetTransformFeedbackVarying_hook_t getHook_glGetTransformFeedbackVarying (){
    return glGetTransformFeedbackVarying_hook ;
}
void setHook_glGetTransformFeedbackVarying ( glGetTransformFeedbackVarying_hook_t hook ){
    glGetTransformFeedbackVarying_hook = hook;
}
void glGetTransformFeedbackVarying ( GLuint program_, GLuint index_, GLsizei bufSize_, GLsizei * length_, GLsizei * size_, GLenum * type_, GLchar * name_ ){
    static PFNGLGETTRANSFORMFEEDBACKVARYINGPROC F;
    if(!F)
        F = ( PFNGLGETTRANSFORMFEEDBACKVARYINGPROC ) mygetprocaddr("glGetTransformFeedbackVarying");
    if( glGetTransformFeedbackVarying_hook )
        glGetTransformFeedbackVarying_hook( program_, index_, bufSize_, length_, size_, type_, name_ );
    F(program_, index_, bufSize_, length_, size_, type_, name_);
}
static glGetTransformFeedbacki64_v_hook_t glGetTransformFeedbacki64_v_hook = 0;
glGetTransformFeedbacki64_v_hook_t getHook_glGetTransformFeedbacki64_v (){
    return glGetTransformFeedbacki64_v_hook ;
}
void setHook_glGetTransformFeedbacki64_v ( glGetTransformFeedbacki64_v_hook_t hook ){
    glGetTransformFeedbacki64_v_hook = hook;
}
void glGetTransformFeedbacki64_v ( GLuint xfb_, GLenum pname_, GLuint index_, GLint64 * param_ ){
    static PFNGLGETTRANSFORMFEEDBACKI64_VPROC F;
    if(!F)
        F = ( PFNGLGETTRANSFORMFEEDBACKI64_VPROC ) mygetprocaddr("glGetTransformFeedbacki64_v");
    if( glGetTransformFeedbacki64_v_hook )
        glGetTransformFeedbacki64_v_hook( xfb_, pname_, index_, param_ );
    F(xfb_, pname_, index_, param_);
}
static glGetTransformFeedbacki_v_hook_t glGetTransformFeedbacki_v_hook = 0;
glGetTransformFeedbacki_v_hook_t getHook_glGetTransformFeedbacki_v (){
    return glGetTransformFeedbacki_v_hook ;
}
void setHook_glGetTransformFeedbacki_v ( glGetTransformFeedbacki_v_hook_t hook ){
    glGetTransformFeedbacki_v_hook = hook;
}
void glGetTransformFeedbacki_v ( GLuint xfb_, GLenum pname_, GLuint index_, GLint * param_ ){
    static PFNGLGETTRANSFORMFEEDBACKI_VPROC F;
    if(!F)
        F = ( PFNGLGETTRANSFORMFEEDBACKI_VPROC ) mygetprocaddr("glGetTransformFeedbacki_v");
    if( glGetTransformFeedbacki_v_hook )
        glGetTransformFeedbacki_v_hook( xfb_, pname_, index_, param_ );
    F(xfb_, pname_, index_, param_);
}
static glGetTransformFeedbackiv_hook_t glGetTransformFeedbackiv_hook = 0;
glGetTransformFeedbackiv_hook_t getHook_glGetTransformFeedbackiv (){
    return glGetTransformFeedbackiv_hook ;
}
void setHook_glGetTransformFeedbackiv ( glGetTransformFeedbackiv_hook_t hook ){
    glGetTransformFeedbackiv_hook = hook;
}
void glGetTransformFeedbackiv ( GLuint xfb_, GLenum pname_, GLint * param_ ){
    static PFNGLGETTRANSFORMFEEDBACKIVPROC F;
    if(!F)
        F = ( PFNGLGETTRANSFORMFEEDBACKIVPROC ) mygetprocaddr("glGetTransformFeedbackiv");
    if( glGetTransformFeedbackiv_hook )
        glGetTransformFeedbackiv_hook( xfb_, pname_, param_ );
    F(xfb_, pname_, param_);
}
static glGetUniformBlockIndex_hook_t glGetUniformBlockIndex_hook = 0;
glGetUniformBlockIndex_hook_t getHook_glGetUniformBlockIndex (){
    return glGetUniformBlockIndex_hook ;
}
void setHook_glGetUniformBlockIndex ( glGetUniformBlockIndex_hook_t hook ){
    glGetUniformBlockIndex_hook = hook;
}
GLuint glGetUniformBlockIndex ( GLuint program_, const GLchar * uniformBlockName_ ){
    static PFNGLGETUNIFORMBLOCKINDEXPROC F;
    if(!F)
        F = ( PFNGLGETUNIFORMBLOCKINDEXPROC ) mygetprocaddr("glGetUniformBlockIndex");
    if( glGetUniformBlockIndex_hook )
        glGetUniformBlockIndex_hook( program_, uniformBlockName_ );
    GLuint retval = F(program_, uniformBlockName_);
    return retval;
}
static glGetUniformIndices_hook_t glGetUniformIndices_hook = 0;
glGetUniformIndices_hook_t getHook_glGetUniformIndices (){
    return glGetUniformIndices_hook ;
}
void setHook_glGetUniformIndices ( glGetUniformIndices_hook_t hook ){
    glGetUniformIndices_hook = hook;
}
void glGetUniformIndices ( GLuint program_, GLsizei uniformCount_, const GLchar ** uniformNames_, GLuint * uniformIndices_ ){
    static PFNGLGETUNIFORMINDICESPROC F;
    if(!F)
        F = ( PFNGLGETUNIFORMINDICESPROC ) mygetprocaddr("glGetUniformIndices");
    if( glGetUniformIndices_hook )
        glGetUniformIndices_hook( program_, uniformCount_, uniformNames_, uniformIndices_ );
    F(program_, uniformCount_, uniformNames_, uniformIndices_);
}
static glGetUniformLocation_hook_t glGetUniformLocation_hook = 0;
glGetUniformLocation_hook_t getHook_glGetUniformLocation (){
    return glGetUniformLocation_hook ;
}
void setHook_glGetUniformLocation ( glGetUniformLocation_hook_t hook ){
    glGetUniformLocation_hook = hook;
}
GLint glGetUniformLocation ( GLuint program_, const GLchar * name_ ){
    static PFNGLGETUNIFORMLOCATIONPROC F;
    if(!F)
        F = ( PFNGLGETUNIFORMLOCATIONPROC ) mygetprocaddr("glGetUniformLocation");
    if( glGetUniformLocation_hook )
        glGetUniformLocation_hook( program_, name_ );
    GLint retval = F(program_, name_);
    return retval;
}
static glGetUniformSubroutineuiv_hook_t glGetUniformSubroutineuiv_hook = 0;
glGetUniformSubroutineuiv_hook_t getHook_glGetUniformSubroutineuiv (){
    return glGetUniformSubroutineuiv_hook ;
}
void setHook_glGetUniformSubroutineuiv ( glGetUniformSubroutineuiv_hook_t hook ){
    glGetUniformSubroutineuiv_hook = hook;
}
void glGetUniformSubroutineuiv ( GLenum shadertype_, GLint location_, GLuint * params_ ){
    static PFNGLGETUNIFORMSUBROUTINEUIVPROC F;
    if(!F)
        F = ( PFNGLGETUNIFORMSUBROUTINEUIVPROC ) mygetprocaddr("glGetUniformSubroutineuiv");
    if( glGetUniformSubroutineuiv_hook )
        glGetUniformSubroutineuiv_hook( shadertype_, location_, params_ );
    F(shadertype_, location_, params_);
}
static glGetUniformdv_hook_t glGetUniformdv_hook = 0;
glGetUniformdv_hook_t getHook_glGetUniformdv (){
    return glGetUniformdv_hook ;
}
void setHook_glGetUniformdv ( glGetUniformdv_hook_t hook ){
    glGetUniformdv_hook = hook;
}
void glGetUniformdv ( GLuint program_, GLint location_, GLdouble * params_ ){
    static PFNGLGETUNIFORMDVPROC F;
    if(!F)
        F = ( PFNGLGETUNIFORMDVPROC ) mygetprocaddr("glGetUniformdv");
    if( glGetUniformdv_hook )
        glGetUniformdv_hook( program_, location_, params_ );
    F(program_, location_, params_);
}
static glGetUniformfv_hook_t glGetUniformfv_hook = 0;
glGetUniformfv_hook_t getHook_glGetUniformfv (){
    return glGetUniformfv_hook ;
}
void setHook_glGetUniformfv ( glGetUniformfv_hook_t hook ){
    glGetUniformfv_hook = hook;
}
void glGetUniformfv ( GLuint program_, GLint location_, GLfloat * params_ ){
    static PFNGLGETUNIFORMFVPROC F;
    if(!F)
        F = ( PFNGLGETUNIFORMFVPROC ) mygetprocaddr("glGetUniformfv");
    if( glGetUniformfv_hook )
        glGetUniformfv_hook( program_, location_, params_ );
    F(program_, location_, params_);
}
static glGetUniformiv_hook_t glGetUniformiv_hook = 0;
glGetUniformiv_hook_t getHook_glGetUniformiv (){
    return glGetUniformiv_hook ;
}
void setHook_glGetUniformiv ( glGetUniformiv_hook_t hook ){
    glGetUniformiv_hook = hook;
}
void glGetUniformiv ( GLuint program_, GLint location_, GLint * params_ ){
    static PFNGLGETUNIFORMIVPROC F;
    if(!F)
        F = ( PFNGLGETUNIFORMIVPROC ) mygetprocaddr("glGetUniformiv");
    if( glGetUniformiv_hook )
        glGetUniformiv_hook( program_, location_, params_ );
    F(program_, location_, params_);
}
static glGetUniformuiv_hook_t glGetUniformuiv_hook = 0;
glGetUniformuiv_hook_t getHook_glGetUniformuiv (){
    return glGetUniformuiv_hook ;
}
void setHook_glGetUniformuiv ( glGetUniformuiv_hook_t hook ){
    glGetUniformuiv_hook = hook;
}
void glGetUniformuiv ( GLuint program_, GLint location_, GLuint * params_ ){
    static PFNGLGETUNIFORMUIVPROC F;
    if(!F)
        F = ( PFNGLGETUNIFORMUIVPROC ) mygetprocaddr("glGetUniformuiv");
    if( glGetUniformuiv_hook )
        glGetUniformuiv_hook( program_, location_, params_ );
    F(program_, location_, params_);
}
static glGetVertexArrayIndexed64iv_hook_t glGetVertexArrayIndexed64iv_hook = 0;
glGetVertexArrayIndexed64iv_hook_t getHook_glGetVertexArrayIndexed64iv (){
    return glGetVertexArrayIndexed64iv_hook ;
}
void setHook_glGetVertexArrayIndexed64iv ( glGetVertexArrayIndexed64iv_hook_t hook ){
    glGetVertexArrayIndexed64iv_hook = hook;
}
void glGetVertexArrayIndexed64iv ( GLuint vaobj_, GLuint index_, GLenum pname_, GLint64 * param_ ){
    static PFNGLGETVERTEXARRAYINDEXED64IVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXARRAYINDEXED64IVPROC ) mygetprocaddr("glGetVertexArrayIndexed64iv");
    if( glGetVertexArrayIndexed64iv_hook )
        glGetVertexArrayIndexed64iv_hook( vaobj_, index_, pname_, param_ );
    F(vaobj_, index_, pname_, param_);
}
static glGetVertexArrayIndexediv_hook_t glGetVertexArrayIndexediv_hook = 0;
glGetVertexArrayIndexediv_hook_t getHook_glGetVertexArrayIndexediv (){
    return glGetVertexArrayIndexediv_hook ;
}
void setHook_glGetVertexArrayIndexediv ( glGetVertexArrayIndexediv_hook_t hook ){
    glGetVertexArrayIndexediv_hook = hook;
}
void glGetVertexArrayIndexediv ( GLuint vaobj_, GLuint index_, GLenum pname_, GLint * param_ ){
    static PFNGLGETVERTEXARRAYINDEXEDIVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXARRAYINDEXEDIVPROC ) mygetprocaddr("glGetVertexArrayIndexediv");
    if( glGetVertexArrayIndexediv_hook )
        glGetVertexArrayIndexediv_hook( vaobj_, index_, pname_, param_ );
    F(vaobj_, index_, pname_, param_);
}
static glGetVertexArrayiv_hook_t glGetVertexArrayiv_hook = 0;
glGetVertexArrayiv_hook_t getHook_glGetVertexArrayiv (){
    return glGetVertexArrayiv_hook ;
}
void setHook_glGetVertexArrayiv ( glGetVertexArrayiv_hook_t hook ){
    glGetVertexArrayiv_hook = hook;
}
void glGetVertexArrayiv ( GLuint vaobj_, GLenum pname_, GLint * param_ ){
    static PFNGLGETVERTEXARRAYIVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXARRAYIVPROC ) mygetprocaddr("glGetVertexArrayiv");
    if( glGetVertexArrayiv_hook )
        glGetVertexArrayiv_hook( vaobj_, pname_, param_ );
    F(vaobj_, pname_, param_);
}
static glGetVertexAttribIiv_hook_t glGetVertexAttribIiv_hook = 0;
glGetVertexAttribIiv_hook_t getHook_glGetVertexAttribIiv (){
    return glGetVertexAttribIiv_hook ;
}
void setHook_glGetVertexAttribIiv ( glGetVertexAttribIiv_hook_t hook ){
    glGetVertexAttribIiv_hook = hook;
}
void glGetVertexAttribIiv ( GLuint index_, GLenum pname_, GLint * params_ ){
    static PFNGLGETVERTEXATTRIBIIVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXATTRIBIIVPROC ) mygetprocaddr("glGetVertexAttribIiv");
    if( glGetVertexAttribIiv_hook )
        glGetVertexAttribIiv_hook( index_, pname_, params_ );
    F(index_, pname_, params_);
}
static glGetVertexAttribIuiv_hook_t glGetVertexAttribIuiv_hook = 0;
glGetVertexAttribIuiv_hook_t getHook_glGetVertexAttribIuiv (){
    return glGetVertexAttribIuiv_hook ;
}
void setHook_glGetVertexAttribIuiv ( glGetVertexAttribIuiv_hook_t hook ){
    glGetVertexAttribIuiv_hook = hook;
}
void glGetVertexAttribIuiv ( GLuint index_, GLenum pname_, GLuint * params_ ){
    static PFNGLGETVERTEXATTRIBIUIVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXATTRIBIUIVPROC ) mygetprocaddr("glGetVertexAttribIuiv");
    if( glGetVertexAttribIuiv_hook )
        glGetVertexAttribIuiv_hook( index_, pname_, params_ );
    F(index_, pname_, params_);
}
static glGetVertexAttribLdv_hook_t glGetVertexAttribLdv_hook = 0;
glGetVertexAttribLdv_hook_t getHook_glGetVertexAttribLdv (){
    return glGetVertexAttribLdv_hook ;
}
void setHook_glGetVertexAttribLdv ( glGetVertexAttribLdv_hook_t hook ){
    glGetVertexAttribLdv_hook = hook;
}
void glGetVertexAttribLdv ( GLuint index_, GLenum pname_, GLdouble * params_ ){
    static PFNGLGETVERTEXATTRIBLDVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXATTRIBLDVPROC ) mygetprocaddr("glGetVertexAttribLdv");
    if( glGetVertexAttribLdv_hook )
        glGetVertexAttribLdv_hook( index_, pname_, params_ );
    F(index_, pname_, params_);
}
static glGetVertexAttribPointerv_hook_t glGetVertexAttribPointerv_hook = 0;
glGetVertexAttribPointerv_hook_t getHook_glGetVertexAttribPointerv (){
    return glGetVertexAttribPointerv_hook ;
}
void setHook_glGetVertexAttribPointerv ( glGetVertexAttribPointerv_hook_t hook ){
    glGetVertexAttribPointerv_hook = hook;
}
void glGetVertexAttribPointerv ( GLuint index_, GLenum pname_, void ** pointer_ ){
    static PFNGLGETVERTEXATTRIBPOINTERVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXATTRIBPOINTERVPROC ) mygetprocaddr("glGetVertexAttribPointerv");
    if( glGetVertexAttribPointerv_hook )
        glGetVertexAttribPointerv_hook( index_, pname_, pointer_ );
    F(index_, pname_, pointer_);
}
static glGetVertexAttribdv_hook_t glGetVertexAttribdv_hook = 0;
glGetVertexAttribdv_hook_t getHook_glGetVertexAttribdv (){
    return glGetVertexAttribdv_hook ;
}
void setHook_glGetVertexAttribdv ( glGetVertexAttribdv_hook_t hook ){
    glGetVertexAttribdv_hook = hook;
}
void glGetVertexAttribdv ( GLuint index_, GLenum pname_, GLdouble * params_ ){
    static PFNGLGETVERTEXATTRIBDVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXATTRIBDVPROC ) mygetprocaddr("glGetVertexAttribdv");
    if( glGetVertexAttribdv_hook )
        glGetVertexAttribdv_hook( index_, pname_, params_ );
    F(index_, pname_, params_);
}
static glGetVertexAttribfv_hook_t glGetVertexAttribfv_hook = 0;
glGetVertexAttribfv_hook_t getHook_glGetVertexAttribfv (){
    return glGetVertexAttribfv_hook ;
}
void setHook_glGetVertexAttribfv ( glGetVertexAttribfv_hook_t hook ){
    glGetVertexAttribfv_hook = hook;
}
void glGetVertexAttribfv ( GLuint index_, GLenum pname_, GLfloat * params_ ){
    static PFNGLGETVERTEXATTRIBFVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXATTRIBFVPROC ) mygetprocaddr("glGetVertexAttribfv");
    if( glGetVertexAttribfv_hook )
        glGetVertexAttribfv_hook( index_, pname_, params_ );
    F(index_, pname_, params_);
}
static glGetVertexAttribiv_hook_t glGetVertexAttribiv_hook = 0;
glGetVertexAttribiv_hook_t getHook_glGetVertexAttribiv (){
    return glGetVertexAttribiv_hook ;
}
void setHook_glGetVertexAttribiv ( glGetVertexAttribiv_hook_t hook ){
    glGetVertexAttribiv_hook = hook;
}
void glGetVertexAttribiv ( GLuint index_, GLenum pname_, GLint * params_ ){
    static PFNGLGETVERTEXATTRIBIVPROC F;
    if(!F)
        F = ( PFNGLGETVERTEXATTRIBIVPROC ) mygetprocaddr("glGetVertexAttribiv");
    if( glGetVertexAttribiv_hook )
        glGetVertexAttribiv_hook( index_, pname_, params_ );
    F(index_, pname_, params_);
}
static glGetnCompressedTexImage_hook_t glGetnCompressedTexImage_hook = 0;
glGetnCompressedTexImage_hook_t getHook_glGetnCompressedTexImage (){
    return glGetnCompressedTexImage_hook ;
}
void setHook_glGetnCompressedTexImage ( glGetnCompressedTexImage_hook_t hook ){
    glGetnCompressedTexImage_hook = hook;
}
void glGetnCompressedTexImage ( GLenum target_, GLint lod_, GLsizei bufSize_, void * pixels_ ){
    static PFNGLGETNCOMPRESSEDTEXIMAGEPROC F;
    if(!F)
        F = ( PFNGLGETNCOMPRESSEDTEXIMAGEPROC ) mygetprocaddr("glGetnCompressedTexImage");
    if( glGetnCompressedTexImage_hook )
        glGetnCompressedTexImage_hook( target_, lod_, bufSize_, pixels_ );
    F(target_, lod_, bufSize_, pixels_);
}
static glGetnTexImage_hook_t glGetnTexImage_hook = 0;
glGetnTexImage_hook_t getHook_glGetnTexImage (){
    return glGetnTexImage_hook ;
}
void setHook_glGetnTexImage ( glGetnTexImage_hook_t hook ){
    glGetnTexImage_hook = hook;
}
void glGetnTexImage ( GLenum target_, GLint level_, GLenum format_, GLenum type_, GLsizei bufSize_, void * pixels_ ){
    static PFNGLGETNTEXIMAGEPROC F;
    if(!F)
        F = ( PFNGLGETNTEXIMAGEPROC ) mygetprocaddr("glGetnTexImage");
    if( glGetnTexImage_hook )
        glGetnTexImage_hook( target_, level_, format_, type_, bufSize_, pixels_ );
    F(target_, level_, format_, type_, bufSize_, pixels_);
}
static glGetnUniformdv_hook_t glGetnUniformdv_hook = 0;
glGetnUniformdv_hook_t getHook_glGetnUniformdv (){
    return glGetnUniformdv_hook ;
}
void setHook_glGetnUniformdv ( glGetnUniformdv_hook_t hook ){
    glGetnUniformdv_hook = hook;
}
void glGetnUniformdv ( GLuint program_, GLint location_, GLsizei bufSize_, GLdouble * params_ ){
    static PFNGLGETNUNIFORMDVPROC F;
    if(!F)
        F = ( PFNGLGETNUNIFORMDVPROC ) mygetprocaddr("glGetnUniformdv");
    if( glGetnUniformdv_hook )
        glGetnUniformdv_hook( program_, location_, bufSize_, params_ );
    F(program_, location_, bufSize_, params_);
}
static glGetnUniformfv_hook_t glGetnUniformfv_hook = 0;
glGetnUniformfv_hook_t getHook_glGetnUniformfv (){
    return glGetnUniformfv_hook ;
}
void setHook_glGetnUniformfv ( glGetnUniformfv_hook_t hook ){
    glGetnUniformfv_hook = hook;
}
void glGetnUniformfv ( GLuint program_, GLint location_, GLsizei bufSize_, GLfloat * params_ ){
    static PFNGLGETNUNIFORMFVPROC F;
    if(!F)
        F = ( PFNGLGETNUNIFORMFVPROC ) mygetprocaddr("glGetnUniformfv");
    if( glGetnUniformfv_hook )
        glGetnUniformfv_hook( program_, location_, bufSize_, params_ );
    F(program_, location_, bufSize_, params_);
}
static glGetnUniformiv_hook_t glGetnUniformiv_hook = 0;
glGetnUniformiv_hook_t getHook_glGetnUniformiv (){
    return glGetnUniformiv_hook ;
}
void setHook_glGetnUniformiv ( glGetnUniformiv_hook_t hook ){
    glGetnUniformiv_hook = hook;
}
void glGetnUniformiv ( GLuint program_, GLint location_, GLsizei bufSize_, GLint * params_ ){
    static PFNGLGETNUNIFORMIVPROC F;
    if(!F)
        F = ( PFNGLGETNUNIFORMIVPROC ) mygetprocaddr("glGetnUniformiv");
    if( glGetnUniformiv_hook )
        glGetnUniformiv_hook( program_, location_, bufSize_, params_ );
    F(program_, location_, bufSize_, params_);
}
static glGetnUniformuiv_hook_t glGetnUniformuiv_hook = 0;
glGetnUniformuiv_hook_t getHook_glGetnUniformuiv (){
    return glGetnUniformuiv_hook ;
}
void setHook_glGetnUniformuiv ( glGetnUniformuiv_hook_t hook ){
    glGetnUniformuiv_hook = hook;
}
void glGetnUniformuiv ( GLuint program_, GLint location_, GLsizei bufSize_, GLuint * params_ ){
    static PFNGLGETNUNIFORMUIVPROC F;
    if(!F)
        F = ( PFNGLGETNUNIFORMUIVPROC ) mygetprocaddr("glGetnUniformuiv");
    if( glGetnUniformuiv_hook )
        glGetnUniformuiv_hook( program_, location_, bufSize_, params_ );
    F(program_, location_, bufSize_, params_);
}
static glHint_hook_t glHint_hook = 0;
glHint_hook_t getHook_glHint (){
    return glHint_hook ;
}
void setHook_glHint ( glHint_hook_t hook ){
    glHint_hook = hook;
}
void glHint ( GLenum target_, GLenum mode_ ){
    static PFNGLHINTPROC F;
    if(!F)
        F = ( PFNGLHINTPROC ) mygetprocaddr("glHint");
    if( glHint_hook )
        glHint_hook( target_, mode_ );
    F(target_, mode_);
}
static glInvalidateBufferData_hook_t glInvalidateBufferData_hook = 0;
glInvalidateBufferData_hook_t getHook_glInvalidateBufferData (){
    return glInvalidateBufferData_hook ;
}
void setHook_glInvalidateBufferData ( glInvalidateBufferData_hook_t hook ){
    glInvalidateBufferData_hook = hook;
}
void glInvalidateBufferData ( GLuint buffer_ ){
    static PFNGLINVALIDATEBUFFERDATAPROC F;
    if(!F)
        F = ( PFNGLINVALIDATEBUFFERDATAPROC ) mygetprocaddr("glInvalidateBufferData");
    if( glInvalidateBufferData_hook )
        glInvalidateBufferData_hook( buffer_ );
    F(buffer_);
}
static glInvalidateBufferSubData_hook_t glInvalidateBufferSubData_hook = 0;
glInvalidateBufferSubData_hook_t getHook_glInvalidateBufferSubData (){
    return glInvalidateBufferSubData_hook ;
}
void setHook_glInvalidateBufferSubData ( glInvalidateBufferSubData_hook_t hook ){
    glInvalidateBufferSubData_hook = hook;
}
void glInvalidateBufferSubData ( GLuint buffer_, GLintptr offset_, GLsizeiptr length_ ){
    static PFNGLINVALIDATEBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLINVALIDATEBUFFERSUBDATAPROC ) mygetprocaddr("glInvalidateBufferSubData");
    if( glInvalidateBufferSubData_hook )
        glInvalidateBufferSubData_hook( buffer_, offset_, length_ );
    F(buffer_, offset_, length_);
}
static glInvalidateFramebuffer_hook_t glInvalidateFramebuffer_hook = 0;
glInvalidateFramebuffer_hook_t getHook_glInvalidateFramebuffer (){
    return glInvalidateFramebuffer_hook ;
}
void setHook_glInvalidateFramebuffer ( glInvalidateFramebuffer_hook_t hook ){
    glInvalidateFramebuffer_hook = hook;
}
void glInvalidateFramebuffer ( GLenum target_, GLsizei numAttachments_, const GLenum * attachments_ ){
    static PFNGLINVALIDATEFRAMEBUFFERPROC F;
    if(!F)
        F = ( PFNGLINVALIDATEFRAMEBUFFERPROC ) mygetprocaddr("glInvalidateFramebuffer");
    if( glInvalidateFramebuffer_hook )
        glInvalidateFramebuffer_hook( target_, numAttachments_, attachments_ );
    F(target_, numAttachments_, attachments_);
}
static glInvalidateNamedFramebufferData_hook_t glInvalidateNamedFramebufferData_hook = 0;
glInvalidateNamedFramebufferData_hook_t getHook_glInvalidateNamedFramebufferData (){
    return glInvalidateNamedFramebufferData_hook ;
}
void setHook_glInvalidateNamedFramebufferData ( glInvalidateNamedFramebufferData_hook_t hook ){
    glInvalidateNamedFramebufferData_hook = hook;
}
void glInvalidateNamedFramebufferData ( GLuint framebuffer_, GLsizei numAttachments_, const GLenum * attachments_ ){
    static PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC F;
    if(!F)
        F = ( PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC ) mygetprocaddr("glInvalidateNamedFramebufferData");
    if( glInvalidateNamedFramebufferData_hook )
        glInvalidateNamedFramebufferData_hook( framebuffer_, numAttachments_, attachments_ );
    F(framebuffer_, numAttachments_, attachments_);
}
static glInvalidateNamedFramebufferSubData_hook_t glInvalidateNamedFramebufferSubData_hook = 0;
glInvalidateNamedFramebufferSubData_hook_t getHook_glInvalidateNamedFramebufferSubData (){
    return glInvalidateNamedFramebufferSubData_hook ;
}
void setHook_glInvalidateNamedFramebufferSubData ( glInvalidateNamedFramebufferSubData_hook_t hook ){
    glInvalidateNamedFramebufferSubData_hook = hook;
}
void glInvalidateNamedFramebufferSubData ( GLuint framebuffer_, GLsizei numAttachments_, const GLenum * attachments_, GLint x_, GLint y_, GLsizei width_, GLsizei height_ ){
    static PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC ) mygetprocaddr("glInvalidateNamedFramebufferSubData");
    if( glInvalidateNamedFramebufferSubData_hook )
        glInvalidateNamedFramebufferSubData_hook( framebuffer_, numAttachments_, attachments_, x_, y_, width_, height_ );
    F(framebuffer_, numAttachments_, attachments_, x_, y_, width_, height_);
}
static glInvalidateSubFramebuffer_hook_t glInvalidateSubFramebuffer_hook = 0;
glInvalidateSubFramebuffer_hook_t getHook_glInvalidateSubFramebuffer (){
    return glInvalidateSubFramebuffer_hook ;
}
void setHook_glInvalidateSubFramebuffer ( glInvalidateSubFramebuffer_hook_t hook ){
    glInvalidateSubFramebuffer_hook = hook;
}
void glInvalidateSubFramebuffer ( GLenum target_, GLsizei numAttachments_, const GLenum * attachments_, GLint x_, GLint y_, GLsizei width_, GLsizei height_ ){
    static PFNGLINVALIDATESUBFRAMEBUFFERPROC F;
    if(!F)
        F = ( PFNGLINVALIDATESUBFRAMEBUFFERPROC ) mygetprocaddr("glInvalidateSubFramebuffer");
    if( glInvalidateSubFramebuffer_hook )
        glInvalidateSubFramebuffer_hook( target_, numAttachments_, attachments_, x_, y_, width_, height_ );
    F(target_, numAttachments_, attachments_, x_, y_, width_, height_);
}
static glInvalidateTexImage_hook_t glInvalidateTexImage_hook = 0;
glInvalidateTexImage_hook_t getHook_glInvalidateTexImage (){
    return glInvalidateTexImage_hook ;
}
void setHook_glInvalidateTexImage ( glInvalidateTexImage_hook_t hook ){
    glInvalidateTexImage_hook = hook;
}
void glInvalidateTexImage ( GLuint texture_, GLint level_ ){
    static PFNGLINVALIDATETEXIMAGEPROC F;
    if(!F)
        F = ( PFNGLINVALIDATETEXIMAGEPROC ) mygetprocaddr("glInvalidateTexImage");
    if( glInvalidateTexImage_hook )
        glInvalidateTexImage_hook( texture_, level_ );
    F(texture_, level_);
}
static glInvalidateTexSubImage_hook_t glInvalidateTexSubImage_hook = 0;
glInvalidateTexSubImage_hook_t getHook_glInvalidateTexSubImage (){
    return glInvalidateTexSubImage_hook ;
}
void setHook_glInvalidateTexSubImage ( glInvalidateTexSubImage_hook_t hook ){
    glInvalidateTexSubImage_hook = hook;
}
void glInvalidateTexSubImage ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLsizei width_, GLsizei height_, GLsizei depth_ ){
    static PFNGLINVALIDATETEXSUBIMAGEPROC F;
    if(!F)
        F = ( PFNGLINVALIDATETEXSUBIMAGEPROC ) mygetprocaddr("glInvalidateTexSubImage");
    if( glInvalidateTexSubImage_hook )
        glInvalidateTexSubImage_hook( texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_ );
    F(texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_);
}
static glIsBuffer_hook_t glIsBuffer_hook = 0;
glIsBuffer_hook_t getHook_glIsBuffer (){
    return glIsBuffer_hook ;
}
void setHook_glIsBuffer ( glIsBuffer_hook_t hook ){
    glIsBuffer_hook = hook;
}
GLboolean glIsBuffer ( GLuint buffer_ ){
    static PFNGLISBUFFERPROC F;
    if(!F)
        F = ( PFNGLISBUFFERPROC ) mygetprocaddr("glIsBuffer");
    if( glIsBuffer_hook )
        glIsBuffer_hook( buffer_ );
    GLboolean retval = F(buffer_);
    return retval;
}
static glIsEnabled_hook_t glIsEnabled_hook = 0;
glIsEnabled_hook_t getHook_glIsEnabled (){
    return glIsEnabled_hook ;
}
void setHook_glIsEnabled ( glIsEnabled_hook_t hook ){
    glIsEnabled_hook = hook;
}
GLboolean glIsEnabled ( GLenum cap_ ){
    static PFNGLISENABLEDPROC F;
    if(!F)
        F = ( PFNGLISENABLEDPROC ) mygetprocaddr("glIsEnabled");
    if( glIsEnabled_hook )
        glIsEnabled_hook( cap_ );
    GLboolean retval = F(cap_);
    return retval;
}
static glIsEnabledi_hook_t glIsEnabledi_hook = 0;
glIsEnabledi_hook_t getHook_glIsEnabledi (){
    return glIsEnabledi_hook ;
}
void setHook_glIsEnabledi ( glIsEnabledi_hook_t hook ){
    glIsEnabledi_hook = hook;
}
GLboolean glIsEnabledi ( GLenum target_, GLuint index_ ){
    static PFNGLISENABLEDIPROC F;
    if(!F)
        F = ( PFNGLISENABLEDIPROC ) mygetprocaddr("glIsEnabledi");
    if( glIsEnabledi_hook )
        glIsEnabledi_hook( target_, index_ );
    GLboolean retval = F(target_, index_);
    return retval;
}
static glIsFramebuffer_hook_t glIsFramebuffer_hook = 0;
glIsFramebuffer_hook_t getHook_glIsFramebuffer (){
    return glIsFramebuffer_hook ;
}
void setHook_glIsFramebuffer ( glIsFramebuffer_hook_t hook ){
    glIsFramebuffer_hook = hook;
}
GLboolean glIsFramebuffer ( GLuint framebuffer_ ){
    static PFNGLISFRAMEBUFFERPROC F;
    if(!F)
        F = ( PFNGLISFRAMEBUFFERPROC ) mygetprocaddr("glIsFramebuffer");
    if( glIsFramebuffer_hook )
        glIsFramebuffer_hook( framebuffer_ );
    GLboolean retval = F(framebuffer_);
    return retval;
}
static glIsProgram_hook_t glIsProgram_hook = 0;
glIsProgram_hook_t getHook_glIsProgram (){
    return glIsProgram_hook ;
}
void setHook_glIsProgram ( glIsProgram_hook_t hook ){
    glIsProgram_hook = hook;
}
GLboolean glIsProgram ( GLuint program_ ){
    static PFNGLISPROGRAMPROC F;
    if(!F)
        F = ( PFNGLISPROGRAMPROC ) mygetprocaddr("glIsProgram");
    if( glIsProgram_hook )
        glIsProgram_hook( program_ );
    GLboolean retval = F(program_);
    return retval;
}
static glIsProgramPipeline_hook_t glIsProgramPipeline_hook = 0;
glIsProgramPipeline_hook_t getHook_glIsProgramPipeline (){
    return glIsProgramPipeline_hook ;
}
void setHook_glIsProgramPipeline ( glIsProgramPipeline_hook_t hook ){
    glIsProgramPipeline_hook = hook;
}
GLboolean glIsProgramPipeline ( GLuint pipeline_ ){
    static PFNGLISPROGRAMPIPELINEPROC F;
    if(!F)
        F = ( PFNGLISPROGRAMPIPELINEPROC ) mygetprocaddr("glIsProgramPipeline");
    if( glIsProgramPipeline_hook )
        glIsProgramPipeline_hook( pipeline_ );
    GLboolean retval = F(pipeline_);
    return retval;
}
static glIsQuery_hook_t glIsQuery_hook = 0;
glIsQuery_hook_t getHook_glIsQuery (){
    return glIsQuery_hook ;
}
void setHook_glIsQuery ( glIsQuery_hook_t hook ){
    glIsQuery_hook = hook;
}
GLboolean glIsQuery ( GLuint id_ ){
    static PFNGLISQUERYPROC F;
    if(!F)
        F = ( PFNGLISQUERYPROC ) mygetprocaddr("glIsQuery");
    if( glIsQuery_hook )
        glIsQuery_hook( id_ );
    GLboolean retval = F(id_);
    return retval;
}
static glIsRenderbuffer_hook_t glIsRenderbuffer_hook = 0;
glIsRenderbuffer_hook_t getHook_glIsRenderbuffer (){
    return glIsRenderbuffer_hook ;
}
void setHook_glIsRenderbuffer ( glIsRenderbuffer_hook_t hook ){
    glIsRenderbuffer_hook = hook;
}
GLboolean glIsRenderbuffer ( GLuint renderbuffer_ ){
    static PFNGLISRENDERBUFFERPROC F;
    if(!F)
        F = ( PFNGLISRENDERBUFFERPROC ) mygetprocaddr("glIsRenderbuffer");
    if( glIsRenderbuffer_hook )
        glIsRenderbuffer_hook( renderbuffer_ );
    GLboolean retval = F(renderbuffer_);
    return retval;
}
static glIsSampler_hook_t glIsSampler_hook = 0;
glIsSampler_hook_t getHook_glIsSampler (){
    return glIsSampler_hook ;
}
void setHook_glIsSampler ( glIsSampler_hook_t hook ){
    glIsSampler_hook = hook;
}
GLboolean glIsSampler ( GLuint sampler_ ){
    static PFNGLISSAMPLERPROC F;
    if(!F)
        F = ( PFNGLISSAMPLERPROC ) mygetprocaddr("glIsSampler");
    if( glIsSampler_hook )
        glIsSampler_hook( sampler_ );
    GLboolean retval = F(sampler_);
    return retval;
}
static glIsShader_hook_t glIsShader_hook = 0;
glIsShader_hook_t getHook_glIsShader (){
    return glIsShader_hook ;
}
void setHook_glIsShader ( glIsShader_hook_t hook ){
    glIsShader_hook = hook;
}
GLboolean glIsShader ( GLuint shader_ ){
    static PFNGLISSHADERPROC F;
    if(!F)
        F = ( PFNGLISSHADERPROC ) mygetprocaddr("glIsShader");
    if( glIsShader_hook )
        glIsShader_hook( shader_ );
    GLboolean retval = F(shader_);
    return retval;
}
static glIsSync_hook_t glIsSync_hook = 0;
glIsSync_hook_t getHook_glIsSync (){
    return glIsSync_hook ;
}
void setHook_glIsSync ( glIsSync_hook_t hook ){
    glIsSync_hook = hook;
}
GLboolean glIsSync ( GLsync sync_ ){
    static PFNGLISSYNCPROC F;
    if(!F)
        F = ( PFNGLISSYNCPROC ) mygetprocaddr("glIsSync");
    if( glIsSync_hook )
        glIsSync_hook( sync_ );
    GLboolean retval = F(sync_);
    return retval;
}
static glIsTexture_hook_t glIsTexture_hook = 0;
glIsTexture_hook_t getHook_glIsTexture (){
    return glIsTexture_hook ;
}
void setHook_glIsTexture ( glIsTexture_hook_t hook ){
    glIsTexture_hook = hook;
}
GLboolean glIsTexture ( GLuint texture_ ){
    static PFNGLISTEXTUREPROC F;
    if(!F)
        F = ( PFNGLISTEXTUREPROC ) mygetprocaddr("glIsTexture");
    if( glIsTexture_hook )
        glIsTexture_hook( texture_ );
    GLboolean retval = F(texture_);
    return retval;
}
static glIsTransformFeedback_hook_t glIsTransformFeedback_hook = 0;
glIsTransformFeedback_hook_t getHook_glIsTransformFeedback (){
    return glIsTransformFeedback_hook ;
}
void setHook_glIsTransformFeedback ( glIsTransformFeedback_hook_t hook ){
    glIsTransformFeedback_hook = hook;
}
GLboolean glIsTransformFeedback ( GLuint id_ ){
    static PFNGLISTRANSFORMFEEDBACKPROC F;
    if(!F)
        F = ( PFNGLISTRANSFORMFEEDBACKPROC ) mygetprocaddr("glIsTransformFeedback");
    if( glIsTransformFeedback_hook )
        glIsTransformFeedback_hook( id_ );
    GLboolean retval = F(id_);
    return retval;
}
static glIsVertexArray_hook_t glIsVertexArray_hook = 0;
glIsVertexArray_hook_t getHook_glIsVertexArray (){
    return glIsVertexArray_hook ;
}
void setHook_glIsVertexArray ( glIsVertexArray_hook_t hook ){
    glIsVertexArray_hook = hook;
}
GLboolean glIsVertexArray ( GLuint array_ ){
    static PFNGLISVERTEXARRAYPROC F;
    if(!F)
        F = ( PFNGLISVERTEXARRAYPROC ) mygetprocaddr("glIsVertexArray");
    if( glIsVertexArray_hook )
        glIsVertexArray_hook( array_ );
    GLboolean retval = F(array_);
    return retval;
}
static glLineWidth_hook_t glLineWidth_hook = 0;
glLineWidth_hook_t getHook_glLineWidth (){
    return glLineWidth_hook ;
}
void setHook_glLineWidth ( glLineWidth_hook_t hook ){
    glLineWidth_hook = hook;
}
void glLineWidth ( GLfloat width_ ){
    static PFNGLLINEWIDTHPROC F;
    if(!F)
        F = ( PFNGLLINEWIDTHPROC ) mygetprocaddr("glLineWidth");
    if( glLineWidth_hook )
        glLineWidth_hook( width_ );
    F(width_);
}
static glLinkProgram_hook_t glLinkProgram_hook = 0;
glLinkProgram_hook_t getHook_glLinkProgram (){
    return glLinkProgram_hook ;
}
void setHook_glLinkProgram ( glLinkProgram_hook_t hook ){
    glLinkProgram_hook = hook;
}
void glLinkProgram ( GLuint program_ ){
    static PFNGLLINKPROGRAMPROC F;
    if(!F)
        F = ( PFNGLLINKPROGRAMPROC ) mygetprocaddr("glLinkProgram");
    if( glLinkProgram_hook )
        glLinkProgram_hook( program_ );
    F(program_);
}
static glLogicOp_hook_t glLogicOp_hook = 0;
glLogicOp_hook_t getHook_glLogicOp (){
    return glLogicOp_hook ;
}
void setHook_glLogicOp ( glLogicOp_hook_t hook ){
    glLogicOp_hook = hook;
}
void glLogicOp ( GLenum opcode_ ){
    static PFNGLLOGICOPPROC F;
    if(!F)
        F = ( PFNGLLOGICOPPROC ) mygetprocaddr("glLogicOp");
    if( glLogicOp_hook )
        glLogicOp_hook( opcode_ );
    F(opcode_);
}
static glMapBuffer_hook_t glMapBuffer_hook = 0;
glMapBuffer_hook_t getHook_glMapBuffer (){
    return glMapBuffer_hook ;
}
void setHook_glMapBuffer ( glMapBuffer_hook_t hook ){
    glMapBuffer_hook = hook;
}
void * glMapBuffer ( GLenum target_, GLenum access_ ){
    static PFNGLMAPBUFFERPROC F;
    if(!F)
        F = ( PFNGLMAPBUFFERPROC ) mygetprocaddr("glMapBuffer");
    if( glMapBuffer_hook )
        glMapBuffer_hook( target_, access_ );
    void * retval = F(target_, access_);
    return retval;
}
static glMapBufferRange_hook_t glMapBufferRange_hook = 0;
glMapBufferRange_hook_t getHook_glMapBufferRange (){
    return glMapBufferRange_hook ;
}
void setHook_glMapBufferRange ( glMapBufferRange_hook_t hook ){
    glMapBufferRange_hook = hook;
}
void * glMapBufferRange ( GLenum target_, GLintptr offset_, GLsizeiptr length_, GLbitfield access_ ){
    static PFNGLMAPBUFFERRANGEPROC F;
    if(!F)
        F = ( PFNGLMAPBUFFERRANGEPROC ) mygetprocaddr("glMapBufferRange");
    if( glMapBufferRange_hook )
        glMapBufferRange_hook( target_, offset_, length_, access_ );
    void * retval = F(target_, offset_, length_, access_);
    return retval;
}
static glMapNamedBuffer_hook_t glMapNamedBuffer_hook = 0;
glMapNamedBuffer_hook_t getHook_glMapNamedBuffer (){
    return glMapNamedBuffer_hook ;
}
void setHook_glMapNamedBuffer ( glMapNamedBuffer_hook_t hook ){
    glMapNamedBuffer_hook = hook;
}
void * glMapNamedBuffer ( GLuint buffer_, GLenum access_ ){
    static PFNGLMAPNAMEDBUFFERPROC F;
    if(!F)
        F = ( PFNGLMAPNAMEDBUFFERPROC ) mygetprocaddr("glMapNamedBuffer");
    if( glMapNamedBuffer_hook )
        glMapNamedBuffer_hook( buffer_, access_ );
    void * retval = F(buffer_, access_);
    return retval;
}
static glMapNamedBufferRange_hook_t glMapNamedBufferRange_hook = 0;
glMapNamedBufferRange_hook_t getHook_glMapNamedBufferRange (){
    return glMapNamedBufferRange_hook ;
}
void setHook_glMapNamedBufferRange ( glMapNamedBufferRange_hook_t hook ){
    glMapNamedBufferRange_hook = hook;
}
void * glMapNamedBufferRange ( GLuint buffer_, GLintptr offset_, GLsizeiptr length_, GLbitfield access_ ){
    static PFNGLMAPNAMEDBUFFERRANGEPROC F;
    if(!F)
        F = ( PFNGLMAPNAMEDBUFFERRANGEPROC ) mygetprocaddr("glMapNamedBufferRange");
    if( glMapNamedBufferRange_hook )
        glMapNamedBufferRange_hook( buffer_, offset_, length_, access_ );
    void * retval = F(buffer_, offset_, length_, access_);
    return retval;
}
static glMemoryBarrier_hook_t glMemoryBarrier_hook = 0;
glMemoryBarrier_hook_t getHook_glMemoryBarrier (){
    return glMemoryBarrier_hook ;
}
void setHook_glMemoryBarrier ( glMemoryBarrier_hook_t hook ){
    glMemoryBarrier_hook = hook;
}
void glMemoryBarrier ( GLbitfield barriers_ ){
    static PFNGLMEMORYBARRIERPROC F;
    if(!F)
        F = ( PFNGLMEMORYBARRIERPROC ) mygetprocaddr("glMemoryBarrier");
    if( glMemoryBarrier_hook )
        glMemoryBarrier_hook( barriers_ );
    F(barriers_);
}
static glMemoryBarrierByRegion_hook_t glMemoryBarrierByRegion_hook = 0;
glMemoryBarrierByRegion_hook_t getHook_glMemoryBarrierByRegion (){
    return glMemoryBarrierByRegion_hook ;
}
void setHook_glMemoryBarrierByRegion ( glMemoryBarrierByRegion_hook_t hook ){
    glMemoryBarrierByRegion_hook = hook;
}
void glMemoryBarrierByRegion ( GLbitfield barriers_ ){
    static PFNGLMEMORYBARRIERBYREGIONPROC F;
    if(!F)
        F = ( PFNGLMEMORYBARRIERBYREGIONPROC ) mygetprocaddr("glMemoryBarrierByRegion");
    if( glMemoryBarrierByRegion_hook )
        glMemoryBarrierByRegion_hook( barriers_ );
    F(barriers_);
}
static glMinSampleShading_hook_t glMinSampleShading_hook = 0;
glMinSampleShading_hook_t getHook_glMinSampleShading (){
    return glMinSampleShading_hook ;
}
void setHook_glMinSampleShading ( glMinSampleShading_hook_t hook ){
    glMinSampleShading_hook = hook;
}
void glMinSampleShading ( GLfloat value_ ){
    static PFNGLMINSAMPLESHADINGPROC F;
    if(!F)
        F = ( PFNGLMINSAMPLESHADINGPROC ) mygetprocaddr("glMinSampleShading");
    if( glMinSampleShading_hook )
        glMinSampleShading_hook( value_ );
    F(value_);
}
static glMultiDrawArrays_hook_t glMultiDrawArrays_hook = 0;
glMultiDrawArrays_hook_t getHook_glMultiDrawArrays (){
    return glMultiDrawArrays_hook ;
}
void setHook_glMultiDrawArrays ( glMultiDrawArrays_hook_t hook ){
    glMultiDrawArrays_hook = hook;
}
void glMultiDrawArrays ( GLenum mode_, const GLint * first_, const GLsizei * count_, GLsizei drawcount_ ){
    static PFNGLMULTIDRAWARRAYSPROC F;
    if(!F)
        F = ( PFNGLMULTIDRAWARRAYSPROC ) mygetprocaddr("glMultiDrawArrays");
    if( glMultiDrawArrays_hook )
        glMultiDrawArrays_hook( mode_, first_, count_, drawcount_ );
    F(mode_, first_, count_, drawcount_);
}
static glMultiDrawArraysIndirect_hook_t glMultiDrawArraysIndirect_hook = 0;
glMultiDrawArraysIndirect_hook_t getHook_glMultiDrawArraysIndirect (){
    return glMultiDrawArraysIndirect_hook ;
}
void setHook_glMultiDrawArraysIndirect ( glMultiDrawArraysIndirect_hook_t hook ){
    glMultiDrawArraysIndirect_hook = hook;
}
void glMultiDrawArraysIndirect ( GLenum mode_, const void * indirect_, GLsizei drawcount_, GLsizei stride_ ){
    static PFNGLMULTIDRAWARRAYSINDIRECTPROC F;
    if(!F)
        F = ( PFNGLMULTIDRAWARRAYSINDIRECTPROC ) mygetprocaddr("glMultiDrawArraysIndirect");
    if( glMultiDrawArraysIndirect_hook )
        glMultiDrawArraysIndirect_hook( mode_, indirect_, drawcount_, stride_ );
    F(mode_, indirect_, drawcount_, stride_);
}
static glMultiDrawElements_hook_t glMultiDrawElements_hook = 0;
glMultiDrawElements_hook_t getHook_glMultiDrawElements (){
    return glMultiDrawElements_hook ;
}
void setHook_glMultiDrawElements ( glMultiDrawElements_hook_t hook ){
    glMultiDrawElements_hook = hook;
}
void glMultiDrawElements ( GLenum mode_, const GLsizei * count_, GLenum type_, const void ** indices_, GLsizei drawcount_ ){
    static PFNGLMULTIDRAWELEMENTSPROC F;
    if(!F)
        F = ( PFNGLMULTIDRAWELEMENTSPROC ) mygetprocaddr("glMultiDrawElements");
    if( glMultiDrawElements_hook )
        glMultiDrawElements_hook( mode_, count_, type_, indices_, drawcount_ );
    F(mode_, count_, type_, indices_, drawcount_);
}
static glMultiDrawElementsBaseVertex_hook_t glMultiDrawElementsBaseVertex_hook = 0;
glMultiDrawElementsBaseVertex_hook_t getHook_glMultiDrawElementsBaseVertex (){
    return glMultiDrawElementsBaseVertex_hook ;
}
void setHook_glMultiDrawElementsBaseVertex ( glMultiDrawElementsBaseVertex_hook_t hook ){
    glMultiDrawElementsBaseVertex_hook = hook;
}
void glMultiDrawElementsBaseVertex ( GLenum mode_, const GLsizei * count_, GLenum type_, const void ** indices_, GLsizei drawcount_, const GLint * basevertex_ ){
    static PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC F;
    if(!F)
        F = ( PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC ) mygetprocaddr("glMultiDrawElementsBaseVertex");
    if( glMultiDrawElementsBaseVertex_hook )
        glMultiDrawElementsBaseVertex_hook( mode_, count_, type_, indices_, drawcount_, basevertex_ );
    F(mode_, count_, type_, indices_, drawcount_, basevertex_);
}
static glMultiDrawElementsIndirect_hook_t glMultiDrawElementsIndirect_hook = 0;
glMultiDrawElementsIndirect_hook_t getHook_glMultiDrawElementsIndirect (){
    return glMultiDrawElementsIndirect_hook ;
}
void setHook_glMultiDrawElementsIndirect ( glMultiDrawElementsIndirect_hook_t hook ){
    glMultiDrawElementsIndirect_hook = hook;
}
void glMultiDrawElementsIndirect ( GLenum mode_, GLenum type_, const void * indirect_, GLsizei drawcount_, GLsizei stride_ ){
    static PFNGLMULTIDRAWELEMENTSINDIRECTPROC F;
    if(!F)
        F = ( PFNGLMULTIDRAWELEMENTSINDIRECTPROC ) mygetprocaddr("glMultiDrawElementsIndirect");
    if( glMultiDrawElementsIndirect_hook )
        glMultiDrawElementsIndirect_hook( mode_, type_, indirect_, drawcount_, stride_ );
    F(mode_, type_, indirect_, drawcount_, stride_);
}
static glNamedBufferData_hook_t glNamedBufferData_hook = 0;
glNamedBufferData_hook_t getHook_glNamedBufferData (){
    return glNamedBufferData_hook ;
}
void setHook_glNamedBufferData ( glNamedBufferData_hook_t hook ){
    glNamedBufferData_hook = hook;
}
void glNamedBufferData ( GLuint buffer_, GLsizeiptr size_, const void * data_, GLenum usage_ ){
    static PFNGLNAMEDBUFFERDATAPROC F;
    if(!F)
        F = ( PFNGLNAMEDBUFFERDATAPROC ) mygetprocaddr("glNamedBufferData");
    if( glNamedBufferData_hook )
        glNamedBufferData_hook( buffer_, size_, data_, usage_ );
    F(buffer_, size_, data_, usage_);
}
static glNamedBufferStorage_hook_t glNamedBufferStorage_hook = 0;
glNamedBufferStorage_hook_t getHook_glNamedBufferStorage (){
    return glNamedBufferStorage_hook ;
}
void setHook_glNamedBufferStorage ( glNamedBufferStorage_hook_t hook ){
    glNamedBufferStorage_hook = hook;
}
void glNamedBufferStorage ( GLuint buffer_, GLsizeiptr size_, const void * data_, GLbitfield flags_ ){
    static PFNGLNAMEDBUFFERSTORAGEPROC F;
    if(!F)
        F = ( PFNGLNAMEDBUFFERSTORAGEPROC ) mygetprocaddr("glNamedBufferStorage");
    if( glNamedBufferStorage_hook )
        glNamedBufferStorage_hook( buffer_, size_, data_, flags_ );
    F(buffer_, size_, data_, flags_);
}
static glNamedBufferSubData_hook_t glNamedBufferSubData_hook = 0;
glNamedBufferSubData_hook_t getHook_glNamedBufferSubData (){
    return glNamedBufferSubData_hook ;
}
void setHook_glNamedBufferSubData ( glNamedBufferSubData_hook_t hook ){
    glNamedBufferSubData_hook = hook;
}
void glNamedBufferSubData ( GLuint buffer_, GLintptr offset_, GLsizeiptr size_, const void * data_ ){
    static PFNGLNAMEDBUFFERSUBDATAPROC F;
    if(!F)
        F = ( PFNGLNAMEDBUFFERSUBDATAPROC ) mygetprocaddr("glNamedBufferSubData");
    if( glNamedBufferSubData_hook )
        glNamedBufferSubData_hook( buffer_, offset_, size_, data_ );
    F(buffer_, offset_, size_, data_);
}
static glNamedFramebufferDrawBuffer_hook_t glNamedFramebufferDrawBuffer_hook = 0;
glNamedFramebufferDrawBuffer_hook_t getHook_glNamedFramebufferDrawBuffer (){
    return glNamedFramebufferDrawBuffer_hook ;
}
void setHook_glNamedFramebufferDrawBuffer ( glNamedFramebufferDrawBuffer_hook_t hook ){
    glNamedFramebufferDrawBuffer_hook = hook;
}
void glNamedFramebufferDrawBuffer ( GLuint framebuffer_, GLenum buf_ ){
    static PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC F;
    if(!F)
        F = ( PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC ) mygetprocaddr("glNamedFramebufferDrawBuffer");
    if( glNamedFramebufferDrawBuffer_hook )
        glNamedFramebufferDrawBuffer_hook( framebuffer_, buf_ );
    F(framebuffer_, buf_);
}
static glNamedFramebufferDrawBuffers_hook_t glNamedFramebufferDrawBuffers_hook = 0;
glNamedFramebufferDrawBuffers_hook_t getHook_glNamedFramebufferDrawBuffers (){
    return glNamedFramebufferDrawBuffers_hook ;
}
void setHook_glNamedFramebufferDrawBuffers ( glNamedFramebufferDrawBuffers_hook_t hook ){
    glNamedFramebufferDrawBuffers_hook = hook;
}
void glNamedFramebufferDrawBuffers ( GLuint framebuffer_, GLsizei n_, const GLenum * bufs_ ){
    static PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC F;
    if(!F)
        F = ( PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC ) mygetprocaddr("glNamedFramebufferDrawBuffers");
    if( glNamedFramebufferDrawBuffers_hook )
        glNamedFramebufferDrawBuffers_hook( framebuffer_, n_, bufs_ );
    F(framebuffer_, n_, bufs_);
}
static glNamedFramebufferParameteri_hook_t glNamedFramebufferParameteri_hook = 0;
glNamedFramebufferParameteri_hook_t getHook_glNamedFramebufferParameteri (){
    return glNamedFramebufferParameteri_hook ;
}
void setHook_glNamedFramebufferParameteri ( glNamedFramebufferParameteri_hook_t hook ){
    glNamedFramebufferParameteri_hook = hook;
}
void glNamedFramebufferParameteri ( GLuint framebuffer_, GLenum pname_, GLint param_ ){
    static PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC F;
    if(!F)
        F = ( PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC ) mygetprocaddr("glNamedFramebufferParameteri");
    if( glNamedFramebufferParameteri_hook )
        glNamedFramebufferParameteri_hook( framebuffer_, pname_, param_ );
    F(framebuffer_, pname_, param_);
}
static glNamedFramebufferReadBuffer_hook_t glNamedFramebufferReadBuffer_hook = 0;
glNamedFramebufferReadBuffer_hook_t getHook_glNamedFramebufferReadBuffer (){
    return glNamedFramebufferReadBuffer_hook ;
}
void setHook_glNamedFramebufferReadBuffer ( glNamedFramebufferReadBuffer_hook_t hook ){
    glNamedFramebufferReadBuffer_hook = hook;
}
void glNamedFramebufferReadBuffer ( GLuint framebuffer_, GLenum src_ ){
    static PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC F;
    if(!F)
        F = ( PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC ) mygetprocaddr("glNamedFramebufferReadBuffer");
    if( glNamedFramebufferReadBuffer_hook )
        glNamedFramebufferReadBuffer_hook( framebuffer_, src_ );
    F(framebuffer_, src_);
}
static glNamedFramebufferRenderbuffer_hook_t glNamedFramebufferRenderbuffer_hook = 0;
glNamedFramebufferRenderbuffer_hook_t getHook_glNamedFramebufferRenderbuffer (){
    return glNamedFramebufferRenderbuffer_hook ;
}
void setHook_glNamedFramebufferRenderbuffer ( glNamedFramebufferRenderbuffer_hook_t hook ){
    glNamedFramebufferRenderbuffer_hook = hook;
}
void glNamedFramebufferRenderbuffer ( GLuint framebuffer_, GLenum attachment_, GLenum renderbuffertarget_, GLuint renderbuffer_ ){
    static PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC F;
    if(!F)
        F = ( PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC ) mygetprocaddr("glNamedFramebufferRenderbuffer");
    if( glNamedFramebufferRenderbuffer_hook )
        glNamedFramebufferRenderbuffer_hook( framebuffer_, attachment_, renderbuffertarget_, renderbuffer_ );
    F(framebuffer_, attachment_, renderbuffertarget_, renderbuffer_);
}
static glNamedFramebufferTexture_hook_t glNamedFramebufferTexture_hook = 0;
glNamedFramebufferTexture_hook_t getHook_glNamedFramebufferTexture (){
    return glNamedFramebufferTexture_hook ;
}
void setHook_glNamedFramebufferTexture ( glNamedFramebufferTexture_hook_t hook ){
    glNamedFramebufferTexture_hook = hook;
}
void glNamedFramebufferTexture ( GLuint framebuffer_, GLenum attachment_, GLuint texture_, GLint level_ ){
    static PFNGLNAMEDFRAMEBUFFERTEXTUREPROC F;
    if(!F)
        F = ( PFNGLNAMEDFRAMEBUFFERTEXTUREPROC ) mygetprocaddr("glNamedFramebufferTexture");
    if( glNamedFramebufferTexture_hook )
        glNamedFramebufferTexture_hook( framebuffer_, attachment_, texture_, level_ );
    F(framebuffer_, attachment_, texture_, level_);
}
static glNamedFramebufferTextureLayer_hook_t glNamedFramebufferTextureLayer_hook = 0;
glNamedFramebufferTextureLayer_hook_t getHook_glNamedFramebufferTextureLayer (){
    return glNamedFramebufferTextureLayer_hook ;
}
void setHook_glNamedFramebufferTextureLayer ( glNamedFramebufferTextureLayer_hook_t hook ){
    glNamedFramebufferTextureLayer_hook = hook;
}
void glNamedFramebufferTextureLayer ( GLuint framebuffer_, GLenum attachment_, GLuint texture_, GLint level_, GLint layer_ ){
    static PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC F;
    if(!F)
        F = ( PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC ) mygetprocaddr("glNamedFramebufferTextureLayer");
    if( glNamedFramebufferTextureLayer_hook )
        glNamedFramebufferTextureLayer_hook( framebuffer_, attachment_, texture_, level_, layer_ );
    F(framebuffer_, attachment_, texture_, level_, layer_);
}
static glNamedRenderbufferStorage_hook_t glNamedRenderbufferStorage_hook = 0;
glNamedRenderbufferStorage_hook_t getHook_glNamedRenderbufferStorage (){
    return glNamedRenderbufferStorage_hook ;
}
void setHook_glNamedRenderbufferStorage ( glNamedRenderbufferStorage_hook_t hook ){
    glNamedRenderbufferStorage_hook = hook;
}
void glNamedRenderbufferStorage ( GLuint renderbuffer_, GLenum internalformat_, GLsizei width_, GLsizei height_ ){
    static PFNGLNAMEDRENDERBUFFERSTORAGEPROC F;
    if(!F)
        F = ( PFNGLNAMEDRENDERBUFFERSTORAGEPROC ) mygetprocaddr("glNamedRenderbufferStorage");
    if( glNamedRenderbufferStorage_hook )
        glNamedRenderbufferStorage_hook( renderbuffer_, internalformat_, width_, height_ );
    F(renderbuffer_, internalformat_, width_, height_);
}
static glNamedRenderbufferStorageMultisample_hook_t glNamedRenderbufferStorageMultisample_hook = 0;
glNamedRenderbufferStorageMultisample_hook_t getHook_glNamedRenderbufferStorageMultisample (){
    return glNamedRenderbufferStorageMultisample_hook ;
}
void setHook_glNamedRenderbufferStorageMultisample ( glNamedRenderbufferStorageMultisample_hook_t hook ){
    glNamedRenderbufferStorageMultisample_hook = hook;
}
void glNamedRenderbufferStorageMultisample ( GLuint renderbuffer_, GLsizei samples_, GLenum internalformat_, GLsizei width_, GLsizei height_ ){
    static PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC F;
    if(!F)
        F = ( PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC ) mygetprocaddr("glNamedRenderbufferStorageMultisample");
    if( glNamedRenderbufferStorageMultisample_hook )
        glNamedRenderbufferStorageMultisample_hook( renderbuffer_, samples_, internalformat_, width_, height_ );
    F(renderbuffer_, samples_, internalformat_, width_, height_);
}
static glObjectLabel_hook_t glObjectLabel_hook = 0;
glObjectLabel_hook_t getHook_glObjectLabel (){
    return glObjectLabel_hook ;
}
void setHook_glObjectLabel ( glObjectLabel_hook_t hook ){
    glObjectLabel_hook = hook;
}
void glObjectLabel ( GLenum identifier_, GLuint name_, GLsizei length_, const GLchar * label_ ){
    static PFNGLOBJECTLABELPROC F;
    if(!F)
        F = ( PFNGLOBJECTLABELPROC ) mygetprocaddr("glObjectLabel");
    if( glObjectLabel_hook )
        glObjectLabel_hook( identifier_, name_, length_, label_ );
    F(identifier_, name_, length_, label_);
}
static glObjectPtrLabel_hook_t glObjectPtrLabel_hook = 0;
glObjectPtrLabel_hook_t getHook_glObjectPtrLabel (){
    return glObjectPtrLabel_hook ;
}
void setHook_glObjectPtrLabel ( glObjectPtrLabel_hook_t hook ){
    glObjectPtrLabel_hook = hook;
}
void glObjectPtrLabel ( const void * ptr_, GLsizei length_, const GLchar * label_ ){
    static PFNGLOBJECTPTRLABELPROC F;
    if(!F)
        F = ( PFNGLOBJECTPTRLABELPROC ) mygetprocaddr("glObjectPtrLabel");
    if( glObjectPtrLabel_hook )
        glObjectPtrLabel_hook( ptr_, length_, label_ );
    F(ptr_, length_, label_);
}
static glPatchParameterfv_hook_t glPatchParameterfv_hook = 0;
glPatchParameterfv_hook_t getHook_glPatchParameterfv (){
    return glPatchParameterfv_hook ;
}
void setHook_glPatchParameterfv ( glPatchParameterfv_hook_t hook ){
    glPatchParameterfv_hook = hook;
}
void glPatchParameterfv ( GLenum pname_, const GLfloat * values_ ){
    static PFNGLPATCHPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLPATCHPARAMETERFVPROC ) mygetprocaddr("glPatchParameterfv");
    if( glPatchParameterfv_hook )
        glPatchParameterfv_hook( pname_, values_ );
    F(pname_, values_);
}
static glPatchParameteri_hook_t glPatchParameteri_hook = 0;
glPatchParameteri_hook_t getHook_glPatchParameteri (){
    return glPatchParameteri_hook ;
}
void setHook_glPatchParameteri ( glPatchParameteri_hook_t hook ){
    glPatchParameteri_hook = hook;
}
void glPatchParameteri ( GLenum pname_, GLint value_ ){
    static PFNGLPATCHPARAMETERIPROC F;
    if(!F)
        F = ( PFNGLPATCHPARAMETERIPROC ) mygetprocaddr("glPatchParameteri");
    if( glPatchParameteri_hook )
        glPatchParameteri_hook( pname_, value_ );
    F(pname_, value_);
}
static glPauseTransformFeedback_hook_t glPauseTransformFeedback_hook = 0;
glPauseTransformFeedback_hook_t getHook_glPauseTransformFeedback (){
    return glPauseTransformFeedback_hook ;
}
void setHook_glPauseTransformFeedback ( glPauseTransformFeedback_hook_t hook ){
    glPauseTransformFeedback_hook = hook;
}
void glPauseTransformFeedback (  ){
    static PFNGLPAUSETRANSFORMFEEDBACKPROC F;
    if(!F)
        F = ( PFNGLPAUSETRANSFORMFEEDBACKPROC ) mygetprocaddr("glPauseTransformFeedback");
    if( glPauseTransformFeedback_hook )
        glPauseTransformFeedback_hook(  );
    F();
}
static glPixelStoref_hook_t glPixelStoref_hook = 0;
glPixelStoref_hook_t getHook_glPixelStoref (){
    return glPixelStoref_hook ;
}
void setHook_glPixelStoref ( glPixelStoref_hook_t hook ){
    glPixelStoref_hook = hook;
}
void glPixelStoref ( GLenum pname_, GLfloat param_ ){
    static PFNGLPIXELSTOREFPROC F;
    if(!F)
        F = ( PFNGLPIXELSTOREFPROC ) mygetprocaddr("glPixelStoref");
    if( glPixelStoref_hook )
        glPixelStoref_hook( pname_, param_ );
    F(pname_, param_);
}
static glPixelStorei_hook_t glPixelStorei_hook = 0;
glPixelStorei_hook_t getHook_glPixelStorei (){
    return glPixelStorei_hook ;
}
void setHook_glPixelStorei ( glPixelStorei_hook_t hook ){
    glPixelStorei_hook = hook;
}
void glPixelStorei ( GLenum pname_, GLint param_ ){
    static PFNGLPIXELSTOREIPROC F;
    if(!F)
        F = ( PFNGLPIXELSTOREIPROC ) mygetprocaddr("glPixelStorei");
    if( glPixelStorei_hook )
        glPixelStorei_hook( pname_, param_ );
    F(pname_, param_);
}
static glPointParameterf_hook_t glPointParameterf_hook = 0;
glPointParameterf_hook_t getHook_glPointParameterf (){
    return glPointParameterf_hook ;
}
void setHook_glPointParameterf ( glPointParameterf_hook_t hook ){
    glPointParameterf_hook = hook;
}
void glPointParameterf ( GLenum pname_, GLfloat param_ ){
    static PFNGLPOINTPARAMETERFPROC F;
    if(!F)
        F = ( PFNGLPOINTPARAMETERFPROC ) mygetprocaddr("glPointParameterf");
    if( glPointParameterf_hook )
        glPointParameterf_hook( pname_, param_ );
    F(pname_, param_);
}
static glPointParameterfv_hook_t glPointParameterfv_hook = 0;
glPointParameterfv_hook_t getHook_glPointParameterfv (){
    return glPointParameterfv_hook ;
}
void setHook_glPointParameterfv ( glPointParameterfv_hook_t hook ){
    glPointParameterfv_hook = hook;
}
void glPointParameterfv ( GLenum pname_, const GLfloat * params_ ){
    static PFNGLPOINTPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLPOINTPARAMETERFVPROC ) mygetprocaddr("glPointParameterfv");
    if( glPointParameterfv_hook )
        glPointParameterfv_hook( pname_, params_ );
    F(pname_, params_);
}
static glPointParameteri_hook_t glPointParameteri_hook = 0;
glPointParameteri_hook_t getHook_glPointParameteri (){
    return glPointParameteri_hook ;
}
void setHook_glPointParameteri ( glPointParameteri_hook_t hook ){
    glPointParameteri_hook = hook;
}
void glPointParameteri ( GLenum pname_, GLint param_ ){
    static PFNGLPOINTPARAMETERIPROC F;
    if(!F)
        F = ( PFNGLPOINTPARAMETERIPROC ) mygetprocaddr("glPointParameteri");
    if( glPointParameteri_hook )
        glPointParameteri_hook( pname_, param_ );
    F(pname_, param_);
}
static glPointParameteriv_hook_t glPointParameteriv_hook = 0;
glPointParameteriv_hook_t getHook_glPointParameteriv (){
    return glPointParameteriv_hook ;
}
void setHook_glPointParameteriv ( glPointParameteriv_hook_t hook ){
    glPointParameteriv_hook = hook;
}
void glPointParameteriv ( GLenum pname_, const GLint * params_ ){
    static PFNGLPOINTPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLPOINTPARAMETERIVPROC ) mygetprocaddr("glPointParameteriv");
    if( glPointParameteriv_hook )
        glPointParameteriv_hook( pname_, params_ );
    F(pname_, params_);
}
static glPointSize_hook_t glPointSize_hook = 0;
glPointSize_hook_t getHook_glPointSize (){
    return glPointSize_hook ;
}
void setHook_glPointSize ( glPointSize_hook_t hook ){
    glPointSize_hook = hook;
}
void glPointSize ( GLfloat size_ ){
    static PFNGLPOINTSIZEPROC F;
    if(!F)
        F = ( PFNGLPOINTSIZEPROC ) mygetprocaddr("glPointSize");
    if( glPointSize_hook )
        glPointSize_hook( size_ );
    F(size_);
}
static glPolygonMode_hook_t glPolygonMode_hook = 0;
glPolygonMode_hook_t getHook_glPolygonMode (){
    return glPolygonMode_hook ;
}
void setHook_glPolygonMode ( glPolygonMode_hook_t hook ){
    glPolygonMode_hook = hook;
}
void glPolygonMode ( GLenum face_, GLenum mode_ ){
    static PFNGLPOLYGONMODEPROC F;
    if(!F)
        F = ( PFNGLPOLYGONMODEPROC ) mygetprocaddr("glPolygonMode");
    if( glPolygonMode_hook )
        glPolygonMode_hook( face_, mode_ );
    F(face_, mode_);
}
static glPolygonOffset_hook_t glPolygonOffset_hook = 0;
glPolygonOffset_hook_t getHook_glPolygonOffset (){
    return glPolygonOffset_hook ;
}
void setHook_glPolygonOffset ( glPolygonOffset_hook_t hook ){
    glPolygonOffset_hook = hook;
}
void glPolygonOffset ( GLfloat factor_, GLfloat units_ ){
    static PFNGLPOLYGONOFFSETPROC F;
    if(!F)
        F = ( PFNGLPOLYGONOFFSETPROC ) mygetprocaddr("glPolygonOffset");
    if( glPolygonOffset_hook )
        glPolygonOffset_hook( factor_, units_ );
    F(factor_, units_);
}
static glPopDebugGroup_hook_t glPopDebugGroup_hook = 0;
glPopDebugGroup_hook_t getHook_glPopDebugGroup (){
    return glPopDebugGroup_hook ;
}
void setHook_glPopDebugGroup ( glPopDebugGroup_hook_t hook ){
    glPopDebugGroup_hook = hook;
}
void glPopDebugGroup (  ){
    static PFNGLPOPDEBUGGROUPPROC F;
    if(!F)
        F = ( PFNGLPOPDEBUGGROUPPROC ) mygetprocaddr("glPopDebugGroup");
    if( glPopDebugGroup_hook )
        glPopDebugGroup_hook(  );
    F();
}
static glPrimitiveRestartIndex_hook_t glPrimitiveRestartIndex_hook = 0;
glPrimitiveRestartIndex_hook_t getHook_glPrimitiveRestartIndex (){
    return glPrimitiveRestartIndex_hook ;
}
void setHook_glPrimitiveRestartIndex ( glPrimitiveRestartIndex_hook_t hook ){
    glPrimitiveRestartIndex_hook = hook;
}
void glPrimitiveRestartIndex ( GLuint index_ ){
    static PFNGLPRIMITIVERESTARTINDEXPROC F;
    if(!F)
        F = ( PFNGLPRIMITIVERESTARTINDEXPROC ) mygetprocaddr("glPrimitiveRestartIndex");
    if( glPrimitiveRestartIndex_hook )
        glPrimitiveRestartIndex_hook( index_ );
    F(index_);
}
static glProgramBinary_hook_t glProgramBinary_hook = 0;
glProgramBinary_hook_t getHook_glProgramBinary (){
    return glProgramBinary_hook ;
}
void setHook_glProgramBinary ( glProgramBinary_hook_t hook ){
    glProgramBinary_hook = hook;
}
void glProgramBinary ( GLuint program_, GLenum binaryFormat_, const void * binary_, GLsizei length_ ){
    static PFNGLPROGRAMBINARYPROC F;
    if(!F)
        F = ( PFNGLPROGRAMBINARYPROC ) mygetprocaddr("glProgramBinary");
    if( glProgramBinary_hook )
        glProgramBinary_hook( program_, binaryFormat_, binary_, length_ );
    F(program_, binaryFormat_, binary_, length_);
}
static glProgramParameteri_hook_t glProgramParameteri_hook = 0;
glProgramParameteri_hook_t getHook_glProgramParameteri (){
    return glProgramParameteri_hook ;
}
void setHook_glProgramParameteri ( glProgramParameteri_hook_t hook ){
    glProgramParameteri_hook = hook;
}
void glProgramParameteri ( GLuint program_, GLenum pname_, GLint value_ ){
    static PFNGLPROGRAMPARAMETERIPROC F;
    if(!F)
        F = ( PFNGLPROGRAMPARAMETERIPROC ) mygetprocaddr("glProgramParameteri");
    if( glProgramParameteri_hook )
        glProgramParameteri_hook( program_, pname_, value_ );
    F(program_, pname_, value_);
}
static glProgramUniform1d_hook_t glProgramUniform1d_hook = 0;
glProgramUniform1d_hook_t getHook_glProgramUniform1d (){
    return glProgramUniform1d_hook ;
}
void setHook_glProgramUniform1d ( glProgramUniform1d_hook_t hook ){
    glProgramUniform1d_hook = hook;
}
void glProgramUniform1d ( GLuint program_, GLint location_, GLdouble v0_ ){
    static PFNGLPROGRAMUNIFORM1DPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM1DPROC ) mygetprocaddr("glProgramUniform1d");
    if( glProgramUniform1d_hook )
        glProgramUniform1d_hook( program_, location_, v0_ );
    F(program_, location_, v0_);
}
static glProgramUniform1dv_hook_t glProgramUniform1dv_hook = 0;
glProgramUniform1dv_hook_t getHook_glProgramUniform1dv (){
    return glProgramUniform1dv_hook ;
}
void setHook_glProgramUniform1dv ( glProgramUniform1dv_hook_t hook ){
    glProgramUniform1dv_hook = hook;
}
void glProgramUniform1dv ( GLuint program_, GLint location_, GLsizei count_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORM1DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM1DVPROC ) mygetprocaddr("glProgramUniform1dv");
    if( glProgramUniform1dv_hook )
        glProgramUniform1dv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform1f_hook_t glProgramUniform1f_hook = 0;
glProgramUniform1f_hook_t getHook_glProgramUniform1f (){
    return glProgramUniform1f_hook ;
}
void setHook_glProgramUniform1f ( glProgramUniform1f_hook_t hook ){
    glProgramUniform1f_hook = hook;
}
void glProgramUniform1f ( GLuint program_, GLint location_, GLfloat v0_ ){
    static PFNGLPROGRAMUNIFORM1FPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM1FPROC ) mygetprocaddr("glProgramUniform1f");
    if( glProgramUniform1f_hook )
        glProgramUniform1f_hook( program_, location_, v0_ );
    F(program_, location_, v0_);
}
static glProgramUniform1fv_hook_t glProgramUniform1fv_hook = 0;
glProgramUniform1fv_hook_t getHook_glProgramUniform1fv (){
    return glProgramUniform1fv_hook ;
}
void setHook_glProgramUniform1fv ( glProgramUniform1fv_hook_t hook ){
    glProgramUniform1fv_hook = hook;
}
void glProgramUniform1fv ( GLuint program_, GLint location_, GLsizei count_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORM1FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM1FVPROC ) mygetprocaddr("glProgramUniform1fv");
    if( glProgramUniform1fv_hook )
        glProgramUniform1fv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform1i_hook_t glProgramUniform1i_hook = 0;
glProgramUniform1i_hook_t getHook_glProgramUniform1i (){
    return glProgramUniform1i_hook ;
}
void setHook_glProgramUniform1i ( glProgramUniform1i_hook_t hook ){
    glProgramUniform1i_hook = hook;
}
void glProgramUniform1i ( GLuint program_, GLint location_, GLint v0_ ){
    static PFNGLPROGRAMUNIFORM1IPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM1IPROC ) mygetprocaddr("glProgramUniform1i");
    if( glProgramUniform1i_hook )
        glProgramUniform1i_hook( program_, location_, v0_ );
    F(program_, location_, v0_);
}
static glProgramUniform1iv_hook_t glProgramUniform1iv_hook = 0;
glProgramUniform1iv_hook_t getHook_glProgramUniform1iv (){
    return glProgramUniform1iv_hook ;
}
void setHook_glProgramUniform1iv ( glProgramUniform1iv_hook_t hook ){
    glProgramUniform1iv_hook = hook;
}
void glProgramUniform1iv ( GLuint program_, GLint location_, GLsizei count_, const GLint * value_ ){
    static PFNGLPROGRAMUNIFORM1IVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM1IVPROC ) mygetprocaddr("glProgramUniform1iv");
    if( glProgramUniform1iv_hook )
        glProgramUniform1iv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform1ui_hook_t glProgramUniform1ui_hook = 0;
glProgramUniform1ui_hook_t getHook_glProgramUniform1ui (){
    return glProgramUniform1ui_hook ;
}
void setHook_glProgramUniform1ui ( glProgramUniform1ui_hook_t hook ){
    glProgramUniform1ui_hook = hook;
}
void glProgramUniform1ui ( GLuint program_, GLint location_, GLuint v0_ ){
    static PFNGLPROGRAMUNIFORM1UIPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM1UIPROC ) mygetprocaddr("glProgramUniform1ui");
    if( glProgramUniform1ui_hook )
        glProgramUniform1ui_hook( program_, location_, v0_ );
    F(program_, location_, v0_);
}
static glProgramUniform1uiv_hook_t glProgramUniform1uiv_hook = 0;
glProgramUniform1uiv_hook_t getHook_glProgramUniform1uiv (){
    return glProgramUniform1uiv_hook ;
}
void setHook_glProgramUniform1uiv ( glProgramUniform1uiv_hook_t hook ){
    glProgramUniform1uiv_hook = hook;
}
void glProgramUniform1uiv ( GLuint program_, GLint location_, GLsizei count_, const GLuint * value_ ){
    static PFNGLPROGRAMUNIFORM1UIVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM1UIVPROC ) mygetprocaddr("glProgramUniform1uiv");
    if( glProgramUniform1uiv_hook )
        glProgramUniform1uiv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform2d_hook_t glProgramUniform2d_hook = 0;
glProgramUniform2d_hook_t getHook_glProgramUniform2d (){
    return glProgramUniform2d_hook ;
}
void setHook_glProgramUniform2d ( glProgramUniform2d_hook_t hook ){
    glProgramUniform2d_hook = hook;
}
void glProgramUniform2d ( GLuint program_, GLint location_, GLdouble v0_, GLdouble v1_ ){
    static PFNGLPROGRAMUNIFORM2DPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM2DPROC ) mygetprocaddr("glProgramUniform2d");
    if( glProgramUniform2d_hook )
        glProgramUniform2d_hook( program_, location_, v0_, v1_ );
    F(program_, location_, v0_, v1_);
}
static glProgramUniform2dv_hook_t glProgramUniform2dv_hook = 0;
glProgramUniform2dv_hook_t getHook_glProgramUniform2dv (){
    return glProgramUniform2dv_hook ;
}
void setHook_glProgramUniform2dv ( glProgramUniform2dv_hook_t hook ){
    glProgramUniform2dv_hook = hook;
}
void glProgramUniform2dv ( GLuint program_, GLint location_, GLsizei count_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORM2DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM2DVPROC ) mygetprocaddr("glProgramUniform2dv");
    if( glProgramUniform2dv_hook )
        glProgramUniform2dv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform2f_hook_t glProgramUniform2f_hook = 0;
glProgramUniform2f_hook_t getHook_glProgramUniform2f (){
    return glProgramUniform2f_hook ;
}
void setHook_glProgramUniform2f ( glProgramUniform2f_hook_t hook ){
    glProgramUniform2f_hook = hook;
}
void glProgramUniform2f ( GLuint program_, GLint location_, GLfloat v0_, GLfloat v1_ ){
    static PFNGLPROGRAMUNIFORM2FPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM2FPROC ) mygetprocaddr("glProgramUniform2f");
    if( glProgramUniform2f_hook )
        glProgramUniform2f_hook( program_, location_, v0_, v1_ );
    F(program_, location_, v0_, v1_);
}
static glProgramUniform2fv_hook_t glProgramUniform2fv_hook = 0;
glProgramUniform2fv_hook_t getHook_glProgramUniform2fv (){
    return glProgramUniform2fv_hook ;
}
void setHook_glProgramUniform2fv ( glProgramUniform2fv_hook_t hook ){
    glProgramUniform2fv_hook = hook;
}
void glProgramUniform2fv ( GLuint program_, GLint location_, GLsizei count_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORM2FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM2FVPROC ) mygetprocaddr("glProgramUniform2fv");
    if( glProgramUniform2fv_hook )
        glProgramUniform2fv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform2i_hook_t glProgramUniform2i_hook = 0;
glProgramUniform2i_hook_t getHook_glProgramUniform2i (){
    return glProgramUniform2i_hook ;
}
void setHook_glProgramUniform2i ( glProgramUniform2i_hook_t hook ){
    glProgramUniform2i_hook = hook;
}
void glProgramUniform2i ( GLuint program_, GLint location_, GLint v0_, GLint v1_ ){
    static PFNGLPROGRAMUNIFORM2IPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM2IPROC ) mygetprocaddr("glProgramUniform2i");
    if( glProgramUniform2i_hook )
        glProgramUniform2i_hook( program_, location_, v0_, v1_ );
    F(program_, location_, v0_, v1_);
}
static glProgramUniform2iv_hook_t glProgramUniform2iv_hook = 0;
glProgramUniform2iv_hook_t getHook_glProgramUniform2iv (){
    return glProgramUniform2iv_hook ;
}
void setHook_glProgramUniform2iv ( glProgramUniform2iv_hook_t hook ){
    glProgramUniform2iv_hook = hook;
}
void glProgramUniform2iv ( GLuint program_, GLint location_, GLsizei count_, const GLint * value_ ){
    static PFNGLPROGRAMUNIFORM2IVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM2IVPROC ) mygetprocaddr("glProgramUniform2iv");
    if( glProgramUniform2iv_hook )
        glProgramUniform2iv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform2ui_hook_t glProgramUniform2ui_hook = 0;
glProgramUniform2ui_hook_t getHook_glProgramUniform2ui (){
    return glProgramUniform2ui_hook ;
}
void setHook_glProgramUniform2ui ( glProgramUniform2ui_hook_t hook ){
    glProgramUniform2ui_hook = hook;
}
void glProgramUniform2ui ( GLuint program_, GLint location_, GLuint v0_, GLuint v1_ ){
    static PFNGLPROGRAMUNIFORM2UIPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM2UIPROC ) mygetprocaddr("glProgramUniform2ui");
    if( glProgramUniform2ui_hook )
        glProgramUniform2ui_hook( program_, location_, v0_, v1_ );
    F(program_, location_, v0_, v1_);
}
static glProgramUniform2uiv_hook_t glProgramUniform2uiv_hook = 0;
glProgramUniform2uiv_hook_t getHook_glProgramUniform2uiv (){
    return glProgramUniform2uiv_hook ;
}
void setHook_glProgramUniform2uiv ( glProgramUniform2uiv_hook_t hook ){
    glProgramUniform2uiv_hook = hook;
}
void glProgramUniform2uiv ( GLuint program_, GLint location_, GLsizei count_, const GLuint * value_ ){
    static PFNGLPROGRAMUNIFORM2UIVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM2UIVPROC ) mygetprocaddr("glProgramUniform2uiv");
    if( glProgramUniform2uiv_hook )
        glProgramUniform2uiv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform3d_hook_t glProgramUniform3d_hook = 0;
glProgramUniform3d_hook_t getHook_glProgramUniform3d (){
    return glProgramUniform3d_hook ;
}
void setHook_glProgramUniform3d ( glProgramUniform3d_hook_t hook ){
    glProgramUniform3d_hook = hook;
}
void glProgramUniform3d ( GLuint program_, GLint location_, GLdouble v0_, GLdouble v1_, GLdouble v2_ ){
    static PFNGLPROGRAMUNIFORM3DPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM3DPROC ) mygetprocaddr("glProgramUniform3d");
    if( glProgramUniform3d_hook )
        glProgramUniform3d_hook( program_, location_, v0_, v1_, v2_ );
    F(program_, location_, v0_, v1_, v2_);
}
static glProgramUniform3dv_hook_t glProgramUniform3dv_hook = 0;
glProgramUniform3dv_hook_t getHook_glProgramUniform3dv (){
    return glProgramUniform3dv_hook ;
}
void setHook_glProgramUniform3dv ( glProgramUniform3dv_hook_t hook ){
    glProgramUniform3dv_hook = hook;
}
void glProgramUniform3dv ( GLuint program_, GLint location_, GLsizei count_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORM3DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM3DVPROC ) mygetprocaddr("glProgramUniform3dv");
    if( glProgramUniform3dv_hook )
        glProgramUniform3dv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform3f_hook_t glProgramUniform3f_hook = 0;
glProgramUniform3f_hook_t getHook_glProgramUniform3f (){
    return glProgramUniform3f_hook ;
}
void setHook_glProgramUniform3f ( glProgramUniform3f_hook_t hook ){
    glProgramUniform3f_hook = hook;
}
void glProgramUniform3f ( GLuint program_, GLint location_, GLfloat v0_, GLfloat v1_, GLfloat v2_ ){
    static PFNGLPROGRAMUNIFORM3FPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM3FPROC ) mygetprocaddr("glProgramUniform3f");
    if( glProgramUniform3f_hook )
        glProgramUniform3f_hook( program_, location_, v0_, v1_, v2_ );
    F(program_, location_, v0_, v1_, v2_);
}
static glProgramUniform3fv_hook_t glProgramUniform3fv_hook = 0;
glProgramUniform3fv_hook_t getHook_glProgramUniform3fv (){
    return glProgramUniform3fv_hook ;
}
void setHook_glProgramUniform3fv ( glProgramUniform3fv_hook_t hook ){
    glProgramUniform3fv_hook = hook;
}
void glProgramUniform3fv ( GLuint program_, GLint location_, GLsizei count_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORM3FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM3FVPROC ) mygetprocaddr("glProgramUniform3fv");
    if( glProgramUniform3fv_hook )
        glProgramUniform3fv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform3i_hook_t glProgramUniform3i_hook = 0;
glProgramUniform3i_hook_t getHook_glProgramUniform3i (){
    return glProgramUniform3i_hook ;
}
void setHook_glProgramUniform3i ( glProgramUniform3i_hook_t hook ){
    glProgramUniform3i_hook = hook;
}
void glProgramUniform3i ( GLuint program_, GLint location_, GLint v0_, GLint v1_, GLint v2_ ){
    static PFNGLPROGRAMUNIFORM3IPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM3IPROC ) mygetprocaddr("glProgramUniform3i");
    if( glProgramUniform3i_hook )
        glProgramUniform3i_hook( program_, location_, v0_, v1_, v2_ );
    F(program_, location_, v0_, v1_, v2_);
}
static glProgramUniform3iv_hook_t glProgramUniform3iv_hook = 0;
glProgramUniform3iv_hook_t getHook_glProgramUniform3iv (){
    return glProgramUniform3iv_hook ;
}
void setHook_glProgramUniform3iv ( glProgramUniform3iv_hook_t hook ){
    glProgramUniform3iv_hook = hook;
}
void glProgramUniform3iv ( GLuint program_, GLint location_, GLsizei count_, const GLint * value_ ){
    static PFNGLPROGRAMUNIFORM3IVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM3IVPROC ) mygetprocaddr("glProgramUniform3iv");
    if( glProgramUniform3iv_hook )
        glProgramUniform3iv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform3ui_hook_t glProgramUniform3ui_hook = 0;
glProgramUniform3ui_hook_t getHook_glProgramUniform3ui (){
    return glProgramUniform3ui_hook ;
}
void setHook_glProgramUniform3ui ( glProgramUniform3ui_hook_t hook ){
    glProgramUniform3ui_hook = hook;
}
void glProgramUniform3ui ( GLuint program_, GLint location_, GLuint v0_, GLuint v1_, GLuint v2_ ){
    static PFNGLPROGRAMUNIFORM3UIPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM3UIPROC ) mygetprocaddr("glProgramUniform3ui");
    if( glProgramUniform3ui_hook )
        glProgramUniform3ui_hook( program_, location_, v0_, v1_, v2_ );
    F(program_, location_, v0_, v1_, v2_);
}
static glProgramUniform3uiv_hook_t glProgramUniform3uiv_hook = 0;
glProgramUniform3uiv_hook_t getHook_glProgramUniform3uiv (){
    return glProgramUniform3uiv_hook ;
}
void setHook_glProgramUniform3uiv ( glProgramUniform3uiv_hook_t hook ){
    glProgramUniform3uiv_hook = hook;
}
void glProgramUniform3uiv ( GLuint program_, GLint location_, GLsizei count_, const GLuint * value_ ){
    static PFNGLPROGRAMUNIFORM3UIVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM3UIVPROC ) mygetprocaddr("glProgramUniform3uiv");
    if( glProgramUniform3uiv_hook )
        glProgramUniform3uiv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform4d_hook_t glProgramUniform4d_hook = 0;
glProgramUniform4d_hook_t getHook_glProgramUniform4d (){
    return glProgramUniform4d_hook ;
}
void setHook_glProgramUniform4d ( glProgramUniform4d_hook_t hook ){
    glProgramUniform4d_hook = hook;
}
void glProgramUniform4d ( GLuint program_, GLint location_, GLdouble v0_, GLdouble v1_, GLdouble v2_, GLdouble v3_ ){
    static PFNGLPROGRAMUNIFORM4DPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM4DPROC ) mygetprocaddr("glProgramUniform4d");
    if( glProgramUniform4d_hook )
        glProgramUniform4d_hook( program_, location_, v0_, v1_, v2_, v3_ );
    F(program_, location_, v0_, v1_, v2_, v3_);
}
static glProgramUniform4dv_hook_t glProgramUniform4dv_hook = 0;
glProgramUniform4dv_hook_t getHook_glProgramUniform4dv (){
    return glProgramUniform4dv_hook ;
}
void setHook_glProgramUniform4dv ( glProgramUniform4dv_hook_t hook ){
    glProgramUniform4dv_hook = hook;
}
void glProgramUniform4dv ( GLuint program_, GLint location_, GLsizei count_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORM4DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM4DVPROC ) mygetprocaddr("glProgramUniform4dv");
    if( glProgramUniform4dv_hook )
        glProgramUniform4dv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform4f_hook_t glProgramUniform4f_hook = 0;
glProgramUniform4f_hook_t getHook_glProgramUniform4f (){
    return glProgramUniform4f_hook ;
}
void setHook_glProgramUniform4f ( glProgramUniform4f_hook_t hook ){
    glProgramUniform4f_hook = hook;
}
void glProgramUniform4f ( GLuint program_, GLint location_, GLfloat v0_, GLfloat v1_, GLfloat v2_, GLfloat v3_ ){
    static PFNGLPROGRAMUNIFORM4FPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM4FPROC ) mygetprocaddr("glProgramUniform4f");
    if( glProgramUniform4f_hook )
        glProgramUniform4f_hook( program_, location_, v0_, v1_, v2_, v3_ );
    F(program_, location_, v0_, v1_, v2_, v3_);
}
static glProgramUniform4fv_hook_t glProgramUniform4fv_hook = 0;
glProgramUniform4fv_hook_t getHook_glProgramUniform4fv (){
    return glProgramUniform4fv_hook ;
}
void setHook_glProgramUniform4fv ( glProgramUniform4fv_hook_t hook ){
    glProgramUniform4fv_hook = hook;
}
void glProgramUniform4fv ( GLuint program_, GLint location_, GLsizei count_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORM4FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM4FVPROC ) mygetprocaddr("glProgramUniform4fv");
    if( glProgramUniform4fv_hook )
        glProgramUniform4fv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform4i_hook_t glProgramUniform4i_hook = 0;
glProgramUniform4i_hook_t getHook_glProgramUniform4i (){
    return glProgramUniform4i_hook ;
}
void setHook_glProgramUniform4i ( glProgramUniform4i_hook_t hook ){
    glProgramUniform4i_hook = hook;
}
void glProgramUniform4i ( GLuint program_, GLint location_, GLint v0_, GLint v1_, GLint v2_, GLint v3_ ){
    static PFNGLPROGRAMUNIFORM4IPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM4IPROC ) mygetprocaddr("glProgramUniform4i");
    if( glProgramUniform4i_hook )
        glProgramUniform4i_hook( program_, location_, v0_, v1_, v2_, v3_ );
    F(program_, location_, v0_, v1_, v2_, v3_);
}
static glProgramUniform4iv_hook_t glProgramUniform4iv_hook = 0;
glProgramUniform4iv_hook_t getHook_glProgramUniform4iv (){
    return glProgramUniform4iv_hook ;
}
void setHook_glProgramUniform4iv ( glProgramUniform4iv_hook_t hook ){
    glProgramUniform4iv_hook = hook;
}
void glProgramUniform4iv ( GLuint program_, GLint location_, GLsizei count_, const GLint * value_ ){
    static PFNGLPROGRAMUNIFORM4IVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM4IVPROC ) mygetprocaddr("glProgramUniform4iv");
    if( glProgramUniform4iv_hook )
        glProgramUniform4iv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniform4ui_hook_t glProgramUniform4ui_hook = 0;
glProgramUniform4ui_hook_t getHook_glProgramUniform4ui (){
    return glProgramUniform4ui_hook ;
}
void setHook_glProgramUniform4ui ( glProgramUniform4ui_hook_t hook ){
    glProgramUniform4ui_hook = hook;
}
void glProgramUniform4ui ( GLuint program_, GLint location_, GLuint v0_, GLuint v1_, GLuint v2_, GLuint v3_ ){
    static PFNGLPROGRAMUNIFORM4UIPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM4UIPROC ) mygetprocaddr("glProgramUniform4ui");
    if( glProgramUniform4ui_hook )
        glProgramUniform4ui_hook( program_, location_, v0_, v1_, v2_, v3_ );
    F(program_, location_, v0_, v1_, v2_, v3_);
}
static glProgramUniform4uiv_hook_t glProgramUniform4uiv_hook = 0;
glProgramUniform4uiv_hook_t getHook_glProgramUniform4uiv (){
    return glProgramUniform4uiv_hook ;
}
void setHook_glProgramUniform4uiv ( glProgramUniform4uiv_hook_t hook ){
    glProgramUniform4uiv_hook = hook;
}
void glProgramUniform4uiv ( GLuint program_, GLint location_, GLsizei count_, const GLuint * value_ ){
    static PFNGLPROGRAMUNIFORM4UIVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORM4UIVPROC ) mygetprocaddr("glProgramUniform4uiv");
    if( glProgramUniform4uiv_hook )
        glProgramUniform4uiv_hook( program_, location_, count_, value_ );
    F(program_, location_, count_, value_);
}
static glProgramUniformMatrix2dv_hook_t glProgramUniformMatrix2dv_hook = 0;
glProgramUniformMatrix2dv_hook_t getHook_glProgramUniformMatrix2dv (){
    return glProgramUniformMatrix2dv_hook ;
}
void setHook_glProgramUniformMatrix2dv ( glProgramUniformMatrix2dv_hook_t hook ){
    glProgramUniformMatrix2dv_hook = hook;
}
void glProgramUniformMatrix2dv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX2DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX2DVPROC ) mygetprocaddr("glProgramUniformMatrix2dv");
    if( glProgramUniformMatrix2dv_hook )
        glProgramUniformMatrix2dv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix2fv_hook_t glProgramUniformMatrix2fv_hook = 0;
glProgramUniformMatrix2fv_hook_t getHook_glProgramUniformMatrix2fv (){
    return glProgramUniformMatrix2fv_hook ;
}
void setHook_glProgramUniformMatrix2fv ( glProgramUniformMatrix2fv_hook_t hook ){
    glProgramUniformMatrix2fv_hook = hook;
}
void glProgramUniformMatrix2fv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX2FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX2FVPROC ) mygetprocaddr("glProgramUniformMatrix2fv");
    if( glProgramUniformMatrix2fv_hook )
        glProgramUniformMatrix2fv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix2x3dv_hook_t glProgramUniformMatrix2x3dv_hook = 0;
glProgramUniformMatrix2x3dv_hook_t getHook_glProgramUniformMatrix2x3dv (){
    return glProgramUniformMatrix2x3dv_hook ;
}
void setHook_glProgramUniformMatrix2x3dv ( glProgramUniformMatrix2x3dv_hook_t hook ){
    glProgramUniformMatrix2x3dv_hook = hook;
}
void glProgramUniformMatrix2x3dv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC ) mygetprocaddr("glProgramUniformMatrix2x3dv");
    if( glProgramUniformMatrix2x3dv_hook )
        glProgramUniformMatrix2x3dv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix2x3fv_hook_t glProgramUniformMatrix2x3fv_hook = 0;
glProgramUniformMatrix2x3fv_hook_t getHook_glProgramUniformMatrix2x3fv (){
    return glProgramUniformMatrix2x3fv_hook ;
}
void setHook_glProgramUniformMatrix2x3fv ( glProgramUniformMatrix2x3fv_hook_t hook ){
    glProgramUniformMatrix2x3fv_hook = hook;
}
void glProgramUniformMatrix2x3fv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC ) mygetprocaddr("glProgramUniformMatrix2x3fv");
    if( glProgramUniformMatrix2x3fv_hook )
        glProgramUniformMatrix2x3fv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix2x4dv_hook_t glProgramUniformMatrix2x4dv_hook = 0;
glProgramUniformMatrix2x4dv_hook_t getHook_glProgramUniformMatrix2x4dv (){
    return glProgramUniformMatrix2x4dv_hook ;
}
void setHook_glProgramUniformMatrix2x4dv ( glProgramUniformMatrix2x4dv_hook_t hook ){
    glProgramUniformMatrix2x4dv_hook = hook;
}
void glProgramUniformMatrix2x4dv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC ) mygetprocaddr("glProgramUniformMatrix2x4dv");
    if( glProgramUniformMatrix2x4dv_hook )
        glProgramUniformMatrix2x4dv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix2x4fv_hook_t glProgramUniformMatrix2x4fv_hook = 0;
glProgramUniformMatrix2x4fv_hook_t getHook_glProgramUniformMatrix2x4fv (){
    return glProgramUniformMatrix2x4fv_hook ;
}
void setHook_glProgramUniformMatrix2x4fv ( glProgramUniformMatrix2x4fv_hook_t hook ){
    glProgramUniformMatrix2x4fv_hook = hook;
}
void glProgramUniformMatrix2x4fv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC ) mygetprocaddr("glProgramUniformMatrix2x4fv");
    if( glProgramUniformMatrix2x4fv_hook )
        glProgramUniformMatrix2x4fv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix3dv_hook_t glProgramUniformMatrix3dv_hook = 0;
glProgramUniformMatrix3dv_hook_t getHook_glProgramUniformMatrix3dv (){
    return glProgramUniformMatrix3dv_hook ;
}
void setHook_glProgramUniformMatrix3dv ( glProgramUniformMatrix3dv_hook_t hook ){
    glProgramUniformMatrix3dv_hook = hook;
}
void glProgramUniformMatrix3dv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX3DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX3DVPROC ) mygetprocaddr("glProgramUniformMatrix3dv");
    if( glProgramUniformMatrix3dv_hook )
        glProgramUniformMatrix3dv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix3fv_hook_t glProgramUniformMatrix3fv_hook = 0;
glProgramUniformMatrix3fv_hook_t getHook_glProgramUniformMatrix3fv (){
    return glProgramUniformMatrix3fv_hook ;
}
void setHook_glProgramUniformMatrix3fv ( glProgramUniformMatrix3fv_hook_t hook ){
    glProgramUniformMatrix3fv_hook = hook;
}
void glProgramUniformMatrix3fv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX3FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX3FVPROC ) mygetprocaddr("glProgramUniformMatrix3fv");
    if( glProgramUniformMatrix3fv_hook )
        glProgramUniformMatrix3fv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix3x2dv_hook_t glProgramUniformMatrix3x2dv_hook = 0;
glProgramUniformMatrix3x2dv_hook_t getHook_glProgramUniformMatrix3x2dv (){
    return glProgramUniformMatrix3x2dv_hook ;
}
void setHook_glProgramUniformMatrix3x2dv ( glProgramUniformMatrix3x2dv_hook_t hook ){
    glProgramUniformMatrix3x2dv_hook = hook;
}
void glProgramUniformMatrix3x2dv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC ) mygetprocaddr("glProgramUniformMatrix3x2dv");
    if( glProgramUniformMatrix3x2dv_hook )
        glProgramUniformMatrix3x2dv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix3x2fv_hook_t glProgramUniformMatrix3x2fv_hook = 0;
glProgramUniformMatrix3x2fv_hook_t getHook_glProgramUniformMatrix3x2fv (){
    return glProgramUniformMatrix3x2fv_hook ;
}
void setHook_glProgramUniformMatrix3x2fv ( glProgramUniformMatrix3x2fv_hook_t hook ){
    glProgramUniformMatrix3x2fv_hook = hook;
}
void glProgramUniformMatrix3x2fv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC ) mygetprocaddr("glProgramUniformMatrix3x2fv");
    if( glProgramUniformMatrix3x2fv_hook )
        glProgramUniformMatrix3x2fv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix3x4dv_hook_t glProgramUniformMatrix3x4dv_hook = 0;
glProgramUniformMatrix3x4dv_hook_t getHook_glProgramUniformMatrix3x4dv (){
    return glProgramUniformMatrix3x4dv_hook ;
}
void setHook_glProgramUniformMatrix3x4dv ( glProgramUniformMatrix3x4dv_hook_t hook ){
    glProgramUniformMatrix3x4dv_hook = hook;
}
void glProgramUniformMatrix3x4dv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC ) mygetprocaddr("glProgramUniformMatrix3x4dv");
    if( glProgramUniformMatrix3x4dv_hook )
        glProgramUniformMatrix3x4dv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix3x4fv_hook_t glProgramUniformMatrix3x4fv_hook = 0;
glProgramUniformMatrix3x4fv_hook_t getHook_glProgramUniformMatrix3x4fv (){
    return glProgramUniformMatrix3x4fv_hook ;
}
void setHook_glProgramUniformMatrix3x4fv ( glProgramUniformMatrix3x4fv_hook_t hook ){
    glProgramUniformMatrix3x4fv_hook = hook;
}
void glProgramUniformMatrix3x4fv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC ) mygetprocaddr("glProgramUniformMatrix3x4fv");
    if( glProgramUniformMatrix3x4fv_hook )
        glProgramUniformMatrix3x4fv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix4dv_hook_t glProgramUniformMatrix4dv_hook = 0;
glProgramUniformMatrix4dv_hook_t getHook_glProgramUniformMatrix4dv (){
    return glProgramUniformMatrix4dv_hook ;
}
void setHook_glProgramUniformMatrix4dv ( glProgramUniformMatrix4dv_hook_t hook ){
    glProgramUniformMatrix4dv_hook = hook;
}
void glProgramUniformMatrix4dv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX4DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX4DVPROC ) mygetprocaddr("glProgramUniformMatrix4dv");
    if( glProgramUniformMatrix4dv_hook )
        glProgramUniformMatrix4dv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix4fv_hook_t glProgramUniformMatrix4fv_hook = 0;
glProgramUniformMatrix4fv_hook_t getHook_glProgramUniformMatrix4fv (){
    return glProgramUniformMatrix4fv_hook ;
}
void setHook_glProgramUniformMatrix4fv ( glProgramUniformMatrix4fv_hook_t hook ){
    glProgramUniformMatrix4fv_hook = hook;
}
void glProgramUniformMatrix4fv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX4FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX4FVPROC ) mygetprocaddr("glProgramUniformMatrix4fv");
    if( glProgramUniformMatrix4fv_hook )
        glProgramUniformMatrix4fv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix4x2dv_hook_t glProgramUniformMatrix4x2dv_hook = 0;
glProgramUniformMatrix4x2dv_hook_t getHook_glProgramUniformMatrix4x2dv (){
    return glProgramUniformMatrix4x2dv_hook ;
}
void setHook_glProgramUniformMatrix4x2dv ( glProgramUniformMatrix4x2dv_hook_t hook ){
    glProgramUniformMatrix4x2dv_hook = hook;
}
void glProgramUniformMatrix4x2dv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC ) mygetprocaddr("glProgramUniformMatrix4x2dv");
    if( glProgramUniformMatrix4x2dv_hook )
        glProgramUniformMatrix4x2dv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix4x2fv_hook_t glProgramUniformMatrix4x2fv_hook = 0;
glProgramUniformMatrix4x2fv_hook_t getHook_glProgramUniformMatrix4x2fv (){
    return glProgramUniformMatrix4x2fv_hook ;
}
void setHook_glProgramUniformMatrix4x2fv ( glProgramUniformMatrix4x2fv_hook_t hook ){
    glProgramUniformMatrix4x2fv_hook = hook;
}
void glProgramUniformMatrix4x2fv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC ) mygetprocaddr("glProgramUniformMatrix4x2fv");
    if( glProgramUniformMatrix4x2fv_hook )
        glProgramUniformMatrix4x2fv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix4x3dv_hook_t glProgramUniformMatrix4x3dv_hook = 0;
glProgramUniformMatrix4x3dv_hook_t getHook_glProgramUniformMatrix4x3dv (){
    return glProgramUniformMatrix4x3dv_hook ;
}
void setHook_glProgramUniformMatrix4x3dv ( glProgramUniformMatrix4x3dv_hook_t hook ){
    glProgramUniformMatrix4x3dv_hook = hook;
}
void glProgramUniformMatrix4x3dv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC ) mygetprocaddr("glProgramUniformMatrix4x3dv");
    if( glProgramUniformMatrix4x3dv_hook )
        glProgramUniformMatrix4x3dv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProgramUniformMatrix4x3fv_hook_t glProgramUniformMatrix4x3fv_hook = 0;
glProgramUniformMatrix4x3fv_hook_t getHook_glProgramUniformMatrix4x3fv (){
    return glProgramUniformMatrix4x3fv_hook ;
}
void setHook_glProgramUniformMatrix4x3fv ( glProgramUniformMatrix4x3fv_hook_t hook ){
    glProgramUniformMatrix4x3fv_hook = hook;
}
void glProgramUniformMatrix4x3fv ( GLuint program_, GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC F;
    if(!F)
        F = ( PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC ) mygetprocaddr("glProgramUniformMatrix4x3fv");
    if( glProgramUniformMatrix4x3fv_hook )
        glProgramUniformMatrix4x3fv_hook( program_, location_, count_, transpose_, value_ );
    F(program_, location_, count_, transpose_, value_);
}
static glProvokingVertex_hook_t glProvokingVertex_hook = 0;
glProvokingVertex_hook_t getHook_glProvokingVertex (){
    return glProvokingVertex_hook ;
}
void setHook_glProvokingVertex ( glProvokingVertex_hook_t hook ){
    glProvokingVertex_hook = hook;
}
void glProvokingVertex ( GLenum mode_ ){
    static PFNGLPROVOKINGVERTEXPROC F;
    if(!F)
        F = ( PFNGLPROVOKINGVERTEXPROC ) mygetprocaddr("glProvokingVertex");
    if( glProvokingVertex_hook )
        glProvokingVertex_hook( mode_ );
    F(mode_);
}
static glPushDebugGroup_hook_t glPushDebugGroup_hook = 0;
glPushDebugGroup_hook_t getHook_glPushDebugGroup (){
    return glPushDebugGroup_hook ;
}
void setHook_glPushDebugGroup ( glPushDebugGroup_hook_t hook ){
    glPushDebugGroup_hook = hook;
}
void glPushDebugGroup ( GLenum source_, GLuint id_, GLsizei length_, const GLchar * message_ ){
    static PFNGLPUSHDEBUGGROUPPROC F;
    if(!F)
        F = ( PFNGLPUSHDEBUGGROUPPROC ) mygetprocaddr("glPushDebugGroup");
    if( glPushDebugGroup_hook )
        glPushDebugGroup_hook( source_, id_, length_, message_ );
    F(source_, id_, length_, message_);
}
static glQueryCounter_hook_t glQueryCounter_hook = 0;
glQueryCounter_hook_t getHook_glQueryCounter (){
    return glQueryCounter_hook ;
}
void setHook_glQueryCounter ( glQueryCounter_hook_t hook ){
    glQueryCounter_hook = hook;
}
void glQueryCounter ( GLuint id_, GLenum target_ ){
    static PFNGLQUERYCOUNTERPROC F;
    if(!F)
        F = ( PFNGLQUERYCOUNTERPROC ) mygetprocaddr("glQueryCounter");
    if( glQueryCounter_hook )
        glQueryCounter_hook( id_, target_ );
    F(id_, target_);
}
static glReadBuffer_hook_t glReadBuffer_hook = 0;
glReadBuffer_hook_t getHook_glReadBuffer (){
    return glReadBuffer_hook ;
}
void setHook_glReadBuffer ( glReadBuffer_hook_t hook ){
    glReadBuffer_hook = hook;
}
void glReadBuffer ( GLenum src_ ){
    static PFNGLREADBUFFERPROC F;
    if(!F)
        F = ( PFNGLREADBUFFERPROC ) mygetprocaddr("glReadBuffer");
    if( glReadBuffer_hook )
        glReadBuffer_hook( src_ );
    F(src_);
}
static glReadPixels_hook_t glReadPixels_hook = 0;
glReadPixels_hook_t getHook_glReadPixels (){
    return glReadPixels_hook ;
}
void setHook_glReadPixels ( glReadPixels_hook_t hook ){
    glReadPixels_hook = hook;
}
void glReadPixels ( GLint x_, GLint y_, GLsizei width_, GLsizei height_, GLenum format_, GLenum type_, void * pixels_ ){
    static PFNGLREADPIXELSPROC F;
    if(!F)
        F = ( PFNGLREADPIXELSPROC ) mygetprocaddr("glReadPixels");
    if( glReadPixels_hook )
        glReadPixels_hook( x_, y_, width_, height_, format_, type_, pixels_ );
    F(x_, y_, width_, height_, format_, type_, pixels_);
}
static glReadnPixels_hook_t glReadnPixels_hook = 0;
glReadnPixels_hook_t getHook_glReadnPixels (){
    return glReadnPixels_hook ;
}
void setHook_glReadnPixels ( glReadnPixels_hook_t hook ){
    glReadnPixels_hook = hook;
}
void glReadnPixels ( GLint x_, GLint y_, GLsizei width_, GLsizei height_, GLenum format_, GLenum type_, GLsizei bufSize_, void * data_ ){
    static PFNGLREADNPIXELSPROC F;
    if(!F)
        F = ( PFNGLREADNPIXELSPROC ) mygetprocaddr("glReadnPixels");
    if( glReadnPixels_hook )
        glReadnPixels_hook( x_, y_, width_, height_, format_, type_, bufSize_, data_ );
    F(x_, y_, width_, height_, format_, type_, bufSize_, data_);
}
static glReleaseShaderCompiler_hook_t glReleaseShaderCompiler_hook = 0;
glReleaseShaderCompiler_hook_t getHook_glReleaseShaderCompiler (){
    return glReleaseShaderCompiler_hook ;
}
void setHook_glReleaseShaderCompiler ( glReleaseShaderCompiler_hook_t hook ){
    glReleaseShaderCompiler_hook = hook;
}
void glReleaseShaderCompiler (  ){
    static PFNGLRELEASESHADERCOMPILERPROC F;
    if(!F)
        F = ( PFNGLRELEASESHADERCOMPILERPROC ) mygetprocaddr("glReleaseShaderCompiler");
    if( glReleaseShaderCompiler_hook )
        glReleaseShaderCompiler_hook(  );
    F();
}
static glRenderbufferStorage_hook_t glRenderbufferStorage_hook = 0;
glRenderbufferStorage_hook_t getHook_glRenderbufferStorage (){
    return glRenderbufferStorage_hook ;
}
void setHook_glRenderbufferStorage ( glRenderbufferStorage_hook_t hook ){
    glRenderbufferStorage_hook = hook;
}
void glRenderbufferStorage ( GLenum target_, GLenum internalformat_, GLsizei width_, GLsizei height_ ){
    static PFNGLRENDERBUFFERSTORAGEPROC F;
    if(!F)
        F = ( PFNGLRENDERBUFFERSTORAGEPROC ) mygetprocaddr("glRenderbufferStorage");
    if( glRenderbufferStorage_hook )
        glRenderbufferStorage_hook( target_, internalformat_, width_, height_ );
    F(target_, internalformat_, width_, height_);
}
static glRenderbufferStorageMultisample_hook_t glRenderbufferStorageMultisample_hook = 0;
glRenderbufferStorageMultisample_hook_t getHook_glRenderbufferStorageMultisample (){
    return glRenderbufferStorageMultisample_hook ;
}
void setHook_glRenderbufferStorageMultisample ( glRenderbufferStorageMultisample_hook_t hook ){
    glRenderbufferStorageMultisample_hook = hook;
}
void glRenderbufferStorageMultisample ( GLenum target_, GLsizei samples_, GLenum internalformat_, GLsizei width_, GLsizei height_ ){
    static PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC F;
    if(!F)
        F = ( PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC ) mygetprocaddr("glRenderbufferStorageMultisample");
    if( glRenderbufferStorageMultisample_hook )
        glRenderbufferStorageMultisample_hook( target_, samples_, internalformat_, width_, height_ );
    F(target_, samples_, internalformat_, width_, height_);
}
static glResumeTransformFeedback_hook_t glResumeTransformFeedback_hook = 0;
glResumeTransformFeedback_hook_t getHook_glResumeTransformFeedback (){
    return glResumeTransformFeedback_hook ;
}
void setHook_glResumeTransformFeedback ( glResumeTransformFeedback_hook_t hook ){
    glResumeTransformFeedback_hook = hook;
}
void glResumeTransformFeedback (  ){
    static PFNGLRESUMETRANSFORMFEEDBACKPROC F;
    if(!F)
        F = ( PFNGLRESUMETRANSFORMFEEDBACKPROC ) mygetprocaddr("glResumeTransformFeedback");
    if( glResumeTransformFeedback_hook )
        glResumeTransformFeedback_hook(  );
    F();
}
static glSampleCoverage_hook_t glSampleCoverage_hook = 0;
glSampleCoverage_hook_t getHook_glSampleCoverage (){
    return glSampleCoverage_hook ;
}
void setHook_glSampleCoverage ( glSampleCoverage_hook_t hook ){
    glSampleCoverage_hook = hook;
}
void glSampleCoverage ( GLfloat value_, GLboolean invert_ ){
    static PFNGLSAMPLECOVERAGEPROC F;
    if(!F)
        F = ( PFNGLSAMPLECOVERAGEPROC ) mygetprocaddr("glSampleCoverage");
    if( glSampleCoverage_hook )
        glSampleCoverage_hook( value_, invert_ );
    F(value_, invert_);
}
static glSampleMaski_hook_t glSampleMaski_hook = 0;
glSampleMaski_hook_t getHook_glSampleMaski (){
    return glSampleMaski_hook ;
}
void setHook_glSampleMaski ( glSampleMaski_hook_t hook ){
    glSampleMaski_hook = hook;
}
void glSampleMaski ( GLuint maskNumber_, GLbitfield mask_ ){
    static PFNGLSAMPLEMASKIPROC F;
    if(!F)
        F = ( PFNGLSAMPLEMASKIPROC ) mygetprocaddr("glSampleMaski");
    if( glSampleMaski_hook )
        glSampleMaski_hook( maskNumber_, mask_ );
    F(maskNumber_, mask_);
}
static glSamplerParameterIiv_hook_t glSamplerParameterIiv_hook = 0;
glSamplerParameterIiv_hook_t getHook_glSamplerParameterIiv (){
    return glSamplerParameterIiv_hook ;
}
void setHook_glSamplerParameterIiv ( glSamplerParameterIiv_hook_t hook ){
    glSamplerParameterIiv_hook = hook;
}
void glSamplerParameterIiv ( GLuint sampler_, GLenum pname_, const GLint * param_ ){
    static PFNGLSAMPLERPARAMETERIIVPROC F;
    if(!F)
        F = ( PFNGLSAMPLERPARAMETERIIVPROC ) mygetprocaddr("glSamplerParameterIiv");
    if( glSamplerParameterIiv_hook )
        glSamplerParameterIiv_hook( sampler_, pname_, param_ );
    F(sampler_, pname_, param_);
}
static glSamplerParameterIuiv_hook_t glSamplerParameterIuiv_hook = 0;
glSamplerParameterIuiv_hook_t getHook_glSamplerParameterIuiv (){
    return glSamplerParameterIuiv_hook ;
}
void setHook_glSamplerParameterIuiv ( glSamplerParameterIuiv_hook_t hook ){
    glSamplerParameterIuiv_hook = hook;
}
void glSamplerParameterIuiv ( GLuint sampler_, GLenum pname_, const GLuint * param_ ){
    static PFNGLSAMPLERPARAMETERIUIVPROC F;
    if(!F)
        F = ( PFNGLSAMPLERPARAMETERIUIVPROC ) mygetprocaddr("glSamplerParameterIuiv");
    if( glSamplerParameterIuiv_hook )
        glSamplerParameterIuiv_hook( sampler_, pname_, param_ );
    F(sampler_, pname_, param_);
}
static glSamplerParameterf_hook_t glSamplerParameterf_hook = 0;
glSamplerParameterf_hook_t getHook_glSamplerParameterf (){
    return glSamplerParameterf_hook ;
}
void setHook_glSamplerParameterf ( glSamplerParameterf_hook_t hook ){
    glSamplerParameterf_hook = hook;
}
void glSamplerParameterf ( GLuint sampler_, GLenum pname_, GLfloat param_ ){
    static PFNGLSAMPLERPARAMETERFPROC F;
    if(!F)
        F = ( PFNGLSAMPLERPARAMETERFPROC ) mygetprocaddr("glSamplerParameterf");
    if( glSamplerParameterf_hook )
        glSamplerParameterf_hook( sampler_, pname_, param_ );
    F(sampler_, pname_, param_);
}
static glSamplerParameterfv_hook_t glSamplerParameterfv_hook = 0;
glSamplerParameterfv_hook_t getHook_glSamplerParameterfv (){
    return glSamplerParameterfv_hook ;
}
void setHook_glSamplerParameterfv ( glSamplerParameterfv_hook_t hook ){
    glSamplerParameterfv_hook = hook;
}
void glSamplerParameterfv ( GLuint sampler_, GLenum pname_, const GLfloat * param_ ){
    static PFNGLSAMPLERPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLSAMPLERPARAMETERFVPROC ) mygetprocaddr("glSamplerParameterfv");
    if( glSamplerParameterfv_hook )
        glSamplerParameterfv_hook( sampler_, pname_, param_ );
    F(sampler_, pname_, param_);
}
static glSamplerParameteri_hook_t glSamplerParameteri_hook = 0;
glSamplerParameteri_hook_t getHook_glSamplerParameteri (){
    return glSamplerParameteri_hook ;
}
void setHook_glSamplerParameteri ( glSamplerParameteri_hook_t hook ){
    glSamplerParameteri_hook = hook;
}
void glSamplerParameteri ( GLuint sampler_, GLenum pname_, GLint param_ ){
    static PFNGLSAMPLERPARAMETERIPROC F;
    if(!F)
        F = ( PFNGLSAMPLERPARAMETERIPROC ) mygetprocaddr("glSamplerParameteri");
    if( glSamplerParameteri_hook )
        glSamplerParameteri_hook( sampler_, pname_, param_ );
    F(sampler_, pname_, param_);
}
static glSamplerParameteriv_hook_t glSamplerParameteriv_hook = 0;
glSamplerParameteriv_hook_t getHook_glSamplerParameteriv (){
    return glSamplerParameteriv_hook ;
}
void setHook_glSamplerParameteriv ( glSamplerParameteriv_hook_t hook ){
    glSamplerParameteriv_hook = hook;
}
void glSamplerParameteriv ( GLuint sampler_, GLenum pname_, const GLint * param_ ){
    static PFNGLSAMPLERPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLSAMPLERPARAMETERIVPROC ) mygetprocaddr("glSamplerParameteriv");
    if( glSamplerParameteriv_hook )
        glSamplerParameteriv_hook( sampler_, pname_, param_ );
    F(sampler_, pname_, param_);
}
static glScissor_hook_t glScissor_hook = 0;
glScissor_hook_t getHook_glScissor (){
    return glScissor_hook ;
}
void setHook_glScissor ( glScissor_hook_t hook ){
    glScissor_hook = hook;
}
void glScissor ( GLint x_, GLint y_, GLsizei width_, GLsizei height_ ){
    static PFNGLSCISSORPROC F;
    if(!F)
        F = ( PFNGLSCISSORPROC ) mygetprocaddr("glScissor");
    if( glScissor_hook )
        glScissor_hook( x_, y_, width_, height_ );
    F(x_, y_, width_, height_);
}
static glScissorArrayv_hook_t glScissorArrayv_hook = 0;
glScissorArrayv_hook_t getHook_glScissorArrayv (){
    return glScissorArrayv_hook ;
}
void setHook_glScissorArrayv ( glScissorArrayv_hook_t hook ){
    glScissorArrayv_hook = hook;
}
void glScissorArrayv ( GLuint first_, GLsizei count_, const GLint * v_ ){
    static PFNGLSCISSORARRAYVPROC F;
    if(!F)
        F = ( PFNGLSCISSORARRAYVPROC ) mygetprocaddr("glScissorArrayv");
    if( glScissorArrayv_hook )
        glScissorArrayv_hook( first_, count_, v_ );
    F(first_, count_, v_);
}
static glScissorIndexed_hook_t glScissorIndexed_hook = 0;
glScissorIndexed_hook_t getHook_glScissorIndexed (){
    return glScissorIndexed_hook ;
}
void setHook_glScissorIndexed ( glScissorIndexed_hook_t hook ){
    glScissorIndexed_hook = hook;
}
void glScissorIndexed ( GLuint index_, GLint left_, GLint bottom_, GLsizei width_, GLsizei height_ ){
    static PFNGLSCISSORINDEXEDPROC F;
    if(!F)
        F = ( PFNGLSCISSORINDEXEDPROC ) mygetprocaddr("glScissorIndexed");
    if( glScissorIndexed_hook )
        glScissorIndexed_hook( index_, left_, bottom_, width_, height_ );
    F(index_, left_, bottom_, width_, height_);
}
static glScissorIndexedv_hook_t glScissorIndexedv_hook = 0;
glScissorIndexedv_hook_t getHook_glScissorIndexedv (){
    return glScissorIndexedv_hook ;
}
void setHook_glScissorIndexedv ( glScissorIndexedv_hook_t hook ){
    glScissorIndexedv_hook = hook;
}
void glScissorIndexedv ( GLuint index_, const GLint * v_ ){
    static PFNGLSCISSORINDEXEDVPROC F;
    if(!F)
        F = ( PFNGLSCISSORINDEXEDVPROC ) mygetprocaddr("glScissorIndexedv");
    if( glScissorIndexedv_hook )
        glScissorIndexedv_hook( index_, v_ );
    F(index_, v_);
}
static glShaderBinary_hook_t glShaderBinary_hook = 0;
glShaderBinary_hook_t getHook_glShaderBinary (){
    return glShaderBinary_hook ;
}
void setHook_glShaderBinary ( glShaderBinary_hook_t hook ){
    glShaderBinary_hook = hook;
}
void glShaderBinary ( GLsizei count_, const GLuint * shaders_, GLenum binaryformat_, const void * binary_, GLsizei length_ ){
    static PFNGLSHADERBINARYPROC F;
    if(!F)
        F = ( PFNGLSHADERBINARYPROC ) mygetprocaddr("glShaderBinary");
    if( glShaderBinary_hook )
        glShaderBinary_hook( count_, shaders_, binaryformat_, binary_, length_ );
    F(count_, shaders_, binaryformat_, binary_, length_);
}
static glShaderSource_hook_t glShaderSource_hook = 0;
glShaderSource_hook_t getHook_glShaderSource (){
    return glShaderSource_hook ;
}
void setHook_glShaderSource ( glShaderSource_hook_t hook ){
    glShaderSource_hook = hook;
}
void glShaderSource ( GLuint shader_, GLsizei count_, const GLchar ** string_, const GLint * length_ ){
    static PFNGLSHADERSOURCEPROC F;
    if(!F)
        F = ( PFNGLSHADERSOURCEPROC ) mygetprocaddr("glShaderSource");
    if( glShaderSource_hook )
        glShaderSource_hook( shader_, count_, string_, length_ );
    F(shader_, count_, string_, length_);
}
static glShaderStorageBlockBinding_hook_t glShaderStorageBlockBinding_hook = 0;
glShaderStorageBlockBinding_hook_t getHook_glShaderStorageBlockBinding (){
    return glShaderStorageBlockBinding_hook ;
}
void setHook_glShaderStorageBlockBinding ( glShaderStorageBlockBinding_hook_t hook ){
    glShaderStorageBlockBinding_hook = hook;
}
void glShaderStorageBlockBinding ( GLuint program_, GLuint storageBlockIndex_, GLuint storageBlockBinding_ ){
    static PFNGLSHADERSTORAGEBLOCKBINDINGPROC F;
    if(!F)
        F = ( PFNGLSHADERSTORAGEBLOCKBINDINGPROC ) mygetprocaddr("glShaderStorageBlockBinding");
    if( glShaderStorageBlockBinding_hook )
        glShaderStorageBlockBinding_hook( program_, storageBlockIndex_, storageBlockBinding_ );
    F(program_, storageBlockIndex_, storageBlockBinding_);
}
static glStencilFunc_hook_t glStencilFunc_hook = 0;
glStencilFunc_hook_t getHook_glStencilFunc (){
    return glStencilFunc_hook ;
}
void setHook_glStencilFunc ( glStencilFunc_hook_t hook ){
    glStencilFunc_hook = hook;
}
void glStencilFunc ( GLenum func_, GLint ref_, GLuint mask_ ){
    static PFNGLSTENCILFUNCPROC F;
    if(!F)
        F = ( PFNGLSTENCILFUNCPROC ) mygetprocaddr("glStencilFunc");
    if( glStencilFunc_hook )
        glStencilFunc_hook( func_, ref_, mask_ );
    F(func_, ref_, mask_);
}
static glStencilFuncSeparate_hook_t glStencilFuncSeparate_hook = 0;
glStencilFuncSeparate_hook_t getHook_glStencilFuncSeparate (){
    return glStencilFuncSeparate_hook ;
}
void setHook_glStencilFuncSeparate ( glStencilFuncSeparate_hook_t hook ){
    glStencilFuncSeparate_hook = hook;
}
void glStencilFuncSeparate ( GLenum face_, GLenum func_, GLint ref_, GLuint mask_ ){
    static PFNGLSTENCILFUNCSEPARATEPROC F;
    if(!F)
        F = ( PFNGLSTENCILFUNCSEPARATEPROC ) mygetprocaddr("glStencilFuncSeparate");
    if( glStencilFuncSeparate_hook )
        glStencilFuncSeparate_hook( face_, func_, ref_, mask_ );
    F(face_, func_, ref_, mask_);
}
static glStencilMask_hook_t glStencilMask_hook = 0;
glStencilMask_hook_t getHook_glStencilMask (){
    return glStencilMask_hook ;
}
void setHook_glStencilMask ( glStencilMask_hook_t hook ){
    glStencilMask_hook = hook;
}
void glStencilMask ( GLuint mask_ ){
    static PFNGLSTENCILMASKPROC F;
    if(!F)
        F = ( PFNGLSTENCILMASKPROC ) mygetprocaddr("glStencilMask");
    if( glStencilMask_hook )
        glStencilMask_hook( mask_ );
    F(mask_);
}
static glStencilMaskSeparate_hook_t glStencilMaskSeparate_hook = 0;
glStencilMaskSeparate_hook_t getHook_glStencilMaskSeparate (){
    return glStencilMaskSeparate_hook ;
}
void setHook_glStencilMaskSeparate ( glStencilMaskSeparate_hook_t hook ){
    glStencilMaskSeparate_hook = hook;
}
void glStencilMaskSeparate ( GLenum face_, GLuint mask_ ){
    static PFNGLSTENCILMASKSEPARATEPROC F;
    if(!F)
        F = ( PFNGLSTENCILMASKSEPARATEPROC ) mygetprocaddr("glStencilMaskSeparate");
    if( glStencilMaskSeparate_hook )
        glStencilMaskSeparate_hook( face_, mask_ );
    F(face_, mask_);
}
static glStencilOp_hook_t glStencilOp_hook = 0;
glStencilOp_hook_t getHook_glStencilOp (){
    return glStencilOp_hook ;
}
void setHook_glStencilOp ( glStencilOp_hook_t hook ){
    glStencilOp_hook = hook;
}
void glStencilOp ( GLenum fail_, GLenum zfail_, GLenum zpass_ ){
    static PFNGLSTENCILOPPROC F;
    if(!F)
        F = ( PFNGLSTENCILOPPROC ) mygetprocaddr("glStencilOp");
    if( glStencilOp_hook )
        glStencilOp_hook( fail_, zfail_, zpass_ );
    F(fail_, zfail_, zpass_);
}
static glStencilOpSeparate_hook_t glStencilOpSeparate_hook = 0;
glStencilOpSeparate_hook_t getHook_glStencilOpSeparate (){
    return glStencilOpSeparate_hook ;
}
void setHook_glStencilOpSeparate ( glStencilOpSeparate_hook_t hook ){
    glStencilOpSeparate_hook = hook;
}
void glStencilOpSeparate ( GLenum face_, GLenum sfail_, GLenum dpfail_, GLenum dppass_ ){
    static PFNGLSTENCILOPSEPARATEPROC F;
    if(!F)
        F = ( PFNGLSTENCILOPSEPARATEPROC ) mygetprocaddr("glStencilOpSeparate");
    if( glStencilOpSeparate_hook )
        glStencilOpSeparate_hook( face_, sfail_, dpfail_, dppass_ );
    F(face_, sfail_, dpfail_, dppass_);
}
static glTexBuffer_hook_t glTexBuffer_hook = 0;
glTexBuffer_hook_t getHook_glTexBuffer (){
    return glTexBuffer_hook ;
}
void setHook_glTexBuffer ( glTexBuffer_hook_t hook ){
    glTexBuffer_hook = hook;
}
void glTexBuffer ( GLenum target_, GLenum internalformat_, GLuint buffer_ ){
    static PFNGLTEXBUFFERPROC F;
    if(!F)
        F = ( PFNGLTEXBUFFERPROC ) mygetprocaddr("glTexBuffer");
    if( glTexBuffer_hook )
        glTexBuffer_hook( target_, internalformat_, buffer_ );
    F(target_, internalformat_, buffer_);
}
static glTexBufferRange_hook_t glTexBufferRange_hook = 0;
glTexBufferRange_hook_t getHook_glTexBufferRange (){
    return glTexBufferRange_hook ;
}
void setHook_glTexBufferRange ( glTexBufferRange_hook_t hook ){
    glTexBufferRange_hook = hook;
}
void glTexBufferRange ( GLenum target_, GLenum internalformat_, GLuint buffer_, GLintptr offset_, GLsizeiptr size_ ){
    static PFNGLTEXBUFFERRANGEPROC F;
    if(!F)
        F = ( PFNGLTEXBUFFERRANGEPROC ) mygetprocaddr("glTexBufferRange");
    if( glTexBufferRange_hook )
        glTexBufferRange_hook( target_, internalformat_, buffer_, offset_, size_ );
    F(target_, internalformat_, buffer_, offset_, size_);
}
static glTexImage1D_hook_t glTexImage1D_hook = 0;
glTexImage1D_hook_t getHook_glTexImage1D (){
    return glTexImage1D_hook ;
}
void setHook_glTexImage1D ( glTexImage1D_hook_t hook ){
    glTexImage1D_hook = hook;
}
void glTexImage1D ( GLenum target_, GLint level_, GLint internalformat_, GLsizei width_, GLint border_, GLenum format_, GLenum type_, const void * pixels_ ){
    static PFNGLTEXIMAGE1DPROC F;
    if(!F)
        F = ( PFNGLTEXIMAGE1DPROC ) mygetprocaddr("glTexImage1D");
    if( glTexImage1D_hook )
        glTexImage1D_hook( target_, level_, internalformat_, width_, border_, format_, type_, pixels_ );
    F(target_, level_, internalformat_, width_, border_, format_, type_, pixels_);
}
static glTexImage2D_hook_t glTexImage2D_hook = 0;
glTexImage2D_hook_t getHook_glTexImage2D (){
    return glTexImage2D_hook ;
}
void setHook_glTexImage2D ( glTexImage2D_hook_t hook ){
    glTexImage2D_hook = hook;
}
void glTexImage2D ( GLenum target_, GLint level_, GLint internalformat_, GLsizei width_, GLsizei height_, GLint border_, GLenum format_, GLenum type_, const void * pixels_ ){
    static PFNGLTEXIMAGE2DPROC F;
    if(!F)
        F = ( PFNGLTEXIMAGE2DPROC ) mygetprocaddr("glTexImage2D");
    if( glTexImage2D_hook )
        glTexImage2D_hook( target_, level_, internalformat_, width_, height_, border_, format_, type_, pixels_ );
    F(target_, level_, internalformat_, width_, height_, border_, format_, type_, pixels_);
}
static glTexImage3D_hook_t glTexImage3D_hook = 0;
glTexImage3D_hook_t getHook_glTexImage3D (){
    return glTexImage3D_hook ;
}
void setHook_glTexImage3D ( glTexImage3D_hook_t hook ){
    glTexImage3D_hook = hook;
}
void glTexImage3D ( GLenum target_, GLint level_, GLint internalformat_, GLsizei width_, GLsizei height_, GLsizei depth_, GLint border_, GLenum format_, GLenum type_, const void * pixels_ ){
    static PFNGLTEXIMAGE3DPROC F;
    if(!F)
        F = ( PFNGLTEXIMAGE3DPROC ) mygetprocaddr("glTexImage3D");
    if( glTexImage3D_hook )
        glTexImage3D_hook( target_, level_, internalformat_, width_, height_, depth_, border_, format_, type_, pixels_ );
    F(target_, level_, internalformat_, width_, height_, depth_, border_, format_, type_, pixels_);
}
static glTexParameterIiv_hook_t glTexParameterIiv_hook = 0;
glTexParameterIiv_hook_t getHook_glTexParameterIiv (){
    return glTexParameterIiv_hook ;
}
void setHook_glTexParameterIiv ( glTexParameterIiv_hook_t hook ){
    glTexParameterIiv_hook = hook;
}
void glTexParameterIiv ( GLenum target_, GLenum pname_, const GLint * params_ ){
    static PFNGLTEXPARAMETERIIVPROC F;
    if(!F)
        F = ( PFNGLTEXPARAMETERIIVPROC ) mygetprocaddr("glTexParameterIiv");
    if( glTexParameterIiv_hook )
        glTexParameterIiv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glTexParameterIuiv_hook_t glTexParameterIuiv_hook = 0;
glTexParameterIuiv_hook_t getHook_glTexParameterIuiv (){
    return glTexParameterIuiv_hook ;
}
void setHook_glTexParameterIuiv ( glTexParameterIuiv_hook_t hook ){
    glTexParameterIuiv_hook = hook;
}
void glTexParameterIuiv ( GLenum target_, GLenum pname_, const GLuint * params_ ){
    static PFNGLTEXPARAMETERIUIVPROC F;
    if(!F)
        F = ( PFNGLTEXPARAMETERIUIVPROC ) mygetprocaddr("glTexParameterIuiv");
    if( glTexParameterIuiv_hook )
        glTexParameterIuiv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glTexParameterf_hook_t glTexParameterf_hook = 0;
glTexParameterf_hook_t getHook_glTexParameterf (){
    return glTexParameterf_hook ;
}
void setHook_glTexParameterf ( glTexParameterf_hook_t hook ){
    glTexParameterf_hook = hook;
}
void glTexParameterf ( GLenum target_, GLenum pname_, GLfloat param_ ){
    static PFNGLTEXPARAMETERFPROC F;
    if(!F)
        F = ( PFNGLTEXPARAMETERFPROC ) mygetprocaddr("glTexParameterf");
    if( glTexParameterf_hook )
        glTexParameterf_hook( target_, pname_, param_ );
    F(target_, pname_, param_);
}
static glTexParameterfv_hook_t glTexParameterfv_hook = 0;
glTexParameterfv_hook_t getHook_glTexParameterfv (){
    return glTexParameterfv_hook ;
}
void setHook_glTexParameterfv ( glTexParameterfv_hook_t hook ){
    glTexParameterfv_hook = hook;
}
void glTexParameterfv ( GLenum target_, GLenum pname_, const GLfloat * params_ ){
    static PFNGLTEXPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLTEXPARAMETERFVPROC ) mygetprocaddr("glTexParameterfv");
    if( glTexParameterfv_hook )
        glTexParameterfv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glTexParameteri_hook_t glTexParameteri_hook = 0;
glTexParameteri_hook_t getHook_glTexParameteri (){
    return glTexParameteri_hook ;
}
void setHook_glTexParameteri ( glTexParameteri_hook_t hook ){
    glTexParameteri_hook = hook;
}
void glTexParameteri ( GLenum target_, GLenum pname_, GLint param_ ){
    static PFNGLTEXPARAMETERIPROC F;
    if(!F)
        F = ( PFNGLTEXPARAMETERIPROC ) mygetprocaddr("glTexParameteri");
    if( glTexParameteri_hook )
        glTexParameteri_hook( target_, pname_, param_ );
    F(target_, pname_, param_);
}
static glTexParameteriv_hook_t glTexParameteriv_hook = 0;
glTexParameteriv_hook_t getHook_glTexParameteriv (){
    return glTexParameteriv_hook ;
}
void setHook_glTexParameteriv ( glTexParameteriv_hook_t hook ){
    glTexParameteriv_hook = hook;
}
void glTexParameteriv ( GLenum target_, GLenum pname_, const GLint * params_ ){
    static PFNGLTEXPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLTEXPARAMETERIVPROC ) mygetprocaddr("glTexParameteriv");
    if( glTexParameteriv_hook )
        glTexParameteriv_hook( target_, pname_, params_ );
    F(target_, pname_, params_);
}
static glTexStorage1D_hook_t glTexStorage1D_hook = 0;
glTexStorage1D_hook_t getHook_glTexStorage1D (){
    return glTexStorage1D_hook ;
}
void setHook_glTexStorage1D ( glTexStorage1D_hook_t hook ){
    glTexStorage1D_hook = hook;
}
void glTexStorage1D ( GLenum target_, GLsizei levels_, GLenum internalformat_, GLsizei width_ ){
    static PFNGLTEXSTORAGE1DPROC F;
    if(!F)
        F = ( PFNGLTEXSTORAGE1DPROC ) mygetprocaddr("glTexStorage1D");
    if( glTexStorage1D_hook )
        glTexStorage1D_hook( target_, levels_, internalformat_, width_ );
    F(target_, levels_, internalformat_, width_);
}
static glTexStorage2D_hook_t glTexStorage2D_hook = 0;
glTexStorage2D_hook_t getHook_glTexStorage2D (){
    return glTexStorage2D_hook ;
}
void setHook_glTexStorage2D ( glTexStorage2D_hook_t hook ){
    glTexStorage2D_hook = hook;
}
void glTexStorage2D ( GLenum target_, GLsizei levels_, GLenum internalformat_, GLsizei width_, GLsizei height_ ){
    static PFNGLTEXSTORAGE2DPROC F;
    if(!F)
        F = ( PFNGLTEXSTORAGE2DPROC ) mygetprocaddr("glTexStorage2D");
    if( glTexStorage2D_hook )
        glTexStorage2D_hook( target_, levels_, internalformat_, width_, height_ );
    F(target_, levels_, internalformat_, width_, height_);
}
static glTexStorage3D_hook_t glTexStorage3D_hook = 0;
glTexStorage3D_hook_t getHook_glTexStorage3D (){
    return glTexStorage3D_hook ;
}
void setHook_glTexStorage3D ( glTexStorage3D_hook_t hook ){
    glTexStorage3D_hook = hook;
}
void glTexStorage3D ( GLenum target_, GLsizei levels_, GLenum internalformat_, GLsizei width_, GLsizei height_, GLsizei depth_ ){
    static PFNGLTEXSTORAGE3DPROC F;
    if(!F)
        F = ( PFNGLTEXSTORAGE3DPROC ) mygetprocaddr("glTexStorage3D");
    if( glTexStorage3D_hook )
        glTexStorage3D_hook( target_, levels_, internalformat_, width_, height_, depth_ );
    F(target_, levels_, internalformat_, width_, height_, depth_);
}
static glTexSubImage1D_hook_t glTexSubImage1D_hook = 0;
glTexSubImage1D_hook_t getHook_glTexSubImage1D (){
    return glTexSubImage1D_hook ;
}
void setHook_glTexSubImage1D ( glTexSubImage1D_hook_t hook ){
    glTexSubImage1D_hook = hook;
}
void glTexSubImage1D ( GLenum target_, GLint level_, GLint xoffset_, GLsizei width_, GLenum format_, GLenum type_, const void * pixels_ ){
    static PFNGLTEXSUBIMAGE1DPROC F;
    if(!F)
        F = ( PFNGLTEXSUBIMAGE1DPROC ) mygetprocaddr("glTexSubImage1D");
    if( glTexSubImage1D_hook )
        glTexSubImage1D_hook( target_, level_, xoffset_, width_, format_, type_, pixels_ );
    F(target_, level_, xoffset_, width_, format_, type_, pixels_);
}
static glTexSubImage2D_hook_t glTexSubImage2D_hook = 0;
glTexSubImage2D_hook_t getHook_glTexSubImage2D (){
    return glTexSubImage2D_hook ;
}
void setHook_glTexSubImage2D ( glTexSubImage2D_hook_t hook ){
    glTexSubImage2D_hook = hook;
}
void glTexSubImage2D ( GLenum target_, GLint level_, GLint xoffset_, GLint yoffset_, GLsizei width_, GLsizei height_, GLenum format_, GLenum type_, const void * pixels_ ){
    static PFNGLTEXSUBIMAGE2DPROC F;
    if(!F)
        F = ( PFNGLTEXSUBIMAGE2DPROC ) mygetprocaddr("glTexSubImage2D");
    if( glTexSubImage2D_hook )
        glTexSubImage2D_hook( target_, level_, xoffset_, yoffset_, width_, height_, format_, type_, pixels_ );
    F(target_, level_, xoffset_, yoffset_, width_, height_, format_, type_, pixels_);
}
static glTexSubImage3D_hook_t glTexSubImage3D_hook = 0;
glTexSubImage3D_hook_t getHook_glTexSubImage3D (){
    return glTexSubImage3D_hook ;
}
void setHook_glTexSubImage3D ( glTexSubImage3D_hook_t hook ){
    glTexSubImage3D_hook = hook;
}
void glTexSubImage3D ( GLenum target_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLsizei width_, GLsizei height_, GLsizei depth_, GLenum format_, GLenum type_, const void * pixels_ ){
    static PFNGLTEXSUBIMAGE3DPROC F;
    if(!F)
        F = ( PFNGLTEXSUBIMAGE3DPROC ) mygetprocaddr("glTexSubImage3D");
    if( glTexSubImage3D_hook )
        glTexSubImage3D_hook( target_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, type_, pixels_ );
    F(target_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, type_, pixels_);
}
static glTextureBarrier_hook_t glTextureBarrier_hook = 0;
glTextureBarrier_hook_t getHook_glTextureBarrier (){
    return glTextureBarrier_hook ;
}
void setHook_glTextureBarrier ( glTextureBarrier_hook_t hook ){
    glTextureBarrier_hook = hook;
}
void glTextureBarrier (  ){
    static PFNGLTEXTUREBARRIERPROC F;
    if(!F)
        F = ( PFNGLTEXTUREBARRIERPROC ) mygetprocaddr("glTextureBarrier");
    if( glTextureBarrier_hook )
        glTextureBarrier_hook(  );
    F();
}
static glTextureBuffer_hook_t glTextureBuffer_hook = 0;
glTextureBuffer_hook_t getHook_glTextureBuffer (){
    return glTextureBuffer_hook ;
}
void setHook_glTextureBuffer ( glTextureBuffer_hook_t hook ){
    glTextureBuffer_hook = hook;
}
void glTextureBuffer ( GLuint texture_, GLenum internalformat_, GLuint buffer_ ){
    static PFNGLTEXTUREBUFFERPROC F;
    if(!F)
        F = ( PFNGLTEXTUREBUFFERPROC ) mygetprocaddr("glTextureBuffer");
    if( glTextureBuffer_hook )
        glTextureBuffer_hook( texture_, internalformat_, buffer_ );
    F(texture_, internalformat_, buffer_);
}
static glTextureBufferRange_hook_t glTextureBufferRange_hook = 0;
glTextureBufferRange_hook_t getHook_glTextureBufferRange (){
    return glTextureBufferRange_hook ;
}
void setHook_glTextureBufferRange ( glTextureBufferRange_hook_t hook ){
    glTextureBufferRange_hook = hook;
}
void glTextureBufferRange ( GLuint texture_, GLenum internalformat_, GLuint buffer_, GLintptr offset_, GLsizeiptr size_ ){
    static PFNGLTEXTUREBUFFERRANGEPROC F;
    if(!F)
        F = ( PFNGLTEXTUREBUFFERRANGEPROC ) mygetprocaddr("glTextureBufferRange");
    if( glTextureBufferRange_hook )
        glTextureBufferRange_hook( texture_, internalformat_, buffer_, offset_, size_ );
    F(texture_, internalformat_, buffer_, offset_, size_);
}
static glTextureParameterIiv_hook_t glTextureParameterIiv_hook = 0;
glTextureParameterIiv_hook_t getHook_glTextureParameterIiv (){
    return glTextureParameterIiv_hook ;
}
void setHook_glTextureParameterIiv ( glTextureParameterIiv_hook_t hook ){
    glTextureParameterIiv_hook = hook;
}
void glTextureParameterIiv ( GLuint texture_, GLenum pname_, const GLint * params_ ){
    static PFNGLTEXTUREPARAMETERIIVPROC F;
    if(!F)
        F = ( PFNGLTEXTUREPARAMETERIIVPROC ) mygetprocaddr("glTextureParameterIiv");
    if( glTextureParameterIiv_hook )
        glTextureParameterIiv_hook( texture_, pname_, params_ );
    F(texture_, pname_, params_);
}
static glTextureParameterIuiv_hook_t glTextureParameterIuiv_hook = 0;
glTextureParameterIuiv_hook_t getHook_glTextureParameterIuiv (){
    return glTextureParameterIuiv_hook ;
}
void setHook_glTextureParameterIuiv ( glTextureParameterIuiv_hook_t hook ){
    glTextureParameterIuiv_hook = hook;
}
void glTextureParameterIuiv ( GLuint texture_, GLenum pname_, const GLuint * params_ ){
    static PFNGLTEXTUREPARAMETERIUIVPROC F;
    if(!F)
        F = ( PFNGLTEXTUREPARAMETERIUIVPROC ) mygetprocaddr("glTextureParameterIuiv");
    if( glTextureParameterIuiv_hook )
        glTextureParameterIuiv_hook( texture_, pname_, params_ );
    F(texture_, pname_, params_);
}
static glTextureParameterf_hook_t glTextureParameterf_hook = 0;
glTextureParameterf_hook_t getHook_glTextureParameterf (){
    return glTextureParameterf_hook ;
}
void setHook_glTextureParameterf ( glTextureParameterf_hook_t hook ){
    glTextureParameterf_hook = hook;
}
void glTextureParameterf ( GLuint texture_, GLenum pname_, GLfloat param_ ){
    static PFNGLTEXTUREPARAMETERFPROC F;
    if(!F)
        F = ( PFNGLTEXTUREPARAMETERFPROC ) mygetprocaddr("glTextureParameterf");
    if( glTextureParameterf_hook )
        glTextureParameterf_hook( texture_, pname_, param_ );
    F(texture_, pname_, param_);
}
static glTextureParameterfv_hook_t glTextureParameterfv_hook = 0;
glTextureParameterfv_hook_t getHook_glTextureParameterfv (){
    return glTextureParameterfv_hook ;
}
void setHook_glTextureParameterfv ( glTextureParameterfv_hook_t hook ){
    glTextureParameterfv_hook = hook;
}
void glTextureParameterfv ( GLuint texture_, GLenum pname_, const GLfloat * param_ ){
    static PFNGLTEXTUREPARAMETERFVPROC F;
    if(!F)
        F = ( PFNGLTEXTUREPARAMETERFVPROC ) mygetprocaddr("glTextureParameterfv");
    if( glTextureParameterfv_hook )
        glTextureParameterfv_hook( texture_, pname_, param_ );
    F(texture_, pname_, param_);
}
static glTextureParameteri_hook_t glTextureParameteri_hook = 0;
glTextureParameteri_hook_t getHook_glTextureParameteri (){
    return glTextureParameteri_hook ;
}
void setHook_glTextureParameteri ( glTextureParameteri_hook_t hook ){
    glTextureParameteri_hook = hook;
}
void glTextureParameteri ( GLuint texture_, GLenum pname_, GLint param_ ){
    static PFNGLTEXTUREPARAMETERIPROC F;
    if(!F)
        F = ( PFNGLTEXTUREPARAMETERIPROC ) mygetprocaddr("glTextureParameteri");
    if( glTextureParameteri_hook )
        glTextureParameteri_hook( texture_, pname_, param_ );
    F(texture_, pname_, param_);
}
static glTextureParameteriv_hook_t glTextureParameteriv_hook = 0;
glTextureParameteriv_hook_t getHook_glTextureParameteriv (){
    return glTextureParameteriv_hook ;
}
void setHook_glTextureParameteriv ( glTextureParameteriv_hook_t hook ){
    glTextureParameteriv_hook = hook;
}
void glTextureParameteriv ( GLuint texture_, GLenum pname_, const GLint * param_ ){
    static PFNGLTEXTUREPARAMETERIVPROC F;
    if(!F)
        F = ( PFNGLTEXTUREPARAMETERIVPROC ) mygetprocaddr("glTextureParameteriv");
    if( glTextureParameteriv_hook )
        glTextureParameteriv_hook( texture_, pname_, param_ );
    F(texture_, pname_, param_);
}
static glTextureStorage1D_hook_t glTextureStorage1D_hook = 0;
glTextureStorage1D_hook_t getHook_glTextureStorage1D (){
    return glTextureStorage1D_hook ;
}
void setHook_glTextureStorage1D ( glTextureStorage1D_hook_t hook ){
    glTextureStorage1D_hook = hook;
}
void glTextureStorage1D ( GLuint texture_, GLsizei levels_, GLenum internalformat_, GLsizei width_ ){
    static PFNGLTEXTURESTORAGE1DPROC F;
    if(!F)
        F = ( PFNGLTEXTURESTORAGE1DPROC ) mygetprocaddr("glTextureStorage1D");
    if( glTextureStorage1D_hook )
        glTextureStorage1D_hook( texture_, levels_, internalformat_, width_ );
    F(texture_, levels_, internalformat_, width_);
}
static glTextureStorage2D_hook_t glTextureStorage2D_hook = 0;
glTextureStorage2D_hook_t getHook_glTextureStorage2D (){
    return glTextureStorage2D_hook ;
}
void setHook_glTextureStorage2D ( glTextureStorage2D_hook_t hook ){
    glTextureStorage2D_hook = hook;
}
void glTextureStorage2D ( GLuint texture_, GLsizei levels_, GLenum internalformat_, GLsizei width_, GLsizei height_ ){
    static PFNGLTEXTURESTORAGE2DPROC F;
    if(!F)
        F = ( PFNGLTEXTURESTORAGE2DPROC ) mygetprocaddr("glTextureStorage2D");
    if( glTextureStorage2D_hook )
        glTextureStorage2D_hook( texture_, levels_, internalformat_, width_, height_ );
    F(texture_, levels_, internalformat_, width_, height_);
}
static glTextureStorage3D_hook_t glTextureStorage3D_hook = 0;
glTextureStorage3D_hook_t getHook_glTextureStorage3D (){
    return glTextureStorage3D_hook ;
}
void setHook_glTextureStorage3D ( glTextureStorage3D_hook_t hook ){
    glTextureStorage3D_hook = hook;
}
void glTextureStorage3D ( GLuint texture_, GLsizei levels_, GLenum internalformat_, GLsizei width_, GLsizei height_, GLsizei depth_ ){
    static PFNGLTEXTURESTORAGE3DPROC F;
    if(!F)
        F = ( PFNGLTEXTURESTORAGE3DPROC ) mygetprocaddr("glTextureStorage3D");
    if( glTextureStorage3D_hook )
        glTextureStorage3D_hook( texture_, levels_, internalformat_, width_, height_, depth_ );
    F(texture_, levels_, internalformat_, width_, height_, depth_);
}
static glTextureSubImage1D_hook_t glTextureSubImage1D_hook = 0;
glTextureSubImage1D_hook_t getHook_glTextureSubImage1D (){
    return glTextureSubImage1D_hook ;
}
void setHook_glTextureSubImage1D ( glTextureSubImage1D_hook_t hook ){
    glTextureSubImage1D_hook = hook;
}
void glTextureSubImage1D ( GLuint texture_, GLint level_, GLint xoffset_, GLsizei width_, GLenum format_, GLenum type_, const void * pixels_ ){
    static PFNGLTEXTURESUBIMAGE1DPROC F;
    if(!F)
        F = ( PFNGLTEXTURESUBIMAGE1DPROC ) mygetprocaddr("glTextureSubImage1D");
    if( glTextureSubImage1D_hook )
        glTextureSubImage1D_hook( texture_, level_, xoffset_, width_, format_, type_, pixels_ );
    F(texture_, level_, xoffset_, width_, format_, type_, pixels_);
}
static glTextureSubImage2D_hook_t glTextureSubImage2D_hook = 0;
glTextureSubImage2D_hook_t getHook_glTextureSubImage2D (){
    return glTextureSubImage2D_hook ;
}
void setHook_glTextureSubImage2D ( glTextureSubImage2D_hook_t hook ){
    glTextureSubImage2D_hook = hook;
}
void glTextureSubImage2D ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLsizei width_, GLsizei height_, GLenum format_, GLenum type_, const void * pixels_ ){
    static PFNGLTEXTURESUBIMAGE2DPROC F;
    if(!F)
        F = ( PFNGLTEXTURESUBIMAGE2DPROC ) mygetprocaddr("glTextureSubImage2D");
    if( glTextureSubImage2D_hook )
        glTextureSubImage2D_hook( texture_, level_, xoffset_, yoffset_, width_, height_, format_, type_, pixels_ );
    F(texture_, level_, xoffset_, yoffset_, width_, height_, format_, type_, pixels_);
}
static glTextureSubImage3D_hook_t glTextureSubImage3D_hook = 0;
glTextureSubImage3D_hook_t getHook_glTextureSubImage3D (){
    return glTextureSubImage3D_hook ;
}
void setHook_glTextureSubImage3D ( glTextureSubImage3D_hook_t hook ){
    glTextureSubImage3D_hook = hook;
}
void glTextureSubImage3D ( GLuint texture_, GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, GLsizei width_, GLsizei height_, GLsizei depth_, GLenum format_, GLenum type_, const void * pixels_ ){
    static PFNGLTEXTURESUBIMAGE3DPROC F;
    if(!F)
        F = ( PFNGLTEXTURESUBIMAGE3DPROC ) mygetprocaddr("glTextureSubImage3D");
    if( glTextureSubImage3D_hook )
        glTextureSubImage3D_hook( texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, type_, pixels_ );
    F(texture_, level_, xoffset_, yoffset_, zoffset_, width_, height_, depth_, format_, type_, pixels_);
}
static glTextureView_hook_t glTextureView_hook = 0;
glTextureView_hook_t getHook_glTextureView (){
    return glTextureView_hook ;
}
void setHook_glTextureView ( glTextureView_hook_t hook ){
    glTextureView_hook = hook;
}
void glTextureView ( GLuint texture_, GLenum target_, GLuint origtexture_, GLenum internalformat_, GLuint minlevel_, GLuint numlevels_, GLuint minlayer_, GLuint numlayers_ ){
    static PFNGLTEXTUREVIEWPROC F;
    if(!F)
        F = ( PFNGLTEXTUREVIEWPROC ) mygetprocaddr("glTextureView");
    if( glTextureView_hook )
        glTextureView_hook( texture_, target_, origtexture_, internalformat_, minlevel_, numlevels_, minlayer_, numlayers_ );
    F(texture_, target_, origtexture_, internalformat_, minlevel_, numlevels_, minlayer_, numlayers_);
}
static glTransformFeedbackBufferBase_hook_t glTransformFeedbackBufferBase_hook = 0;
glTransformFeedbackBufferBase_hook_t getHook_glTransformFeedbackBufferBase (){
    return glTransformFeedbackBufferBase_hook ;
}
void setHook_glTransformFeedbackBufferBase ( glTransformFeedbackBufferBase_hook_t hook ){
    glTransformFeedbackBufferBase_hook = hook;
}
void glTransformFeedbackBufferBase ( GLuint xfb_, GLuint index_, GLuint buffer_ ){
    static PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC F;
    if(!F)
        F = ( PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC ) mygetprocaddr("glTransformFeedbackBufferBase");
    if( glTransformFeedbackBufferBase_hook )
        glTransformFeedbackBufferBase_hook( xfb_, index_, buffer_ );
    F(xfb_, index_, buffer_);
}
static glTransformFeedbackBufferRange_hook_t glTransformFeedbackBufferRange_hook = 0;
glTransformFeedbackBufferRange_hook_t getHook_glTransformFeedbackBufferRange (){
    return glTransformFeedbackBufferRange_hook ;
}
void setHook_glTransformFeedbackBufferRange ( glTransformFeedbackBufferRange_hook_t hook ){
    glTransformFeedbackBufferRange_hook = hook;
}
void glTransformFeedbackBufferRange ( GLuint xfb_, GLuint index_, GLuint buffer_, GLintptr offset_, GLsizeiptr size_ ){
    static PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC F;
    if(!F)
        F = ( PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC ) mygetprocaddr("glTransformFeedbackBufferRange");
    if( glTransformFeedbackBufferRange_hook )
        glTransformFeedbackBufferRange_hook( xfb_, index_, buffer_, offset_, size_ );
    F(xfb_, index_, buffer_, offset_, size_);
}
static glTransformFeedbackVaryings_hook_t glTransformFeedbackVaryings_hook = 0;
glTransformFeedbackVaryings_hook_t getHook_glTransformFeedbackVaryings (){
    return glTransformFeedbackVaryings_hook ;
}
void setHook_glTransformFeedbackVaryings ( glTransformFeedbackVaryings_hook_t hook ){
    glTransformFeedbackVaryings_hook = hook;
}
void glTransformFeedbackVaryings ( GLuint program_, GLsizei count_, const GLchar ** varyings_, GLenum bufferMode_ ){
    static PFNGLTRANSFORMFEEDBACKVARYINGSPROC F;
    if(!F)
        F = ( PFNGLTRANSFORMFEEDBACKVARYINGSPROC ) mygetprocaddr("glTransformFeedbackVaryings");
    if( glTransformFeedbackVaryings_hook )
        glTransformFeedbackVaryings_hook( program_, count_, varyings_, bufferMode_ );
    F(program_, count_, varyings_, bufferMode_);
}
static glUniform1d_hook_t glUniform1d_hook = 0;
glUniform1d_hook_t getHook_glUniform1d (){
    return glUniform1d_hook ;
}
void setHook_glUniform1d ( glUniform1d_hook_t hook ){
    glUniform1d_hook = hook;
}
void glUniform1d ( GLint location_, GLdouble x_ ){
    static PFNGLUNIFORM1DPROC F;
    if(!F)
        F = ( PFNGLUNIFORM1DPROC ) mygetprocaddr("glUniform1d");
    if( glUniform1d_hook )
        glUniform1d_hook( location_, x_ );
    F(location_, x_);
}
static glUniform1dv_hook_t glUniform1dv_hook = 0;
glUniform1dv_hook_t getHook_glUniform1dv (){
    return glUniform1dv_hook ;
}
void setHook_glUniform1dv ( glUniform1dv_hook_t hook ){
    glUniform1dv_hook = hook;
}
void glUniform1dv ( GLint location_, GLsizei count_, const GLdouble * value_ ){
    static PFNGLUNIFORM1DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM1DVPROC ) mygetprocaddr("glUniform1dv");
    if( glUniform1dv_hook )
        glUniform1dv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform1f_hook_t glUniform1f_hook = 0;
glUniform1f_hook_t getHook_glUniform1f (){
    return glUniform1f_hook ;
}
void setHook_glUniform1f ( glUniform1f_hook_t hook ){
    glUniform1f_hook = hook;
}
void glUniform1f ( GLint location_, GLfloat v0_ ){
    static PFNGLUNIFORM1FPROC F;
    if(!F)
        F = ( PFNGLUNIFORM1FPROC ) mygetprocaddr("glUniform1f");
    if( glUniform1f_hook )
        glUniform1f_hook( location_, v0_ );
    F(location_, v0_);
}
static glUniform1fv_hook_t glUniform1fv_hook = 0;
glUniform1fv_hook_t getHook_glUniform1fv (){
    return glUniform1fv_hook ;
}
void setHook_glUniform1fv ( glUniform1fv_hook_t hook ){
    glUniform1fv_hook = hook;
}
void glUniform1fv ( GLint location_, GLsizei count_, const GLfloat * value_ ){
    static PFNGLUNIFORM1FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM1FVPROC ) mygetprocaddr("glUniform1fv");
    if( glUniform1fv_hook )
        glUniform1fv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform1i_hook_t glUniform1i_hook = 0;
glUniform1i_hook_t getHook_glUniform1i (){
    return glUniform1i_hook ;
}
void setHook_glUniform1i ( glUniform1i_hook_t hook ){
    glUniform1i_hook = hook;
}
void glUniform1i ( GLint location_, GLint v0_ ){
    static PFNGLUNIFORM1IPROC F;
    if(!F)
        F = ( PFNGLUNIFORM1IPROC ) mygetprocaddr("glUniform1i");
    if( glUniform1i_hook )
        glUniform1i_hook( location_, v0_ );
    F(location_, v0_);
}
static glUniform1iv_hook_t glUniform1iv_hook = 0;
glUniform1iv_hook_t getHook_glUniform1iv (){
    return glUniform1iv_hook ;
}
void setHook_glUniform1iv ( glUniform1iv_hook_t hook ){
    glUniform1iv_hook = hook;
}
void glUniform1iv ( GLint location_, GLsizei count_, const GLint * value_ ){
    static PFNGLUNIFORM1IVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM1IVPROC ) mygetprocaddr("glUniform1iv");
    if( glUniform1iv_hook )
        glUniform1iv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform1ui_hook_t glUniform1ui_hook = 0;
glUniform1ui_hook_t getHook_glUniform1ui (){
    return glUniform1ui_hook ;
}
void setHook_glUniform1ui ( glUniform1ui_hook_t hook ){
    glUniform1ui_hook = hook;
}
void glUniform1ui ( GLint location_, GLuint v0_ ){
    static PFNGLUNIFORM1UIPROC F;
    if(!F)
        F = ( PFNGLUNIFORM1UIPROC ) mygetprocaddr("glUniform1ui");
    if( glUniform1ui_hook )
        glUniform1ui_hook( location_, v0_ );
    F(location_, v0_);
}
static glUniform1uiv_hook_t glUniform1uiv_hook = 0;
glUniform1uiv_hook_t getHook_glUniform1uiv (){
    return glUniform1uiv_hook ;
}
void setHook_glUniform1uiv ( glUniform1uiv_hook_t hook ){
    glUniform1uiv_hook = hook;
}
void glUniform1uiv ( GLint location_, GLsizei count_, const GLuint * value_ ){
    static PFNGLUNIFORM1UIVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM1UIVPROC ) mygetprocaddr("glUniform1uiv");
    if( glUniform1uiv_hook )
        glUniform1uiv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform2d_hook_t glUniform2d_hook = 0;
glUniform2d_hook_t getHook_glUniform2d (){
    return glUniform2d_hook ;
}
void setHook_glUniform2d ( glUniform2d_hook_t hook ){
    glUniform2d_hook = hook;
}
void glUniform2d ( GLint location_, GLdouble x_, GLdouble y_ ){
    static PFNGLUNIFORM2DPROC F;
    if(!F)
        F = ( PFNGLUNIFORM2DPROC ) mygetprocaddr("glUniform2d");
    if( glUniform2d_hook )
        glUniform2d_hook( location_, x_, y_ );
    F(location_, x_, y_);
}
static glUniform2dv_hook_t glUniform2dv_hook = 0;
glUniform2dv_hook_t getHook_glUniform2dv (){
    return glUniform2dv_hook ;
}
void setHook_glUniform2dv ( glUniform2dv_hook_t hook ){
    glUniform2dv_hook = hook;
}
void glUniform2dv ( GLint location_, GLsizei count_, const GLdouble * value_ ){
    static PFNGLUNIFORM2DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM2DVPROC ) mygetprocaddr("glUniform2dv");
    if( glUniform2dv_hook )
        glUniform2dv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform2f_hook_t glUniform2f_hook = 0;
glUniform2f_hook_t getHook_glUniform2f (){
    return glUniform2f_hook ;
}
void setHook_glUniform2f ( glUniform2f_hook_t hook ){
    glUniform2f_hook = hook;
}
void glUniform2f ( GLint location_, GLfloat v0_, GLfloat v1_ ){
    static PFNGLUNIFORM2FPROC F;
    if(!F)
        F = ( PFNGLUNIFORM2FPROC ) mygetprocaddr("glUniform2f");
    if( glUniform2f_hook )
        glUniform2f_hook( location_, v0_, v1_ );
    F(location_, v0_, v1_);
}
static glUniform2fv_hook_t glUniform2fv_hook = 0;
glUniform2fv_hook_t getHook_glUniform2fv (){
    return glUniform2fv_hook ;
}
void setHook_glUniform2fv ( glUniform2fv_hook_t hook ){
    glUniform2fv_hook = hook;
}
void glUniform2fv ( GLint location_, GLsizei count_, const GLfloat * value_ ){
    static PFNGLUNIFORM2FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM2FVPROC ) mygetprocaddr("glUniform2fv");
    if( glUniform2fv_hook )
        glUniform2fv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform2i_hook_t glUniform2i_hook = 0;
glUniform2i_hook_t getHook_glUniform2i (){
    return glUniform2i_hook ;
}
void setHook_glUniform2i ( glUniform2i_hook_t hook ){
    glUniform2i_hook = hook;
}
void glUniform2i ( GLint location_, GLint v0_, GLint v1_ ){
    static PFNGLUNIFORM2IPROC F;
    if(!F)
        F = ( PFNGLUNIFORM2IPROC ) mygetprocaddr("glUniform2i");
    if( glUniform2i_hook )
        glUniform2i_hook( location_, v0_, v1_ );
    F(location_, v0_, v1_);
}
static glUniform2iv_hook_t glUniform2iv_hook = 0;
glUniform2iv_hook_t getHook_glUniform2iv (){
    return glUniform2iv_hook ;
}
void setHook_glUniform2iv ( glUniform2iv_hook_t hook ){
    glUniform2iv_hook = hook;
}
void glUniform2iv ( GLint location_, GLsizei count_, const GLint * value_ ){
    static PFNGLUNIFORM2IVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM2IVPROC ) mygetprocaddr("glUniform2iv");
    if( glUniform2iv_hook )
        glUniform2iv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform2ui_hook_t glUniform2ui_hook = 0;
glUniform2ui_hook_t getHook_glUniform2ui (){
    return glUniform2ui_hook ;
}
void setHook_glUniform2ui ( glUniform2ui_hook_t hook ){
    glUniform2ui_hook = hook;
}
void glUniform2ui ( GLint location_, GLuint v0_, GLuint v1_ ){
    static PFNGLUNIFORM2UIPROC F;
    if(!F)
        F = ( PFNGLUNIFORM2UIPROC ) mygetprocaddr("glUniform2ui");
    if( glUniform2ui_hook )
        glUniform2ui_hook( location_, v0_, v1_ );
    F(location_, v0_, v1_);
}
static glUniform2uiv_hook_t glUniform2uiv_hook = 0;
glUniform2uiv_hook_t getHook_glUniform2uiv (){
    return glUniform2uiv_hook ;
}
void setHook_glUniform2uiv ( glUniform2uiv_hook_t hook ){
    glUniform2uiv_hook = hook;
}
void glUniform2uiv ( GLint location_, GLsizei count_, const GLuint * value_ ){
    static PFNGLUNIFORM2UIVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM2UIVPROC ) mygetprocaddr("glUniform2uiv");
    if( glUniform2uiv_hook )
        glUniform2uiv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform3d_hook_t glUniform3d_hook = 0;
glUniform3d_hook_t getHook_glUniform3d (){
    return glUniform3d_hook ;
}
void setHook_glUniform3d ( glUniform3d_hook_t hook ){
    glUniform3d_hook = hook;
}
void glUniform3d ( GLint location_, GLdouble x_, GLdouble y_, GLdouble z_ ){
    static PFNGLUNIFORM3DPROC F;
    if(!F)
        F = ( PFNGLUNIFORM3DPROC ) mygetprocaddr("glUniform3d");
    if( glUniform3d_hook )
        glUniform3d_hook( location_, x_, y_, z_ );
    F(location_, x_, y_, z_);
}
static glUniform3dv_hook_t glUniform3dv_hook = 0;
glUniform3dv_hook_t getHook_glUniform3dv (){
    return glUniform3dv_hook ;
}
void setHook_glUniform3dv ( glUniform3dv_hook_t hook ){
    glUniform3dv_hook = hook;
}
void glUniform3dv ( GLint location_, GLsizei count_, const GLdouble * value_ ){
    static PFNGLUNIFORM3DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM3DVPROC ) mygetprocaddr("glUniform3dv");
    if( glUniform3dv_hook )
        glUniform3dv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform3f_hook_t glUniform3f_hook = 0;
glUniform3f_hook_t getHook_glUniform3f (){
    return glUniform3f_hook ;
}
void setHook_glUniform3f ( glUniform3f_hook_t hook ){
    glUniform3f_hook = hook;
}
void glUniform3f ( GLint location_, GLfloat v0_, GLfloat v1_, GLfloat v2_ ){
    static PFNGLUNIFORM3FPROC F;
    if(!F)
        F = ( PFNGLUNIFORM3FPROC ) mygetprocaddr("glUniform3f");
    if( glUniform3f_hook )
        glUniform3f_hook( location_, v0_, v1_, v2_ );
    F(location_, v0_, v1_, v2_);
}
static glUniform3fv_hook_t glUniform3fv_hook = 0;
glUniform3fv_hook_t getHook_glUniform3fv (){
    return glUniform3fv_hook ;
}
void setHook_glUniform3fv ( glUniform3fv_hook_t hook ){
    glUniform3fv_hook = hook;
}
void glUniform3fv ( GLint location_, GLsizei count_, const GLfloat * value_ ){
    static PFNGLUNIFORM3FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM3FVPROC ) mygetprocaddr("glUniform3fv");
    if( glUniform3fv_hook )
        glUniform3fv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform3i_hook_t glUniform3i_hook = 0;
glUniform3i_hook_t getHook_glUniform3i (){
    return glUniform3i_hook ;
}
void setHook_glUniform3i ( glUniform3i_hook_t hook ){
    glUniform3i_hook = hook;
}
void glUniform3i ( GLint location_, GLint v0_, GLint v1_, GLint v2_ ){
    static PFNGLUNIFORM3IPROC F;
    if(!F)
        F = ( PFNGLUNIFORM3IPROC ) mygetprocaddr("glUniform3i");
    if( glUniform3i_hook )
        glUniform3i_hook( location_, v0_, v1_, v2_ );
    F(location_, v0_, v1_, v2_);
}
static glUniform3iv_hook_t glUniform3iv_hook = 0;
glUniform3iv_hook_t getHook_glUniform3iv (){
    return glUniform3iv_hook ;
}
void setHook_glUniform3iv ( glUniform3iv_hook_t hook ){
    glUniform3iv_hook = hook;
}
void glUniform3iv ( GLint location_, GLsizei count_, const GLint * value_ ){
    static PFNGLUNIFORM3IVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM3IVPROC ) mygetprocaddr("glUniform3iv");
    if( glUniform3iv_hook )
        glUniform3iv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform3ui_hook_t glUniform3ui_hook = 0;
glUniform3ui_hook_t getHook_glUniform3ui (){
    return glUniform3ui_hook ;
}
void setHook_glUniform3ui ( glUniform3ui_hook_t hook ){
    glUniform3ui_hook = hook;
}
void glUniform3ui ( GLint location_, GLuint v0_, GLuint v1_, GLuint v2_ ){
    static PFNGLUNIFORM3UIPROC F;
    if(!F)
        F = ( PFNGLUNIFORM3UIPROC ) mygetprocaddr("glUniform3ui");
    if( glUniform3ui_hook )
        glUniform3ui_hook( location_, v0_, v1_, v2_ );
    F(location_, v0_, v1_, v2_);
}
static glUniform3uiv_hook_t glUniform3uiv_hook = 0;
glUniform3uiv_hook_t getHook_glUniform3uiv (){
    return glUniform3uiv_hook ;
}
void setHook_glUniform3uiv ( glUniform3uiv_hook_t hook ){
    glUniform3uiv_hook = hook;
}
void glUniform3uiv ( GLint location_, GLsizei count_, const GLuint * value_ ){
    static PFNGLUNIFORM3UIVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM3UIVPROC ) mygetprocaddr("glUniform3uiv");
    if( glUniform3uiv_hook )
        glUniform3uiv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform4d_hook_t glUniform4d_hook = 0;
glUniform4d_hook_t getHook_glUniform4d (){
    return glUniform4d_hook ;
}
void setHook_glUniform4d ( glUniform4d_hook_t hook ){
    glUniform4d_hook = hook;
}
void glUniform4d ( GLint location_, GLdouble x_, GLdouble y_, GLdouble z_, GLdouble w_ ){
    static PFNGLUNIFORM4DPROC F;
    if(!F)
        F = ( PFNGLUNIFORM4DPROC ) mygetprocaddr("glUniform4d");
    if( glUniform4d_hook )
        glUniform4d_hook( location_, x_, y_, z_, w_ );
    F(location_, x_, y_, z_, w_);
}
static glUniform4dv_hook_t glUniform4dv_hook = 0;
glUniform4dv_hook_t getHook_glUniform4dv (){
    return glUniform4dv_hook ;
}
void setHook_glUniform4dv ( glUniform4dv_hook_t hook ){
    glUniform4dv_hook = hook;
}
void glUniform4dv ( GLint location_, GLsizei count_, const GLdouble * value_ ){
    static PFNGLUNIFORM4DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM4DVPROC ) mygetprocaddr("glUniform4dv");
    if( glUniform4dv_hook )
        glUniform4dv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform4f_hook_t glUniform4f_hook = 0;
glUniform4f_hook_t getHook_glUniform4f (){
    return glUniform4f_hook ;
}
void setHook_glUniform4f ( glUniform4f_hook_t hook ){
    glUniform4f_hook = hook;
}
void glUniform4f ( GLint location_, GLfloat v0_, GLfloat v1_, GLfloat v2_, GLfloat v3_ ){
    static PFNGLUNIFORM4FPROC F;
    if(!F)
        F = ( PFNGLUNIFORM4FPROC ) mygetprocaddr("glUniform4f");
    if( glUniform4f_hook )
        glUniform4f_hook( location_, v0_, v1_, v2_, v3_ );
    F(location_, v0_, v1_, v2_, v3_);
}
static glUniform4fv_hook_t glUniform4fv_hook = 0;
glUniform4fv_hook_t getHook_glUniform4fv (){
    return glUniform4fv_hook ;
}
void setHook_glUniform4fv ( glUniform4fv_hook_t hook ){
    glUniform4fv_hook = hook;
}
void glUniform4fv ( GLint location_, GLsizei count_, const GLfloat * value_ ){
    static PFNGLUNIFORM4FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM4FVPROC ) mygetprocaddr("glUniform4fv");
    if( glUniform4fv_hook )
        glUniform4fv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform4i_hook_t glUniform4i_hook = 0;
glUniform4i_hook_t getHook_glUniform4i (){
    return glUniform4i_hook ;
}
void setHook_glUniform4i ( glUniform4i_hook_t hook ){
    glUniform4i_hook = hook;
}
void glUniform4i ( GLint location_, GLint v0_, GLint v1_, GLint v2_, GLint v3_ ){
    static PFNGLUNIFORM4IPROC F;
    if(!F)
        F = ( PFNGLUNIFORM4IPROC ) mygetprocaddr("glUniform4i");
    if( glUniform4i_hook )
        glUniform4i_hook( location_, v0_, v1_, v2_, v3_ );
    F(location_, v0_, v1_, v2_, v3_);
}
static glUniform4iv_hook_t glUniform4iv_hook = 0;
glUniform4iv_hook_t getHook_glUniform4iv (){
    return glUniform4iv_hook ;
}
void setHook_glUniform4iv ( glUniform4iv_hook_t hook ){
    glUniform4iv_hook = hook;
}
void glUniform4iv ( GLint location_, GLsizei count_, const GLint * value_ ){
    static PFNGLUNIFORM4IVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM4IVPROC ) mygetprocaddr("glUniform4iv");
    if( glUniform4iv_hook )
        glUniform4iv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniform4ui_hook_t glUniform4ui_hook = 0;
glUniform4ui_hook_t getHook_glUniform4ui (){
    return glUniform4ui_hook ;
}
void setHook_glUniform4ui ( glUniform4ui_hook_t hook ){
    glUniform4ui_hook = hook;
}
void glUniform4ui ( GLint location_, GLuint v0_, GLuint v1_, GLuint v2_, GLuint v3_ ){
    static PFNGLUNIFORM4UIPROC F;
    if(!F)
        F = ( PFNGLUNIFORM4UIPROC ) mygetprocaddr("glUniform4ui");
    if( glUniform4ui_hook )
        glUniform4ui_hook( location_, v0_, v1_, v2_, v3_ );
    F(location_, v0_, v1_, v2_, v3_);
}
static glUniform4uiv_hook_t glUniform4uiv_hook = 0;
glUniform4uiv_hook_t getHook_glUniform4uiv (){
    return glUniform4uiv_hook ;
}
void setHook_glUniform4uiv ( glUniform4uiv_hook_t hook ){
    glUniform4uiv_hook = hook;
}
void glUniform4uiv ( GLint location_, GLsizei count_, const GLuint * value_ ){
    static PFNGLUNIFORM4UIVPROC F;
    if(!F)
        F = ( PFNGLUNIFORM4UIVPROC ) mygetprocaddr("glUniform4uiv");
    if( glUniform4uiv_hook )
        glUniform4uiv_hook( location_, count_, value_ );
    F(location_, count_, value_);
}
static glUniformBlockBinding_hook_t glUniformBlockBinding_hook = 0;
glUniformBlockBinding_hook_t getHook_glUniformBlockBinding (){
    return glUniformBlockBinding_hook ;
}
void setHook_glUniformBlockBinding ( glUniformBlockBinding_hook_t hook ){
    glUniformBlockBinding_hook = hook;
}
void glUniformBlockBinding ( GLuint program_, GLuint uniformBlockIndex_, GLuint uniformBlockBinding_ ){
    static PFNGLUNIFORMBLOCKBINDINGPROC F;
    if(!F)
        F = ( PFNGLUNIFORMBLOCKBINDINGPROC ) mygetprocaddr("glUniformBlockBinding");
    if( glUniformBlockBinding_hook )
        glUniformBlockBinding_hook( program_, uniformBlockIndex_, uniformBlockBinding_ );
    F(program_, uniformBlockIndex_, uniformBlockBinding_);
}
static glUniformMatrix2dv_hook_t glUniformMatrix2dv_hook = 0;
glUniformMatrix2dv_hook_t getHook_glUniformMatrix2dv (){
    return glUniformMatrix2dv_hook ;
}
void setHook_glUniformMatrix2dv ( glUniformMatrix2dv_hook_t hook ){
    glUniformMatrix2dv_hook = hook;
}
void glUniformMatrix2dv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLUNIFORMMATRIX2DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX2DVPROC ) mygetprocaddr("glUniformMatrix2dv");
    if( glUniformMatrix2dv_hook )
        glUniformMatrix2dv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix2fv_hook_t glUniformMatrix2fv_hook = 0;
glUniformMatrix2fv_hook_t getHook_glUniformMatrix2fv (){
    return glUniformMatrix2fv_hook ;
}
void setHook_glUniformMatrix2fv ( glUniformMatrix2fv_hook_t hook ){
    glUniformMatrix2fv_hook = hook;
}
void glUniformMatrix2fv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLUNIFORMMATRIX2FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX2FVPROC ) mygetprocaddr("glUniformMatrix2fv");
    if( glUniformMatrix2fv_hook )
        glUniformMatrix2fv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix2x3dv_hook_t glUniformMatrix2x3dv_hook = 0;
glUniformMatrix2x3dv_hook_t getHook_glUniformMatrix2x3dv (){
    return glUniformMatrix2x3dv_hook ;
}
void setHook_glUniformMatrix2x3dv ( glUniformMatrix2x3dv_hook_t hook ){
    glUniformMatrix2x3dv_hook = hook;
}
void glUniformMatrix2x3dv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLUNIFORMMATRIX2X3DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX2X3DVPROC ) mygetprocaddr("glUniformMatrix2x3dv");
    if( glUniformMatrix2x3dv_hook )
        glUniformMatrix2x3dv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix2x3fv_hook_t glUniformMatrix2x3fv_hook = 0;
glUniformMatrix2x3fv_hook_t getHook_glUniformMatrix2x3fv (){
    return glUniformMatrix2x3fv_hook ;
}
void setHook_glUniformMatrix2x3fv ( glUniformMatrix2x3fv_hook_t hook ){
    glUniformMatrix2x3fv_hook = hook;
}
void glUniformMatrix2x3fv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLUNIFORMMATRIX2X3FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX2X3FVPROC ) mygetprocaddr("glUniformMatrix2x3fv");
    if( glUniformMatrix2x3fv_hook )
        glUniformMatrix2x3fv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix2x4dv_hook_t glUniformMatrix2x4dv_hook = 0;
glUniformMatrix2x4dv_hook_t getHook_glUniformMatrix2x4dv (){
    return glUniformMatrix2x4dv_hook ;
}
void setHook_glUniformMatrix2x4dv ( glUniformMatrix2x4dv_hook_t hook ){
    glUniformMatrix2x4dv_hook = hook;
}
void glUniformMatrix2x4dv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLUNIFORMMATRIX2X4DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX2X4DVPROC ) mygetprocaddr("glUniformMatrix2x4dv");
    if( glUniformMatrix2x4dv_hook )
        glUniformMatrix2x4dv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix2x4fv_hook_t glUniformMatrix2x4fv_hook = 0;
glUniformMatrix2x4fv_hook_t getHook_glUniformMatrix2x4fv (){
    return glUniformMatrix2x4fv_hook ;
}
void setHook_glUniformMatrix2x4fv ( glUniformMatrix2x4fv_hook_t hook ){
    glUniformMatrix2x4fv_hook = hook;
}
void glUniformMatrix2x4fv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLUNIFORMMATRIX2X4FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX2X4FVPROC ) mygetprocaddr("glUniformMatrix2x4fv");
    if( glUniformMatrix2x4fv_hook )
        glUniformMatrix2x4fv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix3dv_hook_t glUniformMatrix3dv_hook = 0;
glUniformMatrix3dv_hook_t getHook_glUniformMatrix3dv (){
    return glUniformMatrix3dv_hook ;
}
void setHook_glUniformMatrix3dv ( glUniformMatrix3dv_hook_t hook ){
    glUniformMatrix3dv_hook = hook;
}
void glUniformMatrix3dv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLUNIFORMMATRIX3DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX3DVPROC ) mygetprocaddr("glUniformMatrix3dv");
    if( glUniformMatrix3dv_hook )
        glUniformMatrix3dv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix3fv_hook_t glUniformMatrix3fv_hook = 0;
glUniformMatrix3fv_hook_t getHook_glUniformMatrix3fv (){
    return glUniformMatrix3fv_hook ;
}
void setHook_glUniformMatrix3fv ( glUniformMatrix3fv_hook_t hook ){
    glUniformMatrix3fv_hook = hook;
}
void glUniformMatrix3fv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLUNIFORMMATRIX3FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX3FVPROC ) mygetprocaddr("glUniformMatrix3fv");
    if( glUniformMatrix3fv_hook )
        glUniformMatrix3fv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix3x2dv_hook_t glUniformMatrix3x2dv_hook = 0;
glUniformMatrix3x2dv_hook_t getHook_glUniformMatrix3x2dv (){
    return glUniformMatrix3x2dv_hook ;
}
void setHook_glUniformMatrix3x2dv ( glUniformMatrix3x2dv_hook_t hook ){
    glUniformMatrix3x2dv_hook = hook;
}
void glUniformMatrix3x2dv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLUNIFORMMATRIX3X2DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX3X2DVPROC ) mygetprocaddr("glUniformMatrix3x2dv");
    if( glUniformMatrix3x2dv_hook )
        glUniformMatrix3x2dv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix3x2fv_hook_t glUniformMatrix3x2fv_hook = 0;
glUniformMatrix3x2fv_hook_t getHook_glUniformMatrix3x2fv (){
    return glUniformMatrix3x2fv_hook ;
}
void setHook_glUniformMatrix3x2fv ( glUniformMatrix3x2fv_hook_t hook ){
    glUniformMatrix3x2fv_hook = hook;
}
void glUniformMatrix3x2fv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLUNIFORMMATRIX3X2FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX3X2FVPROC ) mygetprocaddr("glUniformMatrix3x2fv");
    if( glUniformMatrix3x2fv_hook )
        glUniformMatrix3x2fv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix3x4dv_hook_t glUniformMatrix3x4dv_hook = 0;
glUniformMatrix3x4dv_hook_t getHook_glUniformMatrix3x4dv (){
    return glUniformMatrix3x4dv_hook ;
}
void setHook_glUniformMatrix3x4dv ( glUniformMatrix3x4dv_hook_t hook ){
    glUniformMatrix3x4dv_hook = hook;
}
void glUniformMatrix3x4dv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLUNIFORMMATRIX3X4DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX3X4DVPROC ) mygetprocaddr("glUniformMatrix3x4dv");
    if( glUniformMatrix3x4dv_hook )
        glUniformMatrix3x4dv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix3x4fv_hook_t glUniformMatrix3x4fv_hook = 0;
glUniformMatrix3x4fv_hook_t getHook_glUniformMatrix3x4fv (){
    return glUniformMatrix3x4fv_hook ;
}
void setHook_glUniformMatrix3x4fv ( glUniformMatrix3x4fv_hook_t hook ){
    glUniformMatrix3x4fv_hook = hook;
}
void glUniformMatrix3x4fv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLUNIFORMMATRIX3X4FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX3X4FVPROC ) mygetprocaddr("glUniformMatrix3x4fv");
    if( glUniformMatrix3x4fv_hook )
        glUniformMatrix3x4fv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix4dv_hook_t glUniformMatrix4dv_hook = 0;
glUniformMatrix4dv_hook_t getHook_glUniformMatrix4dv (){
    return glUniformMatrix4dv_hook ;
}
void setHook_glUniformMatrix4dv ( glUniformMatrix4dv_hook_t hook ){
    glUniformMatrix4dv_hook = hook;
}
void glUniformMatrix4dv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLUNIFORMMATRIX4DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX4DVPROC ) mygetprocaddr("glUniformMatrix4dv");
    if( glUniformMatrix4dv_hook )
        glUniformMatrix4dv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix4fv_hook_t glUniformMatrix4fv_hook = 0;
glUniformMatrix4fv_hook_t getHook_glUniformMatrix4fv (){
    return glUniformMatrix4fv_hook ;
}
void setHook_glUniformMatrix4fv ( glUniformMatrix4fv_hook_t hook ){
    glUniformMatrix4fv_hook = hook;
}
void glUniformMatrix4fv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLUNIFORMMATRIX4FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX4FVPROC ) mygetprocaddr("glUniformMatrix4fv");
    if( glUniformMatrix4fv_hook )
        glUniformMatrix4fv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix4x2dv_hook_t glUniformMatrix4x2dv_hook = 0;
glUniformMatrix4x2dv_hook_t getHook_glUniformMatrix4x2dv (){
    return glUniformMatrix4x2dv_hook ;
}
void setHook_glUniformMatrix4x2dv ( glUniformMatrix4x2dv_hook_t hook ){
    glUniformMatrix4x2dv_hook = hook;
}
void glUniformMatrix4x2dv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLUNIFORMMATRIX4X2DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX4X2DVPROC ) mygetprocaddr("glUniformMatrix4x2dv");
    if( glUniformMatrix4x2dv_hook )
        glUniformMatrix4x2dv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix4x2fv_hook_t glUniformMatrix4x2fv_hook = 0;
glUniformMatrix4x2fv_hook_t getHook_glUniformMatrix4x2fv (){
    return glUniformMatrix4x2fv_hook ;
}
void setHook_glUniformMatrix4x2fv ( glUniformMatrix4x2fv_hook_t hook ){
    glUniformMatrix4x2fv_hook = hook;
}
void glUniformMatrix4x2fv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLUNIFORMMATRIX4X2FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX4X2FVPROC ) mygetprocaddr("glUniformMatrix4x2fv");
    if( glUniformMatrix4x2fv_hook )
        glUniformMatrix4x2fv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix4x3dv_hook_t glUniformMatrix4x3dv_hook = 0;
glUniformMatrix4x3dv_hook_t getHook_glUniformMatrix4x3dv (){
    return glUniformMatrix4x3dv_hook ;
}
void setHook_glUniformMatrix4x3dv ( glUniformMatrix4x3dv_hook_t hook ){
    glUniformMatrix4x3dv_hook = hook;
}
void glUniformMatrix4x3dv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLdouble * value_ ){
    static PFNGLUNIFORMMATRIX4X3DVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX4X3DVPROC ) mygetprocaddr("glUniformMatrix4x3dv");
    if( glUniformMatrix4x3dv_hook )
        glUniformMatrix4x3dv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformMatrix4x3fv_hook_t glUniformMatrix4x3fv_hook = 0;
glUniformMatrix4x3fv_hook_t getHook_glUniformMatrix4x3fv (){
    return glUniformMatrix4x3fv_hook ;
}
void setHook_glUniformMatrix4x3fv ( glUniformMatrix4x3fv_hook_t hook ){
    glUniformMatrix4x3fv_hook = hook;
}
void glUniformMatrix4x3fv ( GLint location_, GLsizei count_, GLboolean transpose_, const GLfloat * value_ ){
    static PFNGLUNIFORMMATRIX4X3FVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMMATRIX4X3FVPROC ) mygetprocaddr("glUniformMatrix4x3fv");
    if( glUniformMatrix4x3fv_hook )
        glUniformMatrix4x3fv_hook( location_, count_, transpose_, value_ );
    F(location_, count_, transpose_, value_);
}
static glUniformSubroutinesuiv_hook_t glUniformSubroutinesuiv_hook = 0;
glUniformSubroutinesuiv_hook_t getHook_glUniformSubroutinesuiv (){
    return glUniformSubroutinesuiv_hook ;
}
void setHook_glUniformSubroutinesuiv ( glUniformSubroutinesuiv_hook_t hook ){
    glUniformSubroutinesuiv_hook = hook;
}
void glUniformSubroutinesuiv ( GLenum shadertype_, GLsizei count_, const GLuint * indices_ ){
    static PFNGLUNIFORMSUBROUTINESUIVPROC F;
    if(!F)
        F = ( PFNGLUNIFORMSUBROUTINESUIVPROC ) mygetprocaddr("glUniformSubroutinesuiv");
    if( glUniformSubroutinesuiv_hook )
        glUniformSubroutinesuiv_hook( shadertype_, count_, indices_ );
    F(shadertype_, count_, indices_);
}
static glUnmapBuffer_hook_t glUnmapBuffer_hook = 0;
glUnmapBuffer_hook_t getHook_glUnmapBuffer (){
    return glUnmapBuffer_hook ;
}
void setHook_glUnmapBuffer ( glUnmapBuffer_hook_t hook ){
    glUnmapBuffer_hook = hook;
}
GLboolean glUnmapBuffer ( GLenum target_ ){
    static PFNGLUNMAPBUFFERPROC F;
    if(!F)
        F = ( PFNGLUNMAPBUFFERPROC ) mygetprocaddr("glUnmapBuffer");
    if( glUnmapBuffer_hook )
        glUnmapBuffer_hook( target_ );
    GLboolean retval = F(target_);
    return retval;
}
static glUnmapNamedBuffer_hook_t glUnmapNamedBuffer_hook = 0;
glUnmapNamedBuffer_hook_t getHook_glUnmapNamedBuffer (){
    return glUnmapNamedBuffer_hook ;
}
void setHook_glUnmapNamedBuffer ( glUnmapNamedBuffer_hook_t hook ){
    glUnmapNamedBuffer_hook = hook;
}
GLboolean glUnmapNamedBuffer ( GLuint buffer_ ){
    static PFNGLUNMAPNAMEDBUFFERPROC F;
    if(!F)
        F = ( PFNGLUNMAPNAMEDBUFFERPROC ) mygetprocaddr("glUnmapNamedBuffer");
    if( glUnmapNamedBuffer_hook )
        glUnmapNamedBuffer_hook( buffer_ );
    GLboolean retval = F(buffer_);
    return retval;
}
static glUseProgram_hook_t glUseProgram_hook = 0;
glUseProgram_hook_t getHook_glUseProgram (){
    return glUseProgram_hook ;
}
void setHook_glUseProgram ( glUseProgram_hook_t hook ){
    glUseProgram_hook = hook;
}
void glUseProgram ( GLuint program_ ){
    static PFNGLUSEPROGRAMPROC F;
    if(!F)
        F = ( PFNGLUSEPROGRAMPROC ) mygetprocaddr("glUseProgram");
    if( glUseProgram_hook )
        glUseProgram_hook( program_ );
    F(program_);
}
static glUseProgramStages_hook_t glUseProgramStages_hook = 0;
glUseProgramStages_hook_t getHook_glUseProgramStages (){
    return glUseProgramStages_hook ;
}
void setHook_glUseProgramStages ( glUseProgramStages_hook_t hook ){
    glUseProgramStages_hook = hook;
}
void glUseProgramStages ( GLuint pipeline_, GLbitfield stages_, GLuint program_ ){
    static PFNGLUSEPROGRAMSTAGESPROC F;
    if(!F)
        F = ( PFNGLUSEPROGRAMSTAGESPROC ) mygetprocaddr("glUseProgramStages");
    if( glUseProgramStages_hook )
        glUseProgramStages_hook( pipeline_, stages_, program_ );
    F(pipeline_, stages_, program_);
}
static glValidateProgram_hook_t glValidateProgram_hook = 0;
glValidateProgram_hook_t getHook_glValidateProgram (){
    return glValidateProgram_hook ;
}
void setHook_glValidateProgram ( glValidateProgram_hook_t hook ){
    glValidateProgram_hook = hook;
}
void glValidateProgram ( GLuint program_ ){
    static PFNGLVALIDATEPROGRAMPROC F;
    if(!F)
        F = ( PFNGLVALIDATEPROGRAMPROC ) mygetprocaddr("glValidateProgram");
    if( glValidateProgram_hook )
        glValidateProgram_hook( program_ );
    F(program_);
}
static glValidateProgramPipeline_hook_t glValidateProgramPipeline_hook = 0;
glValidateProgramPipeline_hook_t getHook_glValidateProgramPipeline (){
    return glValidateProgramPipeline_hook ;
}
void setHook_glValidateProgramPipeline ( glValidateProgramPipeline_hook_t hook ){
    glValidateProgramPipeline_hook = hook;
}
void glValidateProgramPipeline ( GLuint pipeline_ ){
    static PFNGLVALIDATEPROGRAMPIPELINEPROC F;
    if(!F)
        F = ( PFNGLVALIDATEPROGRAMPIPELINEPROC ) mygetprocaddr("glValidateProgramPipeline");
    if( glValidateProgramPipeline_hook )
        glValidateProgramPipeline_hook( pipeline_ );
    F(pipeline_);
}
static glVertexArrayAttribBinding_hook_t glVertexArrayAttribBinding_hook = 0;
glVertexArrayAttribBinding_hook_t getHook_glVertexArrayAttribBinding (){
    return glVertexArrayAttribBinding_hook ;
}
void setHook_glVertexArrayAttribBinding ( glVertexArrayAttribBinding_hook_t hook ){
    glVertexArrayAttribBinding_hook = hook;
}
void glVertexArrayAttribBinding ( GLuint vaobj_, GLuint attribindex_, GLuint bindingindex_ ){
    static PFNGLVERTEXARRAYATTRIBBINDINGPROC F;
    if(!F)
        F = ( PFNGLVERTEXARRAYATTRIBBINDINGPROC ) mygetprocaddr("glVertexArrayAttribBinding");
    if( glVertexArrayAttribBinding_hook )
        glVertexArrayAttribBinding_hook( vaobj_, attribindex_, bindingindex_ );
    F(vaobj_, attribindex_, bindingindex_);
}
static glVertexArrayAttribFormat_hook_t glVertexArrayAttribFormat_hook = 0;
glVertexArrayAttribFormat_hook_t getHook_glVertexArrayAttribFormat (){
    return glVertexArrayAttribFormat_hook ;
}
void setHook_glVertexArrayAttribFormat ( glVertexArrayAttribFormat_hook_t hook ){
    glVertexArrayAttribFormat_hook = hook;
}
void glVertexArrayAttribFormat ( GLuint vaobj_, GLuint attribindex_, GLint size_, GLenum type_, GLboolean normalized_, GLuint relativeoffset_ ){
    static PFNGLVERTEXARRAYATTRIBFORMATPROC F;
    if(!F)
        F = ( PFNGLVERTEXARRAYATTRIBFORMATPROC ) mygetprocaddr("glVertexArrayAttribFormat");
    if( glVertexArrayAttribFormat_hook )
        glVertexArrayAttribFormat_hook( vaobj_, attribindex_, size_, type_, normalized_, relativeoffset_ );
    F(vaobj_, attribindex_, size_, type_, normalized_, relativeoffset_);
}
static glVertexArrayBindingDivisor_hook_t glVertexArrayBindingDivisor_hook = 0;
glVertexArrayBindingDivisor_hook_t getHook_glVertexArrayBindingDivisor (){
    return glVertexArrayBindingDivisor_hook ;
}
void setHook_glVertexArrayBindingDivisor ( glVertexArrayBindingDivisor_hook_t hook ){
    glVertexArrayBindingDivisor_hook = hook;
}
void glVertexArrayBindingDivisor ( GLuint vaobj_, GLuint bindingindex_, GLuint divisor_ ){
    static PFNGLVERTEXARRAYBINDINGDIVISORPROC F;
    if(!F)
        F = ( PFNGLVERTEXARRAYBINDINGDIVISORPROC ) mygetprocaddr("glVertexArrayBindingDivisor");
    if( glVertexArrayBindingDivisor_hook )
        glVertexArrayBindingDivisor_hook( vaobj_, bindingindex_, divisor_ );
    F(vaobj_, bindingindex_, divisor_);
}
static glVertexArrayElementBuffer_hook_t glVertexArrayElementBuffer_hook = 0;
glVertexArrayElementBuffer_hook_t getHook_glVertexArrayElementBuffer (){
    return glVertexArrayElementBuffer_hook ;
}
void setHook_glVertexArrayElementBuffer ( glVertexArrayElementBuffer_hook_t hook ){
    glVertexArrayElementBuffer_hook = hook;
}
void glVertexArrayElementBuffer ( GLuint vaobj_, GLuint buffer_ ){
    static PFNGLVERTEXARRAYELEMENTBUFFERPROC F;
    if(!F)
        F = ( PFNGLVERTEXARRAYELEMENTBUFFERPROC ) mygetprocaddr("glVertexArrayElementBuffer");
    if( glVertexArrayElementBuffer_hook )
        glVertexArrayElementBuffer_hook( vaobj_, buffer_ );
    F(vaobj_, buffer_);
}
static glVertexArrayVertexBuffer_hook_t glVertexArrayVertexBuffer_hook = 0;
glVertexArrayVertexBuffer_hook_t getHook_glVertexArrayVertexBuffer (){
    return glVertexArrayVertexBuffer_hook ;
}
void setHook_glVertexArrayVertexBuffer ( glVertexArrayVertexBuffer_hook_t hook ){
    glVertexArrayVertexBuffer_hook = hook;
}
void glVertexArrayVertexBuffer ( GLuint vaobj_, GLuint bindingindex_, GLuint buffer_, GLintptr offset_, GLsizei stride_ ){
    static PFNGLVERTEXARRAYVERTEXBUFFERPROC F;
    if(!F)
        F = ( PFNGLVERTEXARRAYVERTEXBUFFERPROC ) mygetprocaddr("glVertexArrayVertexBuffer");
    if( glVertexArrayVertexBuffer_hook )
        glVertexArrayVertexBuffer_hook( vaobj_, bindingindex_, buffer_, offset_, stride_ );
    F(vaobj_, bindingindex_, buffer_, offset_, stride_);
}
static glVertexArrayVertexBuffers_hook_t glVertexArrayVertexBuffers_hook = 0;
glVertexArrayVertexBuffers_hook_t getHook_glVertexArrayVertexBuffers (){
    return glVertexArrayVertexBuffers_hook ;
}
void setHook_glVertexArrayVertexBuffers ( glVertexArrayVertexBuffers_hook_t hook ){
    glVertexArrayVertexBuffers_hook = hook;
}
void glVertexArrayVertexBuffers ( GLuint vaobj_, GLuint first_, GLsizei count_, const GLuint * buffers_, const GLintptr * offsets_, const GLsizei * strides_ ){
    static PFNGLVERTEXARRAYVERTEXBUFFERSPROC F;
    if(!F)
        F = ( PFNGLVERTEXARRAYVERTEXBUFFERSPROC ) mygetprocaddr("glVertexArrayVertexBuffers");
    if( glVertexArrayVertexBuffers_hook )
        glVertexArrayVertexBuffers_hook( vaobj_, first_, count_, buffers_, offsets_, strides_ );
    F(vaobj_, first_, count_, buffers_, offsets_, strides_);
}
static glVertexAttrib1d_hook_t glVertexAttrib1d_hook = 0;
glVertexAttrib1d_hook_t getHook_glVertexAttrib1d (){
    return glVertexAttrib1d_hook ;
}
void setHook_glVertexAttrib1d ( glVertexAttrib1d_hook_t hook ){
    glVertexAttrib1d_hook = hook;
}
void glVertexAttrib1d ( GLuint index_, GLdouble x_ ){
    static PFNGLVERTEXATTRIB1DPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB1DPROC ) mygetprocaddr("glVertexAttrib1d");
    if( glVertexAttrib1d_hook )
        glVertexAttrib1d_hook( index_, x_ );
    F(index_, x_);
}
static glVertexAttrib1dv_hook_t glVertexAttrib1dv_hook = 0;
glVertexAttrib1dv_hook_t getHook_glVertexAttrib1dv (){
    return glVertexAttrib1dv_hook ;
}
void setHook_glVertexAttrib1dv ( glVertexAttrib1dv_hook_t hook ){
    glVertexAttrib1dv_hook = hook;
}
void glVertexAttrib1dv ( GLuint index_, const GLdouble * v_ ){
    static PFNGLVERTEXATTRIB1DVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB1DVPROC ) mygetprocaddr("glVertexAttrib1dv");
    if( glVertexAttrib1dv_hook )
        glVertexAttrib1dv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib1f_hook_t glVertexAttrib1f_hook = 0;
glVertexAttrib1f_hook_t getHook_glVertexAttrib1f (){
    return glVertexAttrib1f_hook ;
}
void setHook_glVertexAttrib1f ( glVertexAttrib1f_hook_t hook ){
    glVertexAttrib1f_hook = hook;
}
void glVertexAttrib1f ( GLuint index_, GLfloat x_ ){
    static PFNGLVERTEXATTRIB1FPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB1FPROC ) mygetprocaddr("glVertexAttrib1f");
    if( glVertexAttrib1f_hook )
        glVertexAttrib1f_hook( index_, x_ );
    F(index_, x_);
}
static glVertexAttrib1fv_hook_t glVertexAttrib1fv_hook = 0;
glVertexAttrib1fv_hook_t getHook_glVertexAttrib1fv (){
    return glVertexAttrib1fv_hook ;
}
void setHook_glVertexAttrib1fv ( glVertexAttrib1fv_hook_t hook ){
    glVertexAttrib1fv_hook = hook;
}
void glVertexAttrib1fv ( GLuint index_, const GLfloat * v_ ){
    static PFNGLVERTEXATTRIB1FVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB1FVPROC ) mygetprocaddr("glVertexAttrib1fv");
    if( glVertexAttrib1fv_hook )
        glVertexAttrib1fv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib1s_hook_t glVertexAttrib1s_hook = 0;
glVertexAttrib1s_hook_t getHook_glVertexAttrib1s (){
    return glVertexAttrib1s_hook ;
}
void setHook_glVertexAttrib1s ( glVertexAttrib1s_hook_t hook ){
    glVertexAttrib1s_hook = hook;
}
void glVertexAttrib1s ( GLuint index_, GLshort x_ ){
    static PFNGLVERTEXATTRIB1SPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB1SPROC ) mygetprocaddr("glVertexAttrib1s");
    if( glVertexAttrib1s_hook )
        glVertexAttrib1s_hook( index_, x_ );
    F(index_, x_);
}
static glVertexAttrib1sv_hook_t glVertexAttrib1sv_hook = 0;
glVertexAttrib1sv_hook_t getHook_glVertexAttrib1sv (){
    return glVertexAttrib1sv_hook ;
}
void setHook_glVertexAttrib1sv ( glVertexAttrib1sv_hook_t hook ){
    glVertexAttrib1sv_hook = hook;
}
void glVertexAttrib1sv ( GLuint index_, const GLshort * v_ ){
    static PFNGLVERTEXATTRIB1SVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB1SVPROC ) mygetprocaddr("glVertexAttrib1sv");
    if( glVertexAttrib1sv_hook )
        glVertexAttrib1sv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib2d_hook_t glVertexAttrib2d_hook = 0;
glVertexAttrib2d_hook_t getHook_glVertexAttrib2d (){
    return glVertexAttrib2d_hook ;
}
void setHook_glVertexAttrib2d ( glVertexAttrib2d_hook_t hook ){
    glVertexAttrib2d_hook = hook;
}
void glVertexAttrib2d ( GLuint index_, GLdouble x_, GLdouble y_ ){
    static PFNGLVERTEXATTRIB2DPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB2DPROC ) mygetprocaddr("glVertexAttrib2d");
    if( glVertexAttrib2d_hook )
        glVertexAttrib2d_hook( index_, x_, y_ );
    F(index_, x_, y_);
}
static glVertexAttrib2dv_hook_t glVertexAttrib2dv_hook = 0;
glVertexAttrib2dv_hook_t getHook_glVertexAttrib2dv (){
    return glVertexAttrib2dv_hook ;
}
void setHook_glVertexAttrib2dv ( glVertexAttrib2dv_hook_t hook ){
    glVertexAttrib2dv_hook = hook;
}
void glVertexAttrib2dv ( GLuint index_, const GLdouble * v_ ){
    static PFNGLVERTEXATTRIB2DVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB2DVPROC ) mygetprocaddr("glVertexAttrib2dv");
    if( glVertexAttrib2dv_hook )
        glVertexAttrib2dv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib2f_hook_t glVertexAttrib2f_hook = 0;
glVertexAttrib2f_hook_t getHook_glVertexAttrib2f (){
    return glVertexAttrib2f_hook ;
}
void setHook_glVertexAttrib2f ( glVertexAttrib2f_hook_t hook ){
    glVertexAttrib2f_hook = hook;
}
void glVertexAttrib2f ( GLuint index_, GLfloat x_, GLfloat y_ ){
    static PFNGLVERTEXATTRIB2FPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB2FPROC ) mygetprocaddr("glVertexAttrib2f");
    if( glVertexAttrib2f_hook )
        glVertexAttrib2f_hook( index_, x_, y_ );
    F(index_, x_, y_);
}
static glVertexAttrib2fv_hook_t glVertexAttrib2fv_hook = 0;
glVertexAttrib2fv_hook_t getHook_glVertexAttrib2fv (){
    return glVertexAttrib2fv_hook ;
}
void setHook_glVertexAttrib2fv ( glVertexAttrib2fv_hook_t hook ){
    glVertexAttrib2fv_hook = hook;
}
void glVertexAttrib2fv ( GLuint index_, const GLfloat * v_ ){
    static PFNGLVERTEXATTRIB2FVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB2FVPROC ) mygetprocaddr("glVertexAttrib2fv");
    if( glVertexAttrib2fv_hook )
        glVertexAttrib2fv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib2s_hook_t glVertexAttrib2s_hook = 0;
glVertexAttrib2s_hook_t getHook_glVertexAttrib2s (){
    return glVertexAttrib2s_hook ;
}
void setHook_glVertexAttrib2s ( glVertexAttrib2s_hook_t hook ){
    glVertexAttrib2s_hook = hook;
}
void glVertexAttrib2s ( GLuint index_, GLshort x_, GLshort y_ ){
    static PFNGLVERTEXATTRIB2SPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB2SPROC ) mygetprocaddr("glVertexAttrib2s");
    if( glVertexAttrib2s_hook )
        glVertexAttrib2s_hook( index_, x_, y_ );
    F(index_, x_, y_);
}
static glVertexAttrib2sv_hook_t glVertexAttrib2sv_hook = 0;
glVertexAttrib2sv_hook_t getHook_glVertexAttrib2sv (){
    return glVertexAttrib2sv_hook ;
}
void setHook_glVertexAttrib2sv ( glVertexAttrib2sv_hook_t hook ){
    glVertexAttrib2sv_hook = hook;
}
void glVertexAttrib2sv ( GLuint index_, const GLshort * v_ ){
    static PFNGLVERTEXATTRIB2SVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB2SVPROC ) mygetprocaddr("glVertexAttrib2sv");
    if( glVertexAttrib2sv_hook )
        glVertexAttrib2sv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib3d_hook_t glVertexAttrib3d_hook = 0;
glVertexAttrib3d_hook_t getHook_glVertexAttrib3d (){
    return glVertexAttrib3d_hook ;
}
void setHook_glVertexAttrib3d ( glVertexAttrib3d_hook_t hook ){
    glVertexAttrib3d_hook = hook;
}
void glVertexAttrib3d ( GLuint index_, GLdouble x_, GLdouble y_, GLdouble z_ ){
    static PFNGLVERTEXATTRIB3DPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB3DPROC ) mygetprocaddr("glVertexAttrib3d");
    if( glVertexAttrib3d_hook )
        glVertexAttrib3d_hook( index_, x_, y_, z_ );
    F(index_, x_, y_, z_);
}
static glVertexAttrib3dv_hook_t glVertexAttrib3dv_hook = 0;
glVertexAttrib3dv_hook_t getHook_glVertexAttrib3dv (){
    return glVertexAttrib3dv_hook ;
}
void setHook_glVertexAttrib3dv ( glVertexAttrib3dv_hook_t hook ){
    glVertexAttrib3dv_hook = hook;
}
void glVertexAttrib3dv ( GLuint index_, const GLdouble * v_ ){
    static PFNGLVERTEXATTRIB3DVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB3DVPROC ) mygetprocaddr("glVertexAttrib3dv");
    if( glVertexAttrib3dv_hook )
        glVertexAttrib3dv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib3f_hook_t glVertexAttrib3f_hook = 0;
glVertexAttrib3f_hook_t getHook_glVertexAttrib3f (){
    return glVertexAttrib3f_hook ;
}
void setHook_glVertexAttrib3f ( glVertexAttrib3f_hook_t hook ){
    glVertexAttrib3f_hook = hook;
}
void glVertexAttrib3f ( GLuint index_, GLfloat x_, GLfloat y_, GLfloat z_ ){
    static PFNGLVERTEXATTRIB3FPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB3FPROC ) mygetprocaddr("glVertexAttrib3f");
    if( glVertexAttrib3f_hook )
        glVertexAttrib3f_hook( index_, x_, y_, z_ );
    F(index_, x_, y_, z_);
}
static glVertexAttrib3fv_hook_t glVertexAttrib3fv_hook = 0;
glVertexAttrib3fv_hook_t getHook_glVertexAttrib3fv (){
    return glVertexAttrib3fv_hook ;
}
void setHook_glVertexAttrib3fv ( glVertexAttrib3fv_hook_t hook ){
    glVertexAttrib3fv_hook = hook;
}
void glVertexAttrib3fv ( GLuint index_, const GLfloat * v_ ){
    static PFNGLVERTEXATTRIB3FVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB3FVPROC ) mygetprocaddr("glVertexAttrib3fv");
    if( glVertexAttrib3fv_hook )
        glVertexAttrib3fv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib3s_hook_t glVertexAttrib3s_hook = 0;
glVertexAttrib3s_hook_t getHook_glVertexAttrib3s (){
    return glVertexAttrib3s_hook ;
}
void setHook_glVertexAttrib3s ( glVertexAttrib3s_hook_t hook ){
    glVertexAttrib3s_hook = hook;
}
void glVertexAttrib3s ( GLuint index_, GLshort x_, GLshort y_, GLshort z_ ){
    static PFNGLVERTEXATTRIB3SPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB3SPROC ) mygetprocaddr("glVertexAttrib3s");
    if( glVertexAttrib3s_hook )
        glVertexAttrib3s_hook( index_, x_, y_, z_ );
    F(index_, x_, y_, z_);
}
static glVertexAttrib3sv_hook_t glVertexAttrib3sv_hook = 0;
glVertexAttrib3sv_hook_t getHook_glVertexAttrib3sv (){
    return glVertexAttrib3sv_hook ;
}
void setHook_glVertexAttrib3sv ( glVertexAttrib3sv_hook_t hook ){
    glVertexAttrib3sv_hook = hook;
}
void glVertexAttrib3sv ( GLuint index_, const GLshort * v_ ){
    static PFNGLVERTEXATTRIB3SVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB3SVPROC ) mygetprocaddr("glVertexAttrib3sv");
    if( glVertexAttrib3sv_hook )
        glVertexAttrib3sv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4Nbv_hook_t glVertexAttrib4Nbv_hook = 0;
glVertexAttrib4Nbv_hook_t getHook_glVertexAttrib4Nbv (){
    return glVertexAttrib4Nbv_hook ;
}
void setHook_glVertexAttrib4Nbv ( glVertexAttrib4Nbv_hook_t hook ){
    glVertexAttrib4Nbv_hook = hook;
}
void glVertexAttrib4Nbv ( GLuint index_, const GLbyte * v_ ){
    static PFNGLVERTEXATTRIB4NBVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4NBVPROC ) mygetprocaddr("glVertexAttrib4Nbv");
    if( glVertexAttrib4Nbv_hook )
        glVertexAttrib4Nbv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4Niv_hook_t glVertexAttrib4Niv_hook = 0;
glVertexAttrib4Niv_hook_t getHook_glVertexAttrib4Niv (){
    return glVertexAttrib4Niv_hook ;
}
void setHook_glVertexAttrib4Niv ( glVertexAttrib4Niv_hook_t hook ){
    glVertexAttrib4Niv_hook = hook;
}
void glVertexAttrib4Niv ( GLuint index_, const GLint * v_ ){
    static PFNGLVERTEXATTRIB4NIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4NIVPROC ) mygetprocaddr("glVertexAttrib4Niv");
    if( glVertexAttrib4Niv_hook )
        glVertexAttrib4Niv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4Nsv_hook_t glVertexAttrib4Nsv_hook = 0;
glVertexAttrib4Nsv_hook_t getHook_glVertexAttrib4Nsv (){
    return glVertexAttrib4Nsv_hook ;
}
void setHook_glVertexAttrib4Nsv ( glVertexAttrib4Nsv_hook_t hook ){
    glVertexAttrib4Nsv_hook = hook;
}
void glVertexAttrib4Nsv ( GLuint index_, const GLshort * v_ ){
    static PFNGLVERTEXATTRIB4NSVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4NSVPROC ) mygetprocaddr("glVertexAttrib4Nsv");
    if( glVertexAttrib4Nsv_hook )
        glVertexAttrib4Nsv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4Nub_hook_t glVertexAttrib4Nub_hook = 0;
glVertexAttrib4Nub_hook_t getHook_glVertexAttrib4Nub (){
    return glVertexAttrib4Nub_hook ;
}
void setHook_glVertexAttrib4Nub ( glVertexAttrib4Nub_hook_t hook ){
    glVertexAttrib4Nub_hook = hook;
}
void glVertexAttrib4Nub ( GLuint index_, GLubyte x_, GLubyte y_, GLubyte z_, GLubyte w_ ){
    static PFNGLVERTEXATTRIB4NUBPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4NUBPROC ) mygetprocaddr("glVertexAttrib4Nub");
    if( glVertexAttrib4Nub_hook )
        glVertexAttrib4Nub_hook( index_, x_, y_, z_, w_ );
    F(index_, x_, y_, z_, w_);
}
static glVertexAttrib4Nubv_hook_t glVertexAttrib4Nubv_hook = 0;
glVertexAttrib4Nubv_hook_t getHook_glVertexAttrib4Nubv (){
    return glVertexAttrib4Nubv_hook ;
}
void setHook_glVertexAttrib4Nubv ( glVertexAttrib4Nubv_hook_t hook ){
    glVertexAttrib4Nubv_hook = hook;
}
void glVertexAttrib4Nubv ( GLuint index_, const GLubyte * v_ ){
    static PFNGLVERTEXATTRIB4NUBVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4NUBVPROC ) mygetprocaddr("glVertexAttrib4Nubv");
    if( glVertexAttrib4Nubv_hook )
        glVertexAttrib4Nubv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4Nuiv_hook_t glVertexAttrib4Nuiv_hook = 0;
glVertexAttrib4Nuiv_hook_t getHook_glVertexAttrib4Nuiv (){
    return glVertexAttrib4Nuiv_hook ;
}
void setHook_glVertexAttrib4Nuiv ( glVertexAttrib4Nuiv_hook_t hook ){
    glVertexAttrib4Nuiv_hook = hook;
}
void glVertexAttrib4Nuiv ( GLuint index_, const GLuint * v_ ){
    static PFNGLVERTEXATTRIB4NUIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4NUIVPROC ) mygetprocaddr("glVertexAttrib4Nuiv");
    if( glVertexAttrib4Nuiv_hook )
        glVertexAttrib4Nuiv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4Nusv_hook_t glVertexAttrib4Nusv_hook = 0;
glVertexAttrib4Nusv_hook_t getHook_glVertexAttrib4Nusv (){
    return glVertexAttrib4Nusv_hook ;
}
void setHook_glVertexAttrib4Nusv ( glVertexAttrib4Nusv_hook_t hook ){
    glVertexAttrib4Nusv_hook = hook;
}
void glVertexAttrib4Nusv ( GLuint index_, const GLushort * v_ ){
    static PFNGLVERTEXATTRIB4NUSVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4NUSVPROC ) mygetprocaddr("glVertexAttrib4Nusv");
    if( glVertexAttrib4Nusv_hook )
        glVertexAttrib4Nusv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4bv_hook_t glVertexAttrib4bv_hook = 0;
glVertexAttrib4bv_hook_t getHook_glVertexAttrib4bv (){
    return glVertexAttrib4bv_hook ;
}
void setHook_glVertexAttrib4bv ( glVertexAttrib4bv_hook_t hook ){
    glVertexAttrib4bv_hook = hook;
}
void glVertexAttrib4bv ( GLuint index_, const GLbyte * v_ ){
    static PFNGLVERTEXATTRIB4BVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4BVPROC ) mygetprocaddr("glVertexAttrib4bv");
    if( glVertexAttrib4bv_hook )
        glVertexAttrib4bv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4d_hook_t glVertexAttrib4d_hook = 0;
glVertexAttrib4d_hook_t getHook_glVertexAttrib4d (){
    return glVertexAttrib4d_hook ;
}
void setHook_glVertexAttrib4d ( glVertexAttrib4d_hook_t hook ){
    glVertexAttrib4d_hook = hook;
}
void glVertexAttrib4d ( GLuint index_, GLdouble x_, GLdouble y_, GLdouble z_, GLdouble w_ ){
    static PFNGLVERTEXATTRIB4DPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4DPROC ) mygetprocaddr("glVertexAttrib4d");
    if( glVertexAttrib4d_hook )
        glVertexAttrib4d_hook( index_, x_, y_, z_, w_ );
    F(index_, x_, y_, z_, w_);
}
static glVertexAttrib4dv_hook_t glVertexAttrib4dv_hook = 0;
glVertexAttrib4dv_hook_t getHook_glVertexAttrib4dv (){
    return glVertexAttrib4dv_hook ;
}
void setHook_glVertexAttrib4dv ( glVertexAttrib4dv_hook_t hook ){
    glVertexAttrib4dv_hook = hook;
}
void glVertexAttrib4dv ( GLuint index_, const GLdouble * v_ ){
    static PFNGLVERTEXATTRIB4DVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4DVPROC ) mygetprocaddr("glVertexAttrib4dv");
    if( glVertexAttrib4dv_hook )
        glVertexAttrib4dv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4f_hook_t glVertexAttrib4f_hook = 0;
glVertexAttrib4f_hook_t getHook_glVertexAttrib4f (){
    return glVertexAttrib4f_hook ;
}
void setHook_glVertexAttrib4f ( glVertexAttrib4f_hook_t hook ){
    glVertexAttrib4f_hook = hook;
}
void glVertexAttrib4f ( GLuint index_, GLfloat x_, GLfloat y_, GLfloat z_, GLfloat w_ ){
    static PFNGLVERTEXATTRIB4FPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4FPROC ) mygetprocaddr("glVertexAttrib4f");
    if( glVertexAttrib4f_hook )
        glVertexAttrib4f_hook( index_, x_, y_, z_, w_ );
    F(index_, x_, y_, z_, w_);
}
static glVertexAttrib4fv_hook_t glVertexAttrib4fv_hook = 0;
glVertexAttrib4fv_hook_t getHook_glVertexAttrib4fv (){
    return glVertexAttrib4fv_hook ;
}
void setHook_glVertexAttrib4fv ( glVertexAttrib4fv_hook_t hook ){
    glVertexAttrib4fv_hook = hook;
}
void glVertexAttrib4fv ( GLuint index_, const GLfloat * v_ ){
    static PFNGLVERTEXATTRIB4FVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4FVPROC ) mygetprocaddr("glVertexAttrib4fv");
    if( glVertexAttrib4fv_hook )
        glVertexAttrib4fv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4iv_hook_t glVertexAttrib4iv_hook = 0;
glVertexAttrib4iv_hook_t getHook_glVertexAttrib4iv (){
    return glVertexAttrib4iv_hook ;
}
void setHook_glVertexAttrib4iv ( glVertexAttrib4iv_hook_t hook ){
    glVertexAttrib4iv_hook = hook;
}
void glVertexAttrib4iv ( GLuint index_, const GLint * v_ ){
    static PFNGLVERTEXATTRIB4IVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4IVPROC ) mygetprocaddr("glVertexAttrib4iv");
    if( glVertexAttrib4iv_hook )
        glVertexAttrib4iv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4s_hook_t glVertexAttrib4s_hook = 0;
glVertexAttrib4s_hook_t getHook_glVertexAttrib4s (){
    return glVertexAttrib4s_hook ;
}
void setHook_glVertexAttrib4s ( glVertexAttrib4s_hook_t hook ){
    glVertexAttrib4s_hook = hook;
}
void glVertexAttrib4s ( GLuint index_, GLshort x_, GLshort y_, GLshort z_, GLshort w_ ){
    static PFNGLVERTEXATTRIB4SPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4SPROC ) mygetprocaddr("glVertexAttrib4s");
    if( glVertexAttrib4s_hook )
        glVertexAttrib4s_hook( index_, x_, y_, z_, w_ );
    F(index_, x_, y_, z_, w_);
}
static glVertexAttrib4sv_hook_t glVertexAttrib4sv_hook = 0;
glVertexAttrib4sv_hook_t getHook_glVertexAttrib4sv (){
    return glVertexAttrib4sv_hook ;
}
void setHook_glVertexAttrib4sv ( glVertexAttrib4sv_hook_t hook ){
    glVertexAttrib4sv_hook = hook;
}
void glVertexAttrib4sv ( GLuint index_, const GLshort * v_ ){
    static PFNGLVERTEXATTRIB4SVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4SVPROC ) mygetprocaddr("glVertexAttrib4sv");
    if( glVertexAttrib4sv_hook )
        glVertexAttrib4sv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4ubv_hook_t glVertexAttrib4ubv_hook = 0;
glVertexAttrib4ubv_hook_t getHook_glVertexAttrib4ubv (){
    return glVertexAttrib4ubv_hook ;
}
void setHook_glVertexAttrib4ubv ( glVertexAttrib4ubv_hook_t hook ){
    glVertexAttrib4ubv_hook = hook;
}
void glVertexAttrib4ubv ( GLuint index_, const GLubyte * v_ ){
    static PFNGLVERTEXATTRIB4UBVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4UBVPROC ) mygetprocaddr("glVertexAttrib4ubv");
    if( glVertexAttrib4ubv_hook )
        glVertexAttrib4ubv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4uiv_hook_t glVertexAttrib4uiv_hook = 0;
glVertexAttrib4uiv_hook_t getHook_glVertexAttrib4uiv (){
    return glVertexAttrib4uiv_hook ;
}
void setHook_glVertexAttrib4uiv ( glVertexAttrib4uiv_hook_t hook ){
    glVertexAttrib4uiv_hook = hook;
}
void glVertexAttrib4uiv ( GLuint index_, const GLuint * v_ ){
    static PFNGLVERTEXATTRIB4UIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4UIVPROC ) mygetprocaddr("glVertexAttrib4uiv");
    if( glVertexAttrib4uiv_hook )
        glVertexAttrib4uiv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttrib4usv_hook_t glVertexAttrib4usv_hook = 0;
glVertexAttrib4usv_hook_t getHook_glVertexAttrib4usv (){
    return glVertexAttrib4usv_hook ;
}
void setHook_glVertexAttrib4usv ( glVertexAttrib4usv_hook_t hook ){
    glVertexAttrib4usv_hook = hook;
}
void glVertexAttrib4usv ( GLuint index_, const GLushort * v_ ){
    static PFNGLVERTEXATTRIB4USVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIB4USVPROC ) mygetprocaddr("glVertexAttrib4usv");
    if( glVertexAttrib4usv_hook )
        glVertexAttrib4usv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribBinding_hook_t glVertexAttribBinding_hook = 0;
glVertexAttribBinding_hook_t getHook_glVertexAttribBinding (){
    return glVertexAttribBinding_hook ;
}
void setHook_glVertexAttribBinding ( glVertexAttribBinding_hook_t hook ){
    glVertexAttribBinding_hook = hook;
}
void glVertexAttribBinding ( GLuint attribindex_, GLuint bindingindex_ ){
    static PFNGLVERTEXATTRIBBINDINGPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBBINDINGPROC ) mygetprocaddr("glVertexAttribBinding");
    if( glVertexAttribBinding_hook )
        glVertexAttribBinding_hook( attribindex_, bindingindex_ );
    F(attribindex_, bindingindex_);
}
static glVertexAttribDivisor_hook_t glVertexAttribDivisor_hook = 0;
glVertexAttribDivisor_hook_t getHook_glVertexAttribDivisor (){
    return glVertexAttribDivisor_hook ;
}
void setHook_glVertexAttribDivisor ( glVertexAttribDivisor_hook_t hook ){
    glVertexAttribDivisor_hook = hook;
}
void glVertexAttribDivisor ( GLuint index_, GLuint divisor_ ){
    static PFNGLVERTEXATTRIBDIVISORPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBDIVISORPROC ) mygetprocaddr("glVertexAttribDivisor");
    if( glVertexAttribDivisor_hook )
        glVertexAttribDivisor_hook( index_, divisor_ );
    F(index_, divisor_);
}
static glVertexAttribFormat_hook_t glVertexAttribFormat_hook = 0;
glVertexAttribFormat_hook_t getHook_glVertexAttribFormat (){
    return glVertexAttribFormat_hook ;
}
void setHook_glVertexAttribFormat ( glVertexAttribFormat_hook_t hook ){
    glVertexAttribFormat_hook = hook;
}
void glVertexAttribFormat ( GLuint attribindex_, GLint size_, GLenum type_, GLboolean normalized_, GLuint relativeoffset_ ){
    static PFNGLVERTEXATTRIBFORMATPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBFORMATPROC ) mygetprocaddr("glVertexAttribFormat");
    if( glVertexAttribFormat_hook )
        glVertexAttribFormat_hook( attribindex_, size_, type_, normalized_, relativeoffset_ );
    F(attribindex_, size_, type_, normalized_, relativeoffset_);
}
static glVertexAttribI1i_hook_t glVertexAttribI1i_hook = 0;
glVertexAttribI1i_hook_t getHook_glVertexAttribI1i (){
    return glVertexAttribI1i_hook ;
}
void setHook_glVertexAttribI1i ( glVertexAttribI1i_hook_t hook ){
    glVertexAttribI1i_hook = hook;
}
void glVertexAttribI1i ( GLuint index_, GLint x_ ){
    static PFNGLVERTEXATTRIBI1IPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI1IPROC ) mygetprocaddr("glVertexAttribI1i");
    if( glVertexAttribI1i_hook )
        glVertexAttribI1i_hook( index_, x_ );
    F(index_, x_);
}
static glVertexAttribI1iv_hook_t glVertexAttribI1iv_hook = 0;
glVertexAttribI1iv_hook_t getHook_glVertexAttribI1iv (){
    return glVertexAttribI1iv_hook ;
}
void setHook_glVertexAttribI1iv ( glVertexAttribI1iv_hook_t hook ){
    glVertexAttribI1iv_hook = hook;
}
void glVertexAttribI1iv ( GLuint index_, const GLint * v_ ){
    static PFNGLVERTEXATTRIBI1IVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI1IVPROC ) mygetprocaddr("glVertexAttribI1iv");
    if( glVertexAttribI1iv_hook )
        glVertexAttribI1iv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI1ui_hook_t glVertexAttribI1ui_hook = 0;
glVertexAttribI1ui_hook_t getHook_glVertexAttribI1ui (){
    return glVertexAttribI1ui_hook ;
}
void setHook_glVertexAttribI1ui ( glVertexAttribI1ui_hook_t hook ){
    glVertexAttribI1ui_hook = hook;
}
void glVertexAttribI1ui ( GLuint index_, GLuint x_ ){
    static PFNGLVERTEXATTRIBI1UIPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI1UIPROC ) mygetprocaddr("glVertexAttribI1ui");
    if( glVertexAttribI1ui_hook )
        glVertexAttribI1ui_hook( index_, x_ );
    F(index_, x_);
}
static glVertexAttribI1uiv_hook_t glVertexAttribI1uiv_hook = 0;
glVertexAttribI1uiv_hook_t getHook_glVertexAttribI1uiv (){
    return glVertexAttribI1uiv_hook ;
}
void setHook_glVertexAttribI1uiv ( glVertexAttribI1uiv_hook_t hook ){
    glVertexAttribI1uiv_hook = hook;
}
void glVertexAttribI1uiv ( GLuint index_, const GLuint * v_ ){
    static PFNGLVERTEXATTRIBI1UIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI1UIVPROC ) mygetprocaddr("glVertexAttribI1uiv");
    if( glVertexAttribI1uiv_hook )
        glVertexAttribI1uiv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI2i_hook_t glVertexAttribI2i_hook = 0;
glVertexAttribI2i_hook_t getHook_glVertexAttribI2i (){
    return glVertexAttribI2i_hook ;
}
void setHook_glVertexAttribI2i ( glVertexAttribI2i_hook_t hook ){
    glVertexAttribI2i_hook = hook;
}
void glVertexAttribI2i ( GLuint index_, GLint x_, GLint y_ ){
    static PFNGLVERTEXATTRIBI2IPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI2IPROC ) mygetprocaddr("glVertexAttribI2i");
    if( glVertexAttribI2i_hook )
        glVertexAttribI2i_hook( index_, x_, y_ );
    F(index_, x_, y_);
}
static glVertexAttribI2iv_hook_t glVertexAttribI2iv_hook = 0;
glVertexAttribI2iv_hook_t getHook_glVertexAttribI2iv (){
    return glVertexAttribI2iv_hook ;
}
void setHook_glVertexAttribI2iv ( glVertexAttribI2iv_hook_t hook ){
    glVertexAttribI2iv_hook = hook;
}
void glVertexAttribI2iv ( GLuint index_, const GLint * v_ ){
    static PFNGLVERTEXATTRIBI2IVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI2IVPROC ) mygetprocaddr("glVertexAttribI2iv");
    if( glVertexAttribI2iv_hook )
        glVertexAttribI2iv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI2ui_hook_t glVertexAttribI2ui_hook = 0;
glVertexAttribI2ui_hook_t getHook_glVertexAttribI2ui (){
    return glVertexAttribI2ui_hook ;
}
void setHook_glVertexAttribI2ui ( glVertexAttribI2ui_hook_t hook ){
    glVertexAttribI2ui_hook = hook;
}
void glVertexAttribI2ui ( GLuint index_, GLuint x_, GLuint y_ ){
    static PFNGLVERTEXATTRIBI2UIPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI2UIPROC ) mygetprocaddr("glVertexAttribI2ui");
    if( glVertexAttribI2ui_hook )
        glVertexAttribI2ui_hook( index_, x_, y_ );
    F(index_, x_, y_);
}
static glVertexAttribI2uiv_hook_t glVertexAttribI2uiv_hook = 0;
glVertexAttribI2uiv_hook_t getHook_glVertexAttribI2uiv (){
    return glVertexAttribI2uiv_hook ;
}
void setHook_glVertexAttribI2uiv ( glVertexAttribI2uiv_hook_t hook ){
    glVertexAttribI2uiv_hook = hook;
}
void glVertexAttribI2uiv ( GLuint index_, const GLuint * v_ ){
    static PFNGLVERTEXATTRIBI2UIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI2UIVPROC ) mygetprocaddr("glVertexAttribI2uiv");
    if( glVertexAttribI2uiv_hook )
        glVertexAttribI2uiv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI3i_hook_t glVertexAttribI3i_hook = 0;
glVertexAttribI3i_hook_t getHook_glVertexAttribI3i (){
    return glVertexAttribI3i_hook ;
}
void setHook_glVertexAttribI3i ( glVertexAttribI3i_hook_t hook ){
    glVertexAttribI3i_hook = hook;
}
void glVertexAttribI3i ( GLuint index_, GLint x_, GLint y_, GLint z_ ){
    static PFNGLVERTEXATTRIBI3IPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI3IPROC ) mygetprocaddr("glVertexAttribI3i");
    if( glVertexAttribI3i_hook )
        glVertexAttribI3i_hook( index_, x_, y_, z_ );
    F(index_, x_, y_, z_);
}
static glVertexAttribI3iv_hook_t glVertexAttribI3iv_hook = 0;
glVertexAttribI3iv_hook_t getHook_glVertexAttribI3iv (){
    return glVertexAttribI3iv_hook ;
}
void setHook_glVertexAttribI3iv ( glVertexAttribI3iv_hook_t hook ){
    glVertexAttribI3iv_hook = hook;
}
void glVertexAttribI3iv ( GLuint index_, const GLint * v_ ){
    static PFNGLVERTEXATTRIBI3IVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI3IVPROC ) mygetprocaddr("glVertexAttribI3iv");
    if( glVertexAttribI3iv_hook )
        glVertexAttribI3iv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI3ui_hook_t glVertexAttribI3ui_hook = 0;
glVertexAttribI3ui_hook_t getHook_glVertexAttribI3ui (){
    return glVertexAttribI3ui_hook ;
}
void setHook_glVertexAttribI3ui ( glVertexAttribI3ui_hook_t hook ){
    glVertexAttribI3ui_hook = hook;
}
void glVertexAttribI3ui ( GLuint index_, GLuint x_, GLuint y_, GLuint z_ ){
    static PFNGLVERTEXATTRIBI3UIPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI3UIPROC ) mygetprocaddr("glVertexAttribI3ui");
    if( glVertexAttribI3ui_hook )
        glVertexAttribI3ui_hook( index_, x_, y_, z_ );
    F(index_, x_, y_, z_);
}
static glVertexAttribI3uiv_hook_t glVertexAttribI3uiv_hook = 0;
glVertexAttribI3uiv_hook_t getHook_glVertexAttribI3uiv (){
    return glVertexAttribI3uiv_hook ;
}
void setHook_glVertexAttribI3uiv ( glVertexAttribI3uiv_hook_t hook ){
    glVertexAttribI3uiv_hook = hook;
}
void glVertexAttribI3uiv ( GLuint index_, const GLuint * v_ ){
    static PFNGLVERTEXATTRIBI3UIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI3UIVPROC ) mygetprocaddr("glVertexAttribI3uiv");
    if( glVertexAttribI3uiv_hook )
        glVertexAttribI3uiv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI4bv_hook_t glVertexAttribI4bv_hook = 0;
glVertexAttribI4bv_hook_t getHook_glVertexAttribI4bv (){
    return glVertexAttribI4bv_hook ;
}
void setHook_glVertexAttribI4bv ( glVertexAttribI4bv_hook_t hook ){
    glVertexAttribI4bv_hook = hook;
}
void glVertexAttribI4bv ( GLuint index_, const GLbyte * v_ ){
    static PFNGLVERTEXATTRIBI4BVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI4BVPROC ) mygetprocaddr("glVertexAttribI4bv");
    if( glVertexAttribI4bv_hook )
        glVertexAttribI4bv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI4i_hook_t glVertexAttribI4i_hook = 0;
glVertexAttribI4i_hook_t getHook_glVertexAttribI4i (){
    return glVertexAttribI4i_hook ;
}
void setHook_glVertexAttribI4i ( glVertexAttribI4i_hook_t hook ){
    glVertexAttribI4i_hook = hook;
}
void glVertexAttribI4i ( GLuint index_, GLint x_, GLint y_, GLint z_, GLint w_ ){
    static PFNGLVERTEXATTRIBI4IPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI4IPROC ) mygetprocaddr("glVertexAttribI4i");
    if( glVertexAttribI4i_hook )
        glVertexAttribI4i_hook( index_, x_, y_, z_, w_ );
    F(index_, x_, y_, z_, w_);
}
static glVertexAttribI4iv_hook_t glVertexAttribI4iv_hook = 0;
glVertexAttribI4iv_hook_t getHook_glVertexAttribI4iv (){
    return glVertexAttribI4iv_hook ;
}
void setHook_glVertexAttribI4iv ( glVertexAttribI4iv_hook_t hook ){
    glVertexAttribI4iv_hook = hook;
}
void glVertexAttribI4iv ( GLuint index_, const GLint * v_ ){
    static PFNGLVERTEXATTRIBI4IVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI4IVPROC ) mygetprocaddr("glVertexAttribI4iv");
    if( glVertexAttribI4iv_hook )
        glVertexAttribI4iv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI4sv_hook_t glVertexAttribI4sv_hook = 0;
glVertexAttribI4sv_hook_t getHook_glVertexAttribI4sv (){
    return glVertexAttribI4sv_hook ;
}
void setHook_glVertexAttribI4sv ( glVertexAttribI4sv_hook_t hook ){
    glVertexAttribI4sv_hook = hook;
}
void glVertexAttribI4sv ( GLuint index_, const GLshort * v_ ){
    static PFNGLVERTEXATTRIBI4SVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI4SVPROC ) mygetprocaddr("glVertexAttribI4sv");
    if( glVertexAttribI4sv_hook )
        glVertexAttribI4sv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI4ubv_hook_t glVertexAttribI4ubv_hook = 0;
glVertexAttribI4ubv_hook_t getHook_glVertexAttribI4ubv (){
    return glVertexAttribI4ubv_hook ;
}
void setHook_glVertexAttribI4ubv ( glVertexAttribI4ubv_hook_t hook ){
    glVertexAttribI4ubv_hook = hook;
}
void glVertexAttribI4ubv ( GLuint index_, const GLubyte * v_ ){
    static PFNGLVERTEXATTRIBI4UBVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI4UBVPROC ) mygetprocaddr("glVertexAttribI4ubv");
    if( glVertexAttribI4ubv_hook )
        glVertexAttribI4ubv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI4ui_hook_t glVertexAttribI4ui_hook = 0;
glVertexAttribI4ui_hook_t getHook_glVertexAttribI4ui (){
    return glVertexAttribI4ui_hook ;
}
void setHook_glVertexAttribI4ui ( glVertexAttribI4ui_hook_t hook ){
    glVertexAttribI4ui_hook = hook;
}
void glVertexAttribI4ui ( GLuint index_, GLuint x_, GLuint y_, GLuint z_, GLuint w_ ){
    static PFNGLVERTEXATTRIBI4UIPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI4UIPROC ) mygetprocaddr("glVertexAttribI4ui");
    if( glVertexAttribI4ui_hook )
        glVertexAttribI4ui_hook( index_, x_, y_, z_, w_ );
    F(index_, x_, y_, z_, w_);
}
static glVertexAttribI4uiv_hook_t glVertexAttribI4uiv_hook = 0;
glVertexAttribI4uiv_hook_t getHook_glVertexAttribI4uiv (){
    return glVertexAttribI4uiv_hook ;
}
void setHook_glVertexAttribI4uiv ( glVertexAttribI4uiv_hook_t hook ){
    glVertexAttribI4uiv_hook = hook;
}
void glVertexAttribI4uiv ( GLuint index_, const GLuint * v_ ){
    static PFNGLVERTEXATTRIBI4UIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI4UIVPROC ) mygetprocaddr("glVertexAttribI4uiv");
    if( glVertexAttribI4uiv_hook )
        glVertexAttribI4uiv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribI4usv_hook_t glVertexAttribI4usv_hook = 0;
glVertexAttribI4usv_hook_t getHook_glVertexAttribI4usv (){
    return glVertexAttribI4usv_hook ;
}
void setHook_glVertexAttribI4usv ( glVertexAttribI4usv_hook_t hook ){
    glVertexAttribI4usv_hook = hook;
}
void glVertexAttribI4usv ( GLuint index_, const GLushort * v_ ){
    static PFNGLVERTEXATTRIBI4USVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBI4USVPROC ) mygetprocaddr("glVertexAttribI4usv");
    if( glVertexAttribI4usv_hook )
        glVertexAttribI4usv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribL1d_hook_t glVertexAttribL1d_hook = 0;
glVertexAttribL1d_hook_t getHook_glVertexAttribL1d (){
    return glVertexAttribL1d_hook ;
}
void setHook_glVertexAttribL1d ( glVertexAttribL1d_hook_t hook ){
    glVertexAttribL1d_hook = hook;
}
void glVertexAttribL1d ( GLuint index_, GLdouble x_ ){
    static PFNGLVERTEXATTRIBL1DPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBL1DPROC ) mygetprocaddr("glVertexAttribL1d");
    if( glVertexAttribL1d_hook )
        glVertexAttribL1d_hook( index_, x_ );
    F(index_, x_);
}
static glVertexAttribL1dv_hook_t glVertexAttribL1dv_hook = 0;
glVertexAttribL1dv_hook_t getHook_glVertexAttribL1dv (){
    return glVertexAttribL1dv_hook ;
}
void setHook_glVertexAttribL1dv ( glVertexAttribL1dv_hook_t hook ){
    glVertexAttribL1dv_hook = hook;
}
void glVertexAttribL1dv ( GLuint index_, const GLdouble * v_ ){
    static PFNGLVERTEXATTRIBL1DVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBL1DVPROC ) mygetprocaddr("glVertexAttribL1dv");
    if( glVertexAttribL1dv_hook )
        glVertexAttribL1dv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribL2d_hook_t glVertexAttribL2d_hook = 0;
glVertexAttribL2d_hook_t getHook_glVertexAttribL2d (){
    return glVertexAttribL2d_hook ;
}
void setHook_glVertexAttribL2d ( glVertexAttribL2d_hook_t hook ){
    glVertexAttribL2d_hook = hook;
}
void glVertexAttribL2d ( GLuint index_, GLdouble x_, GLdouble y_ ){
    static PFNGLVERTEXATTRIBL2DPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBL2DPROC ) mygetprocaddr("glVertexAttribL2d");
    if( glVertexAttribL2d_hook )
        glVertexAttribL2d_hook( index_, x_, y_ );
    F(index_, x_, y_);
}
static glVertexAttribL2dv_hook_t glVertexAttribL2dv_hook = 0;
glVertexAttribL2dv_hook_t getHook_glVertexAttribL2dv (){
    return glVertexAttribL2dv_hook ;
}
void setHook_glVertexAttribL2dv ( glVertexAttribL2dv_hook_t hook ){
    glVertexAttribL2dv_hook = hook;
}
void glVertexAttribL2dv ( GLuint index_, const GLdouble * v_ ){
    static PFNGLVERTEXATTRIBL2DVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBL2DVPROC ) mygetprocaddr("glVertexAttribL2dv");
    if( glVertexAttribL2dv_hook )
        glVertexAttribL2dv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribL3d_hook_t glVertexAttribL3d_hook = 0;
glVertexAttribL3d_hook_t getHook_glVertexAttribL3d (){
    return glVertexAttribL3d_hook ;
}
void setHook_glVertexAttribL3d ( glVertexAttribL3d_hook_t hook ){
    glVertexAttribL3d_hook = hook;
}
void glVertexAttribL3d ( GLuint index_, GLdouble x_, GLdouble y_, GLdouble z_ ){
    static PFNGLVERTEXATTRIBL3DPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBL3DPROC ) mygetprocaddr("glVertexAttribL3d");
    if( glVertexAttribL3d_hook )
        glVertexAttribL3d_hook( index_, x_, y_, z_ );
    F(index_, x_, y_, z_);
}
static glVertexAttribL3dv_hook_t glVertexAttribL3dv_hook = 0;
glVertexAttribL3dv_hook_t getHook_glVertexAttribL3dv (){
    return glVertexAttribL3dv_hook ;
}
void setHook_glVertexAttribL3dv ( glVertexAttribL3dv_hook_t hook ){
    glVertexAttribL3dv_hook = hook;
}
void glVertexAttribL3dv ( GLuint index_, const GLdouble * v_ ){
    static PFNGLVERTEXATTRIBL3DVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBL3DVPROC ) mygetprocaddr("glVertexAttribL3dv");
    if( glVertexAttribL3dv_hook )
        glVertexAttribL3dv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribL4d_hook_t glVertexAttribL4d_hook = 0;
glVertexAttribL4d_hook_t getHook_glVertexAttribL4d (){
    return glVertexAttribL4d_hook ;
}
void setHook_glVertexAttribL4d ( glVertexAttribL4d_hook_t hook ){
    glVertexAttribL4d_hook = hook;
}
void glVertexAttribL4d ( GLuint index_, GLdouble x_, GLdouble y_, GLdouble z_, GLdouble w_ ){
    static PFNGLVERTEXATTRIBL4DPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBL4DPROC ) mygetprocaddr("glVertexAttribL4d");
    if( glVertexAttribL4d_hook )
        glVertexAttribL4d_hook( index_, x_, y_, z_, w_ );
    F(index_, x_, y_, z_, w_);
}
static glVertexAttribL4dv_hook_t glVertexAttribL4dv_hook = 0;
glVertexAttribL4dv_hook_t getHook_glVertexAttribL4dv (){
    return glVertexAttribL4dv_hook ;
}
void setHook_glVertexAttribL4dv ( glVertexAttribL4dv_hook_t hook ){
    glVertexAttribL4dv_hook = hook;
}
void glVertexAttribL4dv ( GLuint index_, const GLdouble * v_ ){
    static PFNGLVERTEXATTRIBL4DVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBL4DVPROC ) mygetprocaddr("glVertexAttribL4dv");
    if( glVertexAttribL4dv_hook )
        glVertexAttribL4dv_hook( index_, v_ );
    F(index_, v_);
}
static glVertexAttribP1ui_hook_t glVertexAttribP1ui_hook = 0;
glVertexAttribP1ui_hook_t getHook_glVertexAttribP1ui (){
    return glVertexAttribP1ui_hook ;
}
void setHook_glVertexAttribP1ui ( glVertexAttribP1ui_hook_t hook ){
    glVertexAttribP1ui_hook = hook;
}
void glVertexAttribP1ui ( GLuint index_, GLenum type_, GLboolean normalized_, GLuint value_ ){
    static PFNGLVERTEXATTRIBP1UIPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBP1UIPROC ) mygetprocaddr("glVertexAttribP1ui");
    if( glVertexAttribP1ui_hook )
        glVertexAttribP1ui_hook( index_, type_, normalized_, value_ );
    F(index_, type_, normalized_, value_);
}
static glVertexAttribP1uiv_hook_t glVertexAttribP1uiv_hook = 0;
glVertexAttribP1uiv_hook_t getHook_glVertexAttribP1uiv (){
    return glVertexAttribP1uiv_hook ;
}
void setHook_glVertexAttribP1uiv ( glVertexAttribP1uiv_hook_t hook ){
    glVertexAttribP1uiv_hook = hook;
}
void glVertexAttribP1uiv ( GLuint index_, GLenum type_, GLboolean normalized_, const GLuint * value_ ){
    static PFNGLVERTEXATTRIBP1UIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBP1UIVPROC ) mygetprocaddr("glVertexAttribP1uiv");
    if( glVertexAttribP1uiv_hook )
        glVertexAttribP1uiv_hook( index_, type_, normalized_, value_ );
    F(index_, type_, normalized_, value_);
}
static glVertexAttribP2ui_hook_t glVertexAttribP2ui_hook = 0;
glVertexAttribP2ui_hook_t getHook_glVertexAttribP2ui (){
    return glVertexAttribP2ui_hook ;
}
void setHook_glVertexAttribP2ui ( glVertexAttribP2ui_hook_t hook ){
    glVertexAttribP2ui_hook = hook;
}
void glVertexAttribP2ui ( GLuint index_, GLenum type_, GLboolean normalized_, GLuint value_ ){
    static PFNGLVERTEXATTRIBP2UIPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBP2UIPROC ) mygetprocaddr("glVertexAttribP2ui");
    if( glVertexAttribP2ui_hook )
        glVertexAttribP2ui_hook( index_, type_, normalized_, value_ );
    F(index_, type_, normalized_, value_);
}
static glVertexAttribP2uiv_hook_t glVertexAttribP2uiv_hook = 0;
glVertexAttribP2uiv_hook_t getHook_glVertexAttribP2uiv (){
    return glVertexAttribP2uiv_hook ;
}
void setHook_glVertexAttribP2uiv ( glVertexAttribP2uiv_hook_t hook ){
    glVertexAttribP2uiv_hook = hook;
}
void glVertexAttribP2uiv ( GLuint index_, GLenum type_, GLboolean normalized_, const GLuint * value_ ){
    static PFNGLVERTEXATTRIBP2UIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBP2UIVPROC ) mygetprocaddr("glVertexAttribP2uiv");
    if( glVertexAttribP2uiv_hook )
        glVertexAttribP2uiv_hook( index_, type_, normalized_, value_ );
    F(index_, type_, normalized_, value_);
}
static glVertexAttribP3ui_hook_t glVertexAttribP3ui_hook = 0;
glVertexAttribP3ui_hook_t getHook_glVertexAttribP3ui (){
    return glVertexAttribP3ui_hook ;
}
void setHook_glVertexAttribP3ui ( glVertexAttribP3ui_hook_t hook ){
    glVertexAttribP3ui_hook = hook;
}
void glVertexAttribP3ui ( GLuint index_, GLenum type_, GLboolean normalized_, GLuint value_ ){
    static PFNGLVERTEXATTRIBP3UIPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBP3UIPROC ) mygetprocaddr("glVertexAttribP3ui");
    if( glVertexAttribP3ui_hook )
        glVertexAttribP3ui_hook( index_, type_, normalized_, value_ );
    F(index_, type_, normalized_, value_);
}
static glVertexAttribP3uiv_hook_t glVertexAttribP3uiv_hook = 0;
glVertexAttribP3uiv_hook_t getHook_glVertexAttribP3uiv (){
    return glVertexAttribP3uiv_hook ;
}
void setHook_glVertexAttribP3uiv ( glVertexAttribP3uiv_hook_t hook ){
    glVertexAttribP3uiv_hook = hook;
}
void glVertexAttribP3uiv ( GLuint index_, GLenum type_, GLboolean normalized_, const GLuint * value_ ){
    static PFNGLVERTEXATTRIBP3UIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBP3UIVPROC ) mygetprocaddr("glVertexAttribP3uiv");
    if( glVertexAttribP3uiv_hook )
        glVertexAttribP3uiv_hook( index_, type_, normalized_, value_ );
    F(index_, type_, normalized_, value_);
}
static glVertexAttribP4ui_hook_t glVertexAttribP4ui_hook = 0;
glVertexAttribP4ui_hook_t getHook_glVertexAttribP4ui (){
    return glVertexAttribP4ui_hook ;
}
void setHook_glVertexAttribP4ui ( glVertexAttribP4ui_hook_t hook ){
    glVertexAttribP4ui_hook = hook;
}
void glVertexAttribP4ui ( GLuint index_, GLenum type_, GLboolean normalized_, GLuint value_ ){
    static PFNGLVERTEXATTRIBP4UIPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBP4UIPROC ) mygetprocaddr("glVertexAttribP4ui");
    if( glVertexAttribP4ui_hook )
        glVertexAttribP4ui_hook( index_, type_, normalized_, value_ );
    F(index_, type_, normalized_, value_);
}
static glVertexAttribP4uiv_hook_t glVertexAttribP4uiv_hook = 0;
glVertexAttribP4uiv_hook_t getHook_glVertexAttribP4uiv (){
    return glVertexAttribP4uiv_hook ;
}
void setHook_glVertexAttribP4uiv ( glVertexAttribP4uiv_hook_t hook ){
    glVertexAttribP4uiv_hook = hook;
}
void glVertexAttribP4uiv ( GLuint index_, GLenum type_, GLboolean normalized_, const GLuint * value_ ){
    static PFNGLVERTEXATTRIBP4UIVPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBP4UIVPROC ) mygetprocaddr("glVertexAttribP4uiv");
    if( glVertexAttribP4uiv_hook )
        glVertexAttribP4uiv_hook( index_, type_, normalized_, value_ );
    F(index_, type_, normalized_, value_);
}
static glVertexAttribPointer_hook_t glVertexAttribPointer_hook = 0;
glVertexAttribPointer_hook_t getHook_glVertexAttribPointer (){
    return glVertexAttribPointer_hook ;
}
void setHook_glVertexAttribPointer ( glVertexAttribPointer_hook_t hook ){
    glVertexAttribPointer_hook = hook;
}
void glVertexAttribPointer ( GLuint index_, GLint size_, GLenum type_, GLboolean normalized_, GLsizei stride_, const void * pointer_ ){
    static PFNGLVERTEXATTRIBPOINTERPROC F;
    if(!F)
        F = ( PFNGLVERTEXATTRIBPOINTERPROC ) mygetprocaddr("glVertexAttribPointer");
    if( glVertexAttribPointer_hook )
        glVertexAttribPointer_hook( index_, size_, type_, normalized_, stride_, pointer_ );
    F(index_, size_, type_, normalized_, stride_, pointer_);
}
static glVertexBindingDivisor_hook_t glVertexBindingDivisor_hook = 0;
glVertexBindingDivisor_hook_t getHook_glVertexBindingDivisor (){
    return glVertexBindingDivisor_hook ;
}
void setHook_glVertexBindingDivisor ( glVertexBindingDivisor_hook_t hook ){
    glVertexBindingDivisor_hook = hook;
}
void glVertexBindingDivisor ( GLuint bindingindex_, GLuint divisor_ ){
    static PFNGLVERTEXBINDINGDIVISORPROC F;
    if(!F)
        F = ( PFNGLVERTEXBINDINGDIVISORPROC ) mygetprocaddr("glVertexBindingDivisor");
    if( glVertexBindingDivisor_hook )
        glVertexBindingDivisor_hook( bindingindex_, divisor_ );
    F(bindingindex_, divisor_);
}
static glViewport_hook_t glViewport_hook = 0;
glViewport_hook_t getHook_glViewport (){
    return glViewport_hook ;
}
void setHook_glViewport ( glViewport_hook_t hook ){
    glViewport_hook = hook;
}
void glViewport ( GLint x_, GLint y_, GLsizei width_, GLsizei height_ ){
    static PFNGLVIEWPORTPROC F;
    if(!F)
        F = ( PFNGLVIEWPORTPROC ) mygetprocaddr("glViewport");
    if( glViewport_hook )
        glViewport_hook( x_, y_, width_, height_ );
    F(x_, y_, width_, height_);
}
static glViewportArrayv_hook_t glViewportArrayv_hook = 0;
glViewportArrayv_hook_t getHook_glViewportArrayv (){
    return glViewportArrayv_hook ;
}
void setHook_glViewportArrayv ( glViewportArrayv_hook_t hook ){
    glViewportArrayv_hook = hook;
}
void glViewportArrayv ( GLuint first_, GLsizei count_, const GLfloat * v_ ){
    static PFNGLVIEWPORTARRAYVPROC F;
    if(!F)
        F = ( PFNGLVIEWPORTARRAYVPROC ) mygetprocaddr("glViewportArrayv");
    if( glViewportArrayv_hook )
        glViewportArrayv_hook( first_, count_, v_ );
    F(first_, count_, v_);
}
static glViewportIndexedf_hook_t glViewportIndexedf_hook = 0;
glViewportIndexedf_hook_t getHook_glViewportIndexedf (){
    return glViewportIndexedf_hook ;
}
void setHook_glViewportIndexedf ( glViewportIndexedf_hook_t hook ){
    glViewportIndexedf_hook = hook;
}
void glViewportIndexedf ( GLuint index_, GLfloat x_, GLfloat y_, GLfloat w_, GLfloat h_ ){
    static PFNGLVIEWPORTINDEXEDFPROC F;
    if(!F)
        F = ( PFNGLVIEWPORTINDEXEDFPROC ) mygetprocaddr("glViewportIndexedf");
    if( glViewportIndexedf_hook )
        glViewportIndexedf_hook( index_, x_, y_, w_, h_ );
    F(index_, x_, y_, w_, h_);
}
static glViewportIndexedfv_hook_t glViewportIndexedfv_hook = 0;
glViewportIndexedfv_hook_t getHook_glViewportIndexedfv (){
    return glViewportIndexedfv_hook ;
}
void setHook_glViewportIndexedfv ( glViewportIndexedfv_hook_t hook ){
    glViewportIndexedfv_hook = hook;
}
void glViewportIndexedfv ( GLuint index_, const GLfloat * v_ ){
    static PFNGLVIEWPORTINDEXEDFVPROC F;
    if(!F)
        F = ( PFNGLVIEWPORTINDEXEDFVPROC ) mygetprocaddr("glViewportIndexedfv");
    if( glViewportIndexedfv_hook )
        glViewportIndexedfv_hook( index_, v_ );
    F(index_, v_);
}
static glWaitSync_hook_t glWaitSync_hook = 0;
glWaitSync_hook_t getHook_glWaitSync (){
    return glWaitSync_hook ;
}
void setHook_glWaitSync ( glWaitSync_hook_t hook ){
    glWaitSync_hook = hook;
}
void glWaitSync ( GLsync sync_, GLbitfield flags_, GLuint64 timeout_ ){
    static PFNGLWAITSYNCPROC F;
    if(!F)
        F = ( PFNGLWAITSYNCPROC ) mygetprocaddr("glWaitSync");
    if( glWaitSync_hook )
        glWaitSync_hook( sync_, flags_, timeout_ );
    F(sync_, flags_, timeout_);
}
