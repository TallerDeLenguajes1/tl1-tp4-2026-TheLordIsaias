#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Tarea{
    int TareaID; //Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo * crearListaVacia();
void crearTareas(Nodo *tareasPendientes);
Tarea crearTarea(int id, char *descripcion, int duracion);
Nodo * crearNodos(Tarea tarea);
void insertarNodo(Nodo **tareas, Nodo *nuevoNodo);


int main(){
    srand(time(NULL));
    Nodo *tareasPendientes;
    tareasPendientes = crearListaVacia();
    Nodo *tareasRealizadas;
    tareasRealizadas = crearListaVacia();
    crearTareas(tareasPendientes);
    return 0;
}

Nodo * crearListaVacia(){
    return NULL;
}

void crearTareas(Nodo *tareasPendientes){
    int bandera = 1;
    while (bandera){
        int opcion;
        do{
            printf("\n--- Creacion de tareas ---");
            printf("\n1. Cargar tarea\n0. Finalizar carga\n\nElige una opcion: ");
            scanf("%d", &opcion);
        } while (opcion < 0 || opcion > 1);
        if(opcion == 0){
            bandera = opcion;
        } else {
            int id;
            if(tareasPendientes == NULL){
                id = 1000;
            } else {
                Nodo *aux = tareasPendientes->Siguiente;
                id = aux->T.TareaID+1;
            }
            char descripcion[100];
            getchar();
            printf("\nIngrese una descripcion para la tarea (Max 100 caracteres): ");
            gets(descripcion);
            int duracion = rand() % 90 + 10;
            Tarea tarea = crearTarea(id, descripcion, duracion);
            Nodo *nuevoNodo = crearNodos(tarea);
            insertarNodo(&tareasPendientes, nuevoNodo);
            printf("\nTarea cargada con exito!\n");
        }
    }
}

Tarea crearTarea(int id, char *descripcion, int duracion){
    Tarea tarea;
    tarea.TareaID = id;
    strcpy(tarea.Descripcion, descripcion);
    tarea.Duracion = duracion;
    return tarea;
}

Nodo * crearNodos(Tarea tarea){
    Nodo *nuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    nuevoNodo->T = tarea;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

void insertarNodo(Nodo **tareas, Nodo *nuevoNodo){
    nuevoNodo->Siguiente = *tareas;
    *tareas = nuevoNodo;
}
