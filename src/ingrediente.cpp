#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "ingrediente.h"

using namespace std;

ingrediente::ingrediente(){
  nombre="";
  calorias=0;
  hc=0,
  proteinas=0;
  grasas=0;
  fibra=0;
  tipo="";
}

ingrediente::ingrediente(string n, int c,float hidratos,float p,float gr,float f,string t=""){
  nombre=n;
  calorias=c;
  hc=hidratos,
  proteinas=p;
  grasas=gr;
  fibra=f;
  tipo=t;
}

bool ingrediente::operator==(const ingrediente &otro){
  return nombre==otro.getNombre() && tipo==otro.getTipo();
}

bool ingrediente::operator!=(const ingrediente &otro){
  return nombre!=otro.getNombre();
}

ostream& operator<< (ostream &os, const ingrediente &ingr){

 os<<ingr.getNombre()<<";"<<ingr.getCalorias()<<";"<<ingr.getHc()<<";"<<ingr.getProteinas()<<";"<<ingr.getGrasas()<<";"<<ingr.getFibra()<<";"<<ingr.getTipo()<<endl;

 return os;
}

istream& operator>>(istream &is, ingrediente &p){

  string linea;
  getline(is,linea);
  //nombre
  string n;
  int pos=linea.find(";");
  n=linea.substr(0,pos);
  if (n != "Alimento (100 gramos)"){
  p.nombre=n;
  linea=linea.substr(pos+1);
  //calorias
  string c;
  pos=linea.find(";");
  c=linea.substr(0,pos);
  p.calorias=stoi(c.c_str());
  linea=linea.substr(pos+1);
  //hc
  string h;
  pos=linea.find(";");
  h=linea.substr(0,pos);
  p.hc=stof(h.c_str());
  linea=linea.substr(pos+1);
  //proteinas
  string pr;
  pos=linea.find(";");
  pr=linea.substr(0,pos);
  p.proteinas=stof(pr.c_str());
  linea=linea.substr(pos+1);
  //grasa
  string g;
  pos=linea.find(";");
  g=linea.substr(0,pos);
  p.grasas=stof(g.c_str());
  linea=linea.substr(pos+1);
  //fibra
  string fi;
  pos=linea.find(";");
  fi=linea.substr(0,pos);
  p.fibra=stof(fi.c_str());
  //tipo
  p.tipo=linea.substr(pos+1);
  pos=p.tipo.find("\r");
  p.tipo=p.tipo.substr(0,pos);
}

  return is;

}
