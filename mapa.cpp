#include "mapa.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;


Mapa::Mapa() : cantidadRutas(0) {
    for (int i = 0; i < maxRutas; ++i) 
    {
        cantidadPuntos[i] = 0; // 
        coloresRutas[i] = sf::Color::Red; 
    }
}

void Mapa::MostarImagen() {
    float windowHeight = 1000;
    float windowWidth = 1000;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Costa Rica MAP");
    window.setKeyRepeatEnabled(false); 

    sf::Texture texture;
    if (!texture.loadFromFile("C:/Users/Extreme PC/Documents/2024imagenproyecto/costaricamap.png")) 
    {
        cout << "No fue posible encontrar el archivo" << endl;
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(
        windowWidth / texture.getSize().x,
        windowHeight / texture.getSize().y
    );

    sf::CircleShape shapePuntos[maxPuntos * maxRutas]; 
    sf::Text nombres[maxPuntos * maxRutas]; 
    sf::Font font;
    if (!font.loadFromFile("C:/Users/Extreme PC/Documents/2024 Programacion/iNTENTO3sfml/iNTENTO3sfml/Fonts/Roboto-Bold.ttf")) 
    {
        cout << "No fue posible cargar la fuente" << endl;
        return;
    }

    string nombresTabla[maxPuntos * maxRutas]; 
    string nombreActual;
    string nombreRutaActual;
    bool esperandoNombre = false;
    bool esperandoNombreRuta = false;
    int puntoActual = -1;
    int rutaActual = -1; 
    bool mostrandoPaleta = false;

    
    sf::Color coloresDisponibles[] = {
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Magenta,
        sf::Color::Yellow
    };

    
    sf::RectangleShape botonTerminar(sf::Vector2f(200, 50));
    sf::Color botonColorNormal(139, 69, 19); 
    sf::Color botonColorHover(160, 82, 45);  
    botonTerminar.setFillColor(botonColorNormal);
    botonTerminar.setPosition((windowWidth - 400) / 2, windowHeight - 130); 

    sf::Text botonTexto("Terminar Ruta", font, 20);
    botonTexto.setFillColor(sf::Color::White);
    botonTexto.setPosition(
        (windowWidth - 400) / 2 + (200 - botonTexto.getLocalBounds().width) / 2,
        windowHeight - 110 
    );

    
    sf::RectangleShape botonEditarRuta(sf::Vector2f(200, 50));
    botonEditarRuta.setFillColor(botonColorNormal);
    botonEditarRuta.setPosition((windowWidth - 400) / 2 - 220, windowHeight - 130); 

    sf::Text botonTextoEditar("Editar Ruta", font, 20);
    botonTextoEditar.setFillColor(sf::Color::White);
    botonTextoEditar.setPosition(
        (windowWidth - 400) / 2 - 220 + (200 - botonTextoEditar.getLocalBounds().width) / 2,
        windowHeight - 110 
    );

    sf::RectangleShape botonAgregar(sf::Vector2f(200, 50));
    botonAgregar.setFillColor(botonColorNormal);
    botonAgregar.setPosition((windowWidth + 20) / 2, windowHeight - 130); 

    sf::Text botonTextoAgregar("Agregar Ruta Nueva", font, 20);
    botonTextoAgregar.setFillColor(sf::Color::White);
    botonTextoAgregar.setPosition(
        (windowWidth + 20) / 2 + 20 + (200 - botonTextoAgregar.getLocalBounds().width) / 2,
        windowHeight - 110 // Ajustar posición vertical
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Obtener la posición del mouse
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // Comprobar si el mouse está sobre los botones
            bool mouseSobreBotonTerminar = botonTerminar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
            bool mouseSobreBotonEditar = botonEditarRuta.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
            bool mouseSobreBotonAgregar = botonAgregar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

            botonTerminar.setFillColor(mouseSobreBotonTerminar ? botonColorHover : botonColorNormal);
            botonEditarRuta.setFillColor(mouseSobreBotonEditar ? botonColorHover : botonColorNormal);
            botonAgregar.setFillColor(mouseSobreBotonAgregar ? botonColorHover : botonColorNormal);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Comprobar si se hace clic en el botón "Terminar Ruta"
                    if (mouseSobreBotonTerminar) {
                        rutaActual = -1; // Terminar la ruta actual
                    }
                    // Comprobar si se hace clic en el botón "Editar Ruta"
                    else if (mouseSobreBotonEditar) {
                        cout << "Editando Ruta..." << endl; // Aquí puedes implementar la lógica deseada
                    }
                    // Comprobar si se hace clic en el botón "Agregar Ruta Nueva"
                    else if (mouseSobreBotonAgregar) {
                        if (cantidadRutas < maxRutas) {
                            mostrandoPaleta = true; // Mostrar paleta de colores
                        }
                    }
                    // Agregar punto en el mapa si hay una ruta activa
                    else if (rutaActual != -1 && cantidadPuntos[rutaActual] < maxPuntos) {
                        int index = cantidadPuntos[rutaActual]; // Índice del punto actual
                        shapePuntos[index + rutaActual * maxPuntos].setRadius(10);
                        shapePuntos[index + rutaActual * maxPuntos].setFillColor(coloresRutas[rutaActual]); // Usar el color de la ruta
                        shapePuntos[index + rutaActual * maxPuntos].setPosition(event.mouseButton.x, event.mouseButton.y);

                        puntos[index + rutaActual * maxPuntos] = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                        puntoActual = index; // Guardar el índice del punto actual
                        esperandoNombre = true; // Activar el modo de entrada de nombre
                        nombreActual.clear(); // Limpiar el nombre anterior
                        cantidadPuntos[rutaActual]++;
                    }
                }
            }

            // Manejo del teclado para ingresar el nombre del punto
            if (esperandoNombre) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) { // Asegurar que sea un carácter ASCII
                        if (event.text.unicode == 8) { // Backspace
                            if (!nombreActual.empty()) {
                                nombreActual.pop_back();
                            }
                        }
                        else if (event.text.unicode == 13) { // Enter
                            nombres[puntoActual + rutaActual * maxPuntos].setFont(font);
                            nombres[puntoActual + rutaActual * maxPuntos].setString(nombreActual);
                            nombres[puntoActual + rutaActual * maxPuntos].setCharacterSize(15);
                            nombres[puntoActual + rutaActual * maxPuntos].setFillColor(sf::Color::White);
                            nombres[puntoActual + rutaActual * maxPuntos].setPosition(puntos[puntoActual + rutaActual * maxPuntos].x, puntos[puntoActual + rutaActual * maxPuntos].y - 20); // Posicionar encima del punto

                            nombresTabla[puntoActual + rutaActual * maxPuntos] = nombreActual; // Guardar en la tabla
                            nombreActual.clear();
                            esperandoNombre = false; // Dejar de esperar el nombre
                        }
                        else {
                            nombreActual += static_cast<char>(event.text.unicode);
                        }
                    }
                }
            }

            // Manejo del teclado para ingresar el nombre de la ruta
            if (mostrandoPaleta) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        for (int i = 0; i < 5; ++i) {
                            sf::RectangleShape colorBox(sf::Vector2f(50, 50));
                            colorBox.setFillColor(coloresDisponibles[i]);
                            colorBox.setPosition(50 + i * 60, 50); // Posicionar la paleta

                            if (colorBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                                coloresRutas[cantidadRutas] = coloresDisponibles[i]; // Asigna el color seleccionado
                                nombreRutaActual.clear(); // Limpia el nombre de la ruta
                                esperandoNombreRuta = true; // Comienza a esperar el nombre de la ruta
                                mostrandoPaleta = false; // Oculta la paleta
                                rutaActual = cantidadRutas++; // Asigna la nueva ruta
                                cantidadPuntos[rutaActual] = 0; // Reiniciar la cantidad de puntos para la nueva ruta
                                break;
                            }
                        }
                    }
                }
            }

            // Manejo del teclado para ingresar el nombre de la ruta
            if (esperandoNombreRuta) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) { // Asegurar que sea un carácter ASCII
                        if (event.text.unicode == 8) { // Backspace
                            if (!nombreRutaActual.empty()) {
                                nombreRutaActual.pop_back();
                            }
                        }
                        else if (event.text.unicode == 13) { 
                            nombresTabla[rutaActual] = nombreRutaActual; 
                            esperandoNombreRuta = false; 
                        }
                        else {
                            nombreRutaActual += static_cast<char>(event.text.unicode);
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(sprite);

        
        for (int r = 0; r < cantidadRutas; r++) 
        {
            for (int i = 0; i < cantidadPuntos[r]; i++) 
            {
                window.draw(shapePuntos[i + r * maxPuntos]);
                window.draw(nombres[i + r * maxPuntos]);

                
                if (i < cantidadPuntos[r] - 1)
                {
                    sf::VertexArray lineas(sf::LinesStrip, 2);
                    lineas[0].position = puntos[i + r * maxPuntos];
                    lineas[1].position = puntos[i + 1 + r * maxPuntos];
                    lineas[0].color = coloresRutas[r]; 
                    lineas[1].color = coloresRutas[r]; 
                    window.draw(lineas);
                }
            }

            
            sf::Text textoRutaGuardada("Ruta " + to_string(r + 1) + ": " + nombresTabla[r], font, 15);
            textoRutaGuardada.setFillColor(sf::Color::Black);
            textoRutaGuardada.setPosition(windowWidth - 310, 80 + r * 20); // Ajusta la posición
            window.draw(textoRutaGuardada);
        }

        
        if (esperandoNombre) 
        {
            sf::Text inputText;
            inputText.setFont(font);
            inputText.setString(nombreActual);
            inputText.setCharacterSize(15);
            inputText.setFillColor(sf::Color::White);
            inputText.setPosition(puntos[puntoActual + rutaActual * maxPuntos].x, puntos[puntoActual + rutaActual * maxPuntos].y + 10); // Posicionar justo debajo del punto
            window.draw(inputText);
        }

        
        if (mostrandoPaleta) 
        {
            for (int i = 0; i < 5; ++i) 
            {
                sf::RectangleShape colorBox(sf::Vector2f(50, 50));
                colorBox.setFillColor(coloresDisponibles[i]);
                colorBox.setPosition(50 + i * 60, 50); // Posicionar la paleta
                window.draw(colorBox);
            }
        }

        
        window.draw(botonEditarRuta);
        window.draw(botonTextoEditar);
        window.draw(botonTerminar);
        window.draw(botonTexto);
        window.draw(botonAgregar);
        window.draw(botonTextoAgregar);

        window.display();
    }
}
