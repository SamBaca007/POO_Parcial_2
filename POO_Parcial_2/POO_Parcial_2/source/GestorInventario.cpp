#include "GestorInventario.h"
#include "FactoryMethod/ProductoFactory.h"

GestorInventario::GestorInventario() {
  // Constructor vacio, la carga se hace con el metodo
}

// Implementacion de los metodos de Sujeto
void
GestorInventario::adjuntar(std::shared_ptr<Observador> observador) {
  listaObservadores.push_back(observador);
}

void
GestorInventario::separar(std::shared_ptr<Observador> observador) {
  // Implementacion de separacion omitida por complejidad.
  // En un proyecto real, se usaria std::remove para eliminar el observador del vector.
}

void
GestorInventario::notificar(const Producto& producto) {
  // Itera sobre todos los observadores y llama a su metodo actualizar
  for (const auto& observador : listaObservadores) {
    observador->actualizar(producto);
  }
}

// Logica para Agregar Producto

void
GestorInventario::agregarProducto(
  const std::string& codigo,
  const std::string& nombre,
  float precio,
  int cantidad) {

  // 1. Verificación de Código Duplicado
  auto it = std::find_if(listaProductos.begin(), listaProductos.end(),
    [&codigo](const std::shared_ptr<Producto>& p) {
      return p->obtenerCodigo() == codigo;
    });

  if (it != listaProductos.end()) {
    std::cout << "\nError al Agregar: El producto con codigo " << codigo
    << " ya existe en el inventario.\n";
    return;
  }

  // 2. Creación del Producto usando el Factory Method
  // El Factory decide si crear un Producto o un ProductoDeFarmacia (o cualquier otra especialización)
  auto nuevoProducto = ProductoFactory::crearProducto(codigo, nombre, precio, cantidad);

  // 3. Agregar a la lista
  listaProductos.push_back(nuevoProducto);

  std::cout << "\n[Inventario] Producto agregado: " << nombre
    << " (Cod: " << codigo << ", Tipo: " << nuevoProducto->obtenerTipo() << ")\n";
}

// Logica para Editar Producto
bool
GestorInventario::editarProducto(
  const std::string& codigo,
  const std::string& nuevoNombre,
  float nuevoPrecio,
  int nuevaCantidad) {

  // 1. Buscar el producto por codigo
  auto it = std::find_if(listaProductos.begin(), listaProductos.end(),
    [&codigo](const std::shared_ptr<Producto>& p) {
      return p->obtenerCodigo() == codigo;
    });

  if (it == listaProductos.end()) {
    std::cout << "\nError al Editar: Producto con codigo " << codigo << " no encontrado.\n";
    return false;
  }

  std::shared_ptr<Producto> productoAEditar = *it;

  // 2. Aplicar las modificaciones
  productoAEditar->establecerNombre(nuevoNombre);
  productoAEditar->establecerPrecio(nuevoPrecio);
  productoAEditar->actualizarCantidad(nuevaCantidad); // Reutilizamos el setter de cantidad

  std::cout << "\n[Inventario] Producto " << codigo << " editado exitosamente: "
    << nuevoNombre << ", Precio: $" << nuevoPrecio
    << ", Stock: " << nuevaCantidad << ".\n";

  // 3. Notificar a los observadores (por si el nuevo stock es bajo)
  notificar(*productoAEditar);

  return true;
}

// Logica para Eliminar Producto
bool
GestorInventario::eliminarProducto(const std::string& codigo) {
  // 1. Buscar el producto por codigo usando std::remove_if
  // std::remove_if mueve los elementos a eliminar al final del vector
  auto it = std::remove_if(listaProductos.begin(), listaProductos.end(),
    [&codigo](const std::shared_ptr<Producto>& p) {
      return p->obtenerCodigo() == codigo;
    });

  // 2. Verificar si se encontró el producto
  if (it == listaProductos.end()) {
    std::cout << "\nError al Eliminar: Producto con codigo "
    << codigo << " no encontrado.\n";
    return false;
  }

  // 3. Eliminar los elementos del vector (desde la posición 'it' hasta el final)
  listaProductos.erase(it, listaProductos.end());

  std::cout << "\n[Inventario] Producto con codigo "
  << codigo << " eliminado exitosamente.\n";
  return true;
}

