#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crudc.h"
#include "list.h"

struct list_head modulename_objname_listhead;

int modulename_objname_mgmt_init(void)
{
    INIT_LIST_HEAD(&modulename_objname_listhead);
    
    return RET_SUCC;
}

struct objname_s* modulename_objname_find(struct keyname_s key)
{
    struct objname_s *node;

    list_for_each_entry(node, &modulename_objname_listhead, mountpoint) {
        if (memcmp(&(node->key), &key, sizeof(struct keyname_s)) == 0) {
            return node;
        }
    }

    return NULL;
}


int modulename_objname_add(struct keyname_s key, struct payloadname_s payload)
{
    struct objname_s *node;

    node = (struct objname_s *)malloc(sizeof(struct objname_s));
    if (node == NULL) {
        return RET_ALLOC_FAIL;
    }

    memcpy(&node->key, &key, sizeof(struct keyname_s));
    memcpy(&node->payload, &payload, sizeof(struct payloadname_s));

    list_add_tail(&node->mountpoint, &modulename_objname_listhead);

    return RET_SUCC;
}

int modulename_objname_del(struct keyname_s key)
{
    struct objname_s *node;

    node = modulename_objname_find(key);
    if (node == NULL) {
        return RET_NOT_FOUND;
    }

    list_del_init(&node->mountpoint);
    free(node);
    
    return RET_SUCC;
}

int modulename_objname_set(struct keyname_s key, struct payloadname_s payload)
{
    struct objname_s *node;

    node = modulename_objname_find(key);
    if (node == NULL) {
        return RET_NOT_FOUND;
    }

    memcpy(&node->payload, &payload, sizeof(struct payloadname_s));

    return RET_SUCC;
}

int modulename_objname_get(struct keyname_s key, struct payloadname_s *payload)
{
    struct objname_s *node;

    if (payload == NULL) {
        return RET_INVALID_PARAM;
    }

    node = modulename_objname_find(key);
    if (node == NULL) {
        return RET_NOT_FOUND;
    }

    memcpy(payload, &node->payload, sizeof(struct payloadname_s));

    return RET_SUCC;
}
