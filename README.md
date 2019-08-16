# Maze Generator
A C++ maze generator that uses recursive backtracking.

It is not using a recursive function to generate the maze but is using its own data stack to store backtracking information which in return means the mazes can be arbitrarily big and we are not limited by the size of the call stack.

## Usage
```
$ ./maze_generator
SYNOPSIS
        maze_generator [-s <seed>] [-z <zoom>] <width> <height> <filename>

OPTIONS
        -s, --seed <seed>
                    random seed (0 or bigger)

        -z, --zoom <zoom>
                    pixel zoom factor for .raw files (default: 1)

        <width>     maze width
        <height>    maze height
        <filename>  output filename (has to end in .maze or .raw)

EXAMPLE
        maze_generator 20 20 test.maze
```
