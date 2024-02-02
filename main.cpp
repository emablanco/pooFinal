#include "avion.h"
#include "avionFinal.h"
#include "balas.h"
#include "balasFuria.h"
#include "base.h"
#include "chatarra.h"
#include "defenza.h"
#include "escudo.h"
#include "furia.h"
#include "humo.h"
#include "meteoro.h"
#include "nave.h"
#include "objetos.h"
#include "superBala.h"
#include "vida.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
#include <utility>
#include <vector>

// CREAR UN DISPAROS PARA UN AVION CADA UN TIEMPO DETERMINADO
void superDisparosEnemigos(Base &, std::vector<Objetos *> &, int &, int &,
                           const sf::Vector2f &, const std::string &,
                           const sf::Vector2f &);
void destruirDefenza(Base &, std::vector<Objetos *> &, Nave *,
                     std::vector<Objetos *> &, const std::string &, int &,
                     const sf::Vector2f &, Objetos *, int &);

void destruirVida(Base &, std::vector<Objetos *> &, Nave *,
                  std::vector<Objetos *> &, const std::string &, int &,
                  const sf::Vector2f &, int &);
void destruirFuria(Base &, std::vector<Objetos *> &, Nave *,
                   std::vector<Objetos *> &, const std::string &, int &,
                   const sf::Vector2f &, int &);

// BUSCAR UNA POSICION FUERA DE LA VISION DE LA NAVE
sf::Vector2f posicionAleatoria(const sf::Vector2f &, const sf::Vector2f &);

// DESTRUIR NAVES QUE NO TENGAN VIDA
void destruirNaves(std::vector<Nave *> &);

// DESTRUIR DISPAROS QUE IMPACTAN O QUE SALEN DE LA VENTANA
void destruirObjetos(std::vector<Objetos *> &, const sf::Vector2f &);

// SI UN DISPARO DEL ENEMIGO IMPACTA EN MI NAVE
void comprobarColiciones(std::vector<Objetos *> &, Nave *, const sf::Vector2f &,
                         const int &, Objetos *);

// CREAR VIDA FUERA DEL AREA DE VISION DEL PERSONAJE
void crearVida(Base &, std::vector<Objetos *> &, int &, int &, Nave *,
               const std::string &, const sf::Vector2f &);
// CREAR DEFENZA FUERA DEL AREA DE VISION DEL PERSONAJE
void crearDefenza(Base &, std::vector<Objetos *> &, int &, int &, Nave *,
                  const std::string &, const sf::Vector2f &);
// CREAR FURIA FUERA DEL AREA DE VISION DEL PERSONAJE
void crearFuria(Base &, std::vector<Objetos *> &, int &, int &, Nave *,
                const std::string &, const sf::Vector2f &);
// CREAR METEOROS FUERA DEL AREA DE VISION DEL PERSONAJE
void crearMeteoros(Base &, std::vector<Objetos *> &, int &, int &, Nave *,
                   const std::string &, const sf::Vector2f &, float,
                   int vida = 1000);
// COMPROBAR SI EL METEORO IMPACTA O SALE FUERA DEL MAPA PARA DESTRUIRLO
void destruirMeteoro(Base &, std::vector<Objetos *> &, Nave *,
                     std::vector<Nave *> &, std::vector<Objetos *> &,
                     const std::string &, int &, const sf::Vector2f &,
                     Objetos *, std::vector<Objetos *> &, std::string,
                     std::vector<Objetos *> &, std::string);

// ELIMINAR LAS EXPLOCIONES CUANDO DESAPARECEN
void destruirHumos(std::vector<Objetos *> &, const float &,
                   const sf::Vector2f &);

// SI UN SUPER DISPARO DEL ENEMIGO IMPACTA EN MI NAVE
void comprobarColicionesSuper(Base &, std::vector<Objetos *> &disparos,
                              Nave *avion, const sf::Vector2f &resolucion,
                              const int &resta, Objetos *escudo,
                              std::vector<Objetos *> &humo_simple,
                              std::string ruta);

// COMPROBAR SI MI DISPARO IMPACTA CON EL OBJETIVO O SALE DE LA VENTANA
void comprobarColiciones(Base &, std::vector<Objetos *> &,
                         std::vector<Nave *> &, const int &,
                         std::vector<Objetos *> &, const std::string &,
                         const sf::Vector2f &, int &);

// CREAR ENEMIGO FUERA DEL AREA DE VISION DE LA NAVE
void crearSuperEnemigo(const sf::Vector2f &resolucion, const std::string &ruta,
                       std::vector<Nave *> &enemigos,
                       const sf::Vector2f &posicion_avion, int vida);
// CREAR ENEMIGO FUERA DEL AREA DE VISION DE LA NAVE
void crearEnemigo(const sf::Vector2f &, const std::string &,
                  std::vector<Nave *> &, const sf::Vector2f &, int vida = 500);
// CREAR UN DISPAROS PARA UN AVION CADA UN TIEMPO DETERMINADO
void crearDisparosEnemigos(Base &, std::vector<Objetos *> &, int &, int &,
                           const sf::Vector2f &, const std::string &,
                           const sf::Vector2f &);

// CREAR UN DISPARO CUANDO SE TOCA EL CLIC IZQUIERDO
void eventoSuper(Base &juego, const sf::Vector2f posicionAvion,
                 int &miAtaqueEspecial_delay,
                 std::vector<Objetos *> &super_balas,
                 const std::string &ruta_superDisparo, int &puntos_rojo);
// CREAR UN DISPARO CUANDO SE TOCA EL CLIC IZQUIERDO
void eventoMouse(Base &, const sf::Vector2f &, int &, std::vector<Objetos *> &,
                 const std::string &);

// CONTROLAR EVENTOS TECLAS
void tecladoPlayer1(Base &, Nave *, const sf::Vector2f &, const sf::Vector2f &);

// SI LA DISTANCIA DEL ENEMIGO ES MENOR A LA ESPECIFICADA EL ENEMIGO TE
// BUSCARA
void calcularDistanciaEnemigo(Nave *, const sf::Vector2f &, const int &);

