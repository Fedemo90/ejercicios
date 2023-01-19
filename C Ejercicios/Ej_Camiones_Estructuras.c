/* Se cuenta con un vector de estructuras con datos de camiones que realizan viajes entre ciudades.

struct fecha { int dia; int mes; int anio; }

struct viajecamion {
	char patente[10];
	char ciudad_origen[50];
	char ciudad_destino[50];
	float peso_transportado;
	struct fecha fecha_viaje;
}


Construya cuatro funciones que reciban el vector y su tamaño, y realicen lo siguiente:

a) Permita el ingreso de los datos de 4 camiones y 2 viajes para cada uno.

b) Muestre en pantalla las patentes, sin repetir. No se debe modificar el orden del vector original.

c) Muestre en pantalla la patente del camión que más viajes realizó. Para esto modifique el punto a, de manera de poder ingresar algún camión con más viajes y probar este punto c.

d) Muestre en pantalla todos los viajes, ordenados por fecha. Los que son de la misma fecha
se deben ordenar por peso transportado descendente.
*/


#include <stdio.h>
#include <string.h>

#define NUM 8
#define VIAJES 2

struct fecha {
    int dia;
    int mes;
    int anio;
};

struct viajecamion {
    char patente [10];
    char ciudad_origen [50];
    char ciudad_destino [50];
    float peso_transportado;
    struct fecha fecha_viaje;
};

void Ingreso (struct viajecamion [], int);
void MostrarPat (struct viajecamion [], int);
void MasViajes (struct viajecamion [], int);
void Viajes (struct viajecamion [], int);
unsigned int dias (struct fecha);

int main(){

    int opc;
    struct viajecamion CAMION1[NUM] = {};
    struct viajecamion CAMION2[NUM] = {};


    while (opc != 5){
        printf("Elija la opcion \n\t\t1 Ingreso\n\n\t\t2 Mostrar Patentes\n\n \t\t3 Mas Viajes\n\n \t\t4 Listado Viajes\n\n\t\t5 SALIR\n\n");
        scanf("%d", &opc);

        if (opc == 1)
            Ingreso (CAMION1, NUM);
        else if (opc == 2)
            MostrarPat (CAMION1, NUM);
        else if (opc == 3)
            MasViajes (CAMION2, NUM);
        else if (opc == 4)
            Viajes (CAMION2, NUM);


    }

}


//FUNCIONES----------------------------------

void Ingreso (struct viajecamion CAM[], int N){

    int i, j, v;

    for(i = 0 ; i < N ; i = i + 2){
        printf("Ingrese la Patente de 9 digitos: ");
        fflush(stdin);
        gets(CAM[i].patente);
        strcpy (CAM[i+1].patente, CAM[i].patente);

        for(j = 0; j < VIAJES; j++){
            v = i;
            printf("\n\nIngrese los datos del viaje %d: \n", j+1);
            printf("\nCiudad de origen: ");
            fflush(stdin);
            gets(CAM[v].ciudad_origen);
            printf("\nCiudad de destino: ");
            fflush(stdin);
            gets(CAM[v].ciudad_destino);
            printf("\nPeso transportado: ");
            fflush(stdin);
            scanf("%f", &CAM[v].peso_transportado);
            printf("\nFecha del Viaje: (dd/mm/aaaa) ");
            fflush(stdin);
            scanf("%d/%d/%d/", &CAM[v].fecha_viaje.dia,  &CAM[v].fecha_viaje.mes,  &CAM[v].fecha_viaje.anio);
            v++;
        }
    }

    printf("\n\nVolver al Menu...\n\n");
    fflush(stdin);
    getchar();

}

void MostrarPat (struct viajecamion CAM[], int N){

    int i, j, flag = 1;

    printf("\n\nPATENTES DE LOS CAMIONES\n\n");
    for(i = 0 ; i < N ; i++){
        flag = 1;
        if (i != 0){
            for (j = i - 1; j >= 0 && flag == 1 ; j--){
                if (!stricmp ( CAM[i].patente, CAM[j].patente )){
                    flag = -1;
                }
            }

            if (flag == 1){
                printf("\t%s\n\n", CAM[i].patente);
            }


        }
        else
            printf("\t%s\n\n", CAM[i].patente);

    }

    printf("\n\nVolver al Menu...\n\n");
    fflush(stdin);
    getchar();

}


