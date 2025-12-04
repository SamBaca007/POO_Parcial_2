#include "Prerequisites.h"
#include "UserInterface/UserInterface.h"
#include <limits>    // Necesario para std::numeric_limits
#include <cstdlib>   // Necesario para system("cls") y system("pause")
#include <iomanip>   // Necesario para std::setprecision
// Incluimos las clases concretas para el shared_ptr en el constructor y el uso de la interfaz.
#include "Gasolinera/GestorGasolinera.h"
#include "Strategy/PagoEfectivo.h"
#include "Strategy/PagoCredito.h"
#include "Strategy/PagoDebito.h"


// ----------------------------------------------------------------------
// Constructor (Actualizado para incluir GestorGasolinera)
// ----------------------------------------------------------------------

/**
 * @brief Constructor de la clase UserInterface.
 * Inicializa los punteros compartidos a GestorInventario, GestorRegistro y crea GestorGasolinera.
 * @param gestorInv Puntero al gestor de inventario.
 * @param gestorReg Puntero al gestor de registros.
 */
UserInterface::
UserInterface(std::shared_ptr<GestorInventario> gestorInv,
  std::shared_ptr<GestorRegistro> gestorReg) {

  gestorInventario = gestorInv; // Inicializamos la referencia al inventario
  gestorRegistro = gestorReg;    // Inicializamos la referencia al registro
  // Inicialización del nuevo módulo de gasolinera (se gestiona internamente)
  gestorGasolinera = std::make_shared<GestorGasolinera>();
}


// ----------------------------------------------------------------------
// Logica del Ciclo Principal y Menús
// ----------------------------------------------------------------------

void
UserInterface::iniciar() {
  // @brief Inicia el ciclo principal del programa (Menu Loop).
  int opcion = 0;
  do {
    // Llama al menú principal y recoge la opción
    mostrarMenuPrincipal();

    // Manejo de la entrada: Intenta leer la opcion.
    if (!(std::cin >> opcion)) {
      // Manejo de errores para entrada no numérica.
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      opcion = -1; // Fuerza un caso inválido
    }

    // Llama al switch que maneja la opción
    manejarOpcion(opcion);

    if (opcion != 0) {
      system("pause"); // Solo pausa si no es salir
    }

  } while (opcion != 0);
}

void
UserInterface::mostrarMenuPrincipal() {
  // @brief Muestra las opciones principales del sistema.
  system("cls");
  std::cout << "===== SISTEMA DE PUNTO DE VENTA INTEGRADO =====\n";
  std::cout << "1. Agregar Nuevo Producto\n";
  std::cout << "2. Editar Producto Existente\n";
  std::cout << "3. Eliminar Producto\n";
  std::cout << "4. Realizar Venta (Inventario)\n";
  std::cout << "5. Realizar Compra (Re-Surtir)\n";
  std::cout << "6. Modulo de Gasolinera\n";
  std::cout << "7. Mostrar Inventario Completo\n";
  std::cout << "8. Ver Historial de Transacciones\n";
  std::cout << "0. Salir del Sistema\n";
  std::cout << "===============================================\n";
  std::cout << "Seleccione una opcion: ";
}

void
UserInterface::manejarOpcion(int opcion) {
  // @brief Procesa la opción seleccionada en el menú principal.
  switch (opcion) {
  case 1: agregarProducto(); break;
  case 2: editarProducto(); break;
  case 3: eliminarProducto(); break;
  case 4: realizarVenta(); break;
  case 5: realizarCompra(); break;
  case 6: moduloGasolinera(); break; // <-- NUEVO MODULO
  case 7:
    system("cls");
    gestorInventario->mostrarInventario();
    break; // No pausa aquí, la pausa está en iniciar()
  case 8: mostrarHistoriales(); break;
  case 0:
    std::cout << "Saliendo del sistema. Adios!\n";
    break;
  default:
    std::cout << "Opcion invalida. Intente de nuevo.\n";
    break; // No pausa aquí, la pausa está en iniciar()
  }
}


// ----------------------------------------------------------------------
// Menu de Historiales (Renombrado de mostrarHistoriales)
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
    case 1: gestorRegistro->mostrarHistorialVentas(); break;
    case 2: gestorRegistro->mostrarHistorialCompras(); break;
    case 0: return;
    default: std::cout << "Opcion invalida.\n"; break;
    }
    system("pause");

  } while (opcion != 0);
}

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
  std::cin.ignore();
  std::getline(std::cin, nombre);
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
  // La pausa es manejada en iniciar()
}

