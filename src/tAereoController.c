#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Transporte_Aereo.h"
#include "auxiliar.h"
#include "tAereoController.h"
#include "parser.h"

static int tAereoController_saveAsText(char* path , LinkedList* pArrayListtAereo);

/** \brief Carga los datos del transporte aereo desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListtAereo LinkedList*
 * \return int
 *
 */
int tAereoController_loadTAereoFromText(char* path , LinkedList* pArrayListtAereo)
{
	FILE* pArchivo;
	int retorno= 0;
	if(path!=NULL)
	{
		pArchivo=fopen(path,"r");
	}
	if(pArchivo != NULL && pArrayListtAereo != NULL)
	{
		retorno = parser_tAereoFromText(pArchivo,pArrayListtAereo);
		printf("Archivo cargado correctamente\n");
	}
	fclose(pArchivo);
	return retorno;
}

int tAereoController_menuTAereo(LinkedList* pArrayListtAereo)
{
	int retorno = -1;
	int option;
	if(pArrayListtAereo != NULL)
	{
		retorno = 0;
		do{
			    	aux_getNumeroInt(&option,"1. Modificar Transporte Aereo\n"
											  "2. Salir\n",
											  "Opción inválida\n",
											  1,2,2);
			        switch(option)
			        {
						case 1:
							tAereoController_editTAereo(pArrayListtAereo);
							break;
			        }
			    }while(option != 2);
	}
	return retorno;
}


int tAereoController_addTAereo(LinkedList* pArrayListtAereo)
{
	int retorno=-0;
	tAereo* pAuxiliarTaereo;
	float cVolumetrica;
	float valorKg;
	char cVolumetricaTxt[15];
	char valorKgTxt[15];

	if(pArrayListtAereo != NULL)
	{
		if(	aux_getNumeroFlotante(&cVolumetrica,"\nIngrese la constante volumetrica: \n","\nERROR\n", 0, 900000, 2) == 0 &&
			aux_getNumeroFlotante(&valorKg,"\nIngrese el valor del kg: \n","\nERROR\n", 0, 100000, 2) == 0 )
		{
			sprintf(cVolumetricaTxt,"%f",cVolumetrica);
			sprintf(valorKgTxt,"%f",valorKg);
			if(tAereo_newParametros(cVolumetricaTxt,valorKgTxt) >= 0)
			{
				pAuxiliarTaereo = (tAereo*)tAereo_newParametros(cVolumetricaTxt,valorKgTxt);
				ll_add(pArrayListtAereo,pAuxiliarTaereo);

				retorno = 1;
				tAereoController_saveAsText("Transporte_Aereo.csv" ,pArrayListtAereo);
			}
		}
	}
	return retorno;
}

static int tAereoController_saveAsText(char* path , LinkedList* pArrayListtAereo)
{
	int retorno = 0;
	tAereo* auxtAereo;
	FILE* pFile=fopen(path,"w");
	if(pFile!=NULL && pArrayListtAereo !=NULL)
	{
		fprintf(pFile,"constanteVolumetrica,valorKg\n");
		for(int i= 0; i < ll_len(pArrayListtAereo); i++)
		{
			auxtAereo=ll_get(pArrayListtAereo,i);
			if(auxtAereo != NULL)
			{
				 fprintf(pFile,"%f,%f\n",auxtAereo->constante_volumetrica,auxtAereo->precio_kg);
			}
		}
		fclose(pFile);

		retorno = 1;
	}
	return retorno;
}

/** \brief Modificar datos de posicion arancelaria
 * \param pArrayListpArancelaria LinkedList*
 * \return int

 */
int tAereoController_editTAereo(LinkedList* pArrayListtAereo)
{
	int retorno = 0;
	tAereo* auxTAereo;
	float cVolumetrica;
	float valorKg;
	int confirma;


	if(pArrayListtAereo != NULL)
	{
		auxTAereo = ll_get(pArrayListtAereo,0);
			if(auxTAereo != NULL)
			{
				printf("%s%15s\n","cVolumetrica","ValorKg");
				tAereo_imprimir(auxTAereo);
				if(aux_getNumeroFlotante(&cVolumetrica,"\nIngrese la constante volumetrica: \n","\nERROR\n", 0, 900000, 2) == 0 &&
					aux_getNumeroFlotante(&valorKg,"\nIngrese el valor del kg: \n","\nERROR\n", 0, 100000, 2) == 0 )
				{
					if(aux_getNumeroInt(&confirma,"Confirma los cambios? 0=NO 1=SI\n","Opcion incorrecta.Reingrese.\n",0,1, 2)== 0 && confirma == 1)
					{
						tAereo_setConstanteVolumetrica(auxTAereo,cVolumetrica);
						tAereo_setPrecioKg(auxTAereo,valorKg);
						tAereoController_saveAsText("Transporte_Aereo.csv" ,pArrayListtAereo);
						printf("El transporte maritimo fue editado correctamente.\n\n");
					}
					else
					{
						printf("No se ha realizado ningun cambio.\n\n");
					}
					retorno = 1;
				}
			}
	}
	return retorno;
}

