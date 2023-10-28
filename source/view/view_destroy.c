#include <libycvid.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_view_destroy(yc_vid_view_t *view, yc_vid_renderer_t *renderer) {
    // TODO: Destroy the world. And the map. And anything else involved.
    free(view->world);

    for (size_t idx = 0; idx < view->_textures_count; ++idx) {
        yc_vid_texture_handle_t *current = &view->_textures_handles[idx];
        renderer->texture->destroy(current);
    }

    return YC_VID_STATUS_OK;
}
