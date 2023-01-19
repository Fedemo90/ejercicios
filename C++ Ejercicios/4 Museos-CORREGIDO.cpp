#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

//--------------- CLASE VISITANTE -----------------------------
class Visitante {
    public:
        Visitante (char *);
        Visitante * SIG;
        char NOM[20];

};

Visitante::Visitante (char * Nom){

    cout <<"Creo visitante";

    strcpy(NOM, Nom);
    SIG = NULL;
}


//--------------- CLASE MUSEO -----------------------------
class Museo {
    public:
        Museo (char *);
        Museo * SIG;
        Visitante * INICIO;
        char NOM[40];
};

Museo::Museo (char * Nom){

    cout <<"Creo museo:";

    strcpy(NOM, Nom);
    SIG = NULL;
    INICIO = NULL;
}


//--------------- CLASE REGISTRO -----------------------------
class RegistroVisitas {
    private:
        Museo * INICIO;
        void agregarMuseo (Museo *);
        void  agregarVisitante (Visitante *, Museo *);

    public:
        RegistroVisitas ();
        void nuevoMuseo(char *);
        void registrarVisita(char *, char *);
        void borrarMuseosPocoVisitados();
        void mirar ();
};

RegistroVisitas::RegistroVisitas (){

    INICIO = NULL;
}

void RegistroVisitas::nuevoMuseo (char * NomM){

    Museo * M;
    M = new Museo (NomM);

    agregarMuseo (M);
}

void RegistroVisitas::agregarMuseo (Museo * Mus){

    Museo * M;

    if (!INICIO){
        INICIO = Mus;
        return;
    }
    M = INICIO;

    while (M->SIG){
        M = M->SIG;
    }
    M->SIG = Mus;
}

void RegistroVisitas::registrarVisita(char * NomM, char * NomV){

    Visitante * V;
    Museo * M;

    V = new Visitante(NomV);

    M = INICIO;

    while (M){
        if (!stricmp(M->NOM, NomM)){
            agregarVisitante (V, M);
            return;
        }
        M = M->SIG;
    }

    cout <<"EL MUSEO NO EXISTE";

}

void RegistroVisitas::agregarVisitante (Visitante * Vis, Museo * Mus){

    Visitante * V;

    if(!Mus->INICIO){
        Mus->INICIO = Vis;
        return;
    }

    V = Mus->INICIO;

    while (V->SIG){
        V = V->SIG;
    }
    V->SIG = Vis;

    return;

}

void RegistroVisitas::mirar(){

    Visitante * V;
    Museo * M;

    M = INICIO;

    while (M){
        cout << "\n\n\t\tMUSEO: " << M->NOM << "\n\n\t\tVisitantes: ";
        V = M->INICIO;
        while (V){
            cout << "\n\t\t\t" << V->NOM;
            V = V->SIG;
        }
        M = M->SIG;
    }
}

void RegistroVisitas::borrarMuseosPocoVisitados(){

    Museo * M, *ANT;
    Visitante * V;
    int cont;

    M = INICIO;
    ANT = NULL;

    while (M){
        V = M->INICIO;
        cont = 0;

        while (V){
            cont++;
            V = V->SIG;
        }

        if (cont < 2){
            if (!ANT){
                INICIO = M->SIG;
                delete M;
                M = INICIO;
            }
            else if (ANT && (M->SIG)){
                ANT->SIG = M->SIG;
                delete M;
                M = ANT->SIG;
            }
            else if (!(M->SIG)){
                ANT->SIG = NULL;
                delete M;
                M = NULL;
            }
        }
        else
            ANT = M;
            M = M->SIG;
    }
}

int main() {
	RegistroVisitas * lista = new RegistroVisitas;

	lista->nuevoMuseo("MALBA");
    lista->nuevoMuseo("Museo Historico Nacional");
    lista->nuevoMuseo("Museo de Ciencias Naturales");

	lista->registrarVisita("MALBA", "Pepe Gomez");
	lista->registrarVisita("Museo Historico Nacional", "Pepe Gomez");
	lista->registrarVisita("MALBA", "Maria Alvarez");
	lista->registrarVisita("Museo de Ciencias Naturales", "Pepe Gomez");
    lista->registrarVisita("Museo de Ciencias Naturales", "Roberto Sanchez");

    printf("Antes de borrar: \n");

    lista->mirar();

	lista->borrarMuseosPocoVisitados();  //borra de la lista a los museos con menos de 2 visitas, para este ejemplo es unicamente el M. Hist. Nac.

    printf("\n\nDespues de borrar: \n");

    printf("\n\n\n");

	lista->mirar();

	printf("\n\n\n");
}
