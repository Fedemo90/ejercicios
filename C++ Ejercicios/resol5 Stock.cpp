/*


Se desea armar una guirnalda para mantener la información de stock de algunos productos.
Estos productos corresponden a diversas marcas.
La lista principal está compuesta de nodos Marca, de los cuales surge una lista secundaria de nodos Producto.

Le llamamos "punto de reposición" a la cantidad de productos que, cuando es alcanzada
(a medida que los productos se venden), indica que debemos comprar más para reponer.




class Comercio {         class Marca {                    class Producto {
	private:               	private:                         char nombre[50];
	Marca * marcas;         char nombre[50];                 int stock;
}                           Marca * sig;                     int ptoreposicion;
                            Producto * productos;            Producto * sig;
                         }                                }


*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class Producto {
    char nombre[50];
    int stock;
    int ptoreposicion;
    Producto * sig;

    public:
        Producto(char *, int , int);
        Producto * friend Marca::crearProducto (char *, int, int);
};

Producto::Producto (char *mod, int stk, int prepo){

    strcpy(nombre, mod);
    stock = stk;
    ptoreposicion = prepo;
    sig = NULL;

}

class Marca {
    private:
        char nombre[50];
        Marca * sig;
        Producto * productos;

    public:
        Marca (char *);
        Marca * crearMarca (char *);
        Producto * crearProducto (char *, int, int);
};

Marca::Marca (char * marca){

    strcpy(nombre, marca);
    sig = NULL;
    productos = NULL;

}

Marca * Marca::crearMarca (char * marca){

    return new Marca (marca);
}

Producto * Marca::crearProducto (char *mod, int stk, int prepo){

    return new Producto (mod, stk, prepo);
}


class Comercio {
	private:
        Marca * marcas;

	public:
	    Comercio();
        void ingresar (char * , char *, int , int);
        void venderUno (char *, char*);
        void imprimirMarcasConProductosAReponer();
        void crearProd (char *, int , int , Marca *);
        void verStock ();
};

Comercio::Comercio (){

    marcas = NULL;
}

void Comercio::ingresar (char * marca, char * mod, int stock, int prepo){

    Marca * M, * MPUNT;

    if(!marcas){
        M = M->crearMarca (marca);
        marcas = M;
        crearProd (mod, stock, prepo, M);
        return;
    }

    MPUNT = marcas;

    while (MPUNT){
        if (!stricmp (MPUNT->nombre,marca)){
            MPUNT->crearProd (mod, stock, prepo);
            return;
        }
        if (!(MPUNT->sig)){
            M =  new Marca (marca);
            MPUNT->sig = M;
            crearProd (mod, stock, prepo, M);
            return;
        }
        MPUNT = MPUNT ->sig;
    }
}

void Comercio::crearProd (char * mod, int stock, int prepo, Marca * MPUNT){

    Producto * Prod, *PBarr;

    Prod = new Producto (mod, stock, prepo);

    if (!(MPUNT->productos)){
        MPUNT->productos = Prod;
        return;
    }

    PBarr = MPUNT->productos;

    while(PBarr){
        if (!stricmp (PBarr->nombre, Prod->nombre)){
            cout << "EL PRODUCTO YA EXISTE";
            return;
        }
        if (!PBarr->sig){
            PBarr->sig = Prod;
            return;
        }
        PBarr = PBarr->sig;
    }

}

void Comercio::venderUno (char * marca, char * mod){

     Marca * M;
     Producto * Prod;

     M = marcas;

     while (M){
        if (!stricmp (M->nombre, marca)){
            Prod = M->productos;
            while (Prod){
                if (!stricmp (Prod->nombre, mod)){
                    if (Prod->stock > 0){
                        Prod->stock--;
                        return;
                    }
                    else{
                        cout << "No hay productos que vender";
                        return;
                    }
                }
                Prod = Prod->sig;
            }
            cout << "No se encontro el producto";
            return;

        }
        M = M->sig;
     }

     cout << "No existe MARCA";
}

void Comercio::imprimirMarcasConProductosAReponer(){

    Marca * M;
    Producto * Prod;
    int entro = 0;

    M = marcas;

    while (M){
        entro = 0;
        Prod = M->productos;
        while (Prod){
            if (Prod->stock <= Prod->ptoreposicion){
                if  (!entro){
                    cout << "\n\n\t\t " << M->nombre;
                    cout << "\n\n\t\t\t " << Prod->nombre;
                    entro = 1;
                }
                else
                    cout << "\n\n\t\t\t " << Prod->nombre;

            }
            Prod = Prod->sig;
        }
        M = M->sig;
    }



}

void Comercio::verStock(){
    Marca * M;
    Producto * Prod;
    int entro = 0;

    M = marcas;

    while (M){
        Prod = M->productos;
        cout << "\n\n\t\t " << M->nombre;
        while (Prod){
            cout << "\n\t\t\t " << Prod->nombre;
            Prod = Prod->sig;
        }
        M = M->sig;
     }

}
int main(void) {
	Comercio c;
	c.ingresar("Samsung", "S10", 10, 2); //marca, producto, stock, punto de reposicion
	c.ingresar("Samsung", "A12", 20, 0);
	c.ingresar("iPhone", "12", 5, 4);
	c.ingresar("iPhone", "12Pro", 0, 2);
	c.ingresar("LG", "Moto Z", 20, 5);

	c.venderUno("iPhone", "12");   //resta 1

	c.verStock();

	cout << "\n\n\n";

	printf("Se debe llamar a estos fabricantes: ");
	c.imprimirMarcasConProductosAReponer();   //mostrar las marcas con faltantes, sin repetir!
											//para el ejemplo debe verse iphone (una sola vez)

    cout << "\n\n\n";
}
