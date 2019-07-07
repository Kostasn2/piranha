#!python3

"""
This is a short script which keeps track of how many local builds were made
# and the overall line count of the project
"""

import sys
import os
import os.path
import shutil

SCRIPT_PATH = os.path.dirname(os.path.realpath(__file__))
ROOT_DIR = SCRIPT_PATH + "/../"
OUTPUT_DIR = ROOT_DIR + "/build/"
BINARY_PATH = ROOT_DIR + "/project/"
INCLUDE_DIR = ROOT_DIR + "/include/"

BINARY_NAME = 'piranha.lib'
PDB_NAME = 'piranha.pdb'


def log(level, data):
    print("{0}: {1}".format(level, data))


def generate_build_lib_path(architecture, mode):
    return OUTPUT_DIR + "/lib/{0}/{1}/".format(architecture, mode)


def generate_build_include_path():
    return OUTPUT_DIR + "/include/"


def genrate_binary_source_path(architecture, mode):
    return BINARY_PATH + "/{0}/{1}/".format(architecture, mode)


def clean_build():
    log("INFO", "Deleting last build...")

    try:
        shutil.rmtree(OUTPUT_DIR)
    except FileNotFoundError:
        log("INFO", "No previous build found, skipping clean")
    except OSError:
        log("ERROR", "Could not clean build, files are likely in use")
        sys.exit(1) # Return with an error


def make_directory(name):
    try:
        os.makedirs(name)
    except FileExistsError:
        log("WARNING", "Build folder was not cleaned")
        pass


def generate_dir():
    log("INFO", "Generating new build path")
    make_directory(OUTPUT_DIR)


def copy_binary(architecture, mode):
    binary_path = genrate_binary_source_path(architecture, mode)
    output_path = generate_build_lib_path(architecture, mode)

    make_directory(output_path)
    shutil.copy(binary_path + BINARY_NAME, output_path)

    try:
        shutil.copy(binary_path + PDB_NAME, output_path)
    except FileNotFoundError:
        log("INFO", "No PDB information found for this build")
        pass


def copy_include_files(architecture, mode):
    output_path = generate_build_include_path()
    make_directory(output_path)

    for root, sub_dirs, files in os.walk(INCLUDE_DIR):
        for file_entry in files:
            shutil.copy(os.path.join(root, file_entry.strip()), output_path)


if __name__ == "__main__":
    architecture = sys.argv[1]
    mode = sys.argv[2]

    clean_build()
    generate_dir()
    copy_binary(architecture, mode)
    copy_include_files(architecture, mode)
