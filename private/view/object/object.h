#ifndef LIBYCVID_PRIVATE_VIEW_OBJECT_H
#define LIBYCVID_PRIVATE_VIEW_OBJECT_H

yc_vid_status_t yc_vid_view_object_initialize(
        yc_vid_view_object_t *object,
        const yc_vid_renderer_t *renderer,
        const yc_vid_database_fetch_resources_result_t *resources
);

yc_vid_status_t yc_vid_view_objects_initialize(
        yc_vid_view_objects_t *objects,
        yc_res_map_level_tiles_t *tiles,
        const yc_vid_renderer_t *renderer,
        const yc_vid_database_api_t *database
);

void yc_vid_view_object_invalidate(yc_vid_view_object_t *object, const yc_vid_renderer_t *renderer);

void yc_vid_view_objects_invalidate(yc_vid_view_objects_t *objects, const yc_vid_renderer_t *renderer);

#endif //LIBYCVID_PRIVATE_VIEW_OBJECT_H
