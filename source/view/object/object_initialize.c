#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_view_object_initialize_from_tile(
        yc_vid_view_object_t *object,
        uint16_t sprite_idx,
        int32_t horizontal_idx,
        int32_t vertical_idx,
        bool is_roof,
        const yc_vid_renderer_t *renderer
) {
    if (NULL == object) { return YC_VID_STATUS_INPUT; }
    if (NULL == renderer) { return YC_VID_STATUS_INPUT; }

    // Initialize empty state.
    object->current.texture = NULL;
    object->current.frame_idx = 0;

    // Coordinates and orientation.
    object->current.correction_x = 0;
    object->current.correction_y = 0;

    object->current.orientation = YC_RES_MATH_ORIENTATION_NE;

    object->current.vertical_idx = vertical_idx;
    object->current.horizontal_idx = horizontal_idx;

    // Set up correct order.
    object->order = is_roof ? YC_VID_TEXTURE_ORDER_ROOF : YC_VID_TEXTURE_ORDER_FLOOR;

    for (yc_res_math_orientation_t orientation = 0; orientation < YC_RES_MATH_ORIENTATION_COUNT; ++orientation) {
        yc_vid_texture_set_t *set = &object->sets[orientation];

        yc_vid_status_t status = renderer->texture->initialize(
                yc_res_pro_fid_from(sprite_idx, YC_RES_PRO_OBJECT_TYPE_TILE), orientation, set, renderer->context
        );

        if (YC_VID_STATUS_OK != status) {
            yc_vid_view_object_invalidate(object, renderer);
            return status;
        }
    }

    return YC_VID_STATUS_OK;
}

yc_vid_status_t yc_vid_view_objects_initialize_from_tiles(
        yc_vid_view_objects_t *objects,
        yc_res_map_level_tiles_t *tiles,
        bool is_roof,
        const yc_vid_renderer_t *renderer
) {
    size_t count = (size_t) (YC_RES_MATH_GRID_SIZE_TILES) * (size_t) YC_RES_MATH_GRID_SIZE_TILES;

    objects->pointers = malloc(sizeof(yc_vid_view_object_t) * count);
    if (NULL == objects->pointers) { return YC_VID_STATUS_MEM; }

    for (int32_t vertical_idx = 0; vertical_idx < YC_RES_MATH_GRID_SIZE_TILES; ++vertical_idx) {
        for (int32_t horizontal_idx = 0; horizontal_idx < YC_RES_MATH_GRID_SIZE_TILES; ++horizontal_idx) {
            uint16_t sprite_idx = tiles->idxes[vertical_idx][horizontal_idx];

            size_t linear_idx = horizontal_idx + vertical_idx * YC_RES_MATH_GRID_SIZE_TILES;
            yc_vid_view_object_t *object = &objects->pointers[linear_idx];

            yc_vid_status_t status = yc_vid_view_object_initialize_from_tile(
                    object,
                    sprite_idx,
                    horizontal_idx,
                    vertical_idx,
                    is_roof,
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

yc_vid_status_t yc_vid_view_object_initialize_from_object(
        yc_vid_view_object_t *video_object,
        yc_res_map_level_object_t *level_object,
        const yc_vid_renderer_t *renderer
) {
    if (NULL == renderer) { return YC_VID_STATUS_INPUT; }

    if (NULL == video_object) { return YC_VID_STATUS_INPUT; }
    if (NULL == level_object) { return YC_VID_STATUS_INPUT; }

    // Initialize empty state.
    video_object->current.texture = NULL;
    video_object->current.frame_idx = 0;

    // Coordinates and orientation.
    video_object->current.correction_x = level_object->correction_x;
    video_object->current.correction_y = level_object->correction_y;

    video_object->current.orientation = level_object->location.orientation_idx;

    video_object->current.vertical_idx =
            level_object->location.grid_idx / YC_RES_MATH_GRID_SIZE_HEXES;
    video_object->current.horizontal_idx =
            (YC_RES_MATH_GRID_SIZE_HEXES - 1) - (level_object->location.grid_idx % YC_RES_MATH_GRID_SIZE_HEXES);

    // Set up correct order.
    video_object->order =
            level_object->flags.is_flat ?
            YC_VID_TEXTURE_ORDER_FLAT :
            yc_vid_texture_order_from_object_type(yc_res_pro_object_type_from_pid(level_object->proto_id));

    for (yc_res_math_orientation_t orientation = 0; orientation < YC_RES_MATH_ORIENTATION_COUNT; ++orientation) {
        yc_vid_texture_set_t *set = &video_object->sets[orientation];

        yc_vid_status_t status = renderer->texture->initialize(
                level_object->sprite_id,
                orientation,
                set,
                renderer->context
        );

        if (YC_VID_STATUS_OK != status) {
            yc_vid_view_object_invalidate(video_object, renderer);
            return status;
        }
    }

    return YC_VID_STATUS_OK;
}

yc_vid_status_t yc_vid_view_objects_initialize_from_objects(
        yc_vid_view_objects_t *view_objects,
        yc_res_map_level_objects_t *level_objects,
        const yc_vid_renderer_t *renderer
) {
    view_objects->pointers = malloc(sizeof(yc_vid_view_object_t) * level_objects->count);
    if (NULL == view_objects->pointers) { return YC_VID_STATUS_MEM; }

    for (size_t index = 0; index < level_objects->count; ++index) {
        yc_vid_status_t status = yc_vid_view_object_initialize_from_object(
                &view_objects->pointers[index], &level_objects->pointers[index], renderer
        );

        if (YC_VID_STATUS_OK != status) { return status; }
    }

    view_objects->count = level_objects->count;
    return YC_VID_STATUS_OK;
}
