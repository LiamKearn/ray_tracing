#include "camera.h"

Camera new_camera(double aspect_ratio, double viewport_height,
                  double focal_length) {
    Camera cam = {
        .aspect_ratio = aspect_ratio,
        .viewport_height = viewport_height,
        .focal_length = focal_length,
        .viewport_width = viewport_height * aspect_ratio,
        .origin = {},
        .vertical = {.y = viewport_height},
    };

    cam.horizontal = (Point3){.x = cam.viewport_width};

    // auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0,
    // focal_length);
    Point3 lower_left_corner = cam.origin;
    Point3 h = Point3_cpy_op_divide(cam.horizontal, 2);
    Point3 v = Point3_cpy_op_divide(cam.vertical, 2);
    Point3_i_subtract(&lower_left_corner, &h);
    Point3_i_subtract(&lower_left_corner, &v);
    Point3 x = {.z = focal_length};
    Point3_i_subtract(&lower_left_corner, &x);
    cam.lower_left_corner = lower_left_corner;

    return cam;
}

Ray camera_ray_for_vertical_horizontal_offsets(const Camera *cam, double u,
                                               double v) {
    Ray ray = {
        .origin = cam->origin,
    };

    Point3 uh = Point3_cpy_op_multiply(cam->horizontal, u);
    Point3 vv = Point3_cpy_op_multiply(cam->vertical, v);
    Point3 temp = Point3_add(&uh, &vv);
    Point3 far = Point3_add(&cam->lower_left_corner, &temp);
    ray.direction = Point3_subtract(&far, &cam->origin);

    return ray;
}
