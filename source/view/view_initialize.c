#include <libycvid.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_view_initialize(yc_env_world_t *world, yc_vid_view_t **result) {
    if (NULL == world) { return YC_VID_STATUS_INPUT; }
    if (NULL == result) { return YC_VID_STATUS_INPUT; }

    yc_vid_view_t *view = malloc(sizeof(yc_vid_view_t));
    if (NULL == view) { return YC_VID_STATUS_MEM; }

    // Assign provided world.
    view->world = world;
    *result = view;

    // Initial zero view port.
    view->_port.origin.x = 0;
    view->_port.origin.y = 0;

    view->_port.dimensions.horizontal = 0;
    view->_port.dimensions.vertical = 0;

    return YC_VID_STATUS_OK;
}
