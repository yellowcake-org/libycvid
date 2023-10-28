#ifndef LIBYCVID_INCLUDE_TYPES_TEXTURE_H
#define LIBYCVID_INCLUDE_TYPES_TEXTURE_H

#include <libycres.h>

typedef uint32_t yc_vid_texture_handle_t;

typedef yc_vid_texture_handle_t (yc_vid_texture_create_t)(yc_res_frm_texture_t *);
typedef yc_vid_status_t (yc_vid_texture_destroy_t)(yc_vid_texture_handle_t *);

typedef yc_vid_status_t (yc_vid_texture_set_coordinates_t)(yc_vid_texture_handle_t *, yc_vid_coordinates_t *);

typedef struct yc_vid_texture_api {
    yc_vid_texture_create_t *create;
    yc_vid_texture_destroy_t *destroy;

    yc_vid_texture_set_coordinates_t *set_coordinates;
} yc_vid_texture_api_t;

#endif //LIBYCVID_INCLUDE_TYPES_TEXTURE_H
