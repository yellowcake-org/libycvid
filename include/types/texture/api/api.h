#ifndef LIBYCVID_INCLUDE_TYPES_TEXTURE_API_H
#define LIBYCVID_INCLUDE_TYPES_TEXTURE_API_H

typedef yc_vid_status_t (yc_vid_texture_initialize_t)(
        uint32_t fid,
        yc_res_math_orientation_t,
        yc_vid_texture_set_t *,
        void *context
);

typedef yc_vid_status_t (yc_vid_texture_invalidate_t)(yc_vid_texture_t *, void *context);

typedef bool (yc_vid_texture_is_equal)(yc_vid_texture_t *, yc_vid_texture_t *);

typedef yc_vid_status_t (yc_vid_texture_set_visibility_t)(
        yc_vid_texture_t *, yc_vid_texture_visibility_t, yc_vid_texture_order_t, void *context
);

typedef yc_vid_status_t (yc_vid_texture_set_coordinates_t)(
        yc_vid_texture_t *, yc_vid_coordinates_t, void *context
);

typedef yc_vid_status_t (yc_vid_texture_set_grid_indexes_t)(
        yc_vid_texture_t *, yc_vid_indexes_t, size_t scale, void *context
);

typedef struct yc_vid_texture_api {
    yc_vid_texture_initialize_t *initialize;
    yc_vid_texture_invalidate_t *invalidate;

    yc_vid_texture_is_equal *is_equal;

    yc_vid_texture_set_visibility_t *set_visibility;
    yc_vid_texture_set_coordinates_t *set_coordinates;
    yc_vid_texture_set_grid_indexes_t *set_indexes;
} yc_vid_texture_api_t;

#endif //LIBYCVID_INCLUDE_TYPES_TEXTURE_API_H
