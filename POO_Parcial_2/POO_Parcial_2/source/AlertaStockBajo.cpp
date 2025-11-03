#include "ObserverPattern/AlertaStockBajo.h"

AlertaStockBajo::
AlertaStockBajo(int umbral) {
  // @brief Inicializa el observador con el valor de stock minimo para las alertas.
  umbralMinimo = umbral; // Variable local autodescriptiva.
}

void
AlertaStockBajo::actualizar(const Producto& producto) {
  // @brief Verifica si el stock del producto notificado ha caido al umbral o por debajo.

  // Logica de Alerta
  if (producto.obtenerCantidad() <= umbralMinimo) {
    // Emite un mensaje de alerta a la consola.
    std::cout << "\n[!!! ALERTA DE STOCK !!!] Producto: " << producto.obtenerNombre()
      << " (Cod: " << producto.obtenerCodigo() << ") ha llegado a "
      << producto.obtenerCantidad() << " unidades."
      << " -> Se recomienda re-surtir.\n";
  }
}