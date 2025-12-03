#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Maze {
private:
    char grid[20][20];
    bool solvable;

    bool dfs(int r, int c, bool visited[20][20]) {
        
        if (r < 0 || r >= 20 || c < 0 || c >= 20)
            return false;

        
        if (grid[r][c] == '#' || visited[r][c])
            return false;

        if (grid[r][c] == 'E')
            return true;

        visited[r][c] = true;

        return dfs(r + 1, c, visited) ||
               dfs(r - 1, c, visited) ||
               dfs(r, c + 1, visited) ||
               dfs(r, c - 1, visited);
    }

public:
    Maze(ifstream &fin) {
        string line;

        for (int r = 0; r < 20; r++) {
            getline(fin, line);
            for (int c = 0; c < 20; c++) {
                grid[r][c] = line[c];
            }
        }

        if (fin.peek() == '\n')
            fin.get();

        int startR = -1, startC = -1;
        for (int r = 0; r < 20; r++) {
            for (int c = 0; c < 20; c++) {
                if (grid[r][c] == 'S') {
                    startR = r;
                    startC = c;
                }
            }
        }

        bool visited[20][20] = {false};
        solvable = dfs(startR, startC, visited);
    }

    string toString() {
        return string("Maze: ") + (solvable ? "YES" : "NO");
    }
};

int main() {
    ifstream fin("maze.dat");

    if (!fin) {
        cout << "Error: could not open maze.dat\n";
        return 1;
    }

    while (fin.peek() != EOF) {
        Maze m(fin);
        cout << m.toString() << endl;
    }

    return 0;
}