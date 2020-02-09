#!/usr/bin/env bash
name=$(date +%s)
mkdir $name
cp $(find -iname *.c) ./$name/
cd $name
tar czf allcfiles.tar *.c
mv allcfiles.tar ../
cd ../
rm -r $name

