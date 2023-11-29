#ifndef LIBYCVID_PRIVATE_VIEW_FRAME_H
#define LIBYCVID_PRIVATE_VIEW_FRAME_H

yc_vid_status_t yc_vid_view_frame_tick_object(
        yc_vid_view_object_t *object,
        const yc_vid_renderer_t *renderer,
        const yc_vid_time_seconds_t *difference
);

yc_vid_status_t yc_vid_view_frame_tick_coordinates_tile(
        yc_vid_view_object_t *tile,
        bool is_roof,
        const yc_vid_renderer_t *renderer
);

yc_vid_status_t yc_vid_view_frame_tick_coordinates_object(
        yc_vid_view_object_t *object,
        const yc_vid_renderer_t *renderer
);

#endif //LIBYCVID_PRIVATE_VIEW_FRAME_H
