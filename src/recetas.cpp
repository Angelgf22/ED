//
// Created by angel on 22/11/19.
//
#include "recetas.h"
#include <map>
#include "receta.h"
#include "ingredientes.h"
#include "instrucciones.h"
#include <list>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

recetas::~recetas(){
    liberar();
}
void recetas::liberar(){
    datos.clear();
}



ostream& operator<< (ostream &os,const recetas &rec){
    for(auto it= rec.cbegin(); it!= rec.cend(); ++it){
        os << *it << endl;
    }
    return os;
}


istream& operator>>(istream &is, recetas &rec){
    rec.liberar();
    string linea="";

    getline(is,linea);

    while ( !is.eof()){
        istringstream ss(linea);
        receta aux;
        ss >> aux;
        rec.aniadir(aux);
        linea = "";
        getline(is,linea);
    }

    return is;
}



void recetas::borrar(const string c){
    datos.erase(c);
}

void recetas::aniadir(const receta &nuevo){
    string codigo= nuevo.getCode();
    datos.insert( pair<string, receta>(codigo, nuevo) );
}

void recetas::inicializa_valores(const ingredientes &base_ingrs){
    for(map<string, receta>::iterator it=datos.begin(); it !=datos.end(); ++it){
        it->second.nutricionales(base_ingrs);
    }
}


void recetas::insertar(map<string, receta>::const_iterator position, const pair<string, receta>& nuevo){
    datos.insert(position, nuevo);
}

receta& recetas::operator[](const string& c){
    return datos[c];
}

void recetas::imprimirConValores(ostream &os){
    for(auto v:datos){
        (v.second).conValores(os);
        os<< endl;
    }
}

int recetas::size()const{
    return datos.size();
}

void recetas::cargarInstrucciones(const string carpeta){
    string direccion= carpeta;
    fstream d;

    for (auto &item : datos) {
        string direccion= "";
        instrucciones aux;
        direccion= carpeta + "/"+ item.first+"m.txt"; //Antes como getCode() en lugar de first
        d.open(direccion, fstream::in );
        if(!d.is_open()){
            cout << " -----> NO SE PUDO ABRIR LA RECETA!!!!! -----> "<< direccion<<endl;
        }else {
        d >> aux;
        (item.second).setInstrucciones(aux);
        d.close();}
    }

}

receta recetas::juntarRecetas(const string code1, const string code2){
    receta rec1= datos[code1];
    receta rec2= datos[code2];

    string code= "F_" + code1 + "_" + code2;
    string nombre= "Fusion " + rec1.getNombre() + " y " + rec2.getNombre();
    unsigned int plato= ( rec1.getPlato() > rec2.getPlato() ) ? ( rec1.getPlato() ) : ( rec2.getPlato() );
    float calorias=    rec1.getCalorias() + rec2.getCalorias();
    float hc=          rec1.getHc() + rec2.getHc();
    float grasas=      rec1.getGrasas() + rec2.getGrasas();
    float proteinas=   rec1.getProteinas() + rec2.getProteinas();
    float fibra=       rec1.getFibra() + rec2.getFibra();
    instrucciones inst= rec1.getInstrucciones() + rec2.getInstrucciones();
    list< pair<string, unsigned int> > ings1, ings;
    ings1= rec1.getIngs();
    ings= rec2.getIngs();
    auto it_aux= ings.begin();

    for( auto it= ings1.begin(); it != ings1.end(); ++it){
        bool esta= false;
        for(auto it2= ings.begin(); it2 != ings.end(); ++it2){
            if( (*it).first == (*it2).first ){
                esta= true;
                it_aux= it2;
            }
        }
        if(!esta){
            ings.push_back(*it);
        }else{
            (*it_aux).second+= (*it).second;
        }
    }

    receta res(code, plato, nombre, ings, calorias, hc, grasas, proteinas, fibra, inst);
    return res;
}


void recetas::escribirSistematicamente(ostream &os){
    for (auto &item : datos) {
        (item.second).escribirSistematicamente(os);
    }
}







