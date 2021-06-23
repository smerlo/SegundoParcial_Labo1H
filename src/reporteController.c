#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "auxiliar.h"
#include "Transporte_Aereo.h"
#include "Articulo.h"
#include "articuloController.h"
#include "Posicion_arancelaria.h"
#include "pArancelariaController.h"
#include "Transporte_Maritimo.h"
#include "Reporte.h"
#include "string.h"

static int generarReporte(LinkedList* pArrayListReporte,LinkedList* pArrayListArticulos,LinkedList* pArrayListPArancelarias,LinkedList* pArrayListTAereo,LinkedList* pArrayListTMaritimo);
static float calcularBaseImponible(float fob,float pSeguro, float flete);
static int crearReporte(LinkedList* pArrayListReporte,Articulo* articulo, pArancelaria* pArancelaria, float mCubicos, float cmCubicos,float costoArgentinoAereo, float costoArgentinoMaritimo);
static int reporteController_ListarReportes(LinkedList* pArrayListReporte);
static int reporteController_sortReporte(LinkedList* pArrayListReporte);
static int reporteController_ListarReportesPArancelaria(LinkedList* pArrayListReporte, LinkedList* pArrayListPArancelarias);

int reporte_menuTAereo(LinkedList* pArrayListReporte,LinkedList* pArrayListArticulos,LinkedList* pArrayListPArancelarias,LinkedList* pArrayListTAereo,LinkedList* pArrayListTMaritimo)
{
	int retorno = -1;
	int option;
	if(pArrayListReporte != NULL && pArrayListArticulos != NULL && pArrayListPArancelarias != NULL && pArrayListTAereo != NULL && pArrayListTMaritimo != NULL)
	{
		if(generarReporte(pArrayListReporte,pArrayListArticulos,pArrayListPArancelarias,pArrayListTAereo,pArrayListTMaritimo) == 0)
		{
			retorno = 0;
			do{
				aux_getNumeroInt(&option,"1. Imprimir articulos con costos\n"
										"2. Ordenar articulos con costos\n"
										"3. Imprimir pArancelarias con Maximo Aereo\n"
										  "4. Salir\n",
										  "Opción inválida\n",
										  1,4,2);
				switch(option)
				{
					case 1:
						reporteController_ListarReportes(pArrayListReporte);
						break;
					case 2:
						reporteController_sortReporte(pArrayListReporte);
						break;
					case 3:
						reporteController_ListarReportesPArancelaria(pArrayListReporte,pArrayListPArancelarias);
						break;
				}
			}while(option != 4);
		}
	}
	return retorno;
}

