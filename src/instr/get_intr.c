#include <stdio.h>#include <stdlib.h>#include <math.h>#include "arch/arch.h"
#include "desc/desc.h"

#include "instr/instructions.h"
#include "instr/parser_instru.h"
#include "instr/get_instr.h"

#include "notify.h"

extern DESC* DESC_ARRAY;
extern DESC_ARRAY_LENGTH;

int get_instr(uint val)
{
    uint opcode;    uint function;    int c;    opcode = parser_instr(val, 26, 31);    if (opcode == 0){        function = parser_instr(val, 0, 5);        c = matchR(function);        if (c == NO_MATCH)            return NO_MATCH;    }    else {        c = matchJI(opcode);        if (c == NO_MATCH)            return NO_MATCH;    }    return c;
}

int matchJI(uint opcode){	int i;	for (i = 0 ; i < DESC_ARRAY_LENGTH; i++) {        if ( (DESC_ARRAY+i)->opcode == opcode ){            return i;        }    }    return NO_MATCH;}int matchR(uint function){	int i;	for (i = 0 ; i < DESC_ARRAY_LENGTH; i++)		if ((DESC_ARRAY+i)->function == function)            return i;    return NO_MATCH;}