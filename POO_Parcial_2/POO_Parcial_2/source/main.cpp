#include "Facade/SistemaVentaFacade.h"

int
main() {
  // El Patrón Facade encapsula toda la inicialización,
  // la composición de Gestores, la configuración del Observer,
  // y la carga inicial del JSON.

  // -----------------------------------------------------------------
  // 1. Inicialización y Composición del Sistema (Simplificada)
  // -----------------------------------------------------------------
  SistemaVentaFacade sistema; // <--- Crea y configura TODO el subsistema.

  // -----------------------------------------------------------------
  // 2. Inicio del Ciclo de Vida del Programa
  // -----------------------------------------------------------------
  sistema.iniciarSistema(); // <--- Inicia la interfaz de usuario.

  // -----------------------------------------------------------------
  // 3. Cierre y Persistencia de Datos
  // -----------------------------------------------------------------
  // El Facade es el responsable de guardar los datos al finalizar.
  // Aunque no la hemos implementado, aquí iría la lógica de guardado:
  // sistema.guardarPersistencia(); 

  return 0;
}