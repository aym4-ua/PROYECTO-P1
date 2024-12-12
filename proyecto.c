#include <stdio.h>
#include <stdbool.h>
#include<string.h>
#define MAX_PRODUCTOS 50
#define MAX_TICKETS 100

typedef struct {
    char cod[4];
    char descripcion[30];
    int stock;
    int minStock;
    float precioUnidad;
    int descuento;
} Producto;


typedef struct {
    char cod[4];
    char descripcion[30];
    int unidadesVendidas;
    float precioUnidad;
    int descuento;
} LineaTicket;


typedef struct {
    int cod;
    int fecha;
    int hora;
    float importeTotal;
    LineaTicket lineas[];
} Ticket;



Producto productos[MAX_PRODUCTOS];

int altaProducto(int numProductos) {
    if (numProductos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos. Límite alcanzado.\n");
        return numProductos;
    }

    Producto producto;

    printf("Introduce el código del producto: ");
    scanf("%s", producto.cod);

    
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(producto.cod, productos[i].cod) == 0) {
            printf("Código ya existente. Introduce otro.\n");
            return numProductos;
        }
    }

    printf("Introduce la descripción del producto: ");
    scanf("%s", producto.descripcion);

   
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(producto.descripcion, productos[i].descripcion) == 0) {
            printf("Descripción ya existente. Introduce otra.\n");
            return numProductos;
        }
    }

    printf("Introduce el stock del producto: ");
    scanf("%d", &producto.stock);

    printf("Introduce el stock mínimo del producto: ");
    scanf("%d", &producto.minStock);

    printf("Introduce el precio por unidad del producto: ");
    scanf("%f", &producto.precioUnidad);

    printf("Introduce el descuento aplicado al producto: ");
    scanf("%d", &producto.descuento);

   
    productos[numProductos] = producto;
    numProductos++; 

    printf("Producto añadido correctamente.\n");
    return numProductos;
}


void bajaProducto(int numProductos) {
    
    Producto producto;
    char confirmacionBaja;
    bool productoExiste = false;
    
    printf("Introduce el código del producto: ");
    scanf("%s",producto.cod);

    for (int i = 0; i < MAX_PRODUCTOS; i++) {

        if (producto.cod == productos[i].cod) {

            printf("Datos del producto:\n");
            printf("Código: %s\n",producto.cod);
            printf("Descripción: %s\n",producto.descripcion);
            printf("Stock: %d\n",producto.stock);
            printf("Stock mínimo: %d\n",producto.minStock);
            printf("Precio por unidad: %.2f\n",producto.precioUnidad);
            printf("Descuento del producto (en porcentaje): %d\n",producto.descuento);

            printf("¿Seguro que quieres dar este producto de baja?\n");
            printf("S/s/7 = Sí\n");
            printf("Cualquier otra tecla = No\n");
            printf("Elección: ");
            scanf("%c",&confirmacionBaja);

            productoExiste = true;

            if (confirmacionBaja == 'S' || confirmacionBaja == 's' || confirmacionBaja == '7') {

                for (int j = i; j < numProductos - 1; j++) {

                    productos[j] = productos[j + 1];

                }

                numProductos--;
                
                printf("Producto eliminado\n");

            } else {

                printf("El producto no ha sido eliminado\n");

            }

        }
        
    }

    if (!productoExiste) {

        printf("El codigo introducido no corresponde a ningún producto existente\n");

    }
        
}

