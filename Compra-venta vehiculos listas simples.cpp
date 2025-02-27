#include <iostream>
#include <cstring>

using namespace std;

void registraV(struct vehiculos *&raiz);  //*& trabaja con el puntero original
void caracteristicas(struct vehiculos *&raiz);

struct vehiculos{
    char placa[7];
    struct hojadevida *hdv;
    struct vehiculos *vsig;
};

struct hojadevida{
    char marca[20], modelo[20], color[10], año[5], precio[11], tipo, estado;
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
    cout<<"3. Consultar vehiculos"<<endl;
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
                cout<<"Elija una opcion: "; cin>>opc2;
                if(opc2 == 1){
                    caracteristicas(raiz);
                };
            break;

        case 2: cout<<"\n\n\tHoja de vida del vehiculo"<<endl; caracteristicas(raiz); break;

        case 3: 

        case 4:

        case 5: 

        case 6:

        case 7: 

        case 8:

        default: cout<<"Opcion invalida"<<endl; break;
    }

}while(opc!=8);

    return 0;
}


void registraV(struct vehiculos *&raiz){
    struct vehiculos *nuevo;               
    nuevo = new(struct vehiculos);         //reserva memoria para un nuevo nodo y almacena la direccion de este 

    cout<<"\nIngrese la placa del vehiculo: "; cin>>nuevo->placa;

    if(raiz==NULL){
        nuevo->vsig = NULL;           //si la lista está vacia, nuevo será el primer nodo de la lista
        raiz = nuevo; 
    } else {
        struct vehiculos *temp = raiz;

        while(temp->vsig != NULL){       //Busca al ultimo nodo de la lista
            temp = temp->vsig;
        }

        temp->vsig = nuevo;          //Y en su sig asigna la direccion de memoria de nuevo
        nuevo->vsig = NULL;          //ahora nuevo es el ultimo nodo      
        raiz->hdv = NULL;     
    } 

    cout<<"\nVehiculo registrado exitosamente"<<endl;
}


void caracteristicas(struct vehiculos *&raiz){

    char placaB[7];

    cout<<"\nDigite la placa del vehiculo: "; cin>>placaB;

    struct vehiculos *tempV = raiz;

    while(tempV != NULL && (strcmp(tempV->placa, placaB) !=0)) {  //Busca si antes de llegar al ultimo nodo, hay una placa igual a la ingresada
        tempV = tempV->vsig;
    }

    if(tempV == NULL){
        cout<<"\nVehiculo no encontrado"<<endl;          //esto es porque llego al final y no encontró una placa igual
        return;
    }
    
    struct hojadevida *nuevaH;
    nuevaH = new(struct hojadevida);   //almacena la direccion en memoria que reservo para el nuevo nodo

    cout<<"\nIngrese los siguientes datos"<<endl;
    cout<<"\nMarca: "; cin>>nuevaH->marca;
    cout<<"Modelo: "; cin>>nuevaH->modelo;
    cout<<"Color: "; cin>>nuevaH->color;
    cout<<"Año: "; cin>>nuevaH->año;
    cout<<"Precio: "; cin>>nuevaH->precio;
    cout<<"Tipo: "; cin>>nuevaH->tipo;
    cout<<"Estado: "; cin>>nuevaH->estado;


    if(tempV->hdv==NULL){
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
    cout<<"\nCaracteristicas agregadas exitosamente"<<endl;
}

void consultar(struct vehiculos *raiz){

    char marcaB[20], modeloB[20], precioMIN[10], precioMAX[10], tipo;

    cout<<"\Elija una opcion de busqueda: "<<endl;
    cout<<"\n1. Marca"<<endl;
    cout<<"2. Modelo"<<endl;
    cout<<"3. Rango de precio"<<endl;
    cout<<"4. Tipo (P-propio C-consignado)"<<endl;





}
