#include<iostream>
#include<cstring>
#include<conio.h>

using namespace std;

void registraC(struct canales *&cabeza);
void agregaP(struct canales *&cabeza);
void consultar(struct canales *cabeza);
void elimcanal(struct canales *&cabeza);
void elimprog(struct canales *&cabeza);
void guiacanales(struct canales *cabeza);

struct canales{
    int num;
    char nombre[30];
     struct canales *sig;
     struct canales *ant;
     struct programas *prog;
};

struct programas{           //le deje coments
    int franjah;            //pa ver si el exnovio
    char nombre[30];        //aun se la come
    char clasificacion[20];
     struct programas *sig;
     struct programas *ant;
};

int main(){

    int opc;

    struct canales *cabeza = NULL;

    cout<<"\n\tBienvenido a la television"<<endl;

    do{

        cout<<"\nSeleccione una opcion"<<endl; 
        cout<<"\n1. Agregar canales a la parrilla"<<endl;  
        cout<<"2. Agregar programas a un canal"<<endl;
        cout<<"3. Consultar informacion de un canal"<<endl;
        cout<<"4. Eliminar canales de la guia"<<endl;
        cout<<"5. Eliminar toda la programacion de un canal"<<endl;
        cout<<"6. Mostrar guia de canales"<<endl;
        cout<<"7. Salir"<<endl;
        cout<<"\nOpcion: "; cin>>opc;

        switch(opc){
            case 1: cout<<"\n\n\tAgregar canales a la parrilla"<<endl; registraC(cabeza);  break;

            case 2: cout<<"\n\n\tAgregar programas a un canal"<<endl; 
            if (cabeza == NULL) {
                cout << "\nNo hay canales registrados" << endl;         //Verifica si no hay canales registrados
                } else {
                agregaP(cabeza);} break;

            case 3: cout<<"\n\n\tConsultar informacion de un canal"<<endl;
            if (cabeza == NULL) {
                cout << "\nNo hay canales registrados" << endl;
                } else {
                consultar(cabeza);} break; 

            case 4: cout<<"\n\n\tEliminar canales de la guia"<<endl;
            if (cabeza == NULL) {
                cout << "\nNo hay canales registrados" << endl;
                } else {
                elimcanal(cabeza);} break;

            case 5: cout<<"\n\n\tEliminar toda la programacion de un canal"<<endl;
            if (cabeza == NULL) {
                cout << "\nNo hay canales registrados" << endl;
                } else {
                elimprog(cabeza);} break; 

            case 6: cout<<"\n\n\tMostrar guia de canales"<<endl; 
            if (cabeza == NULL) {
                cout << "\nNo hay canales registrados" << endl;
                } else {
                guiacanales(cabeza);} break;

            case 7: cout<<"\nSaliendo, gracias por visitar..."<<endl; break;

            default: cout<<"\nOpcion invalida"<<endl; break;
        }

    }while(opc!=7);

    return 0; 
}

void registraC(struct canales *&cabeza){
    
    struct canales *nuevo;
    nuevo = new(struct canales);         //crea un nuevo espacio en memoria para el canal

    cout<<"\nIngrese el nombre del canal: "; cin.ignore(); cin.getline(nuevo->nombre, 30);
    cout<<"Ingrese el numero del canal: "; cin>>nuevo->num;             //se solicita la informacion del canal

    struct canales *temp = cabeza;

    if(cabeza == NULL){          //Si no hay ningun nodo en la lista
        cabeza = nuevo;          //El nuevo canal es la cabeza de la lista
        cabeza->sig = cabeza;    
        cabeza->ant = cabeza;    //se asigna a si mismo en sig y ant ya que es una lista circular
        cabeza->prog = NULL;     //Incializa la lista de programas vacia 
    
    } else {                      //Si ya hay nodos en la lista

        struct canales *verifi = cabeza;
        do{                      //se recorre la lista para verificar que no haya un canal con el mismo numero

            if(verifi->num == nuevo->num){      //si lo hay
                cout<<"\nYa hay un canal registrado con ese numero"<<endl;     
                delete nuevo;       //se libera memoria del nodo que estaba ingresando
                return;             //se retorna la menu
            }
            verifi = verifi->sig;

        }while(verifi != cabeza);
       
        if(nuevo->num < cabeza->num){     //si el num del nuevo canal es menor a el de la cabeza de la lista
            
            nuevo->ant = cabeza->ant;   
            nuevo->sig = cabeza;                  
            cabeza->ant->sig = nuevo;         //el nuevo canal se vuelve la cabeza de la lista 
            cabeza->ant = nuevo; 
            cabeza = nuevo;           
            nuevo->prog = NULL;       //incializa la lista de programas vacia 
       
        } else {                    //si el numero es mayor
                                    
            while(temp->sig != cabeza && temp->sig->num < nuevo->num){  //se va recorriendo la lista y busca canal por canal 
                temp = temp->sig;           //un canal donde el numero del nuevo canal sea mayor
                                            //y se ingresa 
            }                               
                                    
                                     
            nuevo->sig = temp->sig;    
            nuevo->ant = temp;
            nuevo->prog = NULL;      //la lista de programas está vacia
            temp->sig->ant = nuevo;
            temp->sig = nuevo;
        
        }
    }

    cout<<"\nRegistro exitoso"<<endl;
    
    int opc2;

    cout<<"\n¿Desea agregar un programa al canal?"<<endl;   
                cout<<"\n1. Si"<<endl;
                cout<<"2. No"<<endl;                            //Opcion para agregar programas 
                cout<<"\nElija una opcion: "; cin>>opc2;
                  if(opc2 == 1){
                     agregaP(cabeza);
                  };
}

