/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#include "camera.hpp"
#include "render.hpp"
#include "resolution_mode.hpp"
#include <Helpers.h>

camera_struct* camera_data = (camera_struct*)0x0000000140FBC2C0;

static void (FASTCALL* camera_struct__update_view)(camera_struct* cam)
    = (void (FASTCALL*)(camera_struct * cam))0x00000001401F7690;

HOOK(void, FASTCALL, camera_data_update_projection, 0x00000001401F8E90) {
    resolution_struct* res_wind_int = res_window_internal_get();
    resolution_struct* res_wind = res_window_get();

    float_t sprite_half_width = (float_t)res_wind->width * 0.5f;
    float_t sprite_half_height = (float_t)res_wind->height * 0.5f;
    float_t render_half_width = (float_t)res_wind_int->width * 0.5f;
    float_t render_half_height = (float_t)res_wind_int->height * 0.5f;

    static float_t field_20 = tanf(atanf(tanf(0.34557518363f) * 0.75f));

    float_t aet_depth = sprite_half_height / field_20;
    camera_data->aet_depth = aet_depth;

    float_t fov_correct_height = sprite_half_height / tanf(camera_data->fov * 0.5f * DEG_TO_RAD_FLOAT);
    camera_data->fov_correct_height = fov_correct_height;

    float_t v8 = (float_t)camera_data->min_distance / aet_depth;
    float_t v8a = v8 * sprite_half_width;
    float_t v8b = v8 * sprite_half_height;

    mat4 spr_2d_proj;
    mat4_frustrum(-v8a, v8a, v8b, -v8b, camera_data->min_distance, 3000.0, &spr_2d_proj);

    vec3 spr_2d_viewpoint = { sprite_half_width, sprite_half_height, aet_depth };
    vec3 spr_2d_interest = { sprite_half_width, sprite_half_height, 0.0f };
    vec3 spr_2d_up = { 0.0f, 1.0f, 0.0f };
    mat4 spr_2d_view;
    mat4_look_at(&spr_2d_viewpoint, &spr_2d_interest, &spr_2d_up, &spr_2d_view);

    mat4_mul(&spr_2d_view, &spr_2d_proj, &camera_data->view_projection_aet_2d_matrix);
    mat4_transpose(&camera_data->view_projection_aet_2d_matrix,
        &camera_data->view_projection_aet_2d_matrix);

    float_t v13c = render_half_height / tanf(camera_data->fov * 0.5f * DEG_TO_RAD_FLOAT);

    float_t v13 = (float_t)camera_data->min_distance / v13c;
    float_t v13a = v13 * render_half_width;
    float_t v13b = v13 * render_half_height;

    mat4 spr_3d_proj;
    mat4_frustrum(-v13a, v13a, v13b, -v13b, camera_data->min_distance, 3000.0, &spr_3d_proj);

    vec3 spr_3d_viewpoint = { render_half_width, render_half_height, v13c };
    vec3 spr_3d_interest = { render_half_width, render_half_height, 0.0f };
    vec3 spr_3d_up = { 0.0f, 1.0f, 0.0f };
    mat4 spr_3d_view;
    mat4_look_at(&spr_3d_viewpoint, &spr_3d_interest, &spr_3d_up, &spr_3d_view);

    mat4_mul(&spr_3d_view, &spr_3d_proj, &camera_data->view_projection_aet_3d_matrix);
    mat4_transpose(&camera_data->view_projection_aet_3d_matrix,
        &camera_data->view_projection_aet_3d_matrix);

    render->calc_projection_matrix(&camera_data->projection_matrix,
        camera_data->fov, camera_data->aspect, camera_data->min_distance, camera_data->max_distance,
        camera_data->projection_scale.x, camera_data->projection_scale.y,
        camera_data->projection_scale.z, camera_data->projection_scale.w);
    camera_data->fov_horizontal_rad = tanf(camera_data->fov * 0.5f * DEG_TO_RAD_FLOAT);
}

HOOK(void, FASTCALL, camera_update, 0x00000001401F8970) {
    implOfcamera_data_update_projection();
    camera_struct__update_view(camera_data);
    camera_data->fast_change_hist1 = camera_data->fast_change_hist0;
    camera_data->fast_change_hist0 = camera_data->fast_change;
    camera_data->fast_change = false;
}

void camera_struct::update_data() {
    implOfcamera_data_update_projection();
    camera_struct__update_view(camera_data);
}

void camera_patch() {
    INSTALL_HOOK(camera_data_update_projection);
    INSTALL_HOOK(camera_update);
}