void actualizarSprites(std::vector<Objetos *> &objetos);
void actualizarSprites(std::vector<Nave *> &naves);

// COMPROBAR EL SUPER DISPARO IMPACTA CON EL OBJETIVO O SALE DE LA VENTANA
void comprobarSuperColiciones(Base &, std::vector<Objetos *> &,
                              std::vector<Nave *> &, const int &,
                              std::vector<Objetos *> &, const std::string &,
                              const sf::Vector2f &, int &);

int main(int argc, char *argv[]) {

  srand(time(NULL)); // Para que los numeros sean sean siempre aleatorio (rand);

  sf::Vector2f velocidad = {5, 5}; // velocidad del avion
  sf::Vector2f posicion_miAviom = {0, 0};
  int vida_miAvion = 1000;

  int vida_enemigo = 500;
  int vida_superEnemigo = 2000;
  int vida_meteoro = 10000;
  float velocidad_meteoro = 5.0;
  float alpha = 0.1; // hacer las imagenes transparente

  int resta_miDisparoSimple = 1000;
  int resta_miDisparoSuper = 100;
  int resta_enemigoDisparoSimple = 100;
  int resta_enemigoDisparoSuper = 100;

  // ------------- TIEMPO QUE SE MOSTRARA EN PANTALLA LOS PUNTOS
  // --------------------------
  // -- cotador para mostrar los puntos plus recibidos
  float delay_r = 0; // para controlar cuanto tiempo estara el texto rojo
  float delay_v = 0; // para controlar cuanto tiempo estara el texto verde
  float delay_a = 0; // para controlar cuanto tiempo estara el texto azul
  //------------------------------------------------------------------------------------

  int superEnemigos_delay = 0; // contador para crear SuperEnemigos
  int superEnemigos_tiempoDisparo =
      rand() % 500 + 100;         // Cuando se genera un disparo
  int miDisparos_delay = 0;       // contador - delay de mis disparos
  int miAtaqueEspecial_delay = 0; // contador - delay de mis ataques especiales
  int disparosEnemigos_delay = 0; // contador - delay disparos enemigos
  int meteoros_delay = 0;         // contador - delay para crear meteoros
  int meteoros_tiempo = rand() % (500) + 100; // Creara un meteoros
  int plusAzul_delay = 0; // contador - crear ayuda azul(defenza)
  int plusAzul_tiempo = rand() % (2000) + 333; // cuando aparecera la ayuda azul
  int plusVerde_delay = 0; // contador - crear ayuda verde(vida)
  int plusVerde_tiempo =
      rand() % (2000) + 333; // cuando aparecera la ayuda verde
  int plusRojo_delay = 0;    // contador - crear ayuda roja(ataque especial)
  int plusRojo_tiempo = rand() % (2000) + 333; // cuando aparecera la ayuda roja
  int enemigos_muertos = 0;          // cantidad de enemigos_muertos Inicial
  int tiempo = rand() % (500) + 100; // cada cuanto disparara el enemigo
  int distancia_permitida = 900;     // area de vision de los aviones enemigo
                                     //
                                     //
  // CANTIDAD DE VECES QUE TOMO UN OBJETO PLUS
  int puntos_verde = 0; // aparecera un numero junto al avion de color verde
  int puntos_rojo = 0;  // aparecera un numero junto al avion de color rojo
  int puntos_azul = 0;  // aparecera un numero junto al avion de color azul

  // se usa para mostrar en pantalla los puntos plus
  int rojo = 0;                    // puntos que recibe por objetos plus
  int verde = 0;                   // puntos que recibe por objetos plus
  int azul = 0;                    // puntos que recibe por objetos plus;
                                   //
  int miAvion = rand() % (12) + 1; //

  //------------------ RUTA DE LAS IMAGENES PARA LAS TEXTURAS ----------------
  std::string ruta_plusRojo = "./imagen/plus/rojo.png";        // plus
  std::string ruta_plusVerde = "./imagen/plus/verde.png";      // plus
  std::string ruta_plusAzul = "./imagen/plus/azul.png";        // plus
  std::string ruta_explocion = "./imagen/humo/exp.png";        // explocion
  std::string ruta_humoFuego = "./imagen/humo/humo1.png";      // explocion
  std::string ruta_humoRojo = "./imagen/humo/humo_rojo.png";   // explocion
  std::string ruta_humoVerde = "./imagen/humo/humo_verde.png"; // explocion
  std::string ruta_humoAzul = "./imagen/humo/humo_azul.png";   // explocion
  std::string ruta_humoSimple = "./imagen/humo/humo0.png";     // simple
  std::string ruta_meteoro = "./imagen/meteoro/meteoro.png";   // meteo
  std::string ruta_escudo = "./imagen/escudo/escudo.png";
  std::string ruta_superDisparo = "./imagen/disparos/tiro_azul.png"; // furia
  std::string ruta_superDisparox3 = "./imagen/disparos/x3.png";      // Enemigos
  std::string ruta_avionEnemigo = "./imagen/avion1/"; // aviones enemigos
  std::string ruta_superAviones = "./imagen/avion2/nave";
  std::string ruta_wallpapers = "./imagen/wallpapers/wallapapers1.jpg";
  std::string ruta_areaMovimiento = "./imagen/wallpapers/wallapapers2.png";
  std::string ruta_miAvion =
      "./imagen/avion1/" + std::to_string(miAvion) + ".png";

  //-------------------- CREANDO JUEGO ------------------------------------
  sf::Texture *areaMovimiento = new sf::Texture; // area de movimiento
  areaMovimiento->loadFromFile(ruta_areaMovimiento);
  sf::Vector2f resolucion = sf::Vector2f(areaMovimiento->getSize());
  Base juego(ruta_wallpapers, areaMovimiento);

  //------------------------ MI AVION----------------------------------
  Nave *avion =
      new Avion(ruta_miAvion, posicion_miAviom, velocidad, vida_miAvion);

  // ESCUDO
  Objetos *escudo =
      new Escudo(ruta_escudo, avion->posicionSprite(), velocidad.x);

  //----------- CONTENEDORES ------------------------------------------------
  std::vector<Objetos *> disparosMios;     // Almacenar disparos mios
  std::vector<Objetos *> super_balas;      // Almacenar disparos mios
  std::vector<Objetos *> disparosEnemigos; // Almacenar disparos enemigos
  std::vector<Objetos *> chatarra;         // Almacenar chatarra/explocion
  std::vector<Objetos *> fuego;            // Almacenar chatarra/explocion
  std::vector<Objetos *> humo_verde;       // Almacenar chatarra/explocion
  std::vector<Objetos *> humo_azul;        // Almacenar chatarra/explocion
  std::vector<Objetos *> humo_rojo;        // Almacenar chatarra/explocion
  std::vector<Objetos *> humo_simple;      // Almacenar chatarra/explocion
  std::vector<Objetos *> meteoro;          // Almacenar meteoro
  std::vector<Objetos *> vidas;            // Almacenar PLUS VIDA (VERDE)
  std::vector<Objetos *> defenzas;         // Almacenar PLUS DEFENZA (AZUL)
  std::vector<Objetos *> furias;           // Almacenar PLUS ROJO (ROJO)
  std::vector<Nave *> enemigos;            // alamacenar enemigos
  std::vector<Nave *> superEnemigos;       // alamacenar Super Enemigos
  std::vector<Objetos *> superDisparos; // Almacenar disparos de Super Enemigos

  //------------------- CONFIGURACIONES
  //-----------------------------------------
  //
  //

  std::ifstream archivo("./configuraciones/config.txt");

  if (archivo.is_open()) {
    std::string cadena;
    std::string opcion;

    while (std::getline(archivo, cadena)) {
      if (!cadena.empty() and cadena[0] == '_') {
        float valor;
        // Buscamos el símbolo "="
        size_t posicion = cadena.find('=');
        if (posicion != std::string::npos) {
          // Extraemos la subcadena que sigue al símbolo "="
          std::string valor_str = cadena.substr(posicion + 1);
          // Convertimos la subcadena en un valor float
          valor = std::stof(valor_str);
          // escalar
          if (cadena[1] == '1')
            velocidad = {valor, valor};
          if (cadena[1] == '2')
            vida_miAvion = valor;
          if (cadena[1] == '3')
            vida_enemigo = valor;
          if (cadena[1] == '4')
            vida_superEnemigo = valor;
          if (cadena[1] == '5')
            vida_meteoro = valor;
          if (cadena[1] == '6')
            velocidad_meteoro = valor;
          if (cadena[1] == '7')
            resta_miDisparoSimple = valor;
          if (cadena[1] == '8')
            resta_miDisparoSuper = valor;
          if (cadena[1] == '9')
            resta_enemigoDisparoSimple = valor;
          // para donde mira la imagen "Derecha o "izquierda"
          if (cadena[1] == '0')
            resta_enemigoDisparoSuper = valor;
        }
      }
    }
    archivo.close();
  }
  // --------------------------------- INICIAL JUEGO ------------------
  while (juego.estadoVentan()) {

    if (!juego.estadoJuego()) {
      juego.actualizarPosicionMenu();
      juego.dibujarMenu();
    } else {
      if (avion->verEstado()) {

        tecladoPlayer1(juego, avion, resolucion, velocidad);
        // mi avion mira donde esta el mouse
        avion->apuntar(juego.posicionMouse(),
                       juego.posicionSprite(avion->posicionSprite()));
        // si apreto la tecla izquierda del nouse genera un disparo
        eventoMouse(juego, avion->posicionSprite(), miDisparos_delay,
                    disparosMios, ruta_miAvion);
        // si apreto la tecla derecha genere un ataque especial
        eventoSuper(juego, avion->posicionSprite(), miAtaqueEspecial_delay,
                    super_balas, ruta_superDisparo, puntos_rojo);

        // cambio la posicion del escudo a donde esta el avion
        escudo->modificarDireccion(avion->posicionSprite());
        // actualizo el la posicion del escudo
        escudo->moverObjeto();
        // cargo el esprite dentro de la clase padre
        escudo->updateSprite();

        //------------ CANTIDAD MINIMA DE ENEMIGOS ---------------------------

        // los enemigos aumentaran conforme mate.
        while (enemigos.size() <= (enemigos_muertos / 10)) {
          int n = rand() % (42) + 1; // IMAGEN ENEMIGO SIMPLE
          std::string aux = ruta_avionEnemigo + std::to_string(n) + ".png";
          // CREAR ENEMIGOS SIMPLE
          crearEnemigo(resolucion, aux, enemigos, avion->posicionSprite(),
                       vida_enemigo);
          // CREAR SUPER ENEMIGOS
          if (enemigos_muertos % 10 == 0) {
            n = rand() % (5) + 1; // IMAGEN ENEMIGO SUPER
            aux = ruta_superAviones + std::to_string(n) + ".png";
            crearSuperEnemigo(resolucion, aux, superEnemigos,
                              avion->posicionSprite(), vida_superEnemigo);
          }
        }
        avion->updateSprite(); // actualiza el sprite

        // ----------------------------------ENEMIGOS SIMPLES
        for (auto &enemigo : enemigos) {
          // si aparezco en su campo de vision me seguira automaticamente
          calcularDistanciaEnemigo(enemigo, avion->posicionSprite(),
                                   distancia_permitida);
          if (enemigo->verBuscar()) {
            // obtiene mi posicion, apunta y dispara
            sf::Vector2f dir = juego.direccionNormalizada(
                avion->posicionSprite(), enemigo->posicionSprite());
            enemigo->seguirObjetivo(dir, avion->posicionSprite(),
                                    avion->tamanioSprite());
            enemigo->apuntar(juego.posicionSprite(avion->posicionSprite()),
                             juego.posicionSprite(enemigo->posicionSprite()));
            crearDisparosEnemigos(juego, disparosEnemigos,
                                  disparosEnemigos_delay, tiempo,
                                  avion->posicionSprite(), enemigo->verRuta(),
                                  enemigo->posicionSprite());
          }
          enemigo->updateSprite(); // actualiza el sprite
        }

        // ------------------------------------ SUPER ENEMIGOS

        for (auto &enemigo : superEnemigos) {
          // si aparezco en su campo de vision
          calcularDistanciaEnemigo(enemigo, avion->posicionSprite(),
                                   distancia_permitida);
          if (enemigo->verBuscar()) {
            // obtiene mi posicion, apunta y dispara
            sf::Vector2f dir = juego.direccionNormalizada(
                avion->posicionSprite(), enemigo->posicionSprite());
            enemigo->seguirObjetivo(dir, avion->posicionSprite(),
                                    avion->tamanioSprite());
            enemigo->apuntar(juego.posicionSprite(avion->posicionSprite()),
                             juego.posicionSprite(enemigo->posicionSprite()));
            superDisparosEnemigos(juego, superDisparos, superEnemigos_delay,
                                  superEnemigos_tiempoDisparo,
                                  avion->posicionSprite(), ruta_superDisparox3,
                                  enemigo->posicionSprite());
          }
          enemigo->updateSprite(); // actualiza sprite
        }

        //------------------- CREAR AYUDA (VIDA, DEFENZA, ATAQUE ESPECIAL)
        crearMeteoros(juego, meteoro, meteoros_delay, meteoros_tiempo, avion,
                      ruta_meteoro, resolucion, velocidad_meteoro,
                      vida_meteoro);
        crearDefenza(juego, defenzas, plusAzul_delay, plusAzul_tiempo, avion,
                     ruta_plusAzul, resolucion);
        crearVida(juego, vidas, plusVerde_delay, plusVerde_tiempo, avion,
                  ruta_plusVerde, resolucion);
        crearFuria(juego, furias, plusRojo_delay, plusRojo_tiempo, avion,
                   ruta_plusRojo, resolucion);

      } else {
        juego.actualizarPosicionGameOver();
      }

      actualizarSprites(disparosMios);     // MIS DISPAROS
      actualizarSprites(disparosEnemigos); // DISPAROS DE AVIONES ENEMIGOS
      actualizarSprites(superDisparos);    // de los super aviones
      actualizarSprites(super_balas);      // MI DISPARO ESPECIAL

      // ----------------- DESTRUIR METEOROS Y AYUDAS CUANDO IMPACTAN O SALEN DE
      // LA PANTALLA ---------------------------------
      destruirMeteoro(juego, meteoro, avion, enemigos, chatarra, ruta_explocion,
                      enemigos_muertos, resolucion, escudo, fuego,
                      ruta_humoFuego, humo_simple, ruta_humoSimple);
      destruirVida(juego, vidas, avion, humo_verde, ruta_humoVerde,
                   puntos_verde, resolucion, verde);
      destruirDefenza(juego, defenzas, avion, humo_azul, ruta_humoAzul,
                      puntos_azul, resolucion, escudo, azul);
      destruirFuria(juego, furias, avion, humo_rojo, ruta_humoRojo, puntos_rojo,
                    resolucion, rojo);

      //------------ el humo desaparece lentamente
      //------------------------------------------
      destruirHumos(chatarra, alpha, resolucion);
      destruirHumos(humo_simple, alpha, resolucion);
      destruirHumos(fuego, alpha, resolucion);
      destruirHumos(humo_azul, alpha, resolucion);
      destruirHumos(humo_verde, alpha, resolucion);
      destruirHumos(humo_rojo, alpha, resolucion);

      //---------------------------- COMPROBAR LAS COLICIONES DE LOS DISPAROS
      // comprobar coliciones de mis disparos simples
      comprobarColiciones(juego, disparosMios, enemigos, resta_miDisparoSimple,
                          chatarra, ruta_explocion, resolucion,
                          enemigos_muertos);
      // comprobar coliciones de mis disparos con SuperEnemigo
      comprobarColiciones(juego, disparosMios, superEnemigos,
                          resta_miDisparoSimple, chatarra, ruta_explocion,
                          resolucion, enemigos_muertos);
      // comprobar coliciones de mis super disparos con superEnemigos
      comprobarSuperColiciones(juego, super_balas, superEnemigos,
                               resta_miDisparoSuper, chatarra, ruta_explocion,
                               resolucion, enemigos_muertos);
      // comprobar coliciones de mis super disparos con enemigos simples
      comprobarSuperColiciones(juego, super_balas, enemigos,
                               resta_miDisparoSuper, chatarra, ruta_explocion,
                               resolucion, enemigos_muertos);
      // comprobar coliciones de los disparos de mis enemigos simples
      comprobarColiciones(disparosEnemigos, avion, resolucion,
                          resta_enemigoDisparoSimple, escudo);
      // comprobar coliciones de los disparos de mis Super Enemigos
      comprobarColicionesSuper(juego, superDisparos, avion, resolucion,
                               resta_enemigoDisparoSuper, escudo, humo_simple,
                               ruta_humoSimple);

      // ------------------ DIBUJAR
      // -------------------------------------------------------------------------------
      juego.actualizarPuntos(enemigos_muertos * 100);
      juego.actualizarEscudo(escudo->verValor());
      juego.actualizarVida(avion->verVida());
      juego.actualizarFuria(puntos_rojo);
      juego.actualizarMasVida(verde);
      juego.actualizarMasDefenza(azul);
      juego.actualizarMasFuria(rojo);
      juego.actualizarPosicionTextos();
      juego.actualizarVivo(avion->verEstado());
      juego.dibujar(avion, disparosMios, enemigos, disparosEnemigos, chatarra,
                    meteoro, escudo, vidas, defenzas, furias, humo_verde,
                    humo_azul, humo_rojo, fuego, super_balas, superEnemigos,
                    superDisparos, humo_simple);

      //  DIBUJAR -> ver arriba del avion los puntos PLUS recibidos
      if (juego.verEstadoVida()) {
        if (delay_v >= 30) {
          delay_v = 0;
          verde = 0;
        } else {
          delay_v += alpha;
        }
      }

      if (juego.verEstadoEscudo()) {
        if (delay_a >= 30) {
          delay_a = 0;
          azul = 0;
        } else {
          delay_a += alpha;
        }
      }
      if (juego.verEstadoFuria()) {
        if (delay_r >= 30) {
          delay_r = 0;
          rojo = 0;
        } else {
          delay_r += alpha;
        }
      }
    }
  }
  // ------- DESTRUIR LOS PUNTEROS ------------------------------------------
  delete avion;

  for (size_t i = 0; i < disparosMios.size(); i++)
    delete disparosMios[i];
  for (size_t i = 0; i < enemigos.size(); i++)
    delete enemigos[i];
  for (size_t i = 0; i < disparosEnemigos.size(); i++)
    delete disparosEnemigos[i];
  for (size_t i = 0; i < chatarra.size(); i++)
    delete chatarra[i];
  for (size_t i = 0; i < meteoro.size(); i++)
    delete meteoro[i];
  for (size_t i = 0; i < super_balas.size(); ++i)
    delete super_balas[i];
  for (size_t i = 0; i < fuego.size(); ++i)
    delete fuego[i];
  for (size_t i = 0; i < humo_verde.size(); ++i)
    delete humo_verde[i];
  for (size_t i = 0; i < humo_azul.size(); ++i)
    delete humo_azul[i];
  for (size_t i = 0; i < humo_rojo.size(); ++i)
    delete humo_rojo[i];
  for (size_t i = 0; i < vidas.size(); ++i)
    delete vidas[i];
  for (size_t i = 0; i < defenzas.size(); ++i)
    delete defenzas[i];
  for (size_t i = 0; i < furias.size(); ++i)
    delete furias[i];
  for (size_t i = 0; i < humo_simple.size(); ++i)
    delete humo_simple[i];

  return 0;
}

