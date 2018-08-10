#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"


int main()
{
	int dictionary_size;
	int edit_limit;
	int distance = 0;
	char* str = malloc(10000*sizeof(char));
	char* input = malloc(6002*sizeof(char));
	char* now = malloc(6002*sizeof(char));

	int how_many_recommended=0;
	char* name = malloc(13*sizeof(char));
	strcpy(name, "rec.txt");
	FILE* recommended = fopen(name, "w+");
	
	if(!scanf("%d", &dictionary_size)) return-1;
	if(!scanf("%d", &edit_limit)) return -2;
	if(!scanf("%s", input)) return -3;

	while(dictionary_size >= 1){
		if(!scanf("%s", now)) return -4;

		dictionary_size--;
		if(pruning(edit_limit, input, now) == 0){
			distance = edit_distance(input, now);
			if(distance <= edit_limit){
				how_many_recommended += 1;
				write_in_str(str, distance);
				strcat(str, now);
				fprintf(recommended, "%s\n", str);
			}
		}
	}

	fclose(recommended);
	suggestions_printer(how_many_recommended, name);

	free(str);
	free(input);
	free(now);
	remove(name);
	free(name);
	return 0;
}