#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>
using namespace std;

struct datos{
    int id, tel, edad;
    char nombres[30], apellidos[30], sexo[10];
    char fechaservicio[11];
    datos *sig;
};

void registrar(datos *&raiz, datos *&fondo, int edad);
void elimPersonaCola(datos *&raiz, datos *&fondo);
void sgteTurno(datos *&raiz, datos *&fondo, datos *&raizP);
void ListadoAtendidasPila(datos *&raizP);
void guardardatos(datos *&raizP);
void liberarmemoria(datos *&raiz);
void obtenerFecha(char* destino);


int main(){

    int opc;
    int edad;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    bool salir = false;

    datos *raiz = NULL; datos *fondo = NULL;
    datos *raiz1 = NULL; datos *fondo1 = NULL; 
    datos *raiz2 = NULL; datos *fondo2 = NULL; 
    datos *raiz3 = NULL; datos *fondo3 = NULL; 

    datos *raizP = NULL;

    do{
        cout<<"\n\tMenú principal"<<endl;
        cout<<"\n1. Registrar persona"<<endl;
        cout<<"2. Turno siguiente"<<endl;
        cout<<"3. Eliminar persona de la cola"<<endl;
        cout<<"4. Listado de personas atendidas"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"\nElija una opcion: "; cin>>opc;

        switch(opc){

            case 1: cout<<"\n\tRegistro"<<endl;
            cout<<"\nIngrese su edad: "; cin>>edad;
            
            if(edad > 55){
                registrar(raiz1, fondo1, edad);

            } else if(edad <= 55 && edad > 40){

                registrar(raiz2, fondo2, edad);
            } else if(edad <= 40 && edad > 0){

                registrar(raiz3, fondo3, edad);
            } else { 

                cout<<"\nEdad no valida"<<endl;
            } break;

            
            case 2: 
    cout << "\n\tTurno siguiente" << endl;

    
    if (raiz1 != NULL && count1 < 3) {
        sgteTurno(raiz1, fondo1, raizP);
        count1++;
    } 

    else if (raiz2 != NULL && count2 < 2) {
        sgteTurno(raiz2, fondo2, raizP);
        count2++;
    } 
    
    else if (raiz3 != NULL && count3 < 1) {
        sgteTurno(raiz3, fondo3, raizP);
        count3++;
    } 
    
    else {
        
        if (raiz1 == NULL && raiz2 == NULL && raiz3 == NULL) {
            cout << "\nNo hay pacientes registrados" << endl;
        } else {
            
            count1 = count2 = count3 = 0;
        }
    }
    break;
                      
         case 3: cout<<"\n\tEliminar persona de la cola"<<endl; 
            
            if(raiz1 == NULL && raiz2 == NULL && raiz3 == NULL){
                cout<<"\nNo hay pacientes registrados"<<endl;
                break;
            }

            cout<<"\nIngrese su edad: "; cin>>edad;
            
            if(edad > 55){
                elimPersonaCola(raiz1, fondo1);

            } else if(edad <= 55 && edad > 40){
                elimPersonaCola(raiz2, fondo2);

            } else if(edad <= 40 && edad > 0){
                elimPersonaCola(raiz3, fondo3);

            } else {
                cout<<"\nEdad no valida"<<endl;
            } break;

        
            case 4: cout<<"\n\tListado de personas atendidas"<<endl; 
            
            if(raizP == NULL){
                cout<<"\nNinguna persona ha sido atendida"<<endl;
            } else {
            ListadoAtendidasPila(raizP);
             } break;


            case 5: 
            if(raiz1 != NULL || raiz2 != NULL || raiz3 != NULL){
                cout<<"\nEl programa no se puede cerrar ya que no se ha atentido a todas las personas"<<endl;                
            } else {
                cout<<"\nGuardando datos..."<<endl;

                guardardatos(raizP);
                liberarmemoria(raiz1);
                liberarmemoria(raiz2);
                liberarmemoria(raiz3);
                liberarmemoria(raizP);

                cout<<"\nPrograma cerrado. Vuelve pronto..."<<endl;
                salir = true;
            }break;

            default: cout<<"\nOpcion no valida"<<endl; break;
        }

    }while(salir!=true);

    return 0;

}

