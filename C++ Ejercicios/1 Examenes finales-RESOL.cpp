
/*

La siguiente lista enlazada se utiliza para almacenar los exámenes finales rendidos en una carrera.

Se pide hacer las clases y métodos necesarios para que funcione el main provisto.

Debe haber una lista enlazada de Materias, que cada una posee una lista enlazada de Finales.
Además debe existir una clase TUP, que representa a la lista múltiple y es con la cual se comunica el main.

Cada final tiene un nombre de estudiante y nota obtenida.

El método imprimePromedios muestra los nombres de las materias, y el promedio de las notas existentes.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class FINAL {

    public:
        FINAL (char *, float);
        char NOM[20];
        float NOTA;
        FINAL * SIG;


};

FINAL::FINAL(char * S, float N){

    strcpy(NOM, S);
    NOTA = N;
    SIG = NULL;

}

class MATERIA{

    public:
        MATERIA (char *);
        MATERIA * SIG;
        FINAL * INICIO;
        char NOM[20];

};

MATERIA::MATERIA(char * S){
    strcpy(NOM, S);
    INICIO = NULL;
    SIG = NULL;
}

class TUP{

    private:
        MATERIA * INICIO;
        MATERIA * BUSCAR (char *);

    public:
        TUP();
        void crearMateria (char *);
        void inscribirFinal(char *, char *, float);
        void imprimePromedios();

};

TUP::TUP (){
    INICIO = NULL;
}

void TUP::crearMateria (char * Mat){

    MATERIA * PMAT;

    if (!INICIO){
        PMAT = new MATERIA (Mat);
        INICIO = PMAT;
        return;
    }

    PMAT = BUSCAR(Mat);

    if (PMAT){
        cout << "LA MATERIA YA EXISTE";
        return;
    }

    PMAT = new MATERIA (Mat);

    PMAT->SIG = INICIO;
    INICIO = PMAT;

}

MATERIA * TUP::BUSCAR(char * S){

    MATERIA * PMAT;

    PMAT = INICIO;

    while (PMAT){
        if (!stricmp(PMAT->NOM, S) ){
            return PMAT;
        }
        PMAT = PMAT->SIG;
    }

    return NULL;
}

void TUP::inscribirFinal(char * Nom, char * Mat, float nota){
    MATERIA * PMAT;
    FINAL * PF;

    PF = new FINAL (Nom, nota);

    PMAT = BUSCAR(Mat);

    if (PMAT){
        PF->SIG =PMAT->INICIO;
        PMAT->INICIO = PF;
        return;
    }

    cout << "NO EXISTE LA MATERIA\n\n";
}

void TUP::imprimePromedios(){

    MATERIA * PMAT;
    FINAL * PF;
    int contNotas;
    float prom;

    cout <<"LISTA DE MATERIAS\n\n\n";

    PMAT = INICIO;

    while (PMAT){
        cout << PMAT->NOM << ": ";
        PF = PMAT->INICIO;
        prom = 0;
        contNotas = 0;
        if (PF){
            while (PF){
                contNotas++;
                prom = prom + PF->NOTA;
                PF = PF->SIG;
            }
            prom = prom / contNotas;
            cout << prom;
        }
        cout << "\n\n";
        PMAT = PMAT->SIG;
    }


}



int main() {

	TUP * tup = new TUP;

	tup->crearMateria("Matematica");
	tup->crearMateria("Programacion 1");
	tup->crearMateria("Materia fantasma");

	tup->inscribirFinal("Pepe Gomez", "Matematica", 2);
	tup->inscribirFinal("Maria Lopez", "Matematica", 8);
	tup->inscribirFinal("Bart Simpson", "Programacion 1", 8);

	tup->imprimePromedios();
	// debe imprimir:
	//
	// Matematica: 5
	// Programacion 1: 8
}
