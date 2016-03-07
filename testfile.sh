#!/bin/bash

mkdir ./testfile
cd ./testfile
mkdir ./src
mkdir ./dest
cd ./src
mkdir ./src_a
mkdir ./src_b
mkdir ./src_c
base64 /dev/urandom  | head -c 8388608 > file_a
base64 /dev/urandom  | head -c 8388608 > file_b
base64 /dev/urandom  | head -c 8388608 > file_c
cd ./src_a
base64 /dev/urandom  | head -c 8388608 > file_a_a
base64 /dev/urandom  | head -c 8388608 > file_a_b
base64 /dev/urandom  | head -c 8388608 > file_a_c
cd ../src_b
base64 /dev/urandom  | head -c 8388608 > file_b_a
base64 /dev/urandom  | head -c 8388608 > file_b_b
base64 /dev/urandom  | head -c 8388608 > file_b_c
cd ../src_c
base64 /dev/urandom  | head -c 8388608 > file_c_a
base64 /dev/urandom  | head -c 8388608 > file_c_b
base64 /dev/urandom  | head -c 8388608 > file_c_c