// -------------------------------------- FUNCIONES
// ---------------------------------------------------------------------------------
//
//
// COMPROBAR EL SUPER DISPARO IMPACTA CON EL OBJETIVO O SALE DE LA VENTANA
void comprobarSuperColiciones(Base &juego, std::vector<Objetos *> &disparos,
                              std::vector<Nave *> &enemigos, const int &resta,
                              std::vector<Objetos *> &chatarra,
                              const std::string &ruta,
                              const sf::Vector2f &resolucion,
                              int &enemigos_muertos) {
  for (auto &disparo : disparos) {
    for (auto &enemigo : enemigos) {
      if (disparo->verEstado() and disparo->estaColicionando(*enemigo)) {
        enemigo->modificarVida(enemigo->verVida() - resta);

        if (!enemigo->verEstado()) {
          ++enemigos_muertos;
          chatarra.emplace_back(new Chatarra(ruta, enemigo->posicionSprite()));
          juego.sonidoExplocion1();
        }
      }
      destruirNaves(enemigos);
    }
  }
  destruirObjetos(disparos, resolucion);
}
// CREAR UN DISPARO CUANDO SE TOCA EL CLIC DERECHO
void eventoSuper(Base &juego, const sf::Vector2f posicionAvion,
                 int &miAtaqueEspecial_delay,
                 std::vector<Objetos *> &super_balas,
                 const std::string &ruta_superDisparo, int &puntos_rojo) {
  if (puntos_rojo > 0) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) and
        miAtaqueEspecial_delay >= 20) {
      super_balas.emplace_back(
          new SuperBalas(ruta_superDisparo, posicionAvion,
                         juego.direccionNormalizada(posicionAvion), 9.0f));
      juego.sonidoSuperDisparo();
      --puntos_rojo;
      miAtaqueEspecial_delay = 0;
    }
    ++miAtaqueEspecial_delay;
  }
}
void actualizarSprites(std::vector<Objetos *> &objetos) {
  for (auto &objeto : objetos) {
    objeto->moverObjeto();
    objeto->updateSprite();
  }
}

