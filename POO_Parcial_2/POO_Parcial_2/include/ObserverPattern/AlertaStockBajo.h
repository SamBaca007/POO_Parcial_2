#pragma once
#include "ObserverPattern/Observador.h"
#include "Producto.h" 
#include "Prerequisites.h"

class
AlertaStockBajo : public Observador {
public:
  AlertaStockBajo(int umbral);

  // Implementacion del metodo de la interfaz Observador
  void actualizar(const Producto& producto) override;

private:
  int umbralMinimo; // Umbral para disparar la alerta (ej. 5 unidades)
};