void
UserInterface::eliminarProducto() {
  // @brief Recoge el código y llama al gestor de inventario para eliminar.
  system("cls");
  std::string codigo;

  std::cout << "--- ELIMINAR PRODUCTO ---\n";
  std::cout << "Ingrese el Codigo del producto a eliminar: "; std::cin >> codigo;

  gestorInventario->eliminarProducto(codigo);
  // La pausa es manejada en iniciar()
}

// ----------------------------------------------------------------------
// Implementacion de las Acciones (CRUD, Venta, Compra)
// ----------------------------------------------------------------------

// *** NOTA: agregarProducto, editarProducto, eliminarProducto, realizarCompra ***
// *** Los métodos CRUD y realizarCompra son idénticos a los que ya tenías y funcionan.***

void
UserInterface::realizarVenta() {
  // @brief Recibe el código, cantidad, y la estrategia de pago, luego llama al gestor.
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

  std::shared_ptr<EstrategiaPago> estrategiaSeleccionada = nullptr;

  switch (opcionPago) {
  case 1: estrategiaSeleccionada = std::make_shared<PagoEfectivo>(); break;
  case 2: estrategiaSeleccionada = std::make_shared<PagoCredito>(); break;
  case 3: estrategiaSeleccionada = std::make_shared<PagoDebito>(); break;
  default:
    std::cout << "Opcion de pago invalida.\n";
    system("pause");
    return;
  }

  if (estrategiaSeleccionada) {
    gestorInventario->realizarVenta(codigo, cantidad, estrategiaSeleccionada);
  }
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
  // La pausa es manejada en iniciar()
}

// ----------------------------------------------------------------------
// Nuevo Modulo: Gasolinera
// ----------------------------------------------------------------------

void
UserInterface::moduloGasolinera() {
  system("cls");
  std::cout << "--- MODULO DE GASOLINERA ---\n";

  // 1. Mostrar tipos de combustible
  const auto& combustibles = gestorGasolinera->obtenerTiposCombustible();
  std::cout << "\nTIPOS DE COMBUSTIBLE DISPONIBLES:\n";
  for (const auto& c : combustibles) {
    std::cout << c.codigo << ". " << c.nombre << " ($" << std::fixed <<
    std::setprecision(2) << c.precioPorLitro << "/L)\n";
  }

  int codigoCombustible;
  float litrosACargar;
  float montoPagado;
  int opcionPago;

  // 2. Captura de datos
  std::cout << "\nSeleccione el codigo del combustible: ";
  if (!(std::cin >> codigoCombustible)) { /* Manejo de error */ return; }

  std::cout << "Litros a cargar: ";
  if (!(std::cin >> litrosACargar)) { /* Manejo de error */ return; }

  std::cout << "Monto exacto a pagar (para validar 'pago antes'): $";
  if (!(std::cin >> montoPagado)) { /* Manejo de error */ return; }

  // 3. Selección de Estrategia de Pago (Reutilizada del Patrón Strategy)
  std::cout << "\n--- METODO DE PAGO ---\n";
  std::cout << "1. Efectivo\n";
  std::cout << "2. Tarjeta de Credito\n";
  std::cout << "3. Tarjeta de Debito\n";
  std::cout << "Seleccione una opcion: ";
  if (!(std::cin >> opcionPago)) { /* Manejo de error */ return; }

  std::shared_ptr<EstrategiaPago> estrategiaSeleccionada = nullptr;

  switch (opcionPago) {
  case 1: estrategiaSeleccionada = std::make_shared<PagoEfectivo>(); break;
  case 2: estrategiaSeleccionada = std::make_shared<PagoCredito>(); break;
  case 3: estrategiaSeleccionada = std::make_shared<PagoDebito>(); break;
  default:
    std::cout << "Opcion de pago invalida.\n";
    system("pause");
    return;
  }

  // 4. Procesar Transacción
  if (estrategiaSeleccionada) {
    gestorGasolinera->procesarTransaccion(
      codigoCombustible,
      litrosACargar,
      montoPagado,
      estrategiaSeleccionada
    );
  }
}