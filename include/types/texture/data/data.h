#ifndef LIBYCVID_INCLUDE_TYPES_TEXTURE_DATA_H
#define LIBYCVID_INCLUDE_TYPES_TEXTURE_DATA_H

typedef struct yc_vid_texture_handle yc_vid_texture_handle_t;

typedef struct yc_vid_texture {
    yc_vid_texture_handle_t *handle;
} yc_vid_texture_t;

typedef struct yc_vid_texture_set {
    uint16_t fps, keyframe_idx;

    size_t count;
    yc_vid_texture_t *textures;
} yc_vid_texture_set_t;

typedef enum yc_vid_texture_visibility {
    YC_VID_TEXTURE_VISIBILITY_ON,
    YC_VID_TEXTURE_VISIBILITY_OFF
} yc_vid_texture_visibility_t;

typedef struct yc_vid_texture_data {
    yc_res_pal_color_t *pixels;

    yc_vid_shift_t shift;
    yc_vid_dimensions_t dimensions;
} yc_vid_texture_data_t;

#endif //LIBYCVID_INCLUDE_TYPES_TEXTURE_DATA_H
