#ifndef PRINTALL_H
#define PRINTALL_H

#include "cpu.h"
#include "memory.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include "myTerm.h"

#include <stdio.h>

#define BOX_ROW_MEMORY 12
#define BOX_COLUMN_MEMORY 61

#define MINI_BOX_ROW 3
#define MINI_BOX_COLUMN 22

int pa_ProgRun();

int pa_resetTerm();
int pa_initComp();
int pa_printAllBox();

void pa_getXY(int* x, int* y);

void pa_keyPlus();
void pa_keyMinus();
void pa_keyAccumulator();
void pa_keyinstructionCounter();
void pa_keyLoad();
void pa_keySave();
void pa_keyRun();
void pa_keyStep();
void pa_keyReset();
void pa_keyNumber(enum keys key);

void pa_moveUp();
void pa_moveDown();
void pa_moveRight();
void pa_moveLeft();

int pa_resetBGColor();
int pa_setBGColor();

int pa_printMemory();
int pa_printAccumulator();
int pa_printInstructionCounter();
int pa_printOperation();
int pa_printFlags();
int pa_printCase();
int pa_printCaseBigChar(int value, int coord_y);

int pa_printBoxMemory();
int pa_printBoxAccumulator();
int pa_printBoxInstructionCounter();
int pa_printBoxOperation();
int pa_printBoxFlags();
int pa_printBoxCase();
int pa_printKeys();

#endif
