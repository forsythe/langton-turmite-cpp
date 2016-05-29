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
    Color() {
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
bool pause = false, keydown = false, toToggle = false;

Color* palette;
Color termiteColor = Color(255, 0, 0);

void update() {
    CSDLManagerLite::getInstance() -> drawFrame();
    //CSDLManagerLite::getInstance() -> background();
    CSDLInputManagerLite::getInstance() -> update();
}

void iteration(Turmite* t) {
    int tempColor = cells[t->r][t->c];
    cells[t->r][t->c]++;

    if (cells[t->r][t->c] == numStates)
        cells[t->r][t->c] = 0;

    t -> move(tempColor);

}

void redrawGrid(){
    CSDLManagerLite::getInstance() -> background();

    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            if (cells[r][c] > 0){
                int temp = cells[r][c];
                CSDLManagerLite::getInstance() -> setColor(palette[temp].r, palette[temp].g, palette[temp].b, 255);
                CSDLManagerLite::getInstance() -> drawRectTLCorner(c*CELLSIZE, r*CELLSIZE, CELLSIZE, CELLSIZE);
            }
        }
    }


}

int main(int argc, char *argv[]) {
    rows = HEIGHT/CELLSIZE;
    cols = WIDTH/CELLSIZE;

    cout << "Please enter turmite movement pattern: ";
    getline(cin, movementPattern);
    numStates = movementPattern.length();

    palette = new Color[numStates];

    Turmite* bob = new Turmite(rows/2, cols/2, 0, rows, cols, movementPattern);

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

    int steps = 0;

    while (!CSDLInputManagerLite::getInstance() -> isExit()) {

        if (CSDLInputManagerLite::getInstance() -> isKeyDown(SDL_SCANCODE_SPACE)){
            keydown = true;
            toToggle = true;
        } else{
            keydown = false;
        }

        if (toToggle && !keydown){
            pause = !pause;
            toToggle = false;
        }
        cout<<rand()<<endl;

        if (pause){
            CSDLInputManagerLite::getInstance() -> update();
            continue;
        }
        iteration(bob);

        if (steps%STEPSPERFRAME == 0){
            redrawGrid();
            CSDLManagerLite::getInstance() -> setColor(termiteColor.r, termiteColor.g, termiteColor.b, 255);
            CSDLManagerLite::getInstance() -> drawRectTLCorner(bob->c*CELLSIZE, bob->r*CELLSIZE, CELLSIZE, CELLSIZE);
            update();
        }
        steps++;
    }

    cout << "steps taken: " + steps << endl;
    CSDLManagerLite::getInstance()->clean();
    delete bob;
    delete[] palette;
    return 0;
}
