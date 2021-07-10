#ifndef INSTRUCCIONES_H
#define INSTRUCCIONES_H


#include "arbolbinario.h"
#include "acciones.h"
#include "ingredientes.h"
#include <string>

using namespace std;

/**
 * @brief instrucciones
 *
 * Instrucciones es una clase que utiliza contenedor del tipo Arbol Binario
 * en el que guarda las acciones a seguir en un orden dado
 * para preparar la receta que pose el objeto instrucciones
 *
 * Ejemplo de uso:
 * @include receta.cpp
 *
 * @author Angel Gomez Ferrer
 */
class instrucciones{
private:
    ArbolBinario<string> datos;/**< Arbol binario alamacena el codigo de las accion y un numero de ingredientes o subarbol dependiendo de la ariedad*/

public:
    static acciones &acc; /**< Objeto de acciones estatico para ser consultado */
    static ingredientes &ingr;/**< Necesario para consultar ingredientes en el caso de una accion con ariedad dos con nombres de ingredientes compuestos */

    //--------------------------------------------------------------------------
    //Metodos auxiliares (Set y Gets)

    /**
     * @brief Modificador de los datos
     * @param d: Datos a colocar en el objeto (Arbol binario)
     */
    void setDatos(ArbolBinario<string> &d);
    /**
     * @brief Consultor de datos
     * @return Arbol Binario con los datos del objeto
     */
    ArbolBinario<string> getDatos()const{ return datos; }

    //--------------------------------------------------------------------------
    //Operadores

    /**
     * @brief Salida de instrucciones a ostream
     * @param os: stream de salida
     * @param ins: instrucciones a escribir
     * @return Salida de ostream de las instrucciones (mismo formato que las de entrada)
     */
    friend ostream& operator<< (ostream &os,const instrucciones &ins);
    /**
     * @brief Entrada de las instrucciones desde istream
     * @param is: stream de entrada
     * @param ins: Instrucciones que recibe
     * @retval Las instrucciones leidas en ins
     */
    friend istream& operator>> (istream &is, instrucciones &ins);
    /**
     * @brief Sobrecaarga operador =
     * @param otro: al que se iguala las instrucciones
     */
    instrucciones& operator=(const instrucciones &otro);
    /**
     * @brief Junta dos arboles de instrucciones
     * @param otro: arbol a juntar con el que se aplica la funcion
     * @return instrucciones resultado de la suma de las otras dos
     */
    instrucciones operator+(const instrucciones &otro);

};




#endif //INSTRUCCIONES_H

