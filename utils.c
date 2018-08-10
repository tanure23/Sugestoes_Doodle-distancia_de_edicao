#include "utils.h" 

//Returns the absolute value of an integer
int mod(int x){
	return x<0 ? -x:x;
}

//Pruning is a helper function that analyzes if current dictionary...
//...word can be discarded upfront or if calculating edit distance...
//...is going to be necessary
int pruning(int edit_limit, char* input, char* now){
	int len_input = strlen(input);
	int len_now = strlen(now);

	/////////////////////////////////////////////////////
	//First case: pruning by size

	if(len_now > (len_input + edit_limit)){
		return 1;
	}
	else if(len_now < (len_input - edit_limit)){
		return 1;
	} 

	/////////////////////////////////////////////////////
	//0 means we cannot prune, while returning 1 means it can and will discard now
	return 0;
}

//Returns the minimum of three integers
int min(int a, int b, int c){
	if(a<=b){
		if(a<=c) return a;
		else return c;
	}
	else if(b<=a){
		if(b<=c) return b;
		else return c;
	}

	return c;
}

//This may be considered the most important function for the solution. It actually calculates the edit...
//...distance between two given words
int edit_distance(char* input, char* now){
	int len_input = strlen(input);
	int len_now = strlen(now);
	int i, j, distance=0;

	int** memo = malloc((len_input+1)*sizeof(int**));
	for(i=0; i<len_input+1; i++){
		memo[i] = malloc((len_now+1)*sizeof(int*));
	}

	for(i=0; i<len_input+1; i++){
		for(j=0; j<len_now+1; j++){
			if(i==0 || j==0){
				if(i==0){
					if(j==0) memo[i][j] = 0;
					else memo[i][j] = j;
				}
				if(j==0){
					if(i==0) memo[i][j] = 0;
					else memo[i][j] = i;
				}
			}

			else if(i>0 && j>0){
				if(input[i-1] == now[j-1]){
					memo[i][j] = memo[i-1][j-1];
				}
				else{
					memo[i][j] = (min(memo[i][j-1], memo[i-1][j], memo[i-1][j-1])) + 1;
				}
			}
		}
	}
	distance = memo[len_input][len_now];
	
	for(i=0; i<len_input+1; i++){
		free(memo[i]);
	}
	free(memo);
	return distance;
}

//Our solution involves concatenating a word to its respective edit distance so we can sort words by that distance.
//This is a helper function that just writes 4 chars into a string of your choice (dest).
//It is here so we can have control over the ammount of chars we will concatenate to a string later on.
//By adding '#', which is a char smaller than '0' on ASCii table (necessary not to mess up with the order...
//...because if we had 3###dccufmg and 30##dccufmg, the latter must always come second since...
//...we care about the number and 3 is smaller than 30), we ensure only 4 chars will ever be added.
char* write_in_str(char* dest, int distance){
	char* str = malloc(10*sizeof(char));
	if(distance != 0){
		int number_of_digits_ed = ((int)((ceil(log10(distance))+1)*sizeof(char))) -1;
		if(number_of_digits_ed==1){
			sprintf(str, "%d###", distance);
		}
		else if(number_of_digits_ed==2){
			sprintf(str, "%d##", distance);
		}
		else if(number_of_digits_ed==3){
			sprintf(str, "%d#", distance);
		}
		else if(number_of_digits_ed==4){
			sprintf(str, "%d", distance);
		}
		else if(number_of_digits_ed==0){
			sprintf(str, "%d###", distance);
		}
	}
	else{ //this if-else is made solely because log10() doesn't work with 0
		sprintf(str, "%d###", distance);
	}

	strcpy(dest, str);
	free(str);
	return dest;
}

//this is a utility function used by qsort, as it requires (const void*) types for...
//... its comparisons
//IMPORTANT!!
//It is rightful to AnyExample and I do not own any of its properties.
int compare(const void *a, const void *b){ 
    const char **pa = (const char **)a;
    const char **pb = (const char **)b;
    return strcmp(*pa, *pb); 
} 

//This is a basically a function that prints stuff on your terminal's screen.
//It does this by acessing a file, creating an array with its content, sorting...
//...and printing its elements in sorted order. As a consequence of our previous concatenation...
//... they will already be sorted by edit_distance and, in case of a tie between two distances,...
//... alphabetically
void suggestions_printer(int how_many, char* recommended_name){
	int i;
	FILE* in;

	char** suggestions = malloc(how_many*sizeof(char*));
	for(i=0; i<how_many; i++){
		suggestions[i] = malloc(6002*sizeof(char));
	}

	in = fopen(recommended_name, "r");

	for(i=0; i<how_many; i++){
		if(!fscanf(in, "%s", suggestions[i])) break;
	}

	qsort(suggestions, how_many, sizeof(char*), compare);

	for(i=0; i<how_many; i++){
		printf("%s\n", suggestions[i]+4);
	}


	for(i=0; i<how_many; i++){
		free(suggestions[i]);
	}
	free(suggestions);

	fclose(in);

}
