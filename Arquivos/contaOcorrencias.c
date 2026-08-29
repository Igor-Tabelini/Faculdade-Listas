#include <stdio.h>

// stdout, stdin, stderr

int main(int argc, char** argv)
{
	FILE *entrada;
	int c;
    int gt[256] = {0};

	if(argc != 2)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
		return 1;
	}

	entrada = fopen(argv[1],"rb");
	if(!entrada)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	c = fgetc(entrada);
	while(c != EOF)
	{
        gt[c] += 1;
		c = fgetc(entrada);
	}

    for(int i = 0; i < 256; i++)
    {
        if(gt[i] > 0)
        {
            printf("Letra: %c\nQtd: %d\n", i, gt[i]);
        }
    }

	fclose(entrada);
	return 0;
}