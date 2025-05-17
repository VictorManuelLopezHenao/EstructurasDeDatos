#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct arbol{
    string palabra, significado, categoria;
    vector<string> sinonimo;
    arbol *izq;
    arbol *der;
    int altura = 1;
};

arbol *info();
void modificar(arbol *&raiz, const string &palabra);
void mostrar_elem_palabra(arbol *raiz, const string &palabra);
void listado_categoria(arbol *raiz, const string &categoria);
void listado_letra(arbol *raiz, char letra);
void listado_general(arbol *raiz);
void primer_palabra(arbol *raiz);
void ultima_palabra(arbol *raiz);
int contador(arbol *raiz);
void actualizarAltura(arbol *nodo);
int balanceFactor(arbol *nodo);
int altura(arbol *nodo);
arbol* rotarDerecha(arbol* y);
arbol* rotarIzquierda(arbol* x);
arbol* insertarAVL(arbol* raiz, arbol* nuevo);
arbol* eliminarAVL(arbol* raiz, const string& palabra);
arbol* encontrarMin(arbol* nodo);
void visualizarArbol(arbol* raiz, int espacio);

int main(){

    arbol *raiz = NULL;

    int opc;
    string buscar;

    do{
        cout<<"\n\n\tMenú de opciones\n";
        cout<<"\n1. Agregar palabra al diccionario\n2. Modificar elementos de una palabra\n3. Mostrar elementos de una palabra";
        cout<<"\n4. Eliminar palabra\n5. Listado de palabras por categoría gramatical\n6. Listado de palabras por letra (indicado por el usuario)";
        cout<<"\n7. Listado general de palabras en orden alfabético\n8. Mostrar primera y última palabra del diccionario con sus componentes (alfabéticamente)"; 
        cout<<"\n9. Mostrar la cantidad de palabras registradas en el diccionario\n10. Mostrar arbol\n11. Salir";
        cout<<"\n\nSeleccione una opcion: ";  cin>>opc;

        switch(opc){
            case 1: cout<<"\n\tAgregar palabra al diccionario\n"; 
                     raiz = insertarAVL(raiz, info());
                    break;

            case 2: cout<<"\n\tModificar elementos de una palabra\n";
                    
                    if(raiz == NULL){
                         cout<<"\nNo hay palabras registradas en el diccionario\n";
                    } else {
                        cout <<"\nIngrese la palabra que desea modificar: ";
                        cin.ignore(); getline(cin, buscar);  
                        modificar(raiz, buscar);  
                    } break;

            case 3: cout<<"\n\tMostrar elementos de una palabra\n"; 
                    
                    if(raiz == NULL){
                        cout<<"\nNo hay palabras registradas en el diccionario\n";
                    } else {
                        cout <<"\nIngrese la palabra que desea buscar: ";
                        cin.ignore(); getline(cin, buscar);  
                         mostrar_elem_palabra(raiz, buscar); 
                    } break;

            case 4: 
                    cout << "\n\tEliminar palabra\n";
                    if (raiz == NULL) {
                        cout << "\nNo hay palabras registradas en el diccionario.\n";
                    } else {
                        cout << "\nIngrese la palabra que desea eliminar: ";
                        cin.ignore(); 
                        getline(cin, buscar); 
                        raiz = eliminarAVL(raiz, buscar);
                        cout << "\nLa palabra ha sido eliminada correctamente.\n";; 
                    }
                    break;

            case 5: cout<<"\n\tListado de palabras por categoría gramatical\n";
            
                    if(raiz == NULL){
                        cout<<"\nNo hay palabras registradas en el diccionario\n";
                    } else {
                        cout<<"\nIngrese la categoría gramatical (verbo, sustantivo, adjetivo): ";
                        cin.ignore(); getline(cin, buscar);
                        listado_categoria(raiz, buscar);
                    } break;

            case 6: cout<<"\n\tListado de palabras por letra\n"; 
                
                    if(raiz == NULL){
                         cout<<"\nNo hay palabras registradas en el diccionario\n";
                    } else {
                        char letra;
                        cout<<"\nIngrese la letra por la que desea listar las palabras: "; cin>>letra;
                        listado_letra(raiz, letra);
                    } break;
                

            case 7: cout<<"\n\tListado general de palabras en orden alfabético\n"; 
                    
                    if(raiz == NULL){
                     cout<<"\nNo hay palabras registradas en el diccionario\n";
                     } else {
                        listado_general(raiz); 
                     } break;

            case 8: cout<<"\n\tMostrar primera y última palabra del diccionario con sus componentes\n";
                    
                    if(raiz == NULL){
                        cout<<"\nNo hay palabras registradas en el diccionario\n";
                    } else {
                    primer_palabra(raiz);
                    ultima_palabra(raiz);
                }
                    break;

            case 9: cout<<"\n\tCantidad de palabras registradas en el diccionario\n"; 
                    cout<<"\nLa cantidad de palabras registradas es: "<<contador(raiz);
                    break;
                    
            case 10: 
            cout << "\n\tVisualización del árbol AVL\n\n\n";
            if (raiz == NULL) {
                cout << "\nNo hay palabras registradas en el diccionario\n";
            } else {
                visualizarArbol(raiz, 0);
            }
            break;
                

            case 11: cout<<"\nSaliendo del programa...."; break;

            default: cout<<"\nOpcion invalida. Intente de nuevo\n"; break;
        }
    }while(opc!=11);

    return 0;
}

