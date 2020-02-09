#!/usr/bin/env bash
wget $1
tar xvf sample_data.tar
touch result.txt
touch smartzzzz
touch oszzzz
for file in `ls sample_data`
do
	smart_count=`grep -o 'smart' 'sample_data/'$file | wc -l`
	printf "%s smart %d\n" $file $smart_count >> result.txt 
	if [ $smart_count -gt "0" ]
	then
		echo $file >> smartzzzz
	fi
done

for file in `ls sample_data`
do
	os_count=`grep -o 'operating system' 'sample_data/'$file | wc -l`
	printf "%s operating system %d\n" $file $os_count >> result.txt
	if [ $os_count -gt "0" ]
	then
		echo $file >>oszzzz
	fi
done

mkdir smart 
mkdir OS

while IFS='' read -r line
do
	cp './sample_data/'$line ./smart/
done < smartzzzz

 while IFS='' read -r line
 do
 	cp './sample_data/'$line ./OS/
 done < oszzzz

rm oszzzz smartzzzz

exit 0
