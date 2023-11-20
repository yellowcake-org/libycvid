#ifndef LIBYCVID_INCLUDE_TYPES_VIEW_H
#define LIBYCVID_INCLUDE_TYPES_VIEW_H

#include "object/object.h"

typedef struct yc_vid_view {
    yc_res_map_level_t *level;

    yc_vid_region_t port;
    yc_vid_time_seconds_t time;

    // TODO: Ability to process 'world updates':
    // moving, removing and adding objects and tiles.
    // In other words, there has to be a way to make updates from 'level'
    // to objects:
    yc_vid_view_objects_t objects;
    yc_vid_view_objects_t floor, roofs;
} yc_vid_view_t;

#endif //LIBYCVID_INCLUDE_TYPES_VIEW_H
