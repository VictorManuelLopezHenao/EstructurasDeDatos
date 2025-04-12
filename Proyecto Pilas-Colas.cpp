#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
using namespace std;

struct datos{
    int id, tel, edad;
    char nombres[30], apellidos[30], sexo[10];
    string fechaservicio;
    datos *sig;
};

void registrar(datos *&raiz, datos *&fondo, int edad);
void elimPersonaCola(datos *&raiz, datos *&fondo, int edad);
void sgteTurno(datos *&raiz, datos *&fondo, datos *&raizP);
void ListadoAtendidasPila(datos *&raizP);
void guardardatos(datos *&raizP);
void liberarmemoria(datos *&raiz);

int main(){

    int opc;
    int edad;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

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

            
            case 2: cout<<"\n\tTurno siguiente"<<endl; 
            
            while(true){
            if(raiz1 != NULL && count1 < 3){
                sgteTurno(raiz1, fondo1, raizP);
                count1++;

            } else if(raiz2 != NULL && count2 < 2) {
                sgteTurno(raiz2, fondo2, raizP);
                count2++;

            } else if(raiz3 != NULL && count3 < 1){             
                sgteTurno(raiz3, fondo3, raizP);
                count3++;

            } else {

                if(raiz1 == NULL && raiz2 == NULL && raiz3 == NULL){
                    cout<<"\nNo hay pacientes registrados"<<endl;
                    break;
                } else {
                    count1 = count2 = count3 = 0;
                }
            }
         } break;

            
         case 3: cout<<"\n\tEliminar persona de la cola"<<endl; 
            
            if(raiz1 == NULL && raiz2 == NULL && raiz3 == NULL){
                cout<<"\nNo hay pacientes registrados"<<endl;
                break;
            }

            cout<<"\nIngrese su edad: "; cin>>edad;
            
            if(edad > 55){
                elimPersonaCola(raiz1, fondo1, edad);

            } else if(edad <= 55 && edad > 40){
                elimPersonaCola(raiz2, fondo2, edad);

            } else if(edad <= 40 && edad > 0){
                elimPersonaCola(raiz3, fondo3, edad);

            } else {
                cout<<"\nEdad no valida"<<endl;
            } break;

        
            case 4: cout<<"\n\tListado de personas atendidas"<<endl; 
            
            if(raizP == NULL){
                cout<<"\nNinguna persona ha sido atendida"<<endl;
            } else {
            ListadoAtendidasPila(raizP);
             } break;


            case 5: cout<<"\nPrograma cerrado. Vuelve pronto..."<<endl; 
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
                opc = 6;
            }break;

            default: cout<<"\nOpcion no valida"<<endl; break;
        }

    }while(opc!=6);

    return 0;
}

void registrar(datos *&raiz, datos *&fondo, int edad){

    datos *nuevo = new(struct datos);

    cout<<"\nDigite la siguiente informacion: "<<endl;
    cout<<"\nNombres: "; cin.ignore(); cin.getline(nuevo->nombres, 30);
    cout<<"Apellidos: "; cin.getline(nuevo->apellidos, 30);
    cout<<"Sexo: "; cin.getline(nuevo->sexo, 11);
    cout<<"N° de identificacion: "; cin>>nuevo->id; 
    cout<<"N° de telefono: "; cin>>nuevo->tel;
    nuevo->edad = edad;
    
    nuevo->fechaservicio = fecha();

//verificacion de si hay alguien igual id
    //fecha
    nuevo->sig = NULL;

        if(raiz == NULL){
            raiz = nuevo;
            fondo = nuevo;
        } else {
            fondo->sig = nuevo;
            fondo = nuevo;
        }

}

void sgteTurno(datos *&raiz, datos *&fondo, datos *&raizP){
    
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

void elimPersonaCola(datos *&raiz, datos *&fondo, int edad){
   
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
    if(!encontrado){
        cout<<"\nNo se encontró la persona con ID: "<<idB<<endl;
    }

    raiz = auxR;
    fondo = auxF;
}

void ListadoAtendidasPila(datos *&raizP){

    datos *aux = NULL;

    cout<<"\nPersonas atendidas:\n";
    
    while(raizP != NULL){
       
        cout<<endl;
        cout<<raizP->nombres<<" "<<raizP->apellidos<<endl;
        cout<<"Id: "<<raizP->id;

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

void guardardatos(datos *&raizP){
   
    ofstream archivo("PersonasAtendidas.bin", ios::binary | ios::app);

    if(!archivo.is_open()) {
        cout<<"\nError al intentar abrir el archivo"<<endl;
        return;
    }

    while(raizP != NULL){

        archivo.write(reinterpret_cast<const char*>(raizP), sizeof(datos));

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

string fecha(){
    time_t t = time(nullptr);
    tm* ahora = localtime(&t);

    return to_string(ahora->tm_mday) + "/" +
           to_string(ahora->tm_mon + 1) + "/" +
           to_string(ahora->tm_year + 1900);
}