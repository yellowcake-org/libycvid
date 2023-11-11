#ifndef LIBYCVID_INCLUDE_TYPES_VIEW_H
#define LIBYCVID_INCLUDE_TYPES_VIEW_H

#include <libycres.h>

typedef struct yc_vid_view_object {
    size_t count;
    yc_vid_texture_set_t *sets;

    yc_res_math_orientation_t orientations[YC_RES_MATH_ORIENTATION_COUNT];
} yc_vid_view_object_t;

typedef struct yc_vid_view_objects {
    size_t count;
    yc_vid_view_object_t *pointers;
} yc_vid_view_objects_t;

typedef struct yc_vid_view {
    yc_res_map_level_t *level;

    yc_vid_region_t port;
    yc_vid_time_seconds_t time;

    // TODO: Ability to process 'world updates': moving, removing and adding objects and tiles.
    yc_vid_view_objects_t tiles;
    yc_vid_view_objects_t objects;
} yc_vid_view_t;

#endif //LIBYCVID_INCLUDE_TYPES_VIEW_H
