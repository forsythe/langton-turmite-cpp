#include "Turmite.h"
using namespace std;
Turmite::Turmite(int r_rhs, int c_rhs, int angle_rhs, int num_rows, int num_cols, const std::string& moves_rhs) {
    r = r_rhs;
    c = c_rhs;
    cout << "starting at " << r << " " << c <<endl;
    cout << "total rc " << num_rows << " " << num_cols << endl;
    angle = angle_rhs;
    max_rows = num_rows;
    max_cols = num_cols;
    moves = moves_rhs;
    moveLeft = new bool[moves.length()];

    for (int k = 0; k < moves.length(); k++) {
        *(moveLeft+k) = (moves.at(k) == 'L' || moves.at(k) == 'l');
    }
}

void Turmite::move(int cur_cell) {
    angle += *(moveLeft+cur_cell) ? 90: -90;

    if (angle < 0)
        angle = 270;

    if (angle >= 360)
        angle = 0;

    switch(angle) {
    case 0:
        c++;
        break;
    case 90:
        r--;
        break;
    case 180:
        c--;
        break;
    case 270:
        r++;
        break;
    }

    if (r < 0)
        r = max_rows-1;
    if (c < 0)
        c = max_cols-1;
    if (r >= max_rows)
        r %= max_rows;
    if (c >= max_cols)
        c %= max_cols;
}