static int generarReporte(LinkedList* pArrayListReporte,LinkedList* pArrayListArticulos,LinkedList* pArrayListPArancelarias,LinkedList* pArrayListTAereo,LinkedList* pArrayListTMaritimo)
{
	int retorno = -1;
	Articulo* auxArticulo;
	pArancelaria* pArancelariaAux;
	int pArancelariaIndice;
	tAereo* tAereoAux;
	tMaritimo* tMaritimoAux;
	float metrosCubicos;
	float cmCubicos;
	float peso;
	float fleteAereo;
	float fleteMaritimo;
	float bImponibleArea;
	float bImponibleMaritima;
	float costoArgentinoAereo;
	float costoArgentinoMaritimo;


	if(pArrayListReporte != NULL && pArrayListArticulos != NULL && pArrayListPArancelarias != NULL && pArrayListTAereo != NULL && pArrayListTMaritimo != NULL)
	{
		ll_clear(pArrayListReporte);
		tAereoAux = (tAereo*)ll_get(pArrayListTAereo,0);
		tMaritimoAux = (tMaritimo*)ll_get(pArrayListTMaritimo,0);
		for(int i=0; i < ll_len(pArrayListArticulos); i++)
		{
			auxArticulo= (Articulo*)ll_get(pArrayListArticulos,i);
			pArancelariaIndice= pArancelariaController_buscarPorId(pArrayListPArancelarias, auxArticulo->pArancelaria);
			pArancelariaAux= (pArancelaria*)ll_get(pArrayListPArancelarias,pArancelariaIndice);
			printf("%d idArt\n",auxArticulo->id);
			metrosCubicos = articulo_calcularMetrosCubicos(auxArticulo);
			printf("%f metros_cubicos\n",metrosCubicos);
			cmCubicos = articulo_calcularCmCubicos(auxArticulo);
			articulo_getPeso(auxArticulo,&peso);
			fleteAereo = tAereo_CalcularFlete(tAereoAux,cmCubicos,peso);
			fleteMaritimo = tMaritimo_CalcularFlete(tMaritimoAux,metrosCubicos);
			printf("%f flete_Maritimo\n",fleteMaritimo);
			bImponibleArea = calcularBaseImponible(auxArticulo->fob,pArancelariaAux->porcentaje_seguro,fleteAereo);
			printf("%f porcentaje_seguro\n", pArancelariaAux->porcentaje_seguro);
			bImponibleMaritima = calcularBaseImponible(auxArticulo->fob,pArancelariaAux->porcentaje_seguro,fleteMaritimo);
			printf("%f BaseImponibleMaritima\n",bImponibleMaritima);
			printf("%s N.Arancelaria\n", pArancelariaAux->nomenclatura_arancelaria);

			costoArgentinoAereo = pArancelaria_CalcularCostoArgentino(pArancelariaAux, bImponibleArea);
			costoArgentinoMaritimo = pArancelaria_CalcularCostoArgentino(pArancelariaAux, bImponibleMaritima);
			printf("----------------\n");
			if(crearReporte(pArrayListReporte,auxArticulo, pArancelariaAux, metrosCubicos, cmCubicos, costoArgentinoAereo, costoArgentinoMaritimo)!= 0)
			{
				retorno = -1;
				break;
			}
			else
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}

static float calcularBaseImponible(float fob,float pSeguro, float flete)
{
	float retorno = -1;
	float seguro;
	if(fob > 0 && pSeguro > 0 && flete > 0)
	{
		seguro = (pSeguro * fob) / 100;
		retorno = fob + seguro + flete;
	}

	return retorno;
}

static int crearReporte(LinkedList* pArrayListReporte,Articulo* articulo, pArancelaria* pArancelaria, float mCubicos, float cmCubicos,float costoArgentinoAereo, float costoArgentinoMaritimo)
{
	int retorno = -1;
	char idTxt[20];
	char fobTxt[20];
	char mCubicosTxt[20];
	char cmCubicosTxt[20];
	char costoArgentinoAereoTxt[20];
	char costoArgentinoMaritimoTxt[20];
	char codigo[24];
	char nombre[128];
	char nArancelaria[48];
	Reporte* auxReporte;
	if(articulo != NULL && pArancelaria != NULL && mCubicos > 0 && cmCubicos > 0 && costoArgentinoAereo > 0 && costoArgentinoMaritimo > 0)
	{
		sprintf(idTxt,"%d",articulo->id);
		sprintf(fobTxt,"%f",articulo->fob);
		sprintf(mCubicosTxt,"%f",mCubicos);
		sprintf(cmCubicosTxt,"%f",cmCubicos);
		sprintf(costoArgentinoAereoTxt,"%f",costoArgentinoAereo);
		sprintf(costoArgentinoMaritimoTxt,"%f",costoArgentinoMaritimo);
		strcpy(codigo, articulo->codigo);
		strcpy(nombre, articulo->nombre);
		pArancelaria_getNomenclaturaArancelaria(pArancelaria,nArancelaria);
		if(reporte_newParametros(idTxt,codigo,nombre,fobTxt,  nArancelaria, mCubicosTxt,  cmCubicosTxt,  costoArgentinoAereoTxt,  costoArgentinoMaritimoTxt) >= 0)
		{
			pArancelaria_getNomenclaturaArancelaria(pArancelaria,nArancelaria);
			auxReporte = (Reporte*)reporte_newParametros(idTxt,codigo,nombre,fobTxt, nArancelaria, mCubicosTxt,  cmCubicosTxt,  costoArgentinoAereoTxt,  costoArgentinoMaritimoTxt);
			ll_add(pArrayListReporte,auxReporte);

			retorno = 0;
		}
	}
	return retorno;
}

static int reporteController_ListarReportes(LinkedList* pArrayListReporte)
{
	Reporte* auxReporte;
	int retorno = 0;
	if(pArrayListReporte != NULL)
	{
		printf("%s%20s%20s%20s%20s%20s%20s\n","ID","NOMBRE","CODIGO","FOB","N. ARANCELARIA", "C. AEREO","C. MARITIMO");
		for(int i=0; i < ll_len(pArrayListReporte); i++)
		{
			auxReporte= (Reporte*)ll_get(pArrayListReporte,i);
			reporte_imprimir(auxReporte);
		}
		printf("\n\n");
		retorno = 1;
	}
	return retorno;
}

static int reporteController_ListarReportesPArancelaria(LinkedList* pArrayListReporte, LinkedList* pArrayListPArancelarias)
{
	Reporte* auxReporteUno;
	Reporte* auxReporteDos;
	Reporte* auxReporteMayor;
	pArancelaria* auxParancelaria;
	int retorno = 0;
	int flagFirst = 0;
	int flagCambio = 0;
	ll_sort(pArrayListReporte,reporte_CompararNArancelaria,0);
	if(pArrayListReporte != NULL)
	{
		printf("%20s%20s%20s\n","NOMBRE","N. ARANCELARIA", "C. AEREO");
		for(int i=0; i < ll_len(pArrayListPArancelarias); i++)
		{
			flagFirst = 0;
			flagCambio = 0;
			auxParancelaria =(pArancelaria*)ll_get(pArrayListPArancelarias,i);
			for(int j=0;j < ll_len(pArrayListReporte);j++)
			{
				auxReporteUno = (Reporte*)ll_get(pArrayListReporte,j);
				auxReporteDos = (Reporte*)ll_get(pArrayListReporte,j+1);
				if(auxReporteUno != NULL && auxReporteDos != NULL && strcmp(auxReporteUno->pArancelaria,auxParancelaria->nomenclatura_arancelaria) == 0 &&
						strcmp(auxReporteUno->pArancelaria,auxReporteDos->pArancelaria) == 0)
				{
					if(flagFirst == 0)
					{
						auxReporteMayor = (Reporte*)ll_get(pArrayListReporte,j);
						flagFirst = 1;
						flagCambio = 1;
					}else
					if(auxReporteMayor->valorAereo < auxReporteDos->valorAereo)
					{
						auxReporteMayor = (Reporte*)ll_get(pArrayListReporte,j+1);
						flagCambio = 1;
					}
				}
			}
			if(flagCambio != 0 )
			{
				reporte_imprimirParancelariaMayor(auxReporteMayor);
			}
		}
		printf("\n\n");
		retorno = 1;
	}
	return retorno;
}

static int reporteController_sortReporte(LinkedList* pArrayListReporte)
{
	int retorno = 0;
	int opcion;
	if(pArrayListReporte != NULL)
	{
		if(aux_getNumeroInt(&opcion,"1. Ordenar articulos por Id\n"
    	        					"2. Ordenar articulos por Nombre\n"
									"3. Ordenar articulos por Codigo\n"
									"4. Ordenar articulos por FOB\n"
									"5. Ordenar articulos por Nomenclatura Arancelaria\n"
									"6. Ordenar articulos por Costo Aereo\n"
									"7. Ordenar articulos por Costo Maritimo\n"
									"8. Salir\n","Opcion incorrecta.Reingrese.\n",1,8, 2)== 0)
		{
			switch(opcion)
			{
				case 1:
					ll_sort(pArrayListReporte,reporte_CompararId,1);
					printf("Articulos ordenados correctamente por ID.\n\n");
					retorno = 1;
					break;
				case 2:
					ll_sort(pArrayListReporte,reporte_CompararNombre,0);
					printf("Articulos ordenados correctamente por Nombre.\n\n");
					retorno = 1;
					break;
				case 3:
					ll_sort(pArrayListReporte,reporte_CompararCodigo,0);
					printf("Articulos ordenados correctamente por Codigo.\n\n");
					retorno = 1;
					break;
				case 4:
					ll_sort(pArrayListReporte,reporte_CompararFob,1);
					printf("Articulos ordenados correctamente por FOB.\n\n");
					retorno = 1;
					break;
				case 5:
					ll_sort(pArrayListReporte,reporte_CompararNArancelaria,0);
					printf("Articulos ordenados correctamente por Nomenclatura Arancelaria.\n\n");
					retorno = 1;
					break;
				case 6:
					ll_sort(pArrayListReporte,reporte_CompararValorAereo,1);
					printf("Articulos ordenados correctamente por Nomenclatura Arancelaria.\n\n");
					retorno = 1;
					break;
				case 7:
					ll_sort(pArrayListReporte,reporte_CompararValorMaritimo,1);
					printf("Articulos ordenados correctamente por Nomenclatura Arancelaria.\n\n");
					retorno = 1;
					break;

			}
		}


	}
	return retorno;
}
