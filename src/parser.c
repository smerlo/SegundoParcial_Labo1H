#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Articulo.h"
#include "Posicion_arancelaria.h"
#include "Transporte_Aereo.h"
#include "Transporte_Maritimo.h"
#include <string.h>


static int idMaximoEncontradoPArancelaria(LinkedList* pArrayListpArancelaria, int* idMaximo);
static int findParancelariaByNomenclatura(LinkedList* pArrayListpArancelaria, char* nomenclatura);

int parser_ArticuloFromText(FILE* pFile , LinkedList* pArrayListArticulo, LinkedList* pArrayListpArancelaria)
{
	int retorno = -1;
	char idTxt[10];
	int id;
	char codigo[24];
	char nombre[128];
	char fob[15];
	char pArancelaria[48];
	char ancho[15];
	char alto[15];
	char profundidad[15];
	char peso[15];
	char paisFabricacion[48];
	int pArancelariaId;
	char pArancelariaIdTxt[10];

	Articulo* auxArticulo;

	if(pFile!=NULL && pArrayListArticulo != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
						 codigo, nombre, paisFabricacion, fob, peso ,alto, ancho, profundidad, pArancelaria)== 9)
			{
				if(ll_len(pArrayListArticulo) == 0)
				{
					id = 0;
				}
				else
				{
					idMaximoEncontradoPArancelaria(pArrayListArticulo, &id);
					id = id + 1;

				}
				sprintf(idTxt,"%d",id);
				pArancelariaId = findParancelariaByNomenclatura(pArrayListpArancelaria,  pArancelaria);
				if(pArancelariaId >= 0)
				{
					sprintf(pArancelariaIdTxt,"%d",pArancelariaId);
					auxArticulo = (Articulo*) articulo_newParametros(idTxt, codigo, nombre, fob, pArancelariaIdTxt, ancho, alto, profundidad, peso, paisFabricacion);
					if(auxArticulo != NULL && ll_add(pArrayListArticulo,auxArticulo)==0)
					{
						retorno = 0;
					}
				}

			}
		}while(!feof(pFile));
	}
	return retorno;
}


int parser_pArancelariaFromText(FILE* pFile , LinkedList* pArrayListpArancelaria)
{
	int retorno = -1;
	char idTxt[10];
	int id;
	char nArancelaria[48];
	char pSeguro[15];
	char pImportacion[15];
	char pTasa[15];
	char tipoLicencia[14];
	char tipoLicenciaTxt[2];

	pArancelaria* auxpArancelaria;

	if(pFile!=NULL && pArrayListpArancelaria != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
						nArancelaria, pSeguro, pImportacion, pTasa, tipoLicencia )== 5)
			{
				if(ll_len(pArrayListpArancelaria) == 0)
				{
					id = 0;
				}
				else
				{
					idMaximoEncontradoPArancelaria(pArrayListpArancelaria, &id);
					id = id + 1;

				}
				sprintf(idTxt,"%d",id);
				if(strncmp(tipoLicencia,"NO AUTOMATICA",14) == 0)
				{
					strcpy(tipoLicenciaTxt,"0");
				}

				auxpArancelaria = (pArancelaria*) pArancelaria_newParametros(idTxt, nArancelaria, pSeguro, pImportacion, pTasa, tipoLicenciaTxt);
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

static int idMaximoEncontradoPArancelaria(LinkedList* pArrayListpArancelaria, int* idMaximo)
{
	int retorno = -1;
	int i;
	int flag = 0;
	int idAuxMaximo;
	int idAuxiliar;
	pArancelaria* auxiliarPArancelaria;
	pArancelaria* auxPAran;
	if(pArrayListpArancelaria != NULL && idMaximo != NULL)
	{
		retorno=0;
		for(i=0;i<ll_len(pArrayListpArancelaria);i++)
		{
			auxPAran = ll_get(pArrayListpArancelaria,i);
			pArancelaria_getId(auxPAran,&idAuxiliar);
			if(!flag)
			{
				auxiliarPArancelaria = ll_get(pArrayListpArancelaria,i);
				pArancelaria_getId(auxiliarPArancelaria,&idAuxMaximo);
				flag = 1;
			}
			else if(idAuxiliar > idAuxMaximo)
			{
				idAuxMaximo = idAuxiliar;
			}

		}
		*idMaximo = idAuxMaximo;

	}
	return retorno;
}

static int findParancelariaByNomenclatura(LinkedList* pArrayListpArancelaria, char* nomenclatura)
{
	int retorno = -1;
	pArancelaria* auxPAran;
	if(pArrayListpArancelaria != NULL && nomenclatura != NULL)
	{
		for(int i=0;i<ll_len(pArrayListpArancelaria);i++)
		{
			auxPAran = ll_get(pArrayListpArancelaria,i);
			if(strncmp(auxPAran->nomenclatura_arancelaria,nomenclatura,48) == 0)
			{
				pArancelaria_getId(auxPAran, &retorno);
				break;
			}
		}
	}
	return retorno;
}

