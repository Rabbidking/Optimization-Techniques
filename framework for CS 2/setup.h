struct GPUSphere {
	alignas(16) vec4 centerAndRadius;
	alignas(16) vec4 color;
};

struct GPUTriangle {
	alignas(16) vec4 p[3];      //vertices
    alignas(16) vec4 e[3];      //edges: e[i] = p[i+1]-p[i]
    alignas(16) vec4 N;         //normal, unit length
    alignas(4) float D;	        //plane equation D
    alignas(4) float oneOverTwiceArea;	//1.0 / twice the triangle's area
	alignas(16) vec4 color;
};


void setup(int winwidth, int winheight)
{
    globs = std::make_unique<Globals>();
    globs->fbo = std::make_shared<Framebuffer>(winwidth,winheight,1,GL_RGBA);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.2f,0.4f,0.6f,1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    globs->mipsampler.bind(0);
    globs->linearsampler.bind(1);

	/*std::vector<GPUSphere> sphereData(globs->scene.spheres.size());
	for (unsigned i = 0; i < globs->scene.spheres.size(); ++i) {
		sphereData[i].centerAndRadius = vec4(
			globs->scene.spheres[i].c, globs->scene.spheres[i].r);
		sphereData[i].color = vec4(globs->scene.spheres[i].color, 1.0
		);
	}
	auto b = Buffer::create(sphereData);
	b->bindBase(GL_SHADER_STORAGE_BUFFER, 0);*/

	std::vector<GPUTriangle> triangleData(globs->scene.meshes[0].triangles.size());
	for(auto& m : globs->scene.meshes)
	{
		for (unsigned i = 0; i < globs->scene.meshes[0].triangles.size(); ++i) {
			triangleData[i].p[0] = vec4(globs->scene.meshes[0].triangles[i].p[0], 1.0);
			triangleData[i].p[1] = vec4(globs->scene.meshes[0].triangles[i].p[1], 1.0);
			triangleData[i].p[2] = vec4(globs->scene.meshes[0].triangles[i].p[2], 1.0);

			triangleData[i].e[0] = vec4(globs->scene.meshes[0].triangles[i].e[0], 1.0);
			triangleData[i].e[1] = vec4(globs->scene.meshes[0].triangles[i].e[1], 1.0);
			triangleData[i].e[2] = vec4(globs->scene.meshes[0].triangles[i].e[2], 1.0);

			triangleData[i].N = vec4(globs->scene.meshes[0].triangles[i].N, 1.0);
			triangleData[i].D = float(globs->scene.meshes[0].triangles[i].D);
			triangleData[i].oneOverTwiceArea = float(globs->scene.meshes[0].triangles[i].oneOverTwiceArea);
			triangleData[i].color = vec4(m.color, 1.0);
		}
	}
	auto b = Buffer::create(triangleData);
	globs->tri = b;

	Program::setUniform("lightPosition", globs->scene.lightPosition);
	Program::setUniform("lightColor", vec3(1, 1, 1));
}
