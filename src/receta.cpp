//
// Created by angel on 22/11/19.
//

#include "receta.h"
#include "ingrediente.h"
#include "ingredientes.h"
#include "color.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;

receta::receta(){
    code="";
    plato=0;
    nombre="Undefined";
    calorias=hc=grasas=proteinas=fibra=0;
}
receta::receta(string cod, unsigned int plat, string nombr, list< pair<string , unsigned int> > ing, float caloria, float h, float grasa, float proteina, float fibr, instrucciones ins){
    code= cod;
    plato= plat;
    nombre= nombr;
    ings= ing;
    calorias= caloria;
    hc= h;
    grasas= grasa;
    proteinas= proteina;
    fibra= fibr;
    inst= ins;
}

void receta::nutricionales(const ingredientes &base_ingrs){

    for( auto it= ings.begin(); it != ings.end(); ++it){
        ingrediente ingrediente_aux=base_ingrs.get((*it).first);
        float multiplicador= (float)(*it).second/100.0;
        calorias+= (float)ingrediente_aux.getCalorias() * (float)multiplicador;
        hc+= (float)ingrediente_aux.getHc() * (float)multiplicador;
        grasas+= (float)ingrediente_aux.getGrasas() * (float)multiplicador;
        proteinas+= (float)ingrediente_aux.getProteinas() * (float)multiplicador;
        fibra+= (float)ingrediente_aux.getFibra() * (float)multiplicador;
    }
}


ostream& operator<< (ostream &os, const receta &rec){

    os<<rec.getCode()<<";"<<rec.getPlato()<<";"<<rec.getNombre()<<";";
    list < pair<string,unsigned int> >::const_iterator it;
    list < pair<string,unsigned int> >::const_iterator fin;
    fin = rec.ings.cend();
    fin--;
    for(it= rec.ings.cbegin(); it != fin; ++it)
        os << (*it).first<<" "<< (*it).second<<";";

    os << (*fin).first<<" "<< (*fin).second<<endl;

    return os;
}

//FUNCION AUXILIAR (NO PERTENECE A LA CLASE)
string obt_dig(const string linea){
    string numero="";
    for( auto c:linea){
        if(isdigit(c)){
            numero.push_back(c);
        }
    }
    return numero;
}

istream& operator>>(istream &is, receta &p) {

    string linea;
    getline(is, linea);

    auto pos = linea.find(";");

    //Code
    p.code= linea.substr(0, pos);
    linea= linea.substr(pos+1);

    //Plato
    string pl;
    pos= linea.find(";");
    pl= linea.substr(0, pos);
    pl= obt_dig(pl);
    p.plato= stoul(pl, 0, 10);
    linea=linea.substr(pos+1);

    //Nombre
    pos= linea.find(";");
    p.nombre= linea.substr(0,pos);
    linea= linea.substr(pos+1);

    //Ingredientes
    pos= linea.find(";");

    pair < string, unsigned int > ingr;
    string linea_aux;
    while (pos != string::npos){

        linea_aux= linea.substr(0, pos);
        string numero=obt_dig(linea_aux);
        int pos_aux= linea_aux.find(numero);
        ingr.first= linea_aux.substr(0,pos_aux-1);
        ingr.second= stoll(numero, 0, 10);

        p.ings.push_back(ingr);

        linea= linea.substr(pos+1);
        pos= linea.find(";");
    }

    //Ultimo ingrediente
    string numero=obt_dig(linea);
    pos= linea.find(numero);

    ingr.first= linea.substr(0, pos-1);
    ingr.second= stoll( numero, 0, 10 );
    p.ings.push_back(ingr);

    return is;
}



void receta::conValores(ostream &os){
    os << "Valores Nutricionales de la receta "<< *this <<" son: "<<endl<<"Calorias "<<calorias<<"\tHidratos de Carb.\t"<<hc<<"\tProteinas\t"<<proteinas<<"\tGrasas\t"<<grasas<<"\tFibra\t"<<fibra<<endl;
}

void receta::escribirSistematicamente(ostream &os){
    os << FBLU("CODE: ")<< code <<"\t"<<FBLU("NOMBRE: ")<<nombre<< "\t"<<FBLU("PLATO: ")<<plato<<endl;
}

void receta::escrituraCompleja(ostream &os){
    escribirSistematicamente(os);
    os<<UNDL(BOLD("Ingredientes: "))<<endl<<endl;
    for (const auto &item : ings) {
        os<<item.first<<" "<<item.second<<endl;
    }
    os<<endl<<UNDL(BOLD("Información Nutricional:"))<<endl<<endl<<"Calorias: "<<calorias<<endl<<"Hidratos de Carbono: "<<hc<<endl<<"Grasas: "<<grasas<<endl<<"Proteina: "<<proteinas<<endl<<"Fibra: "<<fibra<<endl<<endl;
    os<<UNDL(BOLD("Pasos a seguir: "))<<endl<<endl<<inst<<endl;

}

size_t receta::ningredientes()const{
    return ings.size();
}



