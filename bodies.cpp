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
#include <print>
#include <random>
// Asteroids from 1-6
// Planets Range from circradius 7-12
// Suns from 15-30

b2Vec2 vectorDecomp(b2Vec2 x, b2Vec2 y) {
  b2Vec2 dirVector = x - y;
  float magnitude =
      std::sqrt((dirVector.x * dirVector.x) + (dirVector.y * dirVector.y));

  // Prevent division by zero if objects are exactly on top of each other
  if (magnitude > 0.0001f) {
    dirVector.x /= magnitude;
    dirVector.y /= magnitude;
  }

  return dirVector;
}

float calcDistance(b2Vec2 pair1, b2Vec2 pair2) {
  return std::hypot(pair2.x - pair1.x, pair2.y - pair1.y);
}

float calcGravForce(float massX, float massY, float distance) {
  return World::universalGravityConst *
         ((massX * massY) / (distance * distance));
}

void CelestialBody::setInitialVelocity() {
  float distance{};

  b2Vec2 dirVector{}, pos1, pos2;
  std::vector<b2Vec2> velocities(celestialBodies.size(), b2Vec2_zero);
  for (int i = 0; i < celestialBodies.size(); ++i) {
    for (int j = i + 1; j < celestialBodies.size(); ++j) {
      pos1 = celestialBodies[i]->celestialBody.GetPosition();
      pos2 = celestialBodies[j]->celestialBody.GetPosition();

      distance = calcDistance(pos2, pos1);
      if (distance < 0.1f)
        continue;
      dirVector = vectorDecomp(pos1, pos2);

      b2Vec2 normVector = {-dirVector.y, dirVector.x};
      float orbitalSpeed =
          std::sqrt(std::abs(World::universalGravityConst *
                             (celestialBodies[i]->celestialBody.GetMass() +
                              celestialBodies[j]->celestialBody.GetMass())) /
                    distance);

      float v1 = orbitalSpeed * (celestialBodies[j]->celestialBody.GetMass() /
                                 (celestialBodies[i]->celestialBody.GetMass() +
                                  celestialBodies[j]->celestialBody.GetMass()));
      float v2 = orbitalSpeed * (celestialBodies[i]->celestialBody.GetMass() /
                                 (celestialBodies[i]->celestialBody.GetMass() +
                                  celestialBodies[j]->celestialBody.GetMass()));

      velocities[i] -= v1 * normVector;
      velocities[j] += v2 * normVector;
    }
  }
  for (int i = 0; i < celestialBodies.size(); i++) {
    celestialBodies[i]->celestialBody.SetLinearVelocity(velocities[i]);
  }
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

      // gravitational force
      gravForce =
          calcGravForce(celestialBodies[i]->celestialBody.GetMass(),
                        celestialBodies[j]->celestialBody.GetMass(), distance);
      dirVector = vectorDecomp(pos1, pos2);

      // gravitational force

      dirVector *= gravForce;
      celestialBodies[i]->celestialBody.ApplyForceToCenter(dirVector, true);
      celestialBodies[j]->celestialBody.ApplyForceToCenter(-dirVector, true);
    }
  }
}

void CelestialBody::setSize(CelestialBody &body) {
  std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<> sunRange(100.f, 500.f);
  std::uniform_real_distribution<> planetRange(5.f, 30.f);
  std::uniform_real_distribution<> astrRange(.2f, 3.f);

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
  return sf::Vector2f(bodyPos.x * World::box2DScale,
                      bodyPos.y * World::box2DScale);
}

std::vector<std::unique_ptr<CelestialBody>> CelestialBody::celestialBodies;

Planet::Planet(PhysicsWorld &physWorld) {
  type = PLANET;
  setSize(*this);
  float radius = getSize() * World::box2DScale;
  b2Vec2 origin = randomCoord();
  position = {origin.x * World::box2DScale, origin.y * World::box2DScale};
  b2::Body::Params bodyParam;
  bodyParam.position = position;
  bodyParam.linearDamping = 0.0f;
  bodyParam.angularDamping = 0.0f;
  bodyParam.enableSleep = false;
  bodyParam.type = b2_dynamicBody;

  celestialBody = physWorld.world.CreateBody(b2::OwningHandle, bodyParam);
  b2::ShapeRef physShape =
      celestialBody.CreateShape(b2::DestroyWithParent, b2::Shape::Params{},
                                b2Circle{.center = {0, 0}, .radius = radius});

  celestialSprite.setRadius(getSize() * World::box2DScale);
  celestialSprite.setPosition(this->getBodyPosition());
  celestialSprite.setFillColor(sf::Color::White);
}

Sun::Sun(PhysicsWorld &physWorld) {
  type = SUN;
  setSize(*this);
  float radius = getSize() * World::box2DScale;
  b2Vec2 origin = randomCoord();
  position = {origin.x * World::box2DScale, origin.y * World::box2DScale};
  b2::Body::Params bodyParam;
  bodyParam.position = position;
  bodyParam.linearDamping = 0.0f;
  bodyParam.angularDamping = 0.0f;
  bodyParam.enableSleep = false;
  bodyParam.type = b2_dynamicBody;

  celestialBody = physWorld.world.CreateBody(b2::OwningHandle, bodyParam);

  b2::ShapeRef physShape =
      celestialBody.CreateShape(b2::DestroyWithParent, b2::Shape::Params{},
                                b2Circle{.center = {0, 0}, .radius = radius});

  celestialSprite.setRadius(getSize() * World::box2DScale);
  celestialSprite.setPosition(this->getBodyPosition());
  celestialSprite.setFillColor(sf::Color::Yellow);
}
