#ifndef LIBYCVID_INCLUDE_TYPES_TEXTURE_API_H
#define LIBYCVID_INCLUDE_TYPES_TEXTURE_API_H

typedef yc_vid_status_t (yc_vid_texture_initialize_t)(
        yc_res_pro_object_type_t,
        uint16_t sprite_idx,
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

typedef struct yc_vid_texture_api {
    yc_vid_texture_initialize_t *initialize;
    yc_vid_texture_invalidate_t *invalidate;

    yc_vid_texture_is_equal *is_equal;

    yc_vid_texture_set_visibility_t *set_visibility;
    yc_vid_texture_set_coordinates_t *set_coordinates;
} yc_vid_texture_api_t;

#endif //LIBYCVID_INCLUDE_TYPES_TEXTURE_API_H