arbol *info(){
    arbol *nuevo = new arbol;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    cout<<"\nIngrese una palabra: "; cin>>nuevo->palabra;
    cout<<"Ingrese su significado: "; cin.ignore(); getline(cin, nuevo->significado);
    cout<<"Ingrese su categoria gramatical (verbo, sustantivo, adjetivo): "; getline(cin, nuevo->categoria);

    int opc;
    int count = 0;                  //hacer validacion de categoria gramatical
    string s;
    do{

        if (count == 3) {
            cout << "\nYa ingresaste los tres sinónimos permitidos.\n";
            break; 
        }
    
            cout<<"\n¿Desea agregar un sinonimo (Max 3)?";
            cout<<"\n\n1. Si\n2. No";
            cout<<"\nELija una opcion: "; cin>>opc;

            if (opc == 1) {
                cout <<"\nIngrese un sinónimo: ";
                cin.ignore(); getline(cin, s);
                nuevo->sinonimo.push_back(s);
                count++;
            }
        

    }while(opc!=2);

    return nuevo;
}

void modificar(arbol *&raiz, const string &palabra){
    
    if(raiz == NULL){
        cout<<"\nLa palabra no se encuentra en el diccionario\n";
        return;
    }

    if(palabra < raiz->palabra){
        modificar(raiz->izq, palabra);
    } else if(palabra > raiz->palabra){
        modificar(raiz->der, palabra);
    } else {

        int opc;
        int bucle;

        do{

        
        cout<<"\n¿Que elemento desea modificar?\n";
        cout<<"\n1. Significado\n2. Categoria\n3. Sinonimos\n";
        cout<<"\nElija una opcion: "; cin>>opc;

    

        if(opc == 1){
            cout<<"\nIngrese el nuevo significado: "; cin.ignore(); getline(cin, raiz->significado);
        
        } else if(opc == 2){
            cout<<"\nIngrese la nueva categoria: "; getline(cin, raiz->categoria);
       
        } else if(opc == 3){
           
            int opc2;
            cout<<"\nDigite el numero del sinonimo que desea modificar (1, 2, 3): "; cin>>opc2;

            if(opc2 < 1 || opc2 > raiz->sinonimo.size()){
                cout<<"\nIndice fuera del rango de sinonimos de esta palabra\n";
                return;
            }
            
            string nuevosinonimo;
            cout<<"\nIngresa el nuevo sinonimo: "; cin.ignore(); getline(cin, nuevosinonimo);
            raiz->sinonimo[opc2 - 1] = nuevosinonimo;

        
        } else {
            cout<<"\nOpcion invalida\n";
            return;
        }

        cout<<"\nDesea modificar algo mas?\n";
        cout<<"\n1. Si\n2. No\n";
        cout<<"Seleccione una opcion: "; cin>>bucle;
    
    } while(bucle != 2);
  }
}

