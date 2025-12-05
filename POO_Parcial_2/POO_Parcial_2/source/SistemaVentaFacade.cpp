#include "Facade/SistemaVentaFacade.h"
#include "ObserverPattern/AlertaStockBajo.h"
#include "UserInterface/UserInterface.h"

// -------------------------------------------------------------------------
// Implementación del Constructor Facade
// -------------------------------------------------------------------------

SistemaVentaFacade::SistemaVentaFacade() {
  // 1. Inicialización de los subsistemas de lógica de negocio

  // A. Inicializar el subsistema que NO tiene dependencias (GestorRegistro)
  gestorRegistro = std::make_shared<GestorRegistro>();

  // B. Inicializar el subsistema que REQUIERE la dependencia (GestorInventario)
  //    Ahora GestorInventario recibe el GestorRegistro que requiere.
  gestorInventario = std::make_shared<GestorInventario>(gestorRegistro);

  // 2. Configuración del Observer (Lógica movida desde main.cpp)
  int umbralStockBajo = 5;
  auto observadorAlerta = std::make_shared<AlertaStockBajo>(umbralStockBajo);
  gestorInventario->adjuntar(observadorAlerta);

  // 3. Carga inicial de datos (Lógica movida desde main.cpp)
  if (!gestorInventario->cargarProductosDesdeJson("InventarioTienda.json")) {
    // Manejo de error si el JSON no existe o está mal.
    std::cerr << "[FACADE ERROR] No se pudieron cargar los datos iniciales.\n";
    // Aquí podrías lanzar una excepción o salir si es crítico.
  }

  // 4. Inicialización de la Interfaz (inyectando solo lo necesario)
  // UserInterface necesita saber de GestorInventario y GestorRegistro
  ui = std::make_shared<UserInterface>(gestorInventario, gestorRegistro);

  std::cout << "[FACADE] Subsistemas inicializados con exito.\n";
}

// -------------------------------------------------------------------------
// Implementación del Método de Inicio
// -------------------------------------------------------------------------

void
SistemaVentaFacade::iniciarSistema() {
  std::cout << "[FACADE] Iniciando Interfaz de Usuario...\n";
  // El Facade simplemente delega el inicio del programa a la interfaz
  ui->iniciar();
}