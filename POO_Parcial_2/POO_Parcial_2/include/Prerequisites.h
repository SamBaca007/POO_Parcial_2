#pragma once

// STD Library Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream> // Necesario para leer archivos
#include <sstream> // Necesario para parsear el contenido del archivo

// JSON Library
#include "json.hpp"
// Definimos un alias para usarlo sin "using namespace" y respetar la guia de estilo
using json = nlohmann::json;