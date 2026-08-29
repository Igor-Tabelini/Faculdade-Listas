#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	int contador;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]\n", argv[0]);
		return 1;
	}

	contador = 0;
	f = fopen("cep_ordenado.dat","rb");
    if (f == NULL) 
    {
        fprintf(stderr, "Erro ao abrir arquivo\n");
        return 1;
    }

	fseek(f,0,SEEK_END);
	long tamanhoBytes = ftell(f);
	long tamanhoRegistros = tamanhoBytes/sizeof(Endereco);
	long inicio = 0;
	long fim = tamanhoRegistros-1;

    while(inicio <= fim)
    {
        long meio = (inicio+fim)/2;
	    fseek(f,meio*sizeof(Endereco),SEEK_SET);
        qt = fread(&e,sizeof(Endereco),1,f);
        contador += 1;
        if(strncmp(argv[1], e.cep, 8) == 0)
        {
            printf("CEP localizado: %.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
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

