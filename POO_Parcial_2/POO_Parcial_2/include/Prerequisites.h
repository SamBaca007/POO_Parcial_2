#pragma once
/**
 * @brief Este archivo centraliza todas las inclusiones esenciales y definiciones
 * de alias necesarias para la compilación de todos los archivos del proyecto.
 * Su objetivo es mantener el código limpio y reducir la redundancia de inclusiones.
 */

 // -------------------------------------------------------------------------
 // Inclusiones de la Librería Estándar (STD Library Includes)
 // -------------------------------------------------------------------------
#include <iostream>     // @brief Necesario para operaciones de entrada/salida
#include <string>       // @brief Necesario para el manejo de la clase std::string.
#include <vector>       // @brief Necesario para el manejo de contenedores std::vector
#include <fstream>      // @brief Necesario para la manipulación de archivos (lectura/escritura de JSON).
#include <sstream>      // @brief Necesario para el manejo de flujos de strings y parsing de datos.
#include <memory>       // @brief Necesario para el uso de punteros inteligentes en el patrón Observer.
#include <algorithm>    // @brief Necesario para funciones de manipulación de contenedores como std::find_if y std::remove_if.

// -------------------------------------------------------------------------
// Librería de Terceros: JSON (nlohmann/json)
// -------------------------------------------------------------------------
#include "json.hpp"

/**
 * @brief Define un alias simple para el namespace de la librería JSON.
 * Esto simplifica el código y evita el uso de la directiva 'using namespace'.
 */
using json = nlohmann::json;