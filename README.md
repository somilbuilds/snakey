# Terminal Snake Game in C

A classic Snake game written entirely in C and built to run directly in the Windows terminal! 🐍

## About the Project
*Note: This project was built ~2 years ago when I was first starting to explore C programming, so the codebase structure is reflective of my learning journey at that time.*

I created this project to better understand foundational C concepts and explore terminal-based game development. Through this, I learned a lot about:
- Managing game loops and state in C
- Terminal screen buffer manipulation and cursor positioning (`windows.h`)
- Generating dynamic terminal borders and creating moving elements ("dot so moving dot")
- Handling asynchronous keyboard inputs without pausing the game execution (`_kbhit()` and `_getch()`)
- Creating interactive CLI experiences with custom ASCII art banners!

The repository also contains executable files (`moving_dot.exe` and `snake_border.exe`) which were small experimental builds before combining everything into the final `snakey.exe` game.

## Features
- **Custom ASCII Banner**: A fancy terminal screen that welcomes the player.
- **Local Highscore Tracking**: Saves your best score continuously across sessions in `highscore.txt`.
- **Responsive Controls**: Utilizing non-blocking I/O for smooth snake movement using `W` `A` `S` `D`.
- **Dynamic Borders**: Cleanly built terminal borders that function as the game arena boundaries.

## Setup & Running Guide

This game utilizes the `windows.h` library for terminal rendering, meaning it is designed to be compiled and run on a Windows machine.

### Prerequisites
- A Windows Operating System (for `windows.h` and `conio.h` functionality).
- A C compiler like GCC (MinGW).

### Compilation
1. Open your terminal or command prompt.
2. Navigate to the project directory:
   ```bash
   cd path/to/snakey
   ```
3. Compile the C code using GCC:
   ```bash
   gcc snakey.c -o snakey.exe
   ```

### Playing the Game
Run the compiled executable directly from the terminal:
```bash
./snakey.exe
```

**Controls**:
- `W` - Move Up
- `S` - Move Down
- `A` - Move Left
- `D` - Move Right

Enjoy!
