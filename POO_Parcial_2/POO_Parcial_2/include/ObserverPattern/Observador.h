#pragma once
/**
 * @brief Declaración adelantada de la clase Producto.
 * Necesaria para evitar dependencias circulares con los archivos de producto
 * y poder utilizar Producto como parámetro en el método actualizar.
 */
class Producto;
/**
 * @brief Interfaz pura (Clase Abstracta) que define el 'Observador' en el patrón Observer.
 * Un observador es un objeto que monitorea el estado de un Sujeto y es notificado
 * de los cambios para realizar una acción específica (ej. emitir una alerta).
 */
class
Observador {
public:

  /**
   * @brief Método que será llamado por el Sujeto para notificar un cambio de estado.
   * Es una función virtual pura (= 0) que debe ser implementada por todas las clases
   * concretas de Observador (ej. AlertaStockBajo).
   * @param producto Referencia constante al Producto cuyo estado ha cambiado.
   */
  virtual void
  actualizar(const Producto& producto) = 0;

  /**
   * @brief Destructor virtual.
   * Es esencial para asegurar la correcta eliminación de las clases derivadas
   * a través de un puntero base (polimorfismo).
   */
  virtual ~Observador() {}
};