#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "bodies.h"
#include "camera.h"
#include "world.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

int main() {
  sf::RenderWindow window = windowInit();
  Camera camera(window);

  sf::Clock deltaClock;
  PhysicsWorld physWorld;

  CelestialBody celestBody;

  for (int i = 0; i < 8; i++) {
    celestBody.addBody<Planet>(physWorld);
  }

  celestBody.addBody<Sun>(physWorld);

  celestBody.setInitialVelocity();
  sf::Vector2f pos;
  b2Vec2 posPhys;
  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (const auto *scrollWheel =
              event->getIf<sf::Event::MouseWheelScrolled>()) {
        camera.zoom(scrollWheel->delta);
      }

      if (const auto *mouseMove = event->getIf<sf::Event::MouseMovedRaw>()) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
          camera.scroll(mouseMove->delta);
        }
      }
    }
    window.setView(camera.camera);
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
