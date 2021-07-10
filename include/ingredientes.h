#ifndef INGREDIENTES_H
#define INGREDIENTES_H


#include "ingrediente.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;
/**
  *  @brief ingredientes
  *
  * Ingredientes es un conjunto (vector dinamico) de objetos ingrediente
  * en el cual aparecen ordenados por nombre y por orden alfabetico  
  * de tipo en el indice (vector dinamico de enteros) en el cual 
  * aparecen las posciones en datos de los ingredientes.
  *
  *
  *
  * Un ejemplo de su uso:
  * @include test_ingredientes.cpp
  *
  * @author Angel Gomez Ferrer
  */
class ingredientes{
private:
  vector<ingrediente> datos;/**< Vector dinamico de objeto ingrediente(s) aparecen ordenados alfabeticamente por nombre */
  vector<int> indice;/**< Vector dinamico de enteros en el cual aparece la posicion en datos de los elementos para seguir el orden alfabetico por tipo */
  
public:
  /**
  * @brief Constructor por defecto.
  */
  ingredientes(){};
  /**
  * @brief Constructor a partir de un vector dinamico de objeto ingrediente(s).
  */
  ingredientes(vector<ingrediente> vect);
  /**
  * @brief Destructor de la clase.
  */
  ~ingredientes();


/**
 * @brief Clase iterador
 * */
    class const_iterator;

    class iterator{
    private:
        vector<ingrediente>::iterator it;
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
        ingrediente& operator*(){
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

        friend class ingredientes;
        friend class const_iterator;
    };


  /**
   * @brief Clase iterador constante
   * */
    class const_iterator{
    private:
        vector<ingrediente>::const_iterator it;
    public:
        const_iterator(){}

        const_iterator(const iterator &i):it(i.it){}