void agregaP(struct canales *&cabeza){

    int canalB, opc;
    bool encontrado = false;    //para la verificacion de existencia
    
    struct canales *temp = cabeza;

    cout<<"\nIngrese el numero del canal al cual desea agregar el programa: "; cin>>canalB;

    do{                                    
        if(temp->num == canalB){     //recorre la lista de canales
            encontrado = true;       //se verifica si existe algun canal con el numero ingresado
            break;                   //si existe, rompe la ejecucion del do-while
        }
        temp = temp->sig;            
       
    }while(temp!=cabeza);

    if(encontrado == false){                     //si no existe 
        cout<<"\nCanal no encontrado"<<endl;       
        return;                                  //se retorna al menu
    }


    do{

    struct programas *nuevop;            
    nuevop = new(struct programas);      //crea espacion en memoria para un nuevo programa

    cout<<"\nIngrese el nombre del programa: "; cin.ignore(); cin.getline(nuevop->nombre, 30);
    cout<<"Ingrese la clasificacion del programa: "; cin.getline(nuevop->clasificacion, 20);
    cout<<"\nRecuerde que la duracion de cada programa es de 1 hora";                       
    cout<<"\nIngrese la hora de inicio del programa: "; cin>>nuevop->franjah;  //se solicita la informacion

    struct programas *verifi = temp->prog;

    while(verifi != NULL){                                  //recorre toda la lista
        if(verifi->franjah == nuevop->franjah){             //busca prog por prog si la hora ingresada ya fue registrada 
            cout<<"\nFranja horaria no disponible"<<endl;
            delete nuevop;         //si ya fue registrada, se libera el espacio en memoria de este nuevo prog
            return;               //se retorna al menu
        }
        verifi = verifi->sig;
    }

    if(temp->prog == NULL){        //Si no hay ningun prog en la lista
        temp->prog = nuevop;       //se establece la cabeza de la lista de prog en el canal
        nuevop->sig = NULL;        //Este prog se convierte en la cabeza de la lista
        nuevop->ant = NULL;        //Se le asigna el NULL a su ant y sig, ya que no es lista circular
   
    } else {                        //si ya hay progs en la lista                                 
                                         
        struct programas *tempP = temp->prog;
    
        if(nuevop->franjah < tempP->franjah){ //si la hora del nuevo prog es menor a la de la cabeza de la lista
            nuevop->ant = NULL;               //ant es NUll porque es la nueva cabeza
            nuevop->sig = tempP;              //este prog se convierte en la cabeza de la lista
            tempP->ant = nuevop;       
            temp->prog = nuevop;             //se cambia la cabeza de la lista de progs en el canal
            
        } else {    //si la hora del nuevo prog no es menor a la de la cabeza de la lista

        while(tempP->sig != NULL && tempP->sig->franjah < nuevop->franjah){ //se recorre toda la lista y busca prog por prog
            tempP = tempP->sig;   
        }
        
        if(tempP->sig == NULL){   //si se recorrio toda la lista, este prog se ingresa en la ultima posc
            tempP->sig = nuevop;
            nuevop->sig = NULL;   //como es el ultimo, su sig apunta a NULL
            nuevop->ant = tempP;
        } else {                              //si no se ha llegado al final de la lista
                nuevop->sig = tempP->sig;
                nuevop->ant = tempP;              //se enlaza en medio de dos programas
                tempP->sig->ant = nuevop;         //por ende hay que poner cuidado con el ant y el sig
                tempP->sig = nuevop;                         
        }
   }
}
    
    cout<<"\n¿Desea agregar mas programas?"<<endl;
    cout<<"\n1. Si"<<endl;                                
    cout<<"2. No"<<endl;                                      //opcion para agregar mas programas
    cout<<"\nElija una opcion: "; cin>>opc;   

    }while(opc!=2);    

    cout<<"\nPrograma agregado exitosamente"<<endl;
}

void consultar(struct canales *cabeza){
    char nombreB[30];
    int numB;
    int opc;

    struct canales *temp = cabeza;

    cout<<"\n¿Por que medio desea hacer la consulta?"<<endl;
    cout<<"\n1. Nombre del canal"<<endl;
    cout<<"2. Numero del canal"<<endl;
    cout<<"\nElija una opcion: "; cin>>opc;

    if(opc==1){
        cout<<"\nDigite el nombre del canal: "; cin.ignore(); cin.getline(nombreB, 30);
    } else {
        cout<<"\nDigite el numero del canal: "; cin>>numB;
    }
    
    do{  
            if((strcmp(temp->nombre, nombreB)==0) || (temp->num == numB)){
                cout<<"\nNombre del canal: "<<temp->nombre<<endl;
                cout<<"Numero: "<<temp->num<<endl;

                struct programas *prog = temp->prog;

                while(prog != NULL){

                    cout<<"\nProgramas: "<<endl;

                    cout<<"\nNombre del programa: "<<prog->nombre<<endl;
                    cout<<"Clasificacion: "<<prog->clasificacion<<endl;
                    cout<<"Franja Horaria: "<<prog->franjah<<":00"<<endl;
                    
                    prog = prog->sig;
                }
                return;
            } 
        
    temp = temp->sig;
    
    }while(temp!=cabeza);

    cout<<"\nCanal no encontrado"<<endl;
}

