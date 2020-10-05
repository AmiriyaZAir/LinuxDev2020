#include <curses.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

size_t text_size = 0;
size_t dynamic_size = 1;
char **text = NULL;

size_t dummy;

FILE *fp;

void GetText(const char *filename) {
    if (!(fp = fopen(filename, "r"))) {
        printf("FILE: %s NOT FOUND!\n", filename);

        exit(-1);
    }

    char *str = NULL;
    
    while (getline(&str, &dummy, fp) != -1) {
        if (dynamic_size <= text_size || !text) {
            dynamic_size <<= 1;
            text = realloc(text, sizeof(char*) * dynamic_size);
        }

        text[text_size] = malloc(sizeof(char) * (strlen(str) + 1));
        strncpy(text[text_size++], str, strlen(str) - 1);
    }

    if (str) {
        free(str);
    }

    fclose(fp);
}

int main (int argc, const char** argv)
{
    WINDOW *win;
    
    if (argc <= 1) {
        printf("NO FILE!\n");

        return -1;
    }

    GetText(argv[1]);

    initscr();
    noecho();
    cbreak();
    
    printw("File: %s | Lines: %d\n", argv[1], text_size);
    refresh();

    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);

    int scroll = 0;
    int currentSymbol= 0;

    do {
        werase(win);

        if (currentSymbol == 32) {
            scroll += scroll + LINES - 2 * DX - 1 <= text_size;
        }

        for (int line = 0; line < LINES - 2 * DX - 1; line++) {
            if (scroll + line >= text_size) {
                break;
            }
            
            wprintw(win, "\n %2d: %s", scroll + line + 1, text[scroll + line]);
        }
        
        box(win, 0, 0);
        wrefresh(win);
    } while((currentSymbol = wgetch(win)) != 27);
    
    for (int i = 0; i < text_size; i++) {
        free(text[i]);
    }

    free(text);

    endwin();

    return 0;
}