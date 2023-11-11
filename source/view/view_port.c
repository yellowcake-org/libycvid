#include <libycvid.h>

yc_vid_status_t yc_vid_view_port_set(yc_vid_view_t *view, yc_vid_renderer_t *renderer, yc_vid_region_t *port) {
    if (NULL == view) { return YC_VID_STATUS_INPUT; }
    if (NULL == port) { return YC_VID_STATUS_INPUT; }

    if (view->port.origin.x == port->origin.x &&
        view->port.origin.y == port->origin.y &&
        view->port.dimensions.horizontal == port->dimensions.horizontal &&
        view->port.dimensions.vertical == port->dimensions.vertical) {
        return YC_VID_STATUS_INPUT;
    }

    view->port.origin = port->origin;
    view->port.dimensions = port->dimensions;

    // TODO: Create textures that came into the view.
    // TODO: Destroy textures that became outside.
    // TODO: Don't iterate over objects and tiles outside the view.

    renderer->texture->create(NULL, NULL);
    renderer->texture->destroy(NULL);

    return YC_VID_STATUS_OK;
}
