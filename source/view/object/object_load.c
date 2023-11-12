#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_view_object_load(
        yc_vid_view_object_t *object,
        const yc_vid_renderer_t *renderer,
        yc_res_pro_object_type_t type,
        uint16_t sprite_idx
) {
    // TODO: Input validation!

    // TODO: We need some 'loader' implemented on the platform,
    //  which loads particular type of sprite.

    return YC_VID_STATUS_OK;
}

yc_vid_status_t yc_vid_view_objects_load_from_tiles(
        yc_vid_view_objects_t *objects,
        yc_res_map_level_tiles_t *tiles,
        const yc_vid_renderer_t *renderer
) {
    size_t count = (size_t) (YC_RES_MATH_GRID_SIZE_TILES) * (size_t) YC_RES_MATH_GRID_SIZE_TILES;

    objects->pointers = malloc(sizeof(yc_vid_view_object_t) * count);
    if (NULL == objects->pointers) { return YC_VID_STATUS_MEM; }

    for (size_t horizontal_idx = 0; horizontal_idx < YC_RES_MATH_GRID_SIZE_TILES; ++horizontal_idx) {
        for (size_t vertical_idx = 0; vertical_idx < YC_RES_MATH_GRID_SIZE_TILES; ++vertical_idx) {
            yc_vid_view_object_t *object = &objects->pointers[horizontal_idx * vertical_idx];
            uint16_t sprite_idx = tiles->idxes[horizontal_idx][vertical_idx];

            yc_vid_status_t status = yc_vid_view_object_load(
                    object, renderer, YC_RES_PRO_OBJECT_TYPE_TILE, sprite_idx
            );

            if (YC_VID_STATUS_OK != status) {
                yc_vid_view_objects_destroy(objects, renderer);
                return status;
            }
        }
    }

    objects->count = count;
    return YC_VID_STATUS_OK;
}
