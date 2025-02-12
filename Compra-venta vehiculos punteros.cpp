#include<iostream>
#include<cstring> //para usar strcmp
#include<cctype> //para usar isupper y isdigit

using namespace std;

struct datos{   //Estructura de datos para los vehiculos
    char placa[7];
    char marca[20]; 
    char modelo[15]; 
    char color[10]; 
    char tipo[2]; 
    char estado[2];
    int año;
    int precio;
};

datos vehiculoD[50]; //Array de estructuras que almacena los datos de los vehiculos
datos *pvehiculo[50]; //Array de punteros a la estructura 
int countV = 0; //Contador de vehiculos registrados
                          

void registro();
void actualizar();      //Declaracion de funciones
void consultar();
void eliminar();

int main(){

    int opc; 
    cout<<"\t Bienvenido a Mcqueen"<<endl;
    
    do
    {   //Menu de opciones
        cout<<"\nPor favor selecccione una opción: "<<endl;  
        cout<<"\n1. Registrar vehículo"<<endl;;
        cout<<"2. Consultar vehículo"<<endl;;
        cout<<"3. Actualizar informacion"<<endl;;
        cout<<"4. Eliminar vehículo"<<endl;;
        cout<<"5. Salir"<<endl<<endl;
       
        cout<<"Opcion: "; cin>>opc; 
        
        switch(opc){
          
          case 1: cout<<endl<<"\t Registrar vehículo"; registro(); break; 
          
          case 2: cout<<endl<<"\t Consultar vehículo"; consultar(); break;
          
          case 3: cout<<endl<<"\t Actualizar informacion"; actualizar(); break; 
          
          case 4: cout<<endl<<"\t Eliminar vehículo"; eliminar(); break; 
          
          case 5: cout<<endl<<"Muchas gracias por visitarnos, te esperamos pronto"; break; 
           
          default: cout<<endl<<"Opción no valida"<<endl; break;
          
        }
    }while(opc!=5);   
        return 0;
}


bool validarEntrada(const char *entrada) { //Valida la entrada de datos

    while(*entrada != '\0'){ //Recorre la cadena hasta un caracter nulo
        if(!isupper(*entrada) && !isdigit(*entrada)){ //isupper, verifica si es letra mayuscula 
        return false;}                                //isdigit, verifica si es un digito
        entrada++;
    }
    return true;
}


void registro(){
   
    if(countV >= 50){
        cout<<"\nNo hay espacio para mas vehiculos en este momento"<<endl;
        return;
    }

    datos *Nvehiculo = &vehiculoD[countV]; //Nvehiculo apunta a la direccion de memoria de la estructura 
                                           //que está en la posicion countV del array de datos
    pvehiculo[countV] = Nvehiculo; //almacena el puntero Nvehiculo en la posicion countV del array de punteros

    cout<<"\n\nIngrese los siguientes datos"<<endl;
    cout<<"\nPlaca: "; cin>>Nvehiculo->placa;  //-> Accede a miembros de una estructura a través de un puntero
    if(!validarEntrada(Nvehiculo->placa)){
        cout<<"\nEntrada invalida. Solo se permiten letras mayúsculas y dígitos."<<endl;
        return;
    }

    cout<<"Marca: "; cin>>Nvehiculo->marca;   //-> desreferencia el puntero y obtiene la estructura a la que apunta
    if(!validarEntrada(Nvehiculo->marca)){  
        cout<<"\nEntrada invalida. Solo se permiten letras mayúsculas y dígitos."<<endl;
        return;
    }

    cout<<"Modelo: "; cin>>Nvehiculo->modelo;  //Nvehiculo->modelo = (*Nvehiculo).modelo
    if(!validarEntrada(Nvehiculo->modelo)){ 
        cout<<"\nEntrada invalida. Solo se permiten letras mayúsculas y dígitos."<<endl;
        return;
    }
    
    cout<<"Año: "; cin>>Nvehiculo->año;
   
    cout<<"Color: "; cin>>Nvehiculo->color;
    if(!validarEntrada(Nvehiculo->color)){ 
        cout<<"\nEntrada invalida. Solo se permiten letras mayúsculas y dígitos."<<endl;
        return;
    }
    
    cout<<"Precio: "; cin>>Nvehiculo->precio;


    cout<<"Tipo (P-propio C-consignado): "; cin>>Nvehiculo->tipo;
    if(!validarEntrada(Nvehiculo->tipo)){ 
        cout<<"\nEntrada invalida. Solo se permiten letras mayúsculas y dígitos."<<endl;
        return;
    }
    
    cout<<"Estado (A-activo E-eliminado): "; cin>>Nvehiculo->estado;
    if(!validarEntrada(Nvehiculo->estado)){ 
        cout<<"\nEntrada invalida. Solo se permiten letras mayúsculas y dígitos."<<endl;
        return;
    }

    countV++; //incrementa en 1 el contador de vehiculos registrados
    cout<<"\nVehiculo registrado exitosamente"<<endl;
}


