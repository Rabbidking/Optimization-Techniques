#pragma once
#include "Sphere.h"
#include "math3d.h"
#include "Triangle.h"

void traceSpheres(Scene& scene, vec3& s, vec3& v, vec3& ip, vec3& N, vec3& color, float& closestT, bool& inter)
{
    unsigned ci=(unsigned)-1;
    for(unsigned i=0;i<scene.spheres.size();++i)
    {
        Sphere sph = scene.spheres[i];
        vec3 q = s - sph.c;
		float t;

        float A = dot(v, v);
        float B = 2 * dot(q, v);
        float C = dot(q, q) - pow(sph.r, 2);

        float t1 = (-B + sqrt(pow(B, 2) - 4 * A * C)) / (2 * A);
        float t2 = (-B - sqrt(pow(B, 2) - 4 * A * C)) / (2 * A);

		if ((pow(B, 2) - 4 * A * C) < 0)
			//discriminant is 0
			continue;
        if(t1 < 0 && t2 < 0)
            //no intersection
			continue;
        else if(t1 < 0 && t2 >= 0)
            t = t2;
        else if(t1 >= 0 && t2 < 0)
            t = t1;
        else if(t1 >= 0 && t2 >= 0)
            t = fmin(t1, t2);

		if (t <= closestT)
		{
			closestT = t;
			ci = i;
		}
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

void traceTriangles(Scene& scene, vec3& s, vec3& v, vec3& ip, vec3& N, vec3& color, float& closestT, bool& inter)
{

    for(auto& M : scene.meshes )
	{
        for(unsigned i=0;i<M.triangles.size();++i)
		{
            Triangle& T = M.triangles[i];
			
			//Find Triangles in Scene
			if (dot(T.N, v) == 0)
			{
				//no intersection
				continue;
			}

			float t = -(T.D + dot(T.N, s)) / dot(T.N, v);
			vec3 tmp_ip = s + t * v;
			
			//Barycentric coordinates
			vec3 q[3];
			float sum = 0.0;
			for (int i = 0; i < 3; i++)
			{
				q[i] = cross(T.e[i], (tmp_ip - T.p[i]));
			}
			sum = q[0].magnitude() + q[1].magnitude() + q[2].magnitude();
			float A = sum * T.oneOverTwiceArea;
			if (A <= 1.001)
			{
				//intersection
				if (t <= closestT)
				{
					inter = true;
					color = M.color;
					N = T.N;
					closestT = t;
					ip = tmp_ip;
				}
			}
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
