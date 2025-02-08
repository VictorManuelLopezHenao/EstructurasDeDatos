#include <iostream> 
#include <fstream>
#include <cstring>

using namespace std;

void registro(); 
void guardardatos(); 
void consultar();
void actualizar(); 
void eliminar(); 

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


int main() 
{
    int opc;
    char rata[7];
    
    cout<<"\t Bienvenido a Mcqueen"<<endl;
    
do
{
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


void guardardatos(const datos &vehiculo){  //Guarda los datos de los vehiculos en un archivo binario

    ofstream archivo("DatosVehiculos.bin", ios::binary | ios::app);       //abre el archivo para escritura en modo binario 
                                                                         //para agregar datos al final del archivo se usa ios::app
    if (archivo.is_open()) {                                                   //verifica si el archivo se abrio correctamente
        archivo.write(reinterpret_cast<const char*>(&vehiculo), sizeof(datos));  //escribe los datos en el archivo
        archivo.close();                                                            //cierra el archivo
        cout << "\nSe registraron los datos correctamente" << endl;
    } else {
        cout << "Error al intentar abrir el archivo" << endl;
    }
}


void eliminar() {
    fstream archivo("DatosVehiculos.bin", ios::binary | ios::in | ios::out); // abre el archivo para lectura y escritura en modo binario

    if (!archivo.is_open()) { // verifica si el archivo se abrió correctamente
        cout << "Error al intentar abrir el archivo" << endl;
        return;
    }

    datos vehiculo;
    char placaB[7];
    bool encontrado = false;

    cout << "\n\nIngrese la placa del vehiculo a eliminar: ";
    cin >> placaB;

    while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) { // lee los datos del archivo
        if (strcmp(vehiculo.placa, placaB) == 0) { // compara la placa ingresada con la placa del vehiculo
            encontrado = true;
            vehiculo.estado[0] = 'E'; // cambia el estado del vehiculo a eliminado
            cout << "\nVehiculo eliminado correctamente" << endl;

            // Mueve el puntero de archivo hacia atrás para sobrescribir el registro
            archivo.seekp(-static_cast<int>(sizeof(datos)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&vehiculo), sizeof(datos));
            break;
        }
    }

    if (!encontrado) {
        cout << "\nNo se encontró un vehículo con la placa " << placaB << endl;
    }

    archivo.close();
}


void actualizar() {
    fstream archivo("DatosVehiculos.bin", ios::binary | ios::in | ios::out);

    if (!archivo.is_open()) {
        cout << "Error al intentar abrir el archivo" << endl;
        return;
    }

    datos vehiculo;
    char placaB[7];
    bool encontrado = false;
    int opc2;

    cout << "\n\nIngrese la placa del vehiculo a actualizar: ";
    cin >> placaB;

    while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) {
        if (strcmp(vehiculo.placa, placaB) == 0) {
            encontrado = true;
            cout << "\n¿Que datos desea actualizar?" << endl;
            cout << "\n1. Precio" << endl;
            cout << "2. Estado" << endl;
            cout << "3. Tipo" << endl;
            cout << "\nOpcion: "; cin >> opc2;

            if (opc2 == 1) {
                cout << "Ingrese el nuevo precio: "; cin >> vehiculo.precio;
            } else if (opc2 == 2) {
                cout << "Ingrese el nuevo estado (A-activo E-eliminado): "; cin >> vehiculo.estado;
            } else if(opc2 == 3) {
                cout << "Ingrese el nuevo tipo (P-propio C-consignado): "; cin >> vehiculo.tipo;
            } else {
                cout << "Opción no válida" << endl;
                return;
            }

            // Mueve el puntero de archivo hacia atrás para sobrescribir el registro
            archivo.seekp(-static_cast<int>(sizeof(datos)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&vehiculo), sizeof(datos));
            cout << "\nDatos actualizados correctamente"<<endl<< endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nNo se encontró un vehículo con la placa " << placaB << endl;
    }

    archivo.close();
}


void consultar() {

    datos vehiculo;
    char marcaB[20];
    char modeloB[15];
    int precioMIN;
    int precioMAX;
    char tipo[2];
    bool encontrado = false;

    ifstream archivo("DatosVehiculos.bin", ios::binary | ios::in);

   cout<<endl<<"\nElija una opcion de busqueda: "<<endl;
   cout<<"\n1. Marca"<<endl;
   cout<<"2. Modelo"<<endl;
   cout<<"3. Rango de precio"<<endl;
   cout<<"4. Tipo (P-propio C-consignado)"<<endl;
   
   int opc;
   cout<<"\nOpcion: "; cin>>opc;

    switch(opc){
        case 1: cout<<"Ingrese la marca del vehiculo: "; cin>> marcaB;  
                cout<<"\n\tVehiculos disponibles"<<endl;

            while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) {
                if (strcmp(vehiculo.marca, marcaB) == 0) {
                    encontrado = true;
                    cout << "\nPlaca: " << vehiculo.placa << endl;
                    cout << "Marca: " << vehiculo.marca << endl;
                    cout << "Modelo: " << vehiculo.modelo << endl;
                    cout << "Año: " << vehiculo.año << endl;
                    cout << "Color: " << vehiculo.color << endl;
                    cout << "Valor: " << vehiculo.precio << endl;
                    cout << "Tipo: " << vehiculo.tipo << endl;
                    cout << "Estado: " << vehiculo.estado << endl;
                }
            }
            archivo.close();
    
            if (!encontrado) {
                cout <<"\nNo hay vehiculos marca "<<marcaB<<" disponibles en este momento" << endl;
            } break;
    
        
        case 2: cout<<"Ingrese el modelo del vehiculo: "; cin>> modeloB; 
                cout<<"\n\tVehiculos disponibles"<<endl;
        
           while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) {
                 if (strcmp(vehiculo.modelo, modeloB) == 0) {
                  encontrado = true;
                  cout << "\nPlaca: " << vehiculo.placa << endl;
                  cout << "Marca: " << vehiculo.marca << endl;
                  cout << "Modelo: " << vehiculo.modelo << endl;
                  cout << "Año: " << vehiculo.año << endl;
                  cout << "Color: " << vehiculo.color << endl;
                  cout << "Valor: " << vehiculo.precio << endl;
                  cout << "Tipo: " << vehiculo.tipo << endl;
                  cout << "Estado: " << vehiculo.estado << endl;
            }
        }
        archivo.close();

            if (!encontrado) {
             cout <<"\nNo hay vehiculos modelo "<<modeloB<<" disponibles en este momento" << endl;
           }break;


        case 3: cout<<"Ingrese el precio minimo: ";cin>> precioMIN;
                cout<<"Ingrese el precio maximo: ";cin>> precioMAX; 
                cout<<"\n\tVehiculos disponibles"<<endl;
                
                while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) {
                    if (vehiculo.precio >= precioMIN && vehiculo.precio <= precioMAX) {
                     encontrado = true;
                     cout << "\nPlaca: " << vehiculo.placa << endl;
                     cout << "Marca: " << vehiculo.marca << endl;
                     cout << "Modelo: " << vehiculo.modelo << endl;
                     cout << "Año: " << vehiculo.año << endl;
                     cout << "Color: " << vehiculo.color << endl;
                     cout << "Valor: " << vehiculo.precio << endl;
                     cout << "Tipo: " << vehiculo.tipo << endl;
                     cout << "Estado: " << vehiculo.estado << endl;
               }
           }
           archivo.close();
   
               if (!encontrado) {
                cout <<"\nNo hay vehiculos en ese rango de precio disponibles en este momento" << endl;
              }break;


        case 4: cout<<"Ingrese el tipo (P-propio - C-consignado): "; cin>>tipo;
              cout<<"\n\tVehiculos disponibles"<<endl;
              
      while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) {
          if (strcmp(vehiculo.tipo, tipo) == 0) {
           encontrado = true;
           cout << "\nPlaca: " << vehiculo.placa << endl;
           cout << "Marca: " << vehiculo.marca << endl;
           cout << "Modelo: " << vehiculo.modelo << endl;
           cout << "Año: " << vehiculo.año << endl;
           cout << "Color: " << vehiculo.color << endl;
           cout << "Valor: " << vehiculo.precio << endl;
           cout << "Tipo: " << vehiculo.tipo << endl;
           cout << "Estado: " << vehiculo.estado << endl;
     }
      
  }
 
  archivo.close();
     if (!encontrado) { 
      cout << "\nNo hay vehiculos de tipo " << tipo << " disponibles en este momento" << endl;
      }
      break;
      default:
            cout << "\nOpción no válida" << endl;
            break;
    }
}


void registro(){ //registra los datos de los vehiculos
    
    datos vehiculo;
    cout<<endl<<"\nIngrese los siguientes datos "<<endl; 
    cout<<endl<<"Placa: "; cin>>vehiculo.placa;
    cout<<"Marca: "; cin>>vehiculo.marca;
    cout<<"Modelo: "; cin>>vehiculo.modelo;
    cout<<"Año: "; cin>>vehiculo.año;
    cout<<"Color: "; cin>>vehiculo.color;                                                                                                                                                                                                                                      
    cout<<"Valor: "; cin>>vehiculo.precio;
    cout<<"Tipo: "; cin>>vehiculo.tipo; 
    cout<<"Estado: "; cin>>vehiculo.estado; 

    guardardatos(vehiculo);
}
