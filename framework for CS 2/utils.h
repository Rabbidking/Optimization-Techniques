#pragma once

#include "glfuncs.h"
#include <SDL.h>
#include "math3d.h"
#include <random>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <array>
#include <cmath>


//http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
inline
std::string trim(const std::string& s){
    std::string r = s;
    auto q = r.find_first_not_of(" \t\n\r");
    if( q != std::string::npos )
        r = r.substr(q);
    q = r.find_last_not_of(" \t\n\r");
    if( q != std::string::npos ){
        q++;
        r = r.substr(0,q);
    }
    return r;
}


inline
bool endswith(const std::string& s1, const std::string& s2){
    auto idx = s1.rfind(s2);
    if( idx != std::string::npos && idx == s1.length() - s2.length() )
        return true;
    else
        return false;
}

inline
float uniform(float min, float max){
    static std::minstd_rand engine(42);
    static std::uniform_real_distribution<float> distro;
    float t = distro(engine);
    return min + t * (max-min);
}

inline
float randrange(float min, float max){
    return uniform(min,max);
}


