#include <libycvid.h>
#include <private.h>
#include <stdlib.h>

void yc_vid_view_object_invalidate(yc_vid_view_object_t *object, const yc_vid_renderer_t *renderer) {
    if (NULL == object) { return; }
    if (NULL == renderer) { return; }

    object->current.texture = NULL;
    object->current.frame_idx = 0;

    for (yc_res_math_orientation_t orientation = 0; orientation < YC_RES_MATH_ORIENTATION_COUNT; ++orientation) {
        yc_vid_texture_set_invalidate(&object->sets[orientation], renderer);
    }
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
