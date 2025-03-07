#include <iostream>
#include <cstring> //para el strcmp

using namespace std;

void registraV(struct vehiculos *&raiz);  //*& trabaja con el puntero original
void caracteristicas(struct vehiculos *&raiz);
void existencia(struct vehiculos *raiz);   //* trabaja con una copia del puntero
void actualizar(struct vehiculos *&raiz);   
void eliminar_activar(struct vehiculos *&raiz);
void vborrados(struct vehiculos *&raiz, struct vehiculos *&eliminado);
void imprime(struct vehiculos *temp);
void listaV(struct vehiculos *raiz, struct vehiculos *eliminado, int tipolista);
void countA_E(struct vehiculos *raiz, struct vehiculos *eliminado);


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

    struct vehiculos *raiz = NULL;     //inicio de la lista de vehiculos = NULL
    struct vehiculos *eliminado = NULL;   //inicio de la liste de vehiculos borrados = NULL
   
    int opc;
    int opc2;

    cout<<"\tBienvenidos a Mcqueen"<<endl;

    do{
    cout<<"\nMenú de opciones"<<endl;
    cout<<"\n1. Registrar vehiculos"<<endl;
    cout<<"2. Agregar caracteristicas de vehiculos"<<endl;
    cout<<"3. Existencia de vehiculos"<<endl;
    cout<<"4. Actualizar informacion de vehiculos"<<endl;            //menú
    cout<<"5. Eliminar o activar vehiculos"<<endl;
    cout<<"6. Mover vehiculos eliminados"<<endl;
    cout<<"7. Lista total de vehiculos"<<endl;
    cout<<"8. Cantidad de vehiculos"<<endl;
    cout<<"9. Salir"<<endl;
    cout<<"\nElija una opcion: "; cin>>opc;

    switch(opc){
        case 1: cout<<"\n\n\tRegistrar vehiculos"<<endl; registraV(raiz); 
                cout<<"\n¿Desea agregar las caracteristicas del vehiculo?"<<endl;   
                cout<<"\n1. Si"<<endl;
                cout<<"2. No"<<endl;                          //Opcion de agregar caracteristicas implementada en registar
                cout<<"\nElija una opcion: "; cin>>opc2;
                if(opc2 == 1){
                    caracteristicas(raiz);
                };
            break; //termina la ejecucion del bloque

        case 2: cout<<"\n\n\tHoja de vida del vehiculo"<<endl; caracteristicas(raiz); break;

        case 3: cout<<"\n\n\tExistencia de vehiculos"<<endl; existencia(raiz); break;

        case 4: cout<<"\n\n\tActualizar informacion"<<endl; actualizar(raiz); break;

        case 5: cout<<"\n\n\tEliminar o activar vehiculos"<<endl; eliminar_activar(raiz); break;

        case 6: cout<<"\n\n\tMover vehiculos eliminados"<<endl; vborrados(raiz, eliminado); break;

        case 7: cout<<"\n\n\tLista de vehiculos"<<endl; 
                int tipolista;
                  cout<<"\nElija la lista a consultar: "<<endl;
                  cout<<"\n1. Vehiculos A-activos"<<endl;            //solicita el tipo de lista a imprimir
                  cout<<"2. Vehiculos B-borrados"<<endl;             //y se le manda como argumento a la func ListaV
                  cout<<"\nSeleccione una opcion: "; cin>>tipolista;  //Esto sirve para una mejor legibilidad y ejecucion
              listaV(raiz, eliminado, tipolista); break;

        
        case 8: cout<<"\n\n\tCantidad de vehiculos"<<endl; countA_E(raiz, eliminado); break;

        case 9: cout<<"\n¡Muchas gracias por visitarnos, vuelve pronto!"<<endl; break;  //sale del bucle del menú
        
        default: cout<<"Opcion invalida"<<endl; break;  //si la opc es diferente a las expresadas en el menú, se ejecuta de nuevo el menú
    }

}while(opc!=9); //se ejecuta la primera vez, de ahi en adelante en bucle mientras la opc sea diferente a 8

    return 0;
}


