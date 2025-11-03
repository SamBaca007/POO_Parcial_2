#pragma once
#include "Prerequisites.h"
#include "Producto.h"
#include "ProductoDeFarmacia.h"

// Clase Factory que contiene el Factory Method
class
  ProductoFactory {
public:
  // El Factory Method, retorna un puntero al objeto base (polimorfismo)
  static std::shared_ptr<Producto> crearProducto(
    const std::string& codigo,
    const std::string& nombre,
    float precio,
    int cantidad) {

    // Logica de decision: 
    // Si el codigo empieza con '3' o '7', lo consideramos de Farmacia.
    if (codigo.rfind("3", 0) == 0 || codigo.rfind("7", 0) == 0) {
      // Crea y retorna un ProductoDeFarmacia (un tipo especializado)
      return std::make_shared<ProductoDeFarmacia>(codigo, nombre, precio, cantidad);
    }
    else {
      // Crea y retorna un Producto generico
      return std::make_shared<Producto>(codigo, nombre, precio, cantidad);
    }
  }
  // Nota: No se necesita un .cpp para esta clase si el método es static e inline.
};