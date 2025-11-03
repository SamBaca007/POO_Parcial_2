#pragma once
#include "Prerequisites.h"             // Incluye librerías básicas.
#include "ObserverPattern/Observador.h" // Necesario para definir Observador.
#include "Producto.h"                  // Necesario para el método notificar.

/**
 * @brief Interfaz pura (Clase Abstracta) que define el 'Sujeto' en el patrón Observer.
 * Un sujeto es el objeto que contiene el estado que otros objetos (Observadores)
 * desean monitorear.
 */
class
Sujeto {
public:
  // ---------------------------------------------------------------------
  // Métodos para la Gestión de Observadores
  // ---------------------------------------------------------------------

  /**
   * @brief Permite que un observador se suscriba para recibir notificaciones.
   * @param observador El puntero inteligente al objeto Observador que desea adjuntarse.
   */
  virtual void
  adjuntar(std::shared_ptr<Observador> observador) = 0;

  /**
   * @brief Permite que un observador se desuscriba y deje de recibir notificaciones.
   * @param observador El puntero inteligente al objeto Observador que desea separarse.
   */
  virtual void
  separar(std::shared_ptr<Observador> observador) = 0;

  // ---------------------------------------------------------------------
  // Método de Notificación
  // ---------------------------------------------------------------------

  /**
   * @brief Notifica a todos los observadores adjuntos sobre un cambio de estado.
   * @param producto Referencia constante al Producto cuyo estado ha cambiado.
   */
  virtual void
  notificar(const Producto& producto) = 0;

  /**
   * @brief Destructor virtual. Asegura la destrucción adecuada de las clases derivadas.
   */
  virtual ~Sujeto() {}
};