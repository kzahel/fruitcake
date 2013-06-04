#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef unsigned char byte;

// goals for a board
enum board_goal {
  CLEAR_JELLY,
  DROP_ITEMS,
  REACH_SCORE
};

enum tile_modifiers {
  EMPTY, // was just blown up, empty space
  VSTRIPE, // match 4 by swiping up or down
  HSTRIPE, // match 4 by swiping left or right
  WRAPPED, // match 5 in T or L shape
  COLORBOMB, // match 5
  PLUS_5, // adds 5 seconds
  BRICK, // immobile, brow up by matching nearby
  MOVABLE_BRICK, // blow up by matching nearby
  FALLTHROUGH, // other pieces can fall through
  NET, // caged, immobile, match inside to blow up
  CHOCOLATE // not sure what the growth conditions are...
};

struct MatchInfo {
  // information about a match

};

struct Tile {
  char color;
  byte modifiers; // bitmask for modifiers
  byte modifier_amount; // 1 or 2 for jellied
};

struct Board {
  struct Tile* tiles; // contiguous memory for tiles
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

struct Tile* Board_get(struct Board* board, int x, int y) {
  return board->tiles + y*board->width + x;
  //struct Tile* t = Tile_new_steal( &board->tiles + (y*board->width) + x );
  //return t;
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

struct Coords* Board_check_matching_at(struct Board* board, int x, int y) {
  // check if 3 or more in a row here, or other special patterns

  int colorhere = Board_get(board, x, y)->color;

  int match_up = 0;
  int match_down = 0;
  int match_left = 0;
  int match_right = 0;

  int cx;
  int cy;

  cx = x;
  while (1) {
    cx--;
    if (cx < 0 || cx >= board->width) {
      break;
    }
    if (colorhere == Board_get(board, cx, y)->color) {
      match_left++;
    } else {
      break;
    }
  }

  cx = x;
  while (1) {
    cx++;
    if (cx < 0 || cx >= board->width) {
      break;
    }
    printf("colors %c %c\n", colorhere, Board_get(board, cx, y)->color);
    if (colorhere == Board_get(board, cx, y)->color) {
      match_right++;
    } else {
      break;
    }
  }

  cy = y;
  while (1) {
    cy--;
    if (cy < 0 || cy >= board->height) {
      break;
    }
    if (colorhere == Board_get(board, x, cy)->color) {
      match_up++;
    } else {
      break;
    }
  }

  cy = y;
  while (1) {
    cy++;
    if (cy < 0 || cy >= board->height) {
      break;
    }
    if (colorhere == Board_get(board, x, cy)->color) {
      match_down++;
    } else {
      break;
    }
  }


  printf("matching %i %i %i %i\n", match_left, match_right, match_up, match_down);

  return 
    (match_left + match_right >= 2)
    || (match_up + match_down >= 2);
}


struct Coord** Board_check_has_matches(struct Board* board, struct Coord* coords, int dx, int dy) {
  /* dx and dy are which direction the move came from, if any */
  int match;

  for (int y=0; y<board->height; y++) {
    for (int x=0; x<board->width; x++) {
      match = Board_check_matching_at(board, x, y);
      if (match) {
        // check type of match...
      }
    }
  }

  // checks whether board has matches and returns coords where shit should blow up
}



void Board_blow_up(struct Board* board, struct Coord* coords) {
  // blows up pieces on board at input coords
  
}


int Board_do_gravity(struct Board* board) {
  // makes pieces fall down

  // call this repeatedly until returns false


  // check each piece to see if it can move down (or diagonal)
  
  // when a piece moves, it leaves open a space. see which piece wants to fill it.




  // OR: look for empty fillable space. see if it's reachable by any other piece...

}





int main(int argc, char** argv) {

  struct Tile* t = Tile_new('f');
  printf("tile %c\n", t->color);

  struct Board* b = Board_new(9,9);
  struct Tile* t2 = Board_get(b,0,0);
  
  printf("tile %c\n", t2->color);


  Board_print(b);

  Board_randomize(b);

  Board_print(b);


  

  struct Board* b2 = Board_clone(b);

  int matches;

  matches = Board_check_matching_at(b2, 0, 4);

  printf("board matches %i\n", matches);

  return 0;
}



