#clean results directory
#rm -rf time_results

echo "Running Time Routine"

export DIR="time_results"
export DIR_ITERATIVE=$DIR"/iterative"
export DIR_RECURSIVE=$DIR"/recursive"

mkdir $DIR
mkdir $DIR_ITERATIVE
mkdir $DIR_RECURSIVE

#dijkstra, independent_sets
#./scripts/collection/time_p1.sh

#knapsack
./scripts/collection/time_p2.sh

#treeDiameter kTrees
#./scripts/collection/time_p3.sh

#longestCommonSubSequence1D longestCommonSubSequence2D
#./scripts/collection/time_p4.sh

#chainmatrixmultiplication
#./scripts/collection/time_p5.sh

#mostCommonSubSequebce
#./scripts/collection/time_p6.sh

echo "sending mail"
mail -s "Execution Time Collection Done" zicolas3@gmail.com <<< "Hello, execution has finished :)" 
