#ifndef COLICIONES_H
#define COLICIONES_H

#include <SFML/Graphics/Rect.hpp>
class Coliciones {

private:
public:
  // OBTENER LOS LIMITES GLOBALES
  virtual sf::FloatRect obtenerLimites() const = 0;
  // COMPROBAR SI SE ESTAN TOCANDO ESOS LIMINTES
  bool estaColicionando(const Coliciones &) const;
};

#endif // !DEBUG
