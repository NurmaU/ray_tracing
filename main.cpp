#include <fstream>
#include <iostream>
#include <string>

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "rtweekend.h"
#include "sphere.h"

using std::ofstream;

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if (depth == 0) return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

hittable_list random_scene() {
    hittable_list world;
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(
        make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(
        make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(
        make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
    return world;
}

void render(int image_width, int image_height, int samples_per_pixel,
            camera& cam, const hittable_list& world, int max_depth, int index) {
    ofstream file;
    file.open("./output/file_" + std::to_string(index) + ".ppm");

    file << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = double(i + random_double()) / (image_width - 1);
                auto v = double(j + random_double()) / (image_height - 1);

                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(file, pixel_color, samples_per_pixel);
        }
    }

    file.close();
}

int create_image() {
    // Image
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 200;
    const int max_depth = 10;

    // Camera
    point3 lookfrom(3, 1, 2);
    point3 lookat(0, 0, -1);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 1.0;
    auto aperture = 0.0;

    // World
    hittable_list world = random_scene();

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture,
               dist_to_focus);
    int index = 0;
    render(image_width, image_height, samples_per_pixel, cam, world, max_depth,
           index);

    std::cerr << "\nDone\n";

    return 1;
}

int main() {
    create_image();
    return 1;
}
