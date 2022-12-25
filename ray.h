#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
    public:
    point3 orig;
    vec3 dir;

    public:
    ray(){}
    ray(const point3& orig, const vec3& dir): orig(orig), dir(dir){}

    point3 origin() const {return orig;}
    vec3 direction() const {return dir;}

    point3 at(double t) const{return orig + t * dir;}
};

#endif