void mostrar_elem_palabra(arbol *raiz, const string &palabra){
    if(raiz == NULL){
        cout<<"\nLa palabra no se encuentra en el diccionario\n";
        return;
    }

    if(palabra < raiz->palabra){
        mostrar_elem_palabra(raiz->izq, palabra);
    } else if(palabra > raiz->palabra){
        mostrar_elem_palabra(raiz->der, palabra);
    } else {

        cout<<"\nSignificado: "<<raiz->significado;
        cout<<"\nCategoria: "<<raiz->categoria;
        cout<<"\n\nSinonimos: ";

        for(int i=0; i < raiz->sinonimo.size(); i++){
            cout<<"\n"<<raiz->sinonimo[i];
        }
        cout<<"\n";
    }
    
}

void listado_categoria(arbol *raiz, const string &categoria){
   
    if(raiz != NULL){
        listado_categoria(raiz->izq, categoria);

        if(raiz->categoria == categoria){
            cout<<"\nPalabra: "<<raiz->palabra;
            cout<<"\nSignificado: "<<raiz->significado;           //in orden
            cout<<"\n\nSinonimos: ";

            for(int i=0; i < raiz->sinonimo.size(); i++){
                cout<<"\n"<<raiz->sinonimo[i];
             }
        cout<<"\n\n-----------------------------------------";
        }

        listado_categoria(raiz->der, categoria);
    }
}

void listado_letra(arbol *raiz, char letra){

    if(raiz != NULL){
        
        listado_letra(raiz->izq, letra);

        if(letra == raiz->palabra[0]){
        cout<<"\nPalabra: "<<raiz->palabra;
        cout<<"\nSignificado: "<<raiz->significado;
        cout<<"\nCategoria: "<<raiz->categoria;
        cout<<"\nSinonimos: ";

        for(int i=0; i < raiz->sinonimo.size(); i++){
            cout<<"\n"<<raiz->sinonimo[i];
         }
        cout<<"\n\n-----------------------------------------";
        }

        listado_letra(raiz->der, letra);
    }

}

void listado_general(arbol *raiz){

    if(raiz != NULL){

        listado_general(raiz->izq);
        
        cout<<"\nPalabra: "<<raiz->palabra;
        cout<<"\nSignificado: "<<raiz->significado;
        cout<<"\nCategoria: "<<raiz->categoria;
        cout<<"\nSinonimos: ";

        for(int i=0; i < raiz->sinonimo.size(); i++){
            cout<<"\n"<<raiz->sinonimo[i];
         }
        cout<<"\n\n-----------------------------------------";

        listado_general(raiz->der);

    }
}

void primer_palabra(arbol *raiz){

    while(raiz->izq!=NULL){
        raiz = raiz->izq;
    }

        cout<<"\nPrimer palabra del diccionario:\n";

        cout<<"\nPalabra: "<<raiz->palabra;
        cout<<"\nSignificado: "<<raiz->significado;
        cout<<"\nCategoria: "<<raiz->categoria;
        cout<<"\nSinonimos: ";

        for(int i=0; i < raiz->sinonimo.size(); i++){
            cout<<"\n"<<raiz->sinonimo[i];
         }
        cout<<"\n";
}

void ultima_palabra(arbol *raiz){
    
    while(raiz->der!=NULL){
        raiz = raiz->der;
    }

        cout<<"\nUltima palabra del diccionario:\n";
        cout<<"\nPalabra: "<<raiz->palabra;
        cout<<"\nSignificado: "<<raiz->significado;
        cout<<"\nCategoria: "<<raiz->categoria;
        cout<<"\nSinonimos: ";

        for(int i=0; i < raiz->sinonimo.size(); i++){
            cout<<"\n"<<raiz->sinonimo[i];
         }
        cout<<"\n";
}

int contador(arbol *raiz){
    if(raiz == NULL) return 0;
    return contador(raiz->izq) + 1 + contador(raiz->der);
}

//funciones para AVL

int altura(arbol *nodo) {
    if (nodo == NULL) {
        return 0;
    } else {
        return nodo->altura;
    }
}

