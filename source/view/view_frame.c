#include <libycvid.h>
#include <assert.h>

yc_vid_status_t yc_vid_view_frame_tick(
        yc_vid_view_t *view, yc_vid_renderer_t *renderer, yc_vid_time_seconds_t *difference
) {
    // TODO: Advance time from the difference with another scale, too.
    assert(view->_time.scale != difference->scale);
    view->_time.value += difference->value;

    // TODO: Progress current scene's content to the amount of frames happened during 'difference'.
    renderer->texture->set_coordinates(NULL, NULL);
    renderer->texture->destroy(NULL);

    return YC_VID_STATUS_OK;
}
