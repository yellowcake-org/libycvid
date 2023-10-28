#include <libycvid.h>
#include <stdlib.h>

yc_vid_view_status_t yc_vid_view_init(yc_env_world_t *world, yc_vid_view_t **result) {
    if (NULL == world) { return YC_VID_VIEW_STATUS_INPUT; }
    if (NULL == result) { return YC_VID_VIEW_STATUS_INPUT; }

    yc_vid_view_t *view = malloc(sizeof(yc_vid_view_t));
    if (NULL == view) { return YC_VID_VIEW_STATUS_MEM; }

    view->world = world;
    *result = view;

    return YC_VID_VIEW_STATUS_OK;
}
