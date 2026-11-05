#include <bplus.h>
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

int main() 
{
    bp_create_if_not_exists("cepplus.dat",8,300);
	BP_TREE* t = bp_open("cepplus.dat");
    FILE* f = fopen("cep.dat", "rb");
    unsigned long valor;
    int qt;
    Endereco e;
	int i = 0;
    
    qt = fread(&e,sizeof(Endereco),1,f);

	while(qt > 0)
	{
		valor = i * sizeof(Endereco);
		bp_insert(t,e.cep,valor);
        qt = fread(&e,sizeof(Endereco),1,f);
		i++;		
	}

	printf("1");

    bp_close(t);
	fclose(f);
    return 0;
}