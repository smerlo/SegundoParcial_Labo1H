#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar.h"


static int getInt(int* pResultado);
static int getFloat(float* pResultado);
static int getString(char* cadena, int longitud);
static int getStringNum(char* cadena, int longitud);

/**
 * \brief 	Pide ingresar un numero con decimales, y verifica que se encuentre en el minimo y maximo ingresado
 * \param pResultado es un puntero al espacio de memoria donde se copiara el valor obtenido
 * \param mensaje es un puntero al espacio de memoria donde se encuentra el mensaje que se le mostrara al usuario
 * \param Error es un puntero al espacio de memoria donde se encuentra el mensaje que se le mostrara al usuario en caso de error
 * \param minimo es un numero que define el minimo valor posible a ingresarse
 * \param maximo es un numero que define el maximo valor posible a ingresarse
 * \param reintentos es un numero que define la cantidad de reintentos que tiene el usuario en caso de ingresar un valor incorrecto
 * \return Retorna 0 si se obtiene el nummero correctamente y -1 si ocurre algun error
 *
 */
int aux_getNumeroFlotante(float* pResultado, char* mensaje, char* Error, float minimo, float maximo, int reintentos)
{
	int retorno = -1;
	float bufferAux;
	while(reintentos > 0)
	{
		printf("%s",mensaje);
		if(getFloat(&bufferAux) == 0)
		{
			if(bufferAux >= minimo && bufferAux <= maximo)
			{
				*pResultado = bufferAux;
				retorno = 0;
				break;
			}
		}
		printf("%s",Error);
		reintentos--;
	}
	return retorno;
}


/**
 * \brief 	Llama al metodo para obtener la cadena, verifica que sea equivalente a un numero flotante, la convierte en flotante
 * 			y guarda el valor en la direccion de memoria asignada
 * \param pResultado es un puntero al espacio de memoria donde se guardara el valor obtenido
 * \return Retorna 0 si se obtiene el numero correctamente y -1 si ocurre algun error
 *
 */
static int getFloat(float* pResultado)
{
    int retorno = -1;
    char bufferAux[64];

    if(pResultado != NULL)
    {
    	if(getString(bufferAux,sizeof(bufferAux))==0 && aux_verificarFlotante(bufferAux)== 0)
    	{
			*pResultado = atof(bufferAux);
			retorno = 0;
		}
    }
    return retorno;
}

/**
 * \brief 	Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * 			un máximo de 'longitud - 1' caracteres.
 * \param cadena Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 0 si se obtiene una cadena correctamente y -1 si ocurre algun error
 *
 */
static int getString(char* cadena, int longitud)
{
	int retorno = -1;
	char auxString[64];

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(auxString,sizeof(auxString),stdin) != NULL)
		{
			if(auxString[strnlen(auxString,sizeof(auxString))-1] == '\n')
			{
				auxString[strnlen(auxString,sizeof(auxString))-1] = '\0';
			}
			if(strnlen(auxString,sizeof(auxString)) <= longitud)
			{
				strncpy(cadena,auxString,longitud);
				retorno=0;
			}
		}
	}
	return retorno;
}

/**
 * \brief 	Verifica si el valor ingresado es un numero flotante tanto positivo como negativo
 * \param cadena Puntero al espacio de memoria desde donde se obtiene el valor y se verificara que sea flotante
 * \return Retorna 0 si se corrobora que el numero sea flotante y -1 si no lo es
 *
 */
int aux_verificarFlotante(char* cadena)
{
	int i=0;
		int retorno = 0;
		int contadorPuntos=0;

		if(cadena != NULL && strlen(cadena) > 0)
		{
			for(i=0 ; cadena[i] != '\0'; i++)
			{
				if(i==0 && (cadena[i] == '-' || cadena[i] == '+'))
				{
					continue;
				}
				if(cadena[i] < '0' || cadena[i] > '9' )
				{
					if(cadena[i] == '.' && contadorPuntos == 0)
					{
						contadorPuntos++;
					}
					else
					{
						retorno = -1;
						break;
					}
				}
			}
		}
		return retorno;

}


/**
 * \brief 	Pide ingresar un numero entero, y verifica que se encuentre en el minimo y maximo ingresado
 * \param pResultado es un puntero al espacio de memoria donde se copiara el valor obtenido
 * \param mensaje es un puntero al espacio de memoria donde se encuentra el mensaje que se le mostrara al usuario
 * \param Error es un puntero al espacio de memoria donde se encuentra el mensaje que se le mostrara al usuario en caso de error
 * \param minimo es un numero que define el minimo valor posible a ingresarse
 * \param maximo es un numero que define el maximo valor posible a ingresarse
 * \param reintentos es un numero que define la cantidad de reintentos que tiene el usuario en caso de ingresar un valor incorrecto
 * \return Retorna 0 si se obtiene el numero correctamente y -1 si ocurre algun error
 *
 */
