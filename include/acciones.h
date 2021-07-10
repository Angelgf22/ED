#ifndef ACCIONES_H
#define ACCIONES_H


#include <iostream>
#include <utility>
#include <string>
#include <map>

using namespace std;

/**
 * @brief acciones
 *
 * Acciones es una clase que utiliza un contenedor de STL map
 * almacena las distintas acciones y asociado al codigo (nombre de la accion)
 * su ariedad la cual puede ser 1 o 2.
 *
 * Ejemplo de uso:
 * @include instrucciones.cpp
 *
 * @author Angel Gomez Ferrer
 */

class acciones{
	private:
        map<string,unsigned char > datos;/**< Mapa de la STL alamcena el nombre de las acciones y su respectiva ariedad*/
    public:
    /**
     * @brief Constructor por defecto
     */
    acciones(){}
    /**
     * @brief Destructor de la clase
     */
    ~acciones();
    //--------------------------------------------------------------------------
    //Iteradores

    /**
    * @brief Clase iterador
    * */
    class const_iterator;
    class iterator{
    private:
        map<string, unsigned char>::iterator it;
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
        unsigned char& operator*(){//Poner .second

            return it->second;
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

        friend class acciones;
        friend class const_iterator;
    };


    /**
     * @brief Clase iterador constante (Mismas funciones que class Iterator pero constante 8) )
     * */
    class const_iterator{
    private:
        map<string, unsigned char>::const_iterator it;
    public:
        const_iterator(){}

        const_iterator(const iterator &i):it(i.it){}

        bool operator==(const const_iterator &i)const{
            return i.it==it;
        }
        bool operator!=(const const_iterator &i)const{
            return i.it!=it;
        }
        const unsigned char& operator*()const{
            return it->second;
        }
        const_iterator & operator++(){
            ++it;
            return *this;
        }
        const_iterator & operator--(){
            --it;
            return *this;
        }

        friend class acciones;
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
     * @brief Salida de acciones a ostream
     * @param os: stream de salida
     * @param acc: acciones a escribir
     */
    friend ostream& operator<< (ostream &os,const acciones &acc);
    /**
     * @brief Entrada de acciones desde istream
     * @param is: stream de entrada
     * @param acc: acciones que recibe
     * @retval Las acciones leidas en acc
     * @pre Las acciones deben tener formato: accion ( ariedad == 1 || 2 )
     */
    friend istream& operator>> (istream &is, acciones &acc);
    /**
     * @brief Cosulta la ariedad segun el nombre de la accion
     * @param c: nombre de la accion
     * @return Una referencia a la ariedad de la accion con ese nombre
     */
    unsigned char& operator[](const string& c);
    /**
     * @brief Sobrecarga del operador =
     * @param otro: al que se quiere igualar
     */
    acciones& operator=(const acciones &otro);
    //--------------------------------------------------------------------------
    //Metodos

    /**
     * @brief Libera la memoria de map
     */
    void liberar();
    /**
     * @brief Agrega un nuevo elemento
     * @param accion: la key (nombre de la accion)
     * @param ariedad: ariedad asociada a la accion 1 o 2
     */
    void aniadir(const string accion, const unsigned char ariedad);
    /**
     * @brief Util para saber si un string es una accion ya en map
     * @param accion: string para saber si es una accion registrada en el map
     * @return True si esta en el map, false de lo contrario
     */
    bool pertenece(const string accion);
};


#endif //ACCIONES_H