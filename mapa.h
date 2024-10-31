#ifndef MAPA_H
#define MAPA_H

#include <SFML/Graphics.hpp>
#include <string>

const int maxRutas = 10;  // Cambia según sea necesario
const int maxPuntos = 100; // Cambia según sea necesario

class Mapa {
public:
    Mapa();
    void MostarImagen();

private:
    int cantidadRutas;
    int cantidadPuntos[maxRutas];
    sf::Color coloresRutas[maxRutas];
    sf::Vector2f puntos[maxPuntos * maxRutas]; // Almacena las posiciones de los puntos
};

#endif // MAPA_H