void actualizarSprites(std::vector<Nave *> &naves) {
  for (auto &nave : naves) {
    nave->moverImagen();
    nave->updateSprite();
  }
}

// BUSCAR UNA POSICION FUERA DE LA VISION DE LA NAVE
sf::Vector2f posicionAleatoria(const sf::Vector2f &posicion_avion,
                               const sf::Vector2f &resolucion) {

  // 1080 / 2 = 540, 740 / 2 = 370
  sf::IntRect rec_posicion(posicion_avion.x - resolucion.x / 2,
                           posicion_avion.y - resolucion.y / 2, resolucion.x,
                           resolucion.y);
  sf::Vector2f posicion;
  do {
    posicion.x = rand() % (int)(resolucion.x * 2) - resolucion.x;
    posicion.y = rand() % (int)(resolucion.y * 2) - resolucion.y;
  } while (rec_posicion.contains(posicion.x, posicion.y));

  return posicion;
}

// DESTRUIR NAVES QUE NO TENGAN VIDA
void destruirNaves(std::vector<Nave *> &naves) {
  naves.erase(std::remove_if(naves.begin(), naves.end(),
                             [](Nave *n) -> bool { return !n->verEstado(); }),
              naves.end());
}

// DESTRUIR DISPAROS QUE IMPACTAN O QUE SALEN DE LA VENTANA
void destruirObjetos(std::vector<Objetos *> &objeto,
                     const sf::Vector2f &resolucion) {
  objeto.erase(std::remove_if(objeto.begin(), objeto.end(),
                              [resolucion](Objetos *p) -> bool {
                                return p->verPosicion().x < -resolucion.x or
                                       p->verPosicion().x > resolucion.x or
                                       p->verPosicion().y < -resolucion.y or
                                       p->verPosicion().y > resolucion.y or
                                       !p->verEstado();
                              }),
               objeto.end());
}