void registraV(struct vehiculos *&raiz){
    struct vehiculos *nuevo;               
    nuevo = new(struct vehiculos);         //reserva memoria para un nuevo nodo y almacena la direccion de este en nuevo

    cout<<"\nIngrese la siguiente informacion"<<endl;
    cout<<"\nPlaca: "; cin>>nuevo->placa;
    cout<<"Marca: "; cin>>nuevo->marca;
    cout<<"Modelo: "; cin>>nuevo->modelo;
    cout<<"Color: "; cin>>nuevo->color;                 //solicita la informacion del vehiculo
    cout<<"Año: "; cin>>nuevo->año;
    cout<<"Precio: "; cin>>nuevo->precio;
    cout<<"Tipo: "; cin>>nuevo->tipo;
    cout<<"Estado: "; cin>>nuevo->estado;

    if(raiz==NULL){            //si la lista está vacia
        nuevo->vsig = NULL;     //nuevo en sgte es NULL
        nuevo->hdv = NULL;      //nuevo en hoja de vida es NULL
        raiz = nuevo;           //nuevo será el primer nodo de la lista
    } else {
        struct vehiculos *temp = raiz;   //ptr que recorre la lista 

        while(temp->vsig != NULL){       //recorre toda la lista nodo por nodo, en este caso busca el nodo final para agg un nuevo nodo
            temp = temp->vsig;     //avanza al sgte nodo
        }

        temp->vsig = nuevo;          //en el sig del nodo final(temp) se asigna la direccion de memoria de nuevo
        nuevo->vsig = NULL;          //ahora nuevo es el ultimo nodo      
        nuevo->hdv = NULL;           //Y se le asiga NULL al ptr a hojadevida
    } 

    cout<<"\nVehiculo registrado exitosamente"<<endl;
}


void caracteristicas(struct vehiculos *&raiz){

    int opc;                  
    char placaB[7];  //placa para la busqueda

    cout<<"\nDigite la placa del vehiculo: "; cin>>placaB;  //se solicita la placa para la busqueda 

    struct vehiculos *tempV = raiz;  //ptr para recorrer la lista de vehiculos

   while(tempV != NULL && (strcmp(tempV->placa, placaB) != 0)){ //si la lista no ha terminado y la placa en ese nodo es diferente a la ingresada 
    tempV = tempV->vsig; //se avanza al sgte nodo
   }

   if(tempV == NULL) { //si tempV == NULL, es porque la placa no se encontró
    cout << "\nVehículo no encontrado." << endl; 
    return; //se returna a la func ppal
}
    
    do{  
    struct hojadevida *nuevaH;
    nuevaH = new(struct hojadevida);   //se reserva memoria para un nuevo nodo, y nuevaH almacena esa direccion
    
    cout<<"\nIngrese las caracteristicas del vehiculo (sin espacios)"<<endl;
    cout<<"\n-> "; cin>>nuevaH->adicionales;  //solicita el ingreso de las caracteristicas
    

    if(tempV->hdv == NULL){   //si el vehiculo no tiene hoja de vida
        nuevaH->hsig = NULL;   //sig en hoja de vida es NULL, ya que es el primer nodo de la lista
        tempV->hdv = nuevaH;      //se guarda en esa posicion la direccion de la hoja de vida digilenciada
       }
      
       else {      //si el vehiculo tiene hoja de vida 
        
        struct hojadevida *tempH = tempV->hdv;  //tempH recorre la lista de hoja de vida

        while (tempH->hsig != NULL) {     //se recorre la lista hojadevida, en este caso busca el nodo final
            tempH = tempH->hsig;    //avanza al sgte nodo de la lista 
        }

        tempH->hsig = nuevaH;  //se conectan los nodos, en el sig de la hdv existente se almacena la direccion del nuevo nodo (nuevaH)
        nuevaH->hsig = NULL;  //ahora el nuevo nodo (nuevaH) es el ultimo
    }

    cout<<"\n¿Desea agregar mas caracteristicas?"<<endl;
    cout<<"\n1. Si"<<endl;                                //se pregunta si se quieren agregar mas caracteristicas
    cout<<"2. No"<<endl;                                    
    cout<<"\nElija una opcion: "; cin>>opc; cout<<endl;    //se solicita una opcion
   
}while(opc!=2); //se ejecuta la primera vez y de ahi en adelante en bucle mientras se escoja la opc 1

    
    cout<<"\nCaracteristicas agregadas exitosamente"<<endl;
}


