#include "UserInterface/UserInterface.h"
#include <limits> // Necesario para std::numeric_limits
#include <cstdlib> // Necesario para system("cls") y system("pause")

/**
 * @brief Constructor de la clase UserInterface.
 * Inicializa los punteros compartidos a GestorInventario y GestorRegistro.
 * @param gestorInv Puntero al gestor de inventario.
 * @param gestorReg Puntero al gestor de registros.
 */
UserInterface::
UserInterface(std::shared_ptr<GestorInventario> gestorInv,
  std::shared_ptr<GestorRegistro> gestorReg) {
  gestorInventario = gestorInv; // Inicializamos la referencia al inventario
  gestorRegistro = gestorReg;   // Inicializamos la referencia al registro
}

// ----------------------------------------------------------------------
// Logica del Ciclo Principal y Menús
// ----------------------------------------------------------------------

void
UserInterface::iniciar() {
  // @brief Inicia el ciclo principal del programa (Menu Loop).
  int opcion = 0;
  do {
    mostrarMenuPrincipal();

    // Manejo de la entrada: Intenta leer la opcion.
    if (!(std::cin >> opcion)) {
      // Manejo de errores para entrada no numérica (e.g., el usuario escribe letras).
      std::cin.clear(); // Limpia los indicadores de error del flujo.
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada restante.
      opcion = -1; // Fuerza un caso inválido para que el switch lo maneje.
    }
    manejarOpcion(opcion);
  } while (opcion != 0);
}

void
UserInterface::mostrarMenuPrincipal() {
  // @brief Muestra las opciones principales del sistema.
  system("cls"); // Limpia la consola (comando específico de Windows, cambiar a "clear" en Linux/macOS).
  std::cout << "===== SISTEMA DE PUNTO DE VENTA =====\n";
  std::cout << "1. Gestionar Inventario (CRUD)\n";
  std::cout << "2. Realizar Venta\n";
  std::cout << "3. Realizar Compra (Re-Surtir)\n";
  std::cout << "4. Mostrar Inventario Completo\n";
  std::cout << "5. Ver Historial de Transacciones\n";
  std::cout << "0. Salir del Sistema\n";
  std::cout << "=====================================\n";
  std::cout << "Seleccione una opcion: ";
}

void
UserInterface::manejarOpcion(int opcion) {
  // @brief Procesa la opción seleccionada en el menú principal.
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
    gestorInventario->mostrarInventario(); // Llama a la lógica de negocio.
    system("pause"); // Espera la acción del usuario antes de volver al menú.
    break;
  case 5:
    mostrarHistoriales();
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
// ----------------------------------------------------------------------

void
UserInterface::menuGestionInventario() {
  // @brief Muestra y gestiona el sub-menu de operaciones CRUD.
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

    // Manejo de la entrada no numérica.
    if (!(std::cin >> opcion)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      opcion = -1;
    }
    manejarGestionInventario(opcion);

  } while (opcion != 0);
}

void
UserInterface::manejarGestionInventario(int opcion) {
  // @brief Procesa la opción seleccionada en el menú CRUD.
  switch (opcion) {
  case 1: agregarProducto(); break;
  case 2: editarProducto(); break;
  case 3: eliminarProducto(); break;
  case 0: return; // Regresa al ciclo do-while, que sale.
  default:
    std::cout << "Opcion invalida. Intente de nuevo.\n";
    system("pause");
    break;
  }
}

// ----------------------------------------------------------------------
// Menu de Historiales
// ----------------------------------------------------------------------

void
UserInterface::mostrarHistoriales() {
  // @brief Muestra el sub-menu para elegir entre historial de ventas y compras.
  int opcion = 0;
  do {
    system("cls");
    std::cout << "===== VER HISTORIALES =====\n";
    std::cout << "1. Ver Historial de Ventas\n";
    std::cout << "2. Ver Historial de Compras\n";
    std::cout << "0. Volver al Menu Principal\n";
    std::cout << "===========================\n";
    std::cout << "Seleccione una opcion: ";

    if (!(std::cin >> opcion)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      opcion = -1;
    }

    system("cls");
    switch (opcion) {
    case 1: gestorRegistro->mostrarHistorialVentas(); break; // Llama a la lógica de GestorRegistro.
    case 2: gestorRegistro->mostrarHistorialCompras(); break; // Llama a la lógica de GestorRegistro.
    case 0: return;
    default: std::cout << "Opcion invalida.\n"; break;
    }
    system("pause");

  } while (opcion != 0);
}


