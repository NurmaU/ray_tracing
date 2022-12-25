#include <iostream>
#include "vec3.h"

int create_image(){
    // Image
    const int image_width = 256;
    const int image_height = 256;

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i){
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);
            std::cout << ir << " " << ig << " " << ib << '\n';
        }
    }

    std::cerr << "\nDone\n";

    return 1;
}

int main(){
    // create_image();
    vec3 v1(1,2,3), v2(0, 1, 2);
    // std::cout << (-v1).length_squared() << std::endl;
    std::cout << unit_vector(v1).length_squared() << std::endl; 
    return 1;
}
