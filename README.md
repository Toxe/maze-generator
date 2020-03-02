# Maze Generator
A C++ maze generator that uses recursive backtracking.

The generator is not using a recursive function to calculate the maze but is using its own data stack to store backtracking information which in return means the mazes can be arbitrarily big and are not limited by the size of the call stack.

It supports four different output formats:

- **Text**: Uses ASCII `#` characters for walls.
- **Pretty**: Uses UNICODE line drawing characters.
- **Data**: Export the internal wall data.
- **Raw**: Generate a 1 byte per pixel grayscale raw image.

## Usage
```
$ ./maze_generator
SYNOPSIS
        maze_generator [-t|-p|-d|-r] [-s <seed>] [-z <zoom>] [-i] <width> <height> [<filename>]

OPTIONS
        -t, --text|-p, --pretty|-d, --data|-r, --raw
                    output format (default: text)

        -s, --seed <seed>
                    random seed (0 or bigger)

        -z, --zoom <zoom>
                    pixel zoom factor for .raw files (default: 1)

        -i, --info  output additional info
        <width>     maze width
        <height>    maze height
        <filename>  output filename

EXAMPLE
        maze_generator 20 20 test.maze
```
