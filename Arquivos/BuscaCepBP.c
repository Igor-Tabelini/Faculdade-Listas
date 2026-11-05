#include "bplus.h"
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

int main() {
    BP_TREE* t = bp_open("cepplus.dat");
    char chave[9];
    unsigned long valor;
    int procurado;
    scanf("%d",&procurado);
    sprintf(chave,"%08d",procurado);
    FILE* f = fopen("cep.dat", "rb");
    Endereco e;
    int qt;
    
    if(bp_find(t,chave,&valor))
    {
        fseek(f, valor, SEEK_SET);
        qt = fread(&e, sizeof(Endereco), 1, f);
        printf("%.8s\n", e.cep);
        printf("%.72s\n", e.bairro);
        printf("%.72s\n", e.cidade);
    }
    else {
        printf("Não encontrado\n");
    }
    fclose(f);
    bp_close(t);
    return 0;
}