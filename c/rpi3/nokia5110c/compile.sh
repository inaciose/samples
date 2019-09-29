#!/bin/bash
#Raspberry Pi Nokia 5110 display system info build script

g++ -Wall demo.c nokia5110.c -lbcm2835 -o demo

