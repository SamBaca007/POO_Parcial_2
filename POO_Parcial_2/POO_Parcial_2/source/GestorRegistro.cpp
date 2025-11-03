#include "Register/GestorRegistro.h"

GestorRegistro::
GestorRegistro() {
  // @brief Constructor de la clase. Los vectores de historial se inicializan
  //        automaticamente (por defecto) vacios.
}

// -------------------------------------------------------------------------
// Logica de Registro de Transacciones
// -------------------------------------------------------------------------

void
GestorRegistro::registrarVenta(const std::string& codigo, int cantidad,
float precio, const std::string& fecha) {
  // @brief Crea una nueva estructura RegistroVenta con los datos de la transaccion
  //        y la añade al historial.

  RegistroVenta registro; // Variable local autodescriptiva.
  registro.codigoProducto = codigo;
  registro.cantidadVendida = cantidad;
  registro.precioVenta = precio;
  registro.fecha = fecha;

  historialVentas.push_back(registro);
}

void
GestorRegistro::registrarCompra(const std::string& codigo, int cantidad,
float precio, const std::string& fecha) {
  // @brief Crea una nueva estructura RegistroCompra con los datos de la transaccion
  //        y la añade al historial de re-surtido.

  RegistroCompra registro; // Variable local autodescriptiva.
  registro.codigoProducto = codigo;
  registro.cantidadComprada = cantidad;
  registro.precioCompra = precio;
  registro.fecha = fecha;

  historialCompras.push_back(registro);
}

// -------------------------------------------------------------------------
// Logica de Visualizacion de Historiales
// -------------------------------------------------------------------------

void
GestorRegistro::mostrarHistorialVentas() const {
  // @brief Itera sobre el historial de ventas y muestra los datos en consola.

  std::cout << "\n===== HISTORIAL DE VENTAS =====\n";
  if (historialVentas.empty()) {
    std::cout << "No hay ventas registradas.\n";
    return;
  }

  // Encabezado de la tabla de ventas
  std::cout << "Fecha\t\tCodigo\tCant\tPrecio Total\n";
  std::cout << "------------------------------------------------\n";

  for (const auto& reg : historialVentas) {
    std::cout << reg.fecha << "\t"
      << reg.codigoProducto << "\t"
      << reg.cantidadVendida << "\t"
      << reg.cantidadVendida * reg.precioVenta << "\n";
  }
  std::cout << "===============================\n";
}

void
GestorRegistro::mostrarHistorialCompras() const {
  // @brief Itera sobre el historial de compras y muestra los datos en consola.

  std::cout << "\n===== HISTORIAL DE COMPRAS =====\n";
  if (historialCompras.empty()) {
    std::cout << "No hay compras registradas.\n";
    return;
  }

  // Encabezado de la tabla de compras
  std::cout << "Fecha\t\tCodigo\tCant\tCosto Total\n";
  std::cout << "------------------------------------------------\n";

  for (const auto& reg : historialCompras) {
    std::cout << reg.fecha << "\t"
      << reg.codigoProducto << "\t"
      << reg.cantidadComprada << "\t"
      << reg.cantidadComprada * reg.precioCompra << "\n";
  }
  std::cout << "================================\n";
}