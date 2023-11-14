#include <libycvid.h>
#include <private.h>

yc_vid_status_t yc_vid_view_initialize(
        yc_vid_view_t *view,
        yc_res_map_level_t *level,
        const yc_vid_renderer_t *renderer,
        const yc_vid_database_api_t *database
) {
    if (NULL == view) { return YC_VID_STATUS_INPUT; }
    if (NULL == level) { return YC_VID_STATUS_INPUT; }

    // Assign provided world, since we don't own it and assume it's been allocated.
    view->level = level;

    // Initial zero view port.
    view->port.origin.x = 0;
    view->port.origin.y = 0;

    view->port.dimensions.vertical = 0;
    view->port.dimensions.horizontal = 0;

    // Load objects. Start from 'OK'.
    yc_vid_status_t status = YC_VID_STATUS_OK;

    //  Load floor tiles.
    status = yc_vid_view_objects_initialize(&view->floor, &level->floor, renderer, database);

    if (YC_VID_STATUS_OK != status) {
        yc_vid_view_invalidate(view, renderer);
        return status;
    }

    // Load roofs' tiles.
    status = yc_vid_view_objects_initialize(&view->roofs, &level->roof, renderer, database);

    if (YC_VID_STATUS_OK != status) {
        yc_vid_view_invalidate(view, renderer);
        return status;
    }

    // TODO: Load level's objects.

    return status;
}