// ----------------------------------------------------------------------
// Implementacion de las Acciones (CRUD, Venta, Compra)
// ----------------------------------------------------------------------

void
UserInterface::agregarProducto() {
  // @brief Recoge los datos del nuevo producto y llama al gestor de inventario.
  system("cls");
  std::string codigo, nombre;
  float precio;
  int cantidad;

  std::cout << "--- AGREGAR PRODUCTO ---\n";
  std::cout << "Codigo (ej. 1001): "; std::cin >> codigo;
  std::cout << "Nombre: ";
  std::cin.ignore(); // Limpiar el buffer después de la lectura de código (cin >> string).
  std::getline(std::cin, nombre); // Usamos getline para nombres con espacios.
  std::cout << "Precio: $"; std::cin >> precio;
  std::cout << "Cantidad Inicial: "; std::cin >> cantidad;

  gestorInventario->agregarProducto(codigo, nombre, precio, cantidad);
  system("pause");
}

void
UserInterface::editarProducto() {
  // @brief Recoge los datos del producto a editar y llama al gestor de inventario.
  system("cls");
  std::string codigo, nuevoNombre;
  float nuevoPrecio;
  int nuevaCantidad;

  std::cout << "--- EDITAR PRODUCTO ---\n";
  std::cout << "Ingrese el Codigo del producto a editar: "; std::cin >> codigo;

  // Se solicita toda la información de nuevo para actualizar.
  std::cout << "Nuevo Nombre: ";
  std::cin.ignore();
  std::getline(std::cin, nuevoNombre);
  std::cout << "Nuevo Precio: $"; std::cin >> nuevoPrecio;
  std::cout << "Nueva Cantidad (Stock): "; std::cin >> nuevaCantidad;

  gestorInventario->editarProducto(codigo, nuevoNombre, nuevoPrecio, nuevaCantidad);
  system("pause");
}

void
UserInterface::eliminarProducto() {
  // @brief Recoge el código y llama al gestor de inventario para eliminar.
  system("cls");
  std::string codigo;

  std::cout << "--- ELIMINAR PRODUCTO ---\n";
  std::cout << "Ingrese el Codigo del producto a eliminar: "; std::cin >> codigo;

  gestorInventario->eliminarProducto(codigo);
  system("pause");
}

void
UserInterface::realizarVenta() {
  system("cls");
  std::string codigo;
  int cantidad;
  int opcionPago;

  std::cout << "--- REALIZAR VENTA ---\n";
  std::cout << "Codigo del Producto: "; std::cin >> codigo;
  std::cout << "Cantidad a Vender: "; std::cin >> cantidad;

  std::cout << "\n--- METODO DE PAGO ---\n";
  std::cout << "1. Efectivo\n";
  std::cout << "2. Tarjeta de Credito\n";
  std::cout << "3. Tarjeta de Debito\n";
  std::cout << "Seleccione una opcion: ";

  if (!(std::cin >> opcionPago)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Error: Entrada invalida.\n";
    system("pause");
    return;
  }

  // Puntero que será nuestra Estrategia
  std::shared_ptr<EstrategiaPago> estrategiaSeleccionada = nullptr;

  switch (opcionPago) {
  case 1:
    // Patrón Strategy: Se crea la estrategia concreta de Efectivo.
    estrategiaSeleccionada = std::make_shared<PagoEfectivo>();
    break;
  case 2:
    // Patrón Strategy: Se crea la estrategia concreta de Crédito.
    estrategiaSeleccionada = std::make_shared<PagoCredito>();
    break;
  case 3:
    // Patrón Strategy: Se crea la estrategia concreta de Débito.
    estrategiaSeleccionada = std::make_shared<PagoDebito>();
    break;
  default:
    std::cout << "Opcion de pago invalida.\n";
    system("pause");
    return;
  }

  // Llama al gestor inyectando la Estrategia (Strategy Pattern en acción)
  if (estrategiaSeleccionada) {
    gestorInventario->realizarVenta(codigo, cantidad, estrategiaSeleccionada);
  }

  system("pause");
}

void
UserInterface::realizarCompra() {
  // @brief Recoge los datos de la compra/re-surtido y llama a la lógica transaccional.
  system("cls");
  std::string codigo;
  int cantidad;

  std::cout << "--- REALIZAR COMPRA (RE-SURTIR) ---\n";
  std::cout << "Codigo del Producto: "; std::cin >> codigo;
  std::cout << "Cantidad a Comprar: "; std::cin >> cantidad;

  gestorInventario->realizarCompra(codigo, cantidad);
  system("pause");
}