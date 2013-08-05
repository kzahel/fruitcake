#include<string>
#include<cstdlib>

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


class Tile {
public:
  char color;
  byte modifiers; // bitmask for modifiers
  byte modifier_amount; // 1 or 2 for jellied
  void foo() {
  }
};


int randrange(int maxval) {
  return random() % maxval;
}

class Board {
  class Tile* tiles; // contiguous memory for tiles
 
public:
  int width, height;

  Board(int w, int h) {
    width = w;
    height = h;
    class Tile* t;

    tiles = (Tile*) calloc(width*height, sizeof(class Tile));

    for (int y=0; y<height; y++) {
      for (int x=0; x<width; x++) {
        int offset = y*width + x;
        t = tiles + offset;
        t->color = 'b';
      }
    }

  };
  ~Board() {
  };

  void randomize() {

    Board* board = this;
    class Tile* t;
    std::string a = "a";
    int firstlettervalue = (int) a[0];

    for (int y=0; y<board->height; y++) {
      for (int x=0; x<board->width; x++) {
        int offset = y*board->width + x;

        t = &( board->tiles[ offset ] );

        int r = randrange(6);

        t->color = (char) (firstlettervalue + r);
      }
    }

  }
  
  class Tile* get(int x, int y) {
    return tiles + y*width + x;
  };


  int check_matching_at(int x, int y) {
    // check if 3 or more in a row here, or other special patterns
    class Board* board = this;
    int colorhere = board->get(x, y)->color;

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
      if (colorhere == board->get(cx, y)->color) {
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
      printf("colors %c %c\n", colorhere, board->get(cx, y)->color);
      if (colorhere == board->get(cx, y)->color) {
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
      if (colorhere == board->get(x, cy)->color) {
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
      if (colorhere == board->get(x, cy)->color) {
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




  void print() {
    printf("printing board %p\n\n", this);
    class Tile* t;

    for (int y=0; y<height; y++) {
      for (int x=0; x<width; x++) {
        t = &( tiles[y*width + x] );
        printf("%c", t->color);
      }
      printf("\n");
    }
    printf("\ndone printing board\n");
  }


  void foo() {
    printf("im a board! %i %i\n", width, height);
  };
};

class Coord {
public:
  int x,y;
  Coord(int a, int b) {
    x=a;
    y=b;
  }
};

class Simulation {
private:
  Board* board;
public:

  Simulation(Board* b) {
    board = new Board(b->width, b->height);
    memcpy(board, b, sizeof(class Board));
  }

  void tick() {
    /* 
       advances the simulation

       checks for any matches, and marks them for exploden!

       marks any special pieces to place - note that the piece that
       moved "in" to cause the match gets the special treatment

       this means we can only move one tile at a time

    */
    
  }


  int evaluate_move(Board* b, Coord* c1, Coord* c2) {
    int val = 1;
    printf("eval move returns %i\n", val);
    return val;
  };
};




int main(int argc, char* argv[]) {
  printf("hello\n");

  Board* b = new Board(9,9);


  b->foo();
  b->print();
  b->randomize();
  b->print();


  int matches = b->check_matching_at(0, 4);
  printf("matches %i\n", matches);

  Simulation* s = new Simulation(b);

  s->evaluate_move(b, new Coord(3,0), new Coord(4,0));

  delete b;
  return 0;
}
