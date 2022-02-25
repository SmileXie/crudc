#!/usr/bin/python3

import getopt, sys
import os
import shutil
import glob
import ntpath
import re

DIR_TEMPLATE ='template'
DIR_OUTPUT = 'output'

NOT_REPLACE_FLAG = 'DONOT_REPLACE'

def crudc_replace_in_one_file(path, module_name, struct_name, key_name, payload_name):
    with open(path, 'r') as fp:
        file_string = fp.read()
        file_string = re.sub('payloadname_s \{((.|\n)*?)\};', 'struct payloadname_s {\n    int payload_haha;\n};', file_string)
        file_string = re.sub('structname', struct_name, file_string)
        file_string = re.sub('keyname', key_name, file_string)
        file_string = re.sub('payloadname', payload_name, file_string)
        file_string = re.sub('modulename', module_name, file_string)

        with open(path, 'w') as fp:
            fp.write(file_string)


def crudc_replace_names(module_name, struct_name, key_name, payload_name):
    for file_path in glob.glob(DIR_OUTPUT + r'/**/*', recursive=True):
        if not os.path.isfile(file_path):
            continue
        crudc_replace_in_one_file(file_path, module_name, struct_name, key_name, payload_name)
        

def crudc_print_help():
    print('CRUDC Help:')
    print('    example: ./crudc.py --module=[modulename] --struct=[structname] --key=[keyname] --payload=[payloadname]')
    return

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], '-m:-s:-k:-p:', ['module=', 'struct=', 'key=', 'payload='])
    except getopt.GetoptError:
        crudc_print_help()
        return
    
    for opt_name, opt_value in opts:
        if opt_name in ('-m', '--module'):
            module_name = opt_value
            print("module_name=%s" % module_name)
        if opt_name in ('-s', '--struct'):
            struct_name = opt_value
            print("struct_name=%s" % struct_name)
        if opt_name in ('-k', '--key'):
            key_name = opt_value
            print("key_name=%s" % key_name)
        if opt_name in ('-p', '--payload'):
            payload_name = opt_value
            print("payload_name=%s" % payload_name)
    
    if 'module_name' not in locals():
        module_name = NOT_REPLACE_FLAG
    if 'struct_name' not in locals():
        struct_name = NOT_REPLACE_FLAG
    if 'key_name' not in locals():
        key_name = NOT_REPLACE_FLAG
    if 'payload_name' not in locals():
        payload_name = NOT_REPLACE_FLAG

    shutil.rmtree(DIR_OUTPUT + r'/', ignore_errors=True)
    shutil.copytree(DIR_TEMPLATE + r'/', DIR_OUTPUT + r'/')

    crudc_replace_names(module_name, struct_name, key_name, payload_name)



if __name__ == "__main__":
    main()
