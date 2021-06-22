#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "ArticuloController.h"
#include "pArancelariaController.h"
#include "tMaritimoController.h"
#include "tAereoController.h"
#include "reporteController.h"
#include "auxiliar.h"

int main(void) {
	setbuf(stdout,NULL);
	int option;

	LinkedList* listapArancelarias = ll_newLinkedList();
	LinkedList* listaArticulos = ll_newLinkedList();
	LinkedList* listaTMaritimo = ll_newLinkedList();
	LinkedList* listaTAereo = ll_newLinkedList();
	LinkedList* listReporte = ll_newLinkedList();
	pArancelariaController_loadPArancelariaFromText("posicion.csv",listapArancelarias);
	articuloController_loadArticulosFromText("articulo.csv",listaArticulos,listapArancelarias);
	tAereoController_loadTAereoFromText("Transporte_Aereo.csv",listaTAereo);
	tMaritimoController_loadTMaritimoFromText("Transporte_Maritimo.csv",listaTMaritimo);

	do{
	    	aux_getNumeroInt(&option,"1. Articulos\n"
									  "2. Posiciones Arancelarias\n"
									  "3. Transporte Aereo\n"
									  "4. Transporte Maritimo\n"
									  "5. Informes\n"
									  "6. Salir\n",
									  "Opción inválida\n",
									  1,6,2);
	        switch(option)
	        {

				case 1:
					articuloController_menuArticulos(listaArticulos, listapArancelarias);
					break;
				case 2:
					pArancelariaController_menuPArancelaria(listapArancelarias);
					break;
				case 3:
					tAereoController_menuTAereo(listaTAereo);
					break;
				case 4:
					tMaritimoController_menuTAereo(listaTMaritimo);
					break;
				case 5:
					if(reporte_menuTAereo(listReporte,listaArticulos,listapArancelarias,listaTAereo,listaTMaritimo) != 0)
					{
						printf("Hubo un error al generar los reportes");
					}
					break;
	        }
	    }while(option != 6);
	    return 0;
}
