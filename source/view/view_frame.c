#include <libycvid.h>
#include <assert.h>

// TODO: Support specifying layer to render (multithreading!).
yc_vid_status_t yc_vid_view_frame_tick(
        yc_vid_view_t *view,
        yc_vid_renderer_t *renderer,
        yc_vid_time_seconds_t *difference
) {
    for (size_t horizontal_idx = 0; horizontal_idx < YC_RES_MATH_GRID_SIZE_TILES; ++horizontal_idx) {
        for (size_t vertical_idx = 0; vertical_idx < YC_RES_MATH_GRID_SIZE_TILES; ++vertical_idx) {
            yc_vid_view_object_t *object = &view->floor.pointers[horizontal_idx * vertical_idx];
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

            // Hide old texture, show new. Set correct position.;
            yc_vid_texture_t *new = &set->textures[object->state.frame_idx];
            yc_vid_texture_t *old = object->state.texture;
            object->state.texture = new;

            if (NULL != old) {
                status = renderer->texture->set_visibility(old, YC_VID_TEXTURE_VISIBILITY_OFF);
                if (YC_VID_STATUS_OK != status) { return status; }
            }

            // TODO: Check ranges / bounds.
            yc_vid_coordinates_t coordinates = {
                    .x = 48 * horizontal_idx + 32 * vertical_idx,
                    .y = 24 * vertical_idx - 12 * horizontal_idx
            };

            status = renderer->texture->set_visibility(new, YC_VID_TEXTURE_VISIBILITY_ON);
            if (YC_VID_STATUS_OK != status) { return status; }

            status = renderer->texture->set_coordinates(new, coordinates);
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
