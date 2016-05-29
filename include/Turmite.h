#include <iostream>

#ifndef TURMITE_H
#define TURMITE_H

class Turmite {
public:
    int r, c, angle;
    int max_rows, max_cols;
    std::string moves;

    Turmite(int, int, int, int, int, std::string);

    void move(int);

};

#endif // TURMITE_H
