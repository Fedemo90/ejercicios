#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//--------------- CLASE AUTO------------------------------------
class Auto {
    public:
        Auto (char*, int);
        ~Auto();
        char modelo[40];
        int anio;
        Auto * sig;

};

Auto::Auto (char * Mod, int A){

    strcpy(modelo, Mod);
    anio = A;
    sig = NULL;
}

Auto::~Auto(){

    cout << "Borrando a " << modelo << "\n\n";
}

//--------------- CLASE CLIENTES------------------------------------
class Cliente {
    public:
        Cliente (char *, char*);
        char nombre[30];
        char telefono[20];
        Cliente * sig;
        Auto * primerauto;
        void agregarAuto (char *, int);
        int cantAutos();
        void vaciarAutos();

};

Cliente::Cliente (char * N, char * T ){

    strcpy(nombre, N);
    strcpy(telefono, T);
    sig = NULL;
    primerauto = NULL;

}

void Cliente::agregarAuto(char * Mod, int anio){
    Auto * Au, *A;

    Au = new Auto(Mod, anio);

    if(!primerauto){
        primerauto = Au;
        return;
    }

    A = primerauto;

    while ( A->sig){
        A = A->sig;
    }

    A->sig = Au;

}

int Cliente::cantAutos(){
    Auto * AB;
    int total = 0;

    AB = primerauto;

    while (AB){
        total++;
        AB = AB->sig;
    }

    return total;
}


void Cliente::vaciarAutos(){
    Auto * AB;

    AB = primerauto;

    while (primerauto){
        primerauto = AB->sig;
        delete AB;
        AB = primerauto;
    }

}

//--------------- CLASE LISTA CLIENTES------------------------------------
class ListaClientes {
    private:
        Cliente * inicio;

    public:
        ListaClientes ();
        Cliente * buscar(char *);
        void agregar(char *, char *);
        int cantClientes();
};

ListaClientes::ListaClientes(){

    inicio = NULL;
}

void ListaClientes::agregar(char * Nom, char * Tel){
    Cliente * CL, *C;

    CL = new Cliente(Nom, Tel);

    if (!inicio){
        CL->sig = inicio;
        inicio = CL;
        return;
    }

    C = inicio;

    while (C->sig){
        C = C->sig;
    }

    C->sig = CL;

}

Cliente * ListaClientes::buscar (char * Nom){
    Cliente * CL;

    CL = inicio;

    while (CL){
        if (!stricmp(CL->nombre, Nom)){
            return CL;
        }
        CL = CL->sig;
    }

    printf("\n No existe el cliente");

    return NULL;

}

int ListaClientes::cantClientes(){

    Cliente * CL;
    int total = 0;

    CL = inicio;

    while (CL){
        total++;
        CL = CL->sig;
    }

    return total;
}

int main() {
    ListaClientes * lc = new ListaClientes;  // la guirnalda en sí

    lc->agregar("Pepe", "4555-6565");  //agrega Cliente (lista principal)
    lc->agregar("Maria", "4444-3232");
    lc->agregar("Carlos", "5460-1111");

    lc->buscar("Pepe")->agregarAuto("Renault 12", 1980);  //agrega Auto a un Cliente (lista secundaria)
    lc->buscar("Pepe")->agregarAuto("Renault Fluence", 2013);

    printf("\n Pepe tiene %d autos\n\n" , lc->buscar("Pepe")->cantAutos() );  //debe dar 2

    lc->buscar("Pepe")->vaciarAutos();

    printf("\n Pepe tiene %d autos\n\n" , lc->buscar("Pepe")->cantAutos() );  //debe dar 0

    printf("\n La guirnalda tiene %d clientes\n\n" , lc->cantClientes() );  //debe dar 3

}
