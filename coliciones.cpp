#include "coliciones.h"

bool Coliciones::estaColicionando(const Coliciones &c) const {
  // metodo intersects verifica si se tocan dos rectangulos
  return this->obtenerLimites().intersects(c.obtenerLimites());
}
