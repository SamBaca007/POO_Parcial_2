#pragma once
#include "Prerequisites.h"
#include "GestorInventario.h"
#include "Register/GestorRegistro.h"
#include "../Strategy/EstrategiaPago.h" // Interfaz base
#include "../Strategy/PagoEfectivo.h"   // Estrategias concretas
#include "../Strategy/PagoCredito.h"
#include "../Strategy/PagoDebito.h"
/**
 * @brief Clase responsable de gestionar la Interfaz de Usuario por Consola (CLI).
 * Encapsula la interacción con el usuario, los menús, y la invocación de las
 * funciones de GestorInventario y GestorRegistro.
 */
class
UserInterface {
public:
  /**
   * @brief Constructor de la interfaz de usuario.
   * @param gestorInv Puntero inteligente al GestorInventario principal del sistema.
   * @param gestorReg Puntero inteligente al GestorRegistro para acceder a historiales.
   */
  UserInterface(std::shared_ptr<GestorInventario> gestorInv,
    std::shared_ptr<GestorRegistro> gestorReg);

  /**
   * @brief Inicia el ciclo principal del menú y la interacción con el usuario.
   */
  void
  iniciar();

private:
  // ---------------------------------------------------------------------
  // Miembros Privados (Referencias al Sistema)
  // ---------------------------------------------------------------------
  // Punteros inteligentes para acceder a la lógica del sistema.
  std::shared_ptr<GestorInventario> gestorInventario;
  std::shared_ptr<GestorRegistro> gestorRegistro;

  // ---------------------------------------------------------------------
  // Metodos de Navegación del Menu
  // ---------------------------------------------------------------------

  /**
   * @brief Muestra las opciones principales del sistema.
   */
  void
  mostrarMenuPrincipal();

  /**
   * @brief Procesa la opción seleccionada por el usuario en el menú principal.
   * @param opcion El número de la opción elegida.
   */
  void
  manejarOpcion(int opcion);

  /**
   * @brief Muestra el sub-menú para las operaciones CRUD del inventario.
   */
  void
  menuGestionInventario();

  /**
   * @brief Procesa la opción seleccionada en el menú de gestión de inventario.
   * @param opcion El número de la opción elegida (1: Agregar, 2: Editar, 3: Eliminar).
   */
  void
  manejarGestionInventario(int opcion);

  /**
   * @brief Muestra el sub-menú para ver los historiales de ventas y compras.
   */
  void
  mostrarHistoriales();

  // ---------------------------------------------------------------------
  // Métodos de Acción (CRUD y Transacciones)
  // ---------------------------------------------------------------------

  /**
   * @brief Recibe la entrada del usuario y llama a GestorInventario::agregarProducto.
   */
  void
  agregarProducto();

  /**
   * @brief Recibe la entrada del usuario y llama a GestorInventario::editarProducto.
   */
  void
  editarProducto();

  /**
   * @brief Recibe el código del producto y llama a GestorInventario::eliminarProducto.
   */
  void
  eliminarProducto();

  /**
   * @brief Recibe el código y cantidad y llama a GestorInventario::realizarVenta.
   */
  void
  realizarVenta();

  /**
   * @brief Recibe el código y cantidad y llama a GestorInventario::realizarCompra (re-surtir).
   */
  void
  realizarCompra();
};