void consultar(){

    char marcaB[20], modeloB[15], tipoB[2]; 
    int precioMIN, precioMAX;                         //variables para la busqueda
    bool encontrado = false;

    datos **ptrB = pvehiculo;   //Puntero a un puntero que apunta al array de punteros
                                //puntero que apunta a un puntero (**)

   cout<<endl<<"\nElija una opcion de busqueda: "<<endl;
   cout<<"\n1. Marca"<<endl;
   cout<<"2. Modelo"<<endl;
   cout<<"3. Rango de precio"<<endl;
   cout<<"4. Tipo (P-propio C-consignado)"<<endl;

     int opc;
     cout<<"\nOpcion: "; cin>>opc;

        switch(opc){
            case 1: cout<<"Ingrese la marca del vehiculo: "; cin>>marcaB;
                    cout<<"\n\tVehiculos disponibles"<<endl;

                    while(ptrB < pvehiculo + countV){ //Mientras la direccion a la que apunta ptrB sea 
                                                      //sea menor a la direccion del ultimo vehiculo registrado
                        if(strcmp((*ptrB)->marca, marcaB) == 0){ //compara la marca ingresada con la marca del vehiculo
                            encontrado = true;
                            cout<<"\nPlaca: "<<(*ptrB)->placa<<endl;
                            cout<<"Marca: "<<(*ptrB)->marca<<endl;
                            cout<<"Modelo: "<<(*ptrB)->modelo<<endl;
                            cout<<"Año: "<<(*ptrB)->año<<endl;
                            cout<<"Color: "<<(*ptrB)->color<<endl;
                            cout<<"Valor: "<<(*ptrB)->precio<<endl;
                            cout<<"Tipo: "<<(*ptrB)->tipo<<endl;
                            cout<<"Estado: "<<(*ptrB)->estado<<endl;
                        }
                        ptrB++;
                    }
                    if(!encontrado){
                        cout<<"\nNo hay vehiculos marca "<<marcaB<<" disponibles en este momento"<<endl;
            }break;

            case 2: cout<<"Ingrese el modelo del vehiculo: "; cin>>modeloB; 
                    cout<<"\n\tVehiculos disponibles"<<endl;

                    while(ptrB < pvehiculo + countV){
                        if(strcmp((*ptrB)->modelo, modeloB) == 0){ //compara el modelo ingresado con el modelo del vehiculo
                            encontrado = true;
                            cout<<"\nPlaca: "<<(*ptrB)->placa<<endl;
                            cout<<"Marca: "<<(*ptrB)->marca<<endl;
                            cout<<"Modelo: "<<(*ptrB)->modelo<<endl;
                            cout<<"Año: "<<(*ptrB)->año<<endl;
                            cout<<"Color: "<<(*ptrB)->color<<endl;
                            cout<<"Valor: "<<(*ptrB)->precio<<endl;
                            cout<<"Tipo: "<<(*ptrB)->tipo<<endl;
                            cout<<"Estado: "<<(*ptrB)->estado<<endl;
                        }
                        ptrB++;
                    }
                    if(!encontrado){
                        cout<<"\nNo hay vehiculos modelo "<<modeloB<<" disponibles en este momento"<<endl;
            }break;

            case 3: cout<<"Ingrese el precio minimo: "; cin>>precioMIN;
                    cout<<"Ingrese el precio maximo: "; cin>>precioMAX;
                    cout<<"\n\tVehiculos disponibles"<<endl;

                    while(ptrB < pvehiculo + countV){
                        if((*ptrB)->precio >= precioMIN && (*ptrB)->precio <= precioMAX){ 
                            encontrado = true;
                            cout<<"\nPlaca: "<<(*ptrB)->placa<<endl;
                            cout<<"Marca: "<<(*ptrB)->marca<<endl;
                            cout<<"Modelo: "<<(*ptrB)->modelo<<endl;
                            cout<<"Año: "<<(*ptrB)->año<<endl;
                            cout<<"Color: "<<(*ptrB)->color<<endl;
                            cout<<"Valor: "<<(*ptrB)->precio<<endl;
                            cout<<"Tipo: "<<(*ptrB)->tipo<<endl;
                            cout<<"Estado: "<<(*ptrB)->estado<<endl;
                        }
                        ptrB++;
                    }
                    if(!encontrado){
                        cout<<"\nNo hay vehiculos en ese rango de precio disponibles en este momento"<<endl;
            }break;

            case 4: cout<<"Ingrese el tipo (P-propio C-consignado): "; cin>>tipoB;
                    cout<<"\n\tVehiculos disponibles"<<endl;

                    while(ptrB < pvehiculo + countV){
                        if(strcmp((*ptrB)->tipo, tipoB) == 0){ 
                            encontrado = true;
                            cout<<"\nPlaca: "<<(*ptrB)->placa<<endl;
                            cout<<"Marca: "<<(*ptrB)->marca<<endl;
                            cout<<"Modelo: "<<(*ptrB)->modelo<<endl;
                            cout<<"Año: "<<(*ptrB)->año<<endl;
                            cout<<"Color: "<<(*ptrB)->color<<endl;
                            cout<<"Valor: "<<(*ptrB)->precio<<endl;
                            cout<<"Tipo: "<<(*ptrB)->tipo<<endl;
                            cout<<"Estado: "<<(*ptrB)->estado<<endl;
                        }
                        ptrB++;
                    }
                    if(!encontrado){
                        cout<<"\nNo hay vehiculos de tipo "<<tipoB<<" disponibles en este momento"<<endl;
             }break;

             default: cout<<"\nOpcion no valida"<<endl;
             break;
}
}


void actualizar(){}


void eliminar(){
    char placaB[7];
    bool encontrado = false;
    datos **ptrB = pvehiculo;

    cout<<"\n\nIngrese la placa del vehiculo que desea eliminar: "; cin>>placaB;

    while(ptrB < pvehiculo + countV){
        if(strcmp((*ptrB)->placa, placaB) == 0){
            encontrado = true;
            (*ptrB)->estado[0] = 'E';
            cout<<"\nVehiculo eliminado exitosamente"<<endl;
            break;
        }
    }   
    if(!encontrado){
        cout<<"\nNo se encontro el vehiculo con placa "<<placaB<<endl;
    }
}




