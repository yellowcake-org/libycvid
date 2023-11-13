#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_view_object_initialize(
        yc_vid_view_object_t *object,
        yc_res_pro_object_type_t type,
        const yc_vid_renderer_t *renderer,
        uint16_t sprite_idx
) {
    if (NULL == object) { return YC_VID_STATUS_INPUT; }
    if (NULL == renderer) { return YC_VID_STATUS_INPUT; }
    if (YC_RES_PRO_OBJECT_TYPE_COUNT >= type) { return YC_VID_STATUS_INPUT; }

    yc_vid_status_t status = YC_VID_STATUS_OK;

    // TODO: We need some 'loader' implemented on the platform,
    //  which loads particular type of sprite and provides a palette for it.

    yc_res_pal_parse_result_t palette = { .count = 0, .colors = NULL };
    if (NULL == palette.colors) { return YC_VID_STATUS_CORRUPTED; }

    yc_res_frm_sprite_parse_result_t parsed = { .sprite = NULL };
    if (NULL == parsed.sprite) { return YC_VID_STATUS_CORRUPTED; }

    // Copy orientations table.
    for (size_t orientation_idx = 0; orientation_idx < YC_RES_MATH_ORIENTATION_COUNT; ++orientation_idx) {
        object->orientations[orientation_idx] = parsed.sprite->orientations[orientation_idx];
    }

    // Initialize count and malloc sets' list.
    object->count = parsed.sprite->count;
    object->sets = malloc(sizeof(yc_vid_texture_set_t) * object->count);

    if (NULL == object->sets) {
        status = YC_VID_STATUS_MEM;

        yc_vid_view_object_invalidate(object, renderer);
        goto cleanup_and_return;
    }

    for (size_t pair_idx = 0; pair_idx < object->count; ++pair_idx) {
        yc_vid_texture_set_t *set = &object->sets[pair_idx];
        yc_res_frm_animation_t *animation = &parsed.sprite->animations[pair_idx];

        status = yc_vid_texture_set_initialize(set, animation, &palette, renderer);

        if (YC_VID_STATUS_OK != status) {
            yc_vid_view_object_invalidate(object, renderer);
            goto cleanup_and_return;
        }
    }

    cleanup_and_return:

    palette.count = 0;
    free(palette.colors);
    palette.colors = NULL;

    yc_res_frm_sprite_invalidate(parsed.sprite);
    free(parsed.sprite);
    parsed.sprite = NULL;

    return status;
}

yc_vid_status_t yc_vid_view_objects_initialize(
        yc_vid_view_objects_t *objects, yc_res_map_level_tiles_t *tiles, const yc_vid_renderer_t *renderer
) {
    size_t count = (size_t) (YC_RES_MATH_GRID_SIZE_TILES) * (size_t) YC_RES_MATH_GRID_SIZE_TILES;

    objects->pointers = malloc(sizeof(yc_vid_view_object_t) * count);
    if (NULL == objects->pointers) { return YC_VID_STATUS_MEM; }

    for (size_t horizontal_idx = 0; horizontal_idx < YC_RES_MATH_GRID_SIZE_TILES; ++horizontal_idx) {
        for (size_t vertical_idx = 0; vertical_idx < YC_RES_MATH_GRID_SIZE_TILES; ++vertical_idx) {
            yc_vid_view_object_t *object = &objects->pointers[horizontal_idx * vertical_idx];
            uint16_t sprite_idx = tiles->idxes[horizontal_idx][vertical_idx];

            yc_vid_status_t status = yc_vid_view_object_initialize(
                    object, YC_RES_PRO_OBJECT_TYPE_TILE, renderer, sprite_idx
            );

            if (YC_VID_STATUS_OK != status) {
                yc_vid_view_objects_invalidate(objects, renderer);
                return status;
            }
        }
    }

    objects->count = count;
    return YC_VID_STATUS_OK;
}
