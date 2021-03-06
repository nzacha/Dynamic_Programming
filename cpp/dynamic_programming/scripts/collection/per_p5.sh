#declare program arguments
sizes_5=(500 1000 1500 2000 2500 3000)
args_5=(50 500 5000 50000)
problems_5=("chainMatrixMultiplication")
methods=("iterative" "recursive") 

ulimit -s unlimited

rm -f tmp.txt	

for problem in ${problems_5[@]}
do
	for method in ${methods[@]}
	do
	
		mkdir mem_results/${problem}
		mkdir mem_results/${problem}/${method}
					
		for size in ${sizes_5[@]}
		do
			for arg in ${args_5[@]}
			do
				for attempt in {1..3}
				do
					echo "per ${method} ${problem} ${size} ${attempt}" > log.txt
					echo "Running ${method} " ${problem} " size: ${size} arg: x${attempt}"

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