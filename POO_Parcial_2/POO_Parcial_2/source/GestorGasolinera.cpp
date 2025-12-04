#include "Prerequisites.h"
#include "Gasolinera/GestorGasolinera.h"
#include "IO/GeneradorTicket.h" // Usaremos el generador de tickets para el comprobante

// ----------------------------------------------------------------------
// Implementacion de GestorGasolinera
// ----------------------------------------------------------------------

GestorGasolinera::GestorGasolinera() {
  // Inicialización de datos simulados de combustible
  listaCombustibles = {
      {"Magna", 22.50f, 1},
      {"Premium", 24.80f, 2},
      {"Diesel", 23.10f, 3}
  };
}

const std::vector<Combustible>&
GestorGasolinera::obtenerTiposCombustible() const {
  return listaCombustibles;
}

float
GestorGasolinera::obtenerPrecioPorLitro(int codigoCombustible) const {
  for (const auto& c : listaCombustibles) {
    if (c.codigo == codigoCombustible) {
      return c.precioPorLitro;
    }
  }
  return 0.0f; // Código no encontrado
}

float
GestorGasolinera::calcularCosto(int codigoCombustible, float litrosCargados) const {
  float precio = obtenerPrecioPorLitro(codigoCombustible);
  if (precio > 0.0f) {
    return precio * litrosCargados;
  }
  return 0.0f;
}

bool
GestorGasolinera::procesarTransaccion(int codigoCombustible, float litrosCargados,
float montoPagado, std::shared_ptr<EstrategiaPago> estrategiaPago) {

  float costoCalculado = calcularCosto(codigoCombustible, litrosCargados);

  Combustible combustibleSeleccionado = {};
  for (const auto& c : listaCombustibles) {
    if (c.codigo == codigoCombustible) {
      combustibleSeleccionado = c;
      break;
    }
  }

  // 1. Validación de costos
  const float tolerancia = 0.01f; // Tolerancia para errores de punto flotante
  if (std::abs(montoPagado - costoCalculado) > tolerancia) {
    std::cerr << "\n[ERROR VALIDACION] El monto pagado ($" << std::fixed <<
    std::setprecision(2) << montoPagado << ") no coincide con el costo calculado ($" <<
    costoCalculado << ") por la carga.\n";

    // Simulación de la regla de negocio: ¿Pagó antes de cargar?
    if (montoPagado > costoCalculado) {
      std::cout << "[REGISTRO] Se procesara un reembolso de $" <<
      (montoPagado - costoCalculado) << ".\n";
    }
    else {
      std::cout << "[REGISTRO] Faltan $" << (costoCalculado - montoPagado) <<
      " por pagar (Validacion 'Pago antes'). Transaccion Cancelada.\n";
      return false;
    }
  }

  // 2. Procesamiento del Pago (Patrón Strategy)
  std::string resultadoPago = estrategiaPago->pagar(montoPagado);
  std::cout << "\n[PAGO GAS] Transaccion de $" << montoPagado <<
  " procesada: " << resultadoPago << ".\n";

  // 3. Generación del Comprobante
  generarComprobante(combustibleSeleccionado, litrosCargados,
  costoCalculado, resultadoPago);

  std::cout << "Carga exitosa: " << litrosCargados << " L de " <<
  combustibleSeleccionado.nombre << " por $" << costoCalculado << ".\n";
  return true;
}

void
GestorGasolinera::generarComprobante(const Combustible& combustible, float litros,
float total, const std::string& metodoPago) const {
  // Reutilizamos la lógica del GeneradorTicket, adaptándola a la gasolinera.

  // El ticket de gasolinera es una variante del ticket de venta
  GeneradorTicket generador;

  // Simulación del output del ticket de gasolinera (podríamos crear un método específico en GeneradorTicket, 
  // pero para simplicidad, lo imprimimos aquí):
  std::cout << "\n[COMPROBANTE GAS]\n";
  std::cout << "----------------------------------------\n";
  std::cout << "Estacion de Servicio XYZ\n";
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Tipo: " << combustible.nombre << "\n";
  std::cout << "Precio/L: $" << combustible.precioPorLitro << "\n";
  std::cout << "Litros: " << litros << "\n";
  std::cout << "TOTAL: $" << total << "\n";
  std::cout << "Pago: " << metodoPago << "\n";
  std::cout << "----------------------------------------\n";

  // Simulación de envío de factura (cumpliendo el requisito)
  std::cout << "[FACTURACION GAS] Simulando envio de factura...\n";
}