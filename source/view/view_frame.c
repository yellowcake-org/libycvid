#include <libycvid.h>
#include <private.h>

// TODO: Support specifying layer to render (multithreading!).
yc_vid_status_t yc_vid_view_frame_tick(
        yc_vid_view_t *view,
        const yc_vid_renderer_t *renderer,
        const yc_vid_time_seconds_t *difference
) {
    // TODO: Better check objects in list not to be out of grid's bounds.
    // TODO: Tick and update coordinates for those which we know updated in environment only.

    for (size_t index = 0; index < view->objects.count; ++index) {
        yc_vid_view_object_t *current = &view->objects.pointers[index];
        yc_vid_status_t status = YC_VID_STATUS_OK;

        status = yc_vid_view_frame_tick_object(current, renderer, difference);
        if (YC_VID_STATUS_OK != status) { return status; }
    }

    // TODO: Advance time from the difference with another scale, too.
    if (view->time.scale != difference->scale) { return YC_VID_STATUS_CORRUPTED; }
    view->time.value += difference->value;

    return YC_VID_STATUS_OK;
}
