#pragma once
#include "Strategy/EstrategiaPago.h"

/**
 * @brief Estrategia de pago concreta para transacciones realizadas en efectivo.
 */
class
PagoEfectivo : public EstrategiaPago {
public:
  /**
   * @brief Procesa el pago en efectivo.
   * @param montoTotal El valor total a pagar.
   * @return Un mensaje que confirma el pago en efectivo.
   */
  std::string pagar(float montoTotal) override {
    // En un sistema real, aquí se gestionaría el cambio.
    return "Pago en Efectivo (" + std::to_string(montoTotal) + " unidades)";
  }
};