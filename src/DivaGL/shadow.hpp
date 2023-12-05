/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../KKdLib/default.hpp"
#include "../KKdLib/time.hpp"
#include "../KKdLib/vec.hpp"
#include "render_texture.hpp"
#include "shared.hpp"
#include "types.hpp"

enum shadow_type_enum {
    SHADOW_CHARA = 0,
    SHADOW_STAGE,
    SHADOW_MAX,
};

struct Shadow {
    void* __vftable;
    RenderTexture render_textures[7];
    RenderTexture* curr_render_textures[3];
    float_t view_region;
    float_t range;
    vec3 view_point[2];
    vec3 interest[2];
    vec3 field_1A8[2];
    float_t field_1C0[2];
    float_t field_1C8[2];
    prj::vector<vec3> field_1D0[2];
    int32_t field_200[2];
    float_t field_208;
    vec3 direction;
    vec3 view_point_shared;
    vec3 interest_shared;
    mat4 view_mat[2];
    int32_t near_blur;
    blur_filter_mode blur_filter;
    int32_t far_blur;
    int32_t field_2BC;
    float_t distance;
    float_t field_2C4;
    float_t z_near;
    float_t z_far;
    float_t field_2D0;
    float_t field_2D4;
    float_t field_2D8;
    float_t field_2DC;
    float_t field_2E0;
    float_t ambient;
    bool field_2E8;
    int32_t field_2EC;
    bool field_2F0[2];
    bool self_shadow;
    bool blur_filter_enable[2];
    bool field_2F5;
};

static_assert(sizeof(Shadow) == 0x2F8, "\"Shadow\" struct should have a size of 0x2F8");

extern Shadow* shadow_ptr_get();
