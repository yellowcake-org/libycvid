#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_texture_set_initialize(
        yc_vid_texture_set_t *set,
        const yc_res_frm_animation_t *animation,
        yc_res_pal_parse_result_t *palette,
        const yc_vid_renderer_t *renderer
) {
    set->fps = animation->fps;
    set->keyframe_idx = animation->keyframe_idx;

    set->count = animation->count;
    set->textures = malloc(sizeof(yc_vid_texture_t) * set->count);

    if (NULL == set->textures) {
        yc_vid_texture_set_invalidate(set, renderer);
        return YC_VID_STATUS_MEM;
    }

    for (size_t pair_idx = 0; pair_idx < set->count; ++pair_idx) {
        yc_res_frm_texture_t *blueprint = &animation->frames[pair_idx];
        yc_vid_texture_t *result = &set->textures[pair_idx];

        yc_vid_texture_data_t data = {
                .shift = blueprint->shift,
                .dimensions = {
                        .horizontal = blueprint->dimensions.horizontal,
                        .vertical = blueprint->dimensions.vertical
                },
                .pixels = NULL
        };

        data.pixels = malloc(
                sizeof(yc_res_pal_color_t) *
                blueprint->dimensions.horizontal *
                blueprint->dimensions.vertical
        );

        if (NULL == data.pixels) {
            yc_vid_texture_set_invalidate(set, renderer);
            return YC_VID_STATUS_MEM;
        }

        for (size_t horizontal_idx = 0; horizontal_idx < data.dimensions.horizontal; ++horizontal_idx) {
            for (size_t vertical_idx = 0; vertical_idx < data.dimensions.vertical; ++vertical_idx) {
                size_t linear_idx = horizontal_idx * vertical_idx;

                yc_res_pal_color_t *source = &(*palette).colors[blueprint->pixels[linear_idx]];
                yc_res_pal_color_t *destination = &data.pixels[linear_idx];

                destination->r = source->r;
                destination->g = source->g;
                destination->b = source->b;
            }
        }

        yc_vid_status_t status = renderer->texture->initialize(&data, result);

        free(data.pixels);
        data.pixels = NULL;

        if (YC_VID_STATUS_OK != status) {
            yc_vid_texture_set_invalidate(set, renderer);
            return status;
        }
    }

    return YC_VID_STATUS_OK;
}
