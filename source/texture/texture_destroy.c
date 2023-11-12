#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

void yc_vid_texture_set_destroy(const yc_vid_renderer_t *renderer, yc_vid_texture_set_t *set) {
    for (size_t handle_idx = 0; handle_idx < set->count; ++handle_idx) {
        renderer->texture->destroy(&set->pointers[handle_idx]);
    }

    set->count = 0;
    free(set->pointers);
    set->pointers = NULL;
}
