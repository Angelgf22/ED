//
// Created by angel on 22/11/19.
//

#ifndef RECETA_H
#define RECETA_H

#include "ingrediente.h"
#include "ingredientes.h"
#include "instrucciones.h"
#include <string>
#include <list>
#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * @brief TDA Receta
 *
 * Ejemplo de su uso:
 * @include recetas.cpp
 */


class receta {
private:
    string code;/**< Codigo de la receta*/
    unsigned int plato;/**< Numero de plato 1 (entrante) , 2 (principal) o 3 (postre)*/
    string nombre;/**< Nombre de la receta*/
    list< pair<string , unsigned int> > ings;/**< Lista de la STL contenedor de elementos tipo pair<string , unsigned int> con los ingredientes y los gramos correspondientes*/
    float calorias , hc , grasas , proteinas , fibra;/**< Valores nutricionales de la receta*/
    instrucciones inst;/**< Instrucciones a seguir para preparar la receta*/
public:
    /**
     * @brief Constructor de receta
     */
    receta();
    /**
     * @brief Constructor de receta con parametros
     * @param cod: code
     * @param plat: plato
     * @param nombr: nombre
     * @param ing: ingredientes
     * @param caloria: calorias
     * @param h: Hidratos de carbono
     * @param grasa: Grasas
     * @param proteina: proteinas
     * @param fibr: fibra
     * @param ins: instrucciones
     */
    receta(string cod, unsigned int plat, string nombr, list< pair<string , unsigned int> > ing, float caloria, float h, float grasa, float proteina, float fibr, instrucciones ins);
    /**
     * @brief Adjudica a la receta los valores nutricionales.
     * @param base_ingrs Informacion sobre los ingredientes donde buscar los valores nutricionales.
     */
    void nutricionales(const ingredientes &base_ingrs);

    //--------------------------------------------------------------------------
    //Iteradores


    class const_iterator;
    /**
    * @brief Clase iterador (Subclase de receta)
    *
    * Utilizada para acceder a cada uno de los ingredientes formada por receta.
    *
    * Ejemplo de uso:
    * @include recetas.cpp
    *
    * */
    class iterator{
    private:
        list< pair<string,unsigned int> >::iterator it;
    public:
        /**
         * @brief Constructor por defecto (totalmente prescindible)
         */
        iterator(){}
        /**
         * @brief Sobrecarga de operador ==
         * @param i Iterarador a ser comparado
         * @return Devuelve true si los dos apuntan a la misma direccion
         */
        bool operator==(const iterator &i)const{
            return i.it==it;
        }
        /**
        * @brief Sobrecarga de operador !=
        * @param i Iterarador a ser comparado
        * @return Devuelve true si los dos apuntan a una direccion distinta
         */
        bool operator!=(const iterator &i)const{
            return i.it!=it;
        }
        /**
         * @brief Sobrecarga de *
         * @return Devuelve el contenido de la direccion de memoria en la que apunta el iterador
         */
        pair< string, unsigned int >& operator*(){
            return *it;
        }
        /**
         * @brief Sobrecarga operador ++
         * @return Avanza una posicion en memoria en el contenedor indicado
         */
        iterator& operator++(){
            ++it;
            return *this;
        }
        /**
         * @brief Sobrecarga operador =
         * @param i iterador a ser igualado
         * @return Copia el contenido del otro iterador en this
         */
        iterator& operator=(const iterator& i){
            return *this;
        }
        /**
         * @brief Sobrecarga de operador --
         * @return Retrocede una posicion en memoria en el contenedor indicado
         */
        iterator& operator--(){
            --it;
            return *this;
        }

        friend class receta;
        friend class const_iterator;
    };


    /**
     * @brief Clase iterador constante (Mismas funciones que class Iterator pero constante 8) )
     * */
    class const_iterator{
    private:
        list< pair<string,unsigned int> >::const_iterator it;
    public:
        const_iterator(){}

        const_iterator(const iterator &i):it(i.it){}

        bool operator==(const const_iterator &i)const{
            return i.it==it;
        }
        bool operator!=(const const_iterator &i)const{
            return i.it!=it;
        }
        const pair< string, unsigned int > & operator*()const{
            return *it;
        }
        const_iterator & operator++(){
            ++it;
            return *this;
        }
        const_iterator & operator--(){
            --it;
            return *this;
        }

