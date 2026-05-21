//
// Created by CsDaBest on 5/14/2026.
//

#ifndef N_BODY_SPACE_BODIES_H
#define N_BODY_SPACE_BODIES_H

#include <memory>
#include <vector>

#include <box2cpp/box2cpp.h>

enum BodyType { SUN = 0, PLANET, ASTEROID };

class CelestialBody {
public:
  void spawnBody(CelestialBody body);
  void gravitationPull();
  BodyType type;
  int setSize(CelestialBody body);

private:
  int mass; // also size
  int acceleration;
  b2Vec2 position;
  float gravity;
};

class Planet : public CelestialBody {
public:
  Planet();
  ~Planet();

  std::vector<std::unique_ptr<Planet>> planets;

private:
  BodyType type = PLANET;
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
