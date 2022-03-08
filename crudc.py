#!/usr/bin/python3

import getopt, sys
import os
import shutil
import glob
import re
import json

DIR_TEMPLATE ='template'
DIR_OUTPUT = 'output'

NOT_REPLACE_FLAG = 'DONOT_REPLACE'

DEFAULT_CFG_FILE = 'config.json'

def crudc_replace_in_one_file(path, cfg):
    with open(path, 'r') as fp:
        file_string = fp.read()
        # file_string = re.sub('payloadname_s \{((.|\n)*?)\};', 'struct payloadname_s {\n    int payload_haha;\n};', file_string)
        file_string = re.sub('structname', cfg['structname'], file_string)
        file_string = re.sub('keyname', cfg['keyname'], file_string)
        file_string = re.sub('payloadname', cfg['payloadname'], file_string)
        file_string = re.sub('modulename', cfg['modulename'], file_string)

        with open(path, 'w') as fp:
            fp.write(file_string)


def crudc_replace_names(cfg):
    for file_path in glob.glob(DIR_OUTPUT + r'/**/*', recursive=True):
        if not os.path.isfile(file_path):
            continue
        crudc_replace_in_one_file(file_path, cfg)
        

def crudc_print_help():
    print('CRUDC Help:')
    print('    example: ./crudc.py --config=[config file path]')
    return

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], '-c:', ['config='])
    except getopt.GetoptError:
        crudc_print_help()
        return
    
    for opt_name, opt_value in opts:
        if opt_name in ('-c', '--config'):
            config_file = opt_value

    if 'config_file' not in locals():
        config_file = DEFAULT_CFG_FILE

    with open(config_file, 'r') as fp:
        file_string = fp.read()
        cfg = json.loads(file_string)

    shutil.rmtree(DIR_OUTPUT + r'/', ignore_errors=True)
    shutil.copytree(DIR_TEMPLATE + r'/', DIR_OUTPUT + r'/')

    crudc_replace_names(cfg)



if __name__ == "__main__":
    main()
