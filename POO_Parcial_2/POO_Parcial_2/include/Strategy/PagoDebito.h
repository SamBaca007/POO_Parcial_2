#pragma once
#include "Strategy/EstrategiaPago.h"

/**
 * @brief Estrategia de pago concreta para transacciones con tarjeta de débito.
 */
class
PagoDebito : public EstrategiaPago {
public:
  /**
   * @brief Procesa el pago con tarjeta de débito.
   * Simula la validación de saldo.
   * @param montoTotal El valor total a pagar.
   * @return Un mensaje que confirma el pago con débito.
   */
  std::string pagar(float montoTotal) override {
    // Aquí iría la lógica de comunicación con el banco para el débito.
    return "Pago con Tarjeta de Debito (Validado)";
  }
};