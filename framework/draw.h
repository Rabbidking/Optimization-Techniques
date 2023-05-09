
void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    Program::setUniform("lightPosition",  globs->scene.lightPosition);
    Program::setUniform("lightColor", vec3(1,1,1));
    globs->scene.camera.setUniforms();
    globs->mainProg.use();
	glPatchParameteri(GL_PATCH_VERTICES, 3);
    Program::setUniform("worldMatrix",mat4::identity());
    globs->heightmap.bind(1);
    for(auto& M : globs->scene.meshes ){
        M.draw();
    }
    globs->text1.draw();
    globs->text2.draw();
}

