#pragma once
#include "Strategy/EstrategiaPago.h"

/**
 * @brief Estrategia de pago concreta para transacciones con tarjeta de crédito.
 */
class
PagoCredito : public EstrategiaPago {
public:
  /**
   * @brief Procesa el pago con tarjeta de crédito.
   * Simula la validación de la tarjeta.
   * @param montoTotal El valor total a pagar.
   * @return Un mensaje que confirma el pago con crédito.
   */
  std::string pagar(float montoTotal) override {
    // Aquí iría la lógica de comunicación con la pasarela de pagos.
    return "Pago con Tarjeta de Credito (Procesado)";
  }
};