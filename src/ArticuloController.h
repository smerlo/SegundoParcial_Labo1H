#ifndef ARTICULOCONTROLLER_H_
#define ARTICULOCONTROLLER_H_
int articuloController_loadArticulosFromText(char* path , LinkedList* pArrayListArticulo);
int articuloController_menuArticulos(LinkedList* pArrayListArticulo);
int articuloController_addArticulo(LinkedList* pArrayListArticulo);
int articuloController_editArticulo(LinkedList* pArrayListArticulo);
int articuloController_removeArticulo(LinkedList* pArrayListArticulos);
#endif /* ARTICULOCONTROLLER_H_ */