void elimcanal(struct canales *&cabeza){

    int numB;
    struct canales *temp = cabeza;

    cout<<"\nDigite el numero del canal a eliminar: "; cin>>numB;

    if(temp->sig == cabeza){   //si solo hay un nodo
       if(temp->num == numB){

        struct programas *tempP = temp->prog;
        while(tempP != NULL){                             
            struct programas *elim = tempP;
            tempP = tempP->sig;
            delete elim;
        }
        temp->prog = NULL;

        cout<<"\nEliminacion exitosa"<<endl;
        delete temp;
        cabeza = NULL;
        return;
    }
    
    cout<<"\nEl canal no fue encontrado"<<endl;
    return;
   }


   do{
    if(temp->num == numB){

        struct programas *tempP = temp->prog;
        while(tempP != NULL){
            struct programas *elim = tempP;     //elimina todos los programas
            tempP = tempP->sig;
            delete elim;
        }
        temp->prog = NULL;
        
        if(temp == cabeza){

            cabeza = temp->sig;
            cabeza->ant = temp->ant;
            temp->ant->sig = cabeza;

        } else {

            struct canales *elim = temp->ant;

            elim->sig = temp->sig;
            temp->sig->ant = elim;

        }

        cout<<"\nELiminacion exitosa"<<endl;
        delete temp;
        return;
    
    }
    temp = temp->sig;

   }while(temp!=cabeza);

   cout<<"\nCanal no encontrado"<<endl;
}

void elimprog(struct canales *&cabeza){

    int numB;
    struct canales *temp = cabeza;

    cout<<"\nDigite el numero del canal al cual eliminarle toda la programacion: "; cin>>numB;

    do{
        if(temp->num == numB){
            
            struct programas *tempP = temp->prog;
            
            if(tempP == NULL){
                cout<<"\nEste canal no tiene programas registrados"<<endl;
                return;
            }

            while(tempP != NULL){
                struct programas *elim = tempP;
                tempP = tempP->sig;
                delete elim;
            }
    
            temp->prog = NULL;
            cout<<"\nEliminacion exitosa"<<endl;
            return;

        } else {
            temp = temp->sig;
        }

    }while(temp!=cabeza);
    
    cout<<"\nCanal no encontrado"<<endl;
}
 
void guiacanales(struct canales *cabeza){

    struct canales *temp = cabeza;
    struct programas *tempP = temp->prog; 
    bool verifica = true;
 
    cout<<"\nGuía de canales"<<endl;
    cout<<"\n1. Flecha arriba y flecha abajo para moverse por los canales"<<endl;
    cout<<"2. Flecha izquierda y flecha derecha para moverse por los programas"<<endl;
    cout<<"3. Esc o Enter para volver"<<endl;

    cout<<"\n\nNombre del canal: "<<temp->nombre << endl;
    cout<<"Número: "<<temp->num << endl;
    

    int tecla = getch();

    while (tecla != 27 && tecla != 13) {

        switch (tecla) {

            case 72: // canal siguiente
                    temp = temp->sig; 
                    tempP = temp->prog; 

                    cout<<"\nNombre del canal: "<<temp->nombre<<endl;
                    cout<<"Número: "<<temp->num<<endl;
                    verifica = true;
                
                break;

            case 80: // canal anterior
                    temp = temp->ant; 
                    tempP = temp->prog; 
                    
                    cout<<"\nNombre del canal: "<<temp->nombre<<endl;
                    cout<<"Número: "<<temp->num<<endl;
                    verifica = true;
                
                break;

            case 75: // programa anterior
                    if (tempP && tempP->ant) {
                    tempP = tempP->ant;
                    cout<<"\nNombre del programa: "<<tempP->nombre<<endl;
                    cout<<"Clasificación: "<<tempP->clasificacion<<endl;
                    cout<<"Franja Horaria: "<<tempP->franjah<<":00"<<endl;
                    verifica = true;
                }
                break;

            case 77: // programa siguiente
            if (tempP && verifica == true) { 

                cout<<"\nNombre del programa: "<<tempP->nombre<<endl;
                cout<<"Clasificación: "<<tempP->clasificacion<<endl;  
                cout<<"Franja Horaria: "<<tempP->franjah<<":00"<<endl;
                
                if(tempP->sig != NULL){
                    tempP = tempP->sig; 
                } else {
                    verifica = false;
                }
                  
             }
            break;

            default: break;
        }

        tecla = getch();
    }
}
             