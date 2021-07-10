//
// Created by angel on 28/11/19.
//
#include "ingrediente.h"
#include "recetas.h"
#include "ingredientes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


//Solucion propuesta en clase
recetas sol_optimal(int valor_max, const recetas & recs){

    vector< vector<float> > matriz( recs.size()+1, vector<float>(valor_max+1) );
                                                           //Se reserva memoria e inicializa la matriz con 0
    recetas::const_iterator it= recs.cbegin();


    for(int f=1; f<=recs.size(); f++, ++it){
        for(int c=0; c<=valor_max; c++){

            if( c< (*it).getCalorias() ){
                matriz[f][c]= matriz[f-1][c];
            }else{
                matriz[f][c]= max( matriz[f-1][c], matriz[f-1][c - (*it).getCalorias()] + (*it).getRazon() );
            }

        }
    }

    recetas res;
    it= recs.cend();
    --it;
    for(int f= recs.size(), c=valor_max; f > 0 ; f--, --it){
        if(matriz[f][c] != matriz[f-1][c]){
            res.aniadir(*it);
            c-= (*it).getCalorias();
        }
    }

    return res;
}



int main(int argc,char *argv[]){

    if (argc!=4){
        cout<<"Los argumentos son: "<<endl<<"1) Un fichero con recetas."<<endl << "2) Un fichero con los ingredientes. "<<endl<< "3) Numero maximo de calorias. "<<endl;
        return 0;
    }
    ifstream f(argv[1]);
    if (!f){
        cout<<"No existe el fichero "<<argv[1]<<endl;
    }
    ifstream b(argv[2]);
    if (!b){
        cout<<"No existe el fichero "<<argv[2]<<endl;
    }
    string aux= argv[3];
    float valor_max=stof(aux);
    ingredientes ingrs;
    b>>ingrs;

    recetas rall;
    f>>rall;
    rall.inicializa_valores(ingrs);

    cout<<"\tConjunto de recetas con sus valores nutricionales: "<<endl;
    rall.imprimirConValores(cout);


    recetas res= sol_optimal(valor_max, rall);

    float Cal_total=0.0, Pro_total=0.0;
    for(recetas::const_iterator it=res.cbegin(); it!= res.cend(); ++it){
        Cal_total+= (*it).getCalorias();
        Pro_total+= (*it).getProteinas();
    }


    cout << endl <<"Las recetas elegidas son: "<< endl<< res;

    cout<<endl<< "Calorias totales "<< Cal_total<<"  Proteinas totales "<<Pro_total<<endl;

}