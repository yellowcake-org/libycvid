#include <libycvid.h>
#include <private.h>

yc_vid_status_t yc_vid_view_frame_tick_tile(
        yc_vid_view_object_t *tile,
        const yc_vid_renderer_t *renderer,
        const yc_vid_time_seconds_t *difference,
        size_t horizontal_idx,
        size_t vertical_idx,
        bool is_roof
) {
    // Tiles have to have only 1 set. It doesn't change.
    yc_vid_texture_set_t *set = &tile->sets[0];

    // Calculate frame advance.
    uint64_t advance = (set->fps * difference->value) / difference->scale;
    uint64_t rounds = advance / set->count;
    uint64_t effective = advance - (set->count * rounds);

    // Set new frame index.
    tile->current.frame_idx += effective;

    // Update texture.
    yc_vid_texture_t *new = &set->textures[tile->current.frame_idx];
    yc_vid_texture_t *old = tile->current.texture;
    tile->current.texture = new;

    // Check if texture been changed.
    if (true == renderer->texture->is_equal(old, new)) { return YC_VID_STATUS_OK; }

    // Hide old texture, show new. Set correct position.
    if (NULL != old) {
        yc_vid_status_t status = renderer->texture->set_visibility(
                old,
                YC_VID_TEXTURE_VISIBILITY_OFF,
                YC_VID_TEXTURE_ORDER_FLOOR,
                renderer->context
        );

        if (YC_VID_STATUS_OK != status) { return status; }
    }

    // TODO: Cleanup the code.
    uint64_t pos_x = 0;
    uint64_t pos_y = 0;

    pos_x = 80 * horizontal_idx;
    pos_y = 36 * vertical_idx;

    pos_x = pos_x + vertical_idx * 32;
    pos_y = pos_y + (YC_RES_MATH_GRID_SIZE_TILES - 1 - horizontal_idx) * 12;

    pos_x = pos_x - (horizontal_idx * 32);
    pos_y = pos_y - (vertical_idx * 12) - (is_roof ? 96 : 0);

    // TODO: Check ranges / bounds.
    yc_vid_coordinates_t coordinates = { .x = pos_x, .y = pos_y };

    yc_vid_status_t status = renderer->texture->set_visibility(
            new,
            YC_VID_TEXTURE_VISIBILITY_ON,
            YC_VID_TEXTURE_ORDER_FLOOR,
            renderer->context
    );

    if (YC_VID_STATUS_OK != status) { return status; }

    status = renderer->texture->set_coordinates(new, coordinates, renderer->context);
    if (YC_VID_STATUS_OK != status) { return status; }

    return YC_VID_STATUS_OK;
}
