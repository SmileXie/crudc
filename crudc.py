#!/usr/bin/python3

import getopt, sys
import os
import shutil
import glob
import ntpath

DIR_TEMPLATE ='template'
DIR_OUTPUT = 'output'

NOT_REPLACE_FLAG = 'DONOT_REPLACE'

def crudc_replace_names(module_name, struct_name, key_name, payload_name):
    for input_path in glob.glob(DIR_TEMPLATE + r'/**/*', recursive=True):
        if not os.path.isfile(input_path):
            continue

        with open(input_path, 'r') as read_fp:
            output_path = input_path.replace(DIR_TEMPLATE, DIR_OUTPUT)
            os.makedirs(os.path.dirname(output_path), exist_ok=True)
            with open(output_path, 'w') as write_fp:
                for line in read_fp:
                    line = line.replace('modulename', module_name) if module_name != NOT_REPLACE_FLAG else line 
                    line = line.replace('structname', struct_name) if struct_name != NOT_REPLACE_FLAG else line
                    line = line.replace('keyname', key_name) if key_name != NOT_REPLACE_FLAG else line
                    line = line.replace('payloadname', payload_name) if payload_name != NOT_REPLACE_FLAG else line
                    write_fp.write(line)

def crudc_print_help():
    print('CRUDC Help:')
    print('    example: ./crudc.py --module=[modulename] --struct=[structname] --key=[keyname] --payload=[payloadname]')
    return

def crudc_replace_struct(struct_name):
    # regular exp: payloadname_s((.|\n)*)\};
    pass

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

    crudc_replace_names(module_name, struct_name, key_name, payload_name)



if __name__ == "__main__":
    main()
