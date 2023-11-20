#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

void yc_vid_view_object_invalidate(yc_vid_view_object_t *object, const yc_vid_renderer_t *renderer) {
    if (NULL == object) { return; }
    if (NULL == renderer) { return; }

    object->state.texture = NULL;
    object->state.frame_idx = 0;

    for (size_t set_idx = 0; set_idx < object->count; ++set_idx) {
        yc_vid_texture_set_invalidate(&object->sets[set_idx], renderer);
    }

    object->count = 0;
    free(object->sets);
    object->sets = NULL;
}

void yc_vid_view_objects_invalidate(yc_vid_view_objects_t *objects, const  yc_vid_renderer_t *renderer) {
    if (NULL == objects) { return; }
    if (NULL == renderer) { return; }

    for (size_t object_idx = 0; object_idx < objects->count; ++object_idx) {
        yc_vid_view_object_invalidate(&objects->pointers[object_idx], renderer);
    }

    objects->count = 0;
    free(objects->pointers);
    objects->pointers = NULL;
}
