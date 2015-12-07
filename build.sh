#!/bin/bash

click chroot -a armhf -f ubuntu-sdk-15.04 run arm-linux-gnueabihf-gcc -Iinclude/ -o mtkfmcli src/*.c
