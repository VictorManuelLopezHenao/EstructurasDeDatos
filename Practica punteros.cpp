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
    char año[5];
    char precio[11];
}vehiculoD[50]; //Array tipo estructura para almacenar los datos de los vehiculos
                   
void registro(int countV); 
void actualizar(int countV);      //Declaracion de funciones
void consultar(int countV);
void eliminar(int countV);
void listarVehiculos(int countV);
void buscaPorAño(int countV);
void countVA(int countV);

int main(){

    int opc; 
    int countV = 0; //Contador de vehiculos registrados
    cout<<"\t Bienvenido a Mcqueen"<<endl;
    
    do
    {   //Menu de opciones
        cout<<"\nPor favor selecccione una opción: "<<endl;  
        cout<<"\n1. Registrar vehículo"<<endl;;
        cout<<"2. Consultar vehículo"<<endl;;
        cout<<"3. Actualizar informacion"<<endl;;
        cout<<"4. Eliminar vehículo"<<endl;;
        cout<<"5. listar vehiculos"<<endl;
        cout<<"6. Buscar por año"<<endl;
        cout<<"7. Cuenta vehiculos activos"<<endl;
        cout<<"8. Salir"<<endl<<endl;
       
        cout<<"Opcion: "; cin>>opc; 
        
        switch(opc){
          
          case 1: cout<<endl<<"\t Registrar vehículo";
                  if(countV < 50) {
                    registro(countV); countV++;}    
                    else{
                    cout<<"\nNo hay espacio para mas vehiculos en este momento"<<endl;
                    } break; 
          
          case 2: cout<<endl<<"\t Consultar vehículo"; consultar(countV); break;
          
          case 3: cout<<endl<<"\t Actualizar informacion"; actualizar(countV); break; 
          
          case 4: cout<<endl<<"\t Eliminar vehículo"; eliminar(countV); break; 
          
          case 5: cout<<endl<<"\t Listar vehiculos"; listarVehiculos(countV); break;

          case 6: cout<<endl<<"\t Buscar por año"; buscaPorAño(countV); break;

          case 7: cout<<endl<<"\t Cuenta vehiculos activos"; countVA(countV); break;
          
          case 8: cout<<endl<<"Muchas gracias por visitarnos, te esperamos pronto"; break; 
           
          default: cout<<endl<<"Opción no valida"<<endl; break;
          
        }
    }while(opc!=8);   
        return 0;
}


bool validarEntrada(const char *entrada) { //Valida la entrada de datos
                                            //*entrada es un puntero a una cadena de caracteres

    while(*entrada != '\0'){ //Recorre la cadena hasta un caracter nulo
        if(!isupper(*entrada) && !isdigit(*entrada)){ //isupper, verifica si es letra mayuscula 
        return false;}                                //isdigit, verifica si es un digito
        entrada++;
    }
    return true;
}


void registro(int countV){
   
    datos *Nvehiculo = &vehiculoD[countV]; //Nvehiculo apunta a la direccion de memoria de la estructura 
                                           //que está en la posicion countV del array de datos
    
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
    if(!isdigit(*Nvehiculo->año)){
        cout<<"\nEntrada invalida. Solo se permiten dígitos."<<endl;
        return;
    }

    cout<<"Color: "; cin>>Nvehiculo->color;
    if(!validarEntrada(Nvehiculo->color)){ 
        cout<<"\nEntrada invalida. Solo se permiten dígitos."<<endl;
        return;
    }
    
    cout<<"Precio: "; cin>>Nvehiculo->precio;
    if(!isdigit(*Nvehiculo->precio)){ 
        cout<<"\nEntrada invalida. Solo se permiten dígitos."<<endl;
        return;
    }


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

    
    cout<<"\nVehiculo registrado exitosamente"<<endl;
    cout<<"\nQuedan "<<50 - countV - 1<<" espacios disponibles"<<endl;
}


