#pragma once

#include <stdio.h>

enum Colors {
    RESET_COLOR,
    BLACK_TXT = 30,
    RED_TXT,
    GREEN_TXT,
    YELLOW_TXT,
    BLUE_TXT,
    MAGENTA_TXT,
    CYAN_TXT,
    WHITE_TXT,

    BLACK_BKG = 40,
    RED_BKG,
    GREEN_BKG,
    YELLOW_BKG,
    BLUE_BKG,
    MAGENTA_BKG,
    CYAN_BKG,
    WHITE_BKG
};

enum ClearCodes {
    CLEAR_FROM_CURSOR_TO_END,
    CLEAR_FROM_CURSOR_TO_BEGIN,
    CLEAR_ALL
};

void setupConsole(void);
void restoreConsole(void);
void getCursorPosition(int* row, int* col);

void setTextColor(int code);

void setTextColorBright(int code);

void setBackgroundColor(int code);

void setBackgroundColorBright(int code);

void resetColor(void);

void clearScreen(void);

void clearScreenToBottom(void);

void clearScreenToTop(void);

void clearLine(void);

void clearLineToRight(void);

void clearLineToLeft(void);

void moveUp(int positions);

void moveDown(int positions);

void moveRight(int positions);

void moveLeft(int positions);

void moveTo(int row, int col);

void saveCursorPosition(void);

void restoreCursorPosition(void);