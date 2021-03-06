#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

unsigned short** sol;

char* getSequenceFromFile(char* filename, int fileSize){
	FILE *fp;
    char str[fileSize];
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return NULL;
    }

    fgets(str, fileSize, fp);     
    fclose(fp);

    char* sequence = (char*)calloc((strlen(str)+1), sizeof(char));
    strncpy(sequence, str, (size_t)(strlen(str)));

    return sequence;
}

void* initArray(unsigned short*** table, int height, int width){
	*table = (unsigned short**)calloc(height,sizeof(unsigned short*));

	for (int i=0; i<height; i++){
		(*table)[i] = (unsigned short*)calloc(width, sizeof(unsigned short));
	}

	for (int i=0; i<height; i++){
		for(int j=0; j<width; j++)
			(*table)[i][j]=0;
	}
	return NULL;
}

void* printArray(unsigned short** table, char* rows, char* columns){
	printf("\n");
	int height = strlen(rows)+1;
	int width = strlen(columns)+1;


	//Print Column Label
	printf("     ");
	for (int i=0; i<width; i++){
		printf("%c ",columns[i]);
	} 
	printf("\n");	

	printf("   ");
	for (int i=0; i<width; i++)
		printf("0 ");
	printf("\n");

	//Print Rows with Label
	for (int i=1; i<height; i++){
		printf("%c| ",rows[i-1]);
		for (int j=0; j<width; j++){
			printf("%d ",table[i][j]);
		}
		printf("\n");
	} 
	return NULL;
}

void* destroyArray(unsigned short** table, int height){
	for(int i=0; i<height; i++)
		free(table[i]);
	free(table);
	return NULL;
}

void* findMCSS_iterative(unsigned short** table, char* seqA, char* seqB){
	int height = strlen(seqA);
	int width = strlen(seqB);

	for(int i=1; i<=height; i++){
		for(int j=1; j<=width; j++){
			if(seqA[i-1] == seqB[j-1]){
				table[i][j] = table[i-1][j-1] +1;
				if(table[i][j]<table[i-1][j-1]){
					printf("Short overflow detected!\n");
					printf("Exiting...\n");
					exit(0);
				}
			}else if(table[i][j-1] <= table[i-1][j]){
				table[i][j] = table[i-1][j];
			}else{
				table[i][j] = table[i][j-1];
			}
		}
	}
	return NULL;
}

int max(int a, int b){
	if(a >= b)
		return a;
	return b;
}

int recur_findMCSS(char* seqA, char* seqB, int a, int b){	
	if(a<0 || b<0){
		//sol[i][j]=0; - not nescessary, table already initialized to 0
		return 0;
	}
	if(sol[a+1][b+1]!=0)
		return sol[a+1][b+1];

	if(seqA[a] == seqB[b]){
		sol[a+1][b+1] = (recur_findMCSS(seqA, seqB, a-1, b-1)+1);
	}else{
		sol[a+1][b+1] = max(recur_findMCSS(seqA, seqB, a-1, b),recur_findMCSS(seqA, seqB, a, b-1));
	}

	//printArray(sol, seqA, seqB);
	return sol[a+1][b+1];
}

void* findMCSS_recursive(unsigned short** table, char* seqA, char* seqB){
	int height = strlen(seqA);
	int width = strlen(seqB);
	recur_findMCSS(seqA, seqB, height-1, width-1);
	return NULL;
}


typedef struct node{
	struct node* next;
	int heightA;
	int heightB;
	int value;
}__attribute__((packed));

void* findMCSS_recursive_optimised(char* seqA, char* seqB){
	int height = strlen(seqA);
	int width = strlen(seqB);
	recur_findMCSS(seqA, seqB, height-1, width-1);
	return NULL;
}

