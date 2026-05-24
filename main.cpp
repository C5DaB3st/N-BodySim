#include "bodies.h"
#include "world.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>

int main() {
  sf::RenderWindow window = windowInit();

  sf::Clock deltaClock;

  // test shape size
  sf::CircleShape circle(30);
  PhysicsWorld physWorld;

  CelestialBody celestBody;

  for (int i = 0; i < 4; i++) {
    celestBody.addBody<Planet>(physWorld);
  }
  sf::Vector2f pos;
  b2Vec2 posPhys;
  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    celestBody.addForce();
    physWorld.update(CelestialBody::celestialBodies);

    ImGui::SFML::Update(window, deltaClock.restart());

    window.clear();
    // call all draws here
    drawCelestialBodies(window);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
