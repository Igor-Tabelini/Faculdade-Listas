#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _indiceCep indiceCep;

struct _indiceCep
{
	char cep[8];
	long pos;
};

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
	return strncmp(((indiceCep*)e1)->cep,((indiceCep*)e2)->cep,8);
}

int main(int argc, char**argv)
{
	FILE *f, *saida;
	indiceCep *a;
	Endereco e;
	int linha, indice = 0;
	long posicao, qtd, metade;

	f = fopen("cep.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
	a = (indiceCep*) malloc(qtd*sizeof(indiceCep));
	rewind(f);

	linha = fread(&e, sizeof(Endereco), 1, f);

	while(linha > 0)
	{
		strncpy(a[indice].cep, e.cep, 8);
		a[indice].pos = indice;
		linha = fread(&e, sizeof(Endereco), 1, f);
		indice++;
	}
	
	qsort(a, qtd, sizeof(indiceCep), compara);
	saida = fopen("cep_ordenado.dat", "wb");
	fwrite(a, sizeof(indiceCep), qtd, saida);
	fclose(f);
	fclose(saida);
	free(a);
	return 0;
}

