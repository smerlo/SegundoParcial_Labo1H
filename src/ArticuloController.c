#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Articulo.h"
#include "ArticuloController.h"
#include "parser.h"
#include "auxiliar.h"


static int idMaximoEncontrado(LinkedList* pArrayListArticulo, int* idMaximo);
static int articuloController_saveAsText(char* path , LinkedList* pArrayListArticulos);
static int articuloController_ListarArticulos(LinkedList* pArrayListEmployee);
static int buscarPorId(LinkedList* pArrayListArticulos, int id);
/** \brief Carga los datos de los articulos desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListArticulo LinkedList*
 * \return int
 *
 */
int articuloController_loadArticulosFromText(char* path , LinkedList* pArrayListArticulo)
{
	FILE* pArchivo;
	int retorno= 0;
	if(path!=NULL)
	{
		pArchivo=fopen(path,"r");
	}
	if(pArchivo != NULL && pArrayListArticulo != NULL)
	{
		retorno = parser_ArticuloFromText(pArchivo,pArrayListArticulo);
		printf("Archivo cargado correctamente\n");
	}
	fclose(pArchivo);
	return retorno;
}

int articuloController_menuArticulos(LinkedList* pArrayListArticulo)
{
	int retorno = -1;
	int option;
	if(pArrayListArticulo != NULL)
	{
		retorno = 0;
		do{
			    	aux_getNumeroInt(&option,"1. Alta Articulo\n"
			    	        						  "2. Modificar Articulo\n"
			    	        						  "3. Eliminar Articulo\n"
			    	        						  "4. Salir\n",
			    	    							  "Opción inválida\n",
			    	    							  1,4,2);
			        switch(option)
			        {

						case 1:
							articuloController_addArticulo(pArrayListArticulo);
							break;
						case 2:
							articuloController_editArticulo(pArrayListArticulo);
							break;
						case 3:
							articuloController_removeArticulo(pArrayListArticulo);
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
int articuloController_addArticulo(LinkedList* pArrayListArticulo)
{
	int retorno=-0;
	Articulo* pAuxiliarArticulo;
	int id;
	char codigo[24];
	char nombre[128];
	char descripcion[256];
	float fob;
	int pArancelaria;
	float ancho;
	float alto;
	float profundidad;
	float peso;
	char paisFabricacion[48];
	char idTxt[15];
	char fobTxt[15];
	char pArancelariaTxt[15];
	char anchoTxt[15];
	char altoTxt[15];
	char profundidadTxt[15];
	char pesoTxt[15];

	if(pArrayListArticulo != NULL)
	{
		if(aux_getString(codigo,24,"\nIngrese el codigo del articulo: \n","\nERROR\n",2) == 0 &&
			aux_getString(nombre,128,"\nIngrese el nombre del articulo: \n","\nERROR\n",2) == 0 &&
			aux_getString(descripcion,256,"\nIngrese la descripcion del articulo: \n","\nERROR\n",2) == 0 &&
			aux_getNumeroFlotante(&fob,"\nIngrese FOB del articulo: \n","\nERROR\n", 0, 1000000, 2) == 0 &&
			aux_getNumeroInt(&pArancelaria,"Ingrese el id de posicion arancelaria\n", "Valor incorrecto\n",0, 100000,2) == 0 &&
			aux_getNumeroFlotante(&ancho,"\nIngrese el ancho en cm del articulo: \n","\nERROR\n", 0, 10000000, 2) == 0 &&
			aux_getNumeroFlotante(&alto,"\nIngrese el alto en cm del articulo: \n","\nERROR\n", 0, 10000000, 2) == 0 &&
			aux_getNumeroFlotante(&profundidad,"\nIngrese la profundidad en cm del articulo: \n","\nERROR\n", 0, 10000000, 2) == 0 &&
			aux_getNumeroFlotante(&peso,"\nIngrese el peso en kg del articulo: \n","\nERROR\n", 0, 10000000, 2) == 0 &&
			aux_getString(paisFabricacion,48,"\nIngrese el pais de origen del articulo: \n","\nERROR\n",2) == 0)
		{
			if(ll_len(pArrayListArticulo) == 0)
			{
				id = 0;
			}
			else
			{
				idMaximoEncontrado(pArrayListArticulo, &id);
				id = id + 1;

			}
			sprintf(idTxt,"%d",id);
			sprintf(fobTxt,"%f",fob);
			sprintf(pArancelariaTxt,"%d",pArancelaria);
			sprintf(anchoTxt,"%f",ancho);
			sprintf(altoTxt,"%f",alto);
			sprintf(profundidadTxt,"%f",profundidad);
			sprintf(pesoTxt,"%f",peso);

			if(articulo_newParametros(idTxt,codigo,nombre,descripcion,fobTxt,pArancelariaTxt,anchoTxt,altoTxt,profundidadTxt,pesoTxt,paisFabricacion) >= 0)
			{
				pAuxiliarArticulo = (Articulo*)articulo_newParametros(idTxt,codigo,nombre,descripcion,fobTxt,pArancelariaTxt,anchoTxt,altoTxt,profundidadTxt,pesoTxt,paisFabricacion);
				ll_add(pArrayListArticulo,pAuxiliarArticulo);

				retorno = 1;
				printf("Articulo creado correctamente con ID %d\n\n", id);
				articuloController_saveAsText("Articulos.csv" ,pArrayListArticulo);
			}
		}
	}
	return retorno;
}

static int idMaximoEncontrado(LinkedList* pArrayListArticulo, int* idMaximo)
{
	int retorno = -1;
	int i;
	int flag = 0;
	int idAuxMaximo;
	int idAuxiliar;
	Articulo* auxiliarArticulo;
	Articulo* auxArt;
	if(pArrayListArticulo != NULL && idMaximo != NULL)
	{
		retorno=0;
		for(i=0;i<ll_len(pArrayListArticulo);i++)
		{
			auxArt = ll_get(pArrayListArticulo,i);
			articulo_getId(auxArt,&idAuxiliar);
			if(!flag)
			{
				auxiliarArticulo = ll_get(pArrayListArticulo,i);
				articulo_getId(auxiliarArticulo,&idAuxMaximo);
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

static int articuloController_saveAsText(char* path , LinkedList* pArrayListArticulos)
{
	int retorno = 0;
	Articulo* auxArticulo;
	FILE* pFile=fopen(path,"w");
	if(pFile!=NULL && pArrayListArticulos !=NULL)
	{
		fprintf(pFile,"id,codigo,nombre,descripcion,fob,pArancelaria,ancho,alto,profundidad,peso,pais\n");
		for(int i= 0; i < ll_len(pArrayListArticulos); i++)
		{
			auxArticulo=ll_get(pArrayListArticulos,i);
			if(auxArticulo != NULL)
			{
				 fprintf(pFile,"%d,%s,%s,%s,%f,%d,%f,%f,%f,%f,%s\n",auxArticulo->id,auxArticulo->codigo,auxArticulo->nombre,auxArticulo->descripcion,
						 auxArticulo->fob,auxArticulo->pArancelaria,auxArticulo->ancho,auxArticulo->alto,auxArticulo->profundidad,auxArticulo->peso,auxArticulo->paisFabricacion);
			}
		}
		fclose(pFile);

		retorno = 1;
	}
	return retorno;
}

static int articuloController_ListarArticulos(LinkedList* pArrayListArticulos)
{
	Articulo* auxArticulo;
	int retorno = 0;
	if(pArrayListArticulos != NULL)
	{
		printf("%s%15s%15s%30s%15s%15s%15s%15s%15s%15s%15s\n","ID","CODIGO","NOMBRE","DESCRIPCION","FOB","P. ARANCELARIA", "ANCHO","ALTO","PROFUNDIDAD","PESO","P. FABRICACION");
		for(int i=0; i < ll_len(pArrayListArticulos); i++)
		{
			auxArticulo= (Articulo*)ll_get(pArrayListArticulos,i);
			articulo_imprimir(auxArticulo);
		}
		printf("\n\n");
		retorno = 1;
	}
	return retorno;
}

/**
 * \brief Busca en la lista un articulo por ID
 * \param pArrayListArticulos LinkedList* Puntero a la lista que será evaluada
 * \param Id. Id del articulo a buscar
 * \return int Devuelve la ubicacion donde se encuentra el id, -1 si no lo encuentra y 0 si hay error
 */
static int buscarPorId(LinkedList* pArrayListArticulos, int id)
{
	int retorno=0;
	int i;
	int idAux;
	Articulo* auxArticulo;

	if(pArrayListArticulos != NULL && id >= 0)
	{
		retorno = -1;
		for(i=0;i<ll_len(pArrayListArticulos);i++)
		{
			auxArticulo = ll_get(pArrayListArticulos,i);
			articulo_getId(auxArticulo, &idAux);
			if( idAux == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Modificar datos de Articulo
 * \param pArrayListArticulos LinkedList*
 * \return int

 */
int articuloController_editArticulo(LinkedList* pArrayListArticulos)
{
	int retorno = 0;
	Articulo* auxArticulo;
	int indiceArticulo;
	int id;
	char codigo[24];
	char nombre[128];
	char descripcion[256];
	float fob;
	int pArancelaria;
	float ancho;
	float alto;
	float profundidad;
	float peso;
	char paisFabricacion[48];
	int confirma;


	if(pArrayListArticulos != NULL)
	{
		articuloController_ListarArticulos(pArrayListArticulos);
		if(aux_getNumeroInt(&id,"Ingrese el ID que desea modificar\n","Id incorrecto, reingrese.\n",0,ll_len(pArrayListArticulos), 2)== 0)
		{
			indiceArticulo = buscarPorId(pArrayListArticulos, id);
			auxArticulo = (Articulo*)ll_get(pArrayListArticulos,indiceArticulo);
			if(auxArticulo != NULL)
			{
				articulo_imprimir(auxArticulo);
				if(aux_getString(codigo,24,"\nIngrese el codigo del articulo: \n","\nERROR\n",2) == 0 &&
						aux_getString(nombre,128,"\nIngrese el nombre del articulo: \n","\nERROR\n",2) == 0 &&
						aux_getString(descripcion,256,"\nIngrese la descripcion del articulo: \n","\nERROR\n",2) == 0 &&
						aux_getNumeroFlotante(&fob,"\nIngrese FOB del articulo: \n","\nERROR\n", 0, 1000000, 2) == 0 &&
						aux_getNumeroInt(&pArancelaria,"Ingrese el id de posicion arancelaria\n", "Valor incorrecto\n",0, 10000,2) == 0 &&
						aux_getNumeroFlotante(&ancho,"\nIngrese el ancho en cm del articulo: \n","\nERROR\n", 0, 1000000, 2) == 0 &&
						aux_getNumeroFlotante(&alto,"\nIngrese el alto en cm del articulo: \n","\nERROR\n", 0, 1000000, 2) == 0 &&
						aux_getNumeroFlotante(&profundidad,"\nIngrese la profundidad en cm del articulo: \n","\nERROR\n", 0, 1000000, 2) == 0 &&
						aux_getNumeroFlotante(&peso,"\nIngrese el peso en kg del articulo: \n","\nERROR\n", 0, 1000000, 2) == 0 &&
						aux_getString(paisFabricacion,48,"\nIngrese el pais de origen del articulo: \n","\nERROR\n",2) == 0)
				{
					if(aux_getNumeroInt(&confirma,"Confirma los cambios? 0=NO 1=SI\n","Opcion incorrecta.Reingrese.\n",0,1, 2)== 0 && confirma == 1)
					{
						articulo_setCodigo(auxArticulo,codigo);
						articulo_setNombre(auxArticulo,nombre);
						articulo_setDescripcion(auxArticulo,descripcion);
						articulo_setFob(auxArticulo,fob);
						articulo_setpArancelaria(auxArticulo,pArancelaria);
						articulo_setAncho(auxArticulo,ancho);
						articulo_setAlto(auxArticulo,alto);
						articulo_setProfundidad(auxArticulo,profundidad);
						articulo_setPeso(auxArticulo,peso);
						articulo_setPaisFabricacion(auxArticulo,paisFabricacion);
						articuloController_saveAsText("Articulos.csv" ,pArrayListArticulos);
						printf("El empleado fue editado correctamente.\n\n");
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

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int articuloController_removeArticulo(LinkedList* pArrayListArticulos)
{
	int retorno = 0;
	int indiceArticulo;
	int id;
	int confirma;
	Articulo* auxArticulo;
	if(pArrayListArticulos != NULL)
	{
		articuloController_ListarArticulos(pArrayListArticulos);
		if(aux_getNumeroInt(&id,"Ingrese el ID del articulo a eliminar\n","Id incorrecto, reingrese.\n",0,ll_len(pArrayListArticulos), 2)== 0)
		{
			indiceArticulo = buscarPorId(pArrayListArticulos, id);
			auxArticulo = (Articulo*)ll_get(pArrayListArticulos,indiceArticulo);
			if(auxArticulo != NULL)
			{
				articulo_imprimir(auxArticulo);
				if(aux_getNumeroInt(&confirma,"Confirma los cambios? 0=NO 1=SI\n","Opcion incorrecta.Reingrese.\n",0,1, 2)== 0 && confirma == 1)
				{
					ll_remove(pArrayListArticulos,indiceArticulo);
					articulo_delete(auxArticulo);
					articuloController_saveAsText("Articulos.csv" ,pArrayListArticulos);
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
