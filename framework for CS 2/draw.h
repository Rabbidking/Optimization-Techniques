void draw() {
	//bind buffer here
	globs->cs.use();
	globs->scene.camera.setUniforms();
	Program::updateUniforms();
	globs->fbo->texture->bindImage(0);
	globs->tri->bindBase(GL_SHADER_STORAGE_BUFFER, 1);	//bind triangle buffer
	globs->cs.dispatch(globs->fbo->w / 64, globs->fbo->h, 1);
	globs->fbo->texture->unbindImage(0);
	glMemoryBarrier(GL_ALL_BARRIER_BITS);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, globs->fbo->fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, globs->fbo->w, globs->fbo->h,
		0, 0, globs->fbo->w, globs->fbo->h,
		GL_COLOR_BUFFER_BIT,
		GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}