void existencia(struct vehiculos *raiz){                                        
    
    char marcaB[20], modeloB[20], tipoB[2];
    int opc;                                  //variables para la busqueda
    int precioMIN, precioMAX;
    struct vehiculos *temp = raiz;    //ptr que recorre la lista 

    cout<<"\nConsultar existencia por:  "<<endl;
    cout<<"\n1. Marca"<<endl;
    cout<<"2. Modelo"<<endl;
    cout<<"3. Rango de precio"<<endl;                       //opciones para consultar la existencia de un vhclo
    cout<<"4. Tipo (P-propio C-consignado)"<<endl;
    cout<<"5. Salir"<<endl;
    cout<<"\nElija una opcion: "; cin>>opc;

    switch (opc){
        case 1:     //si se elije marca 
        cout<<"\nDigite la marca: "; cin>>marcaB;  //se solicita la marca para la busqueda
        cout<<"\n\tVehiculos disponibles"<<endl;    //se imprime un mensaje netamente estetico
        while(temp != NULL){        //se recorre la lista nodo por nodo hasta el final
          if(strcmp(temp->marca, marcaB)==0){       //si la marca ingresada es igual a la del nodo actual
              imprime(temp);    //se manda la direccion del nodo actual a imprime y este imprime todos los datos del vehiculo
          }
            temp = temp->vsig;  //avanza al sgte nodo
        } break; //termina la ejecucion del bloque

        case 2:  //si se elije modelo
        cout<<"\nDigite el modelo: "; cin>>modeloB;  //se solicita el modelo para la busqueda
        cout<<"\n\tVehiculos disponibles"<<endl;
        while(temp != NULL){       //se recorre la lista nodo por nodo hasta el final
            if(strcmp(temp->modelo, modeloB)==0){     //si el modelo ingresado es igual al del nodo actual
               imprime(temp); //se manda la direccion del nodo actual a imprime y este imprime todos los datos del vhclo
            }
               temp = temp->vsig; //avanza al sgte nodo
        } break;  //termina la ejecucion del bloque 

        case 3:  //si se elije rango de precio
        cout<<"\nDigite el precio minimo: "; cin>>precioMIN;  //se solicita el precio minimo para la busqueda
        cout<<"Digite el precio maximo: "; cin>>precioMAX;  //y el precio maximo
        cout<<"\nVehiculos disponible"<<endl;
        while(temp != NULL){   //se recorre la lista nodo a nodo hasta el final
         if(precioMIN < temp->precio && precioMAX > temp->precio){  //si el precio del nodo actual está en el rango de dinero ingresado
            imprime(temp); //se le manda a imprime la direccion del nodo actual y este imprime todos los datos del vhclo
         }
           temp = temp->vsig;  //avanza al sgte nodo
        } break; //termina la ejecucion del bloque 

        case 4:  //si se elije tipo
        cout<<"\nDigite el tipo: "; cin>>tipoB;  //se solicita el tipo para la busqueda
        cout<<"\n\tVehiculos disponibles"<<endl;
        while(temp != NULL){            //recorre la lista nodo por nodo hasta el final
            if(strcmp(temp->tipo, tipoB)==0){ //si el tipo ingresado es igual al del nodo actual
                imprime(temp);//se manda a imprime la direccion del nodo actual, y este imprime todos los datos del vhclo
            }
             temp = temp->vsig; //avanza al ste nodo
        } break; //termina la ejecucion del bloque
 
        case 5: cout<<"\nVolviendo al menú...."<<endl; return; break; //regresa al menú si asi lo solicita le usuario

    default: cout<<"Opcion no valida"<<endl; break; //si la opc no es valida, vuelve a la func ppal
    }
}


void actualizar(struct vehiculos *&raiz){
    
    char placaB[7];  //placa para hacer la busqueda
    int opc;      

    struct vehiculos *temp = raiz;     //ptr que recorre la lista

    cout<<"\nDigite la placa del vehiculo a actualizar: "; cin>>placaB;  //solicita la placa para la busqueda 

    while(temp != NULL && (strcmp(temp->placa, placaB)!=0)){   //si la lista no ha terminado y la placa en ese nodo es diferete a la ingresada
        temp = temp->vsig;       //avanza al sgte nodo
    }

    if(temp == NULL){  //si temp==NULL, es porque la placa no se encontró
        cout<<"\nVehiculo con placa "<<placaB<<" no encontrado"<<endl;
        return;  //me retorna a la func ppal
    }

    cout<<"\n¿Que informacion desea actualizar?"<<endl;    
    cout<<"1. Precio"<<endl;                    //opciones de actualizacion
    cout<<"2. Tipo"<<endl;
    cout<<"\nElija una opcion: "; cin>>opc;    //solicita la opcion a ejecutar

    if(opc == 1){    //si se elije precio
        cout<<"\nNuevo precio: "; cin>>temp->precio;  //se pide el nuevo precio y se almacena en la variable precio del nodo actual
    } else if (opc == 2){  //si se elije tipo
        cout<<"\nNuevo tipo (P-propio C-consignado): "; cin>>temp->tipo;  //se pide el nuevo tipo y se almacena en la variable tipo del nodo actual
    } else {
        cout<<"\nOpcion no valida"<<endl; return; //si se elije otra opc, se retorna a la func ppal
    }

    cout<<"\nInformacion actualizada exitosamente"<<endl;

}