void modificarProducto() {

    Producto producto;
    bool productoExiste = false;

    printf("Introduce el código de un producto: ");
    scanf("%s",producto.cod);

    for (int i = 0; i < MAX_PRODUCTOS; i++) {

        if (producto.cod == productos[i].cod) {

            printf("Datos del producto:\n");
            printf("Código: %s\n",producto.cod);
            printf("Descripción: %s\n",producto.descripcion);
            printf("Stock: %d\n",producto.stock);
            printf("Stock mínimo: %d\n",producto.minStock);
            printf("Precio por unidad: %.2f\n",producto.precioUnidad);
            printf("Descuento del producto (en porcentaje): %d\n",producto.descuento);

            productoExiste = true;

            printf("Modifica los datos del producto:\n");

            printf("Nueva descripción: ");
            scanf("%s",producto.descripcion);

            for (int i = 0; i < MAX_PRODUCTOS; i++) {

                if (producto.descripcion == productos[i].descripcion) {

                    printf("Descripción ya existente, introduce otra: ");
                    scanf("%s",producto.descripcion);

                }
                
            }

            printf("Nuevo stock: ");
            scanf("%d",&producto.stock);

            printf("Nuevo stock mínimo: ");
            scanf("%d",&producto.minStock);

            printf("Nuevo precio por unidad: ");
            scanf("%f",&producto.precioUnidad);

            printf("Nuevo descuento aplicado: ");
            scanf("%d",&producto.descuento);

        }
        
    }

    if (!productoExiste) {

        printf("El codigo introducido no corresponde a ningún producto existente\n");

    }

}

void busquedaProducto() {

    Producto producto;
    bool productoExiste = false;
    char cod[4];
    printf("Introduce el código de un producto: ");
    scanf("%s",cod);

    for (int i = 0; i < MAX_PRODUCTOS; i++) {

        if (cod == productos[i].cod) {

            printf("Datos del producto:\n");
            printf("Código: %s\n",producto.cod);
            printf("Descripción: %s\n",producto.descripcion);
            printf("Stock: %d\n",producto.stock);
            printf("Stock mínimo: %d\n",producto.minStock);
            printf("Precio por unidad: %.2f\n",producto.precioUnidad);
            printf("Descuento del producto (en porcentaje): %d\n",producto.descuento);

            productoExiste = true;

        }
        
    }

    if (!productoExiste) {

        printf("El codigo introducido no corresponde a ningún producto existente\n");

    }

}

void crearnuevoticket(Ticket tickets[], int *numTickets) {
    if (*numTickets >= MAX_TICKETS) {
        printf("No se pueden crear más tickets. Límite alcanzado.\n");
        return;
    }

    Ticket ticket;
    LineaTicket lineasTicket[10];
    int totalLineas = 0;
    char confirmacion, respuesta;
    float importeTotal = 0.0;

    printf("Introduce el código del ticket: ");
    scanf("%d", &ticket.cod);
    printf("Introduce la fecha (AAAAMMDD): ");
    scanf("%d", &ticket.fecha);
    printf("Introduce la hora (HHMM): ");
    scanf("%d", &ticket.hora);

    do {
        char codProducto[4];
        printf("Introduce el código del producto: ");
        scanf("%s", codProducto);

        int productoIndex = -1;
        for (int i = 0; i < MAX_PRODUCTOS; i++) {
            if (strcmp(codProducto, productos[i].cod) == 0) {
                productoIndex = i;
                break;
            }
        }

        if (productoIndex == -1) {
            printf("Producto no encontrado. Intenta de nuevo.\n");
            continue;
        }

        Producto producto = productos[productoIndex];
        int unidadesVendidas;

        do {
            printf("Introduce el número de unidades a vender: ");
            scanf("%d", &unidadesVendidas);
            if (unidadesVendidas > producto.stock) {
                printf("Error: No hay suficiente stock. Stock disponible: %d\n", producto.stock);
            }
        } while (unidadesVendidas > producto.stock);

        LineaTicket linea;
        strcpy(linea.cod, producto.cod);
        strcpy(linea.descripcion, producto.descripcion);
        linea.unidadesVendidas = unidadesVendidas;
        linea.precioUnidad = producto.precioUnidad;
        linea.descuento = producto.descuento;

        float precioConDescuento = linea.precioUnidad * (1 - linea.descuento / 100.0);
        importeTotal += precioConDescuento * linea.unidadesVendidas;

        printf("Línea añadida:\n");
        printf("Descripción: %s\n", linea.descripcion);
        printf("Unidades: %d\n", linea.unidadesVendidas);
        printf("Precio con descuento: %.2f\n", precioConDescuento);

        lineasTicket[totalLineas++] = linea;
        productos[productoIndex].stock -= unidadesVendidas;

        if (totalLineas < 10) {
            printf("¿Desea añadir otra línea? (S/N): ");
            scanf(" %c", &respuesta);
        } else {
            printf("Máximo de líneas alcanzado.\n");
            respuesta = 'N';
        }
    } while ((respuesta == 'S' || respuesta == 's') && totalLineas < 10);

    printf("¿Confirmar creación del ticket? (S/N): ");
    scanf(" %c", &confirmacion);

    if (confirmacion == 'S' || confirmacion == 's') {
        ticket.importeTotal = importeTotal;

        tickets[*numTickets] = ticket; 
        (*numTickets)++; 
    } else {
        printf("Creación del ticket cancelada.\n");
    }
}



