void MasViajes (struct viajecamion CAM [], int N){

    int i, j, v, flag = 1;
    int cont, mayor = 0, posM;

    for(i = 0 ; i < N ; i = i + j){
        printf("Ingrese la Patente de 9 digitos: ");
        fflush(stdin);
        gets(CAM[i].patente);
        flag = 1;
        v = i;
        for(j = 0; v < N && flag > 0; j++){
            printf("\n\nIngrese los datos del viaje %d: \n", j+1);
            printf("\nCiudad de origen: ");
            fflush(stdin);
            gets(CAM[v].ciudad_origen);
            printf("\nCiudad de destino: ");
            fflush(stdin);
            gets(CAM[v].ciudad_destino);
            printf("\nPeso transportado: ");
            fflush(stdin);
            scanf("%f", &CAM[v].peso_transportado);
            printf("\nPeso transportado %f: \n", CAM[v].peso_transportado);
            printf("\nFecha del Viaje: (dd/mm/aaaa) ");
            fflush(stdin);
            scanf("%d/%d/%d/", &CAM[v].fecha_viaje.dia,  &CAM[v].fecha_viaje.mes,  &CAM[v].fecha_viaje.anio);
            printf("\nIngrese 1 para seguir ingresando viajes o -1 para continuar:  ");
            printf("\n\n");
            fflush(stdin);
            scanf ("%d", &flag);
            if (flag ==1){
                v++;
                strcpy(CAM[v].patente, CAM[i].patente);
            }
        }
    }

   for(i = 0 ; i < N ; i++){
        flag = 1;
        cont = 0;
        if (i != 0){
            for (j = i - 1; j >= 0 && flag == 1 ; j--){
                if (!stricmp ( CAM[i].patente, CAM[j].patente ))
                    flag = -1;

            }

            if (flag == 1){
                for (j = i; j < N ; j++){
                    if (!stricmp ( CAM[i].patente, CAM[j].patente ))
                        cont++;
                }
            }
            if (cont > mayor){
                mayor = cont;
                posM = i;
            }
        }

        else{
            for (j = i; j < N && flag == 1 ; j++){
                if (!stricmp ( CAM[i].patente, CAM[j].patente )){
                    cont++;
                }
            }
            if (cont > mayor){
                mayor = cont;
                posM = i;
            }
        }
    }


    printf("\n\n----------------------------------------\nEL CAMION QUE HIZO MAS VIAJES FUE %s\n----------------------------------------\n\n", CAM[posM].patente );

    printf("\n\nVolver al Menu...\n\n");
    fflush(stdin);
    getchar();


}

void Viajes (struct viajecamion CAM [], int N){

    int i, j;
    struct viajecamion AUX;
    for (i = 0; i < N - 1; i++){
        for (j = 0; j < N -1-i ; j++){
            if( dias(CAM[j].fecha_viaje) > dias(CAM[j+1].fecha_viaje) ){
                AUX = CAM[j];
                CAM[j] = CAM[j+1];
                CAM[j+1] = AUX;
            }
            else if( dias(CAM[j].fecha_viaje) == dias( CAM[j+1].fecha_viaje ) && CAM[j].peso_transportado < CAM[j+1].peso_transportado ){
                AUX = CAM[j];
                CAM[j] = CAM[j+1];
                CAM[j+1] = AUX;
            }
        }
    }

    printf("%-10s \t\t%-10s \t%-15s \n\n", "PATENTE", "FECHA VIAJE", "PESO TRANSPORTADO");
    for (i = 0; i < N; i++){
        printf("%-10s \t\t%02d/%02d/%d \t\t%-15f \n", CAM[i].patente, CAM[i].fecha_viaje.dia,  CAM[i].fecha_viaje.mes, CAM[i].fecha_viaje.anio, CAM[i].peso_transportado);
    }


    printf("\n\nVolver al Menu...\n\n");
    getchar();

}

unsigned int dias (struct fecha Ing){

    long cant_dias;

    cant_dias = 365 * Ing.anio + 30 * Ing.mes + Ing.dia;

    return cant_dias;

}
