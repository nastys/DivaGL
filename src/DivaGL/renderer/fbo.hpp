/*
    by korenkonder
    GitHub/GitLab: korenkonder
*/

#pragma once

#include "../shared.hpp"

namespace renderer {
    struct FBO {
        enum Flags {
            DEPTH_ATTACHMENT = 0x01,
        };

        Flags flags;
        int32_t width;
        int32_t height;
        GLuint buffer;
        int32_t count;
        GLuint* textures;

        void init(int32_t width, int32_t height,
            GLuint* color_textures, int32_t count, GLuint depth_texture);
        void free();
    };

    static_assert(sizeof(renderer::FBO) == 0x20, "\"renderer::FBO\" struct should have a size of 0x20");
}
