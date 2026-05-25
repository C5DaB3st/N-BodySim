#pragma once

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>

class Camera {
public:
  Camera(sf::RenderWindow &window);
  sf::View camera;
  void zoom(float delta);
  void scroll(const sf::Vector2i delta);
};