// SI UN SUPER DISPARO DEL ENEMIGO IMPACTA EN MI NAVE
void comprobarColicionesSuper(Base &juego, std::vector<Objetos *> &disparos,
                              Nave *avion, const sf::Vector2f &resolucion,
                              const int &resta, Objetos *escudo,
                              std::vector<Objetos *> &humo_simple,
                              std::string ruta) {
  for (auto &disparo : disparos) {
    if (disparo->verEstado() and disparo->estaColicionando(*avion)) {
      if (escudo->verEstado()) {
        escudo->modificarValor(escudo->verValor() - resta);
        juego.sonidoEscudo();
        humo_simple.emplace_back(new Chatarra(ruta, avion->posicionSprite()));
      } else {
        avion->modificarVida(avion->verVida() - resta);
      }
      disparo->modificarEstado(false);
      destruirObjetos(disparos, resolucion);
    }
  }
}

// SI UN DISPARO DEL ENEMIGO IMPACTA EN MI NAVE
void comprobarColiciones(std::vector<Objetos *> &disparos, Nave *avion,
                         const sf::Vector2f &resolucion, const int &resta,
                         Objetos *escudo) {
  for (auto &disparo : disparos) {
    if (disparo->verEstado() and disparo->estaColicionando(*avion)) {
      if (escudo->verEstado())
        escudo->modificarValor(escudo->verValor() - resta);
      else
        avion->modificarVida(avion->verVida() - resta);
      disparo->modificarEstado(false);
      destruirObjetos(disparos, resolucion);
    }
  }
}

