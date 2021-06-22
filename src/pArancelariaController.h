#ifndef PARANCELARIACONTROLLER_H_
#define PARANCELARIACONTROLLER_H_
int pArancelariaController_loadPArancelariaFromText(char* path , LinkedList* pArrayListpArancelaria);
int pArancelariaController_menuPArancelaria(LinkedList* pArrayListpArancelaria);
int pArancelariaController_addPArancelaria(LinkedList* pArrayListpArancelaria);
int pArancelariaController_editpArancelaria(LinkedList* pArrayListpArancelaria);
int pArancelariaController_removePArancelaria(LinkedList* pArrayListpArancelaria);
int pArancelariaController_buscarPorId(LinkedList* pArrayListpArancelaria, int id);

#endif /* PARANCELARIACONTROLLER_H_ */
