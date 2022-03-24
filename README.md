# crudc
Automatically generate CRUD API code in C language. 

# example 

```
./crudc.py --config=[config file path]
```

and then file the codes in `output` directory.

# config file

A json format file defining fields to be replaced.

* modulename: a software module name that will be a prefix of symbol names.
* objname: the name of object to CRUD
* keyname: the name of key of object, that is used for unique field for searching the objects.
* key_struct: a C-lang struct defining the key of object.
* payload_strct: a C-lang struct defining the paylog of object.

E.g.,

```json
{
    "modulename": "stm",
    "objname": "student",
    "keyname": "stukey",
    "payloadname": "studata",
    "key_struct": "{\n    int class_no;\n    int student_no;\n};",
    "payload_struct": "{\n    char name[128];\n    unsigned char gender;\n    unsigned char age;\n};"
}
```
