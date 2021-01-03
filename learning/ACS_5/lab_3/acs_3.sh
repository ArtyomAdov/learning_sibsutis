#!/bin/bash
gcc -O2 -Wall -o key acs_3.c -lm;
./key RAM 64Kb 20;
./key RAM 1Mb 20;
./key HDD 4Mb 20;
./key flash 4Mb 20;
