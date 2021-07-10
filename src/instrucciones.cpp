
#include "acciones.h"
#include "instrucciones.h"
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include "ingredientes.h"
#include "arbolbinario.h"

using namespace std;

extern acciones accs;
extern ingredientes ingrs;

acciones & instrucciones::acc= accs;
ingredientes & instrucciones::ingr= ingrs;


//FUNCIONA
ostream& operator<< (ostream &os,const instrucciones &ins){
    ArbolBinario<string> ab(ins.getDatos());
    string palabra= "";
    ArbolBinario<string>::postorden_iterador it= ab.beginpostorden();
    stack<string> pila;
    while(it!=ab.endpostorden()){
        palabra= *it;
        if(instrucciones::acc.pertenece((*it))){
            if(!pila.empty()) {
                if(instrucciones::acc[*it] == 50){
                    string lin= "";
                    lin= (*it) + "\t" + pila.top();
                    pila.pop();
                    if(!pila.empty()){
                        lin+= "\t" +  pila.top();
                        pila.pop();
                    }
                     os << lin << endl;

                }else{
                os << (*it) << "\t" << pila.top()<<endl;
                pila.pop();
                }
            }else{
                os << (*it)<<endl;
            }
        }else{
            pila.push(*it);
        }
        ++it;
    }
    return os;
}



/**
 * @brief Funcion auxiliar (Separa ingredientes compuestos como en el caso de Rpruebam.txt) Utilizada unicamente en operador >>
 * @param linea: linea con instruccions e ingredientes que la preceden o solo los ingredientes
 * @return Devuelve una pila con varios string cada uno con el nombre de un ingrediente
 */
stack<string> nameIngr(string linea){
    stack<string> res;
    size_t pos= linea.find(" ");
    string aux= linea.substr(0, pos);

        if(instrucciones::acc.pertenece(aux)){
            linea= linea.substr(pos+1);
        }
        istringstream ss(linea);
         aux= "";
         string nombre= "";
        while(ss >> aux){
            nombre= aux;
            while(instrucciones::ingr.get(nombre).getNombre() == "undefined" && ss >> aux){
                nombre+= " " + aux;
            }
            if(instrucciones::ingr.get(nombre).getNombre() != "undefined"){
                res.push(nombre);
            }

        }
        return res;



}


//ESTA FUNCIONA
istream& operator>> (istream &is, instrucciones &ins){

    stack< ArbolBinario<string> > pila;
    string linea="", ingr1="", ingr2="";
    size_t pos;
    getline(is, linea);
    while(!is.eof()){

        pos= linea.find(" ");
        string accion= "";
        accion= linea.substr(0, pos);

        int ariedad= instrucciones::acc[accion];

        if (ariedad == 49){// ariedad 1
            linea= linea.substr(pos+1);
            ArbolBinario<string> aux(accion);
            if(instrucciones::acc.pertenece(linea)){//Posible bug
                aux.Insertar_Hi(aux.getRaiz(), pila.top());
                pila.pop();
                pila.push(aux);
            }else{
                aux.Insertar_Hi(aux.getRaiz(), linea);
                pila.push(aux);
            }


        }else if ((int)ariedad == 50){
            linea= linea.substr(pos+1);
            ArbolBinario<string> aux(accion);
            if(instrucciones::acc.pertenece(linea)){
                aux.Insertar_Hd(aux.getRaiz(), pila.top());
                pila.pop();
                aux.Insertar_Hi(aux.getRaiz(), pila.top());
                pila.pop();
                pila.push(aux);
            }else{
                string linea2= linea;
                stack<string> pila_ingr= nameIngr(linea2);
                if(pila_ingr.size() == 1) {

                    ingr1 = linea.substr(accion.length() - 3);
                    aux.Insertar_Hd(aux.getRaiz(), ingr1);
                    aux.Insertar_Hi(aux.getRaiz(), pila.top());
                    pila.pop();
                    pila.push(aux);
                }else if( pila_ingr.size() == 2){
                    aux.Insertar_Hd(aux.getRaiz(), pila_ingr.top());
                    pila_ingr.pop();
                    aux.Insertar_Hi(aux.getRaiz(), pila_ingr.top());
                    pila_ingr.pop();
                    pila.push(aux);
                }


            }

        }
        linea = "";
        getline(is, linea);
    }
    ins.setDatos(pila.top());
    pila.pop();

    if( !pila.empty() ){
        cout<< "----------------------Pila no vacia----------------------"<<endl<< " LINEA 88 INSTRUCIONES.CPP";
    }

    return is;

}



