#ifndef LIBYCVID_INCLUDE_TYPES_VIEW_H
#define LIBYCVID_INCLUDE_TYPES_VIEW_H

#include <libycenv.h>

typedef struct yc_vid_view {
    yc_env_world_t *world;

    yc_vid_region_t _port;
    yc_vid_time_seconds_t _time;

    size_t _textures_count;
    yc_vid_texture_handle_t *_textures_handles;
} yc_vid_view_t;

#endif //LIBYCVID_INCLUDE_TYPES_VIEW_H
