#pragma once
#include "Prerequisites.h"
#include "Gasolinera/Combustible.h"
#include "Strategy/EstrategiaPago.h"

// -------------------------------------------------------------------------
// Clase: GestorGasolinera
// -------------------------------------------------------------------------
/**
 * @brief Gestiona la lógica de negocio del módulo de gasolinera.
 * Contiene los tipos de combustible disponibles y realiza las validaciones
 * y transacciones de carga/pago.
 */
class
GestorGasolinera {
public:
  /**
   * @brief Constructor que inicializa los tipos de combustible disponibles.
   */
  GestorGasolinera();

  /**
   * @brief Retorna la lista de tipos de combustible.
   * @return Referencia constante al vector de combustibles.
   */
  const std::vector<Combustible>&
  obtenerTiposCombustible() const;

  /**
   * @brief Calcula el costo total de una carga en base a litros y tipo de combustible.
   * @param codigoCombustible Código del combustible (1, 2, 3...).
   * @param litrosCargados Cantidad de litros.
   * @return El costo total. Retorna 0.0f si el código es inválido.
   */
  float
  calcularCosto(int codigoCombustible, float litrosCargados) const;

  /**
   * @brief Simula y procesa la transacción completa de carga y pago.
   * Lanza la lógica de pago (Strategy) y realiza la validación.
   * @param codigoCombustible Código del combustible.
   * @param litrosCargados Cantidad de litros surtidos.
   * @param montoPagado Cantidad de dinero pagado.
   * @param estrategiaPago La estrategia de pago seleccionada.
   * @return True si la transacción fue exitosa y validada.
   */
  bool
  procesarTransaccion(int codigoCombustible, float litrosCargados, float montoPagado,
  std::shared_ptr<EstrategiaPago> estrategiaPago);

private:
  std::vector<Combustible> listaCombustibles;

  // Método auxiliar para obtener el precio unitario
  float obtenerPrecioPorLitro(int codigoCombustible) const;

  // Método auxiliar para generar el comprobante (ticket) de la gasolinera
  void generarComprobante(const Combustible& combustible, float litros, float total, 
  const std::string& metodoPago) const;
};