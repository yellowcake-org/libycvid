#include <libycvid.h>
#include <private.h>

yc_vid_status_t yc_vid_view_frame_tick_object(
        yc_vid_view_object_t *object,
        const yc_vid_renderer_t *renderer,
        const yc_vid_time_seconds_t *difference
) {
    // Choose current set using the orientation.
    yc_vid_texture_set_t *set = &object->sets[object->current.orientation];

    // Calculate frame advance.
    uint64_t advance = (set->fps * difference->value) / difference->scale;
    uint64_t rounds = advance / set->count;
    uint64_t effective = advance - (set->count * rounds);

    // Set new frame index.
    object->current.frame_idx += effective;

    // Update texture.
    yc_vid_texture_t *new = &set->textures[object->current.frame_idx];
    yc_vid_texture_t *old = object->current.texture;
    object->current.texture = new;

    // Check if texture been changed.
    if (true == renderer->texture->is_equal(old, new)) { return YC_VID_STATUS_OK; }

    // Hide old texture, show new. Set correct position.
    if (NULL != old) {
        yc_vid_status_t status = renderer->texture->set_visibility(
                old, YC_VID_TEXTURE_VISIBILITY_OFF, object->order, renderer->context
        );

        if (YC_VID_STATUS_OK != status) { return status; }
    }

    yc_vid_status_t status = renderer->texture->set_visibility(
            new, YC_VID_TEXTURE_VISIBILITY_ON, object->order, renderer->context
    );

    if (YC_VID_STATUS_OK != status) { return status; }
    return YC_VID_STATUS_OK;
}

yc_vid_status_t yc_vid_view_frame_tick_coordinates_tile(
        yc_vid_view_object_t *tile,
        bool is_roof,
        const yc_vid_renderer_t *renderer
) {
    size_t vertical_idx = tile->current.vertical_idx;
    size_t horizontal_idx = tile->current.horizontal_idx;

    // TODO: Cleanup the code.
    uint64_t pos_x = 80 * horizontal_idx;
    uint64_t pos_y = 36 * vertical_idx;

    pos_x = pos_x + vertical_idx * 32;
    pos_y = pos_y + (YC_RES_MATH_GRID_SIZE_TILES - 1 - horizontal_idx) * 12;

    pos_x = pos_x - (horizontal_idx * 32);
    pos_y = pos_y - (vertical_idx * 12) - (is_roof ? 96 : 0);

    // TODO: Check ranges / bounds.
    yc_vid_coordinates_t coordinates = { .x = pos_x, .y = pos_y };
    return renderer->texture->set_coordinates(tile->current.texture, coordinates, renderer->context);
}

yc_vid_status_t yc_vid_view_frame_tick_coordinates_object(
        yc_vid_view_object_t *object,
        const yc_vid_renderer_t *renderer
) {
    int32_t vertical_idx = object->current.vertical_idx;
    int32_t horizontal_idx = object->current.horizontal_idx;

    // TODO: Cleanup the code.
    int32_t pos_x = 0;
    int32_t pos_y = 0;

    pos_x = 80 * horizontal_idx;
    pos_y = 36 * vertical_idx;

    pos_x = pos_x + vertical_idx * 32;
    pos_y = pos_y + (YC_RES_MATH_GRID_SIZE_TILES - 1 - horizontal_idx) * 12;

    pos_x = pos_x - (horizontal_idx * 32);
    pos_y = pos_y - (vertical_idx * 12);

    int32_t scale = YC_RES_MATH_GRID_SIZE_HEXES / YC_RES_MATH_GRID_SIZE_TILES;

    pos_x = pos_x / scale;
    pos_y = pos_y / scale;

    bool is_row_even = horizontal_idx % 2 == 0;

    pos_x = pos_x - 8 + (is_row_even ? 0 : 8);
    pos_y = pos_y - 8 + (is_row_even ? 0 : 6);

    pos_x = pos_x + (int32_t) object->current.correction_x;
    pos_y = pos_y + (int32_t) object->current.correction_y;

    // TODO: Check ranges / bounds.
    yc_vid_coordinates_t coordinates = { .x = pos_x, .y = pos_y + 36 * 16 };
    return renderer->texture->set_coordinates(object->current.texture, coordinates, renderer->context);
}
