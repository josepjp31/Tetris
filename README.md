# Tetris in C++ (SDL2)

A complete version of the classic Tetris game developed in C++ as part of the **Metodologia de la Programació** course (2023-2024 academic year, UAB). It includes a graphical game, an automatic test mode, a scoring system with levels, and a leaderboard of top scores.

<!-- Add a screenshot of the game here:
![Game screenshot](docs/captura.png)
-->

## Features

- Full gameplay on a **21×11 board** with the 7 classic pieces (O, I, T, L, J, Z, S), generated randomly (type, rotation, and initial position).
- Lateral movement, rotation in both directions, and free fall, with collision detection against the board limits and placed pieces.
- Complete line clearing and gravity for the upper cells.
- Scoring, **levels** with increasing speed, and game-over detection (*GAME OVER*).
- **Test mode**: the initial board state, piece sequence, and movement sequence are read from text files and executed automatically.
- Persistent **high-score ranking** stored in a file.
- Console-based main menu; the game is displayed in a graphical window.

## Controls (normal mode)

| Key | Action |
|---|---|
| ← / → | Move the piece left / right |
| ↑ | Rotate clockwise |
| ↓ | Rotate counterclockwise |
| Space | Drop the piece to the bottom |
| Esc | Exit the game |

## Score and levels

- +10 points for each piece placed.
- +100 points for each completed line, with a bonus of +50 (2 lines at once), +75 (3 lines), or +100 (4 lines).
- Every time the score exceeds `level × 200`, the level increases and the drop interval is multiplied by 0.75 (starting at 1 s). These values are defined as constants in `Partida.h`.

## Main menu

```
1. Play in normal mode
2. Play in test mode
3. Show scores
4. Exit
```

When a normal match ends, the player is asked for their name and the score is inserted into the ranking. The ranking is loaded from `puntuacions.txt` at startup and saved when the program exits.

## Test mode

The program prompts for three file names, which must be located in `1. Resources/data/Games/`:

1. **Initial state** (same format as `partida.txt`): first line with the current piece (`tipo fila columna giro`), followed by the board matrix with a color code per cell (0 = empty, 1–7 = colors).
2. **Piece sequence**: one piece per line, `tipo fila columna giro`.
3. **Movement sequence**: one integer per line.

Piece codes: `1`=O, `2`=I, `3`=T, `4`=L, `5`=J, `6`=Z, `7`=S.
Movement codes: `0` left, `1` right, `2` rotate clockwise, `3` rotate counterclockwise, `4` move down one row, `5` drop to the bottom.

The game ends when the moves or pieces run out.

## Project structure

```
0. C++ Code/
   Graphic Lib/      Graphics library provided by the university (SDL2)
   Logic Game/       Game logic code
1. Resources/
   data/Graphics/    Sprites for the board, background, and pieces
   data/Fonts/       Font for text rendering
   data/Games/       Match and ranking files
2. Platforms/
   0. Windows Desktop/   Visual Studio solution (MP_Practica.sln)
```

### Class design (`Logic Game`)

| Class | Responsibility |
|---|---|
| `Figura` | Type, color, position, and shape of the active piece. Rotations are implemented using matrix transposition + row/column inversion. |
| `Tauler` | Board matrix; checks collisions, places pieces, and clears complete lines. |
| `Joc` | Joins `Tauler` and `Figura`: `giraFigura`, `mouFigura`, `baixaFigura`, `colocaFigura`, piece generation, and drawing. |
| `Partida` | Manages a match: keyboard input or test mode, score, level, speed, and info screen. |
| `Tetris` | Graphical loop of the game and ranking (`std::list<Puntuacio>` ordered). |
| `LlistaFigures`, `LlistaMoviments` | Queues implemented with **dynamic linked lists** (`NodeFigura`, `NodeMoviment`) for the test mode sequences. |

## Build and run

Requirements: **Windows** and **Visual Studio 2022** (v143 toolset) with C++ desktop development.

1. Open `2. Platforms/0. Windows Desktop/MP_Practica.sln`.
2. Select the **x86** configuration (the one specified in the course assignment).
3. In *Project → Properties → Debugging*, set the **Working Directory** to `$(ProjectDir)\..\..\1. Resources`, so the game can find `./data/...`.
4. Build and run.

> **Dependencies:** the project links against `SDL2`, `SDL2_image`, `SDL2_ttf`, and `libpng`. This repository includes the headers, but not the `.lib` / `.dll` files (they are excluded by `.gitignore`). You must add them under `2. Platforms/0. Windows Desktop/extlibs/` (and copy the `.dll` files next to the executable) in order to compile.

## Credits

- Assignment and graphics library (`Graphic Lib`, sprites, and font): material from the *Metodologia de la Programació* course, UAB.
- Game logic: Josep Montoro Pascual and Alejandro Zorrilla Bejarano
- Graphics and audio based on [SDL2](https://www.libsdl.org/).
