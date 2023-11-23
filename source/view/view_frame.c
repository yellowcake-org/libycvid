#include <libycvid.h>
#include <assert.h>

// TODO: Support specifying layer to render (multithreading!).
yc_vid_status_t yc_vid_view_frame_tick(
        yc_vid_view_t *view,
        const yc_vid_renderer_t *renderer,
        const yc_vid_time_seconds_t *difference
) {
    for (size_t vertical_idx = 0; vertical_idx < YC_RES_MATH_GRID_SIZE_TILES; ++vertical_idx) {
        for (size_t horizontal_idx = 0; horizontal_idx < YC_RES_MATH_GRID_SIZE_TILES; ++horizontal_idx) {
            size_t linear_idx = horizontal_idx + vertical_idx * YC_RES_MATH_GRID_SIZE_TILES;
            yc_vid_view_object_t *object = &view->floor.pointers[linear_idx];

            yc_vid_status_t status = YC_VID_STATUS_OK;

            // Tiles have to have only 1 set. It doesn't change.
            if (1 != object->sets->count) { return YC_VID_STATUS_CORRUPTED; }
            yc_vid_texture_set_t *set = &object->sets[object->orientations[YC_RES_MATH_ORIENTATION_NE]];

            // Calculate frame advance.
            uint64_t advance = (set->fps * difference->value) / difference->scale;
            uint64_t rounds = advance / set->count;
            uint64_t effective = advance - (set->count * rounds);

            // Set new frame index.
            object->state.frame_idx += effective;

            // Update texture.
            yc_vid_texture_t *new = &set->textures[object->state.frame_idx];
            yc_vid_texture_t *old = object->state.texture;
            object->state.texture = new;

            // Check if texture been changed.
            if (true == renderer->texture->is_equal(old, new)) { continue; }

            // Hide old texture, show new. Set correct position.
            if (NULL != old) {
                status = renderer->texture->set_visibility(old, YC_VID_TEXTURE_VISIBILITY_OFF, renderer->context);
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
            pos_y = pos_y - (vertical_idx * 12);

            // TODO: Check ranges / bounds.
            yc_vid_coordinates_t coordinates = { .x = pos_x, .y = pos_y };

            status = renderer->texture->set_visibility(new, YC_VID_TEXTURE_VISIBILITY_ON, renderer->context);
            if (YC_VID_STATUS_OK != status) { return status; }

            status = renderer->texture->set_coordinates(new, coordinates, renderer->context);
            if (YC_VID_STATUS_OK != status) { return status; }
        }
    }

    for (size_t vertical_idx = 0; vertical_idx < YC_RES_MATH_GRID_SIZE_TILES; ++vertical_idx) {
        for (size_t horizontal_idx = 0; horizontal_idx < YC_RES_MATH_GRID_SIZE_TILES; ++horizontal_idx) {
            size_t linear_idx = horizontal_idx + vertical_idx * YC_RES_MATH_GRID_SIZE_TILES;
            yc_vid_view_object_t *object = &view->roofs.pointers[linear_idx];

            yc_vid_status_t status = YC_VID_STATUS_OK;

            // Tiles have to have only 1 set. It doesn't change.
            if (1 != object->sets->count) { return YC_VID_STATUS_CORRUPTED; }
            yc_vid_texture_set_t *set = &object->sets[object->orientations[YC_RES_MATH_ORIENTATION_NE]];

            // Calculate frame advance.
            uint64_t advance = (set->fps * difference->value) / difference->scale;
            uint64_t rounds = advance / set->count;
            uint64_t effective = advance - (set->count * rounds);

            // Set new frame index.
            object->state.frame_idx += effective;

            // Update texture.
            yc_vid_texture_t *new = &set->textures[object->state.frame_idx];
            yc_vid_texture_t *old = object->state.texture;
            object->state.texture = new;

            // Check if texture been changed.
            if (true == renderer->texture->is_equal(old, new)) { continue; }

            // Hide old texture, show new. Set correct position.
            if (NULL != old) {
                status = renderer->texture->set_visibility(old, YC_VID_TEXTURE_VISIBILITY_OFF, renderer->context);
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
            pos_y = pos_y - (vertical_idx * 12);

            // TODO: Check ranges / bounds.
            yc_vid_coordinates_t coordinates = { .x = pos_x, .y = pos_y - 96 };

            status = renderer->texture->set_visibility(new, YC_VID_TEXTURE_VISIBILITY_ON, renderer->context);
            if (YC_VID_STATUS_OK != status) { return status; }

            status = renderer->texture->set_coordinates(new, coordinates, renderer->context);
            if (YC_VID_STATUS_OK != status) { return status; }
        }
    }

    // iterating objects...
    // selection: object -> (location + orientation) -> animation -> frame -> texture_handle
    // update: hide current, show new; set coords for new

    // TODO: Advance time from the difference with another scale, too.
    if (view->time.scale != difference->scale) { return YC_VID_STATUS_CORRUPTED; }
    view->time.value += difference->value;

    return YC_VID_STATUS_OK;
}
