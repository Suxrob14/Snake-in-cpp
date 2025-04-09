#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;
vector<int> tailX;
vector<int> tailY;
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

int getRandom(int max) {
    return rand() % max;
}

int Setup() {
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = getRandom(width);
    fruitY = getRandom(height);
    score = 0;
    nTail = 0;
    tailX.clear();
    tailY.clear();
    return 0;
}

int Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";

            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }

            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
    return 0;
}

int Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': exit(0);
        }
    }
    return 0;
}

int Logic() {
    int prevX = x;
    int prevY = y;
    int prev2X, prev2Y;
    for (int i = 0; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            exit(0);

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = getRandom(width);
        fruitY = getRandom(height);
        tailX.push_back(x);
        tailY.push_back(y);
        nTail++;
    }
    return 0;
}

int main() {
    Setup();
    while (true) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}
