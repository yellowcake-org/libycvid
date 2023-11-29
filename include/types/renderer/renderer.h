#ifndef LIBYCVID_INCLUDE_TYPES_RENDERER_H
#define LIBYCVID_INCLUDE_TYPES_RENDERER_H

typedef struct yc_vid_renderer {
    void *context;
    const yc_vid_texture_api_t *texture;
} yc_vid_renderer_t;

#endif //LIBYCVID_INCLUDE_TYPES_RENDERER_H
