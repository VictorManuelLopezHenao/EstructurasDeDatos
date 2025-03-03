#include <iostream>
#include <cstring>

using namespace std;

void registraV(struct vehiculos *&raiz);  //*& trabaja con el puntero original
void caracteristicas(struct vehiculos *&raiz);
void existencia(struct vehiculos *raiz);
void actualizar(struct vehiculos *&raiz);
void eliminar_activar(struct vehiculos *&raiz);
void vborrados(struct vehiculos *&raiz, struct eliminados *&raizelim);
void listaV(struct vehiculos *raiz, struct eliminados *raizelim);

struct eliminados{
    struct vehiculos *elim;
    struct eliminados *esig;
};

struct vehiculos{
    char placa[7]; char marca[20], modelo[20], color[10], año[5], tipo[2], estado[2];
    int precio;
    struct hojadevida *hdv;
    struct vehiculos *vsig;
};

struct hojadevida{
    char adicionales[30];
    struct hojadevida *hsig;
};



int main(){

    struct vehiculos *raiz = NULL;
    struct eliminados *raizelim = NULL;
   
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

        case 4: cout<<"\n\n\tActualizar informacion"<<endl; actualizar(raiz); break;

        case 5: cout<<"\n\n\tEliminar o activar vehiculos"<<endl; eliminar_activar(raiz); break;

        case 6: cout<<"\n\n\tMover vehiculos eliminados"<<endl; vborrados(raiz, raizelim); break;

        case 7: cout<<"\n\n\tLista de vehiculos"<<endl; listaV(raiz, raizelim); break;

        case 8: cout<<"\n¡Muchas gracias por visitarnos, vuelve pronto!"<<endl; break;
        
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
    
    char marcaB[20], modeloB[20], tipoB[2];
    int opc;
    int precioMIN, precioMAX;
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
          if(strcmp(temp->marca, marcaB)==0){            
              listaV(temp, NULL); // para llamar a listaV con NULL para raizelim
          }
            temp = temp->vsig;
        } break;

        case 2: 
        cout<<"\nDigite el modelo: "; cin>>modeloB;
        cout<<"\n\tVehiculos disponibles"<<endl;
        while(temp != NULL){
            if(strcmp(temp->modelo, modeloB)==0){         //cambiar a listaV, por lo que tiene ella adentro.
               listaV(temp, NULL);
            }
               temp = temp->vsig;
        } break;

        case 3: 
        cout<<"\nDigite el precio minimo: "; cin>>precioMIN;
        cout<<"Digite el precio maximo: "; cin>>precioMAX;
        cout<<"\nVehiculos disponible"<<endl;
        while(temp != NULL){
         if(precioMIN < temp->precio && precioMAX > temp->precio){
            listaV(temp, NULL);
         }
           temp = temp->vsig;
        } break;

        case 4:
        cout<<"\nDigite el tipo: "; cin>>tipoB;
        cout<<"\n\tVehiculos disponibles"<<endl;
        while(temp != NULL){                                   
            if(strcmp(temp->tipo, tipoB)==0){
                listaV(temp, NULL);
            }
             temp = temp->vsig;
        } break;
 
        case 5: cout<<"\nVolviendo al menú...."<<endl; return; break;

    default: cout<<"Opcion no valida"<<endl; break;
    }
}


void actualizar(struct vehiculos *&raiz){
    
    char placaB[7];
    int opc;

    struct vehiculos *temp = raiz;

    cout<<"\nDigite la placa del vehiculo a actualizar: "; cin>>placaB;

    while(temp != NULL && (strcmp(temp->placa, placaB)!=0)){
        temp = temp->vsig;
    }

    if(temp == NULL){
        cout<<"\nVehiculo con placa "<<placaB<<" no encontrado"<<endl;
        return;
    }

    cout<<"\n¿Que informacion desea actualizar?"<<endl;
    cout<<"1. Precio"<<endl;
    cout<<"2. Tipo"<<endl;
    cout<<"\nElija una opcion: "; cin>>opc;

    if(opc == 1){
        cout<<"\nNuevo precio: "; cin>>temp->precio;
    } else if (opc == 2){
        cout<<"\nNuevo tipo (P-propio C-consignado): "; cin>>temp->tipo;
    } else {
        cout<<"\nOpcion no valida"<<endl; return;
    }

    cout<<"\nInformacion actualizada exitosamente"<<endl;

}


void eliminar_activar(struct vehiculos *&raiz){

    char placaB[7]; 

    struct vehiculos *temp = raiz;

    cout<<"\nDigite la placa del vehiculo: "; cin>>placaB;

    while(temp != NULL && strcmp(temp->placa, placaB)!=0){
        temp = temp->vsig;
    }

    if(temp == NULL){
        cout<<"\nVehiculo con placa "<<placaB<<" no encontrado"<<endl;
        return;
    }

    if(strcmp(temp->estado, "A")==0){
        temp->estado[0] = 'E';
    } else {
        temp->estado[0] = 'A';
    }

    cout<<"\nCambio de estado del vehiculo exitoso"<<endl;
}


void vborrados(struct vehiculos *&raiz, struct eliminados *&raizelim){

    struct vehiculos *temp = raiz;
    struct vehiculos *prev = NULL;

    while(temp != NULL){
        if(temp->estado[0] == 'E'){
            struct eliminados *nuevoElim;
            nuevoElim = new(struct eliminados);
            nuevoElim->elim = temp;
            nuevoElim->esig = raizelim;
            raizelim = nuevoElim;

            if(prev == NULL) {
                raiz = temp->vsig;
            } else {
                prev->vsig = temp->vsig;
            }

            struct vehiculos *tempElim = temp;
            temp = temp->vsig;
            tempElim->vsig = NULL;
            
        } else {
            prev = temp;
            temp = temp->vsig;
        }
    }
    
    cout << "\nVehiculos eliminados movidos exitosamente" << endl;
    return;
}


void listaV(struct vehiculos *raiz, struct eliminados *raizelim){

    int opc;

    struct vehiculos *temp = raiz;
   

        cout<<"\nElija la lista a consultar: "<<endl;
        cout<<"\n1. Vehiculos A-activos"<<endl;
        cout<<"2. Vehiculos B-borrados"<<endl;
        cout<<"\nSeleccione una opcion: "; cin>>opc;

        if(opc == 1){

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

    } else if(opc==2){
        struct eliminados *tempElim = raizelim;
        while(tempElim != NULL) {
            struct vehiculos *temp = tempElim->elim;
            cout << "\nPlaca: " << temp->placa << endl;
            cout << "Marca: " << temp->marca << endl;
            cout << "Modelo: " << temp->modelo << endl;
            cout << "Color: " << temp->color << endl;
            cout << "Año: " << temp->año << endl;
            cout << "Precio: " << temp->precio << endl;
            cout << "Tipo: " << temp->tipo << endl;
            cout << "Estado: " << temp->estado << endl;

            struct hojadevida *temph = temp->hdv;
            while(temph != NULL) {
                cout << "Caracteristica: " << temph->adicionales << endl;
                temph = temph->hsig;
            }
            tempElim = tempElim->esig;
        }
    } else {
        cout<<"\nOpcion no valida"<<endl;
        return;
    }
    }