void buscarOeliminarTicket(Ticket tickets[], int *numTickets) {
    if (*numTickets == 0) {
        printf("No hay tickets registrados.\n");
        return;
    }

    int codTicket;
    printf("Introduce el código del ticket que deseas buscar/eliminar: ");
    scanf("%d", &codTicket);

    int index = -1;
    for (int i = 0; i < *numTickets; i++) {
        if (tickets[i].cod == codTicket) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Ticket no encontrado.\n");
        return;
    }

    
    Ticket ticket = tickets[index];
    printf("\nInformación del ticket encontrado:\n");
    printf("--------------------------------------\n");
    printf("Código del ticket: %d\n", ticket.cod);
    printf("Fecha: %d\n", ticket.fecha);
    printf("Hora: %d\n", ticket.hora);
    printf("Importe total: %.2f\n", ticket.importeTotal);
    printf("--------------------------------------\n");

    char opcion;
    printf("¿Qué deseas hacer con este ticket?\n");
    printf("M - Volver al menú principal\n");
    printf("E - Eliminar el ticket\n");
    printf("Opción: ");
    scanf(" %c", &opcion); 
    if (opcion == 'E' || opcion == 'e') {
        for (int i = index; i < *numTickets - 1; i++) {
            tickets[i] = tickets[i + 1];
        }
        (*numTickets)--; 
        printf("Ticket eliminado correctamente.\n");
    } else if (opcion == 'M' || opcion == 'm') {
        printf("Volviendo al menú principal.\n");
    } else {
        printf("Opción no válida. Volviendo al menú principal.\n");
    }
}



void comprobarStock(Producto productos[], int numProductos) {
    printf("Productos con stock crítico:\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < numProductos; i++) {
        if (productos[i].stock <= productos[i].minStock) {
            printf("Código: %s\n", productos[i].cod);
            printf("Descripción: %s\n", productos[i].descripcion);
            printf("Stock actual: %d\n", productos[i].stock);
            printf("Stock mínimo: %d\n", productos[i].minStock);
            printf("Precio por unidad: %.2f\n", productos[i].precioUnidad);
            printf("-----------------------------------------\n");
        }
    }
}

int main() {
    int opcion;
    int numProductos = 0;          
    int numTickets = 0;            
    Ticket tickets[MAX_TICKETS];   

    do {
        printf("\nMenú principal:\n");
        printf("1 - Dar de alta un producto\n");
        printf("2 - Dar de baja un producto\n");
        printf("3 - Modificar la información de un producto\n");
        printf("4 - Buscar la información de un producto\n");
        printf("5 - Crear un ticket\n");
        printf("6 - Buscar/eliminar un ticket\n");
        printf("7 - Comprobar stock\n");
        printf("0 - Salir\n");
        printf("Opción elegida: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                numProductos = altaProducto(numProductos);
                break;
            case 2:
                bajaProducto(numProductos);
                break;
            case 3:
                modificarProducto();
                break;
            case 4:
                busquedaProducto();
                break;
            case 5:
                crearnuevoticket(tickets, &numTickets);
                break;
            case 6:
                buscarOeliminarTicket(tickets, &numTickets);
                break;
            case 7:
                comprobarStock(productos, numProductos);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intenta de nuevo.\n");
        }

    } while (opcion != 0);

    return 0;
}

