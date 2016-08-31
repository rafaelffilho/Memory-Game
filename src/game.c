#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <search.h>
#include <time.h>
#include <signal.h>

void sigproc();

int main(int argc, char const *argv[]){
	
	srand(time(NULL));
	signal(SIGINT, sigproc);

	int matrix[6][5][2];
	int showed[6][5];
	int numbers[15];
	int temp;
	int t = 1;
	int i = 0;
	int fCard;
	int fCardx;
	int fCardy;
	int sCard;
	int sCardx;
	int sCardy;
	bool exit = false;

	while(!exit){


		if(i == 15)
			break;

		temp = rand() % 50;
		if(!sequential_search(numbers, 15, temp)){
			numbers[i] = temp;
			i++;
		}

	}

	for(int i = 0; i < 6; i++){
		for(int q = 0; q < 5; q++){
			matrix[i][q][0] = NULL;
			matrix[i][q][1] = 1;
			showed[i][q] = t;
			printf("%d\t", matrix[i][q]);
			t++;
		}
		printf("\n");
	}

	t = 0;

	for(int i = 0; i < 15; i++){

		while(!exit){

			int position = rand() % 30; 

			if(matrix[position / 5][position % 5][0] == NULL){
				matrix[position / 5][position % 5][0] = numbers[i];
				exit = true;
			}
		}
		exit = false;

		while(!exit){

			int position = rand() % 30; 

			if(matrix[position / 5][position % 5][0] == NULL){
				matrix[position / 5][position % 5][0] = numbers[i];
				exit = true;
			}
		}
		exit = false;
	}

	while(!exit){

		system("clear");

		printf("Numbers:\n");

		for(int i = 0; i < 6; i++){
			for(int q = 0; q < 5; q++){
				if(matrix[i][q][1] == 0){
					printf("%d\t", matrix[i][q][0]);	
				} else{
					printf("X\t");
				}
			
			}
			printf("\n");
		}

		printf("\n\nPosições:\n");

		for(int i = 0; i < 6; i++){
			for(int q = 0; q < 5; q++){
				printf("%d\t", showed[i][q]);
			}
			printf("\n");
		}

		printf("\nChoose 2 cards: ");
		scanf("%d %d", &fCard, &sCard);

		fCardx = (fCard - 1) % 5;
		fCardy = (fCard - 1) / 5;
		sCardx = (sCard - 1) % 5;
		sCardy = (sCard - 1) / 5;

		printf("First card: %d\nSecond card: %d\n", matrix[fCardy][fCardx][0], matrix[sCardy][sCardx][0]);

		if(matrix[fCardy][fCardx][0] == matrix[sCardy][sCardx][0]){
			printf("Acerto mizerarvi!\n");
			matrix[fCardy][fCardx][1] = 0;
			matrix[sCardy][sCardx][1] = 0;
		} else{
			printf("Erroouuu!\n");
		}

		printf("Press enter to continue.");

		getchar();
		getchar();
	}
	return 0;
}

void sigproc(){

	printf("\b\bByyaaee!!\n");
	exit(0);

}