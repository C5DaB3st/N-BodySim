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
  physWorld.init();

  Planet planet(physWorld);

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

    physWorld.world.Step(World::timeStep, World::subStepCount);

    window.clear();
    // call all draws here
    window.draw(planet.celestialShape);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
