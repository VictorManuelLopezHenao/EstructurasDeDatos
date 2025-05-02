#include<iostream>
#include <iomanip>

using namespace std;

struct arbol{
    int info;
    arbol *izq;
    arbol *der;
};

void agregar(arbol *&raiz, int n);
void Muestra_InOrden(arbol *&raiz);
void dibujarArbol(arbol *raiz);


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

            case 3: cout << "\n\tDibujar el árbol\n";
                dibujarArbol(raiz);
            break;
           
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

void dibujarArbol(arbol *raiz) {
    if (raiz == NULL) {
        cout << "El árbol está vacío." << endl;
        return;
    }

    // Función auxiliar para calcular la altura del árbol
    auto altura = [](arbol* n, auto&& altura) -> int {
        if (n == NULL) return 0;
        return 1 + max(altura(n->izq, altura), altura(n->der, altura));
    };

    // Función recursiva para imprimir el árbol
    auto imprimirNivel = [](arbol* nodo, int nivel, int espaciado, auto&& imprimirNivel) {
        if (nodo == NULL) {
            cout << setw(espaciado) << " ";
            return;
        }
        if (nivel == 1) {
            cout << setw(espaciado) << nodo->info;
        } else if (nivel > 1) {
            imprimirNivel(nodo->izq, nivel - 1, espaciado, imprimirNivel);
            cout << setw(espaciado) << " ";
            imprimirNivel(nodo->der, nivel - 1, espaciado, imprimirNivel);
        }
    };

    int h = altura(raiz, altura);
    int espaciado = 4; // Ajusta este valor para cambiar el espaciado entre nodos

    for (int i = 1; i <= h; i++) {
        imprimirNivel(raiz, i, espaciado * (h - i + 1), imprimirNivel);
        cout << endl << endl;
    }
}