#ifndef GHOST_H
#define GHOST_H

#include <math.h>

#include <limits>
#include <vector>
#include <string>

#include "opengl.hpp"
#include "maze.hpp"

#include "pacman.hpp"

enum behaviour { scatter, frightened, chase };

class Ghost {
 protected:
  // ---------------------------------------------------------------------------
  // Attributes

  static std::vector<std::string> personality;
  std::string name;

  Pacman *pacman;
  Maze *maze;

  orientation direction;

  glm::vec3 position;
  glm::vec2 target;

  glm::vec2 home;
  glm::vec2 homeExit;
  glm::vec2 homeEntrance;

  bool useDoor;
  bool isHome;
  bool dead;

  static behaviour mode;

  // ---------------------------------------------------------------------------
  // Virtual methods

  virtual void updateTarget() = 0;

  // ---------------------------------------------------------------------------
  // Methods

  void move(float delta);
  orientation oppositeDirection(orientation direction);
  void updateDirection();
  void checkNeighbours(float distances[]);
  void checkTunnel();
  bool isBelowDoor();

 public:
  // ---------------------------------------------------------------------------
  // Getters

  static std::vector<std::string> getPersonality();
  static behaviour getMode();

  orientation getOrientation();
  glm::vec3 getPosition();
  bool isDead();

  // ---------------------------------------------------------------------------
  // Setters

  static void setMode(behaviour mode);

  void setOrientation(orientation direction);
  void setIsHome(bool isHome);
  void setUseDoor(bool door);
  void setDead(bool dead);

  // ---------------------------------------------------------------------------
  // Methods

  virtual void reset() = 0;

  void updatePosition(float delta);
  void turnAround();

  // ---------------------------------------------------------------------------
  // Constructors

  Ghost(Pacman *pacman, Maze *maze);
  virtual ~Ghost();
};

#endif
