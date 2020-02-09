#!/bin/bash

mkdir Assignment-1 && cd Assignment-1;
i=1
while [ $i -lt 11 ];
do
	mkdir Query-$i;
	touch Query-$i/response-$i.sh;
	let i=i+1
done
