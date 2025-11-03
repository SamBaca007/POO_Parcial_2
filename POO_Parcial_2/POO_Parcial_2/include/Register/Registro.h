#pragma once
// Incluye librerías básicas y la librería JSON (desde Prerequisites.h)
#include "Prerequisites.h" 
/**
 * @brief Estructura que define los datos inmutables de una venta realizada.
 * Esta estructura se utiliza para mantener un registro histórico de las transacciones.
 */
struct 
RegistroVenta {
  std::string codigoProducto;  // @brief Código de identificación del producto vendido.
  int cantidadVendida;         // @brief Cantidad de unidades vendidas en la transaccion.
  float precioVenta;           // @brief Precio unitario del producto en el momento de la venta.
  std::string fecha;           // @brief Fecha en la que se registró la venta (formato simple AAAA-MM-DD).
};

/**
 * @brief Estructura que define los datos inmutables de una compra o re-surtido.
 * Esta estructura se utiliza para mantener un registro histórico de las transacciones.
 */
struct
RegistroCompra {
  std::string codigoProducto;  // @brief Código de identificación del producto comprado.
  int cantidadComprada;        // @brief Cantidad de unidades compradas en la transaccion.
  float precioCompra;          // @brief Costo unitario del producto en el momento de la compra.
  std::string fecha;           // @brief Fecha en la que se registró la compra (formato simple AAAA-MM-DD).
};