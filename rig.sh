#!/bin/sh
gcc rig.c -o rig

sleep 2

while true; do
  TAR=AAAAAAAA ./rig
  TAR=BBBBBBBB ./rig
  TAR=CCCCCCCC ./rig
  TAR=DDDDDDDD ./rig
done
