#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

enum {
	PROGNAME,   // 0
	INPUTFILE,  // 1
	OUTPUTFILE, // 2
	NARGS       // 3
};

typedef struct DATA DATA;
struct DATA {	
	long double progress;
	long double total;
	clock_t timeTotal;
};

/* Função que estima o tempo restante. */
void *evaluate(void *d) {
	DATA *dt = (DATA *) d;
	clock_t after, before = clock();
	double secs;

	while(dt->total > 0) {
		
		after = clock();	
		secs = (after - before) / (CLOCKS_PER_SEC * 1.0);
		
		if(secs >= 1) {				
			before = clock();

			if(dt->progress != 0)			
				printf("Time remaining: %d seconds\n", (int) ceil((1.0 * dt->total) / dt->progress));
			else
				/* Caso o número de bytes acumulado seja 0. */
				printf("Time remaining: stalled\n");				

			dt->progress = 0;		
		} 
	}

	/* Calcula o tempo total final. */
	after = clock();
	before = dt->timeTotal;
	secs = (after - before) / (CLOCKS_PER_SEC * 1.0);

	/* Imprime o tempo total de cópia. */
	printf("Total time: %.lf seconds\n", secs);	
}

/* Função que realiza a cópia do arquivo. */
int copyFile(const char *input, const char *output) {
	FILE *fp_input, *fp_output;
	pthread_t *thread;	
	long double total = 0;
	char c;

	/* Abre o arquivo de leitura. */
	fp_input = fopen(input, "r");
	if (fp_input == NULL) {
		printf("Unable to open input file.\n");
		return 1;
	}

	/* Cria o arquivo de escrita. */
	fp_output = fopen(output, "w");
	if (fp_output == NULL) {
		printf("You do not have the correct permission.\n");
		return 1;
	}

	/* Realiza a leitura do total de bytes a ser transferido. */
	fseek(fp_input, 0, SEEK_END);
	total = ftell(fp_input);
	rewind(fp_input);

	/* Imprime o total de bytes. */
	printf("Data size of %.LF bytes:\n", total);

	/* Aloca memória para estrutura de dados. */
	DATA *dt = (DATA *) malloc(sizeof(DATA));

	/* Inicializa os dados. */
	dt->total = total;
	dt->progress = 0;	
	dt->timeTotal = clock();

	/* Aloca memória para a thread. */
	thread = (pthread_t *) malloc(sizeof(pthread_t));

	/* Cria a thread. */
	pthread_create(thread, NULL, evaluate, (void *) dt);

	/* Lê todos os bytes do arquivo e grava na saída. */
	while(!feof(fp_input)) {
		fscanf(fp_input, "%c", &c);
		fprintf(fp_output, "%c", c);				
		dt->progress++;
		dt->total--;		
	}

	fclose(fp_input);
	fclose(fp_output);
	pthread_exit(NULL);
	free(dt);
	free(thread);
}

int main(int argc, char const *argv[]) {
	/* Verifica se a quantidade de argumentos está correta. */
	if (argc != NARGS) {
		printf("Usage: %s input_filename output_filename\n", argv[PROGNAME]);		
		return 1;
	}

	/* Inicia o processo de cópia. */
	copyFile(argv[INPUTFILE], argv[OUTPUTFILE]);

	return 0;
}