#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "CSDLManagerLite.h"
#include "CSDLInputManagerLite.h"
#include "defs.h"
#include "Turmite.h"


using namespace std;

struct Color {
    int r, g, b;
    Color(){
        r = 0;
        g = 0;
        b = 0;
    }
    Color(int rr, int gg, int bb) {
        r = rr;
        g = gg;
        b = bb;
    }
};

int cells[HEIGHT/CELLSIZE][WIDTH/CELLSIZE];
int rows, cols;
int numStates;
string movementPattern;

Turmite* t;
Color* palette = new Color[10];
Color termiteColor = Color(255, 0, 0);

void update() {
    CSDLManagerLite::getInstance() -> drawFrame();
    //CSDLManagerLite::getInstance() -> background();
    CSDLInputManagerLite::getInstance() -> update();
}

void iteration() {
    int tempColor = cells[t->r][t->c];
    cells[t->r][t->c]++;

    if (cells[t->r][t->c] == numStates)
        cells[t->r][t->c] = 0;

    CSDLManagerLite::getInstance() -> setColor(
        palette[cells[t->r][t->c]].r,
        palette[cells[t->r][t->c]].g,
        palette[cells[t->r][t->c]].b,
        255);

    CSDLManagerLite::getInstance() -> drawRectTLCorner(t->c*CELLSIZE, t->r*CELLSIZE, CELLSIZE, CELLSIZE);

    t -> move(tempColor);
    CSDLManagerLite::getInstance() -> setColor(termiteColor.r, termiteColor.g, termiteColor.b, 255);
    CSDLManagerLite::getInstance() -> drawRectTLCorner(t->c*CELLSIZE, t->r*CELLSIZE, CELLSIZE, CELLSIZE);
}

int main(int argc, char *argv[]) {
    rows = HEIGHT/CELLSIZE;
    cols = WIDTH/CELLSIZE;

    cout << "Please enter turmite movement pattern: ";
    getline(cin, movementPattern);
    numStates = movementPattern.length();

    t = new Turmite(rows/2, cols/2, 0, rows, cols, movementPattern);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cells[r][c] = 0;
        }
    }

    srand(time(NULL)); //Seed

    palette[0] = Color(0,0,0);
    for (int k = 1; k < numStates; k++) {
        palette[k] = Color(rand()%256, rand()%256, rand()%256);
    }

    CSDLManagerLite::getInstance()->initializeSDL(WIDTH, HEIGHT, TITLE);

    while (!CSDLInputManagerLite::getInstance() -> isExit()) {
        iteration();
        update();
    }

    CSDLManagerLite::getInstance()->clean();
    delete t;
    delete[] palette;
    return 0;
}