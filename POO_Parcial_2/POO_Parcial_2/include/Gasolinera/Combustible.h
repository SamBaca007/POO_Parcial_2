#pragma once
#include "Prerequisites.h"

/**
 * @brief Estructura de datos simple para representar un tipo de combustible.
 */
struct
Combustible {
  std::string nombre; // Ej: "Magna", "Premium", "Diesel"
  float precioPorLitro;
  int codigo;         // Identificador para seleccionar en el menú (1, 2, 3...)
};