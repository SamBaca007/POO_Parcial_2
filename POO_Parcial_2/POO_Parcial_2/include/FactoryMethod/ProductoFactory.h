#pragma once
#include "Prerequisites.h"
#include "Producto.h"
#include "ProductoDeFarmacia.h"

/**
 * @brief Clase Factory que implementa el patrón Factory Method.
 * Es responsable de la creación de objetos de la jerarquía Producto,
 * decidiendo qué subclase (ej. Producto o ProductoDeFarmacia) instanciar.
 */
class
ProductoFactory {
public:
  static std::shared_ptr<Producto>
    /**
     * @brief El Factory Method. Decide qué tipo de objeto Producto crear basado en el código.
     * Si el código inicia con '3' o '7', se crea un ProductoDeFarmacia; de lo contrario,
     * se crea un Producto genérico.
     * @param codigo Código de identificación del producto.
     * @param nombre Nombre del producto.
     * @param precio Precio unitario del producto.
     * @param cantidad Stock inicial del producto.
     * @return Un puntero inteligente al objeto base (Producto), que puede ser una subclase.
     */
    crearProducto(
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
  // Nota: No se necesita un .cpp para esta clase ya que el método es static e inline, 
  // y la implementación reside en el archivo de encabezado.
};