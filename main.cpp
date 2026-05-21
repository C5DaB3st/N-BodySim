#include "world.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window = windowInit();

  sf::Clock deltaClock;

  // test shape size
  sf::CircleShape circle(30);

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

    window.clear();
    // call all draws here
    worldInit();
    window.draw(circle);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
