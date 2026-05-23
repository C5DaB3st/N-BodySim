//
// Created by CsDaBest on 5/14/2026.
//

#ifndef N_BODY_SPACE_BODIES_H
#define N_BODY_SPACE_BODIES_H

#include "world.h"
#include <box2cpp/box2cpp.h>
#include <memory>
#include <vector>

namespace Bodies {
const float box2DScale = 1.0f / 30.0f; // scale box2D to SFML
}

enum BodyType { SUN = 0, PLANET, ASTEROID };

class CelestialBody {
public:
  void spawnBody(CelestialBody body);
  void gravitationPull();
  void setMass(CelestialBody &body);
  float getMass();
  b2Vec2 getPosition();
  b2::Body celestialBody;
  sf::CircleShape celestialShape;
  BodyType type;

private:
  float mass; // also size
  int acceleration;
  b2Vec2 position;
  float gravity;
};

class Planet : public CelestialBody {
public:
  Planet(PhysicsWorld &physWorld);

  std::vector<std::unique_ptr<Planet>> planets;
};

class Sun : public CelestialBody {
public:
  Sun();
  ~Sun();
  std::vector<std::unique_ptr<Sun>> suns;

private:
  BodyType type = SUN;
};

class Asteroid : public CelestialBody {
public:
  Asteroid();
  ~Asteroid();
  std::vector<std::unique_ptr<Asteroid>> asteroids;

private:
  BodyType type = ASTEROID;
};
#endif // N_BODY_SPACE_BODIES_H

int randomSize(BodyType);
