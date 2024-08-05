#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "utils.h"
#include "vec3.h"

class camera {
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;

    void render(const hittable& world) {
        this->initialize();

        std::cout << "P3\n" << this->image_width << ' ' << this->image_height << "\n255\n";

        for (int j = 0; j < this->image_height; j++) {
            std::clog << "\rScanlines remaining: " << (this->image_height - j) << ' '
                      << std::flush;

            for (int i = 0; i < this->image_width; i++) {
                color pixel_color(0, 0, 0);

                for (int sample = 0; sample < this->samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, this->max_depth, world);
                }

                write_color(std::cout, this->pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                  \n";
    }

private:
    int image_height;
    double pixel_samples_scale;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void initialize() {
        // Calculate the image height and ensure that its at least 1
        this->image_height = int(this->image_width / this->aspect_ratio);
        this->image_height = (this->image_height < 1) ? 1 : this->image_height;

        this->pixel_samples_scale = 1.0 / this->samples_per_pixel;

        center = point3(0.0, 0.0, 0.0);

        // Camera
        // Viewport widths less than one are ok since they are real valued
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const {
        auto offset = this->sample_square();
        auto pixel_sample = this->pixel00_loc + ((i + offset.x()) * this->pixel_delta_u) +
                            ((j + offset.y()) * this->pixel_delta_v);

        auto ray_origin = this->center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const { return vec3(random_double() - 0.5, random_double() - 0.5, 0); }

    color ray_color(const ray& r, int depth, const hittable& world) {
        if (depth <= 0)
            return color(0, 0, 0);

        hit_record rec;

        if (world.hit(r, interval(0.001, infinity), rec)) {
            // vec3 direction = random_on_hemisphere(rec.normal);
            vec3 direction = rec.normal + random_unit_vector();
            return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif
