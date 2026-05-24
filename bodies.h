//
// Created by CsDaBest on 5/14/2026.
//

#ifndef N_BODY_SPACE_BODIES_H
#define N_BODY_SPACE_BODIES_H

#include "box2d/math_functions.h"
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
  template <class T, class... Args> static T &addBody(Args &&...args);
  void addForce();
  void setSize(CelestialBody &body);
  float getSize();
  sf::Vector2f getBodyPosition();
  b2::Body celestialBody;
  sf::CircleShape celestialSprite;
  BodyType type;
  b2Vec2 position;
  static std::vector<std::unique_ptr<CelestialBody>> celestialBodies;

private:
  float size;
  int acceleration;
  float gravity;
};

class Planet : public CelestialBody {
public:
  Planet(PhysicsWorld &physWorld);
};

class Sun : public CelestialBody {
public:
  Sun();

private:
  BodyType type = SUN;
};

class Asteroid : public CelestialBody {
public:
  Asteroid();

private:
  BodyType type = ASTEROID;
};
#endif // N_BODY_SPACE_BODIES_H

int randomSize(BodyType);

b2Vec2 vectorDecomp(b2Vec2 x, b2Vec2 y);
float calcDistance(b2Vec2 x, b2Vec2 y);
float calcGravForce(float massX, float massY, float distance);

template <class T, class... Args> T &CelestialBody::addBody(Args &&...args) {
  auto obj = std::make_unique<T>(std::forward<Args>(args)...);

  T &ref = *obj;
  celestialBodies.push_back(std::move(obj));

  return ref;
}