instrucciones& instrucciones::operator=(const instrucciones &otro){
    if(&otro != this){
        datos= otro.datos;
    }

    return *this;
}


void instrucciones::setDatos(ArbolBinario<string> &d){
    datos= d;
}
instrucciones instrucciones::operator+(const instrucciones &otro){
    instrucciones nuevo;
    ArbolBinario<string> res("Acompañar");
    ArbolBinario<string> aux_(datos);
    res.Insertar_Hi(res.getRaiz(), aux_);

    ArbolBinario<string> aux(otro.getDatos());

    res.Insertar_Hd(res.getRaiz(), aux);
    nuevo.setDatos(res);
    return nuevo;
}






//-------------------------------------------------------------------------
//Intentos (Para consultar)

//Primer Intento (No sirve)
/*istream& operator>> (istream &is, instrucciones &ins){

    queue< ArbolBinario<string> > pila;
    string linea="", ingr1="", ingr2="";
    size_t pos;
    getline(is, linea);
    while(!is.eof()){

        pos= linea.find(" ");
        string accion= "";
        accion= linea.substr(0, pos);

        int ariedad= instrucciones::acc[accion];

        if (ariedad == 49){// 1
            linea= linea.substr(pos+1);
            ArbolBinario<string> aux(accion);
            if(instrucciones::acc.pertenece(linea)){//                               Posible a modificar con /n o /r o " "
                aux.Insertar_Hi(aux.getRaiz(), pila.front());
                pila.pop();
                pila.push(aux);
            }else{
                aux.Insertar_Hi(aux.getRaiz(), linea);
                pila.push(aux);
            }


        }else if ((int)ariedad == 50){
            linea= linea.substr(pos+1);
            ArbolBinario<string> aux(accion);
            if(instrucciones::acc.pertenece(linea)){ //posible a cambiar
                aux.Insertar_Hi(aux.getRaiz(), pila.front());
                pila.pop();
                aux.Insertar_Hd(aux.getRaiz(), pila.front());
                pila.pop();
                pila.push(aux);
            }else{
                ingr1= linea.substr(accion.length()-3);
                aux.Insertar_Hi(aux.getRaiz(), ingr1);
                aux.Insertar_Hd(aux.getRaiz(), pila.front());
                pila.pop();
                pila.push(aux);


            }

        }
        linea = "";
        getline(is, linea);
    }
    ins.setDatos(pila.front());
    pila.pop();

    if( !pila.empty() ){
        cout<<endl<< "----------------------Pila no vacia----------------------"<<endl<< " LINEA 88 INSTRUCIONES.CPP";
    }

    return is;

}*/

//Segundo intento (No sirve)

/*ostream& operator<< (ostream &os,const instrucciones &ins){
    ArbolBinario<string> ab(ins.getDatos());
    string accion= "";
    string linea= "";
    ArbolBinario<string>::postorden_iterador it= ab.beginpostorden();
    while(it!=ab.endpostorden()){
        //if(instrucciones::acc.pertenece((*it))) {
            linea = (*it);
            ++it;
            int ariedad = instrucciones::acc[linea] - 48;
            while (!instrucciones::acc.pertenece((*it)) && it != ab.endpostorden() && ariedad > 0) {
                linea += " " + (*it);
                ++it;
                ariedad--;
            }
            os << linea << endl;
            linea = "";
        //}
    }
    return os;
}*/

//Prueba
/*istream& operator>> (istream &is, instrucciones &ins){


    //CAMPO DE PRUEBAS


    stack< ArbolBinario<string> > pila;
    ArbolBinario<string> aux("Cortar");
    aux.Insertar_Hi(aux.getRaiz(), "Patata");
    pila.push(aux);
    ArbolBinario<string> aux2("Batir");
    aux.Insertar_Hi(aux.getRaiz(), "Huevo");
    pila.push(aux);
    ArbolBinario<string> res("Mezclar");
    res.Insertar_Hi(res.getRaiz(), pila.top());
    pila.pop();
    res.Insertar_Hd(res.getRaiz(), pila.top());
    pila.pop();
    ins.setDatos(res);
    return is;


}*/

