//
// Created by CsDaBest on 5/20/2026.
//
#include "bodies.h"
#include "SFML/System/Vector2.hpp"
#include "box2cpp/box2cpp.h"
#include "box2d/types.h"
#include "world.h"
#include <ctime>
#include <memory>
#include <random>
// Asteroids from 1-6
// Planets Range from circradius 7-12
// Suns from 15-30

b2Vec2 vectorDecomp(b2Vec2 x, b2Vec2 y) {
  b2Vec2 dirVector = x - y;
  float magnitude =
      std::sqrt((dirVector.x * dirVector.x) + (dirVector.y * dirVector.y));
  dirVector.x /= magnitude;
  dirVector.y /= magnitude;

  return dirVector;
}

float calcDistance(b2Vec2 pair1, b2Vec2 pair2) {
  return std::hypot(pair2.x - pair1.x, pair2.y - pair1.y);
}

float calcGravForce(float massX, float massY, float distance) {
  return World::universalGravityConst *
         ((massX * massY) / (distance * distance));
}

void CelestialBody::addForce() {
  float gravForce{};
  float distance{};
  b2Vec2 dirVector{}, pos1, pos2;
  for (int i = 0; i < celestialBodies.size(); ++i) {
    for (int j = i + 1; j < celestialBodies.size(); ++j) {
      pos1 = celestialBodies[i]->celestialBody.GetPosition();
      pos2 = celestialBodies[j]->celestialBody.GetPosition();

      distance = calcDistance(pos2, pos1);

      if (distance < 0.1f)
        continue;

      gravForce =
          calcGravForce(celestialBodies[i]->celestialBody.GetMass(),
                        celestialBodies[j]->celestialBody.GetMass(), distance);
      dirVector = vectorDecomp(pos1, pos2);
      dirVector *= gravForce * 15000.0f;
      celestialBodies[i]->celestialBody.ApplyForceToCenter(dirVector, true);
      celestialBodies[j]->celestialBody.ApplyForceToCenter(-dirVector, true);
    }
  }
}

void CelestialBody::setSize(CelestialBody &body) {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> sunRange(15, 30);
  std::uniform_int_distribution<> planetRange(7, 12);
  std::uniform_int_distribution<> astrRange(1, 6);

  switch (body.type) {
  case SUN:
    body.size = sunRange(gen);
    break;

  case PLANET:
    body.size = planetRange(gen);
    break;

  case ASTEROID:
    body.size = astrRange(gen);
    break;
  }
}

float CelestialBody::getSize() { return this->size; }

sf::Vector2f CelestialBody::getBodyPosition() {
  b2Vec2 bodyPos = this->celestialBody.GetPosition();
  return sf::Vector2f(bodyPos.x * 30, bodyPos.y * 30);
}

std::vector<std::unique_ptr<CelestialBody>> CelestialBody::celestialBodies;

Planet::Planet(PhysicsWorld &physWorld) {
  type = PLANET;
  setSize(*this);
  float radius = getSize() * Bodies::box2DScale;
  b2Vec2 origin = randomCoord();
  position = {origin.x / 30, origin.y / 30};
  b2::Body::Params bodyParam;
  bodyParam.position = position;
  bodyParam.type = b2_dynamicBody;

  celestialBody = physWorld.world.CreateBody(b2::OwningHandle, bodyParam);

  b2::ShapeRef physShape =
      celestialBody.CreateShape(b2::DestroyWithParent, b2::Shape::Params{},
                                b2Circle{.center = {0, 0}, .radius = radius});

  celestialSprite.setRadius(getSize());
  celestialSprite.setPosition(this->getBodyPosition());
  celestialSprite.setFillColor(sf::Color::White);
}
