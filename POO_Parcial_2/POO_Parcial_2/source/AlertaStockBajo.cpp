#include "ObserverPattern/AlertaStockBajo.h"

AlertaStockBajo::AlertaStockBajo(int umbral) {
  umbralMinimo = umbral;
}

// Logica de Alerta
void AlertaStockBajo::actualizar(const Producto& producto) {
  if (producto.obtenerCantidad() <= umbralMinimo) {
    std::cout << "\n[!!! ALERTA DE STOCK !!!] Producto: " << producto.obtenerNombre()
      << " (Cod: " << producto.obtenerCodigo() << ") ha llegado a "
      << producto.obtenerCantidad() << " unidades."
      << " -> Se recomienda re-surtir.\n";
  }
}