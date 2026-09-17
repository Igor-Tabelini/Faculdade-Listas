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
	FILE *a, *b, *saida;
	Endereco ea, eb;
	char nome1[40];
	char nome2[40];
	int cont = 8;


	for(int i = 0; i < cont - 1; i+=2)
	{
		sprintf(nome1, "bloco%d.txt", i);
		sprintf(nome2, "bloco%d.txt", i+1);

		a = fopen(nome1,"rb");
		b = fopen(nome2,"rb");

		sprintf(nome1, "bloco%d.txt", cont);
		cont++;

		saida = fopen(nome1, "wb");

		fread(&ea,sizeof(Endereco),1,a);
		fread(&eb,sizeof(Endereco),1,b);

		// eof -> End Of File
		while(!feof(a) && !feof(b))
		{
			if(compara(&ea,&eb)<0) // ea < eb
			{
				fwrite(&ea,sizeof(Endereco),1,saida);
				fread(&ea,sizeof(Endereco),1,a);
			}
			else if(compara(&eb, &ea))
			{
				fwrite(&eb,sizeof(Endereco),1,saida);
				fread(&eb,sizeof(Endereco),1,b);
			}
			else
			{
				fwrite(&ea,sizeof(Endereco),1,saida);
				fread(&ea,sizeof(Endereco),1,a);
			}
		}

		while(!feof(a))
		{
			fwrite(&ea,sizeof(Endereco),1,saida);
			fread(&ea,sizeof(Endereco),1,a);		
		}
		
		while(!feof(b))
		{
			fwrite(&eb,sizeof(Endereco),1,saida);
			fread(&eb,sizeof(Endereco),1,b);		
		}

		fclose(a);
		fclose(b);
		fclose(saida);
	}

	return 0;
}

