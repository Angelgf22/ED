//
// Created by angel on 17/12/19.
//

#include "acciones.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

acciones::~acciones(){
    liberar();
}
void acciones::liberar(){
    datos.clear();
}

ostream& operator<< (ostream &os,const acciones &acc){
    for(auto it= acc.cbegin(); it!= acc.cend(); ++it){
        os <<*it << endl;
    }
    return os;
}

istream& operator>> (istream &is, acciones &acc){
    string linea;
    int pos;

    while(!is.eof()){
        getline(is, linea);
        pos= linea.find(" ");
        const unsigned char* t= reinterpret_cast<const unsigned char*>((linea.substr(pos+1)).c_str());
        acc.aniadir(linea.substr(0, pos), t[0]);

    }
    return is;
}



unsigned char& acciones::operator[](const string& c){
    return datos[c];
}

acciones& acciones::operator=(const acciones &otro){
    if(&otro != this){
        datos=otro.datos;
    }
    return *this;
}

void acciones::aniadir(const string accion, const unsigned char ariedad){
    pair<string, unsigned char> aux;
    aux.first= accion;
    aux.second= ariedad;
    datos.insert(aux);
}
bool acciones::pertenece(const string accion){
    auto it= datos.find(accion);

    if(it != datos.end()){
        return true;
    }else{
        return false;
    }
}





