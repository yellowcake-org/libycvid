#ifndef LIBYCVID_INCLUDE_TYPES_VIEW_OBJECT_H
#define LIBYCVID_INCLUDE_TYPES_VIEW_OBJECT_H

typedef struct yc_vid_view_object {
    size_t count;
    yc_vid_texture_set_t *sets;

    yc_res_math_orientation_t orientations[YC_RES_MATH_ORIENTATION_COUNT];
} yc_vid_view_object_t;

typedef struct yc_vid_view_objects {
    size_t count;
    yc_vid_view_object_t *pointers;
} yc_vid_view_objects_t;

#endif //LIBYCVID_INCLUDE_TYPES_VIEW_OBJECT_H