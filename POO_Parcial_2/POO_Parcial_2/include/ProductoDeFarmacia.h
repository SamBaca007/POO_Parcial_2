#pragma once
#include "Producto.h"

// Clase concreta que hereda de Producto
class
ProductoDeFarmacia : public Producto {
public:
  // Llama al constructor de la clase base (Producto)
  ProductoDeFarmacia(const std::string& codigo, const std::string& nombre, float precio, int cantidad)
    : Producto(codigo, nombre, precio, cantidad) {
  }

  // Ejemplo de un método especializado (polimorfismo)
  std::string obtenerTipo() const override {
    return "Farmacia";
  }

};