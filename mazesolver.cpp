#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 

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
    Maze(const string &filename) {
        ifstream fin(filename.c_str());
        if (!fin) {
            cerr << "Error: could not open " << filename << endl;
            solvable = false;
            return;
        }

        string line;
        for (int r = 0; r < 20; r++) {
            getline(fin, line);

            
            for (int c = 0; c < 20; c++) {
                grid[r][c] = line[c];
            }
        }

    
        int startR = -1, startC = -1;
        for (int r = 0; r < 20; r++) {
            for (int c = 0; c < 20; c++) {
                if (grid[r][c] == 'S') {
                    startR = r;
                    startC = c;
                }
            }
        }

        bool visited[20][20];
        memset(visited, false, sizeof(visited));

        if (startR == -1 || startC == -1) {
            solvable = false; 
        } else {
            solvable = dfs(startR, startC, visited);
        }
    }

    string toString() const {
        return string("Maze: ") + (solvable ? "YES" : "NO");
    }
};

int main() {
    Maze m("maze.dat");
    cout << m.toString() << endl;
    return 0;
}