#pragma once
#include "Producto.h"
#include "Prerequisites.h"
#include "ObserverPattern/Sujeto.h"

class
GestorInventario : public Sujeto {
public:
  GestorInventario();

  // Metodo para cargar el archivo JSON
  bool cargarProductosDesdeJson(const std::string& nombreArchivo);

  // Metodos para el manejo del inventario (compra, venta, etc.)
  void mostrarInventario() const;

  // Funcionalidad de Compra
  void realizarCompra(const std::string& codigoProducto, int cantidadComprada);

  // Funcionalidad para AGREGAR un nuevo producto
  void agregarProducto(
    const std::string& codigo,
    const std::string& nombre,
    float precio,
    int cantidad
  );

  // Funcionalidad para EDITAR un producto existente
  bool editarProducto(
    const std::string& codigo,
    const std::string& nuevoNombre,
    float nuevoPrecio,
    int nuevaCantidad
  );

  // Funcionalidad para ELIMINAR un producto existente
  bool eliminarProducto(const std::string& codigo);

  // Funcionalidad de venta (que activara la notificacion)
  void realizarVenta(const std::string& codigoProducto, int cantidadVendida);

  // Implementacion de los metodos de Sujeto (Observer Pattern)
  void adjuntar(std::shared_ptr<Observador> observador) override;
  void separar(std::shared_ptr<Observador> observador) override;
  void notificar(const Producto& producto) override;

private:
  // Vector de punteros inteligentes para manejar los productos
  std::vector<std::shared_ptr<Producto>> listaProductos;
  // Contenedor para los observadores (los suscriptores de las alertas)
  std::vector<std::shared_ptr<Observador>> listaObservadores;
};
