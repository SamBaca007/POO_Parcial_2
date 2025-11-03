#include "Prerequisites.h"
#include "GestorInventario.h"
#include "ObserverPattern/AlertaStockBajo.h"
#include "UserInterface/UserInterface.h"
#include "Register/GestorRegistro.h"

int main() {
  // 1. Inicializar el Gestor de Registro
  auto gestorRegistro = std::make_shared<GestorRegistro>();

  // 2. Inicializar el Gestor de Inventario (Le pasamos el gestor de registro)
  auto gestorInventario = std::make_shared<GestorInventario>(gestorRegistro);

  if (!gestorInventario->cargarProductosDesdeJson("InventarioTienda.json")) {
    return 1;
  }

  // 3. Configurar el patron Observer
  int umbralStockBajo = 5;
  auto observadorAlerta = std::make_shared<AlertaStockBajo>(umbralStockBajo);
  gestorInventario->adjuntar(observadorAlerta);

  // 4. Inicializar la Interfaz (Le pasamos ambos gestores)
  UserInterface interfaz(gestorInventario, gestorRegistro);
  interfaz.iniciar();

  // Aquí irá la función de GUARDAR JSON

  return 0;
}