
#ifndef AUXILIAR_H_
#define AUXILIAR_H_

int aux_getNumeroFlotante(float* pResultado, char* mensaje, char* Error, float minimo, float maximo, int reintentos);
int aux_getNumeroInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int aux_getString(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int aux_getStringNum(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int aux_verificarNumerica(char* cadena, int limite);
int aux_verificarFlotante(char* cadena);


#endif /* AUXILIAR_H_ */
