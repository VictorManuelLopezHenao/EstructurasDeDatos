#include <iostream> 
#include <fstream>
#include <cstring> //para usar strcmp
#include <cctype> //para usar isupper y isdigit

using namespace std;  

void registro();             //Declaracion de funciones
void guardardatos(); 
void consultar();
void actualizar(); 
void eliminar(); 
void listarVehiculos();
void buscarPorAño();
void CVA();

struct datos{   //Estructura de datos para los vehiculos
    char placa[7];
    char marca[20]; 
    char modelo[15]; 
    char color[10]; 
    char tipo[2]; 
    char estado[2];
    char año[11];
    char precio[11];
};


int main()  //Funcion principal
{
    int opc;
    
    cout<<"\t Bienvenido a Mcqueen"<<endl;
    
do
{   //Menu de opciones
    cout<<"\nPor favor selecccione una opción: "<<endl;  
    cout<<"\n1. Registrar vehículo"<<endl;;
    cout<<"2. Consultar vehículo"<<endl;;
    cout<<"3. Actualizar informacion"<<endl;;
    cout<<"4. Eliminar vehículo"<<endl;;
    cout<<"5. lista de vehiculos"<<endl;
    cout<<"6. Buscar por año"<<endl;
    cout<<"7. Cantidad vehiculos activos"<<endl;
    cout<<"8. Salir"<<endl<<endl;
   
    cout<<"Opcion: "; cin>>opc; 
    
    switch(opc){
      
      case 1: cout<<endl<<"\t Registrar vehículo"; registro(); break; 
      
      case 2: cout<<endl<<"\t Consultar vehículo"; consultar(); break;
      
      case 3: cout<<endl<<"\t Actualizar informacion"; actualizar(); break; 
      
      case 4: cout<<endl<<"\t Eliminar vehículo"; eliminar(); break; 

      case 5: cout<<endl<<"\t Lista de vehiculos"; listarVehiculos(); break;
      
      case 6: cout<<endl<<"\t Consultar por año"; buscarPorAño(); break;

      case 7: cout<<endl<<"\t Vehiculos Activos"; CVA(); break;

      case 8: cout<<endl<<"Muchas gracias por visitarnos, te esperamos pronto"; break; 
       
      default: cout<<endl<<"Opción no valida"<<endl; break;
      
    }
}while(opc!=8);   
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


bool validarEntrada(const char* entrada) {      //Valida la entrada de datos
    for (int i = 0; i < strlen(entrada); i++) {      //recorre la cadena de caracteres //strlen = longitud de la cadena 
        if (!isupper(entrada[i]) && !isdigit(entrada[i])) {   // isupper, verifica si es letra mayuscula //isdigit, verifica si es un digito
            return false; //si no es una letra mayuscula o un digito retorna falso
        }
    }
    return true;
}


void eliminar() {  //Cambia el estado del vehiculo a eliminado
    fstream archivo("DatosVehiculos.bin", ios::binary | ios::in | ios::out); // abre el archivo para lectura y escritura en modo binario

    if (!archivo.is_open()) { // verifica si el archivo se abrió correctamente
        cout << "Error al intentar abrir el archivo" << endl;
        return;
    }

    datos vehiculo; // crea una variable del tipo de la estructura
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
            archivo.seekp(-static_cast<int>(sizeof(datos)), ios::cur); //Mueve el puntero una posicion hacia atras del tamaño de la estructura
            archivo.write(reinterpret_cast<const char*>(&vehiculo), sizeof(datos));  //sobreescribe el registro
            break;
        }
    }

    if (!encontrado) {
        cout << "\nNo se encontró un vehículo con la placa " << placaB << endl;
    }

    archivo.close();
}


void actualizar() {   //Actualiza los datos de los vehiculos
    fstream archivo("DatosVehiculos.bin", ios::binary | ios::in | ios::out);

    if (!archivo.is_open()) {
        cout << "Error al intentar abrir el archivo" << endl;
        return;
    }

    datos vehiculo; // crea una variable del tipo de la estructura
    char placaB[7];
    bool encontrado = false;
    int opc2;

    cout << "\n\nIngrese la placa del vehiculo a actualizar: ";
    cin >> placaB;

    while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) { // lee los datos del archivo
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
            archivo.seekp(-static_cast<int>(sizeof(datos)), ios::cur); //Mueve el puntero una posicion hacia atras del tamaño de la estructura
            archivo.write(reinterpret_cast<const char*>(&vehiculo), sizeof(datos)); //sobreescribe el registro
            cout << "\nDatos actualizados correctamente"<<endl<< endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nNo se encontró un vehículo con la placa " << placaB << endl;
    }

    archivo.close();
}


