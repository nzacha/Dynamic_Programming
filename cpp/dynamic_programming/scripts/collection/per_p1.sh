#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000)
problems_1=("dijkstra" "mostCommonSubSequence" "independentSets")
methods=("iterative") #"recursive" 

ulimit -s unlimited

rm -f tmp.txt	

for problem in ${problems_1[@]}
do
	for method in ${methods[@]}
	do
	
		mkdir mem_results/${problem}
		mkdir mem_results/${problem}/${method}
					
		for size in ${sizes_1[@]}
		do
			for attempt in {1..3}
			do
				echo "per ${method} ${problem} ${size} ${attempt}" > log.txt
				echo "Running ${method} " ${problem} " size: ${size} x${attempt}"

				./executable.out ${problem} ${size} -${method} -q &
				pid=$!

				top -d 0.1 -bp ${pid} >> tmp.txt &
				top_pid=$!

				#wait for program end
				tail --pid=${pid} -f /dev/null
				#kill top_pid

				cat tmp.txt | grep ${pid} | tr -s ' ' | cut -d ' ' -f11 > mem_results/${problem}/${method}/per_${size}_${attempt}.txt

				rm tmp.txt
			done
		done
	done
done