#pragma once
#include "Prerequisites.h"
#include "GestorInventario.h"
#include "Gasolinera/GestorGasolinera.h"
#include "Register/GestorRegistro.h"
#include "UserInterface/UserInterface.h"

// -------------------------------------------------------------------------
// Clase: SistemaVentaFacade (Patrón Fachada)
// -------------------------------------------------------------------------
/**
 * @brief Proporciona una interfaz simplificada (Fachada) al subsistema de ventas.
 * Encapsula la inicialización y la dependencia de múltiples subsistemas.
 */
class
SistemaVentaFacade {
public:
  /**
   * @brief Constructor que inicializa todos los subsistemas internos.
   */
  SistemaVentaFacade();

  /**
   * @brief Inicia el ciclo principal del sistema, delegando la tarea a la interfaz.
   */
  void
  iniciarSistema();

private:
  // Referencias a los subsistemas que componen el sistema
  std::shared_ptr<GestorInventario> gestorInventario;
  std::shared_ptr<GestorGasolinera> gestorGasolinera; // Gasolinera no es estrictamente parte del Facade, pero se inicializa aquí.
  std::shared_ptr<GestorRegistro> gestorRegistro;

  // El Facade también inicializará y mantendrá la UI
  std::shared_ptr<UserInterface> ui;
};