void consultar() {    //Consulta los datos de los vehiculos

    datos vehiculo;    // crea una variable del tipo de la estructura
    char marcaB[20];   
    char modeloB[15];
    char precioMIN[11];             //variables para la busqueda
    char precioMAX[11];
    char tipo[2];
    bool encontrado = false;

    ifstream archivo("DatosVehiculos.bin", ios::binary | ios::in); //abre el archivo en modo lectura

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

            while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) { //lee los datos del archivo
                if (strcmp(vehiculo.marca, marcaB) == 0) {            //compara la marca ingresada con la marca del vehiculo
                    encontrado = true;          //si se encuentra un vehiculo 
                    cout << "\nPlaca: " << vehiculo.placa << endl; 
                    cout << "Marca: " << vehiculo.marca << endl;
                    cout << "Modelo: " << vehiculo.modelo << endl;
                    cout << "Año: " << vehiculo.año << endl;                //muestra los datos del vehiculo
                    cout << "Color: " << vehiculo.color << endl;
                    cout << "Valor: " << vehiculo.precio << endl;
                    cout << "Tipo: " << vehiculo.tipo << endl;
                    cout << "Estado: " << vehiculo.estado << endl;
                }
            }
            archivo.close(); //cierra el archivo
    
            if (!encontrado) {       //si no se encontraron vehiculos con la marca ingresada
                cout <<"\nNo hay vehiculos marca "<<marcaB<<" disponibles en este momento" << endl;
            } break;
    
        
        case 2: cout<<"Ingrese el modelo del vehiculo: "; cin>> modeloB; 
                cout<<"\n\tVehiculos disponibles"<<endl;
        
           while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) {//lee los datos del archivo
                 if (strcmp(vehiculo.modelo, modeloB) == 0) { //compara el modelo ingresado con el modelo del vehiculo
                  encontrado = true;
                  cout << "\nPlaca: " << vehiculo.placa << endl;
                  cout << "Marca: " << vehiculo.marca << endl;
                  cout << "Modelo: " << vehiculo.modelo << endl;
                  cout << "Año: " << vehiculo.año << endl;                //muestra los datos del vehiculo
                  cout << "Color: " << vehiculo.color << endl;
                  cout << "Valor: " << vehiculo.precio << endl;
                  cout << "Tipo: " << vehiculo.tipo << endl;
                  cout << "Estado: " << vehiculo.estado << endl;
            }
        }
        archivo.close(); //cierra el archivo

            if (!encontrado) {
             cout <<"\nNo hay vehiculos modelo "<<modeloB<<" disponibles en este momento" << endl;
           }break;


        case 3: cout<<"Ingrese el precio minimo: ";cin>> precioMIN;
                cout<<"Ingrese el precio maximo: ";cin>> precioMAX; 
                cout<<"\n\tVehiculos disponibles"<<endl;
                
                while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) {
                    if (vehiculo.precio >= precioMIN && vehiculo.precio <= precioMAX) { //compara el rango de precio ingresado con el precio del vehiculo
                     encontrado = true;
                     cout << "\nPlaca: " << vehiculo.placa << endl;
                     cout << "Marca: " << vehiculo.marca << endl;
                     cout << "Modelo: " << vehiculo.modelo << endl;
                     cout << "Año: " << vehiculo.año << endl;             //muestra los datos del vehiculo
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
              
      while (archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))) {  //lee los datos del archivo
          if (strcmp(vehiculo.tipo, tipo) == 0) { //compara el tipo ingresado con el tipo del vehiculo
           encontrado = true;
           cout << "\nPlaca: " << vehiculo.placa << endl;
           cout << "Marca: " << vehiculo.marca << endl;
           cout << "Modelo: " << vehiculo.modelo << endl; 
           cout << "Año: " << vehiculo.año << endl;                //muestra los datos del vehiculo
           cout << "Color: " << vehiculo.color << endl; 
           cout << "Valor: " << vehiculo.precio << endl;
           cout << "Tipo: " << vehiculo.tipo << endl;
           cout << "Estado: " << vehiculo.estado << endl;
     }
      
  }
 
  archivo.close(); //cierra el archivo
     if (!encontrado) {       
      cout << "\nNo hay vehiculos de tipo " << tipo << " disponibles en este momento" << endl;
      }
      break;
      default:    //si la opcion ingresada no es valida
            cout << "\nOpción no válida" << endl;
            break;
    }
}


