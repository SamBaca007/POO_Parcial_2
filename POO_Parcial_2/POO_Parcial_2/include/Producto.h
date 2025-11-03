#pragma once
#include "Prerequisites.h"

class
Producto {
public:
  // Constructor
  Producto(const std::string& codigo, const std::string& nombre, float precio, int cantidad);

  // Metodos para modificar (Ejemplo: al vender o re-surtir)
  void actualizarCantidad(int nuevaCantidad);

  // Convertimos a virtual para permitir el polimorfismo
  virtual std::string obtenerTipo() const {
    return "General";
  }

  // Metodos para obtener información
  std::string obtenerCodigo() const;
  std::string obtenerNombre() const;
  float obtenerPrecio() const;
  int obtenerCantidad() const;

  // Metodos para modificar Nombre y Precio
  void establecerNombre(const std::string& nuevoNombre);
  void establecerPrecio(float nuevoPrecio);

private:
  // Atributos privados
  std::string codigoProducto;
  std::string nombreProducto;
  float precioUnitario;
  int cantidadStock;
};