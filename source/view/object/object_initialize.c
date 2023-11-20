#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_view_object_initialize(
        yc_vid_view_object_t *object,
        const yc_vid_renderer_t *renderer,
        const yc_vid_database_fetch_resources_result_t *resources
) {
    if (NULL == object) { return YC_VID_STATUS_INPUT; }
    if (NULL == renderer) { return YC_VID_STATUS_INPUT; }
    if (NULL == resources) { return YC_VID_STATUS_INPUT; }

    if (NULL == resources->frm.sprite) { return YC_VID_STATUS_INPUT; }
    if (NULL == resources->pal.colors) { return YC_VID_STATUS_INPUT; }

    yc_vid_status_t status = YC_VID_STATUS_OK;

    // Initialize empty state.
    object->state.texture = NULL;
    object->state.frame_idx = 0;

    // Copy orientations table.
    for (size_t orientation_idx = 0; orientation_idx < YC_RES_MATH_ORIENTATION_COUNT; ++orientation_idx) {
        object->orientations[orientation_idx] = resources->frm.sprite->orientations[orientation_idx];
    }

    // Initialize count and malloc sets' list.
    object->count = resources->frm.sprite->count;
    object->sets = malloc(sizeof(yc_vid_texture_set_t) * object->count);

    if (NULL == object->sets) {
        status = YC_VID_STATUS_MEM;

        yc_vid_view_object_invalidate(object, renderer);
        goto cleanup_and_return;
    }

    for (size_t pair_idx = 0; pair_idx < object->count; ++pair_idx) {
        yc_vid_texture_set_t *set = &object->sets[pair_idx];
        yc_res_frm_animation_t *animation = &resources->frm.sprite->animations[pair_idx];

        status = yc_vid_texture_set_initialize(set, animation, &resources->pal, renderer);

        if (YC_VID_STATUS_OK != status) {
            yc_vid_view_object_invalidate(object, renderer);
            goto cleanup_and_return;
        }
    }

    cleanup_and_return:
    return status;
}

yc_vid_status_t yc_vid_view_objects_initialize(
        yc_vid_view_objects_t *objects,
        yc_res_map_level_tiles_t *tiles,
        const yc_vid_renderer_t *renderer,
        const yc_vid_database_api_t *database
) {
    size_t count = (size_t) (YC_RES_MATH_GRID_SIZE_TILES) * (size_t) YC_RES_MATH_GRID_SIZE_TILES;

    objects->pointers = malloc(sizeof(yc_vid_view_object_t) * count);
    if (NULL == objects->pointers) { return YC_VID_STATUS_MEM; }

    for (size_t vertical_idx = 0; vertical_idx < YC_RES_MATH_GRID_SIZE_TILES; ++vertical_idx) {
        for (size_t horizontal_idx = 0; horizontal_idx < YC_RES_MATH_GRID_SIZE_TILES; ++horizontal_idx) {
            uint16_t sprite_idx = tiles->idxes[vertical_idx][horizontal_idx];

            size_t linear_idx = horizontal_idx + vertical_idx * YC_RES_MATH_GRID_SIZE_TILES;
            yc_vid_view_object_t *object = &objects->pointers[linear_idx];

            yc_vid_database_fetch_resources_result_t resources = {
                    .pal = { .count = 0, .colors = NULL },
                    .frm = { .sprite = NULL }
            };

            yc_vid_status_t status = database->fetch(
                    YC_RES_PRO_OBJECT_TYPE_TILE,
                    sprite_idx,
                    &resources,
                    database->context
            );

            if (YC_VID_STATUS_OK != status) {
                yc_vid_view_objects_invalidate(objects, renderer);
                return status;
            }

            status = yc_vid_view_object_initialize(object, renderer, &resources);

            // Cleanup fetched data.
            free(resources.pal.colors);
            yc_res_frm_sprite_invalidate(resources.frm.sprite);
            free(resources.frm.sprite);

            if (YC_VID_STATUS_OK != status) {
                yc_vid_view_objects_invalidate(objects, renderer);
                return status;
            }
        }
    }

    objects->count = count;
    return YC_VID_STATUS_OK;
}
