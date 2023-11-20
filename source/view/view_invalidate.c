#include <libycvid.h>
#include <libycenv.h>
#include <private.h>

void yc_vid_view_invalidate(yc_vid_view_t *view, const yc_vid_renderer_t *renderer) {
    view->level = NULL;

    yc_vid_view_objects_invalidate(&view->floor, renderer);
    yc_vid_view_objects_invalidate(&view->roofs, renderer);
    yc_vid_view_objects_invalidate(&view->objects, renderer);
}
