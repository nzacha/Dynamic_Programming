#clean results directory
rm -rf time_results
mkdir time_results

echo "Running Time Routine"

export DIR="time_results"
export DIR_ITERATIVE=$DIR"/iterative"
export DIR_RECURSIVE=$DIR"/recursive"

mkdir $DIR
mkdir $DIR_ITERATIVE
mkdir $DIR_RECURSIVE

#dijkstra, independent_sets mostCommonSubSequebce
./scripts/collection/time_p1.sh

#chainmatrixmultiplication
./scripts/collection/time_p2.sh

#allpairshortestpath
#./scripts/collection/time_p3.sh

#knapsack
#./scripts/collection/time_p4.sh

#treeDiameter
#./scripts/collection/time_p6.sh

#kTrees
#./scripts/collection/time_p7.sh

#longestCommonSubSequence
./scripts/collection/time_p5.sh

echo "sending mail"
mail -s "Execution Time Collection Done" zicolas3@gmail.com <<< "Hello, execution has finished :)" 
