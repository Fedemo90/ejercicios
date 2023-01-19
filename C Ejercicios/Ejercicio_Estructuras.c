/*  Dada la siguiente estructura utilizada en un sistema de reproducción de música, donde se almacenan datos de canciones:

struct cancion {
	char nombre[50];
	char autor[50];
	int reproducciones[12];
}

El campo reproducciones contiene la cantidad de reproducciones de la canción en cada uno de los meses del año.

La estructura no se puede modificar (es decir, agregar o quitar campos).

1) Realice una función que recibe un vector de canciones y su largo, con el siguiente prototipo:
    void autores(struct cancion[], int n);

Debe mostrar en pantalla el nombre de todos los autores, sin repetirlos.

2) Realice otra función con este prototipo:
    void autor_totales(struct cancion[], int n, char autor[]);

Debe mostrar en pantalla la cantidad de reproducciones totales que tuvo un autor, para todas sus canciones, sumando todos los meses del año.
La función recibe el vector, su largo y el nombre del autor a buscar.

3) Construya el main para probar estas funciones. Puede utilizar ingresos por teclado o bien datos fijos con resultados conocidos.*/


#include <stdio.h>
#include <string.h>
#define NUM 10

struct cancion {
    char nombre[50];
    char autor[50];
    int reproducciones[12];
};

void autores (struct cancion [], int);
void autor_totales (struct cancion [], int, char []);


//MAIN------------------------------------------

int main(){

    int i, j, cont;
    char aut[50];
    struct cancion LISTA [NUM] ={};

    char CANCIONES [] [50] = { "Kill My Mind", "Butter", "Todo de Ti", "Mienteme", "Millones", "Tan Enamorados", "Canción Bonita", "Life Goes On", "Tus Besos", "Que Mas Pues"};

    char AUTORES [] [50] = { "Louis Tomlinson", "BTS", "Rauw Alejandro", "Maria Becerra", "Camilo", "BTS", "Carlos Vives", "BTS", "Karol Sevilla", "Camilo"};

    for (i = 0; i < NUM ; i++){
        strcpy(LISTA[i].nombre, CANCIONES[i]);
        strcpy(LISTA[i].autor, AUTORES[i]);
        for( j = 0; j < 12; j++){
            LISTA[i].reproducciones[j] = rand () % 20;
        }
    }



    autores (LISTA, NUM);

    printf ("\n\n");

    printf("2.\nIngrese el autor para ver las reproducciones totales: ");
    gets(aut);

    autor_totales (LISTA, NUM, aut);

    printf("Ver datos de las reproducciones...\n");
    getchar();

    //MUESTRA LOS VALORES DE REPRODUCCIONES PARA VERIFICAR EL RESULTADO

    printf("\n\n MUESTRA DE DATOS\n\n\n");

    for (i = 0; i < NUM; i++){
        cont = 0;
        printf("%s: %s \n", LISTA[i].autor,  LISTA[i].nombre );
            printf(" %7s %7s %7s %7s %7s %7s %7s %7s %7s %7s %7s %7s\n", "MES 1", "MES 2", "MES 3", "MES 4", "MES 5", "MES 6", "MES 7", "MES 8", "MES 9", "MES 10", "MES 11", "MES 12");
            for (j = 0; j < 12;j++){
                printf("%7d ", LISTA[i].reproducciones[j]);
                cont = cont + LISTA[i].reproducciones[j];
            }
            printf("\nTotal de reproducciones: %d\n\n\n", cont);
    }
}

//FUNCIONES --------------------------------------

void autores (struct cancion C[], int N){

    int i, j , flag = 1;

    printf("1. \nNOMBRE DE LOS AUTORES\n\n");

    for (i = 0; i < N; i++){
        flag = 1;
        if (i != 0){
            for(j = i -1; j >= 0 && flag == 1 ; j--){
                if (! stricmp (C[i].autor, C[j].autor )){
                    flag = -1;
                }
            }
            if (flag == 1){
                printf("%-15s\n\n ", C[i].autor );
            }
        }
        else
            printf("%-15s\n\n ", C[i].autor );
    }


}

void autor_totales (struct cancion C[], int N, char aut[] ){

    int i, j, cont = 0;

    for(i = 0 ;i < N;i++){
        if (!stricmp(C[i].autor, aut)){
            for(j = 0; j < 12; j++){
                cont = cont + C[i].reproducciones[j];
            }
        }

    }

    printf ("\n\nEl autor %s tiene %d reproducciones totales\n\n", aut, cont);

}
