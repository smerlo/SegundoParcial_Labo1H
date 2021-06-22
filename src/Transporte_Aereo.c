#include <stdio.h>
#include <stdlib.h>
#include "Transporte_Aereo.h"
#include "auxiliar.h"
#include <string.h>

static float calcularPrecioXpeso(float peso, float valorKg);
static float calcularPesoXvolumen(float cmCubicos, float cVolumetrica);

int tAereo_setConstanteVolumetrica(tAereo* this, float cVolumetrica)
{
	int retorno = 0;
	if(this != NULL && cVolumetrica >= 0)
	{
		this->constante_volumetrica = cVolumetrica;
		retorno = 1;
	}
	return retorno;
}

int tAereo_getConstanteVolumetrica(tAereo* this, float* cVolumetrica)
{
	int retorno = 0;
	if(this != NULL && cVolumetrica != NULL)
	{
		*cVolumetrica = this->constante_volumetrica;
		retorno = 1;
	}
	return retorno;
}

int tAereo_setPrecioKg(tAereo* this, float precioKg)
{
	int retorno = 0;
	if(this != NULL && precioKg >= 0)
	{
		this->precio_kg = precioKg;
		retorno = 1;
	}
	return retorno;
}

int tAereo_getPrecioKg(tAereo* this, float* precioKg)
{
	int retorno = 0;
	if(this != NULL && precioKg != NULL)
	{
		*precioKg = this->precio_kg;
		retorno = 1;
	}
	return retorno;
}

tAereo* tAereo_new(void)
{
	tAereo* aux = NULL;
	aux = malloc(sizeof(tAereo));
	return aux;
}

tAereo* tAereo_newParametros(char* cVolumetrica, char* precioKg)
{
	tAereo* aux = NULL;
	aux = tAereo_new();
	if(aux != NULL && cVolumetrica != NULL && precioKg != NULL)
	{
		if(aux_verificarFlotante(cVolumetrica) == 0 && aux_verificarFlotante(precioKg) == 0 )
		{
			if(tAereo_setConstanteVolumetrica(aux,atof(cVolumetrica)) == 1 && tAereo_setPrecioKg(aux, atof(precioKg)) == 1)
			{
				return aux;
			}
			else
			{
				tAereo_delete(aux);
			}
		}
	}
	return NULL;
}

void tAereo_delete(tAereo* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

int tAereo_imprimir(tAereo* this)
{
	int retorno=0;
	float cVolumetrica;
	float valorKg;

	if(this != NULL)
	{
		retorno = 1;
		tAereo_getConstanteVolumetrica(this,&cVolumetrica);
		tAereo_getPrecioKg(this,&valorKg);

		printf("%f%15f\n",cVolumetrica,valorKg);
	}
	return retorno;
}

float tAereo_CalcularFlete(tAereo* this, float cmCubicos, float peso)
{
	float retorno = -1;
	float cVolumetrica;
	float valorKg;
	float pesoCalculado;
	float precioPeso;
	float precioPesoCalculado;
	if(this !=NULL && cmCubicos > 0)
	{
		tAereo_getConstanteVolumetrica(this,&cVolumetrica);
		tAereo_getPrecioKg(this,&valorKg);
		precioPeso = calcularPrecioXpeso(peso, valorKg);
		pesoCalculado = calcularPesoXvolumen(cmCubicos, cVolumetrica);
		precioPesoCalculado = calcularPrecioXpeso(pesoCalculado, valorKg);
		if(precioPeso > precioPesoCalculado)
		{
			retorno = precioPeso;
		}
		else
		{
			retorno = precioPesoCalculado;
		}
	}
	return retorno;
}

static float calcularPrecioXpeso(float peso, float valorKg)
{
	float retorno = -1;
	if(peso > 0 && valorKg > 0)
	{
		retorno = peso * valorKg;
	}
	return retorno;
}

static float calcularPesoXvolumen(float cmCubicos, float cVolumetrica)
{
	float retorno = -1;
	if(cmCubicos > 0 && cVolumetrica > 0)
	{
		retorno = cmCubicos/cVolumetrica;
	}
	return retorno;
}