        friend class receta;
    };
    /**
     * @return Devuelve un iterador apuntando a la primera posicion de memoria con contenido del contenedor al que pertenece.
     */
    iterator begin(){
        iterator i;
        i.it=ings.begin();
        return i;
    }
    /**
     * @return Devuelve un iterador apuntando a la primera posicion de memoria sin contenido del contenedor al que pertenece.
     */
    iterator end(){
        iterator i;
        i.it=ings.end();
        return i;
    }
    /**
     * @return Devuelve un iterador apuntando a la primera posicion de memoria con contenido del contenedor al que pertenece.
     */
    const_iterator begin()const{
        const_iterator i;
        i.it=ings.begin();
        return i;
    }
    /**
     * @return Devuelve un iterador apuntando a la primera posicion de memoria sin contenido del contenedor al que pertenece.
     */
    const_iterator end()const{
        const_iterator i;
        i.it=ings.end();
        return i;
    }

    //--------------------------------------------------------------------------
    //Operadores

    /**
    * @brief Salida de una receta a ostream
    * @param os: stream de salida
    * @param ingr: ingrediente a escribir en la receta
    * @post Se obtiene con el formato: Codigo;Numero de plato;Nombre de la receta;Ingrediente Gramos;......;Ultimo_Ingrediente Gramos
    */
    friend ostream& operator<< (ostream &os, const receta &ingr);
    /**
    * @brief Entrada de una receta desde istream
    * @param is: stream de entrada
    * @param p: receta que recibe el valor
    * @retval La receta leída en p
    * @pre La entrada debe tener el formato: Codigo;Numero de plato;Nombre de la receta;Ingrediente Gramos;......;Ultimo_Ingrediente Gramos
    */
    friend istream& operator>>(istream &is, receta &p);

    //--------------------------------------------------------------------------
    //Getters

    /**
     * @brief Consultor de codigo (Formato R* donde * es un numero)
     * @return (string)code
     */
    string getCode()const { return code; }
    /**
    * @brief Consultor de nombre
    * @return (string)nombre
    */
    string getNombre()const { return nombre; }
    /**
    * @brief Consultor de numero de plato
    * @return (int)plato
    */
    unsigned int getPlato()const { return plato; }
    /**
    * @brief Consultor de calorias
    * @return (float)calorias
    */
    float getCalorias()const { return calorias; }
    /**
    * @brief Consultor de Hidratos de Carbono
    * @return (float)hc
    */
    float getHc()const { return hc; }
    /**
    * @brief Consultor de grasas
    * @return (float)grasas
    */
    float getGrasas()const { return grasas; }
    /**
    * @brief Consultor de proteinas
    * @return (float)proteinas
    */
    float getProteinas()const { return proteinas; }
    /**
    * @brief Consultor de fibra
    * @return (float)fibra
    */
    float getFibra()const { return fibra; }
    /**
    * @brief Consultor de la Razon (Proteinas / hc )
    * @return (float)razon de la receta
    */
    float getRazon()const { return proteinas / hc; }
    /**
    * @brief Consultor de ingredientes de la receta
    * @return list< pair<string,unsigned int> >ings
    */
    list< pair<string,unsigned int> > getIngs()const { return ings; }

    instrucciones getInstrucciones()const{ return inst; }
    //--------------------------------------------------------------------------
    //Setters
    void setInstrucciones(const instrucciones &i){ inst= i;}

    //--------------------------------------------------------------------------
    //Utilidades

    /**
     * @brief Imprime la receta con sus valores nutricionales (Calorias , hc , grasas , proteinas , fibra)
     * @param os stream de salida
     */
    void conValores(ostream &os);
    /**
     * @brief Escribe la receta con el formato: CODE: -- NOMBRE: --- PLATO: -
     * @param os Escritura
     */
    void escribirSistematicamente(ostream &os);
    /**
     * @brief Escribe la receta dando la mayor informacion de la misma
     * @param os Escritura
     */
    void escrituraCompleja(ostream &os);
    /**
     * @brief Numero de ingredientes de la receta
     * @return (size_t) ings.size()
     */
     size_t ningredientes()const;

};


#endif //RECETA_H
