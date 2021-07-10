//
// Created by angel on 22/11/19.
//

#ifndef RECETAS_H
#define RECETAS_H

#include <map>
#include "receta.h"
#include "ingredientes.h"
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

/**
 * @brief recetas
 *
 * Recetas es una clase que utiliza un contenedor de STL map en el
 * que mantiene las recetas ordenadas por Codigo unico (string que pertenece a la clase receta)
 * y la receta con ese codigo unico asociado.
 *
 * Ejemplo de uso:
 * @include test_receta.cpp
 * @include nutricion_receta.cpp
 *
 * @author Angel Gomez Ferrer
 */
class recetas {
private:
    map<string, receta> datos;/**< Mapa de la STL mantiene las recetas ordenadas por su codigo*/

public:
    /**
     * @brief constructor por defecto de recetas (totalmente prescindible)
     */
    recetas(){}
    /**
     * @brief Destructor de recetas
     */
    ~recetas();

    //--------------------------------------------------------------------------
    //Iteradores

    /**
    * @brief Clase iterador
    * */
    class const_iterator;

    class iterator{
    private:
        map<string, receta>::iterator it;
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
        receta& operator*(){
            return (*it).second;
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

        friend class recetas;
        friend class const_iterator;
    };


    /**
     * @brief Clase iterador constante (Mismas funciones que class Iterator pero constante 8) )
     * */
    class const_iterator{
    private:
        map<string, receta>::const_iterator it;
    public:
        const_iterator(){}

        const_iterator(const iterator &i):it(i.it){}

        bool operator==(const const_iterator &i)const{
            return i.it==it;
        }
        bool operator!=(const const_iterator &i)const{
            return i.it!=it;
        }
        const receta& operator*()const{
            return (*it).second;
        }
        const_iterator & operator++(){
            ++it;
            return *this;
        }
        const_iterator & operator--(){
            --it;
            return *this;
        }

        friend class recetas;
    };
    /**
     * @return Devuelve un iterador apuntando a la primera posicion de memoria con contenido del contenedor al que pertenece.
     */
    iterator begin(){
        iterator i;
        i.it=datos.begin();
        return i;
    }
    /**
     * @return Devuelve un iterador apuntando a la primera posicion de memoria sin contenido del contenedor al que pertenece.
     */
    iterator end(){
        iterator i;
        i.it=datos.end();
        return i;
    }
    /**
     * @return Devuelve un iterador apuntando a la primera posicion de memoria con contenido del contenedor al que pertenece.
     */
    const_iterator cbegin()const{
        const_iterator i;
        i.it=datos.begin();
        return i;
    }
    /**
     * @return Devuelve un iterador apuntando a la primera posicion de memoria sin contenido del contenedor al que pertenece.
     */
    const_iterator cend()const{
        const_iterator i;
        i.it=datos.end();
        return i;
    }

    //--------------------------------------------------------------------------
    //Operadores

    /**
    * @brief Salida de recetas a ostream
    * @param os: stream de salida
    * @param rec: recetas a escribir
    * @post Los objetos receta contenidos en datos.
    */
    friend ostream& operator<< (ostream &os,const recetas &rec);
    /**
    * @brief Entrada de recetas desde istream
    * @param is: stream de entrada
    * @param rec: recetas que recibe
    * @retval Las recetas leídas en p
    * @pre La entrada de las recetas debe tener el formato: Codigo;Numero de plato;Nombre de la receta;Ingrediente Gramos;......;Ultimo_Ingrediente Gramos
    */
    friend istream& operator>> (istream &is, recetas &rec);
    /**
    * @brief Consulta el elemento por codigo
    * @param c: codigo de la receta
    * @return Una referencia a la receta con ese codigo.
    */
    receta& operator[](const string& c);

    //--------------------------------------------------------------------------
    //Getters
    /**
     * @Bried Consultor de Mapa datos
     * @return Map< string , receta > datos
     */
    const map<string, receta>& getDatos()const{ return datos; }

    //--------------------------------------------------------------------------
    //Utilidades

    /**
     * @brief Borra una receta
     * @param c Codigo de la receta a borrar
     */
    void borrar(const string c);
    /**
     * @brief Agrega un nuevo elemento
     * @param nuevo Receta a agregar al mapa
     */
    void aniadir(const receta &nuevo);
    /**
     * @brief Inserta un elemento en la posicion dad
     * @param position Iterador con la poscion en la que agregar el elemento
     * @param nueva Receta a insertar
     */
    void insertar(map<string, receta>::const_iterator position, const pair<string, receta>& nueva);
    /**
     * @brief Tamaño del mapa de recetas
     * @return datos.size()
     */
    int size()const;
    /**
     * @brief Da valor a todos los valores nutricionales de cada una de las recetas
     * @param base_ingrs (Ingredientes) Informacion de los ingredientes
     */
    void inicializa_valores(const ingredientes &base_ingrs);
    /**
     * @brief Imprime la recetas con sus valores nutricionales
     * @param os stream de salida
     * @pre Los valores nutricionales deben ser inicialiazados antes con inicializa_valores(ingredientes)
     * @post La receta y sus valores nutricionales
     */
    void imprimirConValores(ostream &os);
    /**
     * @brief Libera la memoria del mapa
     */
    void liberar();
    /**
     * @brief Carga las instrucciones de las recetas
     * @param carpeta (Directorio con los datos de las intrucciones)
     */
    void cargarInstrucciones(const string carpeta);
    /**
     * @brief Junta dos recetas
     * @param code1 Codigo de una receta
     * @param code2 Codigo
     * @return Una receta producto de las insertadas
     */
    receta juntarRecetas(const string code1, const string code2);
    /**
     * @brief Escribe las recetas con el formato: CODE: -- NOMBRE: --- PLATO: -
     * @param os Escritura
     */
    void escribirSistematicamente(ostream &os);


};

#endif //RECETAS_H
