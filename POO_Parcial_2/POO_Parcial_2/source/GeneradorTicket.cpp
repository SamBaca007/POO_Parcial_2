#include "Prerequisites.h"
#include "IO/GeneradorTicket.h"
#include <ctime> // Para obtener la fecha y hora actual
#include <iomanip> // Para std::setprecision

// ----------------------------------------------------------------------
// Implementacion de GeneradorTicket
// ----------------------------------------------------------------------

void
GeneradorTicket::generarTicketVentaYSimularEnvio(
  const std::string& codigoProducto,
  const std::string& nombreProducto,
  int cantidadVendida,
  float precioUnitario,
  float montoTotal,
  const std::string& metodoPago
) const {
  // 1. Obtener fecha y hora actual
  time_t now = time(0);
  std::string fechaYHora = ctime(&now);
  // Eliminar el salto de línea que ctime añade
  fechaYHora.erase(fechaYHora.find_last_not_of(" \n\r\t") + 1);

  std::string nombreArchivo = "Ticket_Venta_" + codigoProducto + "_"
  + std::to_string(now) + ".txt";
  std::ofstream archivo(nombreArchivo); // Abre el archivo de salida

  if (archivo.is_open()) {
    // Formato del ticket
    archivo << "========================================\n";
    archivo << "          TICKET DE VENTA OFICIAL       \n";
    archivo << "========================================\n";
    archivo << "Fecha y Hora: " << fechaYHora << "\n";
    archivo << "Metodo de Pago: " << metodoPago << "\n";
    archivo << "----------------------------------------\n";
    archivo << std::fixed << std::setprecision(2);
    archivo << "Producto: " << nombreProducto << " (Cod: " << codigoProducto << ")\n";
    archivo << "Cantidad: " << cantidadVendida << "\n";
    archivo << "Precio Unitario: $" << precioUnitario << "\n";
    archivo << "----------------------------------------\n";
    archivo << "TOTAL: $" << montoTotal << "\n";
    archivo << "========================================\n";
    archivo.close();
    std::cout << "\n[TICKETING] Ticket de venta generado: " << nombreArchivo << "\n";
  }
  else {
    std::cerr << "\n[ERROR TICKET] No se pudo crear el archivo de ticket: "
    << nombreArchivo << "\n";
  }

  // 2. Simular envío de factura por correo (Output en consola)
  std::cout << "\n[FACTURACION] Simulando envio de factura electronica a:\n";
  std::cout << "-> Correo: cliente_ejemplo@empresa.com\n";
  std::cout << "-> Asunto: Su Factura de Compra " << fechaYHora << "\n";
  std::cout << "-> Contenido: Se adjunta el archivo " << nombreArchivo << "\n";
  std::cout << "----------------------------------------\n";
}

void
GeneradorTicket::generarTicketCompra(const RegistroCompra& compra) const {
  // @brief Genera un comprobante de compra para re-surtido.

  std::string nombreArchivo = "Comprobante_Compra_" + compra.codigoProducto
  + "_" + compra.fecha + ".txt";
  std::ofstream archivo(nombreArchivo);

  if (archivo.is_open()) {
    archivo << "========================================\n";
    archivo << "      COMPROBANTE DE RE-SURTIDO/COMPRA  \n";
    archivo << "========================================\n";
    archivo << "Fecha: " << compra.fecha << "\n";
    archivo << "----------------------------------------\n";
    archivo << std::fixed << std::setprecision(2);
    archivo << "Producto: (Cod: " << compra.codigoProducto << ")\n";
    archivo << "Cantidad Comprada: " << compra.cantidadComprada << "\n";
    archivo << "Costo Unitario: $" << compra.precioCompra << "\n";
    archivo << "Costo Total: $" << (compra.cantidadComprada * compra.precioCompra) << "\n";
    archivo << "========================================\n";
    archivo.close();
    std::cout << "\n[REGISTRO] Comprobante de compra generado: " << nombreArchivo << "\n";
  }
  else {
    std::cerr << "\n[ERROR TICKET] No se pudo crear el archivo de compra: "
    << nombreArchivo << "\n";
  }
}