//
// Created by CsDaBest on 5/20/2026.
//

#ifndef N_BODY_SPACE_WORLD_H
#define N_BODY_SPACE_WORLD_H

#include <SFML/Graphics.hpp>
#include <box2cpp/box2cpp.h>
#include <imgui-SFML.h>
#include <imgui.h>

sf::RenderWindow windowInit();
void worldInit();

inline b2::World world(b2::World::Params{});

inline float timeStep = 1.0f / 60.0f;
inline const int subStepCount = 4;
#endif // N_BODY_SPACE_WORLD_H
