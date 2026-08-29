#include <stdio.h>
#include <string.h>

typedef struct _indiceCep indiceCep;

struct _indiceCep
{
	char cep[8];
	long pos;
};

int main(int argc, char**argv)
{
	FILE *f;
	indiceCep e;
	int qt;
	int contador = 0;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]\n", argv[0]);
		return 1;
	}


	f = fopen("cep_ordenado.dat","rb");
    if (f == NULL) 
    {
        fprintf(stderr, "Erro ao abrir arquivo\n");
        return 1;
    }

	fseek(f,0,SEEK_END);
	long tamanhoBytes = ftell(f);
	long tamanhoRegistros = tamanhoBytes/sizeof(indiceCep);
	long inicio = 0;
	long fim = tamanhoRegistros-1;

    while(inicio <= fim)
    {
        long meio = (inicio+fim)/2;
	    fseek(f,meio*sizeof(indiceCep),SEEK_SET);
        qt = fread(&e,sizeof(indiceCep),1,f);
        contador += 1;
        if(strncmp(argv[1], e.cep, 8) == 0)
        {
            printf("CEP localizado: %ld\n%.8s\n", e.pos,e.cep);
            break;
        }
        else if(strncmp(argv[1], e.cep, 8) > 0)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    printf("Contador: %d\n", contador);
    fclose(f);
    return 0;
}

