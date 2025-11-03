#include "Producto.h"

/**
 * @brief Constructor. Inicializa todos los atributos privados de la clase Producto.
 */
Producto::
Producto(const std::string& codigo, const std::string& nombre, float precio,
int cantidad) {
  codigoProducto = codigo;        // @brief Inicializa el código.
  nombreProducto = nombre;        // @brief Inicializa el nombre.
  precioUnitario = precio;        // @brief Inicializa el precio.
  cantidadStock = cantidad;       // @brief Inicializa el stock.
}

// -------------------------------------------------------------------------
// Implementación de Getters
// -------------------------------------------------------------------------

std::string
Producto::obtenerCodigo() const {
  return codigoProducto;
}

std::string
Producto::obtenerNombre() const {
  return nombreProducto;
}

float
Producto::obtenerPrecio() const {
  return precioUnitario;
}

int
Producto::obtenerCantidad() const {
  return cantidadStock;
}

// -------------------------------------------------------------------------
// Implementación de Setters y Modificadores
// -------------------------------------------------------------------------

void
Producto::actualizarCantidad(int nuevaCantidad) {
  // @brief Modifica el stock (usado en venta y compra).
  cantidadStock = nuevaCantidad;
}

void
Producto::establecerNombre(const std::string& nuevoNombre) {
  // @brief Modifica el nombre del producto (usado en CRUD Editar).
  nombreProducto = nuevoNombre;
}

void
Producto::establecerPrecio(float nuevoPrecio) {
  // @brief Modifica el precio del producto (usado en CRUD Editar).
  precioUnitario = nuevoPrecio;
}