int balanceFactor(arbol *nodo) {
    if (nodo == NULL) {
        return 0;
    } else {
        int alturaDerecha = altura(nodo->der);
        int alturaIzquierda = altura(nodo->izq);
        return alturaDerecha - alturaIzquierda;
    }
}

void actualizarAltura(arbol *nodo) {
    if (nodo) {
        nodo->altura = max(altura(nodo->izq), altura(nodo->der)) + 1;
    }
}

arbol* rotarDerecha(arbol* y) {
    arbol* x = y->izq;
    arbol* T2 = x->der;

    x->der = y;
    y->izq = T2;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

arbol* rotarIzquierda(arbol* x) {
    arbol* y = x->der;
    arbol* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}

arbol* insertarAVL(arbol* raiz, arbol* nuevo) {
    if (!raiz)
        return nuevo;

    if (nuevo->palabra < raiz->palabra)
        raiz->izq = insertarAVL(raiz->izq, nuevo);
    else if (nuevo->palabra > raiz->palabra)
        raiz->der = insertarAVL(raiz->der, nuevo);
    else {
        cout << "\nLa palabra ya existe en el diccionario\n";
        return raiz;
    }

    actualizarAltura(raiz);
    int balance = balanceFactor(raiz);

    // Caso Izquierda Izquierda
    if (balance < -1 && nuevo->palabra < raiz->izq->palabra)
        return rotarDerecha(raiz);

    // Caso Derecha Derecha
    if (balance > 1 && nuevo->palabra > raiz->der->palabra)
        return rotarIzquierda(raiz);

    // Caso Izquierda Derecha
    if (balance < -1 && nuevo->palabra > raiz->izq->palabra) {
        raiz->izq = rotarIzquierda(raiz->izq);
        return rotarDerecha(raiz);
    }

    // Caso Derecha Izquierda
    if (balance > 1 && nuevo->palabra < raiz->der->palabra) {
        raiz->der = rotarDerecha(raiz->der);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

arbol* encontrarMin(arbol* nodo) {
    while (nodo->izq)
        nodo = nodo->izq;
    return nodo;
}

arbol* eliminarAVL(arbol* raiz, const string& palabra) {
    if (!raiz) return NULL;

    if (palabra < raiz->palabra)
        raiz->izq = eliminarAVL(raiz->izq, palabra);
    else if (palabra > raiz->palabra)
        raiz->der = eliminarAVL(raiz->der, palabra);
    else {
        if (!raiz->izq || !raiz->der) {
            arbol* temp = raiz->izq ? raiz->izq : raiz->der;
            delete raiz;
            return temp;
        }

        arbol* temp = encontrarMin(raiz->der);
        raiz->palabra = temp->palabra;
        raiz->significado = temp->significado;
        raiz->categoria = temp->categoria;
        raiz->sinonimo = temp->sinonimo;
        raiz->der = eliminarAVL(raiz->der, temp->palabra);
    }

    actualizarAltura(raiz);
    int balance = balanceFactor(raiz);

    // Casos de re-balanceo
    if (balance < -1 && balanceFactor(raiz->izq) <= 0)
        return rotarDerecha(raiz);
    if (balance < -1 && balanceFactor(raiz->izq) > 0) {
        raiz->izq = rotarIzquierda(raiz->izq);
        return rotarDerecha(raiz);
    }
    if (balance > 1 && balanceFactor(raiz->der) >= 0)
        return rotarIzquierda(raiz);
    if (balance > 1 && balanceFactor(raiz->der) < 0) {
        raiz->der = rotarDerecha(raiz->der);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

void visualizarArbol(arbol* raiz, int espacio) {
    if (raiz == NULL)
        return;

    espacio += 10; //aumenta el espacion entre niveles

    // Mostrar primero el subárbol derecho
    visualizarArbol(raiz->der, espacio);

    for (int i = 10; i < espacio; i++)
        cout << " ";

    // Mostrar los primeros 3 caracteres de la palabra
    if (raiz->palabra.length() >= 3)
        cout << raiz->palabra.substr(0, 3) << endl;
    else
        cout << raiz->palabra << endl;

    // Mostrar subárbol izquierdo
    visualizarArbol(raiz->izq, espacio);
}