# Maze

-28 * 31 blocos

-224 * 248 pixeis

+---+
|   | -> 8 x 8 pixels
+---+

Dado as coordenadas do canto inferior esquerdo e a dimensão do objeto,
determinamos todos os blocos contidos neste intervalo.

# Pacman

- Initial coords = (100, 100) (bottom left)
- Size = (17,17)
- set movement speed (calcular a média de duração de um ciclo de renderização)

O pacman ocupa a célula onde o seu centro se encontra

# Ghosts

### Lidar com o modo eaten
~~~c
 case eaten:
      this->target = this->maze->getCenter(glm::vec3(104, 148, 16));
      break;
~~~

# Game

Garantir um delta divisor de 1, de forma a que nunca saltemos o centro nos
incrementos de posição.















~~~c
for (int i = 0; i < 4; i++) {
    testBlock = this->maze->blockNext(ghostBlock, (orientation)i);
    if (true) {
      centered = fabs(ghostCenter.y - blockCenter.y) <= 0.01f;


    if ((this->isHome || oppositeDir != (orientation)i) &&
        (!centered || this->maze->valid(testBlock, this->door))) {
      if (this->mode != frightened) {
        nextPos = this->maze->blockToPixel(testBlock);
        distances[i] = this->maze->euclidianDist(nextPos, this->target);
      } else {
        distances[i] = 1.0f;
      }
    }
~~~
