#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Posicion_arancelaria.h"
#include "auxiliar.h"
#include "pArancelariaController.h"
#include "parser.h"

static int idMaximoEncontrado(LinkedList* pArrayListpArancelaria, int* idMaximo);
static int pArancelariaController_saveAsText(char* path , LinkedList* pArrayListpArancelaria);

/** \brief Carga los datos de las Posiciones Arancelarias desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListpArancelaria LinkedList*
 * \return int
 *
 */
int pArancelariaController_loadPArancelariaFromText(char* path , LinkedList* pArrayListpArancelaria)
{
	FILE* pArchivo;
	int retorno= 0;
	if(path!=NULL)
	{
		pArchivo=fopen(path,"r");
	}
	if(pArchivo != NULL && pArrayListpArancelaria != NULL)
	{
		retorno = parser_pArancelariaFromText(pArchivo,pArrayListpArancelaria);
		printf("Archivo cargado correctamente\n");
	}
	fclose(pArchivo);
	return retorno;
}

int pArancelariaController_menuPArancelaria(LinkedList* pArrayListpArancelaria)
{
	int retorno = -1;
	int option;
	if(pArrayListpArancelaria != NULL)
	{
		retorno = 0;
		do{
			    	aux_getNumeroInt(&option,"1. Alta Posicion Arancelaria\n"
											  "2. Modificar Posicion Arancelaria\n"
											  "3. Eliminar Posicion Arancelaria\n"
											  "4. Salir\n",
											  "Opción inválida\n",
											  1,4,2);
			        switch(option)
			        {

						case 1:
							pArancelariaController_addPArancelaria(pArrayListpArancelaria);
							break;
						case 2:
							pArancelariaController_editpArancelaria(pArrayListpArancelaria);
							break;
						case 3:
							pArancelariaController_removePArancelaria(pArrayListpArancelaria);
							break;
			        }
			    }while(option != 4);
	}
	return retorno;
}

/** \brief Alta de articulos
 * \param pArrayListArticulo LinkedList*
 * \return int
 *
 */
int pArancelariaController_addPArancelaria(LinkedList* pArrayListpArancelaria)
{
	int retorno=-0;
	pArancelaria* pAuxiliarpArancelaria;
	int id;
	char nomenclatura[48];
	float porcentaje_seguro;
	float porcentaje_importacion;
	float pocentaje_tasaEstadistica;
	int tipo_licencia;
	char idTxt[15];
	char seguroTxt[15];
	char importacionTxt[15];
	char tasaTxt[15];
	char licenciaTxt[15];

	if(pArrayListpArancelaria != NULL)
	{
		if(aux_getString(nomenclatura,24,"\nIngrese la nomenclatura arancelaria: \n","\nERROR\n",2) == 0 &&
			aux_getNumeroFlotante(&porcentaje_seguro,"\nIngrese el % de seguro: \n","\nERROR\n", 0, 100, 2) == 0 &&
			aux_getNumeroFlotante(&porcentaje_importacion,"\nIngrese el % de importacion: \n","\nERROR\n", 0, 100, 2) == 0 &&
			aux_getNumeroFlotante(&pocentaje_tasaEstadistica,"\nIngrese el % de tasa estadistica: \n","\nERROR\n", 0, 100, 2) == 0 &&
			aux_getNumeroInt(&tipo_licencia,"Ingrese el tipo de licencia:\n", "Valor incorrecto\n",0, 1,2) == 0 )
		{
			if(ll_len(pArrayListpArancelaria) == 0)
			{
				id = 0;
			}
			else
			{
				idMaximoEncontrado(pArrayListpArancelaria, &id);
				id = id + 1;

			}
			sprintf(idTxt,"%d",id);
			sprintf(seguroTxt,"%f",porcentaje_seguro);
			sprintf(importacionTxt,"%f",porcentaje_importacion);
			sprintf(tasaTxt,"%f",pocentaje_tasaEstadistica);
			sprintf(licenciaTxt,"%d",tipo_licencia);

			if(pArancelaria_newParametros(idTxt,nomenclatura,seguroTxt,importacionTxt,tasaTxt,licenciaTxt) >= 0)
			{
				pAuxiliarpArancelaria = (pArancelaria*)pArancelaria_newParametros(idTxt,nomenclatura,seguroTxt,importacionTxt,tasaTxt,licenciaTxt);
				ll_add(pArrayListpArancelaria,pAuxiliarpArancelaria);

				retorno = 1;
				printf("Articulo creado correctamente con ID %d\n\n", id);
				pArancelariaController_saveAsText("Posiciones_Arancelarias.csv" ,pArrayListpArancelaria);
			}
		}
	}
	return retorno;
}