// CREAR VIDA FUERA DEL AREA DE VISION DEL PERSONAJE
void crearVida(Base &juego, std::vector<Objetos *> &vida, int &delay,
               int &tiempo, Nave *avion, const std::string &ruta,
               const sf::Vector2f &resolucion) {
  // POSICION FUERA DEL AREA DE VISION DEL PERSONAJE
  sf::Vector2f posicion =
      posicionAleatoria(avion->posicionSprite(), resolucion);
  if (delay >= tiempo) {
    vida.emplace_back(new Vida(
        ruta, posicion,
        juego.direccionNormalizada(avion->posicionSprite(), posicion)));
    delay = 0;
    tiempo = rand() % (10000) + 3333;
  }
  ++delay;
}

// CREAR DEFENZA FUERA DEL AREA DE VISION DEL PERSONAJE
void crearDefenza(Base &juego, std::vector<Objetos *> &defenza, int &delay,
                  int &tiempo, Nave *avion, const std::string &ruta,
                  const sf::Vector2f &resolucion) {
  // POSICION FUERA DEL AREA DE VISION DEL PERSONAJE
  sf::Vector2f posicion =
      posicionAleatoria(avion->posicionSprite(), resolucion);
  if (delay >= tiempo) {
    defenza.emplace_back(new Defenza(
        ruta, posicion,
        juego.direccionNormalizada(avion->posicionSprite(), posicion)));
    delay = 0;
    tiempo = rand() % (10000) + 3333;
  }
  ++delay;
}

// CREAR FURIA FUERA DEL AREA DE VISION DEL PERSONAJE
void crearFuria(Base &juego, std::vector<Objetos *> &furia, int &delay,
                int &tiempo, Nave *avion, const std::string &ruta,
                const sf::Vector2f &resolucion) {
  // POSICION FUERA DEL AREA DE VISION DEL PERSONAJE
  sf::Vector2f posicion =
      posicionAleatoria(avion->posicionSprite(), resolucion);
  if (delay >= tiempo) {
    furia.emplace_back(new Furia(
        ruta, posicion,
        juego.direccionNormalizada(avion->posicionSprite(), posicion)));
    delay = 0;
    tiempo = rand() % (1000) + 333;
  }
  ++delay;
}

// CREAR METEOROS FUERA DEL AREA DE VISION DEL PERSONAJE
void crearMeteoros(Base &juego, std::vector<Objetos *> &meteoros, int &delay,
                   int &tiempo, Nave *avion, const std::string &ruta,
                   const sf::Vector2f &resolucion, float velocidad, int vida) {
  // POSICION FUERA DEL AREA DE VISION DEL PERSONAJE
  sf::Vector2f posicion =
      posicionAleatoria(avion->posicionSprite(), resolucion);
  if (delay >= tiempo) {
    meteoros.emplace_back(new Meteoro(
        ruta, posicion,
        juego.direccionNormalizada(avion->posicionSprite(), posicion),
        velocidad, vida));
    delay = 0;
    tiempo = rand() % (500) + 100;
  }
  ++delay;
}

// CUANDO IMPACTA SALDRA UN HUMO DEL COLOR QUE IMPACTA..
void destruirVida(Base &juego, std::vector<Objetos *> &ayudas, Nave *avion,
                  std::vector<Objetos *> &humos, const std::string &ruta,
                  int &contador, const sf::Vector2f &resolucion, int &verde) {

  // Mover y actualizar proyectiles
  for (auto &ayuda : ayudas) {

    ayuda->moverObjeto();
    ayuda->updateSprite();

    sf::Vector2f posicion = ayuda->verPosicion();

    if (ayuda->estaColicionando(*avion)) { // MI aviones
      ++contador;
      humos.emplace_back(new Humo(ruta, avion->posicionSprite()));
      avion->modificarVida(avion->verVida() + ayuda->verValor());

      ayuda->modificarEstado(false);
      verde = 1000;

      juego.sonidoExplocion2();
      destruirObjetos(ayudas, resolucion);
    }
    // Verificar si el proyectil salió de la ventana
    if (posicion.x < 0 or posicion.x > resolucion.x or posicion.y < 0 or
        posicion.y > resolucion.y) {
      destruirObjetos(ayudas, resolucion);
    }
  }
}
void destruirFuria(Base &juego, std::vector<Objetos *> &ayudas, Nave *avion,
                   std::vector<Objetos *> &humos, const std::string &ruta,
                   int &contador, const sf::Vector2f &resolucion, int &rojo) {

  // Mover y actualizar proyectiles
  for (auto &ayuda : ayudas) {

    ayuda->moverObjeto();
    ayuda->updateSprite();

    sf::Vector2f posicion = ayuda->verPosicion();

    if (ayuda->estaColicionando(*avion)) { // MI AVIONES
      humos.emplace_back(new Humo(ruta, avion->posicionSprite()));
      ayuda->modificarEstado(false);
      juego.sonidoExplocion2();
      destruirObjetos(ayudas, resolucion);
      ++contador;
      rojo = 1;
    }
    // Verificar si el proyectil salió de la ventana
    if (posicion.x < 0 or posicion.x > resolucion.x or posicion.y < 0 or
        posicion.y > resolucion.y) {
      destruirObjetos(ayudas, resolucion);
    }
  }
}

