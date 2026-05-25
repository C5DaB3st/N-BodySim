#include "camera.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

Camera::Camera(sf::RenderWindow &window) {
  camera = window.getDefaultView();
  camera.zoom(500.f);
}

void Camera::zoom(float delta) {

  if (delta > 0) {
    camera.zoom(.8f);
  } else {
    camera.zoom(1.3f);
  }
}

void Camera::scroll(const sf::Vector2i delta) {
  sf::Vector2f viewSize = camera.getSize();
  viewSize *= .002f;
  camera.move(static_cast<sf::Vector2f>(-delta) * viewSize.x);
}
