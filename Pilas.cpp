#include <iostream>
using namespace std;

struct nodo {
    int info;
    struct nodo *sig;
};


// ______________________________

void insertarN(struct nodo *&raiz){

    struct nodo *nuevo = new(nodo);
    cout<<"Ingrese el int: "; cin>>nuevo->info;

    if(raiz == NULL){
        raiz = nuevo;
        raiz->sig = NULL;

    } else{
       nuevo->sig = raiz;
       raiz = nuevo;
      }
}


void imprimirP(struct nodo *&raiz) {

    if (raiz == NULL) {
        cout<<"La pila está vacía."<<endl;
        return;
    }

    struct nodo *auxTemp = NULL;
    
    // Vaciar la pila original y mover los elementos a la auxiliar
    while (raiz != NULL) {
        cout<<raiz->info<<" "; // Mostrar la cabeza
        struct nodo *temp = raiz; // Guardar la referencia al nodo actual
        raiz = raiz->sig; // Mover la cabeza al siguiente nodo
        temp->sig = auxTemp; // Apilar el nodo en la auxiliar
        auxTemp = temp;
    }

    cout<<endl;

    // Restaurar la pila original desde la auxiliar
    while (auxTemp != NULL) {
        struct nodo *temp = auxTemp;
        auxTemp = auxTemp->sig;
        temp->sig = raiz;
        raiz = temp;
    }
}



int extraer(struct nodo *&raiz) {              // Extraer el nodo superior de la pila (pop)
    if (raiz == NULL) {
        cout<<"La pila está vacía."<<endl;
        return -1;
    }
    
    int informacion = raiz->info;
    struct nodo *bor = raiz;
    raiz = raiz->sig;
    delete bor;  // Liberar memoria correctamente
    return informacion;
}


void liberar(struct nodo *&raiz) {                                  // Liberar toda la pila
    struct nodo *reco = raiz;
    struct nodo *bor;

    if (raiz == NULL) {
        cout<<"La pila ya está vacía."<<endl;
        return;
    }

    while (reco != NULL) {
        bor = reco;
        reco = reco->sig;
        delete bor;  // Liberar memoria correctamente
    }
    raiz = NULL;
    cout<<"Pila liberada." <<endl;
}


int cantidad(struct nodo *&raiz) { // Contar los nodos de la pila respetando la lógica de pilas
    if (raiz == NULL) {
        return 0;
    }

    struct nodo *auxTemp = NULL;
    int contador = 0;

    // Pasar nodos a la pila auxiliar mientras contamos
    while (raiz != NULL) {
        contador++;
        struct nodo *temp = raiz;
        raiz = raiz->sig;
        temp->sig = auxTemp;
        auxTemp = temp;
    }

    // Restaurar la pila original desde la auxiliar
    while (auxTemp != NULL) {
        struct nodo *temp = auxTemp;
        auxTemp = auxTemp->sig;
        temp->sig = raiz;
        raiz = temp;
    }

    return contador;
}


int main(){

    int opc;
    struct nodo *raiz = NULL;

    do{
    cout<<"MENÚ PILAS";
    cout<<"\n1. Insertar nodo"<<endl;
    cout<<"2. Imprimir pila"<<endl;
    cout<<"3. Extraer (Sale último nodo en llegar)"<<endl;
    cout<<"4. Cantidad"<<endl;
    cout<<"5. Liberar (Vaciar pila)"<<endl;
    cout<<"6. Salir"<<endl;
    
    cout<<"\nIngrese una opción: "; cin>>opc;

     switch(opc){

    case 1:
        insertarN(raiz);
        break;

    case 2:
        imprimirP(raiz);
        break;

    case 3:
        cout<<"Elemento extraído: "<<extraer(raiz)<<endl;
        break;

    case 4:
        cout<<"Cantidad de nodos en la pila: "<<cantidad(raiz)<<endl;
        break;

    case 5:
        liberar(raiz);
        break;

    case 6:
        liberar(raiz);
        cout<<"\nHasta luego.\n";
        system("pause");
        return 0;

    default:
        cout<<"Opción no válida.\n";
        break;

    }
   }while(opc!=6);
  }