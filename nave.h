#ifndef NAVE_H
#define NAVE_H
#include "coliciones.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp> //para usar ""draw""
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib>
#include <utility>

class Nave : public sf::Drawable, public Coliciones {
private:
  sf::Sprite ima_spr;                            // SPRITE PARA DIBUJAR
  virtual const sf::Sprite &obtenerSprite() = 0; // TRAER EL SPRITE DEL HIJO
  virtual sf::FloatRect limitesNave() const = 0; // LIMITES GLOBALES

public:
  Nave();
  const bool updateSprite(); // CARGAR EL SPRITE HIJO EN ima_spr
  // CONVERTIR NAVE EN DIBUJABLE
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  sf::FloatRect
  obtenerLimites() const override; // SE USA PARA COMPROBAR COLICIONES
  // VIRTUAL METODOS

  // OBTENER POSICION DEL SPRITE -> RETURN SF::VECTOR2F
  virtual const sf::Vector2f posicionSprite() = 0;
  // MOVER SPRITE METODO MOVE
  virtual const void moverImagen() = 0;
  virtual const void moverImagen(sf::Vector2f) = 0;
  // ROTAR IMAHEN -> BOOL
  virtual const bool rotarImagen(const float &) = 0;
  // EL SPRITE MIRA DONDE ESTA EL MOUSE -> VOID
  virtual void apuntar(const sf::Vector2f, const sf::Vector2f) = 0;
  // CAMBIAL LA VELOCIDAD DE MOVIMIENTO
  virtual void cambiarVelocidad(sf::Vector2f) = 0;
  // CAMBIAR POSICION DEL SPRITE
  virtual void cambiarPosicion(sf::Vector2f) = 0;
  // VER LA VELOCIDAD CON LA QUE SE MUEVE EL SPRITE
  virtual sf::Vector2f verVelocidad() = 0;
  // VER LA CANTIDAD DE VIDA
  virtual int verVida() = 0;
  // ACTUALIZAR VIDA
  virtual void modificarVida(int) = 0;
  // POSICION DEL ENEMIGO Y SU TAMANIO
  virtual void seguirObjetivo(sf::Vector2f, sf::Vector2f, sf::Vector2f) = 0;
  // VEREL TAMANIO DE LA TEXTURA
  virtual sf::Vector2f tamanioTextura() = 0;
  // VER EL TAMANIO DEL SPRITE
  virtual sf::Vector2f tamanioSprite() = 0;
  // VER EL ANGULO DE ROTACION
  virtual float obtenerRotacion() = 0;
  // MODIFICAR EL ESTADO DE LA NAVE
  virtual void modificarEstado(bool) = 0;
  // VER EL ESTADO DE LA NAVE
  virtual bool verEstado() = 0;
  // RUTA DE LA IMAGEN
  virtual std::string verRuta() = 0;
  // VER SI ESTA ACTIVA LA BUSQUEDA
  virtual bool verBuscar() = 0;
  // ACTUALIZAR EL ESTADO DE LA BUSQUEDA
  virtual bool modificarBuscar(bool) = 0;
};

#endif // !NAVE_H
