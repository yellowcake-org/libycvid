#include <libycvid.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_view_initialize(yc_res_map_level_t *level, yc_vid_view_t **result) {
    if (NULL == level) { return YC_VID_STATUS_INPUT; }
    if (NULL == result) { return YC_VID_STATUS_INPUT; }

    yc_vid_view_t *view = malloc(sizeof(yc_vid_view_t));
    if (NULL == view) { return YC_VID_STATUS_MEM; }

    // Assign provided world, since we don't own it and assume it's been allocated.
    view->level = level;
    *result = view;

    // Initial zero view port.
    view->port.origin.x = 0;
    view->port.origin.y = 0;

    view->port.dimensions.horizontal = 0;
    view->port.dimensions.vertical = 0;

    // Empty textures lists
    view->tiles.count = 0;
    view->tiles.pointers = NULL;

    view->objects.count = 0;
    view->objects.pointers = NULL;

    return YC_VID_STATUS_OK;
}
