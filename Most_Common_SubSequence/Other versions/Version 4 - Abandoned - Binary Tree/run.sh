rm -rf Results
mkdir Results
mkdir Results/Time
mkdir Results/Memory

sizes=(10 100 200 500 1000 5000 10000 20000 50000 80000)

for size in ${sizes[@]};
do
	for method in 1;
	do	
		#calculate memory used in iterative once for every size ONLY
		for i in 1;			
		do
			echo "Running size: ${size} for method: ${method} x${i}"		
			valgrind ./a.out ../Inputs/sequenceA_${i}_${size}.txt ../Inputs/sequenceB_${i}_${size}.txt $method > Results/res_${i}_${method}_${size}.txt 2>&1;
			cat Results/res_${i}_${method}_${size}.txt | grep "bytes allocated" | cut -d ' ' -f 11 > Results/Memory/mem_${i}_${method}_${size}.txt;	
			cat Results/res_${i}_${method}_${size}.txt | grep "Time_taken" | cut -d ':' -f2 > Results/Time/time_${i}_${method}_${size}.txt;	
		done

		#memory used is the same for all iterative runs of same size no need to calculate
		for i in {2..5}; 
		do	
			echo "Running size: ${size} for method: ${method} x${i}"		
			./a.out ../Inputs/sequenceA_${i}_${size}.txt ../Inputs/sequenceB_${i}_${size}.txt $method > Results/res_${i}_${method}_${size}.txt			
			cat Results/res_${i}_${method}_${size}.txt | grep "Time_taken" | cut -d ':' -f2 > Results/Time/time_${i}_${method}_${size}.txt;	
			#rm Results/1_${size}.txt				
		done
	done

	for method in 2;
	do				
		for i in {1..5}; 
		do	
			echo "Running size: ${size} for method: ${method} x${i}"		
			#valgrind ./a.out Inputs/sequenceA_${i}_${size}.txt Inputs/sequenceB_${i}_${size}.txt $method > Results/res_${i}_${method}_${size}.txt 2>&1;
			./a.out ../Inputs/sequenceA_${i}_${size}.txt ../Inputs/sequenceB_${i}_${size}.txt $method > Results/res_${i}_${method}_${size}.txt			
			#cat Results/res_${i}_${method}_${size}.txt | grep "bytes allocated" | cut -d ' ' -f 11 > Results/Memory/mem_${i}_${method}_${size}.txt;	
			cat Results/res_${i}_${method}_${size}.txt | grep "Time_taken" | cut -d ':' -f2 > Results/Time/time_${i}_${method}_${size}.txt;	
			#rm Results/1_${size}.txt				
		done
	done
done 