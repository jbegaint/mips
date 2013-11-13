#include <stdio.h>#include <stdlib.h>#include <math.h>#include "arch/arch.h"#include "desc/desc.h"#include "instructions/instructions.h"#include "instructions/parser_instructions.h"#include "instructions/get_instructions.h"#include "notify.h"DESC* DESC_ARRAY;int DESC_ARRAY_LENGTH;int get_instr(uint val){    uint opcode;    uint function;    int c;    opcode = parser_instr(val, 26, 31);    if (opcode == 0) {        function = parser_instr(val, 0, 5);        c = matchR(function);        if (c == NO_MATCH)            return NO_MATCH;    }    else {        c = matchJI(opcode);        if (c == NO_MATCH)            return NO_MATCH;    }    DEBUG_MSG("MATCH c: %d %s", c, DESC_ARRAY[c].name);    return c;}int matchJI(uint opcode){	for (int i = 0 ; i < DESC_ARRAY_LENGTH; i++) {        if ((DESC_ARRAY+i)->opcode == opcode)            return i;    }    return NO_MATCH;}int matchR(uint function){	for (int i = 0 ; i < DESC_ARRAY_LENGTH; i++) {		if ((DESC_ARRAY+i)->function == function)            return i;    }    return NO_MATCH;}