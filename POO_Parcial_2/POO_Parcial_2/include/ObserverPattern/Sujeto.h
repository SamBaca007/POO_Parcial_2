#pragma once
#include "Prerequisites.h"
#include "ObserverPattern/Observador.h"

// Interfaz pura para el Sujeto
class
Sujeto {
public:
  // Metodos para gestionar los observadores (adjuntar/separar)
  virtual void adjuntar(std::shared_ptr<Observador> observador) = 0;
  virtual void separar(std::shared_ptr<Observador> observador) = 0;

  // Metodo para notificar a todos los observadores
  virtual void notificar(const Producto& producto) = 0;

  // Destructor virtual
  virtual ~Sujeto() {}
};