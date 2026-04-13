<h1 align="center">🐍 Terminal Snake in C</h1>

<p align="center">
  <strong>A classic Snake game engineered directly in the Windows terminal buffer.</strong><br>
  <em>Built approx. 2 years ago as a deep-dive into C programming, terminal buffering, and game loops.</em>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c" alt="Language C" />
  <img src="https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows" alt="Windows" />
  <img src="https://img.shields.io/badge/Status-Completed-success?style=for-the-badge" alt="Status" />
</p>

---

## 📖 Table of Contents
- [About the Project](#-about-the-project)
- [Visuals](#-visuals)
- [How It Works (Technical Details)](#-how-it-works-technical-details)
- [Installation & Setup](#-installation--setup)
- [Controls](#-controls)

---

## 🔍 About the Project

This repository contains `snakey.c`, a fully functioning Snake game that runs natively in the Windows command prompt. Built ~2 years ago, it served as an experimental playground to learn fundamental programming concepts in C. 

Before building the full game, I developed smaller modules to fundamentally understand the mechanics:
- **`moving_dot.exe`**: An experiment to understand how to move a single character across the screen seamlessly without leaving a trail.
- **`snake_border.exe`**: Built to understand how to dynamically generate a playable matrix or terminal border.

These small experiments ultimately grew into the final, polished terminal application!

---

## 📸 Visuals

*(You can add a `.gif` or screenshot of your gameplay here later!)*

**The Custom ASCII Art Welcome Banner:**
```text
███████╗ ██████╗ ███╗   ███╗██╗██╗     ███████╗
██╔════╝██╔═══██╗████╗ ████║██║██║ ██╗ ██╔════╝
███████╗██║   ██║██╔████╔██║██║██║ ╚═╝ ███████╗
╚════██║██║   ██║██║╚██╔╝██║██║██║     ╚════██║
███████║╚██████╔╝██║ ╚═╝ ██║██║███████╗███████║
╚══════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝╚══════╝╚══════╝
```

---

## ⚙️ How It Works (Technical Details)

This game avoids the jittery, flickering issues common with standard `system("cls")` animations by manually manipulating the standard output handle.

### 1. Terminal Screen Buffer (`windows.h`)
Instead of clearing the entire screen each frame, the program securely moves the console cursor to specific `X, Y` coordinates using `SetConsoleCursorPosition`.

```c
pos = (COORD){0, 0};
SetConsoleCursorPosition(hConsole, pos);
```

### 2. Non-blocking Input (`conio.h`)
To ensure the snake constantly moves without explicitly pausing the game loop for the user to press a key, `_kbhit()` and `_getch()` are actively utilized:

```c
if (_kbhit()) {
    ch = _getch();
    // Handling state updates without blocking the loop...
    if (ch == 'w' && !isDown) { isUp = 1; isDown = 0; isLeft = 0; isRight = 0; }
}
```

### 3. Hiding the Cursor
To keep the visual presentation clean and artifact-free, the blinking terminal cursor is purposefully hidden:

```c
void hidecursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = 0; // hide
    SetConsoleCursorInfo(console, &cursorInfo);
}
```

### 4. Persistent Storage
A straightforward file mechanism tracks the player's best scores by writing to `highscore.txt`, allowing for competitive continuity across multiple sessions.

---

## 🚀 Installation & Setup

Since this game relies heavily on Windows-specific libraries (`windows.h`, `conio.h`), **it is natively compatible with Windows OS**.

### Prerequisites
- Windows OS
- A C Compiler (e.g., MinGW / GCC)

### Setup Instructions
1. **Clone the Repository**
   ```bash
   git clone https://github.com/somilbuilds/snakey.git
   cd snakey
   ```

2. **Compile the Game**
   Using GCC, compile the main source file:
   ```bash
   gcc snakey.c -o snakey.exe
   ```

3. **Run the Executable**
   ```bash
   ./snakey.exe
   ```

---

## 🎮 Controls
- <kbd>W</kbd> - Move Up
- <kbd>A</kbd> - Move Left
- <kbd>S</kbd> - Move Down
- <kbd>D</kbd> - Move Right

*Tip: The game speeds up visually as you play. Try not to run into walls or your own tail!*