//NO SIRVE
/*void instrucciones::cargarStatics(const ingredientes &ingrs, const acciones &accs){
    ingredientes instrucciones::ingr= ingrs;
    acciones instrucciones::acc= accs;
}*/

//SEGUNDO INTENTO (NO SIRVE)
/*istream& operator>> (istream &is, instrucciones &ins){

    stack< ArbolBinario<string> > pila;


    int ariedad= 0;
    while(!is.eof()){
        string linea= "", aux_s="", ingr1= "", ingr2= "", accion= "";
        getline(is, linea);
        ArbolBinario<string> aux;
        istringstream ss(linea);

        int cont=0;

        while( ss>>aux_s ){
            accion= aux_s;
            ArbolBinario<string> aux(accion);
            if(cont == 0){
                ariedad= instrucciones::acc[accion];
            }else if( cont == 1){
                if( ariedad == 49){//1
                    while( ss >> aux_s){
                        ingr1+= " " + aux_s;
                    }

                }else if( ariedad == 50){//2
                    while(instrucciones::ingr.get(ingr1).getNombre() == "undefined" && is>> aux_s){
                        ingr1 += " " + aux_s;
                    }
                }

            }else if( cont == 2){
                if(ariedad == 49){
                    cout<<endl<< "Error al leer ariedad 1 en contador == 2"; //Se puede borrar
                }else {
                    while( ss >> aux_s){
                        ingr2+= " " + aux_s;
                    }
                }

            }
            cont++;
        }

        if(ariedad == 1){
            if( ingr1 == ""){
                aux.Insertar_Hi(aux.getRaiz(), pila.top());
                pila.pop();
                pila.push(aux);
            }else{
                aux.Insertar_Hi(aux.getRaiz(), ingr1);
                pila.push(aux);
            }

        }else if (ariedad == 2){
            if( ingr1 == ""){
                if( ingr2 != "") {
                    cout << endl << "Error ingr2 distinto de nada con ingr1 == "" "; //Borrar
                }

                aux.Insertar_Hi(aux.getRaiz(), pila.top());
                pila.pop();
                aux.Insertar_Hd(aux.getRaiz(), pila.top());
                pila.pop();
                pila.push(aux);

            }else{
                if( ingr2 != ""){
                    aux.Insertar_Hi(aux.getRaiz(), ingr1);
                    aux.Insertar_Hd(aux.getRaiz(), ingr2);
                    pila.push(aux);
                }else{
                    aux.Insertar_Hi(aux.getRaiz(), ingr1);
                    aux.Insertar_Hd(aux.getRaiz(), pila.top());
                    pila.pop();
                    pila.push(aux);
                }
            }
        }


    cont=0;
    }
    ins.setDatos(pila.top());
    pila.pop();
    if(!pila.empty()){
        cout<<endl<<"La pila vuelve a no quedar vacia :'D";
    }
return is;

}*/


//NO sirve (puede ser util) Fragmento que no funciona del operador >> que funciona
/*string ingraux="";
pos= linea.find(" ");
do{
    ingr1= instrucciones::ingr.get(ingraux).getNombre();
    ingraux= linea.substr(0, pos);
    pos++;
}while( ingr1 == "undefined" );
pos= linea.rfind(ingr1);
linea= linea.substr(pos);
ingr2= linea;
cout<<"Ver si salen solo ingredientes aqui: "<<ingr1<<"AHORA EL 2 "<<ingr2<<endl<<endl;
aux.Insertar_Hi(aux.getRaiz(), ingr1);
if(instrucciones::acc.pertenece(linea) && ingr2 != ingr1){//Tambien posible a cambiar
    aux.Insertar_Hd(aux.getRaiz(), pila.top());
    pila.pop();
    pila.push(aux);
}else{
    aux.Insertar_Hd(aux.getRaiz(), ingr2);
    pila.push(aux);
}*/