#include <libycvid.h>
#include <libycenv.h>
#include <private.h>

void yc_vid_view_destroy(yc_vid_view_t *view, const yc_vid_renderer_t *renderer) {
    view->level = NULL;

    yc_vid_view_objects_destroy(&view->floor, renderer);
    yc_vid_view_objects_destroy(&view->roofs, renderer);
    yc_vid_view_objects_destroy(&view->objects, renderer);
}
