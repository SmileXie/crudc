#include <stdio.h>
#include <stdlib.h>
#include "crudc.h"

int main()
{
    struct payloadname_s payload;
    struct keyname_s key;
    int ret;
    int i;

    modulename_objname_mgmt_init();

    key.student_no = 10;
    payload.age = 20;
    printf("add node: key %d, payload %d\n", key.student_no, payload.age);

    ret = modulename_objname_add(key, payload);
    if (ret != RET_SUCC) {
        printf("fail to add.\n");
    }

    ret = modulename_objname_get(key, &payload);
    if (ret != RET_SUCC) {
        printf("fail to get.\n");
        exit(-1);
    }

    printf("get node: key %d, payload %d\n", key.student_no, payload.age);

    for (i = 0; i < 20; i++) {
        key.student_no = i * 10;
        payload.age = i * 10 + 5;
        printf("add node: key %d, payload %d\n", key.student_no, payload.age);

        ret = modulename_objname_add(key, payload);
        if (ret != RET_SUCC) {
            printf("fail to add.\n");
        }

    }

    key.student_no = 30;

    ret = modulename_objname_get(key, &payload);
    if (ret != RET_SUCC) {
        printf("fail to get.\n");
        exit(-1);
    }

    printf("get node: key %d, payload %d\n", key.student_no, payload.age);

    key.student_no = 30;
    payload.age = 100;
    printf("set node: key %d, payload %d\n", key.student_no, payload.age);

    ret = modulename_objname_set(key, payload);
    if (ret != RET_SUCC) {
        printf("fail to set.\n");
        exit(-1);
    }

    ret = modulename_objname_get(key, &payload);
    if (ret != RET_SUCC) {
        printf("fail to get.\n");
        exit(-1);
    }

    printf("get node: key %d, payload %d\n", key.student_no, payload.age);

    key.student_no = 180;

    printf("del node: key %d\n", key.student_no);
    ret = modulename_objname_del(key);
    if (ret != RET_SUCC) {
        printf("fail to del.\n");
        exit(-1);
    }

    ret = modulename_objname_get(key, &payload);
    if (ret != RET_NOT_FOUND) {
        printf("fail to del.\n");
        exit(-1);
    }

    printf("get node: key %d not found ok\n", key.student_no);

    return 0;
}