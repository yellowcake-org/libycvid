#ifndef LIBYCVID_INCLUDE_TYPES_VIEW_OBJECT_STATE_H
#define LIBYCVID_INCLUDE_TYPES_VIEW_OBJECT_STATE_H

#include <stddef.h>

typedef struct yc_vid_view_object_state {
    size_t frame_idx;

    int32_t horizontal_idx, vertical_idx;
    uint32_t correction_x, correction_y;
    yc_res_math_orientation_t orientation;

    yc_vid_texture_t *texture;
} yc_vid_view_object_state_t;

#endif //LIBYCVID_INCLUDE_TYPES_VIEW_OBJECT_STATE_H
