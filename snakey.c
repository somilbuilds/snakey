#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
// ====== Global Variables ======
typedef struct {
    int x;
    int y;
} coord;

char ch;

COORD pos;
HANDLE hConsole;
int snake_length;
coord snake[800];
coord food;

void hidecursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = 0; // hide
    SetConsoleCursorInfo(console, &cursorInfo);
}

// ====== Highscore helpers ======
int getHighScore() {
    FILE *fp = fopen("highscore.txt", "r");
    int hs = 0;
    if (fp != NULL) {
        if (fscanf(fp, "%d", &hs) != 1) hs = 0;
        fclose(fp);
    }
    return hs;
}

void saveHighScore(int score) {
    FILE *fp = fopen("highscore.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%d", score);
        fclose(fp);
    }
}
// ================================

// ====== Main Function ======
int main() {
    system("cls");
    srand(time(NULL));

    // get console handle/key
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // dimensions of the border/arena
    int border_hori = 42;
    int border_vert = 22;

    // load highscore
    int highscore = getHighScore();

    hidecursor();

    // ===== Outer loop for restart =====
    while (1) {
        system("cls");

        // reset snake & food
        food.x = rand() % (40) + 1;
        food.y = rand() % (20) + 1;
        snake_length = 2;
        int a = border_hori / 2;
        int b = border_vert / 2;
        snake[0] = (coord){a, b};
        snake[1] = (coord){a - 1, b};

        int isUp = 0, isDown = 0, isLeft = 0, isRight = 0;

        // banner
        pos = (COORD){43, 1};
        SetConsoleCursorPosition(hConsole, pos);
        printf("███████╗ ██████╗ ███╗   ███╗██╗██╗     ███████╗");
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
        printf("██╔════╝██╔═══██╗████╗ ████║██║██║ ██╗ ██╔════╝");
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
        printf("███████╗██║   ██║██╔████╔██║██║██║ ╚═╝ ███████╗");
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
        printf("╚════██║██║   ██║██║╚██╔╝██║██║██║     ╚════██║");
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
        printf("███████║╚██████╔╝██║ ╚═╝ ██║██║███████╗███████║");
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
        printf("╚══════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝╚══════╝╚══════╝");
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("███████╗██╔██╗ ██║███████║█████╔╝ █████╗"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("███████║██║ ╚████║██║  ██║██║  ██╗███████╗"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf(" ██████╗  █████╗ ███╗   ███╗███████╗"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("██╔════╝ ██╔══██╗████╗ ████║██╔════╝"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("██║  ███╗███████║██╔████╔██║█████╗"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗"); 
        pos.Y++; SetConsoleCursorPosition(hConsole, pos); 
        printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝");

        pos.Y += 2;
        SetConsoleCursorPosition(hConsole, pos);
        printf("Local Highscore: %d", highscore);

        // ====== Game Loop ======
        while (1) {
            pos = (COORD){0, 0};
            SetConsoleCursorPosition(hConsole, pos);

            for (int i = 0; i < border_vert; i++) {
                for (int j = 0; j < border_hori; j++) {
                    int isSnake = 0, isHead = 0, isFood = 0;

                    // borders
                    if (i == 0 || i == border_vert - 1 || j == 0 || j == border_hori - 1) {
                        printf("█");
                        continue;
                    }

                    // snake / food
                    for (int k = 0; k < snake_length; k++) {
                        if (j == snake[k].x && i == snake[k].y) {
                            isSnake = 1;
                            if (k == 0) isHead = 1;
                            break;
                        } else if (j == food.x && i == food.y) {
                            isFood = 1;
                            break;
                        }
                    }

                    if (isSnake) {
                        if (isHead) printf("@");
                        else printf("O");
                    } else if (isFood) {
                        printf("*");
                    } else {
                        printf(" ");
                    }
                }
                printf("\n");
            }

            if (snake[0].x == food.x && snake[0].y == food.y) {
                snake_length++;
                food.x = rand() % (border_hori - 2) + 1;
                food.y = rand() % (border_vert - 2) + 1;
            }

            if (_kbhit()) {
                ch = _getch();
                if (ch == 'w' && !isDown) { isUp = 1; isDown = isLeft = isRight = 0; }
                if (ch == 's' && !isUp) { isDown = 1; isUp = isLeft = isRight = 0; }
                if (ch == 'a' && !isRight) { isLeft = 1; isUp = isDown = isRight = 0; }
                if (ch == 'd' && !isLeft) { isRight = 1; isUp = isDown = isLeft = 0; }
            }

            if (isUp) {
                for (int l = snake_length - 1; l > 0; l--) snake[l] = snake[l - 1];
                snake[0].y--;
            }
            if (isDown) {
                for (int l = snake_length - 1; l > 0; l--) snake[l] = snake[l - 1];
                snake[0].y++;
            }
            if (isLeft) {
                for (int l = snake_length - 1; l > 0; l--) snake[l] = snake[l - 1];
                snake[0].x--;
            }
            if (isRight) {
                for (int l = snake_length - 1; l > 0; l--) snake[l] = snake[l - 1];
                snake[0].x++;
            }

            pos = (COORD){43, border_vert - 1};
            SetConsoleCursorPosition(hConsole, pos);
            printf("Live score: %d   ", snake_length - 2); // spaces to clear old text

            // ===== Collision / Game over =====
            for (int k = 1; k < snake_length; k++) {
                if ((snake[0].x == snake[k].x && snake[0].y == snake[k].y) ||
                    snake[0].x == 0 || snake[0].x == border_hori - 1 ||
                    snake[0].y == 0 || snake[0].y == border_vert - 1) {

                    int finalScore = snake_length - 2;
                    pos = (COORD){border_hori / 2 - 10, border_vert / 2 - 5};
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("GAME OVER!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Score: %d", finalScore);

                    if (finalScore > highscore) {
                        highscore = finalScore;
                        saveHighScore(highscore);
                        pos.Y++;
                        SetConsoleCursorPosition(hConsole, pos);
                        printf("New Highscore!");
                    }

                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Highscore: %d", highscore);
                    
                    pos.Y += 2;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Play again? (Y/N)");

                    char choice;
                    while (1) {
                        choice = _getch();
                        if (choice == 'y' || choice == 'Y') break; // restart outer loop
                        if (choice == 'n' || choice == 'N') exit(0);
                    }
                    goto restartGame; // break inner loop safely
                }
            }

            Sleep(10);
        }

        restartGame: ; // label for restart
    }
}
