#pragma once
#include "Prerequisites.h"
#include "GestorInventario.h"
#include "Gasolinera/GestorGasolinera.h"
#include "Register/GestorRegistro.h"
#include "Strategy/EstrategiaPago.h" // Interfaz base
#include "Strategy/PagoEfectivo.h"   // Estrategias concretas
#include "Strategy/PagoCredito.h"
#include "Strategy/PagoDebito.h"

// ---------------------------------------------------------------------
// CLASE UserInterface
// ---------------------------------------------------------------------

/**
 * @brief Clase responsable de gestionar la Interfaz de Usuario por Consola (CLI).
 * Encapsula la interacción con el usuario, los menús, y la invocación de las
 * funciones de GestorInventario, GestorRegistro y GestorGasolinera.
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
  std::shared_ptr<GestorInventario> gestorInventario;
  std::shared_ptr<GestorGasolinera> gestorGasolinera; // Objeto de Gasolinera
  std::shared_ptr<GestorRegistro> gestorRegistro;

  // ---------------------------------------------------------------------
  // Metodos de Navegación del Menu
  // ---------------------------------------------------------------------

  // Declaración de los métodos que manejan el flujo
  void mostrarMenuPrincipal(); // Muestra el texto del menú
  void manejarOpcion(int opcion); // Contiene el switch de las opciones

  void mostrarHistoriales();

  // ---------------------------------------------------------------------
  // Métodos de Acción (CRUD y Transacciones)
  // ---------------------------------------------------------------------

  void agregarProducto();
  void editarProducto();
  void eliminarProducto();

  /**
   * @brief Recibe el código y cantidad y llama a GestorInventario::realizarVenta
   * (Incluye la selección de la Estrategia de Pago).
   */
  void realizarVenta();

  void realizarCompra();

  /**
   * @brief Muestra el menú y gestiona la lógica del módulo de gasolinera.
   */
  void moduloGasolinera();
};