int aux_getNumeroInt(int* pResultado, char* mensaje, char* Error, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int auxInt;
	do
	{
		printf("%s",mensaje);
		if(getInt(&auxInt) == 0 &&	auxInt >= minimo &&	auxInt <= maximo)
		{
			retorno = 0;
			*pResultado = auxInt;
			break;
		}
		printf("%s",Error);
		reintentos--;
	}while(reintentos>=0);

	return retorno;
}

/**
 * \brief 	Obtiene un numero entero ingresado por el usuario y verifica que el mismo sea correcto
 * \param pResultado Puntero al espacio de memoria donde se copiara el valor obtenido
 * \return Retorna 0 si se obtiene un numero correctamente y -1 si ocurre algun error
 *
 */
static int getInt(int* pResultado)
{
    int retorno = -1;
    char auxString[64];
    if(	pResultado != NULL &&
    	getString(auxString,sizeof(auxString)) == 0 &&
		aux_verificarNumerica(auxString,sizeof(auxString)) == 0)
	{
		*pResultado = atoi(auxString) ;
		retorno = 0;
	}
    return retorno;
}


/**
 * \brief 	Verifica si el valor ingresado es un numero entero tanto positivo como negativo
 * \param cadena Puntero al espacio de memoria desde donde se obtiene el valor y se verificara que sea un numero entero
 *  * \param limite Define el tamaño de cadena
 * \return Retorna 0 si se corrobora que el numero entero y -1 si no lo es
 *
 */
int aux_verificarNumerica(char* cadena, int limite)
{
	int retorno = -1;
	if(cadena != NULL && limite > 0)
	{
		retorno = 0;
		for(int i = 0;i<limite && cadena[i] != '\0';i++)
		{
			if((i != 0 && (cadena[i] == '+' || cadena[i] == '-')) || (cadena[i] < '0'||cadena[i] > '9'))
			{
				retorno = -1;
				break;
			}else
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 * \brief 	Pide ingresar un string y verifica que sea de la longitud adecuada
 * \param longitud es un numero que define la longitud maxima de la cadena a obtener
 * \param pResultado es un puntero al espacio de memoria donde se copiara el valor obtenido
 * \param mensaje es un puntero al espacio de memoria donde se encuentra el mensaje que se le mostrara al usuario
 * \param mensajeError es un puntero al espacio de memoria donde se encuentra el mensaje que se le mostrara al usuario en caso de error
 * \param reintentos es un numero que define la cantidad de reintentos que tiene el usuario en caso de ingresar un valor incorrecto
 * \return Retorna 0 si se obtiene el numero correctamente y -1 si ocurre algun error
 *
 */
int aux_getString(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getString(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

/**
 * \brief 	Pide ingresar un string y verifica que sea numerica y de la longitud adecuada
 * \param longitud es un numero que define la longitud maxima de la cadena a obtener
 * \param pResultado es un puntero al espacio de memoria donde se copiara el valor obtenido
 * \param mensaje es un puntero al espacio de memoria donde se encuentra el mensaje que se le mostrara al usuario
 * \param mensajeError es un puntero al espacio de memoria donde se encuentra el mensaje que se le mostrara al usuario en caso de error
 * \param reintentos es un numero que define la cantidad de reintentos que tiene el usuario en caso de ingresar un valor incorrecto
 * \return Retorna 0 si se obtiene el numero correctamente y -1 si ocurre algun error
 *
 */
int aux_getStringNum(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getStringNum(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

/**
 * \brief 	Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena siempre y cuando sea numerica y
 * 			un máximo de 'longitud - 1' caracteres.
 * \param cadena Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 0 si se obtiene una cadena correctamente y -1 si ocurre algun error
 *
 */
int getStringNum(char* cadena, int longitud)
{
	int retorno = -1;
	char auxString[64];
	long aux;
	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(auxString,sizeof(auxString),stdin) != NULL)
		{
			if(auxString[strnlen(auxString,sizeof(auxString))-1] == '\n')
			{
				auxString[strnlen(auxString,sizeof(auxString))-1] = '\0';
			}
			if(strnlen(auxString,sizeof(auxString)) <= longitud)
			{

				aux = atol(auxString);
				if(aux != 0 && strnlen(auxString, longitud) == 11)
				{
					strncpy(cadena,auxString,longitud);
					retorno=0;
				}
			}
		}
	}
	return retorno;
}

