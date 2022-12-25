#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

double hit_sphere(const point3& center, double radius, const ray& r){
    vec3 oc = r.origin() - center;

    auto a = r.direction().length_squared();
    auto half_b = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0)
        return -1;
    return (-half_b - sqrt(discriminant))/(a);
}


color ray_color(const ray& r){
    point3 center = point3(0,0,-1);
    auto t = hit_sphere(center, 0.5, r);
    if (t > 0){
        vec3 N = unit_vector(r.at(t) - center);
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y()+1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int create_image(){
    // Image
    const auto aspect_ratio = 16.0/ 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto vieport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0,0,0);
    auto horizontal = vec3(vieport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i){
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone\n";

    return 1;
}

int main(){
    create_image();
    // vec3 v1(1,2,3), v2(0, 1, 2);
    // std::cout << (-v1).length_squared() << std::endl;
    // std::cout << unit_vector(v1).length_squared() << std::endl; 
    return 1;
}
