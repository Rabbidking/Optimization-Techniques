


//Note: Must link with windowscodecs.lib (Windows) or libturbojpeg, libpng, and libz (Linux)


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include "Mesh.h"
#include "Camera.h"
#include "Image.h"
#include "Scene.h"
#include "traceRay.h"

bool traceRay(Scene& scene, vec3& rayStart, vec3& rayDir, vec3& ip, vec3& N, vec3& color);

vec3 reflect(vec3 a, vec3 b){
    float dp = dot(a,b);
    vec3 c = dp*b;
    return c+c-a;
}

vec3 shadePixel( Scene& scene, vec3& ip, vec3& N, vec3& color ){
    vec3 L = normalize( scene.lightPosition-ip );
    float dp = dot(L,N);
    float sp;
    if( dp < 0 ){ 
        dp = 0.0;
        sp=0.0;
    } else {
        vec3 V = normalize(scene.camera.eye - ip);
        vec3 R = reflect( L,N );
        sp = dot(V,R);
        if( sp < 0 )
            sp = 0.0;
        sp = pow(sp, 16.0 );
    }
    return dp * color + vec3(sp,sp,sp);
}
    
void raytrace(Scene& scene, std::vector<std::vector<vec3>>& pic){
    unsigned w = pic[0].size();
    unsigned h = pic.size();
    float d = 1.0 / tan(scene.camera.fov_radians);
    float dy = 2.0/(h-1);
    float dx = 2.0/(w-1);
    float y=1.0;
    for(unsigned yi=0;yi<h;++yi,y-=dy){
    	std::cout << yi << " ";
    	if( ( (yi+1) % 20) == 0 )
    		std::cout << "\n";
    	std::cout.flush();
        float x=-1.0;
        for(unsigned xi=0;xi<w;++xi,x+=dx){
            vec3 rayDir = x*scene.camera.right + y*scene.camera.up + d*scene.camera.look;
            bool wasIntersection;
            vec3 ip;
            vec3 N;
            vec3 color;
            wasIntersection = traceRay(scene,scene.camera.eye,rayDir, ip, N, color);
            if( !wasIntersection )
                pic[yi][xi] = vec3(0.0,0.0,0.0);
            else
                pic[yi][xi] = shadePixel( scene, ip,N,color );
        }
    }
    std::cout << "\n";
}

uint8_t colorconvert(float f){
    if( f<0 )
        return 0;
    if( f>1 )
        return 255;
    return (uint8_t)(f*255);
}
int main(int argc, char* argv[])
{
    using namespace std;
    int width=512;
    int height=width;

    if( argc == 1 ){
        std::cout << "Need command line argument: Scene file\n";
        return 1;
    }
    
    Scene scene(argv[1]);

    vector<vector<vec3>> picdata;
    picdata.resize(height);
    for(int i=0;i<height;++i){
        picdata[i].resize(width);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    raytrace(scene,picdata);
    auto end = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration<double>(end-start).count();
    std::cout << delta << " seconds\n";
    Image img(width,height,"RGB8");
    uint8_t* pix = (uint8_t*) img.pixels();
    for(int y=0;y<height;++y){
        for(int x=0;x<width;++x){
            *pix++ = colorconvert(picdata[y][x].x); //red
            *pix++ = colorconvert(picdata[y][x].y); //green
            *pix++ = colorconvert(picdata[y][x].z); //blue
        }
    }
    img.writePng("out.png");
    return 0;
}
 