        bool operator==(const const_iterator &i)const{
            return i.it==it;
        }
        bool operator!=(const const_iterator &i)const{
            return i.it!=it;
        }
        const ingrediente & operator*()const{
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


        friend class ingredientes;
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
     * @return Devuelve un iterador apuntando a la primera posicion de memoria sin contenido del contenedor al que pertenece.
     */
    const_iterator begin()const{
        const_iterator i;
        i.it=datos.begin();
        return i;
    }
    /**
     * @return Devuelve un iterador apuntando a la primera posicion de memoria con contenido del contenedor al que pertenece.
     */
    const_iterator end()const{
        const_iterator i;
        i.it=datos.end();
        return i;
    }

  /**
  * @brief Salida de ingredientes a ostream
  * @param os: stream de salida
  * @param ingr: ingredientes a escribir
  * @post Los objetos ingrediente contenidos en datos (por orden alfabetico de nombre) y cada un con formato de salida de ingrediente
  */  
  friend ostream& operator<< (ostream &os, ingredientes &ingr);
  /**
  * @brief Entrada de ingredientes desde istream
  * @param is: stream de entrada
  * @param p: ingredientes que recibe
  * @retval Los ingredientes leídos en p
  * @pre La entrada de los ingredientes debe tener el formato: Alimento (100 gramos);Calorias (Kcal.);Hidratos de Carb.;Proteinas;Grasas;Fibra;Tipo
  * @pre Las dos primeras lineas deben tener informacion de los datos despreciable para ingredientes 
  */   
  friend istream& operator>>(istream &is, ingredientes &p);
  /**
  * @brief Agrega a ingredientes de forma ordenada el elemento
  * @param nuevo: ingrediente a introducir
  * @pre El nuevo ingrediente no debe estar introducido 
  */
  void aniadir(const ingrediente &nuevo);
  /**
  * @brief Consulta el elemento de la poscion
  * @param pos: posicion del elemento
  * @return una referencia al ingrediente de la posicion dada del vector dinamico datos
  */
  const ingrediente& operator[](int pos)const;
  /**
  * @brief Sobrecarga de operador =
  * @param otro: ingredientes a ser copiado en "this"
  */
  ingredientes& operator=(const ingredientes &otro);
  /**
  * @brief Obtiene el numero de ingredientes almacenados en datos.
  */
  int size()const;
  /**
  * @brief Consultor ingredinetes de un tipo.
  * @param t: string con el tipo a ser consultado.
  * @return Devuelve los ingredientes del tipo dado por parametro.
  */  
  ingredientes getIngredienteTipo(const string t);
  /**
  * @brief Comprueba si el ingrediente dado esta en datos y su posicion o la que deberia estar
  * @param ingr: ingrediente a comprobar
  * @param pos: entero pasado por referencia para alamacenar la posicion devuelta.
  * @return Si lo encuentra devuelve la posicion y true de lo contrario, devuelve la posicion 
  * en la que debe ser insertado y false.
  */
  bool esta_en_datos(const ingrediente ingr, int &pos);
  /**
  * @brief Comprueba si el ingrediente dado esta en indice y su posicion o la que deberia estar
  * @param ingr: ingrediente a comprobar
  * @param pos: entero pasado por referencia para alamacenar la posicion devuelta.
  * @return Si lo encuentra devuelve la posicion y true de lo contrario, devuelve la posicion 
  * en la que debe ser insertado y false.
  */
  bool esta_en_indice(const ingrediente ingr, int &pos);
  /**
  * @brief Imprime los ingredientes por tipo
  * @param os: stream de salida
  * @return Devuelve los ingredientes en el orden del indice (alfabeticamente por tipo)
  */
  void ImprimirPorTipo(ostream &os);
  /**
  * @brief funcion para ordenar los ingredientes si fuera necesario. (No utilizada en ningun metodo)
  */
  void ordenar();
  /**
  * @brief Borra el ingrediente con el nombre dado
  * @param n: nombre del ingrediente a borrar
  * @pre El ingrediente debe pertenecer al conjunto de ingredientes
  * @post Elimina el ingrediente de datos e indice modificando los valores de las posciones de los demas indices
  */
  void borrar(const string n);
  /**
  * @brief libera la memoria de los dos vectores dinamicos
  */
  void liberar();
  /**
  * @brief Cosnultor de ingrediente
  * @param nombre: nombre del ingrediente
  * @return Devuelve el ingrediente con ese nombre
  */
  ingrediente get(const string nombre)const;
  /**
  * @brief Consultor de los tipos
  * @return Devuleve un vector deinamico de strings con los nombres de los tipos que aparecen en ingredientes
  */
  vector<string> getTipos();
  /**
  * @brief promedio de cada atributo de ingrediente 
  * @param ingrs: ingredientes de los que calcular la media
  * @param res: vector dinamico pasado por referencia para almacenar los resultados.
  * @return devuelve un vector por referencia de float con la media de cada atributo
  * siendo la posicion 0-> Calorias, 1-> Proteinas, 2-> Hidratos de carb , 3-> Grasas y 4-> corresponde a la media de Fibras
  */
  void promedio(const ingredientes &ingrs,vector<float> res);
  /**
  * @brief varianzas de cada atributo de ingrediente 
  * @param ingrs: ingredientes de los que calcular la varianza
  * @param media: valores de la media calculado desde el metodo promedio.
  * @param res: vector dinamico pasado por referencia para almacenar los resultados.
  * @return devuelve un vector por referencia de float con la varianza de cada atributo
  * siendo la posicion 0-> Calorias, 1-> Proteinas, 2-> Hidratos de carb , 3-> Grasas y 4-> corresponde a la varianza de Fibra
  */
  void varianza(const ingredientes &ingrs,vector<float> media,vector<float> res);
  /**
  * @brief maximos de cada atributo de ingrediente 
  * @param ingrs: ingredientes de los que calcular los maximos
  * @param nombre_max: vector dinamico de string pasado por referencia para ser devuelto
  * @return devuelve un vector por referencia de string con el valor maximo del atributo y el nombre del ingredinete al que pertenece ese maximo
  * siendo la posicion 0-> Calorias, 1-> Proteinas, 2-> Hidratos de carb , 3-> Grasas y 4-> corresponde al valor maximo de Fibra
  */
  void maximos(const ingredientes &ingrs,vector<string> nombre_max);
  /**
  * @brief minimos de cada atributo de ingrediente 
  * @param ingrs: ingredientes de los que calcular los minimos
  * @param nombre_min: vector dinamico de string pasado por referencia para ser devuelto
  * @return devuelve un vector por referencia de string con el valor minimo del atributo y el nombre del ingredinete al que pertenece ese minimo
  * siendo la posicion 0-> Calorias, 1-> Proteinas, 2-> Hidratos de carb , 3-> Grasas y 4-> corresponde al valor minimo de Fibra
  */
  void minimos(const ingredientes &ingrs,vector<string> nombre_min);

};




#endif //INGREDIENTES_H
