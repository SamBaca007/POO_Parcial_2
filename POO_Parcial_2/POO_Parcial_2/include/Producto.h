#pragma once
#include "Prerequisites.h"

/**
 * @brief Clase base que representa un artículo genérico dentro del inventario.
 * Contiene los atributos básicos (código, nombre, precio, stock) y los métodos
 * necesarios para la gestión CRUD y transacciones (venta/compra).
 */
class
Producto {
public:
  /**
   * @brief Constructor que inicializa el objeto Producto.
   * @param codigo Código de identificación único del producto.
   * @param nombre Nombre descriptivo del producto.
   * @param precio Precio unitario de venta.
   * @param cantidad Stock inicial en el inventario.
   */
  Producto(const std::string& codigo, const std::string& nombre,
  float precio, int cantidad);

  void
    /**
     * @brief Actualiza la cantidad de stock del producto.
     * Se usa tanto para incrementar (compra) como para decrementar (venta).
     * @param nuevaCantidad El nuevo valor de stock después de la transacción.
     */
    actualizarCantidad(int nuevaCantidad);

  /**
   * @brief Obtiene el tipo de producto.
   * Es un método virtual para permitir el polimorfismo. Las subclases
   * (ej. ProductoDeFarmacia) lo sobrescribirán.
   * @return Siempre retorna "General" para la clase base.
   */
  virtual std::string
  obtenerTipo() const {
    return "General";
  }

  /**
   * @brief Obtiene el código de identificación del producto.
   * @return El código del producto.
   */
  std::string
  obtenerCodigo() const;

  /**
   * @brief Obtiene el nombre del producto.
   * @return El nombre del producto.
   */
  std::string
  obtenerNombre() const;

  /**
   * @brief Obtiene el precio unitario del producto.
   * @return El precio del producto.
   */
  float
  obtenerPrecio() const;

  /**
   * @brief Obtiene la cantidad actual de stock.
   * @return La cantidad de unidades en stock.
   */
  int
  obtenerCantidad() const;

  // ---------------------------------------------------------------------
  // Métodos Setters (Modificar para CRUD)
  // ---------------------------------------------------------------------

  /**
   * @brief Establece un nuevo nombre para el producto.
   * Utilizado en la función de Editar (CRUD).
   * @param nuevoNombre El nuevo nombre a asignar.
   */
  void
  establecerNombre(const std::string& nuevoNombre);

  /**
   * @brief Establece un nuevo precio unitario para el producto.
   * Utilizado en la función de Editar (CRUD).
   * @param nuevoPrecio El nuevo precio a asignar.
   */
  void
  establecerPrecio(float nuevoPrecio);

private:
  std::string codigoProducto;     // @brief Código de identificación.
  std::string nombreProducto;     // @brief Nombre del artículo.
  float precioUnitario;           // @brief Precio de venta.
  int cantidadStock;              // @brief Cantidad de unidades en stock.
};