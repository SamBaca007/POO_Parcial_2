#pragma once
#include "Producto.h" // Incluye la clase base de la cual hereda.

/**
 * @brief Clase concreta que representa un producto clasificado como de Farmacia.
 * Hereda de Producto y especializa ciertas funcionalidades (ej. obtenerTipo).
 */
class
ProductoDeFarmacia : public Producto {
public:
  /**
   * @brief Constructor que inicializa el ProductoDeFarmacia.
   * Llama directamente al constructor de la clase base Producto.
   * @param codigo Código de identificación del producto.
   * @param nombre Nombre del producto.
   * @param precio Precio unitario.
   * @param cantidad Stock inicial.
   */
  ProductoDeFarmacia(const std::string& codigo, const std::string& nombre,
  float precio, int cantidad)
    : Producto(codigo, nombre, precio, cantidad) {
  }

  /**
   * @brief Sobreescribe el método base para retornar el tipo específico "Farmacia".
   * Este es un ejemplo de polimorfismo.
   * @return El tipo de producto como string ("Farmacia").
   */
  std::string
  obtenerTipo() const override {
    return "Farmacia";
  }
};