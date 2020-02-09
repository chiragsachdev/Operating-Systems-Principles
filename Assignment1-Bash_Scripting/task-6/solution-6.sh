#!/usr/bin/env bash

mkdir TXT
mkdir JPG
mkdir ZIP


tar xvf input.tar.gz --ungzip
mv ./input/*.txt ./TXT/
mv ./input/*.jpg ./JPG/
mv ./input/*.* ./ZIP/
mv ./input/* ./ZIP/
ls -R
tar -cvf rest_zipped.tar.gz ZIP --gzip

exit 0
