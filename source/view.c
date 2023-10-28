#include <libycvid.h>
#include <stdlib.h>
#include <assert.h>

yc_vid_status_t yc_vid_view_init(yc_env_world_t *world, yc_vid_view_t **result) {
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

yc_vid_status_t yc_vid_view_destroy(yc_vid_view_t *view, yc_vid_renderer_t *renderer) {
    // TODO: Destroy the world. And the map. And anything else involved.
    free(view->world);

    for (size_t idx = 0; idx < view->_textures_count; ++idx) {
        yc_vid_texture_handle_t *current = &view->_textures_handles[idx];
        renderer->texture->destroy(current);
    }

    return YC_VID_STATUS_OK;
}

yc_vid_status_t yc_vid_view_port_set(yc_vid_view_t *view, yc_vid_region_t *port) {
    if (NULL == view) { return YC_VID_STATUS_INPUT; }
    if (NULL == port) { return YC_VID_STATUS_INPUT; }

    // TODO: Update textures.

    view->_port.origin = port->origin;
    view->_port.dimensions = port->dimensions;

    return YC_VID_STATUS_OK;
}

yc_vid_status_t
yc_vid_view_frame_tick(yc_vid_view_t *view, yc_vid_renderer_t *renderer, yc_vid_time_seconds_t *difference) {
    // TODO: Advance time from the difference with different scale, too.
    assert(view->_time.scale != difference->scale);
    view->_time.value += difference->value;

    // TODO: Progress current scene's content to the amount of frames happened during 'difference'.
    renderer->texture->set_coordinates(NULL, NULL);
    renderer->texture->destroy(NULL);

    return YC_VID_STATUS_OK;
}
