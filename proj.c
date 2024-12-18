#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PRODUCTOS 50
#define MAX_TICKETS 100
#define MAX_LINEAS_TICKET 10

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
    LineaTicket lineas[MAX_LINEAS_TICKET];
    int totalLineas;
} Ticket;

Producto productos[MAX_PRODUCTOS];
Ticket tickets[MAX_TICKETS];

int altaProducto(int numProductos);
void bajaProducto(int *numProductos);
void modificarProducto(int numProductos);
void busquedaProducto(int numProductos);
void comprobarStock(int numProductos);
int crearTicket(int numTickets, int numProductos);
void buscarEliminarTicket(int *numTickets);

int altaProducto(int numProductos) {
    if (numProductos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos. Límite alcanzado.\n");
        return numProductos;
    }

    Producto producto;

    printf("Introduce el código del producto (3 caracteres): ");
    scanf("%s", producto.cod);

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(producto.cod, productos[i].cod) == 0) {
            printf("Código ya existente. Introduce otro.\n");
            return numProductos;
        }
    }

    printf("Introduce la descripción del producto: ");
    scanf("%s", producto.descripcion);

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

void bajaProducto(int *numProductos) {
    char codigo[4];
    printf("Introduce el código del producto a eliminar: ");
    scanf("%s", codigo);

    for (int i = 0; i < *numProductos; i++) {
        if (strcmp(codigo, productos[i].cod) == 0) {
            printf("Producto encontrado: %s - %s\n", productos[i].cod, productos[i].descripcion);
            printf("Eliminando producto...\n");

            for (int j = i; j < *numProductos - 1; j++) {
                productos[j] = productos[j + 1];
            }

            (*numProductos)--;
            printf("Producto eliminado correctamente.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}
void modificarProducto(int numProductos) {
    char codigo[4];
    printf("Introduce el código del producto a modificar: ");
    scanf("%s", codigo);

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(codigo, productos[i].cod) == 0) {
            printf("Modificando el producto %s - %s\n", productos[i].cod, productos[i].descripcion);

            printf("Nueva descripción: ");
            scanf("%s", productos[i].descripcion);

            printf("Nuevo stock: ");
            scanf("%d", &productos[i].stock);

            printf("Nuevo stock mínimo: ");
            scanf("%d", &productos[i].minStock);

            printf("Nuevo precio por unidad: ");
            scanf("%f", &productos[i].precioUnidad);

            printf("Nuevo descuento: ");
            scanf("%d", &productos[i].descuento);

            printf("Producto modificado correctamente.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}
int crearTicket(int numTickets, int numProductos) {
    if (numTickets >= MAX_TICKETS) {
        printf("No se pueden crear más tickets.\n");
        return numTickets;
    }

    Ticket ticket;
    ticket.cod = numTickets + 1;
    printf("Introduce la fecha (AAAAMMDD): ");
    scanf("%d", &ticket.fecha);
    printf("Introduce la hora (HHMM): ");
    scanf("%d", &ticket.hora);

    ticket.totalLineas = 0;
    ticket.importeTotal = 0.0;

    char continuar = 'S';
    while (continuar == 'S' && ticket.totalLineas < MAX_LINEAS_TICKET) {
        LineaTicket linea;
        printf("\nIntroduce el código del producto: ");
        scanf("%s", linea.cod);
        
        int encontrado = -1;
        for (int i = 0; i < numProductos; i++) {
            if (strcmp(linea.cod, productos[i].cod) == 0) {
                encontrado = i;
                break;
            }
        }
        
        if (encontrado == -1) {
            printf("Producto no encontrado.\n");
            continue;
        }

        printf("Producto: %s - Stock: %d - Precio: %.2f - Descuento: %d%%\n",
               productos[encontrado].descripcion, productos[encontrado].stock,
               productos[encontrado].precioUnidad, productos[encontrado].descuento);
        
        printf("Unidades a vender: ");
        scanf("%d", &linea.unidadesVendidas);
        if (linea.unidadesVendidas > productos[encontrado].stock || linea.unidadesVendidas <= 0) {
            printf("Stock insuficiente o unidades inválidas.\n");
            continue;
        }

        strcpy(linea.descripcion, productos[encontrado].descripcion);
        linea.precioUnidad = productos[encontrado].precioUnidad;
        linea.descuento = productos[encontrado].descuento;
        
        ticket.lineas[ticket.totalLineas++] = linea;
        ticket.importeTotal += linea.unidadesVendidas * linea.precioUnidad * (1 - linea.descuento / 100.0);
        productos[encontrado].stock -= linea.unidadesVendidas;

        printf("Línea añadida. ¿Desea agregar otra línea? (S/N): ");
        scanf(" %c", &continuar);
    }

    tickets[numTickets] = ticket;
    printf("Ticket %d creado. Importe total: %.2f\n", ticket.cod, ticket.importeTotal);
    return numTickets + 1;
}

void buscarEliminarTicket(int *numTickets) {
    int codigo;
    printf("Introduce el código del ticket: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *numTickets; i++) {
        if (tickets[i].cod == codigo) {
            printf("Ticket encontrado. Importe total: %.2f\n", tickets[i].importeTotal);
            char opcion;
            printf("Eliminar ticket? (S/N): ");
            scanf(" %c", &opcion);
            if (opcion == 'S') {
                for (int j = i; j < *numTickets - 1; j++) {
                    tickets[j] = tickets[j + 1];
                }
                (*numTickets)--;
                printf("Ticket eliminado.\n");
            }
            return;
        }
    }
    printf("Ticket no encontrado.\n");
}
void comprobarStock(int numProductos) {
    printf("Productos con stock crítico:\n");
    for (int i = 0; i < numProductos; i++) {
        if (productos[i].stock <= productos[i].minStock) {
            printf("Código: %s, Descripción: %s, Stock actual: %d\n",
                   productos[i].cod, productos[i].descripcion, productos[i].stock);
        }
    }
}



void busquedaProducto(int numProductos) {
    char codigo[4];
    printf("Introduce el código del producto: ");
    scanf("%s", codigo);

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(codigo, productos[i].cod) == 0) {
            printf("Código: %s\n", productos[i].cod);
            printf("Descripción: %s\n", productos[i].descripcion);
            printf("Stock actual: %d\n", productos[i].stock);
            printf("Stock mínimo: %d\n", productos[i].minStock);
            printf("Precio por unidad: %.2f\n", productos[i].precioUnidad);
            printf("Descuento: %d%%\n", productos[i].descuento);
            return;
        }
    }

    printf("Producto no encontrado.\n");
}


int main() {
    int opcion;
    int numProductos = 0, numTickets = 0;

    do {
        printf("\nMenú principal:\n");
        printf("1 - Alta producto\n");
        printf("2 - Baja producto\n");
        printf("3 - Crear ticket\n");
        printf("4 - Buscar/Eliminar ticket\n");
        printf("5 - Comprobar stock\n");
        printf("6-MOdificar\n");
                printf("7 - Busqueda\n");

        printf("0 - Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                numProductos = altaProducto(numProductos);
                break;
            case 2:
                bajaProducto(&numProductos);
                break;
            case 3:
                numTickets = crearTicket(numTickets, numProductos);
                break;
            case 4:
                buscarEliminarTicket(&numTickets);
                break;
            case 5:
                comprobarStock(numProductos);
                break;
            case 6:
                modificarProducto(numProductos);
                break;

            case 7:
            busquedaProducto(numProductos);
            break;

            
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 0);

    return 0;
}
