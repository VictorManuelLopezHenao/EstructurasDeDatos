#include <iostream> 
#include <string>
#include <fstream>
using namespace std;


struct datos{   //Estructura de datos para los vehiculos
    string placa, marca, modelo, color, estado, tipo;
    int año;
    float valor;
};

void guardardatos(const datos &vehiculo){  //Guarda los datos de los vehiculos en un archivo binario

    ofstream archivo("DatosVehiculos.bin", ios::binary | ios::app);       //abre el archivo para escritura en modo binario 
                                                                         //para agregar datos al final del archivo se usa ios::app
    if (archivo.is_open()) {                                                   //verifica si el archivo se abrio correctamente
        archivo.write(reinterpret_cast<const char*>(&vehiculo), sizeof(datos));  //escribe los datos en el archivo
        archivo.close();                                                            //cierra el archivo
        cout << "Se registraron los datos correctamente" << endl;
    } else {
        cout << "Error al intentar abrir el archivo" << endl;
    }
}

void consultar() {
    // Abre el archivo para lectura en modo binario
    ifstream archivo("DatosVehiculos.bin", ios::binary | ios::in);

    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cout << "Error al intentar abrir el archivo para lectura" << endl;
        return;
    }

    datos vehiculo;
    string placabuscada;

    cout << endl << "\nIngrese la placa del vehículo que desea consultar: "; 
    cin >> placabuscada;

    // Lee y compara los datos de cada vehículo en el archivo
    while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) {
        if (vehiculo.placa == placabuscada) {
            // Si se encuentra el vehículo, muestra la información
            cout << endl << "Placa: " << vehiculo.placa << endl;
            cout << "Marca: " << vehiculo.marca << endl;
            cout << "Modelo: " << vehiculo.modelo << endl;
            cout << "Año: " << vehiculo.año << endl;
            cout << "Color: " << vehiculo.color << endl;
            cout << "Valor: " << vehiculo.valor << endl;
            cout << "Tipo: " << vehiculo.tipo << endl;
            cout << "Estado: " << vehiculo.estado << endl;
            archivo.close(); 
            return; // Detiene la búsqueda después de encontrar el vehículo
        }
    }

    cout << "Vehículo con placa " << placabuscada << " no encontrado." << endl;

    archivo.close(); 
}


void registro(){ //registra los datos de los vehiculos
    
    datos vehiculo;
    
    cout<<endl<<"\nIngrese los siguientes datos "<<endl; 
    cout<<endl<<"Placa: "; cin>>vehiculo.placa;
    cout<<"Marca: "; cin>>vehiculo.marca;
    cout<<"Modelo: "; cin>>vehiculo.modelo;
    cout<<"Año: "; cin>>vehiculo.año;
    cout<<"Color: "; cin>>vehiculo.color;                                                                                                                                                                                                                                      
    cout<<"Valor: "; cin>>vehiculo.valor;
    cout<<"Tipo: "; cin>>vehiculo.tipo; 
    cout<<"Estado: "; cin>>vehiculo.estado; 

    guardardatos(vehiculo);
}



int main() 
{
    int opc;
    
    cout<<"\t Bienvenido a Mcqueen"<<endl;
    
    inicio: 

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
      
      case 3: cout<<endl<<"\t Actualizar informacion";break; 
      
      case 4: cout<<endl<<"\t Eliminar vehículo";break; 
      
      case 5: cout<<endl<<"Muchas gracias por visitarnos, te esperamos pronto"; break; 
       
      default: cout<<endl<<"Opción no valida"<<endl; goto inicio;
      
    }
    
    return 0;
}

