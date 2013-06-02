#include<stdio.h>
#include<stdlib.h>

struct Tile {
  char color;
};

struct Board {
  struct Tile** tiles;
  int width;
  int height;
};


struct Tile* Tile_new(char c) {
  struct Tile* newtile = malloc(sizeof(struct Tile));
  newtile->color = c;
  return newtile;
}

struct Tile* Tile_new_steal(void * ptr) {
  // creates a tile structure at a given memory location
  struct Tile* t = ptr;
}

struct Board* Board_new(int width, int height) {

  // allocates memory for all the tiles in the board
  struct Board* b;

  struct Tile** tiles = malloc(sizeof(struct Tile) * width * height);

  b->tiles = tiles;

  b->width = width;
  b->height = height;
  return b;

}

static struct Tile* Board_get(struct Board* board, int x, int y) {
  struct Tile* t = Tile_new_steal( &board->tiles + (y*board->width) + x );
  return t;
}

int main(int argc, char** argv) {
  puts("prog begin");

  struct Tile* t = Tile_new('f');
  printf("tile %c\n", t->color);


  struct Board* b = Board_new(10,20);

  puts("prog end");
  return 0;
}



