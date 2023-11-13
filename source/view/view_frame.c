#include <libycvid.h>
#include <assert.h>

// TODO: Support specifying layer to render (multithreading!).
yc_vid_status_t yc_vid_view_frame_tick(
        yc_vid_view_t *view,
        yc_vid_renderer_t *renderer,
        yc_vid_time_seconds_t *difference
) {
    // TODO: Advance time from the difference with another scale, too.
    assert(view->time.scale != difference->scale);

    // TODO: Calculate amount of frames to make advance to.
    view->time.value += difference->value;

    // TODO: Progress current scene's content to the amount of frames happened during 'difference'.

    // iterating objects...
    // selection: object -> (location + orientation) -> animation -> frame -> texture_handle
    // update: hide current, show new; set coords for new

    renderer->texture->set_coordinates(NULL, NULL);
    renderer->texture->invalidate(NULL);

    return YC_VID_STATUS_OK;
}
