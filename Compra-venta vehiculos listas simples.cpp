#include <iostream>
#include <cstring>

using namespace std;

void registraV(struct vehiculos *&raiz);  //*& trabaja con el puntero original
void caracteristicas(struct vehiculos *&raiz);
void existencia(struct vehiculos *raiz);
void listaV(struct vehiculos *raiz);

struct vehiculos{
    char placa[7]; char marca[20], modelo[20], color[10], año[5], precio[11], tipo[2], estado[2];
    struct hojadevida *hdv;
    struct vehiculos *vsig;
};

struct hojadevida{
    char adicionales[30];
    struct hojadevida *hsig;
};

int main(){

    struct vehiculos *raiz = NULL;

   
    int opc;
    int opc2;

    cout<<"\tBienvenidos a Mcqueen"<<endl;

    do{
    cout<<"\nMenú de opciones"<<endl;
    cout<<"\n1. Registrar vehiculos"<<endl;
    cout<<"2. Agregar caracteristicas de vehiculos"<<endl;
    cout<<"3. Existencia de vehiculos"<<endl;
    cout<<"4. Actualizar informacion de vehiculos"<<endl;
    cout<<"5. Eliminar o activar vehiculos"<<endl;
    cout<<"6. Mover vehiculos eliminados"<<endl;
    cout<<"7. Lista total de vehiculos"<<endl;
    cout<<"8. Salir"<<endl;
    cout<<"\nElija una opcion: "; cin>>opc;

    switch(opc){
        case 1: cout<<"\n\n\tRegistrar vehiculos"<<endl; registraV(raiz); 
                cout<<"\n¿Desea agregar las caracteristicas del vehiculo?"<<endl;
                cout<<"\n1. Si"<<endl;
                cout<<"2. No"<<endl;
                cout<<"\nElija una opcion: "; cin>>opc2;
                if(opc2 == 1){
                    caracteristicas(raiz);
                };
            break;

        case 2: cout<<"\n\n\tHoja de vida del vehiculo"<<endl; caracteristicas(raiz); break;

        case 3: cout<<"\n\n\tExistencia de vehiculos"<<endl; existencia(raiz); break;

        case 4:

        case 5: 

        case 6:

        case 7: cout<<"\n\n\tLista de vehiculos"<<endl; listaV(raiz); break;

        case 8:

        default: cout<<"Opcion invalida"<<endl; break;
    }

}while(opc!=8);

    return 0;
}


void registraV(struct vehiculos *&raiz){
    struct vehiculos *nuevo;               
    nuevo = new(struct vehiculos);         //reserva memoria para un nuevo nodo y almacena la direccion de este 

    cout<<"\nIngrese la siguiente informacion"<<endl;
    cout<<"\nPlaca: "; cin>>nuevo->placa;
    cout<<"Marca: "; cin>>nuevo->marca;
    cout<<"Modelo: "; cin>>nuevo->modelo;
    cout<<"Color: "; cin>>nuevo->color;
    cout<<"Año: "; cin>>nuevo->año;
    cout<<"Precio: "; cin>>nuevo->precio;
    cout<<"Tipo: "; cin>>nuevo->tipo;
    cout<<"Estado: "; cin>>nuevo->estado;

    if(raiz==NULL){
        nuevo->vsig = NULL;  
        nuevo->hdv = NULL;         //si la lista está vacia, nuevo será el primer nodo de la lista
        raiz = nuevo; 
    } else {
        struct vehiculos *temp = raiz;

        while(temp->vsig != NULL){       //Busca al ultimo nodo de la lista
            temp = temp->vsig;
        }

        temp->vsig = nuevo;          //Y en su sig asigna la direccion de memoria de nuevo
        nuevo->vsig = NULL;          //ahora nuevo es el ultimo nodo      
        nuevo->hdv = NULL;    
    } 

    cout<<"\nVehiculo registrado exitosamente"<<endl;
}


