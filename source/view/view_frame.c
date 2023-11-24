#include <libycvid.h>
#include <private.h>

// TODO: Support specifying layer to render (multithreading!).
yc_vid_status_t yc_vid_view_frame_tick(
        yc_vid_view_t *view,
        const yc_vid_renderer_t *renderer,
        const yc_vid_time_seconds_t *difference
) {
    for (size_t vertical_idx = 0; vertical_idx < YC_RES_MATH_GRID_SIZE_TILES; ++vertical_idx) {
        for (size_t horizontal_idx = 0; horizontal_idx < YC_RES_MATH_GRID_SIZE_TILES; ++horizontal_idx) {
            size_t linear_idx = horizontal_idx + vertical_idx * YC_RES_MATH_GRID_SIZE_TILES;

            yc_vid_view_frame_tick_tile(
                    &view->floor.pointers[linear_idx],
                    renderer,
                    difference,
                    horizontal_idx,
                    vertical_idx,
                    false
            );

            yc_vid_view_frame_tick_tile(
                    &view->roofs.pointers[linear_idx],
                    renderer,
                    difference,
                    horizontal_idx,
                    vertical_idx,
                    true
            );
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