void destruirDefenza(Base &juego, std::vector<Objetos *> &ayudas, Nave *avion,
                     std::vector<Objetos *> &humos, const std::string &ruta,
                     int &contador, const sf::Vector2f &resolucion,
                     Objetos *defenza, int &azul) {

  // Mover y actualizar proyectiles
  for (auto &ayuda : ayudas) {

    ayuda->moverObjeto();
    ayuda->updateSprite();

    sf::Vector2f posicion = ayuda->verPosicion();

    if (ayuda->estaColicionando(*avion)) { // MI aviones
      humos.emplace_back(new Humo(ruta, avion->posicionSprite()));
      defenza->modificarValor(defenza->verValor() + ayuda->verValor());

      ayuda->modificarEstado(false);
      azul = 1000;

      juego.sonidoExplocion2();
      destruirObjetos(ayudas, resolucion);
      ++contador;
    }
    // Verificar si el proyectil salió de la ventana
    if (posicion.x < 0 or posicion.x > resolucion.x or posicion.y < 0 or
        posicion.y > resolucion.y) {
      destruirObjetos(ayudas, resolucion);
    }
  }
}

// COMPROBAR SI EL METEORO IMPACTA O SALE FUERA DEL MAPA PARA DESTRUIRLO
void destruirMeteoro(Base &juego, std::vector<Objetos *> &meteoros, Nave *avion,
                     std::vector<Nave *> &enemigos,
                     std::vector<Objetos *> &chatarra, const std::string &ruta,
                     int &enemigos_muertos, const sf::Vector2f &resolucion,
                     Objetos *escudo, std::vector<Objetos *> &fuego,
                     std::string ruta2, std::vector<Objetos *> &humo_simple,
                     std::string ruta_meteoro) {
  // Mover y actualizar proyectiles
  for (auto &meteoro : meteoros) {

    meteoro->moverObjeto();
    meteoro->updateSprite();

    sf::Vector2f posicion = meteoro->verPosicion();

    for (auto &enemigo : enemigos) {

      if (meteoro->estaColicionando(*enemigo)) { // AVIONES ENEMIGOS

        meteoro->modificarEstado(false);

        enemigo->modificarVida(enemigo->verVida() - meteoro->verValor());

        if (!enemigo->verEstado()) {

          ++enemigos_muertos;

          chatarra.emplace_back(new Chatarra(ruta, enemigo->posicionSprite()));

          juego.sonidoExplocion1();
        }

        destruirObjetos(meteoros, resolucion);
      }
    }
    if (meteoro->estaColicionando(*avion)) { // MI AVIONES

      humo_simple.emplace_back(
          new Chatarra(ruta_meteoro, avion->posicionSprite()));
      if (escudo->verEstado()) {
        escudo->modificarValor(escudo->verValor() - meteoro->verValor());
        juego.sonidoEscudo();

      } else {
        avion->modificarVida(avion->verVida() - meteoro->verValor());
      }

      fuego.emplace_back(new Chatarra(ruta2, avion->posicionSprite()));

      meteoro->modificarEstado(false);

      juego.sonidoExplocion2();

      destruirObjetos(meteoros, resolucion);
    }

    // Verificar si el proyectil salió de la ventana
    if (posicion.x < 0 or posicion.x > resolucion.x or posicion.y < 0 or
        posicion.y > resolucion.y) {
      destruirObjetos(meteoros, resolucion);
    }

    // ELIMINAR
    destruirNaves(enemigos);
  }
}

// COMPROBAR SI EL METEORO IMPACTA O SALE FUERA DEL MAPA PARA DESTRUIRLO
void destruirMeteoro(Base &juego, std::vector<Objetos *> &meteoros, Nave *avion,
                     std::vector<Nave *> &enemigos,
                     std::vector<Objetos *> &chatarra, const std::string &ruta,
                     int &enemigos_muertos, const sf::Vector2f &resolucion,
                     Objetos *escudo, std::vector<Objetos *> &fuego,
                     std::string ruta2) {
  // Mover y actualizar proyectiles
  for (auto &meteoro : meteoros) {

    meteoro->moverObjeto();
    meteoro->updateSprite();

    sf::Vector2f posicion = meteoro->verPosicion();

    for (auto &enemigo : enemigos) {

      if (meteoro->estaColicionando(*enemigo)) { // AVIONES ENEMIGOS

        meteoro->modificarEstado(false);

        enemigo->modificarVida(enemigo->verVida() - meteoro->verValor());

        if (!enemigo->verEstado()) {

          ++enemigos_muertos;

          chatarra.emplace_back(new Chatarra(ruta, enemigo->posicionSprite()));

          juego.sonidoExplocion1();
        }

        destruirObjetos(meteoros, resolucion);
      }
    }
    if (meteoro->estaColicionando(*avion)) { // MI AVIONES

      if (escudo->verEstado()) {
        escudo->modificarValor(escudo->verValor() - meteoro->verValor());
        juego.sonidoEscudo();

      } else {
        avion->modificarVida(avion->verVida() - meteoro->verValor());
      }

      fuego.emplace_back(new Chatarra(ruta2, avion->posicionSprite()));

      meteoro->modificarEstado(false);

      juego.sonidoExplocion2();

      destruirObjetos(meteoros, resolucion);
    }

    // Verificar si el proyectil salió de la ventana
    if (posicion.x < 0 or posicion.x > resolucion.x or posicion.y < 0 or
        posicion.y > resolucion.y) {
      destruirObjetos(meteoros, resolucion);
    }

    // ELIMINAR
    destruirNaves(enemigos);
  }
}

