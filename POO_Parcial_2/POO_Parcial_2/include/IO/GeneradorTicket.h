#pragma once
#include "Prerequisites.h"
#include "Register/Registro.h" // Necesario para usar RegistroVenta y RegistroCompra

// -------------------------------------------------------------------------
// Clase: GeneradorTicket
// -------------------------------------------------------------------------
/**
 * @brief Clase utilitaria responsable de la generación de documentos de transacción.
 * Maneja la salida a archivo (.TXT) para tickets/comprobantes y simula el
 * envío de facturas por correo electrónico (salida en consola).
 */
class
GeneradorTicket {
public:
  /**
   * @brief Genera un archivo .txt con los detalles de la venta y simula el envío por correo.
   * @param codigoProducto El código del producto vendido.
   * @param nombreProducto El nombre del producto.
   * @param cantidadVendida La cantidad de unidades vendidas.
   * @param precioUnitario El precio al momento de la venta.
   * @param montoTotal El costo total de la transacción.
   * @param metodoPago El nombre del método de pago utilizado (ej. "Efectivo", "Crédito").
   */
  void generarTicketVentaYSimularEnvio(const std::string& codigoProducto,
      const std::string& nombreProducto, int cantidadVendida, float precioUnitario,
      float montoTotal, const std::string& metodoPago) const;

  /**
   * @brief Genera un archivo .txt para el comprobante de compra (re-surtido).
   * @param compra Estructura de RegistroCompra que contiene los detalles de la transacción.
   */
  void generarTicketCompra(const RegistroCompra& compra) const;
};