#include <stdio.h>
#include <stdlib.h>
#include "Transporte_Maritimo.h"
#include "auxiliar.h"
#include <string.h>

int tMaritimo_setMetrosCubicos(tMaritimo* this, float mCubicos)
{
	int retorno = 0;
	if(this != NULL && mCubicos >= 0)
	{
		this->metros_cubicos = mCubicos;
		retorno = 1;
	}
	return retorno;
}

int tMaritimo_getMetrosCubicos(tMaritimo* this, float* mCubicos)
{
	int retorno = 0;
	if(this != NULL && mCubicos != NULL)
	{
		*mCubicos = this->metros_cubicos;
		retorno = 1;
	}
	return retorno;
}

int tMaritimo_setValor(tMaritimo* this, float valor)
{
	int retorno = 0;
	if(this != NULL && valor >= 0)
	{
		this->valor = valor;
		retorno = 1;
	}
	return retorno;
}

int tMaritimo_getValor(tMaritimo* this, float* valor)
{
	int retorno = 0;
	if(this != NULL && valor != NULL)
	{
		*valor = this->valor;
		retorno = 1;
	}
	return retorno;
}

tMaritimo* tMaritimo_new(void)
{
	tMaritimo* aux = NULL;
	aux = malloc(sizeof(tMaritimo));
	return aux;
}

tMaritimo* tMaritimo_newParametros(char* mCubicos, char* valor)
{
	tMaritimo* aux = NULL;
	aux = tMaritimo_new();
	if(aux != NULL && mCubicos != NULL && valor != NULL)
	{
		if(aux_verificarFlotante(mCubicos) == 0 && aux_verificarFlotante(valor) == 0 )
		{
			if(tMaritimo_setMetrosCubicos(aux, atof(mCubicos)) == 1 && tMaritimo_setValor(aux,atof(valor)) == 1)
			{
				return aux;
			}
			else
			{
				tMaritimo_delete(aux);
			}
		}
	}
	return NULL;
}

void tMaritimo_delete(tMaritimo* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

int tMaritimo_imprimir(tMaritimo* this)
{
	int retorno=0;
	float metros_cubicos;
	float valor;

	if(this != NULL)
	{
		retorno = 1;
		tMaritimo_getMetrosCubicos(this,&metros_cubicos);
		tMaritimo_getValor(this,&valor);

		printf("%f%15f\n",metros_cubicos,valor);
	}
	return retorno;
}

float tMaritimo_CalcularFlete(tMaritimo* this, float metrosCubicos)
{
	float retorno = -1;
	float tamanio;
	float valor;
	float precioXmCubico;
	if(this != NULL && metrosCubicos > 0)
	{
		tMaritimo_getMetrosCubicos(this,&tamanio);
		tMaritimo_getValor(this,&valor);
		precioXmCubico = valor/tamanio;
		retorno = metrosCubicos * precioXmCubico;
	}
	return retorno;

}
