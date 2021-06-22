#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Articulo.h"
#include "Posicion_arancelaria.h"
#include "Transporte_Aereo.h"
#include "Transporte_Maritimo.h"
#include <string.h>

int parser_ArticuloFromText(FILE* pFile , LinkedList* pArrayListArticulo)
{
	int retorno = -1;
	char id[10];
	char codigo[24];
	char nombre[128];
	char descripcion[256];
	char fob[15];
	char pArancelaria[15];
	char ancho[15];
	char alto[15];
	char profundidad[15];
	char peso[15];
	char paisFabricacion[48];

	Articulo* auxArticulo;

	if(pFile!=NULL && pArrayListArticulo != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
						id, codigo, nombre, descripcion, fob, pArancelaria, ancho, alto, profundidad, peso, paisFabricacion)== 11)
			{
				auxArticulo = (Articulo*) articulo_newParametros(id, codigo, nombre, descripcion, fob, pArancelaria, ancho, alto, profundidad, peso, paisFabricacion);
				if(auxArticulo != NULL && ll_add(pArrayListArticulo,auxArticulo)==0)
				{
					retorno = 0;
				}
			}
		}while(!feof(pFile));
	}
	return retorno;
}


int parser_pArancelariaFromText(FILE* pFile , LinkedList* pArrayListpArancelaria)
{
	int retorno = -1;
	char id[10];
	char nArancelaria[48];
	char pSeguro[15];
	char pImportacion[15];
	char pTasa[15];
	char tipoLicencia[2];

	pArancelaria* auxpArancelaria;

	if(pFile!=NULL && pArrayListpArancelaria != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
						id, nArancelaria, pSeguro, pImportacion, pTasa, tipoLicencia )== 6)
			{
				auxpArancelaria = (pArancelaria*) pArancelaria_newParametros(id, nArancelaria, pSeguro, pImportacion, pTasa, tipoLicencia);
				if(auxpArancelaria != NULL && ll_add(pArrayListpArancelaria,auxpArancelaria)==0)
				{
					retorno = 0;
				}
			}
		}while(!feof(pFile));
	}
	return retorno;
}

int parser_tAereoFromText(FILE* pFile , LinkedList* pArrayListtAereo)
{
	int retorno = -1;
	char cVolumetrica[10];
	char precioKg[10];

	tAereo* auxtAreo;

	if(pFile!=NULL && pArrayListtAereo != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],%[^\n]\n", cVolumetrica, precioKg )== 2)
			{
				auxtAreo = (tAereo*) tAereo_newParametros(cVolumetrica, precioKg);
				if(auxtAreo != NULL && ll_add(pArrayListtAereo,auxtAreo)==0)
				{
					retorno = 0;
				}
			}
		}while(!feof(pFile));
	}
	return retorno;
}

int parser_tMaritimoFromText(FILE* pFile , LinkedList* pArrayListtMaritimo)
{
	int retorno = -1;
	char mCubicos[20];
	char valor[20];

	tMaritimo* auxtMaritimo;

	if(pFile!=NULL && pArrayListtMaritimo != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],%[^\n]\n", mCubicos, valor )== 2)
			{
				auxtMaritimo = (tMaritimo*) tMaritimo_newParametros(mCubicos, valor);
				if(auxtMaritimo != NULL && ll_add(pArrayListtMaritimo,auxtMaritimo)==0)
				{
					retorno = 0;
				}
			}
		}while(!feof(pFile));
	}
	return retorno;

}