void* printSolution_iterative(unsigned short** table, char* seqA, char* seqB){
	#ifdef DEBUG
	printf("\nPrinting solution for \"%s\" and \"%s\"\n", seqA, seqB);
	#endif

	int height = strlen(seqA);
	int width = strlen(seqB);

	char path[height];
	int c = 0;

	int j=width;
	for(int i=height; i>0 && j>0;){
		for(; i>0 && j>0;){
			if(table[i-1][j-1] == table[i-1][j] && table[i-1][j-1] == table[i][j-1] && table[i-1][j-1] == (table[i][j]-1)){
				path[c++]=seqA[i-1];
				i--;
				j--;
			}else if (table[i][j] == table[i-1][j]){
				i--;
			}else{
				j--;
			}
		}
	}
	path[c++]='\0';

	char mcss[c];
	for(int i=0; i<c; i++)
		mcss[i]=path[c-i-2];

	#ifdef DEBUG
		printf("A Most Common SubSequence is: %s\n", mcss);
	#endif
	printf("Solution.length:%ld\n", strlen(mcss));

	return NULL;
}

void* printSolution_recursive(unsigned short** table, char* seqA, char* seqB){
	#ifdef DEBUG
	printf("\nPrinting solution for \"%s\" and \"%s\"\n", seqA, seqB);
	#endif

	int height = strlen(seqA);
	int width = strlen(seqB);

	char path[height];
	int c = 0;

	int j=width;
	for(int i=height; i>0 && j>0;){
		for(; i>0 && j>0;){
			if(table[i-1][j-1] == (table[i][j]-1) && table[i][j-1] < table[i][j] && table[i-1][j] < table[i][j]){
				path[c++]=seqA[i-1];
				i--;
				j--;
			}else if (table[i][j] == table[i-1][j]){
				i--;
			}else{
				j--;
			}
		}
	}
	path[c++]='\0';

	char mcss[c];
	for(int i=0; i<c; i++)
		mcss[i]=path[c-i-2];

	#ifdef DEBUG
		printf("A Most Common SubSequence is: %s\n", mcss);
	#endif	
	printf("Solution.length:%ld\n", strlen(mcss));
	return NULL;
}

int main(int argc, char** argv){	
	if(argc!=5){
		printf("%s\n", "Correct Format: ./a.out [\"Sequence_A filename\"] [\"Sequence_B filename\"] ['iterative: 1' or 'recursive: 2'] ['File Size']\n");
		return 1;
	}

	char* seqA = getSequenceFromFile(argv[1], atoi(argv[4]));
	char* seqB = getSequenceFromFile(argv[2], atoi(argv[4]));
	if(!seqA || !seqB){
		printf("Unable to read Sequences from Files\n");
		return 1;
	}

	int method = atoi(argv[3]);

	if (method<1 || method>2){
		printf("Invalid method number!\n");
		return 1;
	}

	#ifdef DEBUG
		printf("Running \"%s\" with %d arguments \n", argv[0], argc);
		printf("Sequence A: %s\n", seqA);
		printf("Sequence B: %s\n", seqB);
	#else
		printf("Sequence_A:%ld\n", strlen(seqA));
		printf("Sequence_B:%ld\n", strlen(seqB));
	#endif

	initArray(&sol, strlen(seqA)+1, strlen(seqB)+1);

	//time starts
	clock_t time;

	if(method == 1){

		#ifdef DEBUG
			printf("Using Iterative (Bottom-Up) approach\n");
			printArray(sol, seqA, seqB);
		#endif

		time = clock();
		findMCSS_iterative(sol, seqA, seqB);
		time = clock() - time;

		#ifdef DEBUG
			printArray(sol, seqA, seqB);
		#endif
		printSolution_iterative(sol,seqA, seqB);
	
	}else if(method == 2){

		#ifdef DEBUG
			printf("Using Recursive (Top-Down) approach\n");
			//printHashMap(t);
		#endif

		time = clock();
		findMCSS_recursive(sol, seqA, seqB);		
		time = clock() - time;

		#ifdef DEBUG
			printArray(sol, seqA, seqB);
		#endif
		printSolution_recursive(sol,seqA, seqB);

	}

	destroyArray(sol, strlen(seqA)+1);
	free(seqA);
	free(seqB);
	
	double time_taken = ((double)time)/CLOCKS_PER_SEC; // calculate the elapsed time
	#ifdef DEBUG
		printf("\nThe program took %f seconds to execute\n", time_taken);	
	#else
		printf("Time_taken:%f\n", time_taken);	
	#endif

	return 0;
}
	