static int idMaximoEncontrado(LinkedList* pArrayListpArancelaria, int* idMaximo)
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

static int pArancelariaController_saveAsText(char* path , LinkedList* pArrayListpArancelaria)
{
	int retorno = 0;
	pArancelaria* auxpArancelaria;
	FILE* pFile=fopen(path,"w");
	if(pFile!=NULL && pArrayListpArancelaria !=NULL)
	{
		fprintf(pFile,"id,nomenclatura,seguro,tasa_importacion,tasa_estadistica,licencia\n");
		for(int i= 0; i < ll_len(pArrayListpArancelaria); i++)
		{
			auxpArancelaria=ll_get(pArrayListpArancelaria,i);
			if(auxpArancelaria != NULL)
			{
				 fprintf(pFile,"%d,%s,%f,%f,%f,%d\n",auxpArancelaria->id,auxpArancelaria->nomenclatura_arancelaria,
						 auxpArancelaria->porcentaje_seguro,auxpArancelaria->porcentaje_importacion,auxpArancelaria->pocentaje_tasaEstadistica,auxpArancelaria->tipo_licencia);
			}
		}
		fclose(pFile);

		retorno = 1;
	}
	return retorno;
}

static int pArancelariaController_ListarPosiciones(LinkedList* pArrayListpArancelaria)
{
	pArancelaria* auxPArancelaria;
	int retorno = 0;
	if(pArrayListpArancelaria != NULL)
	{
		printf("%s%15s%15s%15s%15s%15s\n","ID","NOMENCLATURA","SEGURO","% IMPORTACION","T. ESTADISTICA","LICENCIA");
		for(int i=0; i < ll_len(pArrayListpArancelaria); i++)
		{
			auxPArancelaria= (pArancelaria*)ll_get(pArrayListpArancelaria,i);
			pArancelaria_imprimir(auxPArancelaria);
		}
		printf("\n\n");
		retorno = 1;
	}
	return retorno;
}

/**
 * \brief Busca en la lista una posicion arancelaria por ID
 * \param pArrayListpArancelaria LinkedList* Puntero a la lista que será evaluada
 * \param Id. Id del articulo a buscar
 * \return int Devuelve la ubicacion donde se encuentra el id, -1 si no lo encuentra y 0 si hay error
 */
