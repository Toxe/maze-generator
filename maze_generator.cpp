#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

struct Node {
    bool visited = false;
    bool has_north_wall = true;
    bool has_east_wall = true;
    bool has_south_wall = true;
    bool has_west_wall = true;
};

void coord_in_direction(const int x, const int y, const int dir, int* nx, int* ny)
{
    *nx = x;
    *ny = y;

    switch (dir) {
    case 0:
        *nx = x;
        *ny = y - 1;
        break;
    case 1:
        *nx = x + 1;
        *ny = y;
        break;
    case 2:
        *nx = x;
        *ny = y + 1;
        break;
    case 3:
        *nx = x - 1;
        *ny = y;
        break;
    }
}

Node* node_at(Node* maze, const int num_cols, const int x, const int y)
{
    return &maze[y * num_cols + x];
}

void print(Node* maze, const int num_rows, const int num_cols)
{
    for (int y = 0; y < num_rows; ++y) {
        for (int x = 0; x < num_cols; ++x) {
            const Node* node = node_at(maze, num_cols, x, y);

            if (node->has_north_wall)
                std::cout << "+--";
            else
                std::cout << "+  ";
        }

        std::cout << "+" << std::endl;

        for (int x = 0; x < num_cols; ++x) {
            const Node* node = node_at(maze, num_cols, x, y);

            if (node->has_west_wall)
                std::cout << "|  ";
            else
                std::cout << "   ";

            if (x == num_cols - 1)
                if (node->has_east_wall)
                    std::cout << "|" << std::endl;
        }


        if (y == num_rows - 1) {
            for (int x = 0; x < num_cols; ++x) {
                const Node* node = node_at(maze, num_cols, x, y);

                if (node->has_south_wall)
                    std::cout << "+--";
                else
                    std::cout << "+  ";
            }

            std::cout << "+" << std::endl;
        }
    }
}

void visit(Node* maze, const int num_rows, const int num_cols, const int x, const int y)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> directions{0, 1, 2, 3};
    std::shuffle(directions.begin(), directions.end(), g);

    Node* current_node = node_at(maze, num_cols, x, y);

    current_node->visited = true;

    for (auto dir : directions) {
        int nx, ny;
        coord_in_direction(x, y, dir, &nx, &ny);

        if (nx >= 0 && ny >= 0 && nx < num_cols && ny < num_rows) {
            Node* next_node = node_at(maze, num_cols, nx, ny);

            if (!next_node->visited) {
                switch (dir) {
                case 0:
                    current_node->has_north_wall = false;
                    next_node->has_south_wall = false;
                    break;
                case 1:
                    current_node->has_east_wall = false;
                    next_node->has_west_wall = false;
                    break;
                case 2:
                    current_node->has_south_wall = false;
                    next_node->has_north_wall = false;
                    break;
                case 3:
                    current_node->has_west_wall = false;
                    next_node->has_east_wall = false;
                    break;
                }

                visit(maze, num_rows, num_cols, nx, ny);
            }

        }
    }
}

int main()
{
    constexpr int num_rows = 10;
    constexpr int num_cols = 10;

    Node maze[num_rows * num_cols];

    visit(maze, num_rows, num_cols, 0, 0);
    print(maze, num_rows, num_cols);
}
