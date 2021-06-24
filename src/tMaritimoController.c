#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Transporte_Maritimo.h"
#include "auxiliar.h"
#include "tMaritimoController.h"
#include "parser.h"

static int tMaritimoController_saveAsText(char* path , LinkedList* pArrayListtMaritimo);

/** \brief Carga los datos del transporte maritimo desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListtMaritimo LinkedList*
 * \return int
 *
 */
int tMaritimoController_loadTMaritimoFromText(char* path , LinkedList* pArrayListtMaritimo)
{
	FILE* pArchivo;
	int retorno= 0;
	if(path!=NULL)
	{
		pArchivo=fopen(path,"r");
	}
	if(pArchivo != NULL && pArrayListtMaritimo != NULL)
	{
		retorno = parser_tMaritimoFromText(pArchivo,pArrayListtMaritimo);
		//printf("Archivo cargado correctamente\n");
	}
	fclose(pArchivo);
	return retorno;
}

int tMaritimoController_menuTAereo(LinkedList* pArrayListtMaritimo)
{
	int retorno = -1;
	int option;
	if(pArrayListtMaritimo != NULL)
	{
		retorno = 0;
		do{
			    	aux_getNumeroInt(&option,"1. Modificar Transporte Maritimo\n"
											  "2. Salir\n",
											  "Opción inválida\n",
											  1,2,2);
			        switch(option)
			        {
						case 1:
							tMaritimoController_edittMaritimo(pArrayListtMaritimo);
							break;
			        }
			    }while(option != 2);
	}
	return retorno;
}


int tMaritimoController_addTMaritimo(LinkedList* pArrayListtMaritimo)
{
	int retorno=-0;
	tMaritimo* pAuxiliarTmaritimo;
	float metros_cubicos;
	float valor;
	char mcubicosTxt[15];
	char valorTxt[15];

	if(pArrayListtMaritimo != NULL)
	{
		if(	aux_getNumeroFlotante(&metros_cubicos,"\nIngrese los m3 del contenedor: \n","\nERROR\n", 0, 100, 2) == 0 &&
			aux_getNumeroFlotante(&valor,"\nIngrese el valor del contenedor: \n","\nERROR\n", 0, 100000, 2) == 0 )
		{
			sprintf(mcubicosTxt,"%f",metros_cubicos);
			sprintf(valorTxt,"%f",valor);
			if(tMaritimo_newParametros(mcubicosTxt,valorTxt) >= 0)
			{
				pAuxiliarTmaritimo = (tMaritimo*)tMaritimo_newParametros(mcubicosTxt,valorTxt);
				ll_add(pArrayListtMaritimo,pAuxiliarTmaritimo);

				retorno = 1;
				tMaritimoController_saveAsText("Transporte_Maritimo.csv" ,pArrayListtMaritimo);
			}
		}
	}
	return retorno;
}

static int tMaritimoController_saveAsText(char* path , LinkedList* pArrayListtMaritimo)
{
	int retorno = 0;
	tMaritimo* auxtMaritimo;
	FILE* pFile=fopen(path,"w");
	if(pFile!=NULL && pArrayListtMaritimo !=NULL)
	{
		fprintf(pFile,"metrosCubicos,valor\n");
		for(int i= 0; i < ll_len(pArrayListtMaritimo); i++)
		{
			auxtMaritimo=ll_get(pArrayListtMaritimo,i);
			if(auxtMaritimo != NULL)
			{
				 fprintf(pFile,"%f,%f\n",auxtMaritimo->metros_cubicos,auxtMaritimo->valor );
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
int tMaritimoController_edittMaritimo(LinkedList* pArrayListtMaritimo)
{
	int retorno = 0;
	tMaritimo* auxTMaritimo;
	float metros_cubicos;
	float valor;
	int confirma;


	if(pArrayListtMaritimo != NULL)
	{
		auxTMaritimo = ll_get(pArrayListtMaritimo,0);
			if(auxTMaritimo != NULL)
			{
				printf("%s%15s\n","M3","Valor");
				tMaritimo_imprimir(auxTMaritimo);
				if(aux_getNumeroFlotante(&metros_cubicos,"\nIngrese los m3 del contenedor: \n","\nERROR\n", 0, 100, 2) == 0 &&
						aux_getNumeroFlotante(&valor,"\nIngrese el valor del contenedor: \n","\nERROR\n", 0, 100000, 2) == 0 )
				{
					if(aux_getNumeroInt(&confirma,"Confirma los cambios? 0=NO 1=SI\n","Opcion incorrecta.Reingrese.\n",0,1, 2)== 0 && confirma == 1)
					{
						tMaritimo_setMetrosCubicos(auxTMaritimo,metros_cubicos);
						tMaritimo_setValor(auxTMaritimo,valor);
						tMaritimoController_saveAsText("Transporte_Maritimo.csv" ,pArrayListtMaritimo);
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
