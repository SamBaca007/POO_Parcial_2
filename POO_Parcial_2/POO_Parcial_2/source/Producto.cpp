#include "Producto.h"

// Implementación del constructor y métodos
Producto::Producto(const std::string& codigo, const std::string& nombre, float precio, int cantidad) {
  codigoProducto = codigo;
  nombreProducto = nombre;
  precioUnitario = precio;
  cantidadStock = cantidad;
}

std::string Producto::obtenerCodigo() const {
  return codigoProducto;
}

std::string Producto::obtenerNombre() const {
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

void
Producto::actualizarCantidad(int nuevaCantidad) {
  cantidadStock = nuevaCantidad;
}

void Producto::establecerNombre(const std::string& nuevoNombre) {
  nombreProducto = nuevoNombre;
}

void Producto::establecerPrecio(float nuevoPrecio) {
  precioUnitario = nuevoPrecio;
}