/*Manuel Alejandro Godinez Navarro 23300210
 Fernando Samael Alvarez Nuño 23300207
 Actividad integradora 3 TDS 2R
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura 
struct Mochila {
    int id;
    char nombre[50];
    float precio;
    int cantidad;
    char color[20];
    char descripcion[100];
};

// Estructura 
struct Venta {
    int id;
    char fecha[11]; // "YYYY-MM-DD"
    float total;
};

// Rutas de archivos 
const char *archivoProductos = "C:\\\\proyecto\\\\producto.dat";
const char *archivoVentas = "C:\\\\proyecto\\\\ventas.dat";

// Prototipos de funciones
void agregarProducto();
void mostrarProductos();
void modificarProducto();
void eliminarProducto();
void mostrarVentas();
void agregarVenta(int idProducto, int cantidad, float precio);

int main() {
    int opc;
    do {
    	system("cls");
        printf("1. Agregar producto\n");
        printf("2. Mostrar todos los productos\n");
        printf("3. Modificar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Mostrar ventas\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                agregarProducto();
                break;
            case 2:
                mostrarProductos();
                break;
            case 3:
                modificarProducto();
                break;
            case 4:
                eliminarProducto();
                break;
            case 5:
                mostrarVentas();
                break;
        } system("pause");
    } while (opc != 6);
}
//Funciones
void agregarProducto() {
    struct Mochila nuevaMochila;
    FILE *archivo;
    
    printf("\nIngrese el ID de la mochila: ");
    scanf("%d", &nuevaMochila.id);

    printf("Ingrese el nombre de la mochila: ");
    scanf(" %[^\n]", nuevaMochila.nombre);

    printf("Ingrese el precio de la mochila: ");
    scanf("%f", &nuevaMochila.precio);

    printf("Ingrese la cantidad de mochilas: ");
    scanf("%d", &nuevaMochila.cantidad);

    printf("Ingrese el color de la mochila: ");
    scanf(" %[^\n]", nuevaMochila.color);

    printf("Ingrese la descripcion de la mochila: ");
    scanf(" %[^\n]", nuevaMochila.descripcion);

    archivo = fopen(archivoProductos, "ab");
    if (!archivo) {
        printf("No se pudo abrir o crear el archivo de mochilas.\n");
        return;
    }

    fwrite(&nuevaMochila, sizeof(struct Mochila), 1, archivo);
    fclose(archivo);

    printf("Mochila agregada correctamente.\n");

    agregarVenta(nuevaMochila.id, nuevaMochila.cantidad, nuevaMochila.precio);
}

void agregarVenta(int idProducto, int cantidad, float precio) {
    struct Venta nuevaVenta;
    FILE *archivo;

    printf("\nIngrese la fecha de la venta (YYYY-MM-DD): ");
    scanf(" %[^\n]", nuevaVenta.fecha);

    nuevaVenta.id = idProducto; // Relacionamos la venta con el producto
    nuevaVenta.total = precio * cantidad;

    archivo = fopen(archivoVentas, "ab");
    if (!archivo) {
        printf("No se pudo abrir o crear el archivo de ventas.\n");
        return;
    }

    fwrite(&nuevaVenta, sizeof(struct Venta), 1, archivo);
    fclose(archivo);

    printf("Venta registrada correctamente. Total: %.2f\n", nuevaVenta.total);
}

void mostrarProductos() {
    struct Mochila mochila;
    FILE *archivo = fopen(archivoProductos, "rb");

    if (!archivo) {
        printf("No se encontraron mochilas registradas.\n");
        return;
    }

    printf("\n--- Lista de Mochilas ---\n");
    while (fread(&mochila, sizeof(struct Mochila), 1, archivo)) {
        printf("ID: %d\n", mochila.id);
        printf("Nombre: %s\n", mochila.nombre);
        printf("Precio: %.2f\n", mochila.precio);
        printf("Cantidad: %d\n", mochila.cantidad);
        printf("Color: %s\n", mochila.color);
        printf("Descripción: %s\n", mochila.descripcion);
        printf("-------------------------\n");
    }

    fclose(archivo);
}

void modificarProducto() {
    struct Mochila mochila;
    FILE *archivo, *archivoTemporal;
    int idBuscado, encontrado = 0;

    printf("\nIngrese el ID de la mochila a modificar: ");
    scanf("%d", &idBuscado);

    archivo = fopen(archivoProductos, "rb");
    archivoTemporal = fopen("C:\\\\proyecto\\\\temp.dat", "wb");

    if (!archivo || !archivoTemporal) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    while (fread(&mochila, sizeof(struct Mochila), 1, archivo)) {
        if (mochila.id == idBuscado) {
            encontrado = 1;

            printf("Ingrese el nuevo nombre de la mochila: ");
            scanf(" %[^\n]", mochila.nombre);

            printf("Ingrese el nuevo precio de la mochila: ");
            scanf("%f", &mochila.precio);

            printf("Ingrese la nueva cantidad de mochilas: ");
            scanf("%d", &mochila.cantidad);

            printf("Ingrese el nuevo color de la mochila: ");
            scanf(" %[^\n]", mochila.color);

            printf("Ingrese la nueva descripción de la mochila: ");
            scanf(" %[^\n]", mochila.descripcion);
        }

        fwrite(&mochila, sizeof(struct Mochila), 1, archivoTemporal);
    }

    fclose(archivo);
    fclose(archivoTemporal);

    if (encontrado) {
        remove(archivoProductos);
        rename("C:\\\\proyecto\\\\temp.dat", archivoProductos);
        printf("Mochila modificada correctamente.\n");
    } else {
        printf("Mochila con ID %d no encontrada.\n", idBuscado);
    }
}

void eliminarProducto() {
    struct Mochila mochila;
    FILE *archivo, *archivoTemporal;
    int idBuscado, encontrado = 0;

    printf("\nIngrese el ID de la mochila a eliminar: ");
    scanf("%d", &idBuscado);

    archivo = fopen(archivoProductos, "rb");
    archivoTemporal = fopen("C:\\\\proyecto\\\\temp.dat", "wb");

    if (!archivo || !archivoTemporal) {
        printf("Error al abrir los archivos.\n");
        return;
    }

    while (fread(&mochila, sizeof(struct Mochila), 1, archivo)) {
        if (mochila.id == idBuscado) {
            encontrado = 1;
        } else {
            fwrite(&mochila, sizeof(struct Mochila), 1, archivoTemporal);
        }
    }

    fclose(archivo);
    fclose(archivoTemporal);

    if (encontrado) {
        remove(archivoProductos);
        rename("C:\\\\proyecto\\\\temp.dat", archivoProductos);
        printf("Mochila eliminada correctamente.\n");
    } else {
        printf("Mochila con ID %d no encontrada.\n", idBuscado);
    }
}

void mostrarVentas() {
    struct Venta venta;
    FILE *archivo = fopen(archivoVentas, "rb");

    if (!archivo) {
        printf("No se encontraron registros de ventas.\n");
        return;
    }

    printf("\n--- Lista de Ventas ---\n");
    while (fread(&venta, sizeof(struct Venta), 1, archivo)) {
        printf("ID de Venta: %d\n", venta.id);
        printf("Fecha: %s\n", venta.fecha);
        printf("Total: $%.2f\n", venta.total);
        printf("-----------------------\n");
    }

    fclose(archivo);
}

