#include "world.h"

sf::RenderWindow windowInit() {
  constexpr int width = 1280;
  constexpr int height = 720;
  sf::RenderWindow window(sf::VideoMode({width, height}),
                          "Nth Body Simulation - CsDaBest");

  if (ImGui::SFML::Init(window))
    return window;

  return window;
}

void buildGui() {}
