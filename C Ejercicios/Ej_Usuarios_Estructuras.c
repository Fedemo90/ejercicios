/*  Dada la siguiente estructura para almacenar datos de usuarios de un sistema:

struct fecha { int dia; int mes; int anio; }

struct usuario {
	char email[100];
	struct fecha ingresos[30];
}

En el vector ingresos se encuentran las fechas de ingreso al sistema por el usuario,
almacenadas sin ningún orden en particular.

Las posiciones sin utilizar del vector ingresos se indican con una fecha que tiene sus
tres componentes en -1. Esto es así porque tenemos lugar para almacenar hasta 30 ingresos,
pero algunos usuarios habrán entrado menos veces.

Se pide:

1) Determine cuánto espacio ocupa en memoria un vector de 10 de estas struct usuario.

2) Realice una función que reciba un vector de usuarios y muestre en pantalla el
email del usuario que más ingresos realizó al sistema.

3) Realice una función que reciba el vector de usuarios y muestre en pantalla
los emails y la última fecha en la que cada uno ingresó al sistema.

4) Realice una función que reciba el vector de usuarios y muestre en pantalla
el email del usuario que hace más tiempo que no entra (contando desde su última vez).  */

#include <stdio.h>
#include <string.h>
#include <time.h>
#define NUM 10
#define ING 30


struct fecha {
    int dia;
    int mes;
    int anio;
};

struct usuario {
    char email [100];
    struct fecha ingresos[ING];

};

void MAYOR_ING (struct usuario [], int);
void ULTIMO_ING (struct usuario [], int, int);
void MAS_TIEMPO (struct usuario CL [], int, int);
unsigned int dias (struct fecha);


int main()
{
    int i, j, seguir = 1;
    struct usuario Clientes[NUM] = {};

    printf("El tamaño del Vector de estructuras es de %d bytes\n\n", sizeof(Clientes));

    char emails[NUM] [30] = {"alessoquora@gmail.com", "mirianhota@hotmail.com", "zozitla@gmail.com", "dianaParedes@yahoo.com", "LorenziniAbogados@gmail.com"};// "Kikajola@gmail.com", "ulise_diaz@hotmail.com", "omartoribio@gmail.com", "gmail.com","lokounpoco@outlook.com"};

    for (i = 0 ; i < NUM ; i++){
        for(j = 0 ; j < ING ; j++){
            Clientes[i].ingresos[j].dia = -1;
            Clientes[i].ingresos[j].mes = -1;
            Clientes[i].ingresos[j].anio = -1;
        }
    }

    for (i = 0 ; i < NUM ; i++)
        strcpy(Clientes[i].email, emails[i]);

    printf("Ingrese las fechas de ingresos de:\n\n");

    for (i = 0 ; i < NUM ; i++){
        printf("\n%s: \n\n", Clientes[i].email);
        seguir = 1;
        for(j = 0 ; j < ING && seguir == 1; j++){
            fflush(stdin);
            scanf("%d/%d/%d", &Clientes[i].ingresos[j].dia, &Clientes[i].ingresos[j].mes, &Clientes[i].ingresos[j].anio);
            printf("Ingrese 1 para seguir o -1 para finalizar: ");
            fflush(stdin);
            scanf("%d", &seguir);

        }
    }
    for(i = 0; i < NUM; i++){
        printf("%d/%d/%d \n\n", &Clientes[i].ingresos[i].dia, &Clientes[i].ingresos[i].mes, &Clientes[i].ingresos[i].anio);

    MAYOR_ING (Clientes, NUM);

    ULTIMO_ING (Clientes, NUM, ING);

    MAS_TIEMPO (Clientes, NUM, ING);



}

}

//FUNCIONES------------------------------------------------

// MUESTRA EL USUARIO QUE HIZO MAS INGRESOS-------------------------------------

void MAYOR_ING (struct usuario CL [], int N){

    int i, j, cont = 0, mayor = -1, user;

    for (i = 0 ; i < N; i++){
        j = 0;
        cont = 0;
        while ( CL[i].ingresos[j].dia != -1 ){
            cont++;
            j++;
        }
        if (cont > mayor){
            mayor = cont;
            user = i;
        }

    }

    if (mayor != -1){
        printf ("\n\nEl Usuario que realizo mas ingresos al sistema fue el: %s\n\n", CL[user].email );
    }
    else
        printf ("\n\nNingun Usuario hizo ingresos al sistema");
}


// MUESTRA ULTIMO INGRESO DE CADA USUARIO-------------------------------------

void ULTIMO_ING (struct usuario CL [], int N, int Ing){

    int i, j, posI;
    unsigned int ultima = -1;

    printf("%-20s \t%15s \n\n", "EMAIL", "ULTIMO INGRESO");

    for (i = 0 ; i < N; i++){
        for (j = 0 ; j < Ing && CL[i].ingresos[j].dia != -1; j++){
            if (dias (CL[i].ingresos[j]) > ultima && CL[i].ingresos[j].dia != -1){
                ultima = dias (CL[i].ingresos[j]);
                posI = j;
                printf("ENTRO AL IF i = %d. POsI = %d\n\n", i, posI);
            }
            printf("i = %d. POsI = %d\n\n", i, posI);
        }
        printf("%-20s \t\t%02d/%02d/%d \n\n", CL[i].email , CL[i].ingresos[posI].dia, CL[i].ingresos[posI].mes, CL[i].ingresos[posI].anio);
    }
}

unsigned int dias (struct fecha Ing){

    long cant_dias;

    cant_dias = 365 * Ing.anio + 30 * Ing.mes + Ing.dia;

    printf("CANT DIAS %d", cant_dias );

    return cant_dias;

}

// MUESTRA EL USUARIO QUE HACE MAYOR TIERMPO NO INGRESA------------------------------
void MAS_TIEMPO (struct usuario CL [], int N, int Ing){

    int i, j, posU, posI;
    time_t mayor = time(0);
    unsigned int MasDias = mayor / 86400, MenorDias;
    printf("Mas dias %d\n", MasDias);
    printf("Menor dias %d\n", MenorDias);

    for (i = 0 ; i < N; i++){
        for (j = 0 ; j < Ing && CL[i].ingresos[j].dia != -1; j++){
            MenorDias = dias (CL[i].ingresos[j]);
            printf("Menor dias %d\n", MenorDias);
            if ( MenorDias < MasDias){
                printf("ENTRO AL IF %d   %d\n", i, j);
                MasDias = MenorDias;
                posI = j;
                posU = i;
            }
        }
    }
    printf("PosU = %d. POsI = %d\n\n", posU, posI);

    printf ("El Usuario que hace mas tiempo que no entra es el %s el %02d/%02d/%d \n\n", CL[posU].email, CL[posU].ingresos[posI].dia, CL[posU].ingresos[posI].mes, CL[posU].ingresos[posI].anio);

}
