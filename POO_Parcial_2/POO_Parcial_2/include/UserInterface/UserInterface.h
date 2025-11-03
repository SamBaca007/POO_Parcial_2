#pragma once
#include "Prerequisites.h"
#include "GestorInventario.h"

// Clase para manejar la interfaz de usuario (respetando el estilo)
class
  UserInterface {
public:
  UserInterface(std::shared_ptr<GestorInventario> gestor); // Constructor

  void iniciar(); // Metodo principal para correr el menu (Camel Case)

private:
  std::shared_ptr<GestorInventario> gestorInventario; // Referencia al gestor

  // Metodos del menu (privados y Camel Case)
  void mostrarMenuPrincipal();
  void manejarOpcion(int opcion);
  void menuGestionInventario();
  void manejarGestionInventario(int opcion);

  // Funciones para cada accion CRUD
  void agregarProducto();
  void editarProducto();
  void eliminarProducto();
  void realizarVenta();
  void realizarCompra();
};