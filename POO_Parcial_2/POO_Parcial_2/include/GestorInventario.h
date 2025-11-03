#pragma once
#include "Producto.h"                   // Clase base para los artículos del inventario.
#include "Prerequisites.h"              // Inclusiones de librerías esenciales.
#include "ObserverPattern/Sujeto.h"     // Interfaz base para el patrón Observer.
#include "Register/GestorRegistro.h"    // Clase para el registro de transacciones.

/**
 * @brief Clase central del sistema, responsable de la gestión de inventario (CRUD),
 * las transacciones (Compra/Venta) y actúa como Sujeto en el patrón Observer
 * para notificar cambios de stock.
 */
class
GestorInventario : public Sujeto { // Hereda de Sujeto para implementar el patrón Observer.
public:
  /**
   * @brief Constructor que inicializa el GestorInventario.
   * @param registro Puntero inteligente al GestorRegistro para persistir las transacciones.
   */
  GestorInventario(std::shared_ptr<GestorRegistro> registro);

  /**
   * @brief Carga los productos iniciales desde un archivo JSON.
   * Utiliza el Factory Method para crear cada instancia de Producto.
   * @param nombreArchivo El nombre o ruta del archivo JSON a leer.
   * @return True si la carga fue exitosa, false en caso de error.
   */
  bool
  cargarProductosDesdeJson(const std::string& nombreArchivo);

  // ---------------------------------------------------------------------
  // Métodos de Visualización
  // ---------------------------------------------------------------------

  /**
   * @brief Muestra el listado completo de productos y su stock actual.
   */
  void
  mostrarInventario() const;

  // ---------------------------------------------------------------------
  // Métodos de Transacción
  // ---------------------------------------------------------------------

  /**
   * @brief Procesa la compra de un producto (re-surtido).
   * Incrementa el stock del producto y registra la transacción.
   * @param codigoProducto Código del producto a comprar.
   * @param cantidadComprada Cantidad de unidades a añadir al stock.
   */
  void
  realizarCompra(const std::string& codigoProducto, int cantidadComprada);

  /**
   * @brief Procesa la venta de un producto.
   * Decrementa el stock del producto, notifica a los Observadores y registra la transacción.
   * @param codigoProducto Código del producto a vender.
   * @param cantidadVendida Cantidad de unidades a vender.
   */
  void
  realizarVenta(const std::string& codigoProducto, int cantidadVendida);

  // ---------------------------------------------------------------------
  // Métodos CRUD
  // ---------------------------------------------------------------------

  /**
   * @brief Añade un nuevo producto al inventario.
   * Utiliza ProductoFactory para instanciar la clase correcta.
   * @param codigo Código del nuevo producto.
   * @param nombre Nombre del nuevo producto.
   * @param precio Precio unitario.
   * @param cantidad Stock inicial.
   */
  void
  agregarProducto(
      const std::string& codigo,
      const std::string& nombre,
      float precio,
      int cantidad
    );

  /**
   * @brief Modifica los atributos (nombre, precio, stock) de un producto existente.
   * @param codigo Código del producto a editar.
   * @param nuevoNombre Nuevo nombre a asignar.
   * @param nuevoPrecio Nuevo precio a asignar.
   * @param nuevaCantidad Nuevo stock a asignar.
   * @return True si el producto fue encontrado y editado, false si no se encontró.
   */
  bool
  editarProducto(
      const std::string& codigo,
      const std::string& nuevoNombre,
      float nuevoPrecio,
      int nuevaCantidad
    );

  /**
   * @brief Elimina un producto del inventario basándose en su código.
   * @param codigo Código del producto a eliminar.
   * @return True si el producto fue eliminado, false si no se encontró.
   */
  bool
  eliminarProducto(const std::string& codigo);

  // ---------------------------------------------------------------------
  // Implementacion de Metodos de Sujeto (Observer Pattern)
  // ---------------------------------------------------------------------

  /**
   * @brief Añade un observador (ej. AlertaStockBajo) a la lista de suscriptores.
   * @param observador Puntero al observador a adjuntar.
   */
  void
  adjuntar(std::shared_ptr<Observador> observador) override;

  /**
   * @brief Remueve un observador de la lista de suscriptores.
   * @param observador Puntero al observador a separar.
   */
  void
  separar(std::shared_ptr<Observador> observador) override;

  /**
   * @brief Notifica a todos los observadores que el estado de un producto ha cambiado (stock).
   * @param producto Referencia constante al Producto que disparó la notificación.
   */
  void
  notificar(const Producto& producto) override;

private:
  // ---------------------------------------------------------------------
  // Atributos Privados
  // ---------------------------------------------------------------------

  // @brief Contenedor principal de todos los productos en el inventario.
  std::vector<std::shared_ptr<Producto>> listaProductos;

  // @brief Contenedor de todos los observadores suscritos a los cambios de stock.
  std::vector<std::shared_ptr<Observador>> listaObservadores;

  // @brief Puntero al gestor de registros para almacenar el historial de transacciones.
  std::shared_ptr<GestorRegistro> gestorRegistro;
};
