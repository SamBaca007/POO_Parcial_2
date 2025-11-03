#pragma once
#include "ObserverPattern/Observador.h" // La clase debe heredar de esta interfaz.
#include "Producto.h"                  // Necesario para la función actualizar (recibe un Producto). 
#include "Prerequisites.h"             // Inclusiones estándar.

/**
 * @brief Observador concreto que maneja la lógica de las alertas de stock.
 * Dispara una notificación si el stock actual del producto es igual o inferior
 * a su umbral mínimo configurado.
 */
class
AlertaStockBajo : public Observador{
public:
  /**
   * @brief Constructor que inicializa el umbral de stock.
   * @param umbral El valor límite para considerar que el stock es bajo.
   */
  AlertaStockBajo(int umbral);

  /**
   * @brief Implementación del método de la interfaz Observador.
   * Verifica si el stock del producto notificado ha caído por debajo del umbral.
   * @param producto Referencia constante al Producto cuyo estado ha cambiado.
   */
  void
  actualizar(const Producto& producto) override;

  private:
    int umbralMinimo; // @brief Umbral numérico para disparar la alerta (ej. 5 unidades).
};