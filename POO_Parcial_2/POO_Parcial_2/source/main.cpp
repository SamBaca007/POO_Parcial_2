#include "Prerequisites.h"                    // Inclusiones estándar.
#include "GestorInventario.h"                 // La clase central de lógica de negocio.
#include "ObserverPattern/AlertaStockBajo.h"  // Observador concreto.
#include "UserInterface/UserInterface.h"      // Interfaz de usuario.
#include "Register/GestorRegistro.h"          // Gestión del historial de transacciones.

/**
 * @brief Función principal (main) del programa.
 * Responsable de la inicialización de todos los componentes, la carga de datos
 * y la configuración del patrón Observer antes de iniciar la interfaz de usuario.
 */
int
main() {
  // -----------------------------------------------------------------
  // 1. Inicialización y Composición del Sistema
  // -----------------------------------------------------------------

  // @brief Inicializa el Gestor de Registro (almacena ventas y compras).
  auto gestorRegistro = std::make_shared<GestorRegistro>();

  // @brief Inicializa el Gestor de Inventario. Se le inyecta el GestorRegistro
  //        (patrón Composition) para que pueda registrar transacciones.
  auto gestorInventario = std::make_shared<GestorInventario>(gestorRegistro);

  // @brief Intenta cargar los datos iniciales del inventario desde el archivo JSON.
  if (!gestorInventario->cargarProductosDesdeJson("InventarioTienda.json")) {
    // Si falla la carga (ej. archivo no existe), el programa termina.
    return 1;
  }

  // -----------------------------------------------------------------
  // 2. Configuración del Patrón Observer
  // -----------------------------------------------------------------

  int umbralStockBajo = 5; // @brief Define el límite mínimo de stock para disparar alertas.

  // @brief Crea el Observador concreto (el que mostrará las alertas en consola).
  auto observadorAlerta = std::make_shared<AlertaStockBajo>(umbralStockBajo);

  // @brief El Inventario (Sujeto) adjunta al Observador para ser notificado de cambios.
  gestorInventario->adjuntar(observadorAlerta);

  // -----------------------------------------------------------------
  // 3. Inicio del Ciclo de Vida del Programa
  // -----------------------------------------------------------------

  // @brief Inicializa la Interfaz de Usuario, inyectando ambos gestores (dependencias).
  UserInterface interfaz(gestorInventario, gestorRegistro);

  // @brief Inicia el ciclo principal del menú y la interacción con el usuario.
  interfaz.iniciar();

  // -----------------------------------------------------------------
  // 4. Cierre y Persistencia de Datos
  // -----------------------------------------------------------------

  // Aquí irá la función de GUARDAR JSON (guardarProductosAJson).
  // Esta función debe ser llamada antes de que el programa termine para 
  // persistir cualquier cambio realizado en el inventario.

  return 0;
}