#include<stdio.h>
#include<stdlib.h>
#include<math.h>


// goals for a board
enum board_goal {
  CLEAR_JELLY,
  DROP_ITEMS,
  REACH_SCORE
};



struct Tile {
  char color;
};

struct Board {
  struct Tile* tiles;
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
  return t;
}

void Tile_print(struct Tile* t) {
  printf("<Tile(color:%c)>\n", t->color);
}

struct Board* Board_new(int width, int height) {
  // allocates memory for all the tiles in the board
  struct Board* b = malloc(sizeof(struct Board));

  b->tiles = calloc(width*height, sizeof(struct Tile));
  b->width = width;
  b->height = height;
  //struct Tile* t;

  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      int offset = y*width + x;
      struct Tile* t = b->tiles + offset;
      t->color = 'b';
    }
  }

  return b;
}

static struct Tile* Board_get(struct Board* board, int x, int y) {
  struct Tile* t = Tile_new_steal( &board->tiles + (y*board->width) + x );
  return t;
}

void Board_set(struct Board* board, int x, int y, char color) {
  struct Tile* t = Board_get(board, x, y);
  t->color = color;
}

void Board_print(struct Board* board) {
  printf("printing board %d\n\n", (int) &board);

  for (int y=0; y<board->height; y++) {
    for (int x=0; x<board->width; x++) {
      struct Tile* t = &( board->tiles[y*board->width + x] );
      printf("%c", t->color);
    }
    printf("\n");
  }
  printf("\ndone printing board\n");
}

int randrange(maxval) {
  return random() % maxval;
  /*
  long v = random();
  long maxv = pow(2, 31) - 1;
  printf("random %i %i", v, maxv);
  return v / maxv;
  */
}

/*
enum tilecolors = {
  red = 0;
  green = 1;
  blue = 2;
};
*/

void Board_randomize(struct Board* board) {


  //int firstletter = atoi(a);
  char* a = "a";
  int firstlettervalue = (int) a[0];

  //int firstletter

  for (int y=0; y<board->height; y++) {
    for (int x=0; x<board->width; x++) {
      int offset = y*board->width + x;

      struct Tile* t = &( board->tiles[ offset ] );

      int r = randrange(6);

      t->color = (char) (firstlettervalue + r);
      //t->color = 'g';

    }
  }

}

struct Board* Board_clone(struct Board* board) {
  
}

struct Coord {
  int x;
  int y;
};

struct Coord** Board_get_matching_line(struct Board* board, struct Coord* c) {
  // returns a list of coordinates 
}

struct Coord** Board_check_has_matches(struct Board* board, struct Coord* coords) {
  // checks whether board has matches and returns coords where shit should blow up
}

void Board_blow_up(struct Board* board, struct Coord* coords) {
  // blows up pieces on board at input coords
  
}


bool Board_do_gravity(struct Board* board) {
  // makes pieces fall down

  // call this repeatedly until returns false
}




int main(int argc, char** argv) {

  struct Tile* t = Tile_new('f');
  printf("tile %c\n", t->color);

  struct Board* b = Board_new(4,4);
  struct Tile* t2 = Board_get(b,0,0);
  
  printf("tile %c\n", t2->color);


  Board_print(b);

  Board_randomize(b);

  Board_print(b);


  struct Board* b2 = Board_clone(b);

  return 0;
}



