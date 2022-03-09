#ifndef _CRUDC_H_
#define _CRUDC_H_

#include "list.h"

#define RET_SUCC            (0)
#define RET_NOT_FOUND       (1)

#define RET_ALLOC_FAIL      (-1)
#define RET_INVALID_PARAM   (-2)

struct keyname_s {
    int keyele; 
};

struct payloadname_s {
    int payload_data;
};

struct objname_s {
    struct list_head mountpoint;
    struct keyname_s key;
    struct payloadname_s payload;
};

int modulename_objname_mgmt_init(void);
struct objname_s* modulename_objname_find(struct keyname_s key);

int modulename_objname_add(struct keyname_s key, struct payloadname_s payload);
int modulename_objname_del(struct keyname_s key);
int modulename_objname_set(struct keyname_s key, struct payloadname_s payload);
int modulename_objname_get(struct keyname_s key, struct payloadname_s *payload);

#endif