void registrar(datos *&raiz, datos *&fondo, int edad){ 

    datos *nuevo = new(struct datos);

    cout<<"\nDigite la siguiente informacion: "<<endl;
    cout<<"\nNombres: "; cin.ignore(); cin.getline(nuevo->nombres, 30);
    cout<<"Apellidos: "; cin.getline(nuevo->apellidos, 30);
    cout<<"Sexo: "; cin>>nuevo->sexo;
    cout<<"N° de identificacion: "; cin>>nuevo->id; 
    cout<<"N° de telefono: "; cin>>nuevo->tel;
    nuevo->edad = edad;

    obtenerFecha(nuevo->fechaservicio);
    
    datos *auxR = NULL;
    datos *auxF = NULL;
    bool duplicado = false;

    while (raiz != NULL) {
        datos *temp = raiz;
        raiz = raiz->sig;
        temp->sig = NULL;

        if (temp->id == nuevo->id) {
            duplicado = true;
        }

        // Mover el nodo a la cola auxiliar
        if (auxR == NULL) {
            auxR = temp;
            auxF = temp;
        } else {
            auxF->sig = temp;
            auxF = temp;
        }
    }

    if (duplicado) {
        cout << "\nError: La persona con ID " << nuevo->id << " ya solicitó un turno." << endl;
        delete nuevo; // Liberar memoria del nodo creado
        return;
    }

    raiz = auxR;
    fondo = auxF;

        nuevo->sig = NULL;

        if(raiz == NULL){
            raiz = nuevo;
            fondo = nuevo;
        } else {
            fondo->sig = nuevo;
            fondo = nuevo;
        }

}

void sgteTurno(datos *&raiz, datos *&fondo, datos *&raizP){  //problemas
    
    cout<<"\nSiguiente turno:\n"<<endl;
    cout<<raiz->nombres<<" "<<raiz->apellidos<<endl;
    cout<<"ID: "<<raiz->id<<endl;

    datos *temp = raiz;
    raiz = raiz->sig;

    temp->sig = raizP;
    raizP = temp;
       
    if(raiz == NULL){
        fondo = NULL;
    }
}

void elimPersonaCola(datos *&raiz, datos *&fondo){
   
    int idB;
    cout<<"\nIngrese la identificacion de la persona a eliminar: "; cin>>idB;

    datos *auxR = NULL;
    datos *auxF = NULL;
    bool encontrado = false;


    while(raiz != NULL){
        datos *temp = raiz;
        raiz = raiz->sig;
        temp->sig = NULL;
        
        if(temp->id == idB && !encontrado){
            datos *elim = temp;
            delete elim;
            cout<<"\nPersona eliminada correctamente"<<endl;
            encontrado = true;
        } else {
            if(auxR == NULL){
                auxR = temp;
                auxF = temp;
            } else {
                auxF->sig = temp;
                auxF = temp;
            }
        }
      
    }
    raiz = auxR;
    fondo = auxF;
    
    if(!encontrado){
        cout<<"\nNo se encontró la persona con ID: "<<idB<<endl;
    }
}

void ListadoAtendidasPila(datos *&raizP){

    datos *aux = NULL;

    cout<<"\nPersonas atendidas:\n";
    
    while(raizP != NULL){
       
        cout<<raizP->nombres<<" "<<raizP->apellidos<<endl;
        cout<<"Id: "<<raizP->id<<endl<<endl;

        datos *temp = raizP;
        raizP = raizP->sig;
        temp->sig = aux;
        aux = temp;
    }

    while(aux != NULL){
        datos *temp = aux;
        aux = aux->sig;
        temp->sig = raizP;
        raizP = temp;
    }
}

void guardardatos(datos *&raizP) {
    ofstream archivo("PersonasAtendidas.bin", ios::binary | ios::app);

    if (!archivo.is_open()) {
        cout << "\nError al intentar abrir el archivo." << endl;
        return;
    }

    while (raizP != NULL) {
        datos persona; 
        // Copiar campo por campo
        persona.id = raizP->id;
        persona.tel = raizP->tel;
        persona.edad = raizP->edad;
        strcpy(persona.nombres, raizP->nombres);
        strcpy(persona.apellidos, raizP->apellidos);
        strcpy(persona.sexo, raizP->sexo);
        strcpy(persona.fechaservicio, raizP->fechaservicio);

        archivo.write(reinterpret_cast<const char*>(&persona), sizeof(persona));

        datos *temp = raizP;
        raizP = raizP->sig;
        delete temp;
    }

    archivo.close();
}

void liberarmemoria(datos *&raiz){
    while(raiz != NULL){
        datos *temp = raiz;
        raiz = raiz->sig;
        delete temp;
    }
}

void obtenerFecha(char* destino) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(destino, 11, "%d/%m/%Y", tm_info);
}



