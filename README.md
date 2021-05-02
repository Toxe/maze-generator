![Screenshot](images/screenshot.png)

# Maze Generator
A C++ maze generator that uses recursive backtracking.

The generator is not using a recursive function to calculate the maze but is using its own data stack to store backtracking information which in return means the mazes can be arbitrarily big and are not limited by the size of the call stack.

It supports four different output formats:

- **Text**: Uses ASCII `#` characters for walls.
- **Pretty**: Uses UNICODE line drawing characters.
- **Data**: Export the internal wall data.
- **Raw**: Generate a 1 byte per pixel grayscale raw image.

## Dependencies

- CMake
- Vcpkg

## Usage
```
$ ./maze_generator -h
Maze Generator
Usage: maze_generator.exe [OPTIONS] width height [filename]

Positionals:
  width INT REQUIRED          maze width
  height INT REQUIRED         maze height
  filename TEXT               output filename

Options:
  -h,--help                   Print this help message and exit
  -s,--seed INT               random seed (0 or bigger)
  -z,--zoom INT=1             pixel zoom factor for .raw files
  -i,--info                   output additional info
  -v                          log level (-v: verbose, -vv: debug messages)
[Option Group: output format (default: text)]
  Options:
    -t,--text Excludes: --pretty --data --raw
                                text: uses ASCII '#' characters for walls
    -p,--pretty Excludes: --text --data --raw
                                pretty: uses UNICODE line drawing characters
    -d,--data Excludes: --text --pretty --raw
                                data: export the internal wall data
    -r,--raw Excludes: --text --pretty --data
                                raw: generate a 1 byte per pixel grayscale raw image
```

# Examples

Generate 10x10 mazes with random seed 42.

## Default "text" format

```
maze_generator --seed 42 --text 10 10 example.txt
```

```
#####################
#       #   #       #
####### # # ####### #
#       # #         #
# ####### ###########
# #   #         #   #
# # # # ####### # # #
# # # # #     # # # #
# ### # # ### # # # #
#   #   # #   #   # #
### # ### # ##### # #
# # # # # #     # # #
# # # # # ##### # # #
#   #   #   # # # # #
# ####### # # # ### #
#       # # # #   # #
####### ### # ### # #
#     #   # #     # #
# ####### # # ##### #
#           #       #
#####################
```

## "Pretty" format (UNICODE line drawing characters)

```
maze_generator --seed 42 --pretty 10 10 example.pretty
```

```
┌───────────────┬───────┬───────────────┐
│               │       │               │
├────────────   │   ╷   └────────────   │
│               │   │                   │
│   ┌───────┬───┘   └───────────┬───────┤
│   │       │                   │       │
│   │   ╷   │   ┌───────────┐   │   ╷   │
│   │   │   │   │           │   │   │   │
│   └───┤   ╵   │   ┌────   │   ╵   │   │
│       │       │   │       │       │   │
├───┐   │   ┌───┤   │    ───┴───┐   │   │
│   │   │   │   │   │           │   │   │
│   ╵   │   ╵   │   └───┬───┐   │   │   │
│       │       │       │   │   │   │   │
│    ───┴───────┤   ╷   │   │   └───┤   │
│               │   │   │   │       │   │
├───────────┐   └───┤   │   └────   │   │
│           │       │   │           │   │
│    ───────┴────   ╵   │    ───────┘   │
│                       │               │
└───────────────────────┴───────────────┘
```

## "Raw" image format

### Without zoom

Without zoom this generates a 1 byte per pixel grayscale raw image.

The image dimensions are:

- image width = maze width x 2 + 1
- image height = maze height x 2 + 1

Example: Image size of a 10x10 maze is 21x21 pixels.

```
maze_generator --seed 42 --raw 10 10 example.raw
```

#### Convert raw image to PNG

##### ImageMagick

```
convert -size 21x21 -depth 8 gray:example.raw example.png
```

##### IrfanView

- Image width and height: 21
- 8 BPP grayscale

![Example](images/example.png)


### With zoom

With zoom enabled this generates a "zoom level" bytes per pixel grayscale raw image.

The image dimensions are:

- image width = zoom level x (maze width x 2 + 1)
- image height = zoom level (maze height x 2 + 1)

Example: Image size of a 10x10 maze with zoom level 10 is 210x210 pixels.

```
maze_generator --seed 42 --raw --zoom 10 10 10 example10.raw
```

#### Convert raw image to PNG

##### ImageMagick

```
convert -size 210x210 -depth 8 gray:example10.raw example10.png
```

##### IrfanView

- Image width and height: 210
- 8 BPP grayscale

![Example zoom 10](images/example_zoom10.png)

## "Data" format (dump internal data structure)

```
maze_generator --seed 42 --data 10 10 example.data
```

```
N-SW|N-S-|N-S-|NE--|N--W|NE--|N-SW|N-S-|N-S-|NE--
N--W|N-S-|N-S-|-ES-|-E-W|--SW|N-S-|N-S-|N-S-|-ES-
-E-W|N--W|NE--|N--W|--S-|N-S-|N-S-|NE--|N--W|NE--
-E-W|-ESW|-E-W|-E-W|N--W|N-S-|NE--|-E-W|-E-W|-E-W
--SW|NE--|---W|-ES-|-E-W|N--W|-ES-|--SW|-E--|-E-W
NE-W|-E-W|-E-W|NE-W|-E-W|--SW|N-S-|NE--|-E-W|-E-W
---W|-ES-|--SW|-ES-|---W|NE--|NE-W|-E-W|-ESW|-E-W
--SW|N-S-|N-S-|NE--|-ESW|-E-W|-E-W|--SW|NE--|-E-W
N--W|N-S-|NES-|--SW|NE--|-E-W|---W|N-S-|-ES-|-E-W
--SW|N-S-|N-S-|N-S-|--S-|-ES-|--SW|N-S-|N-S-|-ES-
```
