#include "mapa.h"
#include <iostream>
#include <cstring> // Para strcpy, si es necesario
#include <SFML/Graphics.hpp>

// Constructor
using namespace std;
Mapa::Mapa() : contador(0) {}

void Mapa::MostarImagen() {
    // Implementación del método (agrega la lógica que necesites aquí)
    float windowHeight = 1100;
    float windowWidht = 1104;

    sf::RenderWindow window(sf::VideoMode(windowWidht, windowHeight), "Costa Rica MAP");

    sf::Texture texture;
    if (!texture.loadFromFile("C:/Users/Extreme PC/Documents/2024imagenproyecto/costaricamap.png"))
    {
        cout << "No fue posible encontrar el archivo" << endl;
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sprite.setScale(
        windowWidht / texture.getSize().x,
        windowHeight / texture.getSize().y
    );
       

    //Extreme PC

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
