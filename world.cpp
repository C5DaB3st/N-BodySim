#include "world.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/WindowEnums.hpp"
#include "bodies.h"
#include <random>

sf::RenderWindow windowInit() {
  constexpr int width = 1920;
  constexpr int height = 1080;

  sf::ContextSettings settings;
  settings.antiAliasingLevel = 0;
  sf::RenderWindow window(sf::VideoMode({width, height}),
                          "Nth Body Simulation - CsDaBest", sf::Style::Default,
                          sf::State::Windowed, settings);

  if (ImGui::SFML::Init(window))
    return window;

  return window;
}

b2Vec2 randomCoord() {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> xCoord(-300, 300);
  std::uniform_int_distribution<> yCoord(-300, 300);

  b2Vec2 result{};
  result.x = xCoord(gen);
  result.y = yCoord(gen);

  return result;
}

PhysicsWorld::PhysicsWorld() {
  world.SetGravity(World::worldGravity); // no gravity in space :P

  b2::Body::Params bodyParam;
  bodyParam.type = b2_dynamicBody;
}

void PhysicsWorld::update(std::vector<std::unique_ptr<CelestialBody>> &bodies) {
  world.Step(World::timeStep, World::subStepCount);

  for (auto &body : bodies) {
    body->celestialSprite.setPosition(body->getBodyPosition());
  }
}
void drawCelestialBodies(sf::RenderWindow &window) {
  for (auto &body : CelestialBody::celestialBodies)
    window.draw(body->celestialSprite);
}
void buildGui() {}
