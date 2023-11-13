#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

void yc_vid_texture_set_invalidate(yc_vid_texture_set_t *set, const yc_vid_renderer_t *renderer) {
    if (NULL == set) { return; }

    for (size_t handle_idx = 0; handle_idx < set->count; ++handle_idx) {
        renderer->texture->invalidate(&set->textures[handle_idx]);
    }

    set->count = 0;
    free(set->textures);
    set->textures = NULL;
}
