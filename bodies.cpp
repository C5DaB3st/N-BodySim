//
// Created by CsDaBest on 5/20/2026.
//
#include "bodies.h"
#include "box2cpp/box2cpp.h"
#include "box2d/box2d.h"
#include "box2d/types.h"
#include "world.h"
#include <ctime>
#include <random>
// Asteroids from 1-6
// Planets Range from circradius 7-12
// Suns from 15-30

void CelestialBody::setMass(CelestialBody &body) {
  std::mt19937 gen(std::time(nullptr));
  std::uniform_int_distribution<> sunRange(15, 30);
  std::uniform_int_distribution<> planetRange(7, 12);
  std::uniform_int_distribution<> astrRange(1, 6);

  switch (body.type) {
  case SUN:
    body.mass = sunRange(gen);
    break;

  case PLANET:
    body.mass = planetRange(gen);
    break;

  case ASTEROID:
    body.mass = astrRange(gen);
    break;
  }
}

float CelestialBody::getMass() { return this->mass; }

Planet::Planet(PhysicsWorld &physWorld) {
  type = PLANET;
  setMass(*this);
  float radius = getMass() * Bodies::box2DScale;
  b2Vec2 origin = randomCoord();

  b2::Body::Params bodyParam;
  bodyParam.position = randomCoord();
  bodyParam.type = b2_dynamicBody;
  bodyParam.gravityScale = -9.81;
  celestialBody = physWorld.world.CreateBody(b2::OwningHandle, bodyParam);

  b2::ShapeRef physShape =
      celestialBody.CreateShape(b2::DestroyWithParent, b2::Shape::Params{},
                                b2Circle{.center = {0, 0}, .radius = radius});
  celestialShape.setRadius(radius);
  celestialShape.setPosition({origin.x, -origin.y});
}