void
GestorInventario::realizarCompra(const std::string&
codigoProducto, int cantidadComprada) {
  auto it = std::find_if(listaProductos.begin(), listaProductos.end(),
    [&codigoProducto](const std::shared_ptr<Producto>& p) {
      return p->obtenerCodigo() == codigoProducto;
    });

  if (it == listaProductos.end()) {
    std::cout << "Compra Fallida: Producto con codigo "
    << codigoProducto << " no encontrado.\n";
    return;
  }

  std::shared_ptr<Producto> productoAComprar = *it;
  int stockActual = productoAComprar->obtenerCantidad();

  // 2. Actualizar stock
  int nuevoStock = stockActual + cantidadComprada;
  productoAComprar->actualizarCantidad(nuevoStock);

  std::cout << "\nCompra Exitosa: " << cantidadComprada << " unidades de "
  << productoAComprar->obtenerNombre() << " re-surtidas. Stock total: "
  << nuevoStock << ".\n";
}

// ----------------------------------------------------------------------
// Logica de Venta (El punto clave donde se usa el patron Observer)

void
GestorInventario::realizarVenta(const std::string&
codigoProducto, int cantidadVendida) {
  // 1. Buscar el producto
  auto it = std::find_if(listaProductos.begin(), listaProductos.end(),
    [&codigoProducto](const std::shared_ptr<Producto>& p) {
      return p->obtenerCodigo() == codigoProducto;
    });

  if (it == listaProductos.end()) {
    std::cout << "Venta Fallida: Producto con codigo "
    << codigoProducto << " no encontrado.\n";
    return;
  }

  std::shared_ptr<Producto> productoAVender = *it;
  int stockActual = productoAVender->obtenerCantidad();

  // 2. Verificar y actualizar stock
  if (stockActual < cantidadVendida) {
    std::cout << "Venta Fallida: Stock insuficiente de "
    << productoAVender->obtenerNombre()
    << ". Stock actual: " << stockActual << ".\n";
    return;
  }

  int nuevoStock = stockActual - cantidadVendida;
  productoAVender->actualizarCantidad(nuevoStock);

  std::cout << "\nVenta Exitosa: " << cantidadVendida << " unidades de "
    << productoAVender->obtenerNombre() << " vendidas. Stock restante: "
    << nuevoStock << ".\n";

  // 3. Notificar a los observadores (DISPARO DEL PATRON OBSERVER)
  // Esto hace que la clase AlertaStockBajo revise el nuevo stock.
  notificar(*productoAVender);
}

bool
GestorInventario::cargarProductosDesdeJson(const std::string& nombreArchivo) {
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

    if (j.is_array()) {
      for (const auto& elemento : j) {
        // 1. Extraer los datos
        std::string codigo = elemento.at("codigo").get<std::string>();
        std::string nombre = elemento.at("nombre").get<std::string>();
        float precio = elemento.at("precio").get<float>();
        int cantidad = elemento.at("cantidad").get<int>();

        // 2. Uso del Factory Method para crear el objeto
        // El Factory decide qué tipo de objeto crear (Producto o ProductoDeFarmacia)
        auto nuevoProducto = ProductoFactory::crearProducto(codigo, nombre,
        precio, cantidad);

        // 3. Almacenar
        listaProductos.push_back(nuevoProducto);
      }
      std::cout << "Inventario cargado exitosamente. Total de productos: "
      << listaProductos.size() << "\n";
      return true;
    }
    // ... (Manejo de errores) ...
  }
  catch (const json::exception& e) {
    std::cerr << "Error al parsear JSON: " << e.what() << "\n";
    return false;
  }
}

// Metodo simple de prueba
void
GestorInventario::mostrarInventario() const {
  std::cout << "\n--- Inventario Actual ---\n";
  for (const auto& p : listaProductos) {
    std::cout << "Cod: " << p->obtenerCodigo()
      << " | Nombre: " << p->obtenerNombre()
      << " | Precio: $" << p->obtenerPrecio()
      << " | Stock: " << p->obtenerCantidad()
      << " | Tipo: " << p->obtenerTipo() // Muestra si es General o Farmacia
      << "\n";
  }
  std::cout << "-------------------------\n";
}