#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Função que estima o tempo restante. */
int evaluate(int total, int progress) {
	if(progress != 0) 		
		printf("Time remaining: %d seconds.\n", (int) ((5 * total)/progress - 0.5));
	 else
		/* Caso o número de bytes acumulado seja 0. */
		printf("Time remaining: stalled\n");	
	return 0;
}

int main(int argc, char const *argv[]) {
	int total = 0, progress = 0, bytes = 0, i = 0;	

	/* Realiza a leitura do total de bytes a ser transferido. */
	scanf("%d", &total);

	/* Imprime o total de bytes. */
	printf("Data size of %d bytes:\n", total);

	for(i = 1; total > 0; i++) {
		/* Realiza a leitura do número de bytes lido. */
		scanf("%d", &bytes);

		/* Incrementa o progresso da cópia. */
		progress += bytes;

		/* Atualiza o número de bytes restante. */
		total -= bytes;			

		/* A cada 5 segundos, realiza a estimativa de tempo. */
		if(i % 5 == 0) progress = evaluate(total, progress);		
	}

	printf("Total time: %d seconds\n", i-1);

	return 0;
}