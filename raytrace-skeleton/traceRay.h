#pragma once


void traceSpheres(Scene& scene, vec3& s, vec3& v, vec3& ip, vec3& N, vec3& color, float& closestT, bool& inter)
{
    unsigned ci=(unsigned)-1;
    for(unsigned i=0;i<scene.spheres.size();++i){
    }
    
    if( ci == (unsigned)-1 ){
        inter=false;
        return;
    }
    ip = s + closestT * v;
    N = normalize(ip - scene.spheres[ci].c);
    color = scene.spheres[ci].color;
    inter=true;
}

void traceTriangles(Scene& scene, vec3& s, vec3& v, vec3& ip, vec3& N, 
            vec3& color, float& closestT, bool& inter)
{
    for(auto& M : scene.meshes ){
        for(unsigned i=0;i<M.triangles.size();++i){
            Triangle& T = M.triangles[i];
        }
    }
}

bool traceRay(Scene& scene, vec3& s, vec3& v, vec3& ip, vec3& N, vec3& color)
{
    float closestT = 1E99;
    bool inter;
    traceSpheres(scene,s,v,ip,N,color,closestT,inter);
    traceTriangles(scene,s,v,ip,N,color,closestT,inter);
    return inter;
}
