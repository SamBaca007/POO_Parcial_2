#pragma once
#include "Prerequisites.h"
#include "Register/Registro.h"
/**
 * @brief Clase responsable de gestionar y almacenar todos los historiales
 * de transacciones de venta y compra del inventario.
 */
class
GestorRegistro {
public:
  /**
   * @brief Constructor por defecto de GestorRegistro.
   */
  GestorRegistro();

  // ---------------------------------------------------------------------
  // Métodos de Registro
  // ---------------------------------------------------------------------

  /**
   * @brief Registra una nueva transacción de venta en el historial.
   * @param codigo El código del producto vendido.
   * @param cantidad La cantidad de unidades vendidas.
   * @param precio El precio unitario de venta registrado.
   * @param fecha La fecha en la que se realizó la venta (formato "AAAA-MM-DD" simplificado).
   */
  void
  registrarVenta(const std::string& codigo, int cantidad,
      float precio, const std::string& fecha);

  /**
   * @brief Registra una nueva transacción de compra (re-surtido) en el historial.
   * @param codigo El código del producto comprado.
   * @param cantidad La cantidad de unidades compradas.
   * @param precio El costo unitario de compra registrado.
   * @param fecha La fecha en la que se realizó la compra (formato "AAAA-MM-DD" simplificado).
   */
  void
  registrarCompra(const std::string& codigo, int cantidad,
      float precio, const std::string& fecha);

  // ---------------------------------------------------------------------
  // Métodos de Visualización
  // ---------------------------------------------------------------------

  /**
   * @brief Muestra en consola el historial completo de ventas.
   */
  void mostrarHistorialVentas() const;

  /**
   * @brief Muestra en consola el historial completo de compras.
   */
  void mostrarHistorialCompras() const;

private:
  // Contenedores internos para la persistencia del historial.
  std::vector<RegistroVenta> historialVentas;
  std::vector<RegistroCompra> historialCompras;
};