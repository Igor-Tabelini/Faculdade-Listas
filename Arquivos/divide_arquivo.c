#include <stdio.h>
#include <stdlib.h>
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
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char** argv)
{
    FILE *f;
	Endereco *buffer;
    char nome[30];

	f = fopen("cep.txt","rb");
	fseek(f,0,SEEK_END);
	long tamanhoBytes = ftell(f);
	long tamanhoRegistros = tamanhoBytes/sizeof(Endereco);
    long tamanhoBloco = tamanhoRegistros/8;
    long resto = tamanhoRegistros % 8;
    buffer = (Endereco*) malloc((tamanhoBloco + 1) * sizeof(Endereco));
	rewind(f);

    for(int i = 0; i < 8; i++)
    {
		sprintf(nome, "bloco%d.txt", i);
		FILE *saida = fopen(nome, "wb");

		if(i < resto)
		{
			fread(buffer, (tamanhoBloco + 1)* sizeof(Endereco), 1, f);
			qsort(buffer, tamanhoBloco + 1, sizeof(Endereco), compara);
			fwrite(buffer, (tamanhoBloco + 1)* sizeof(Endereco), 1, saida);
		}
		else
		{
			fread(buffer, (tamanhoBloco)* sizeof(Endereco), 1, f);
			qsort(buffer, tamanhoBloco, sizeof(Endereco), compara);
			fwrite(buffer, (tamanhoBloco)* sizeof(Endereco), 1, saida);
		}

		fclose(saida);
    }

	fclose(f);
	return 0;	
}