#include <libycvid.h>
#include <libycenv.h>
#include <stdlib.h>

yc_vid_status_t yc_vid_view_objects_destroy(yc_vid_view_objects_t *objects, yc_vid_renderer_t *renderer);

yc_vid_status_t yc_vid_view_destroy(yc_vid_view_t *view, yc_vid_renderer_t *renderer) {
    yc_vid_status_t status = YC_VID_STATUS_OK;

    // The owner of the world is responsible for its dismantle, so we just NULL the pointer.
    view->level = NULL;

    status = yc_vid_view_objects_destroy(&view->tiles, renderer);
    if (YC_VID_STATUS_OK != status) { return status; }

    view->tiles.count = 0;
    free(view->tiles.pointers);
    view->tiles.pointers = NULL;

    status = yc_vid_view_objects_destroy(&view->objects, renderer);
    if (YC_VID_STATUS_OK != status) { return status; }

    view->objects.count = 0;
    free(view->objects.pointers);
    view->objects.pointers = NULL;

    return status;
}

yc_vid_status_t yc_vid_view_objects_destroy(yc_vid_view_objects_t *objects, yc_vid_renderer_t *renderer) {
    for (size_t i = 0; i < objects->count; ++i) {
        yc_vid_view_object_t *object = &objects->pointers[i];

        for (size_t j = 0; j < object->count; ++j) {
            yc_vid_texture_set_t *set = &object->sets[j];

            for (size_t k = 0; k < set->count; ++k) {
                yc_vid_texture_handle_t *handle = &set->pointers[k];
                renderer->texture->destroy(handle);
            }

            set->count = 0;
            free(set->pointers);
            set->pointers = NULL;
        }

        object->count = 0;
        free(object->sets);
        object->sets = NULL;
    }

    return YC_VID_STATUS_OK;
}
