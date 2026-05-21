#include "world.h"
#include "box2d/types.h"

sf::RenderWindow windowInit() {
  constexpr int width = 1280;
  constexpr int height = 720;
  sf::RenderWindow window(sf::VideoMode({width, height}),
                          "Nth Body Simulation - CsDaBest");

  if (ImGui::SFML::Init(window))
    return window;

  return window;
}

void worldInit() {
  b2WorldDef worldDef = b2DefaultWorldDef();

  worldDef.gravity = (b2Vec2){0.0f, 0.0f}; // no gravity in space

  b2WorldId worldId = b2CreateWorld(&worldDef);
}

void buildGui() {}
