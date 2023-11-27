#ifndef LIBYCVID_INCLUDE_TYPES_MATH_H
#define LIBYCVID_INCLUDE_TYPES_MATH_H

#include <stdint.h>

typedef struct yc_vid_coordinates {
    uint64_t x, y;
} yc_vid_coordinates_t;

typedef struct yc_vid_indexes {
    int32_t x, y;
} yc_vid_indexes_t;

typedef struct yc_vid_dimensions {
    uint64_t horizontal, vertical;
} yc_vid_dimensions_t;

typedef struct yc_vid_region {
    yc_vid_coordinates_t origin;
    yc_vid_dimensions_t dimensions;
} yc_vid_region_t;

#endif //LIBYCVID_INCLUDE_TYPES_MATH_H
