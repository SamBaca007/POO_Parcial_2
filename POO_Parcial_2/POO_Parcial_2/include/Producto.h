#pragma once
#include "Prerequisites.h"

class
Producto {
public:
  // Constructor
  Producto(const std::string& codigo, const std::string& nombre, float precio, int cantidad);

  // Metodos para obtener información (Respetando Camel Case)
  std::string obtenerCodigo() const;
  std::string obtenerNombre() const;
  float obtenerPrecio() const;
  int obtenerCantidad() const;

  // Metodos para modificar (Ejemplo: al vender o re-surtir)
  void actualizarCantidad(int nuevaCantidad); // Camel Case

private:
  // Atributos privados (Respetando Camel Case, como se sugiere en el documento con m_id)
  std::string codigoProducto;
  std::string nombreProducto;
  float precioUnitario; // La primera palabra en minuscula
  int cantidadStock;
};