void caracteristicas(struct vehiculos *&raiz){

    int opc;
    char placaB[7];

    cout<<"\nDigite la placa del vehiculo: "; cin>>placaB;

    struct vehiculos *tempV = raiz;

   while(tempV != NULL && (strcmp(tempV->placa, placaB) != 0)){
    tempV = tempV->vsig;
   }

   if(tempV == NULL) {
    cout << "\nVehículo no encontrado." << endl;
    return;
}
    
    do{
    struct hojadevida *nuevaH;
    nuevaH = new(struct hojadevida);   //almacena la direccion en memoria que reservo para el nuevo nodo
    
    cout<<"\nIngrese las caracteristicas del vehiculo (sin espacios)"<<endl;
    cout<<"\n-> "; cin>>nuevaH->adicionales;
    

    if(tempV->hdv == NULL){
        nuevaH->hsig = NULL;      //si el vehiculo no tiene hoja de vida, se guarda en esa posicion la direccion de la hoja de vida digilenciada
        tempV->hdv = nuevaH;  
       }
      
       else {
        
        struct hojadevida *tempH = tempV->hdv;

        while (tempH->hsig != NULL) {    //
            tempH = tempH->hsig;
        }

        tempH->hsig = nuevaH;
        nuevaH->hsig = NULL; 
    }

    cout<<"\n¿Desea agregar mas caracteristicas?"<<endl;
    cout<<"\n1. Si"<<endl;
    cout<<"2. No"<<endl;
    cout<<"\nElija una opcion: "; cin>>opc; cout<<endl;
   
}while(opc!=2);

    
    cout<<"\nCaracteristicas agregadas exitosamente"<<endl;
}


void existencia(struct vehiculos *raiz){                                        
    
    char marcaB[20], modeloB[20], precioMIN[10], precioMAX[10], tipoB[2];
    int opc;

    struct vehiculos *temp = raiz;

    cout<<"\nConsultar existencia por:  "<<endl;
    cout<<"\n1. Marca"<<endl;
    cout<<"2. Modelo"<<endl;
    cout<<"3. Rango de precio"<<endl;
    cout<<"4. Tipo (P-propio C-consignado)"<<endl;
    cout<<"5. Salir"<<endl;
    cout<<"\nElija una opcion: "; cin>>opc;

    switch (opc){
        case 1:
        cout<<"\nDigite la marca: "; cin>>marcaB;
        cout<<"\n\tVehiculos disponibles"<<endl;
        while(temp != NULL){
          if(strcmp(temp->marca, marcaB)==0){             //SE IMPRIME DOBLE
              listaV(temp);
          }
            temp = temp->vsig;
        } break;

        case 2: 
        cout<<"\nDigite el modelo: "; cin>>modeloB;
        cout<<"\n\tVehiculos disponibles"<<endl;
        while(temp != NULL){
            if(strcmp(temp->modelo, modeloB)==0){         //SE IMPRIME DOBLE
               listaV(temp);
            }
               temp = temp->vsig;
        } break;

        case 4:
        cout<<"\nDigite el tipo: "; cin>>tipoB;
        cout<<"\n\tVehiculos disponibles"<<endl;
        while(temp != NULL){                                   //FUNCIONA A MEDIAS
            if(strcmp(temp->tipo, tipoB)==0){
                listaV(temp);
            }
             temp = temp->vsig;
        } break;

    default: cout<<"Opcion no valida"<<endl; break;
    }
    

}


void listaV(struct vehiculos *raiz){

    struct vehiculos *temp = raiz;
   

    while(temp != NULL){
        
        cout<<"\nPlaca: "<<temp->placa<<endl;
        cout<<"Marca: "<<temp->marca<<endl;
        cout<<"Modelo: "<<temp->modelo<<endl;
        cout<<"Color: "<<temp->color<<endl;
        cout<<"Año: "<<temp->año<<endl;
        cout<<"Precio: "<<temp->precio<<endl;
        cout<<"Tipo: "<<temp->tipo<<endl;
        cout<<"Estado: "<<temp->estado<<endl;

        struct hojadevida *temph = temp->hdv;
        while(temph != NULL){
            cout<<"Caracteristica: "<<temph->adicionales<<endl;
            temph = temph->hsig;
        }
        temp = temp->vsig;
    }
    

}
