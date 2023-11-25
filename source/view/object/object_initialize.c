#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_view_object_initialize(
        yc_vid_view_object_t *object,
        yc_res_pro_object_type_t type,
        uint16_t sprite_idx,
        const yc_vid_renderer_t *renderer
) {
    if (NULL == object) { return YC_VID_STATUS_INPUT; }
    if (NULL == renderer) { return YC_VID_STATUS_INPUT; }

    // Initialize empty state.
    object->current.texture = NULL;
    object->current.frame_idx = 0;

    for (yc_res_math_orientation_t orientation = 0; orientation < YC_RES_MATH_ORIENTATION_COUNT; ++orientation) {
        yc_vid_texture_set_t *set = &object->sets[orientation];

        yc_vid_status_t status = renderer->texture->initialize(
                type, sprite_idx, orientation, set, renderer->context
        );

        if (YC_VID_STATUS_OK != status) {
            yc_vid_view_object_invalidate(object, renderer);
            return status;
        }
    }

    return YC_VID_STATUS_OK;
}

yc_vid_status_t yc_vid_view_objects_initialize(
        yc_vid_view_objects_t *objects,
        yc_res_map_level_tiles_t *tiles,
        const yc_vid_renderer_t *renderer
) {
    size_t count = (size_t) (YC_RES_MATH_GRID_SIZE_TILES) * (size_t) YC_RES_MATH_GRID_SIZE_TILES;

    objects->pointers = malloc(sizeof(yc_vid_view_object_t) * count);
    if (NULL == objects->pointers) { return YC_VID_STATUS_MEM; }

    for (size_t vertical_idx = 0; vertical_idx < YC_RES_MATH_GRID_SIZE_TILES; ++vertical_idx) {
        for (size_t horizontal_idx = 0; horizontal_idx < YC_RES_MATH_GRID_SIZE_TILES; ++horizontal_idx) {
            uint16_t sprite_idx = tiles->idxes[vertical_idx][horizontal_idx];

            size_t linear_idx = horizontal_idx + vertical_idx * YC_RES_MATH_GRID_SIZE_TILES;
            yc_vid_view_object_t *object = &objects->pointers[linear_idx];

            yc_vid_status_t status = yc_vid_view_object_initialize(
                    object,
                    YC_RES_PRO_OBJECT_TYPE_TILE,
                    sprite_idx,
                    renderer
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
