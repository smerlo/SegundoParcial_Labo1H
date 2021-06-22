#ifndef ARTICULOCONTROLLER_H_
#define ARTICULOCONTROLLER_H_
int articuloController_loadArticulosFromText(char* path , LinkedList* pArrayListArticulo, LinkedList* listapArancelarias);
int articuloController_menuArticulos(LinkedList* pArrayListArticulo, LinkedList* listapArancelarias);
int articuloController_addArticulo(LinkedList* pArrayListArticulo,LinkedList* listapArancelarias);
int articuloController_editArticulo(LinkedList* pArrayListArticulos,LinkedList* listapArancelarias);
int articuloController_removeArticulo(LinkedList* pArrayListArticulos,LinkedList* listapArancelarias);
#endif /* ARTICULOCONTROLLER_H_ */
