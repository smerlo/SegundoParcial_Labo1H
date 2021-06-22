#include <stdio.h>
#include <stdlib.h>
#include "Posicion_Arancelaria.h"
#include "auxiliar.h"
#include <string.h>


int pArancelaria_setId(pArancelaria* this, int id)
{
	int retorno = 0;
	if(this != NULL && id >= 0)
	{
		this->id = id;
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_getId(pArancelaria* this, int* id)
{
	int retorno = 0;
	if(this != NULL && id != NULL)
	{
		*id = this->id;
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_setNomenclaturaArancelaria(pArancelaria* this, char* nArancelaria)
{
	int retorno = 0;
	if(this != NULL && nArancelaria != NULL)
	{
		strcpy(this->nomenclatura_arancelaria, nArancelaria);
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_getNomenclaturaArancelaria(pArancelaria* this, char* nArancelaria)
{
	int retorno = 0;
	if(this != NULL && nArancelaria != NULL)
	{
		strcpy(nArancelaria, this->nomenclatura_arancelaria);
		retorno = 1;
	}
		return retorno;
}

int pArancelaria_setSeguro(pArancelaria* this, float seguro)
{
	int retorno = 0;
	if(this != NULL && seguro >= 0)
	{
		this->porcentaje_seguro = seguro;
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_getSeguro(pArancelaria* this, float* seguro)
{
	int retorno = 0;
	if(this != NULL && seguro != NULL)
	{
		*seguro = this->porcentaje_seguro;
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_setImportacion(pArancelaria* this, float pImportacion)
{
	int retorno = 0;
	if(this != NULL && pImportacion >= 0)
	{
		this->porcentaje_importacion = pImportacion;
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_getImportacion(pArancelaria* this, float* pImportacion)
{
	int retorno = 0;
	if(this != NULL && pImportacion != NULL)
	{
		*pImportacion = this->porcentaje_importacion;
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_setTasa(pArancelaria* this, float tasa)
{
	int retorno = 0;
	if(this != NULL && tasa >= 0)
	{
		this->pocentaje_tasaEstadistica = tasa;
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_getTasa(pArancelaria* this, float* tasa)
{
	int retorno = 0;
	if(this != NULL && tasa != NULL)
	{
		*tasa = this->pocentaje_tasaEstadistica;
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_setTipoLicencia(pArancelaria* this, int tLicencia)
{
	int retorno = 0;
	if(this != NULL && tLicencia >= 0)
	{
		this->tipo_licencia = tLicencia;
		retorno = 1;
	}
	return retorno;
}

int pArancelaria_getTipoLicencia(pArancelaria* this, int* tLicencia)
{
	int retorno = 0;
	if(this != NULL && tLicencia != NULL)
	{
		*tLicencia = this->tipo_licencia;
		retorno = 1;
	}
	return retorno;
}

/**
 * \brief Reserva un espacio en memoria para guardar una posicion arancelaria
 * \param Void (No recibe nada en los parametros)
 * \return Retorna un puntero al espacio de memoria donde guardará la posicion arancelaria
 */
pArancelaria* pArancelaria_new(void)
{
	pArancelaria* aux = NULL;
	aux = malloc(sizeof(pArancelaria));
	return aux;
}

pArancelaria* pArancelaria_newParametros(char* idStr, char* nArancelaria, char* pSeguroStr, char* pImportacionStr, char* pTasaStr, char* tipoLicenciaStr)
{
	pArancelaria* aux = NULL;
	aux = pArancelaria_new();
	if(aux != NULL && idStr != NULL && nArancelaria != NULL && pSeguroStr != NULL && pImportacionStr != NULL && pTasaStr != NULL && tipoLicenciaStr != NULL)
	{
		if(aux_verificarNumerica(idStr, 10) == 0 && aux_verificarFlotante(pSeguroStr) == 0 && aux_verificarFlotante(pImportacionStr) == 0 && aux_verificarFlotante(pTasaStr) == 0 && aux_verificarNumerica(tipoLicenciaStr, 1) == 0)
		{
			if(pArancelaria_setId(aux, atoi(idStr)) == 1 && pArancelaria_setNomenclaturaArancelaria(aux, nArancelaria) == 1 && pArancelaria_setSeguro(aux, atof(pSeguroStr)) == 1 &&
					pArancelaria_setImportacion(aux, atof(pImportacionStr)) == 1 && pArancelaria_setTasa(aux, atof(pTasaStr)) == 1 && pArancelaria_setTipoLicencia(aux, atoi(tipoLicenciaStr)) == 1)

			{
				return aux;
			}
			else
			{
				pArancelaria_delete(aux);
			}
		}
	}
	return NULL;
}

void pArancelaria_delete(pArancelaria* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

int pArancelaria_imprimir(pArancelaria* this)
{
	int retorno=0;
	int id;
	char nomenclatura_arancelaria[48];
	float porcentaje_seguro;
	float porcentaje_importacion;
	float pocentaje_tasaEstadistica;
	int tipo_licencia;

	if(this != NULL)
	{
		retorno = 1;
		pArancelaria_getId(this,&id);
		pArancelaria_getNomenclaturaArancelaria(this,nomenclatura_arancelaria);
		pArancelaria_getSeguro(this,&porcentaje_seguro);
		pArancelaria_getImportacion(this,&porcentaje_importacion);
		pArancelaria_getTasa(this,&pocentaje_tasaEstadistica);
		pArancelaria_getTipoLicencia(this, &tipo_licencia);

		printf("%d%30s%15f%15f%15f%15d\n",id,nomenclatura_arancelaria,porcentaje_seguro,porcentaje_importacion,pocentaje_tasaEstadistica,tipo_licencia);
	}
	return retorno;
}



float pArancelaria_CalcularCostoArgentino(pArancelaria* this, float baseImponible)
{
	float retorno = -1;
	float valorImportacion;
	float valorTasa;
	if(this != NULL && baseImponible > 0)
	{
		valorImportacion = (this->porcentaje_importacion * baseImponible) / 100;
		valorTasa = (this->pocentaje_tasaEstadistica * baseImponible) / 100;
		retorno = baseImponible + valorImportacion + valorTasa;
	}
	return retorno;
}