void consultar(int countV){

    char marcaB[20], modeloB[15], tipoB[2]; 
    char precioMIN[11], precioMAX[11];                         //variables para la busqueda
    bool encontrado = false;

    datos *ptrB = vehiculoD;   //Puntero que apunta al array de punteros
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

                    while(ptrB < vehiculoD + countV){ //Mientras la direccion a la que apunta ptrB sea 
                                                      //sea menor a la direccion del ultimo vehiculo registrado
                        if(strcmp(ptrB->marca, marcaB) == 0){ //compara la marca ingresada con la marca del vehiculo
                            encontrado = true;
                            cout<<"\nPlaca: "<<(ptrB)->placa<<endl;
                            cout<<"Marca: "<<(ptrB)->marca<<endl;
                            cout<<"Modelo: "<<(ptrB)->modelo<<endl;
                            cout<<"Año: "<<(ptrB)->año<<endl;
                            cout<<"Color: "<<(ptrB)->color<<endl;
                            cout<<"Valor: "<<(ptrB)->precio<<endl;
                            cout<<"Tipo: "<<(ptrB)->tipo<<endl;
                            cout<<"Estado: "<<(ptrB)->estado<<endl;
                        }
                        ptrB++;
                    }
                    if(!encontrado){
                        cout<<"\nNo hay vehiculos marca "<<marcaB<<" disponibles en este momento"<<endl;
            }break;

            case 2: cout<<"Ingrese el modelo del vehiculo: "; cin>>modeloB; 
                    cout<<"\n\tVehiculos disponibles"<<endl;

                    while(ptrB < vehiculoD + countV){
                        if(strcmp(ptrB->modelo, modeloB) == 0){ //compara el modelo ingresado con el modelo del vehiculo
                            encontrado = true;
                            cout<<"\nPlaca: "<<(ptrB)->placa<<endl;
                            cout<<"Marca: "<<(ptrB)->marca<<endl;
                            cout<<"Modelo: "<<(ptrB)->modelo<<endl;
                            cout<<"Año: "<<(ptrB)->año<<endl;
                            cout<<"Color: "<<(ptrB)->color<<endl;
                            cout<<"Valor: "<<(ptrB)->precio<<endl;
                            cout<<"Tipo: "<<(ptrB)->tipo<<endl;
                            cout<<"Estado: "<<(ptrB)->estado<<endl;
                        }
                        ptrB++;
                    }
                    if(!encontrado){
                        cout<<"\nNo hay vehiculos modelo "<<modeloB<<" disponibles en este momento"<<endl;
            }break;

            case 3: cout<<"Ingrese el precio minimo: "; cin>>precioMIN;
                    cout<<"Ingrese el precio maximo: "; cin>>precioMAX;
                    cout<<"\n\tVehiculos disponibles"<<endl;

                    while(ptrB < vehiculoD + countV){
                        if(ptrB->precio >= precioMIN && ptrB->precio <= precioMAX){ 
                            encontrado = true;
                            cout<<"\nPlaca: "<<(ptrB)->placa<<endl;
                            cout<<"Marca: "<<(ptrB)->marca<<endl;
                            cout<<"Modelo: "<<(ptrB)->modelo<<endl;
                            cout<<"Año: "<<(ptrB)->año<<endl;
                            cout<<"Color: "<<(ptrB)->color<<endl;
                            cout<<"Valor: "<<(ptrB)->precio<<endl;
                            cout<<"Tipo: "<<(ptrB)->tipo<<endl;
                            cout<<"Estado: "<<(ptrB)->estado<<endl;
                        }
                        ptrB++;
                    }
                    if(!encontrado){
                        cout<<"\nNo hay vehiculos en ese rango de precio disponibles en este momento"<<endl;
            }break;

            case 4: cout<<"Ingrese el tipo (P-propio C-consignado): "; cin>>tipoB;
                    cout<<"\n\tVehiculos disponibles"<<endl;

                    while(ptrB < vehiculoD + countV){
                        if(strcmp(ptrB->tipo, tipoB) == 0){ 
                            encontrado = true;
                            cout<<"\nPlaca: "<<(ptrB)->placa<<endl;
                            cout<<"Marca: "<<(ptrB)->marca<<endl;
                            cout<<"Modelo: "<<(ptrB)->modelo<<endl;
                            cout<<"Año: "<<(ptrB)->año<<endl;
                            cout<<"Color: "<<(ptrB)->color<<endl;
                            cout<<"Valor: "<<(ptrB)->precio<<endl;
                            cout<<"Tipo: "<<(ptrB)->tipo<<endl;
                            cout<<"Estado: "<<(ptrB)->estado<<endl;
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


void actualizar(int countV){
    
    char placaB[7];
    int opc;
    datos *ptr = vehiculoD; 
    bool encontrado = false;
    
    cout<<"\n\nIngrese la placa del vehiculo a actualizar: "; cin>>placaB;

    while(ptr < vehiculoD + countV){
        if(strcmp(ptr->placa, placaB) == 0){
            encontrado = true;
            cout<<"\n¿Que datos desea actualizar?"<<endl;
            cout<<"\n1. Marca";
            cout<<"\n2. Modelo";
            cout<<"\n3. Año";
            cout<<"\n4. Color";
            cout<<"\n5. Precio";
            cout<<"\n6. Tipo";
            cout<<"\n7. Estado";
            cout<<"\n8. Salir"<<endl;
            cout<<"\nElija una opcion: "; cin>>opc;

            switch(opc){
                case 1: cout<<"\nIngrese la nueva marca: "; cin>>ptr->marca; break;
                case 2: cout<<"\nIngrese el nuevo modelo: "; cin>>ptr->modelo; break;
                case 3: cout<<"\nIngrese el nuevo año: "; cin>>ptr->año; break;
                case 4: cout<<"\nIngrese el nuevo color: "; cin>>ptr->color; break;
                case 5: cout<<"\nIngrese el nuevo precio: "; cin>>ptr->precio; break;
                case 6: cout<<"\nIngrese el nuevo tipo (P-propio C-consignado): "; cin>>ptr->tipo; break;
                case 7: cout<<"\nIngrese el nuevo estado (A-activo E-eliminado): "; cin>>ptr->estado; break;
                case 8: cout<<"\nGracias por visitarnos, te esperamos pronto"<<endl; break;

                default: cout<<"Opcion invalida"<<endl; break;
            }   
            
            cout<<"\nDatos actualizados correctamente"<<endl;
            return; 
        }
    }
       if(!encontrado){
       cout<<"\nVehiculo con placa "<<placaB<<" no encontrado"<<endl;
        } return;
}


void eliminar(int countV){
    char placaB[7];  
    bool encontrado = false;
    datos *ptrB = vehiculoD; //puntero que apunta al array de punteros

    cout<<"\n\nIngrese la placa del vehiculo que desea eliminar: "; cin>>placaB;

    while(ptrB < vehiculoD + countV){
        if(strcmp(ptrB->placa, placaB) == 0){  //*ptrB accede a la estructura a la que apunta el puntero pvehiculo
            encontrado = true;
            ptrB->estado[0] = 'E'; 
            cout<<"\nVehiculo eliminado exitosamente"<<endl;
            break;
        }
    }   
    if(!encontrado){
        cout<<"\nNo se encontro el vehiculo con placa "<<placaB<<endl;
    }
}


void listarVehiculos(int countV){
    
    datos *ptr = vehiculoD;

    if(countV == 0){
        cout<<"\nNo hay vehiculos registrados"<<endl;
        return;
    }

    while(ptr < vehiculoD + countV){
        cout<<"\nPlaca: "<<ptr->placa<<endl;
        cout<<"Marca: "<<ptr->marca<<endl;
        cout<<"Modelo: "<<ptr->modelo<<endl;
        cout<<"Año: "<<ptr->año<<endl;
        cout<<"Color: "<<ptr->color<<endl;
        cout<<"Valor: "<<ptr->precio<<endl;
        cout<<"Tipo: "<<ptr->tipo<<endl;
        cout<<"Estado: "<<ptr->estado<<endl;
        cout<<endl;
        ptr++;
    } 
}


void buscaPorAño(int countV){
    
  
    datos *ptr = vehiculoD;
    char añoB[5];
    bool encontrado = false;

    cout<<"\nIngrese el año a consultar: ";cin>>añoB;
  

  while(ptr < vehiculoD + countV){
    if(strcmp(ptr->año, añoB) == 0){
        encontrado = true;
        cout<<"\nPlaca: "<<ptr->placa<<endl;
        cout<<"Marca: "<<ptr->marca<<endl;
        cout<<"Modelo: "<<ptr->modelo<<endl;
        cout<<"Año: "<<ptr->año<<endl;
        cout<<"Color: "<<ptr->color<<endl;
        cout<<"Valor: "<<ptr->precio<<endl;
        cout<<"Tipo: "<<ptr->tipo<<endl;
        cout<<"Estado: "<<ptr->estado<<endl;
        
    } 
    ptr++;
} 

  if(!encontrado){
    cout<<"\nNo hay vehiculos del año "<<añoB<<" disponibles en este momento"<<endl;
  }
}


void countVA(int countV){
    int cuentaVA = 0;
    datos *ptr = vehiculoD;

    while(ptr < vehiculoD + countV){
        if(strcmp(ptr->estado, "A")==0){
            cuentaVA++;  
        }
        ptr++;
    }  cout<<"\n\nHay "<<cuentaVA<<" vehiculos en estado activo"<<endl;
    
      if(cuentaVA == 0){
        cout<<"No hay ningun vehiculo en estado Activo (A)"<<endl;
           }
}

