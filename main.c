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
void crearTareas(Nodo **tareasPendientes);
Tarea crearTarea(int id, char *descripcion, int duracion);
Nodo * crearNodos(Tarea tarea);
void insertarNodo(Nodo **tareas, Nodo *nuevoNodo);
void mostrarTareas(Nodo *listaTareas);
void completarTarea(Nodo **tareasPendientes, Nodo **tareasRealizadas);
int menuPrincipal();
void buscarTarea(Nodo *tareasPendientes, Nodo *tareasRealizadas);
Nodo * nodoBuscadoPorID(Nodo *tareasPendientes, int idTarea);
Nodo * nodoBuscadoPorClave(Nodo *tareasPendientes, char *clave);
void mostrarTareaSingular(Tarea tarea, int lista);


int main(){
    srand(time(NULL));
    Nodo *tareasPendientes;
    tareasPendientes = crearListaVacia();
    Nodo *tareasRealizadas;
    tareasRealizadas = crearListaVacia();
    int opcionPrincipal = menuPrincipal();
    while(opcionPrincipal != 0){
        switch (opcionPrincipal){
        case 1:
            crearTareas(&tareasPendientes); // Punto 1
            break;
        case 2:
            if(tareasPendientes != NULL){
                mostrarTareas(tareasPendientes); // Punto 3
            } else {
                printf("\nNo se han cargado tareas. No hay nada que mostrar...");
            }
            break;
        case 3:
            if(tareasRealizadas != NULL){
                mostrarTareas(tareasRealizadas); // Punto 3
            } else {
                printf("\nNo se han completado tareas. No hay nada que mostrar...");
            }
            break;
        case 4:
            buscarTarea(tareasPendientes, tareasRealizadas); // Punto 4
            break;
        case 5:
            completarTarea(&tareasPendientes, &tareasRealizadas); // Punto 2
            break;
        default:
            break;
        }
        opcionPrincipal = menuPrincipal();
    }
    return 0;
}

Nodo * crearListaVacia(){
    return NULL;
}

void crearTareas(Nodo **tareasPendientes){
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
            if(*tareasPendientes == NULL){
                id = 1000;
            } else {
                Nodo *aux = *tareasPendientes;
                id = aux->T.TareaID + 1;
            }
            char descripcion[100];
            getchar();
            printf("\nIngrese una descripcion para la tarea (Max 100 caracteres): ");
            gets(descripcion);
            int duracion = rand() % 90 + 10;
            Tarea tarea = crearTarea(id, descripcion, duracion);
            Nodo *nuevoNodo = crearNodos(tarea);
            insertarNodo(tareasPendientes, nuevoNodo);
            printf("\nTarea cargada con exito!\n");
        }
    }
}

Tarea crearTarea(int id, char *descripcion, int duracion){
    Tarea tarea;
    tarea.TareaID = id;
    tarea.Descripcion = (char *) malloc(sizeof(char) * (strlen(descripcion) + 1));
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

int menuPrincipal(){
    int opcion;
    do{
        printf("\n\n\n---- MENU PRINCIPAL -----\n");
        printf("0. Salir\n1. Carga de tareas\n2. Consultar tareas pendientes\n3. Consultar tareas realizadas\n4. Buscar tarea\n5. Completar tareas\n\nElige una opcion (0-5): ");
        scanf("%d", &opcion);
    }while(opcion<0 || opcion>5);
    return opcion;

}

void mostrarTareas(Nodo *listaTareas){
    Nodo *aux = listaTareas;
    while(aux != NULL){
        printf("\n---------------\nID de la tarea: %d\nDescripcion de la tarea: %s\nDuracion de la tarea: %d", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
        aux = aux->Siguiente;
    }
}

void completarTarea(Nodo **tareasPendientes, Nodo **tareasRealizadas){
    mostrarTareas(*tareasPendientes);
    int idTarea;
    printf("\n\nIngrese el ID de la tarea a completar: ");
    scanf("%d", &idTarea);
    Nodo *buscado = nodoBuscadoPorID(*tareasPendientes, idTarea);
    if(buscado == NULL){
        printf("\nLa tarea no se encuentra en la lista de pendientes.");
    } else {
        if(*tareasPendientes == buscado){
            *tareasPendientes = buscado->Siguiente;
        } else {
            Nodo *aux = *tareasPendientes;
            while (aux != NULL && aux->Siguiente != buscado){
                aux = aux->Siguiente;
            }
            aux->Siguiente = buscado->Siguiente;
        }
        insertarNodo(tareasRealizadas, buscado);
    }
}

void buscarTarea(Nodo *tareasPendientes, Nodo *tareasRealizadas){
    int opcion;
    Nodo *buscado;
    do{
        printf("\n\n0. Salir\n1. Buscar tarea por ID.\n2. Buscar tarea por palabra clave\n\nElija una opcion: ");
        scanf("%d", &opcion);
    } while (opcion<0 || opcion > 2);
    switch (opcion){
    case 1:
        int idABuscar;
        printf("\n\n----- Busqueda por ID -----\nIntroduzca el ID: ");
        scanf("%d", &idABuscar);
        buscado = nodoBuscadoPorID(tareasPendientes, idABuscar);
        if(buscado == NULL){
            buscado = nodoBuscadoPorID(tareasRealizadas, idABuscar);
            if(buscado == NULL){
                printf("\n----ID BUSCADO NO ENCONTRADO EN NINGUNA LISTA----");
            } else {
                mostrarTareaSingular(buscado->T, 1); // 1 Significa que la tarea pertenece a realizadas
            }
        } else {
            mostrarTareaSingular(buscado->T, 0); // 0 Significa que la tarea pertenece a pendientes
        }
        break;
    case 2:
        char claveABuscar[20];
        printf("----- Busqueda por Palabra Clave -----\nIntroduzca la Clave: ");
        getchar();
        gets(claveABuscar);
        buscado = nodoBuscadoPorClave(tareasPendientes, claveABuscar);
        if(buscado == NULL){
            buscado = nodoBuscadoPorClave(tareasRealizadas, claveABuscar);
            if(buscado == NULL){
                printf("\n----CLAVE BUSCADA NO ENCONTRADA EN NINGUNA LISTA----");
            } else {
                mostrarTareaSingular(buscado->T, 1); // 1 Significa que la tarea pertenece a realizadas
            }
        } else {
            mostrarTareaSingular(buscado->T, 0); // 0 Significa que la tarea pertenece a pendientes
        }
        break;
    default:
        break;
    }
}

Nodo * nodoBuscadoPorID(Nodo *tareas, int idTarea){
    Nodo *aux = tareas;
    while (aux != NULL && aux->T.TareaID != idTarea){
        aux = aux->Siguiente;
    }
    if(aux == NULL){
        return NULL;
    } else{
        return aux;
    }
}

Nodo * nodoBuscadoPorClave(Nodo *tareasPendientes, char *clave){ // Solo devuelve la primera tarea que contenga el string de la clave. Consultar
    Nodo *aux = tareasPendientes;
    while (aux != NULL && strstr(aux->T.Descripcion, clave) == NULL){
        aux = aux->Siguiente;
    }
    if(aux == NULL){
        return NULL;
    } else{
        return aux;
    }
    return aux;
}

void mostrarTareaSingular(Tarea tarea, int lista){
    printf("\nID de Tarea: %d\nDuracion: %d\nDescripcion: ", tarea.TareaID, tarea.Duracion);
    puts(tarea.Descripcion);
    if(lista == 0){
        printf("Lista a la que pertenece: Pendientes");
    } else {
        printf("Lista a la que pertenece: Realizadas");
    }
}