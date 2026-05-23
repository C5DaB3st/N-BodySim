#include "world.h"
#include <ctime>
#include <random>

sf::RenderWindow windowInit() {
  constexpr int width = 1280;
  constexpr int height = 720;
  sf::RenderWindow window(sf::VideoMode({width, height}),
                          "Nth Body Simulation - CsDaBest");

  if (ImGui::SFML::Init(window))
    return window;

  return window;
}

b2Vec2 randomCoord() {
  std::mt19937 gen(std::time(nullptr));
  std::uniform_int_distribution<> xCoord(0, 1280);
  std::uniform_int_distribution<> yCoord(0, 720);

  b2Vec2 result{};
  result.x = xCoord(gen);
  result.y = yCoord(gen);

  return result;
}

void PhysicsWorld::init() {
  world.SetGravity({0.0f, 0.0f}); // no gravity in space :P

  b2::Body::Params bodyParam;
  bodyParam.type = b2_dynamicBody;
}
void buildGui() {}
