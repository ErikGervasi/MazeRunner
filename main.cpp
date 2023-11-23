// ERIK LUIZ GERVASI

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

struct Position {
    int x, y;
};

bool isValid(const vector<vector<char>>& maze, int x, int y) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] != 'X';
}

bool findPath(vector<vector<char>>& maze, Position start, Position end) {
    queue<Position> q;
    q.push(start);
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
    vector<vector<Position>> predecessors(maze.size(), vector<Position>(maze[0].size()));

    visited[start.x][start.y] = true;
    predecessors[start.x][start.y] = {-1, -1};

    bool pathFound = false;

    while (!q.empty() && !pathFound) {
        Position current = q.front(); q.pop();

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(maze, newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true;
                predecessors[newX][newY] = current;

                if (newX == end.x && newY == end.y) {
                    pathFound = true;
                    break;
                }

                q.push({newX, newY});
            }
        }
    }

    if (!pathFound) {
        cout << "\033[31m" << "Caminho não encontrado!" << "\033[0m" << endl;
        return false;
    }

    Position p = end;
    while (!(p.x == start.x && p.y == start.y)) {
        maze[p.x][p.y] = '*';
        p = predecessors[p.x][p.y];
    }
    maze[start.x][start.y] = '*'; // Marcar a posição inicial

    return true;
}

void printMaze(const vector<vector<char>>& maze) {
    for (const auto& row : maze) {
        for (char cell : row) {
            if (cell == '*') {
                cout << "\033[33m" << cell << "\033[0m" << " ";
            } else {
                cout << cell << " ";
            }
        }
        cout << endl;
    }
}

void readMazeFromFile(vector<vector<char>>& maze, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\033[31m" << "Nao foi possivel abrir o arquivo." << "\033[0m" << endl;
        return;
    }

    int rows, cols;
    file >> rows >> cols;
    maze.resize(rows, vector<char>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> maze[i][j];
        }
    }

    file.close();
}

void createMaze(vector<vector<char>>& maze, int rows, int cols) {
    maze.resize(rows, vector<char>(cols, ' '));
    cout << "Digite o labirinto (use 'X' para paredes e '_' para caminhos):" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> maze[i][j];
        }
    }
}

void saveMazeToFile(const vector<vector<char>>& maze, string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "\033[31m" << "Naoo foi possivel abrir o arquivo." << "\033[0m" << endl;
        return;
    }

    file << maze.size() << " " << maze[0].size() << endl;
    for (const auto& row : maze) {
        for (char cell : row) {
            file << cell << " ";
        }
        file << endl;
    }

    file.close();
}

int main() {
    vector<vector<char>> maze;
    string filename;
    Position start, end;
    int choice, rows, cols;


    cout << " ___________  \n";
    cout << "|           | \n";
    cout << "| LABIRINTO | \n";
    cout << "|     -     | \n";
    cout << "|   ERIK    | \n";
    cout << "|  GERVASI  | \n";
    cout << "|     -     | \n";
    cout << "|  K-HARD   | \n";
    cout << "|___________| \n" << endl;

    cout << "Como deseja jogar?" << endl;

    cout << endl << "1. Ler labirinto de arquivo" << endl;
    cout << "2. Criar novo labirinto" << endl;
    cout << endl << "Digite sua escolha: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Digite o nome do arquivo: ";
        cin >> filename;
        readMazeFromFile(maze, filename);
    } else if (choice == 2) {
        cout << "Digite o numero de linhas e colunas: ";
        cin >> rows >> cols;
        createMaze(maze, rows, cols);
        cout << "Digite o nome do arquivo para salvar: ";
        cin >> filename;
        saveMazeToFile(maze, filename);
    } else {
        cout << "Opcao invalida." << endl;
        return 1;
    }

    cout << "Digite a posicao inicial (x y): ";
    cin >> start.x >> start.y;
    cout << "Digite a posicao final (x y): ";
    cin >> end.x >> end.y;

    if (!isValid(maze, start.x, start.y) || !isValid(maze, end.x, end.y)) {
        cout << "\033[31m" << "Posicoes invalidas" << "\033[0m" << endl;
        return 1;
    }

    if (findPath(maze, start, end)) {
        printMaze(maze);
        cout << endl << "\033[31m" << "\tLabirinto finalizado" << "\033[0m" << endl;
        cout << "\033[32m" << "\tOBRIGADO POR JOGAR!!" << "\033[0m" << endl;

    }

    return 0;
}
