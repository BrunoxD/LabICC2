#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* Libera toda memória utlizada pela matriz. */
void freePuzzle(char **matrix) {
	int i;

	for(i = 0; i < 5; i++) free(matrix[i]);

	free(matrix);
}

/* Imprime a matriz do puzzle. */
void printPuzzle(char **matrix) {
	int i, j;

	for(i = 0; i < 5; i++) {
		for(j = 0; j < 5; j++) 
			printf("%c ", matrix[i][j]);						
		printf("\n");
	}
}

/* Realiza os movimentos no puzzle. */
int slidePuzzle(char **matrix, int *lin, int *col, char move) {
	switch(move) {
		case 'A':
			/* Caso inválido de movimento. */			
			if((*lin)-1 < 0) return 0;

			/* Desliza o caractere para a nova posição. */
			move = matrix[*lin][*col];
			matrix[*lin][*col] = matrix[(*lin)-1][*col];
			(*lin)--;
			matrix[*lin][*col] = move;

			break;		

		case 'B':		
			/* Caso inválido de movimento. */			
			if((*lin)+1 > 4) return 0;

			/* Desliza o caractere para a nova posição. */
			move = matrix[*lin][*col];
			matrix[*lin][*col] = matrix[(*lin)+1][*col];
			(*lin)++;
			matrix[*lin][*col] = move;

			break;

		case 'R':
			/* Caso inválido de movimento. */
			if((*col)+1 > 4) return 0;

			/* Desliza o caractere para a nova posição. */
			move = matrix[*lin][*col];
			matrix[*lin][*col] = matrix[*lin][(*col)+1];
			(*col)++;
			matrix[*lin][*col] = move;

			break;

		case 'L':
			/* Caso inválido de movimento. */
			if((*col)-1 < 0) return 0;

			/* Desliza o caractere para a nova posição. */
			move = matrix[*lin][*col];
			matrix[*lin][*col] = matrix[*lin][(*col)-1];
			(*col)--;
			matrix[*lin][*col] = move;

			break;
	}

	return 1;
}

/* Joga o puzzle. */
int playPuzzle(char **matrix, int *lin, int *col) {
	char move = 'Z';

	while(move != 'O') {
		move = fgetc(stdin);		
		if(isalpha(move) && slidePuzzle(matrix, lin, col, move) == 0) return 0;
	}

	return 1;
}

/* Lê a matriz do puzzle. */
char **readPuzzle(int *lin, int *col) {
	char c, **matrix = (char **) malloc(sizeof(char *) * 5);
	int i, j;

	/* Realiza a leitura da matriz 5x5. */
	for(i = 0; i < 5; i++) {
		matrix[i] = (char *) malloc(sizeof(char) * 6);
		for(j = 0; j < 6; j++) {
			c = fgetc(stdin);

			if(isalpha(c)) matrix[i][j] = c;
			
			/* Verifica se o caractere inserido é o vazio. */
			if(c == 32) {								
				matrix[i][j] = c;
				*lin = i;
				*col = j;
			}
		}			
		matrix[i][j-1] = '\0';

		/* Retira o caractere do carriage return. */
		fgetc(stdin);
	}

	return matrix;
}

int main(int argc, char const *argv[]) {
	int lin, col;
	
	/* Realiza a leitura da matriz do puzzle. */
	char **matrix = readPuzzle(&lin, &col);

	/* Joga o puzzle e obtém o resultado. */
	if(playPuzzle(matrix, &lin, &col)) 
		printPuzzle(matrix);
	else
		printf("This puzzle has no final configuration.\n");

	/* Desaloca memória utilizada pelo puzzle. */
	freePuzzle(matrix);

	return 0;	
}