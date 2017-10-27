# ecb-des

[![Build Status](https://travis-ci.org/geeksocket/ecb-des.svg?branch=master)](https://travis-ci.org/geeksocket/ecb-des) ![stability-experimental](https://img.shields.io/badge/stability-experimental-orange.svg) 

Command line tool in C (OpenMP) for Electronic Codebook block cipher using DES

### How to build

- Clone the repo in a directory
  ```sh
  $ git clone https://github.com/geeksocket/ecb-des
  $ cd ecb-des
  ```
- Compile using gcc
  ```sh
  $ gcc -lcrypt -fopenmp ecb-des.c -o ecb-des
  ```

### How to run

- Once you create the binary it can be run as
  ```sh
  $ ./ecb-des
  ```

## Licensing

ecb-des is licensed under GNU General Public License v3.0. See [LICENSE](https://github.com/geeksocket/ecb-des/blob/master/LICENSE) for the full license text.

