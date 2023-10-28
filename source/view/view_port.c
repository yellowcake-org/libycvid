#include <libycvid.h>

yc_vid_status_t yc_vid_view_port_set(yc_vid_view_t *view, yc_vid_renderer_t *renderer, yc_vid_region_t *port) {
    if (NULL == view) { return YC_VID_STATUS_INPUT; }
    if (NULL == port) { return YC_VID_STATUS_INPUT; }

    // TODO: Update textures.

    view->_port.origin = port->origin;
    view->_port.dimensions = port->dimensions;

    // TODO: Destroy textures that became outside.
    renderer->texture->destroy(NULL);

    return YC_VID_STATUS_OK;
}
