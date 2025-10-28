#pragma once
#include "Producto.h"
#include "Prerequisites.h"

class
  GestorInventario {
public:
  GestorInventario();

  // Metodo para cargar el archivo JSON
  bool cargarProductosDesdeJson(const std::string& nombreArchivo); // Camel Case

  // Metodos para el manejo del inventario (compra, venta, etc.)
  void mostrarInventario() const;

private:
  // Vector de punteros inteligentes para manejar los productos
  std::vector<std::shared_ptr<Producto>> listaProductos;
  // Usamos Camel Case para la variable miembro.
};
