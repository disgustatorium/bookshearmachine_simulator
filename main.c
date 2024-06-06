#include <ncurses.h>
#include <stdlib.h>

void print_general_purpose_registers(WINDOW *win) {
    int start_y = 2;
    int start_x = 2;
    int cell_height = 3;
    int cell_width = 12; 

    // Print the title
    mvwprintw(win, start_y - 2, start_x, "Registers");

    // Print the column headers (0-F) to the left
    for (int i = 0; i < 16; i++) {
        mvwprintw(win, start_y + i * cell_height + cell_height / 2, start_x, "%X", i); // Adjusted x-coordinate to be 0 or greater
    }

    // Print the register cells
    for (int i = 0; i < 16; i++) {
        WINDOW *cell_win = derwin(win, cell_height, cell_width, start_y + (i * cell_height), start_x + 4); // Adjusted starting x-coordinate
        box(cell_win, 0, 0);
        mvwprintw(cell_win, 1, 2, "00000000"); // Printing "00000000" in each cell
        wrefresh(cell_win);
        delwin(cell_win); // Delete the window to avoid memory leak
    }
}


// Function to print the memory grid
void print_memory_grid(WINDOW *win) {
    int start_y = 2;
    int start_x = 2;
    int cell_height = 3;
    int cell_width = 6;

    // Print the title
    mvwprintw(win, start_y - 2, start_x, "Main Memory");

    // Print the row and column headers
    for (int i = 0; i < 16; i++) {
        mvwprintw(win, start_y - 1, start_x + (i * cell_width) + cell_width / 2, "%X", i);
        mvwprintw(win, start_y + (i * cell_height) + cell_height / 2, start_x - 1, "%X", i);
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            WINDOW *cell_win = derwin(win, cell_height, cell_width, start_y + (i * cell_height), start_x + (j * cell_width));
            box(cell_win, 0, 0);
            mvwprintw(cell_win, 1, 2, "00");
            wrefresh(cell_win);
            delwin(cell_win); // Delete the window to avoid memory leak
        }
    }
}

int main() {
    // Initialize ncurses
    initscr();
    noecho();
    cbreak();

    // Check if the terminal supports colors
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    // Enable color
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    // Create a window for the general-purpose registers
    int reg_height = 50;
    int reg_width = 20;
    int reg_start_y = 5;
    int reg_start_x = 10;
    WINDOW *reg_win = newwin(reg_height, reg_width, reg_start_y, reg_start_x);

    // Create a window for the memory grid
    int mem_height = 50;
    int mem_width = 100;
    int mem_start_y = 5;
    int mem_start_x = reg_start_x + reg_width + 5;
    WINDOW *mem_win = newwin(mem_height, mem_width, mem_start_y, mem_start_x);

    // Enable keypad input
    keypad(reg_win, TRUE);
    keypad(mem_win, TRUE);
    
    // Set default background color and draw box around the windows
    wbkgd(reg_win, COLOR_PAIR(0)); // Set default background color
    wbkgd(mem_win, COLOR_PAIR(0)); // Set default background color
    box(reg_win, 0, 0);
    box(mem_win, 0, 0);

    // Print registers and memory grid
    print_general_purpose_registers(reg_win);
    print_memory_grid(mem_win);
    wrefresh(reg_win);
    wrefresh(mem_win);

    // Wait for user input
    wgetch(reg_win);

    // Cleanup and end ncurses
    delwin(reg_win);
    delwin(mem_win);
    endwin();

    return 0;
}
