#include<iostream>
using namespace std;

struct nodo{
    int info;
    nodo *sig;
};

void insertar(nodo *&raiz, nodo *&fondo);
void extraer(nodo *&raiz, nodo *&fondo);
void imprimir(nodo *&raiz, nodo *&fondo);
void liberar(nodo *&raiz, nodo *&fondo);
void insertarN(nodo *&raiz, nodo *&fondo);
void extraerN(nodo *&raiz, nodo *&fondo);
int cantidad(nodo *&raiz, nodo *&fondo);

int main(){

    nodo *raiz = NULL; 
    nodo *fondo = NULL; 
    
    int opc, opc2;

    do {
        cout << "\n\tMENÚ COLAS"<<endl;
        cout << "\n1. Insertar nodo"<<endl;
        cout << "2. Extraer nodo"<<endl;
        cout << "3. Imprimir cola"<<endl;
        cout << "4. Vaciar cola"<<endl;;
        cout << "5. Ver si la cola está vacía"<<endl;
        cout << "6. Salir"<<endl;;
        cout << "\nEscoja una opción: "; cin>>opc;

        switch (opc) {
           
            case 1: cout<<"\n\tInsertar nodo"<<endl; 
            cout<<"\n1. Insertar en la ultima posicion"<<endl;
            cout<<"2. Insertar en la poscision N"<<endl;
            cout<<"\nElija una opcion: "; cin>>opc2;
            
            if(opc2 == 1){
                insertar(raiz, fondo);
             } else if(opc2 == 2){
                insertarN(raiz, fondo);
             } else {
                cout<<"\nOpcion no disponible"<<endl;
             } break;
           
            case 2: cout<<"\n\tExtraer nodo"<<endl;
            if(raiz == NULL){
                cout<<"\nLa cola está vacia"<<endl;
            
            } else {
                cout<<"\n1. Extraer de la primera posicion"<<endl;
                cout<<"2. Extraer de la poscision N"<<endl;
                cout<<"\nElija una opcion: "; cin>>opc2;
               
                if(opc2 == 1){
                    extraer(raiz, fondo);
                 }else if(opc2 == 2){
                    extraerN(raiz, fondo);
                 } else {
                    cout<<"\nOpcion no disponible"<<endl;
                 } 
                } break;
           
            case 3: cout<<"\n\tImprimir cola"<<endl;
            if(raiz == NULL){
                cout<<"\nLa cola está vacia"<<endl;
            } else {
                imprimir(raiz, fondo);
            } break;
           
            case 4: cout<<"\n\tLiberar cola"<<endl; 
            if(raiz == NULL){
                cout<<"\nLa cola está vacia"<<endl;
            } else {
                liberar(raiz, fondo);
            } break;
        
               
            case 5:
            if(raiz == NULL){
                cout<<"\nLa cola está vacia"<<endl;
            } else {
                cout<<"\nLa cola tiene informacion"<<endl;
            } break;
        
                case 6: cout<<"\nHasta luego..."<<endl; break;
            
                default: cout<<"\nOpción no valida"<<endl; break;
        }
        
    } while (opc != 6);

    return 0;
}

void insertar(nodo *&raiz, nodo *&fondo){

    struct nodo *nuevo = new(nodo);
    cout<<"\nIngrese un numero: "; cin>>nuevo->info;
    nuevo->sig = NULL;

    if(raiz == NULL){
        raiz = nuevo;
        fondo = nuevo;
    } else { 
        fondo->sig = nuevo;
        fondo = nuevo;
    }
}

void extraer(nodo *&raiz, nodo *&fondo){
    
    int informacion = raiz->info;
    nodo *elim = raiz;

    if(raiz == fondo){
        raiz = NULL;
        fondo = NULL;
    } else {
        raiz = raiz->sig;
    }

    delete elim;

    cout<<"\nDato extraido: "<<informacion<<endl;

}

void imprimir(nodo *&raiz, nodo *&fondo){

    nodo *auxR = NULL;
    nodo *auxF = NULL;

    cout<<"\nInformacion de los nodos:\n";
    while(raiz != NULL){
        cout<<raiz->info<<endl;
       
        if(auxR == NULL){
            auxR = raiz;
            auxF = raiz;
        } else {
            auxF->sig = raiz;
            auxF = raiz;
        }
        
        raiz = raiz->sig;
        auxF->sig = NULL;
    }

    raiz = auxR;
    fondo = auxF;
}

void liberar(nodo *&raiz, nodo *&fondo){

    while(raiz != NULL){
        nodo *temp = raiz;
        raiz = raiz->sig;
        delete temp;
    }
    raiz = NULL;
    fondo = NULL;

    cout<<"\nLiberación exitosa"<<endl;
}
   
void insertarN(nodo *&raiz, nodo *&fondo) {
   
    int posc;
    cout << "\nIngrese la posicion donde desea agregar el nodo: "; cin >> posc;

    if (posc == (cantidad(raiz, fondo) + 1)) {
        insertar(raiz, fondo);                         //ult posc
        return;
    }

    if (posc > cantidad(raiz, fondo) || posc <= 0) {
        cout << "\nPosicion no disponible" << endl;
        return;
    }

    nodo *auxR = NULL;  
    nodo *auxF = NULL;  

    int count = 1;

    
    while (raiz != NULL) {
        if (count == posc) {              //hasta la posc deseada
            insertar(auxR, auxF);
        }

        // Guardar nodo actual
        nodo *temp = raiz;
        raiz = raiz->sig;

        temp->sig = NULL;

        // Enlazar el nodo actual en la nueva cola
        if (auxR == NULL) {
            auxR = temp;
            auxF = temp;
        } else {
            auxF->sig = temp;
            auxF = temp;
        }


        count++;
    }

    raiz = auxR;
    fondo = auxF;
}

void extraerN(nodo *&raiz, nodo *&fondo){
    
    int posc;
    cout<<"\nIngrese la posicion donde desea extraer el nodo: "; cin>>posc;

    if(posc > cantidad(raiz, fondo) || posc <= 0){
        cout<<"\nPosicion no disponible"<<endl;
        return;
    }

    nodo *auxR = NULL;
    nodo *auxF = NULL;

    int count = 1;

    while(raiz != NULL){
        nodo *temp = raiz;
        raiz = raiz->sig;
        temp->sig = NULL;
        
        if(posc == count){
            nodo *elim = temp;
            cout<<"\nInformacion del nodo eliminado: "<<elim->info<<endl;
            delete elim;
        } else {
            if(auxR == NULL){
                auxR = temp;
                auxF = temp;
            } else {
                auxF->sig = temp;
                auxF = temp;
            }
        }
        count++;
    }

    raiz = auxR;
    fondo = auxF;
}

int cantidad(nodo *&raiz, nodo *&fondo){

    int count = 0;

    nodo *auxR = NULL;
    nodo *auxF = NULL;

    while(raiz != NULL){
        count++;

        if(auxR == NULL){
            auxR = raiz;
            auxF = raiz;
        } else {
            auxF->sig = raiz;
            auxF = raiz;
        }

        raiz = raiz->sig;
        auxF->sig = NULL;
    }
    
    raiz = auxR;
    fondo = auxF;

    return count;
}
