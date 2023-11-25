#ifndef LIBYCVID_PRIVATE_VIEW_FRAME_H
#define LIBYCVID_PRIVATE_VIEW_FRAME_H

yc_vid_status_t yc_vid_view_frame_tick_tile(
        yc_vid_view_object_t *tile,
        const yc_vid_renderer_t *renderer,
        const yc_vid_time_seconds_t *difference,
        size_t horizontal_idx,
        size_t vertical_idx,
        bool is_roof
);

#endif //LIBYCVID_PRIVATE_VIEW_FRAME_H
