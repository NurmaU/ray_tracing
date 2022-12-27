#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
   private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

   public:
    camera(double vfov, double aspect_ratio) {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = viewport_height * aspect_ratio;
        auto focal_length = 1.0;

        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        lower_left_corner =
            origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
    }

    ray get_ray(double u, double v) {
        return ray(origin,
                   lower_left_corner + u * horizontal + v * vertical - origin);
    }
};

#endif