#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]){
	int width = 16;
	char **data = (char **) malloc(sizeof(char *)*3);
	data[3] = (char *) malloc(sizeof(char)*width/2);
	data[2] = (char *) malloc(sizeof(char)*width);
	data[3][0] = 10;
	data[3][1] = 11;
	data[3][2] = 12;
	data[3][3] = 13;
	data[3][4] = 14;
	data[3][5] = 15;
	data[3][6] = 16;
	data[3][7] = 17;

	printf(">> %d\n", data[2][1]);

	printf("-> Size of char %d\n", (int) sizeof(char));

	memset(data[2], 9, width);
	printf("> %d\n", *(data[2]+0));

	// From smaller register to bigger one
	memcpy(data[2]+width/2, data[3], width/2);

	for (int i=0; i<width; i++){
		printf("<1> %d\n", data[2][i]);
	}
	printf(">>>\n");
	memset(data[2]+width/2, 5, width/2);

	// From bigger register to smaller one
	memcpy(data[3], data[2]+width/2, width/2);

	for (int i=0; i<width/2; i++){
		printf("<2> %d\n", data[3][i]);
	}
	return 0;
}