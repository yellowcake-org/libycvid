#ifndef LIBYCVID_INCLUDE_METHODS_VIEW_H
#define LIBYCVID_INCLUDE_METHODS_VIEW_H

yc_vid_status_t yc_vid_view_initialize(yc_res_map_level_t *level, yc_vid_view_t **result);
yc_vid_status_t yc_vid_view_destroy(yc_vid_view_t *view, yc_vid_renderer_t *renderer);

yc_vid_status_t yc_vid_view_port_set(yc_vid_view_t *view, yc_vid_renderer_t *renderer, yc_vid_region_t *port);
yc_vid_status_t yc_vid_view_frame_tick(
        yc_vid_view_t *view, yc_vid_renderer_t *renderer, yc_vid_time_seconds_t *difference
);

#endif //LIBYCVID_INCLUDE_METHODS_VIEW_H
