#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include <iostream>

class sphere : public hittable {
private:
    point3 center;
    double radius;

public:
    sphere(const point3& center, double radius)
        : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        auto cq = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), cq);
        auto c = cq.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;

        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            auto root = (h + sqrtd) / a;

            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(root);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
};

#endif
