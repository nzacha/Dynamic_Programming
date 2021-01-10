#declare program arguments
sizes_4=(8000 16000 24000 32000 40000 48000 56000)
args_4=(50 500 5000)
problems_4=("longestIncreasingSubSequence2D") #"longestIncreasingSubSequence1D" 
methods=("iterative" "recursive") 

ulimit -s unlimited

rm -f tmp.txt	

for problem in ${problems_4[@]}
do
	for method in ${methods[@]}
	do
	
		mkdir mem_results/${problem}
		mkdir mem_results/${problem}/${method}
					
		for size in ${sizes_4[@]}
		do
			for arg in ${args_4[@]}
			do
				for attempt in {1..3}
				do
					echo "per ${method} ${problem} ${size} ${arg} ${attempt}" > log.txt
					echo "Running ${method} " ${problem} " size: ${size} arg: ${arg} x${attempt}"

					./executable.out ${problem} ${size} ${arg} -${method} -q &
					pid=$!

					top -d 0.1 -bp ${pid} >> tmp.txt &
					top_pid=$!

					#wait for program end
					tail --pid=${pid} -f /dev/null
					#kill top_pid

					cat tmp.txt | grep ${pid} | tr -s ' ' | cut -d ' ' -f11 > mem_results/${problem}/${method}/per_${size}_${arg}_${attempt}.txt

					rm tmp.txt
				done
			done
		done
	done
done