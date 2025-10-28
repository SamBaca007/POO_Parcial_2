#include "GestorInventario.h"

GestorInventario::GestorInventario() {
  // Constructor vacio, la carga se hace con el metodo
}

bool GestorInventario::cargarProductosDesdeJson(const std::string& nombreArchivo) {
  // 1. Abrir el archivo
  std::ifstream archivo(nombreArchivo);

  // 2. Verificar si se pudo abrir
  if (!archivo.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << ".\n";
    return false;
  }

  // 3. Leer el contenido y parsear el JSON
  try {
    json j = json::parse(archivo);

    // 4. Asegurarse que el JSON es un array
    if (j.is_array()) {
      for (const auto& elemento : j) {
        // 5. Extraer los datos y crear un nuevo Producto
        std::string codigo = elemento.at("codigo").get<std::string>();
        std::string nombre = elemento.at("nombre").get<std::string>();
        float precio = elemento.at("precio").get<float>();
        int cantidad = elemento.at("cantidad").get<int>();

        // Creacion del objeto Producto (Aplicacion basica de Factory Method)
        // En el siguiente paso, esto se refinará con el patron de diseño Factory real.
        auto nuevoProducto = std::make_shared<Producto>(codigo, nombre, precio, cantidad);

        // Almacenar en el inventario
        listaProductos.push_back(nuevoProducto);
      }
      std::cout << "Inventario cargado exitosamente. Total de productos: " << listaProductos.size() << "\n";
      return true;
    }
    else {
      std::cerr << "Error: El archivo JSON no contiene un array de productos.\n";
      return false;
    }
  }
  catch (const json::exception& e) {
    std::cerr << "Error al parsear JSON: " << e.what() << "\n";
    return false;
  }
}

// Metodo simple de prueba (Respetando el estilo)
void GestorInventario::mostrarInventario() const {
  std::cout << "\n--- Inventario Actual ---\n";
  for (const auto& p : listaProductos) {
    std::cout << "Cod: " << p->obtenerCodigo()
      << " | Nombre: " << p->obtenerNombre()
      << " | Precio: $" << p->obtenerPrecio()
      << " | Cantidad: " << p->obtenerCantidad() << "\n";
  }
  std::cout << "-------------------------\n";
}