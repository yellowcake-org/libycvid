#ifndef LIBYCVID_INCLUDE_TYPES_TEXTURE_DATA_H
#define LIBYCVID_INCLUDE_TYPES_TEXTURE_DATA_H

typedef struct yc_vid_texture_data {
    yc_res_pal_color_t *pixels;

    yc_vid_shift_t shift;
    yc_vid_dimensions_t dimensions;
} yc_vid_texture_data_t;

#endif //LIBYCVID_INCLUDE_TYPES_TEXTURE_DATA_H
