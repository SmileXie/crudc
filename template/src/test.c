#include <stdio.h>
#include <stdlib.h>
#include "crudc.h"

int main()
{
    struct payloadname_s payload;
    struct keyname_s key;
    int ret;
    int i;

    modulename_structname_init();

    key.keyele = 10;
    payload.payload_data = 20;
    printf("add node: key %d, payload %d\n", key.keyele, payload.payload_data);

    ret = modulename_structname_add(key, payload);
    if (ret != RET_SUCC) {
        printf("fail to add.\n");
    }

    ret = modulename_structname_get(key, &payload);
    if (ret != RET_SUCC) {
        printf("fail to get.\n");
        exit(-1);
    }

    printf("get node: key %d, payload %d\n", key.keyele, payload.payload_data);

    for (i = 0; i < 20; i++) {
        key.keyele = i * 10;
        payload.payload_data = i * 10 + 5;
        printf("add node: key %d, payload %d\n", key.keyele, payload.payload_data);

        ret = modulename_structname_add(key, payload);
        if (ret != RET_SUCC) {
            printf("fail to add.\n");
        }

    }

    key.keyele = 30;

    ret = modulename_structname_get(key, &payload);
    if (ret != RET_SUCC) {
        printf("fail to get.\n");
        exit(-1);
    }

    printf("get node: key %d, payload %d\n", key.keyele, payload.payload_data);

    key.keyele = 30;
    payload.payload_data = 100;
    printf("set node: key %d, payload %d\n", key.keyele, payload.payload_data);

    ret = modulename_structname_set(key, payload);
    if (ret != RET_SUCC) {
        printf("fail to set.\n");
        exit(-1);
    }

    ret = modulename_structname_get(key, &payload);
    if (ret != RET_SUCC) {
        printf("fail to get.\n");
        exit(-1);
    }

    printf("get node: key %d, payload %d\n", key.keyele, payload.payload_data);

    key.keyele = 180;

    printf("del node: key %d\n", key.keyele);
    ret = modulename_structname_del(key);
    if (ret != RET_SUCC) {
        printf("fail to del.\n");
        exit(-1);
    }

    ret = modulename_structname_get(key, &payload);
    if (ret != RET_NOT_FOUND) {
        printf("fail to del.\n");
        exit(-1);
    }

    printf("get node: key %d not found ok\n", key.keyele);

    return 0;
}