#include <libycvid.h>

void yc_vid_viewport_tick(void) {
    yc_res_map_t *map = NULL;
    yc_res_map_invalidate(map);

    yc_env_world_t *world = NULL;
    yc_env_world_init(map, &world);

    yc_env_world_tick(world);
}
