#!/usr/bin/env bash
pids=(`ps -uf | grep infloop | grep -v -e '/bin/grep' | tr -s ' ' | cut -d ' ' -f 2`)
for pid in ${pids[@]:1}
do
	kill $pid
done
echo 'Done'
exit 0
