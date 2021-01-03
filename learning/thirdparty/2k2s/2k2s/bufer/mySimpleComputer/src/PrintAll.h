#ifndef PRINTALL_H
#define PRINTALL_H

#include <stdio.h>
#include "memory.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"

#define BOX_ROW_MEMORY 12
#define BOX_COLUMN_MEMORY 61

#define MINI_BOX_ROW 3
#define MINI_BOX_COLUMN 22

int instructionCounter;

int pa_ProgRun();
int pa_setBGColor(int ind, int y, int x, int y_term, int x_term);
int pa_resetBGColor(int y, int x, int y_term, int x_term);
int pa_printAll(int y, int x, int y_term, int x_term);
int pa_initprintMemory();
int pa_printBoxMemory();
int pa_printMemory();
int pa_printAccumulator();
int pa_printBoxInstructionCounter();
int pa_printInstructionCounter();
int pa_printOperation();
int pa_printFlags();
int pa_printBoxCase();
int pa_printCase(int y, int x);
int pa_printCaseBigChar(int value, int coord_y);
int pa_printKeys();

#endif