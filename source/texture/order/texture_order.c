#include <libycvid.h>
#include <private.h>

yc_vid_texture_order_t yc_vid_texture_order_from_object_type(yc_res_pro_object_type_t type) {
    switch (type) {
        case YC_RES_PRO_OBJECT_TYPE_ITEM:
            return YC_VID_TEXTURE_ORDER_ITEM;
        case YC_RES_PRO_OBJECT_TYPE_CRITTER:
            return YC_VID_TEXTURE_ORDER_CRITTER;
        case YC_RES_PRO_OBJECT_TYPE_SCENERY:
            return YC_VID_TEXTURE_ORDER_SCENERY;
        case YC_RES_PRO_OBJECT_TYPE_WALL:
            return YC_VID_TEXTURE_ORDER_WALL;
        case YC_RES_PRO_OBJECT_TYPE_TILE:
            return YC_VID_TEXTURE_ORDER_FLAT;
        case YC_RES_PRO_OBJECT_TYPE_MISC:
            return YC_VID_TEXTURE_ORDER_MISC;
        default:
            return YC_VID_TEXTURE_ORDER_ROOF;
    }
}