int pArancelariaController_buscarPorId(LinkedList* pArrayListpArancelaria, int id)
{
	int retorno=0;
	int i;
	int idAux;
	pArancelaria* auxPArancelaria;

	if(pArrayListpArancelaria != NULL && id >= 0)
	{
		retorno = -1;
		for(i=0;i<ll_len(pArrayListpArancelaria);i++)
		{
			auxPArancelaria = ll_get(pArrayListpArancelaria,i);
			pArancelaria_getId(auxPArancelaria, &idAux);
			if( idAux == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Modificar datos de posicion arancelaria
 * \param pArrayListpArancelaria LinkedList*
 * \return int

 */
int pArancelariaController_editpArancelaria(LinkedList* pArrayListpArancelaria)
{
	int retorno = 0;
	pArancelaria* auxPArancelaria;
	int indicepArancelaria;
	int id;
	char nomenclatura[48];
	float porcentaje_seguro;
	float porcentaje_importacion;
	float pocentaje_tasaEstadistica;
	int tipo_licencia;
	int confirma;


	if(pArrayListpArancelaria != NULL)
	{
		pArancelariaController_ListarPosiciones(pArrayListpArancelaria);
		if(aux_getNumeroInt(&id,"Ingrese el ID que desea modificar\n","Id incorrecto, reingrese.\n",0,ll_len(pArrayListpArancelaria), 2)== 0)
		{
			indicepArancelaria = pArancelariaController_buscarPorId(pArrayListpArancelaria, id);
			auxPArancelaria = ll_get(pArrayListpArancelaria,indicepArancelaria);
			if(auxPArancelaria != NULL)
			{
				pArancelaria_imprimir(auxPArancelaria);
				if(aux_getString(nomenclatura,24,"\nIngrese la nomenclatura arancelaria: \n","\nERROR\n",2) == 0 &&
						aux_getNumeroFlotante(&porcentaje_seguro,"\nIngrese el % de seguro: \n","\nERROR\n", 0, 100, 2) == 0 &&
						aux_getNumeroFlotante(&porcentaje_importacion,"\nIngrese el % de importacion: \n","\nERROR\n", 0, 100, 2) == 0 &&
						aux_getNumeroFlotante(&pocentaje_tasaEstadistica,"\nIngrese el % de tasa estadistica: \n","\nERROR\n", 0, 100, 2) == 0 &&
						aux_getNumeroInt(&tipo_licencia,"Ingrese el tipo de licencia:\n", "Valor incorrecto\n",0, 1,2) == 0 )
				{
					if(aux_getNumeroInt(&confirma,"Confirma los cambios? 0=NO 1=SI\n","Opcion incorrecta.Reingrese.\n",0,1, 2)== 0 && confirma == 1)
					{
						pArancelaria_setNomenclaturaArancelaria(auxPArancelaria,nomenclatura);
						pArancelaria_setSeguro(auxPArancelaria,porcentaje_seguro);
						pArancelaria_setImportacion(auxPArancelaria,porcentaje_importacion);
						pArancelaria_setTasa(auxPArancelaria,pocentaje_tasaEstadistica);
						pArancelaria_setTipoLicencia(auxPArancelaria,tipo_licencia);

						pArancelariaController_saveAsText("Posiciones_Arancelarias.csv" ,pArrayListpArancelaria);
						printf("La posicion arancelaria fue editada correctamente.\n\n");
					}
					else
					{
						printf("No se ha realizado ningun cambio.\n\n");
					}
					retorno = 1;
				}
			}
		}
	}
	return retorno;
}

int pArancelariaController_removePArancelaria(LinkedList* pArrayListpArancelaria)
{
	int retorno = 0;
	int indicepArancelaria;
	int id;
	int confirma;
	pArancelaria* auxpArancelaria;
	if(pArrayListpArancelaria != NULL)
	{
		pArancelariaController_ListarPosiciones(pArrayListpArancelaria);
		if(aux_getNumeroInt(&id,"Ingrese el ID del articulo a eliminar\n","Id incorrecto, reingrese.\n",0,ll_len(pArrayListpArancelaria), 2)== 0)
		{
			indicepArancelaria = pArancelariaController_buscarPorId(pArrayListpArancelaria, id);
			auxpArancelaria = ll_get(pArrayListpArancelaria,indicepArancelaria);
			if(auxpArancelaria != NULL)
			{
				pArancelaria_imprimir(auxpArancelaria);
				if(aux_getNumeroInt(&confirma,"Confirma los cambios? 0=NO 1=SI\n","Opcion incorrecta.Reingrese.\n",0,1, 2)== 0 && confirma == 1)
				{
					ll_remove(pArrayListpArancelaria,indicepArancelaria);
					pArancelaria_delete(auxpArancelaria);
					pArancelariaController_saveAsText("Posiciones_Arancelarias.csv" ,pArrayListpArancelaria);
					printf("Empleado eliminado correctamente\n\n");
				}
				else
				{
					printf("No se ha eliminado ningun empleado.\n\n");
				}
				retorno = 1;
			}
		}
	}
	return retorno;
}
