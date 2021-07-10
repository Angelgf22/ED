#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;
/**
  *  @brief ingrediente
  *
  * Ingrediente es un conjunto de datos para
  * representar las caracteristicas de un alimento
  * se utiliza como elemento a insertar en la clase ingredientes
  * 
  *
  * Un ejemplo de su uso:
  * @include ingredientes.cpp
  *
  * @author Angel Gomez Ferrer
  */

class ingrediente{
private:
  string nombre; /**< Nombre del ingrediente */
  int calorias; /**< Valor entero con las calorias cada 100 gramos */
  float hc;/**< Float con % en Hidratos de Carbono */
  float proteinas;/**< Float con % en Proteinas */
  float grasas;/**< Float con % en Grasas */
  float fibra;/**< Float con % en Fibra */
  string tipo;/**< Tipo del alimento */
 public:
    /**
    *@brief constructor por defecto.
    */
   ingrediente();
   /**
   * @brief Constructor completo con cada una de los parametros de la clase.
   * @param n: Nombre del ingrediente.
   * @param c: Valor entero con las calorias cada 100 gramos
   * @param hidratos: Float con % en Hidratos de Carbono
   * @param p: Float con % en Proteinas
   * @param gr: Float con % en Grasas
   * @param f: Float con % en Fibra
   * @param t: Tipo del alimento
   */
   ingrediente(string n, int c,float hidratos, float p, float gr, float f, string t);
   /**
   * @brief Operador == compara los dos objetos en tipo y nombre.
   * @param otro: segundo ingrediente a comparar
   * @return Devuelve un bool si los dos objetos son iguales en tipo y nombre (true)
   */
   bool operator==(const ingrediente &otro);
   /**
   * @brief Operador != compara los dos objetos en tipo y nombre.
   * @param otro: segundo ingrediente a comparar
   * @return Devuelve un bool si los dos objetos son distintos en tipo y nombre (true)
   */   
   bool operator!=(const ingrediente &otro);
  /**
  * @brief Salida de un ingrediente a ostream
  * @param os: stream de salida
  * @param ingr: ingrediente a escribir
  * @post Se obtiene con el formato: Alimento (100 gramos);Calorias (Kcal.);Hidratos de Carb.;Proteinas;Grasas;Fibra;Tipo
  */
   friend ostream& operator<< (ostream &os, const ingrediente &ingr);
  /**
  * @brief Entrada de un ingrediente desde istream
  * @param is: stream de entrada
  * @param p: ingrediente que recibe el valor
  * @retval El ingrediente leído en p
  * @pre La entrada debe tener el formato: Alimento (100 gramos);Calorias (Kcal.);Hidratos de Carb.;Proteinas;Grasas;Fibra;Tipo
  */   
   friend istream& operator>>(istream &is, ingrediente &p);
   /**
   * @brief Consultor de nombre
   * @return nombre
   */
   string getNombre()const{
     return nombre;
   }
   /**
   * @brief Modificador de nombre
   * @param n: (string) nombre a introducir
   */
   void setNombre(const string n){
     nombre = n;
   }
   /**
   * @brief Consultor de Calorias
   * @return (int) calorias
   */
   int getCalorias()const{
     return calorias;
   }
   /**
   * @brief Modificador de calorias
   * @param c: calorias a introducir
   */
   void setCalorias(const int c){
     calorias = c;
   }
   /**
   * @brief Consultor de proteinas
   * @return proteinas
   */
   float getProteinas()const{
     return proteinas;
   }
   /**
   * @brief Modificador de proteinas
   * @param pr: (float) proteinas a introducir
   */
   void setProteinas(const float pr){
     proteinas = pr;
   }
   /**
   * @brief Consultor de Hidratos de Carbono
   * @return hc
   */
   float getHc()const{
     return hc;
   }
   /**
   * @brief Modificador de Hidratos de carbono
   * @param h: (float) hc a introducir
   */
   void setHc(const float h){
     hc = h;
   }
   /**
   * @brief Consultor de grasa
   * @return grasas
   */
   float getGrasas()const{
     return grasas;
   }
   /**
   * @brief Modificador de grasas
   * @param g: (float) grasas a introducir
   */
   void setGrasas(const float g){
     grasas = g;
   }
   /**
   * @brief Consultor de Fibra
   * @return fibra
   */
   float getFibra()const{
     return fibra;
   }
   /**
   * @brief Modificador de fibra
   * @param f: (float) fibra a introducir
   */
   void setFibra(const float f){
     fibra = f;
   }
   /**
   * @brief Consultor de tipo
   * @return tipo
   */
   string getTipo()const{
     return tipo;
   }
   /**
   * @brief Modificador de tipo
   * @param t: (string) tipo a introducir
   */
   void setTipo(const string t){
     tipo = t;
   }


};


#endif //INGREDIENTE_H
