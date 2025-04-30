#include<iostream>
#include<windows.h>

using namespace std;

struct arbol{
    int info;
    arbol *izq;
    arbol *der;
};

void agregar(arbol *&raiz, int n);
void Muestra_InOrden(arbol *&raiz);
void dibujarArbol(arbol* raiz, int x, int y, int separacion);

int main(){

    arbol *raiz = NULL;
    
    int opc;

    do{

        cout<<"\n\tMenú de opciones\n";
        cout<<"\n1. Agregar un nodo a un arbol binario\n";
        cout<<"2. Mostrar el contenido de un arbol en InOrden\n";
        cout<<"3. Dibujar el arbol\n";
        cout<<"4. Salir\n";
        cout<<"\nSeleccione una opcion: "; cin>>opc;

        switch(opc){
            case 1: cout<<"\n\tAgregar nodo\n";
                int n;
                cout<<"\nIngrese el valor del nodo: "; cin>>n;
                agregar(raiz, n);
            break;

            case 2: cout<<"\n\tImpresion en In-Orden\n";
                Muestra_InOrden(raiz);
            break;

            case 3: 
            system("cls");
            dibujarArbol(raiz, 40, 2, 20);
            cout << "\n\n";
            break;

            case 4: cout<<"\nSaliendo del programa...\n"; break;

            default: cout<<"\nOpcion invalida. Intente nuevamente\n"; break;
    
        }

    }while(opc!=5);

    return 0;
}

void agregar(arbol *&raiz, int n){

    arbol *nuevo = new arbol;

    if(raiz == NULL){
        raiz = nuevo;
        raiz->info = n;
        raiz->izq = NULL;
        raiz->der = NULL;
        return;
    }

    int opc;
    cout<<"\n\nEl nodo actual es: "<<raiz->info;
    cout<<"\n¿Donde desea agregar el nuevo nodo?\n";
    cout<<"\n1. Izquierda\n2. Derecha\n";
    cout<<"\nElija una opcion: "; cin>>opc;

    if(opc == 1){
         if(raiz->izq == NULL){
            raiz->izq = nuevo;
            raiz->izq->info = n;
            raiz->izq->izq = NULL;
            raiz->izq->der = NULL;
        } else {
            agregar(raiz->izq, n);
        }
    
    } else if(opc == 2){
            
            if(raiz->der == NULL){
                raiz->der = nuevo;
                raiz->der->info = n;
                raiz->der->izq = NULL;
                raiz->der->der = NULL;

            } else {
                agregar(raiz->der, n);
            }

        } else {
            cout <<"\nOpción inválida. Intente nuevamente.\n";
        }
}


void Muestra_InOrden(arbol *&raiz){
    if(raiz != NULL){
        Muestra_InOrden(raiz->izq);
        cout<<raiz->info<<" - ";
        Muestra_InOrden(raiz->der);
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Dibujo recursivo del árbol
void dibujarArbol(arbol* raiz, int x, int y, int separacion) {
    if (raiz == NULL) return;

    gotoxy(x, y);
    cout << raiz->info;

    // Dibuja líneas visuales (opcional)
    if (raiz->izq != NULL) {
        gotoxy(x - separacion / 2, y + 1);
        cout << "/";
        dibujarArbol(raiz->izq, x - separacion, y + 2, separacion / 2);
    }

    if (raiz->der != NULL) {
        gotoxy(x + separacion / 2, y + 1);
        cout << "\\";
        dibujarArbol(raiz->der, x + separacion, y + 2, separacion / 2);
    }
}