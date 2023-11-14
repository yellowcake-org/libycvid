#ifndef LIBYCVID_INCLUDE_TYPES_TEXTURE_SET_H
#define LIBYCVID_INCLUDE_TYPES_TEXTURE_SET_H

typedef struct yc_vid_texture_set {
    uint16_t fps, keyframe_idx;

    size_t count;
    yc_vid_texture_t *textures;
} yc_vid_texture_set_t;

#endif //LIBYCVID_INCLUDE_TYPES_TEXTURE_SET_H
