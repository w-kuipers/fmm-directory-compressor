# FMM Directory Compressor

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![PyPI release](https://img.shields.io/pypi/v/fmmpy-directory-compressor)](https://pypi.org/project/fmmpy-directory-compressor/)

Compress a directory into a single .FSA file. This library was build for the Filmage Media Manager to create project directory structures.

## Installation

### Linux
#### Debian/Ubuntu

    sudo apt-get install fmm-directory-compressor

### Python API

    pip install fmmpy-directory-compressor
    
 Note the `pip` refers to the Python 3 package manager. In environment where Python 2 is also available the correct command may be `pip3`.


## Usage

### CLI
#### Compress directory
    fmm-directory-compressor compress-directory path/to/src path/to/dst

You'll be asked to provide a filename. A .fsa file will be generated.
If you are using windows, the compression might fail when your source directory contains paths that are longer than 260 characters. These file paths can be ignored with the `--skip-long-paths` flag, but with this method these files/directories wont be present in the compressed file. 

#### Decompress directory
    fmm-directory-compressor decompress-directory path/to/file.fsa path/to/dst
You'll be asked to provide a root directory name. The directory structure will be rebuild.

### Python API
The python wrapper yields the same functionality as the CLI application. Just include the library and you're ready to go.

    import fmm_directory_compressor

    ## Compress directory
    fmm_directory_compressor.compress_directory("path/to/src", "yourfilename", "path/to/dst")

    ## Decompress directory
    fmm_directory_compressor.decompress_directory("root-directory-name", "path/to/yourfile.fsa", "path/to/dst")

## Building
#### CLI program and Python wrapper
The majority of this project uses CMake to build the executables. In the root/build directory run:

    cmake .. [options]
    cmake --build .

This will build a Debug executable.

#### JavaScript Wrapper
For building the JavaScript wrapper `emscripten` is required. Please refer to the [official installation manual](https://emscripten.org/docs/getting_started/downloads.html).
On windows you might want to run the command `emsdk activate latest --permanent` in the emsdk root folder.

To build the JavaScript wrapper run this command in the root directory:

    emcc --bind -o build/release/js/fmmjs-directory-compressor.js src/DC_js.cpp

#### Table of options:
| Option flag    |     Does  |
| ------------- | -----:|
| -DALL     | Builds everything |
| -DCLI   |   Builds only the Command Line Interface program |
| -DPY     |   Builds only the Python wrapper |


## Support

If you found a problem with the software, please [create an issue](https://github.com/w-kuipers/fmm-directory-compressor/issues) on GitHub.

## Maintainer

This project is maintained by [Wibo Kuipers](https://github.com/w-kuipers).

The source has been setup to work with Linux and Windows. Mac OS has not been tested yet.
