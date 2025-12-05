#pragma once
#include "Prerequisites.h" // Incluye std::string y otros tipos base.

// -------------------------------------------------------------------------
// Interfaz: EstrategiaPago (Patrón Strategy)
// -------------------------------------------------------------------------
/**
 * @brief Interfaz abstracta para definir la estrategia de pago.
 * Todas las clases de pago concretas (Efectivo, Crédito, Débito) deben
 * implementar el método 'pagar'. Actúa como la interfaz para el Patrón Strategy.
 */
class
EstrategiaPago {
public:
  /**
   * @brief Implementa la lógica de procesamiento de un pago específico.
   * @param montoTotal El valor total a pagar.
   * @return Una cadena de texto que describe el resultado o el método de pago utilizado.
   */
  virtual std::string pagar(float montoTotal) = 0; // Método virtual puro.

  /**
   * @brief Destructor virtual.
   */
  virtual ~EstrategiaPago() {}
};