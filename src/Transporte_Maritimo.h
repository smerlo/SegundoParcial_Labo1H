#ifndef TRANSPORTE_MARITIMO_H_
#define TRANSPORTE_MARITIMO_H_
typedef struct
{
    float metros_cubicos;
    float valor;
}tMaritimo;

int tMaritimo_setMetrosCubicos(tMaritimo* this, float mCubicos);
int tMaritimo_getMetrosCubicos(tMaritimo* this, float* mCubicos);
int tMaritimo_setValor(tMaritimo* this, float valor);
int tMaritimo_getValor(tMaritimo* this, float* valor);
tMaritimo* tMaritimo_new(void);
tMaritimo* tMaritimo_newParametros(char* mCubicos, char* valor);
void tMaritimo_delete(tMaritimo* this);
int tMaritimo_imprimir(tMaritimo* this);
float tMaritimo_CalcularFlete(tMaritimo* this, float metrosCubicos);
#endif /* TRANSPORTE_MARITIMO_H_ */
