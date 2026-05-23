// Created by CsDaBest on 5/20/2026.

#ifndef N_BODY_SPACE_WORLD_H
#define N_BODY_SPACE_WORLD_H

#include <SFML/Graphics.hpp>
#include <box2cpp/box2cpp.h>
#include <imgui-SFML.h>
#include <imgui.h>

sf::RenderWindow windowInit();

b2Vec2 randomCoord();

namespace World {
constexpr float timeStep = 1.0f / 60.0f;
constexpr int subStepCount = 4;
const b2Vec2 worldGravity = {0, 0};
} // namespace World

// make a class with static members in order to have world and parent be
// persistent
class PhysicsWorld {
public:
  void init();
  b2::World world;
};
#endif // N_BODY_SPACE_WORLD_H
