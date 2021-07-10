#include "ingredientes.h"
#include "ingrediente.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;


  ingredientes::ingredientes(vector<ingrediente> vect){
    for(int i=0; i<vect.size();i++){
      int pos=0,pos_indice=0;
      if(!esta_en_datos(vect[i],pos)){
        datos.insert(vect.begin()+pos,vect[i]);
        if(!esta_en_indice(vect[i],pos_indice)){
          indice.insert(indice.begin()+pos,pos);
        }
      }
    }

  }

  ostream& operator<<(ostream &os, ingredientes &ingrs){
    for(int i=0; i<ingrs.size();i++){
      os<<ingrs.datos[i];
    }
    return os;
  }


  ingredientes::~ingredientes(){
    liberar();
  }
  void ingredientes::liberar(){
    datos.clear();
    indice.clear();
  }

  istream& operator>>(istream &is, ingredientes &ingrs){
    ingrs.liberar();
    string linea;
    getline(is,linea);
    getline(is,linea);

    while ( is.eof() == 0 ){
        istringstream ss(linea);
        ingrediente aux;
        ss >> aux;
        ingrs.aniadir(aux);
        linea = "";
        getline(is,linea);
    }

    return is;
  }

  void ingredientes::aniadir(const ingrediente &nuevo){

    int pos=0,pos_indice=0;
    bool esta_datos= esta_en_datos(nuevo,pos), esta_indice= esta_en_indice(nuevo,pos_indice);
    if(!esta_indice && !esta_datos){
      for(int i=0; i<indice.size(); i++){
        if(indice[i]>=pos){
          indice[i]++;
        }
      }
    }


    if(!esta_indice && !esta_datos){
      datos.insert(datos.begin()+pos,nuevo);
      indice.insert(indice.begin()+pos_indice,pos);
    }

  }


 const ingrediente& ingredientes::operator[](int pos)const{
    return datos[pos];
 }


  ingredientes& ingredientes::operator=(const ingredientes &otro){
    if(&otro!=this){
      datos=otro.datos;
      indice=otro.indice;
    }
    return *this;
  }

  int ingredientes::size()const{
    return datos.size();
  }

  ingredientes ingredientes::getIngredienteTipo(const string t){
    ingredientes aux;
    for(int i=0; i<datos.size(); i++){
      if(datos[i].getTipo()==t){
        aux.aniadir(datos[i]);
      }
    }
    return aux;
  }

  bool ingredientes::esta_en_datos(const ingrediente ingr, int &pos){

    int med, inf=0, sup=datos.size();
    bool enc=false;
    while ((inf<sup) && (!enc)){
      med= (inf+sup)/2;
      if (datos[med]==ingr)
        enc= true;
      else if (datos[med].getNombre() < ingr.getNombre())
        inf= med+1;
      else
        sup= med;
    }
    if(enc){
      pos=med;
      return enc;
    }else{
      pos=inf;
      return false;
    }
  }


  bool ingredientes::esta_en_indice(const ingrediente ingr, int &pos){

    int med, inf=0, sup=indice.size();
    bool enc=false;
    while ((inf<sup) && (!enc)){
      med= (inf+sup)/2;
      if (datos[indice[med]]==ingr)
        enc= true;
      else if ( datos[indice[med]].getTipo() != ingr.getTipo() )
         if (datos[indice[med]].getTipo() < ingr.getTipo())
            inf= med+1;
        else
            sup= med;
       else if ( datos[indice[med]].getNombre() < ingr.getNombre() )
                inf= med+1;
            else
                sup= med;
    }

    if(enc){
      pos=med;
      return enc;

    }else{
      pos=inf;
      return false;
    }

  }

  void ingredientes::ImprimirPorTipo(ostream &os){
    for(vector<int>::const_iterator it= indice.begin(); it != indice.end(); ++it){
      os<<datos[*(it)]<<endl;
    }
  }

  void ingredientes::ordenar(){
    for(int i=0; i<datos.size()-1;i++){
      for(int j=0; j<datos.size()-i-1; j++){
        if(datos[j].getNombre() > datos[j+1].getNombre()){
          ingrediente aux=datos[j];
          datos[j]=datos[j+1];
          datos[j+1]=aux;
        }
        if(datos[indice[j]].getTipo() > datos[indice[j+1]].getTipo()){
          int aux = indice[j];
          indice[j] = indice[j+1];
          indice[j+1] = aux;
        }
      }
    }
  }

  void ingredientes::borrar(const string n){
    int pos=0,pos_indice=0;
    if(esta_en_datos(get(n),pos) && esta_en_indice(get(n),pos_indice)){
      datos.erase(datos.begin()+pos);
        indice.erase(indice.begin()+pos_indice);
        for(int i=0; i<indice.size(); i++){
          if(indice[i]>pos){
            indice[i]--;
          }
        }

    }

  }

  ingrediente ingredientes::get(const string nombre)const{
    ingrediente ingr;
    ingr.setNombre("undefined");
    int pos=0;
    bool enc=false;
    for(int i=0; i<size() && !enc; i++){
      if(datos[i].getNombre()==nombre){
        pos=i;
        enc=true;
      }
    }
    if(enc)
    return datos[pos];
    else
      return ingr;
  }

  vector<string> ingredientes::getTipos(){
    vector<string> aux;
    bool noesta=true;
    aux.insert(aux.end(),datos[indice[0]].getTipo());
    for(int i=1; i<indice.size(); i++){
      for(int j=0; j<aux.size(); j++){
        if(aux[j]==datos[indice[i]].getTipo())
          noesta=false;
      }
      if(noesta)
        aux.insert(aux.end(),datos[indice[i]].getTipo());
      noesta=true;
    }
    return aux;
  }

  void ingredientes::promedio(const ingredientes &ingrs,vector<float> res){

    //inicializo a 0...
    for(int i=0; i<5;i++){
      res[i]=0.0;
    }
    for(int i=0; i<ingrs.datos.size();i++){
      res[0]+=ingrs.datos[i].getCalorias();
      res[1]+=ingrs.datos[i].getHc();
      res[2]+=ingrs.datos[i].getProteinas();
      res[3]+=ingrs.datos[i].getGrasas();
      res[4]+=ingrs.datos[i].getFibra();
    }
    for(int i=0; i<5; i++){
      res[i]/=ingrs.datos.size();
    }

  }

  void ingredientes::varianza(const ingredientes &ingrs,vector<float> media,vector<float> res){

    promedio(ingrs,media);

    //inicializo a 0...
    for(int i=0; i<5;i++){
      res[i]=0;
    }
    for(int i=0; i<ingrs.datos.size();i++){
      res[0]+=((ingrs.datos[i].getCalorias() - media[0]) * (ingrs.datos[i].getCalorias() - media[0]));
      res[1]+=((ingrs.datos[i].getHc() - media[1]) * (ingrs.datos[i].getHc() - media[1]));
      res[2]+=((ingrs.datos[i].getProteinas() - media[2]) * (ingrs.datos[i].getProteinas() - media[2]));
      res[3]+=((ingrs.datos[i].getGrasas() - media[3]) * (ingrs.datos[i].getGrasas() - media[3]));
      res[4]+=((ingrs.datos[i].getFibra() - media[4]) * (ingrs.datos[i].getFibra() - media[4]));
    }

    for(int i=0; i<5;i++){
      res[i]/=ingrs.datos.size();
      res[i]=sqrt(res[i]);
    }

  }

  void ingredientes::maximos(const ingredientes &ingrs,vector<string> nombre_max){
    vector<float> maximos;

    maximos[0]=ingrs.datos[0].getCalorias();
    maximos[1]=ingrs.datos[0].getHc();
    maximos[2]=ingrs.datos[0].getProteinas();
    maximos[3]=ingrs.datos[0].getGrasas();
    maximos[4]=ingrs.datos[0].getFibra();

    for(int i=0; i<5; i++){
      nombre_max[i]=ingrs.datos[0].getNombre();
    }

    for(int i=1; i<ingrs.datos.size(); i++){
        if(maximos[0]<ingrs.datos[i].getCalorias()){
          maximos[0]=ingrs.datos[i].getCalorias();
          nombre_max[0]=ingrs.datos[i].getNombre();
        }
        if(maximos[1]<ingrs.datos[i].getHc()){
          maximos[1]=ingrs.datos[i].getHc();
          nombre_max[1]=ingrs.datos[i].getNombre();
        }
        if(maximos[2]<ingrs.datos[i].getProteinas()){
          maximos[2]=ingrs.datos[i].getProteinas();
          nombre_max[2]=ingrs.datos[i].getNombre();
        }
        if(maximos[3]<ingrs.datos[i].getGrasas()){
          maximos[3]=ingrs.datos[i].getGrasas();
          nombre_max[3]=ingrs.datos[i].getNombre();
        }
        if(maximos[4]<ingrs.datos[i].getFibra()){
          maximos[4]=ingrs.datos[i].getFibra();
          nombre_max[4]=ingrs.datos[i].getNombre();
        }
    }

    for(int i=0; i<5; i++){
      ostringstream oss;
      oss << maximos[i] << " " << nombre_max[i];
      nombre_max[i]=oss.str();
    }

  }

  void ingredientes::minimos(const ingredientes &ingrs,vector<string> nombre_min){
    vector<float> minimos;

    minimos[0]=ingrs.datos[0].getCalorias();
    minimos[1]=ingrs.datos[0].getHc();
    minimos[2]=ingrs.datos[0].getProteinas();
    minimos[3]=ingrs.datos[0].getGrasas();
    minimos[4]=ingrs.datos[0].getFibra();

    for(int i=0; i<5; i++){
      nombre_min[i]=ingrs.datos[0].getNombre();
    }

    for(int i=1; i<ingrs.datos.size(); i++){
        if(minimos[0]>ingrs.datos[i].getCalorias()){
          minimos[0]=ingrs.datos[i].getCalorias();
          nombre_min[0]=ingrs.datos[i].getNombre();
        }
        if(minimos[1]>ingrs.datos[i].getHc()){
          minimos[1]=ingrs.datos[i].getHc();
          nombre_min[1]=ingrs.datos[i].getNombre();
        }
        if(minimos[2]>ingrs.datos[i].getProteinas()){
          minimos[2]=ingrs.datos[i].getProteinas();
          nombre_min[2]=ingrs.datos[i].getNombre();
        }
        if(minimos[3]>ingrs.datos[i].getGrasas()){
          minimos[3]=ingrs.datos[i].getGrasas();
          nombre_min[3]=ingrs.datos[i].getNombre();
        }
        if(minimos[4]>ingrs.datos[i].getFibra()){
          minimos[4]=ingrs.datos[i].getFibra();
          nombre_min[4]=ingrs.datos[i].getNombre();
        }
    }

    for(int i=0; i<5; i++){
      ostringstream oss;
      oss << minimos[i] << " " << nombre_min[i];
      nombre_min[i]=oss.str();
    }

  }
