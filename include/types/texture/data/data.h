#ifndef LIBYCVID_INCLUDE_TYPES_TEXTURE_DATA_H
#define LIBYCVID_INCLUDE_TYPES_TEXTURE_DATA_H

#include <libycres.h>

typedef uint32_t yc_vid_texture_handle_t;

typedef struct yc_vid_texture_set {
    uint16_t fps, keyframe_idx;

    size_t count;
    yc_vid_texture_handle_t *pointers;
} yc_vid_texture_set_t;

typedef enum yc_vid_texture_visibility {
    YC_VID_TEXTURE_VISIBILITY_ON,
    YC_VID_TEXTURE_VISIBILITY_OFF
} yc_vid_texture_visibility_t;

typedef struct yc_vid_texture_data {
    yc_res_pal_color_t *pixels;

    yc_res_frm_shift_t shift;
    yc_vid_dimensions_t dimensions;
} yc_vid_texture_data_t;

#endif //LIBYCVID_INCLUDE_TYPES_TEXTURE_DATA_H
