
#include "objetos.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <complex>
#include <string>
#include <utility>

Objetos::Objetos() {}
void Objetos::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(spr, states);
}
void Objetos::updateSprite() { spr = obtenerSprite(); }
/**
void Objetos::updateDisparo() { circulo = obtenerDisparo(); }

// DIBUJAR
void Objetos::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(circulo, states);
}
**/
sf::FloatRect Objetos::obtenerLimites() const { return limitesObjetos(); }
