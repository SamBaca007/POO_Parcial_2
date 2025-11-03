#pragma once

// Declaracion adelantada para evitar dependencias circulares
class Producto;

// Interfaz pura para el Observador
class
Observador {
public:
  // Metodo que sera llamado por el Sujeto al haber un cambio.
  // Es una funcion virtual pura (= 0)
  virtual void actualizar(const Producto& producto) = 0;

  // Destructor virtual para asegurar la correcta eliminacion de las clases derivadas
  virtual ~Observador() {}
};