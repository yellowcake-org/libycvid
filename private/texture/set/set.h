#ifndef LIBYCVID_PRIVATE_TEXTURE_SET_H
#define LIBYCVID_PRIVATE_TEXTURE_SET_H

yc_vid_status_t yc_vid_texture_set_initialize(
        yc_vid_texture_set_t *set,
        const yc_res_frm_animation_t *animation,
        const yc_res_pal_parse_result_t *palette,
        const yc_vid_renderer_t *renderer
);

void yc_vid_texture_set_invalidate(yc_vid_texture_set_t *set, const yc_vid_renderer_t *renderer);

#endif //LIBYCVID_PRIVATE_TEXTURE_SET_H
