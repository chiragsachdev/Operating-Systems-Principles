#!/usr/bin/env bash
cat /proc/cpuinfo | grep processor | uniq -c | wc -l > cpuinfo.txt
cat /proc/cpuinfo | grep 'core id' | cut -d : -f 2 | cut -d ' ' -f 2 >> cpuinfo.txt
cat /proc/cpuinfo | grep 'cache size' | cut -d : -f 2 | cut -d ' ' -f 2 >> cpuinfo.txt
