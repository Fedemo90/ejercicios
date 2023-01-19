/*

Se cuenta con una clase Hospital que posee una lista enlazada de
objetos Medico. Cada Medico tiene a su vez una lista de Paciente.

Se pide:
--------

1) Declarar las 3 clases

2) Escribir el método

		void Hospital::medicosDelPaciente(char *)

que recibe el nombre de un Paciente y muestra en pantalla todos
los médicos con quienes se atiende.



3) Escribir el método

		Medico * Hospital::medicoConMenosPacientes(void)

que retorna un puntero al Medico que menos pacientes tenga.
Se sabe que los médicos tienen siempre pacientes, al menos uno.


*/
 #include <stdio.h>
 #include <stdlib.h>
 #include <iostream>
 #include <string.h>

using namespace std;


//---------------- PACIENTES---------------------------------

class PACIENTE{

    public:
        PACIENTE (char *);
        PACIENTE * SIG;
        char nombre[20];

};

PACIENTE::PACIENTE(char * Nom){

    strcpy(nombre, Nom);
    SIG = NULL;

}

//---------------- MEDICOS---------------------------------

class MEDICO{

    public:
        MEDICO(char *);
        MEDICO * SIG;
        char nombre[20];
        PACIENTE * INICIO;
};

MEDICO::MEDICO(char * Nom){

    strcpy(nombre, Nom);
    INICIO = NULL;
    SIG = NULL;
}

//---------------- HOSPITAL ---------------------------------

class HOSPITAL{

    private:
        MEDICO * INICIO;
        void PonerMed(MEDICO *);
        void PonerPac(PACIENTE *, char *);
        MEDICO * medicoConMenosPacientes();

    public:
        HOSPITAL();
        void medicosDelPaciente(char *);

        int BUSCARPAC (MEDICO *, char *);
        void agregarMedico (char *);
        void agregarPac (char *, char *);
        void  verMedicos();


};

HOSPITAL::HOSPITAL(){
    INICIO = NULL;
}

void HOSPITAL::medicosDelPaciente(char * NomPac){
    MEDICO * MED;

    MED = INICIO;

    cout << "Medicos del paciente: " << NomPac << "\n\n\n";
    while (MED){
        if (BUSCARPAC (MED, NomPac)){
            cout << MED->nombre <<"\n\n";
        }
        MED = MED->SIG;
    }

}

MEDICO * HOSPITAL::medicoConMenosPacientes(){
    MEDICO * MED, *MEDmenos;
    PACIENTE * PAC;
    int CantPac, menorCant;

    MED = INICIO;

    while (MED){
        PAC = MED->INICIO;
        CantPac = 0;

        while (PAC){
            CantPac++;
            PAC = PAC->SIG;
        }
        if (MED != INICIO){
            if (CantPac < menorCant){
                menorCant = CantPac;
                MEDmenos = MED;
            }
        }
        else{
            menorCant = CantPac;
            MEDmenos = MED;
        }

        MED = MED->SIG;
    }

    return MEDmenos;

}

int HOSPITAL::BUSCARPAC (MEDICO * MED, char * Nom){
    PACIENTE * PAC;

    PAC = MED->INICIO;

    while (PAC){
        if (!stricmp(PAC->nombre,Nom)){
            return 1;
        }
        PAC = PAC->SIG;
    }

    return 0;
}
void HOSPITAL::agregarMedico (char * Nom){
    MEDICO * MED;
    MED = new MEDICO(Nom);
    PonerMed(MED);

}

void HOSPITAL::PonerMed (MEDICO * MED){
    MEDICO * M;
    M = INICIO;

    if (!INICIO){
        INICIO = MED;
        return;
    }

    while (M->SIG){
        M = M->SIG;
    }

    M->SIG = MED;

}

void HOSPITAL::agregarPac (char * Nom, char * Med){
    PACIENTE * PAC;

    PAC = new PACIENTE (Nom);

    PonerPac (PAC, Med);

}

void HOSPITAL::PonerPac (PACIENTE * PAC, char * Med){

    MEDICO * M;
    PACIENTE * P;
    M = INICIO;

    while (M){
        if (!stricmp(M->nombre, Med)){
            P = M->INICIO;
            if (!P){
                M->INICIO = PAC;
                return;
            }

            while (P->SIG){
                P = P->SIG;
            }
            P->SIG = PAC;
            return;
        }

        M = M->SIG;
    }

    cout << "No existe Medico con ese nombre";

}

void HOSPITAL::verMedicos(){
    MEDICO * M;
    M = INICIO;

    cout << "LISTADO DE MEDICOS\n\n";

    while(M){
        cout << M->nombre << "\n\n";
        M = M->SIG;
    }

}

int main(){

    char  nombreMed [20], nombrePac[20];

    HOSPITAL LISTA;

    cout <<"Agregar medicos o poner FIN para finalizar\n\n\t\t";

    cin >> nombreMed;
    cout <<"\n\t\t";

    while(stricmp(nombreMed,"FIN")){
        LISTA.agregarMedico(nombreMed);
        cin >> nombreMed;
        cout <<"\n\t\t";
    }

    LISTA.verMedicos();

    cout <<"\n Agregar pacientes o FIN para finalizar \n\n\t\t";

    cout <<"Nombre del paciente: ";
    cin >> nombrePac;
    cout << "\n\n\t\t";

    if (stricmp(nombrePac,"FIN")){
        cout << "Nombre del Medico: ";
        cin >> nombreMed;
        cout << "\n\n\t\t";
    }


    while(stricmp(nombrePac,"FIN")){
        LISTA.agregarPac(nombrePac, nombreMed);
        cout <<"Nombre del paciente: ";
        cin >> nombrePac;
        cout << "\n\n\t\t";

        if (stricmp(nombrePac,"FIN")){
            cout << "Nombre del Medico: ";
            cin >> nombreMed;
            cout << "\n\n\t\t";
        }

    }

    cout <<"Ingrese nombre del paciente para ver Medicos \n\nNombre del paciente: ";
    cin >> nombrePac;
    cout << "\n\n\t\t";
    LISTA.medicosDelPaciente(nombrePac);



}
