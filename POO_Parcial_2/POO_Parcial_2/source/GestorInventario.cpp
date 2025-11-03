#include "GestorInventario.h"
#include "FactoryMethod/ProductoFactory.h"
#include <algorithm> // Necesario para std::find_if y std::remove_if.
#include <ctime>     // Necesario para obtener la fecha (aunque simulada).
#include <iostream>  // Necesario para la salida de consola (errores/éxitos).

/**
 * @brief Constructor de la clase. Inicializa la referencia al gestor de registros.
 * @param registro Puntero al GestorRegistro para guardar las transacciones.
 */
GestorInventario::
GestorInventario(std::shared_ptr<GestorRegistro> registro) {
  gestorRegistro = registro; // Inicializamos el gestor de registro (composition).
}

// -------------------------------------------------------------------------
// Implementacion de los metodos de Sujeto (Patrón Observer)
// -------------------------------------------------------------------------

void
GestorInventario::adjuntar(std::shared_ptr<Observador> observador) {
  // @brief Añade un nuevo observador a la lista de suscriptores.
  listaObservadores.push_back(observador);
}

void
GestorInventario::separar(std::shared_ptr<Observador> observador) {
  // @brief Remueve un observador de la lista de suscriptores.
  // Implementacion de separacion omitida por complejidad (en el ejemplo).
  // En un proyecto real, se usaria std::remove_if con std::erase.
}

void
GestorInventario::notificar(const Producto& producto) {
  // @brief Itera sobre todos los observadores adjuntos y llama a su método actualizar().
  // Esto les permite reaccionar al cambio de estado del producto (stock).
  for (const auto& observador : listaObservadores) {
    observador->actualizar(producto);
  }
}

// -------------------------------------------------------------------------
// Logica CRUD
// -------------------------------------------------------------------------

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
  // El Factory decide si crear un Producto o un ProductoDeFarmacia (polimorfismo).
  auto nuevoProducto = ProductoFactory::crearProducto(codigo, nombre, precio, cantidad);

  // 3. Agregar a la lista
  listaProductos.push_back(nuevoProducto);

  std::cout << "\n[Inventario] Producto agregado: " << nombre
    << " (Cod: " << codigo << ", Tipo: " << nuevoProducto->obtenerTipo() << ")\n";
}

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
    std::cout << "\nError al Editar: Producto con codigo " << codigo
    << " no encontrado.\n";
    return false;
  }

  std::shared_ptr<Producto> productoAEditar = *it;

  // 2. Aplicar las modificaciones
  productoAEditar->establecerNombre(nuevoNombre); // Setter para nombre
  productoAEditar->establecerPrecio(nuevoPrecio); // Setter para precio
  productoAEditar->actualizarCantidad(nuevaCantidad); // Setter para cantidad (reutilizado)

  std::cout << "\n[Inventario] Producto " << codigo << " editado exitosamente: "
    << nuevoNombre << ", Precio: $" << nuevoPrecio
    << ", Stock: " << nuevaCantidad << ".\n";

  // 3. Notificar a los observadores (por si el nuevo stock es bajo)
  notificar(*productoAEditar);

  return true;
}

bool
GestorInventario::eliminarProducto(const std::string& codigo) {
  // 1. Buscar el producto por codigo usando std::remove_if
  // std::remove_if mueve los elementos que cumplen la condición al final del vector.
  auto it = std::remove_if(listaProductos.begin(), listaProductos.end(),
    [&codigo](const std::shared_ptr<Producto>& p) {
      return p->obtenerCodigo() == codigo;
    });

  // 2. Verificar si se encontró el producto (si 'it' no ha cambiado de posición).
  if (it == listaProductos.end()) {
    std::cout << "\nError al Eliminar: Producto con codigo "
      << codigo << " no encontrado.\n";
    return false;
  }

  // 3. Eliminar los elementos del vector (la parte final con los elementos 'removidos').
  listaProductos.erase(it, listaProductos.end());

  std::cout << "\n[Inventario] Producto con codigo "
    << codigo << " eliminado exitosamente.\n";
  return true;
}

// -------------------------------------------------------------------------
// Logica de Transacciones
// -------------------------------------------------------------------------

void
GestorInventario::realizarCompra(const std::string&
  codigoProducto, int cantidadComprada) {
  // 1. Buscar el producto
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

  // --- 3. Registro de Compra ---
  // Simulacion de obtener precio y fecha actual
  float precioUnitarioCompra = 10.00; // Valor fijo de ejemplo
  std::string fechaActual = "2025-10-31"; // Fecha simulada

  gestorRegistro->registrarCompra(
    codigoProducto,
    cantidadComprada,
    precioUnitarioCompra,
    fechaActual
  );

  std::cout << "\nCompra Exitosa: " << cantidadComprada << " unidades de "
    << productoAComprar->obtenerNombre() << " re-surtidas. Stock total: "
    << nuevoStock << ".\n";
}

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

  // --- 3. Registro de Venta ---
  std::string fechaActual = "2025-10-31"; // Fecha simulada

  gestorRegistro->registrarVenta(
    codigoProducto,
    cantidadVendida,
    productoAVender->obtenerPrecio(), // Usa el precio actual del producto.
    fechaActual
  );

  std::cout << "\nVenta Exitosa: " << cantidadVendida << " unidades de "
    << productoAVender->obtenerNombre() << " vendidas. Stock restante: "
    << nuevoStock << ".\n";

  // 4. Notificar a los observadores (DISPARO DEL PATRON OBSERVER)
  // Esto llama a AlertaStockBajo::actualizar() para verificar el nuevo stock.
  notificar(*productoAVender);
}

// -------------------------------------------------------------------------
// Logica de Persistencia (Carga JSON)
// -------------------------------------------------------------------------

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
        // 1. Extracción de datos del elemento JSON
        std::string codigo = elemento.at("codigo").get<std::string>();
        std::string nombre = elemento.at("nombre").get<std::string>();
        float precio = elemento.at("precio").get<float>();
        int cantidad = elemento.at("cantidad").get<int>();

        // 2. Uso del Factory Method para crear el objeto
        // El Factory decide qué tipo de objeto crear (Producto o ProductoDeFarmacia).
        auto nuevoProducto = ProductoFactory::crearProducto(codigo, nombre,
          precio, cantidad);

        // 3. Almacenar en la lista de productos
        listaProductos.push_back(nuevoProducto);
      }
      std::cout << "Inventario cargado exitosamente. Total de productos: "
        << listaProductos.size() << "\n";
      return true;
    }
  }
  catch (const json::exception& e) {
    std::cerr << "Error al parsear JSON: " << e.what() << "\n";
    return false;
  }
  return false; // Retorno por defecto si el JSON no es un array o hay un error no capturado.
}

// -------------------------------------------------------------------------
// Logica de Visualización
// -------------------------------------------------------------------------

void
GestorInventario::mostrarInventario() const {
  // @brief Itera sobre la lista y muestra los detalles de cada producto.
  std::cout << "\n--- Inventario Actual ---\n";

  // Encabezado de la tabla
  std::cout << "Cod\tNombre\t\tPrecio\tStock\tTipo\n";
  std::cout << "------------------------------------------------\n";

  for (const auto& p : listaProductos) {
    std::cout << p->obtenerCodigo()
      << "\t" << p->obtenerNombre()
      << "\t$" << p->obtenerPrecio()
      << "\t" << p->obtenerCantidad()
      << "\t" << p->obtenerTipo() // Uso de polimorfismo para obtener el tipo correcto.
      << "\n";
  }
  std::cout << "-------------------------\n";
}