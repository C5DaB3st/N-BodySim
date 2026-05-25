// Created by CsDaBest on 5/20/2026.

#ifndef N_BODY_SPACE_WORLD_H
#define N_BODY_SPACE_WORLD_H

#include <SFML/Graphics.hpp>
#include <box2cpp/box2cpp.h>
#include <cmath>
#include <imgui-SFML.h>
#include <imgui.h>

sf::RenderWindow windowInit();

b2Vec2 randomCoord();
void drawCelestialBodies(sf::RenderWindow &window);

namespace World {
constexpr float timeStep = 1.0f / 60.0f;
constexpr int subStepCount = 4;
const b2Vec2 worldGravity = {0, 0};
const float universalGravityConst = -6.674e-11 * 15000.0f;
constexpr float box2DScale = 30.f;
} // namespace World

class CelestialBody;
class PhysicsWorld {
public:
  PhysicsWorld();
  void update(std::vector<std::unique_ptr<CelestialBody>> &bodies);
  b2::World world{b2::World::Params{}};
};
#endif // N_BODY_SPACE_WORLD_H
