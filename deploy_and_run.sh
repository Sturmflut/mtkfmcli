#!/bin/bash

adb push mtkfmcli /tmp
adb shell /tmp/mtkfmcli $@
