#ifndef LIBYCVID_INCLUDE_TYPES_DATABASE_H
#define LIBYCVID_INCLUDE_TYPES_DATABASE_H

typedef struct yc_vid_database_fetch_resources_result {
    yc_res_pal_parse_result_t pal;
    yc_res_frm_parse_result_t frm;
} yc_vid_database_fetch_resources_result_t;

typedef yc_vid_status_t (yc_vid_database_fetch_resources_t)(
        yc_res_pro_object_type_t type,
        uint16_t sprite_idx,
        yc_vid_database_fetch_resources_result_t *result,
        void *context
);

typedef struct yc_vid_database_api {
    void *context;
    yc_vid_database_fetch_resources_t *fetch;
} yc_vid_database_api_t;

#endif //LIBYCVID_INCLUDE_TYPES_DATABASE_H
