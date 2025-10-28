#include "Prerequisites.h"
#include "GestorInventario.h"

int
main() {

  GestorInventario gestor;

  // Carga del archivo InventarioTienda.json
  gestor.cargarProductosDesdeJson("InventarioTienda.json");

  gestor.mostrarInventario();

  return 0;
}