// ELIMINAR LAS EXPLOCIONES CUANDO DESAPARECEN
void destruirHumos(std::vector<Objetos *> &humos, const float &alpha,
                   const sf::Vector2f &resolucion) {
  for (auto humo : humos) {
    humo->modificarAlpha(alpha);
    humo->updateSprite();
  }
  destruirObjetos(humos, resolucion);
}

// COMPROBAR SI MI DISPARO IMPACTA CON EL OBJETIVO O SALE DE LA VENTANA
void comprobarColiciones(Base &juego, std::vector<Objetos *> &disparos,
                         std::vector<Nave *> &enemigos, const int &resta,
                         std::vector<Objetos *> &chatarra,
                         const std::string &ruta,
                         const sf::Vector2f &resolucion,
                         int &enemigos_muertos) {
  for (auto disparo : disparos) {
    for (auto enemigo : enemigos) {
      if (disparo->verEstado() and disparo->estaColicionando(*enemigo)) {
        enemigo->modificarVida(enemigo->verVida() - resta);
        disparo->modificarEstado(false);

        if (!enemigo->verEstado()) {
          ++enemigos_muertos;
          chatarra.emplace_back(new Chatarra(ruta, enemigo->posicionSprite()));
          juego.sonidoExplocion1();
        }
      }
      destruirNaves(enemigos);
      destruirObjetos(disparos, resolucion);
    }
  }
}
// CREAR ENEMIGO FUERA DEL AREA DE VISION DE LA NAVE
void crearSuperEnemigo(const sf::Vector2f &resolucion, const std::string &ruta,
                       std::vector<Nave *> &enemigos,
                       const sf::Vector2f &posicion_avion, int vida) {
  sf::Vector2f posicion = posicionAleatoria(posicion_avion, resolucion);
  enemigos.emplace_back(new AvionFinal(ruta, posicion, {3, 3}, vida));
}

// CREAR ENEMIGO FUERA DEL AREA DE VISION DE LA NAVE
void crearEnemigo(const sf::Vector2f &resolucion, const std::string &ruta,
                  std::vector<Nave *> &enemigos,
                  const sf::Vector2f &posicion_avion, int vida) {
  sf::Vector2f posicion = posicionAleatoria(posicion_avion, resolucion);
  enemigos.emplace_back(new Avion(ruta, posicion, {3, 3}, vida));
}

// CREAR UN DISPAROS PARA UN AVION CADA UN TIEMPO DETERMINADO
void superDisparosEnemigos(Base &juego, std::vector<Objetos *> &disparos,
                           int &disparosEnemigos_delay, int &tiempo,
                           const sf::Vector2f &enemigo, const std::string &ruta,
                           const sf::Vector2f &avion_posicion) {
  if (disparosEnemigos_delay >= tiempo) {
    disparos.emplace_back(
        new SuperBalas(ruta, avion_posicion,
                       juego.direccionNormalizada(enemigo, avion_posicion)));
    disparosEnemigos_delay = 0;
    juego.sonidoDisparo2();
    tiempo = rand() % (400) + 10;
  }
  ++disparosEnemigos_delay;
}

// CREAR UN DISPAROS PARA UN AVION CADA UN TIEMPO DETERMINADO
void crearDisparosEnemigos(Base &juego, std::vector<Objetos *> &disparos,
                           int &disparosEnemigos_delay, int &tiempo,
                           const sf::Vector2f &enemigo, const std::string &ruta,
                           const sf::Vector2f &avion_posicion) {
  if (disparosEnemigos_delay >= tiempo) {

    disparos.emplace_back(
        new Balas(ruta, avion_posicion,
                  juego.direccionNormalizada(enemigo, avion_posicion)));
    disparosEnemigos_delay = 0;
    juego.sonidoDisparo2();
    tiempo = rand() % (400) + 10;
  }
  ++disparosEnemigos_delay;
}

// CREAR UN DISPARO CUANDO SE TOCA EL CLIC IZQUIERDO
void eventoMouse(Base &juego, const sf::Vector2f &posicion_avion, int &delay,
                 std::vector<Objetos *> &projectiles, const std::string &ruta) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and delay >= 15) {
    projectiles.emplace_back(
        new Balas(ruta, posicion_avion,
                  juego.direccionNormalizada(posicion_avion), 9.0f));
    juego.sonidoDisparo1();
    delay = 0;
  }
  ++delay;
}

// CONTROLAR EVENTOS TECLAS
void tecladoPlayer1(Base &juego, Nave *avion, const sf::Vector2f &resolucion,
                    const sf::Vector2f &velocidad) {
  sf::Vector2f mover;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and
      avion->posicionSprite().y > -(resolucion.y / 2.f)) {
    mover = {0, velocidad.y * -1};
    avion->moverImagen(mover);
    juego.moverVisor(mover);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and
      avion->posicionSprite().y < resolucion.y / 2.f) {
    mover = {0, velocidad.y};
    avion->moverImagen(mover);
    juego.moverVisor(mover);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and
      avion->posicionSprite().x > -(resolucion.x / 2.f)) {
    mover = {velocidad.x * -1, 0};
    avion->moverImagen(mover);
    juego.moverVisor(mover);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and
      avion->posicionSprite().x < resolucion.x / 2.f) {
    mover = {velocidad.x, 0};
    avion->moverImagen(mover);
    juego.moverVisor(mover);
  }
}

// SI LA DISTANCIA DEL ENEMIGO ES MENOR A LA ESPECIFICADA EL ENEMIGO TE
// BUSCARA
void calcularDistanciaEnemigo(Nave *enemigo, const sf::Vector2f &avion_posicion,
                              const int &distancia) {
  sf::Vector2f dir = avion_posicion - enemigo->posicionSprite();
  if (std::abs(dir.x) + std::abs(dir.y) <= distancia) {
    enemigo->modificarBuscar(true);
  }
}
