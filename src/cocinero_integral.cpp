//
// Created by angel on 30/12/19.
//
#include "arbolbinario.h"
#include "ingrediente.h"
#include "ingredientes.h"
#include "recetas.h"
#include "instrucciones.h"
#include "acciones.h"
#include "color.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

acciones accs;
ingredientes ingrs;

int main(int argc,char *argv[]){

    if(argc != 5){
        cout<< "Para ejecutar: bin/cocinero_integral datos/Acciones.txt datos/recetas.txt datos/ingredientes.txt datos/instrucciones\n";
        return 0;
    }

    //Cargar acciones
    string na= argv[1];
    ifstream a(na);
    if (!a){
        cout<<"No puedo abrir acciones "<<na<<endl;
        cout<< "Para ejecutar: bin/cocinero_integral datos/Acciones.txt datos/recetas.txt datos/ingredientes.txt datos/instrucciones\n";
        return 0;
    }
    a >> accs;
    a.close();

    //Cargar recetas
    string nb= argv[2];
    ifstream b(nb);
    if (!b){
        cout<<"No puedo abrir recetas "<<nb<<endl;
        cout<< "Para ejecutar: bin/cocinero_integral datos/Acciones.txt datos/recetas.txt datos/ingredientes.txt datos/instrucciones\n";
        return 0;
    }
    recetas recs;
    b >> recs;
    b.close();

    //Cargar ingredientes
    string nc= argv[3];
    ifstream c(nc);
    if(!c){
        cout <<"No puedo abrir ingredientes "<<nc<<endl;
        cout<< "Para ejecutar: bin/cocinero_integral datos/Acciones.txt datos/recetas.txt datos/ingredientes.txt datos/instrucciones\n";
        return 0;
    }
    c >> ingrs;
    c.close();

    //instrucciones::cargarStatics(ingrs, accs);

    //Cargo valores nutricionales
    recs.inicializa_valores(ingrs);

    //Leo las recetas en formato corto
    recs.escribirSistematicamente(cout);

    cout <<endl<<"Pulse una tecla..."<<endl;

    recs.cargarInstrucciones(argv[4]);

    cout<<endl<<FGRN("-------Se han cargado las instrucciones-------");
    cout<<endl<<endl<<"De que receta quiere obtener informacion: "<<endl;
    string codigo="";
    cin>>codigo;
    recs[codigo].escrituraCompleja(cout);

    cin.get();

    cout<<endl<<"Inserte el codigo de la primera receta a fusionar: ";
    string fusion1= "", fusion2= "";
    cin>> fusion1;
    cout<<endl<<"Inserte el codigo de la segunda receta a fusionar: "<<endl;
    cin>> fusion2;
    receta fusionada= recs.juntarRecetas(fusion1, fusion2);
    cout<<endl<<"La receta producto de la fusion realizada es: "<<endl;
    fusionada.escrituraCompleja(cout);

    return 0;


    




}