void registro(){ //registra los datos de los vehiculos
    
    datos vehiculo; //crea una variable del tipo de la estructura
    cout<<endl<<"\nIngrese los siguientes datos "<<endl; 
    
    cout<<endl<<"Placa: "; cin>>vehiculo.placa;
    if (!validarEntrada(vehiculo.placa)) {  //valida la entrada 
        cout << "Entrada inválida. Solo se permiten letras mayúsculas y dígitos." << endl;
        return; //si la entrada no es valida sale de la funcion

    }
        ifstream archivo("DatosVehiculos.bin", ios::binary | ios::in);
        if(!archivo.is_open()){
            cout<<"\nError al abrir el archivo"<<endl;
            return;
        }
        datos Vexistente;

        while (archivo.read(reinterpret_cast<char*>(&Vexistente), sizeof(datos))){
        if(strcmp(Vexistente.placa, vehiculo.placa)==0){
            cout<<"El vehiculo con placa "<<vehiculo.placa<<" ya ha sido registrado"<<endl;
            return;
        }
    }
    archivo.close();  
    

    cout<<"Marca: "; cin>>vehiculo.marca;
    
    if (!validarEntrada(vehiculo.marca)) {
        cout << "Entrada inválida. Solo se permiten letras mayúsculas y dígitos." << endl;
        return;
    }

    cout<<"Modelo: "; cin>>vehiculo.modelo;
    if(!validarEntrada(vehiculo.modelo)){
        cout<<"Entrada inválida. Solo se permiten letras mayúsculas y dígitos."<<endl;
        return;
    }

    cout<<"Año: "; cin>>vehiculo.año;
    if(!isdigit(vehiculo.año[0])){
        cout<<"Entrada inválida. Solo se permiten dígitos."<<endl;
        return;
    }


    cout<<"Color: "; cin>>vehiculo.color;   
    if (!validarEntrada(vehiculo.color)) {
        cout << "Entrada inválida. Solo se permiten letras mayúsculas y dígitos." << endl;
        return;
    }                

    cout<<"Valor: "; cin>>vehiculo.precio;
    if(!isdigit(vehiculo.precio[0])){
        cout<<"Entrada inválida. Solo se permiten dígitos."<<endl;
        return;
    }
    
    cout<<"Tipo: "; cin>>vehiculo.tipo; 
    if (!validarEntrada(vehiculo.tipo)) {
        cout << "Entrada inválida. Solo se permiten letras mayúsculas y dígitos." << endl;
        return;
    }

    cout<<"Estado: "; cin>>vehiculo.estado; 
    if (!validarEntrada(vehiculo.estado)) {
        cout << "Entrada inválida. Solo se permiten letras mayúsculas y dígitos." << endl;
        return;
    }

    guardardatos(vehiculo);
}


void listarVehiculos(){

    ifstream archivo("DatosVehiculos.bin", ios::binary | ios::in);  //abre el archivo en modo lectura 

    if(!archivo.is_open()){
        cout<<"Error al intentar abrir el archivo"<<endl;
        return;
    }

    datos vehiculo;

            cout<<"\n\tVehiculos almacenados"<<endl;
    
    while(archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))){
        cout<<endl<<vehiculo.placa<<endl;
        cout<<vehiculo.marca<<endl;
        cout<<vehiculo.modelo<<endl;
        cout<<vehiculo.año<<endl;
        cout<<vehiculo.color<<endl;
        cout<<vehiculo.precio<<endl;
        cout<<vehiculo.tipo<<endl;
        cout<<vehiculo.estado<<endl;
    }
    archivo.close();
}


void buscarPorAño(){

datos vehiculo;
char añoB[5];
bool encontrado = false;

ifstream archivo("DatosVehiculos.bin", ios::binary | ios::in);

  if(!archivo.is_open()){
    cout<<"Error al abrir el archivo"<<endl;
    return;
  }

  cout<<"\nDigite el año a consultar: "<<endl; cin>>añoB;

  while(archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))){
   if(strcmp(vehiculo.año, añoB)==0){
    encontrado = true;
    cout<<"\nPlaca: "<<vehiculo.placa<<endl;
    cout<<"Marca: "<<vehiculo.marca<<endl;
    cout<<"Modelo: "<<vehiculo.modelo<<endl;
    cout<<"Año: "<<vehiculo.año<<endl;
    cout<<"Color: "<<vehiculo.color<<endl;
    cout<<"Precio: "<<vehiculo.precio<<endl;
    cout<<"Tipo: "<<vehiculo.tipo<<endl;
    cout<<"Estado: "<<vehiculo.estado<<endl;
   }
  }
  archivo.close();

  if(!encontrado){
    cout<<"\nNo hay vehiculos año "<<añoB<<" disponibles"<<endl;
  }
}


void CVA(){

    datos vehiculo;
    int count = 0;

    ifstream archivo("DatosVehiculos.bin", ios::binary | ios::in);

    if(!archivo.is_open()){
        cout<<"\nError al abrir el archivo"<<endl;
        return;
    }

    while(archivo.read(reinterpret_cast<char*>(&vehiculo), sizeof(datos))){
        if(strcmp(vehiculo.estado, "A")==0){
            count++;
        }
    } cout<<"\nCantidad de vehiculos Activos : "<<count<<endl;

    if(count == 0){
        cout<<"\nNo hay vehiculos de estado A-activo disponibles"<<endl;
    }

}