void eliminar_activar(struct vehiculos *&raiz){

    char placaB[7];        //placa para hacer la busqueda

    struct vehiculos *temp = raiz;      //ptr para recorrer la lista 

    cout<<"\nDigite la placa del vehiculo: "; cin>>placaB;    //solicita la placa para hacer la busqueda 

    while(temp != NULL && strcmp(temp->placa, placaB)!=0){    //si la lista no ha terminado y la placa en ese nodo es diferente a la ingresada
        temp = temp->vsig;                                    //avanza al siguiente nodo
    } 

    if(temp == NULL){     //si temp==NULL, es porque la placa no se encontró
        cout<<"\nVehiculo con placa "<<placaB<<" no encontrado"<<endl; 
        return;   //me retorna a la func ppal
    }

    if(strcmp(temp->estado, "A")==0){       //si el estado del vehiculo es A
        temp->estado[0] = 'E';             //se cambia el estado a E
    } else {
        temp->estado[0] = 'A';         //si no es A, es decir, es E, se cambia el estado a A
    }

    cout<<"\nCambio de estado del vehiculo exitoso"<<endl;
}


void vborrados(struct vehiculos *&raiz, struct vehiculos *&eliminado){

    struct vehiculos *temp = raiz;   //ptr para recorrer la lista
    struct vehiculos *ant = NULL;     //ptr al nodo anterior a temp

    while(temp != NULL){            //Recorre la lista nodo por nodo hasta el final
       if(temp->estado[0] == 'E'){      //si el estado del vehiculo es Eliminado
       
    struct vehiculos *tempeli = temp;    //se guarda en tempeli el nodo eliminado
         
        if(ant == NULL){            //si el nodo a eliminar es el primero
            raiz = temp->vsig;       //se actualiza la raiz, para que apunte al siguiente
         }else{
          ant->vsig = temp->vsig;      //si no, se actualiza ant para que salte el nodo eliminado, y apunte al sgte
         }
         
         temp = temp->vsig;  // Avanza al siguiente nodo antes de modificar el eliminado
         
         
          tempeli->vsig = eliminado;         // Inserta el nodo eliminado al inicio de la lista de eliminados
          eliminado = tempeli;      //se actualiza eliminado para que apunte al nuevo nodo eliminado
         
        } else {
            ant = temp;  //si el vehiculo no es E, ant apunta al nodo actual
            temp = temp->vsig;  //y temp al siguiente
        }
    }

    cout << "\nVehiculos eliminados movidos exitosamente" << endl;
}


void listaV(struct vehiculos *raiz, struct vehiculos *eliminado, int tipolista){

    struct vehiculos *temp = raiz;
    
    if(tipolista == 1){   //si el tipo de lista es vehiculos activos 
        temp = raiz;         //temp toma el valor de raiz (ptr a la lista de activos)
    } else if(tipolista == 2){   //si es la lista de eliminados 
        temp = eliminado;     //temp toma el valor de eliminado (ptr a la lista de eliminados)
    }; 

    while(temp != NULL){      //se recorre la lista nodo por nodo hasta el final 
        imprime(temp);        //se llama a imprime, para imprimir los datos del vehiculo actual(temp)
        temp = temp->vsig;     //avanza al sgte nodo de la lista
    }
}     


void imprime(struct vehiculos *temp){

        cout<<"\n\nPlaca: "<<temp->placa<<endl;              
        cout<<"Marca: "<<temp->marca<<endl;
        cout<<"Modelo: "<<temp->modelo<<endl;
        cout<<"Color: "<<temp->color<<endl;       //imprime los datos registrados de cada vehiculo
        cout<<"Año: "<<temp->año<<endl;
        cout<<"Precio: "<<temp->precio<<endl;
        cout<<"Tipo: "<<temp->tipo<<endl;
        cout<<"Estado: "<<temp->estado<<endl;

       
      
       struct hojadevida *aux = temp->hdv;   //se crea un puntero a la hoja de vida de un vehiculo actual (temp)
       while (aux != NULL){                 //se recorre la lista de hojas de vida 
        cout<<"Caracteristica: ";       
        cout<<aux->adicionales<<endl;       //se imprimen las caracteristicas encontradas
         aux = aux->hsig;                  //se avanza al siguiente nodo de la lista de caracteristicas
       }
}


void countA_E(struct vehiculos *raiz, struct vehiculos *eliminado){
    
    int countA = 0;
    int countE = 0;

    struct vehiculos *temp = raiz;

    while(temp != NULL){
        temp = temp->vsig;
        countA++;
    }

    temp = eliminado;
   
    while(temp!=NULL){
        temp = temp->vsig;
        countE++;
    }
     
    cout<<"\nCantidad de vehiculos Activos: "<<countA<<endl<<"Cantidad de vehiculos Eliminados: "
    <<countE<<endl<<"Cantidad total de vehiculos: "<<countA + countE<<endl;

}


void ordena_tipo(struct vehiculos *&raiz){

    struct vehiculos *temp = raiz;

    while(temp != NULL){
        if(strcmp(temp->tipo, "C")==0)
        imprime(temp);
        temp=temp->vsig;
    }

    while(temp != NULL){
        if(strcmp(temp->tipo, "P")==0){
            imprime(temp);
            temp = temp->vsig;
        }
    }

}