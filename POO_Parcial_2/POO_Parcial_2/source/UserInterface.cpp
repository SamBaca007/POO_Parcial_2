#include "UserInterface/UserInterface.h"

// ----------------------------------------------------------------------
// Implementacion de UserInterface (Respetando el estilo de documentacion)

UserInterface::UserInterface(std::shared_ptr<GestorInventario> gestor) {
  gestorInventario = gestor;
}

void UserInterface::iniciar() {
  int opcion = 0;
  do {
    mostrarMenuPrincipal();
    // Intentamos leer la opcion
    if (!(std::cin >> opcion)) {
      // Manejo de entrada no numerica
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      opcion = -1; // Fuerza un caso invalido
    }
    manejarOpcion(opcion);
  } while (opcion != 0);
}

void UserInterface::mostrarMenuPrincipal() {
  system("cls"); // Limpiar la pantalla
  std::cout << "===== SISTEMA DE PUNTO DE VENTA =====\n";
  std::cout << "1. Gestionar Inventario (CRUD)\n";
  std::cout << "2. Realizar Venta\n";
  std::cout << "3. Realizar Compra (Re-Surtir)\n";
  std::cout << "4. Mostrar Inventario Completo\n";
  std::cout << "0. Salir del Sistema\n";
  std::cout << "=====================================\n";
  std::cout << "Seleccione una opcion: ";
}

void UserInterface::manejarOpcion(int opcion) {
  switch (opcion) {
  case 1:
    menuGestionInventario();
    break;
  case 2:
    realizarVenta();
    break;
  case 3:
    realizarCompra();
    break;
  case 4:
    system("cls");
    gestorInventario->mostrarInventario();
    system("pause"); // Pausa hasta que el usuario presione una tecla
    break;
  case 0:
    std::cout << "Saliendo del sistema. Adios!\n";
    break;
  default:
    std::cout << "Opcion invalida. Intente de nuevo.\n";
    system("pause");
    break;
  }
}

// ----------------------------------------------------------------------
// Menu de Gestion de Inventario (CRUD)

void UserInterface::menuGestionInventario() {
  int opcion = 0;
  do {
    system("cls");
    std::cout << "===== GESTION DE INVENTARIO (CRUD) =====\n";
    std::cout << "1. Agregar Nuevo Producto\n";
    std::cout << "2. Editar Producto Existente\n";
    std::cout << "3. Eliminar Producto\n";
    std::cout << "0. Volver al Menu Principal\n";
    std::cout << "========================================\n";
    std::cout << "Seleccione una opcion: ";

    if (!(std::cin >> opcion)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      opcion = -1;
    }
    manejarGestionInventario(opcion);

  } while (opcion != 0);
}

void UserInterface::manejarGestionInventario(int opcion) {
  switch (opcion) {
  case 1: agregarProducto(); break;
  case 2: editarProducto(); break;
  case 3: eliminarProducto(); break;
  case 0: return; // Regresa al menu principal
  default:
    std::cout << "Opcion invalida. Intente de nuevo.\n";
    system("pause");
    break;
  }
}

// ----------------------------------------------------------------------
// Implementacion de las Acciones

void UserInterface::agregarProducto() {
  system("cls");
  std::string codigo, nombre;
  float precio;
  int cantidad;

  std::cout << "--- AGREGAR PRODUCTO ---\n";
  std::cout << "Codigo (ej. 1001): "; std::cin >> codigo;
  std::cout << "Nombre: ";
  std::cin.ignore(); // Limpiar el buffer despues de la lectura de codigo
  std::getline(std::cin, nombre); // Usamos getline para nombres con espacios
  std::cout << "Precio: $"; std::cin >> precio;
  std::cout << "Cantidad Inicial: "; std::cin >> cantidad;

  gestorInventario->agregarProducto(codigo, nombre, precio, cantidad);
  system("pause");
}

void UserInterface::editarProducto() {
  system("cls");
  std::string codigo, nuevoNombre;
  float nuevoPrecio;
  int nuevaCantidad;

  std::cout << "--- EDITAR PRODUCTO ---\n";
  std::cout << "Ingrese el Codigo del producto a editar: "; std::cin >> codigo;

  // Si no es necesario leer todos los campos, podrias tener metodos separados en GestorInventario
  // Pero para simplicidad, se pide toda la info de nuevo:
  std::cout << "Nuevo Nombre: ";
  std::cin.ignore();
  std::getline(std::cin, nuevoNombre);
  std::cout << "Nuevo Precio: $"; std::cin >> nuevoPrecio;
  std::cout << "Nueva Cantidad (Stock): "; std::cin >> nuevaCantidad;

  gestorInventario->editarProducto(codigo, nuevoNombre, nuevoPrecio, nuevaCantidad);
  system("pause");
}

void UserInterface::eliminarProducto() {
  system("cls");
  std::string codigo;

  std::cout << "--- ELIMINAR PRODUCTO ---\n";
  std::cout << "Ingrese el Codigo del producto a eliminar: "; std::cin >> codigo;

  gestorInventario->eliminarProducto(codigo);
  system("pause");
}

void UserInterface::realizarVenta() {
  system("cls");
  std::string codigo;
  int cantidad;

  std::cout << "--- REALIZAR VENTA ---\n";
  std::cout << "Codigo del Producto: "; std::cin >> codigo;
  std::cout << "Cantidad a Vender: "; std::cin >> cantidad;

  gestorInventario->realizarVenta(codigo, cantidad);
  system("pause");
}

void UserInterface::realizarCompra() {
  system("cls");
  std::string codigo;
  int cantidad;

  std::cout << "--- REALIZAR COMPRA (RE-SURTIR) ---\n";
  std::cout << "Codigo del Producto: "; std::cin >> codigo;
  std::cout << "Cantidad a Comprar: "; std::cin >> cantidad;

  gestorInventario->realizarCompra(codigo, cantidad);
  system("pause");
}