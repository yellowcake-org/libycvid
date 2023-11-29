#ifndef LIBYCVID_PRIVATE_VIEW_OBJECT_H
#define LIBYCVID_PRIVATE_VIEW_OBJECT_H

yc_vid_status_t yc_vid_view_object_initialize_from_tile(
        yc_vid_view_object_t *object,
        uint16_t sprite_idx,
        int32_t horizontal_idx,
        int32_t vertical_idx,
        bool is_roof,
        const yc_vid_renderer_t *renderer
);

yc_vid_status_t yc_vid_view_objects_initialize_from_tiles(
        yc_vid_view_objects_t *objects,
        yc_res_map_level_tiles_t *tiles,
        bool is_roof,
        const yc_vid_renderer_t *renderer
);

yc_vid_status_t yc_vid_view_object_initialize_from_object(
        yc_vid_view_object_t *video_object,
        yc_res_map_level_object_t *level_object,
        const yc_vid_renderer_t *renderer
);

yc_vid_status_t yc_vid_view_objects_initialize_from_objects(
        yc_vid_view_objects_t *view_objects,
        yc_res_map_level_objects_t *level_objects,
        const yc_vid_renderer_t *renderer
);

void yc_vid_view_object_invalidate(yc_vid_view_object_t *object, const yc_vid_renderer_t *renderer);
void yc_vid_view_objects_invalidate(yc_vid_view_objects_t *objects, const yc_vid_renderer_t *renderer);

#endif //LIBYCVID_PRIVATE_VIEW_OBJECT_H
