
#include "nave.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <complex>
#include <utility>

Nave::Nave() {}

const bool Nave::updateSprite() {
  ima_spr = obtenerSprite();
  return true;
}

// DIBUJAR
void Nave::draw(sf::RenderTarget &target, sf::RenderStates states) const {

  target.draw(ima_spr, states);
}

sf::FloatRect Nave::obtenerLimites() const { return limitesNave(); }
