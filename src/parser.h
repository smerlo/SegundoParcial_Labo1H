#ifndef PARSER_H_
#define PARSER_H_
int parser_ArticuloFromText(FILE* pFile , LinkedList* pArrayListArticulo);
int parser_pArancelariaFromText(FILE* pFile , LinkedList* pArrayListpArancelaria);
int parser_tAereoFromText(FILE* pFile , LinkedList* pArrayListtAereo);
int parser_tMaritimoFromText(FILE* pFile , LinkedList* pArrayListtMaritimo);
#endif /* PARSER_H_ */
