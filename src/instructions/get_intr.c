#include <stdio.h>#include <stdlib.h>#include <math.h>#include "arch/arch.h"#include "desc/desc.h"#include "instructions/instructions.h"#include "instructions/parser_instructions.h"#include "instructions/get_instructions.h"#include "notify.h"#include "helpers.h"DESC* DESC_ARRAY;int DESC_ARRAY_LENGTH;int get_instr(uint val){    uint opcode;    uint function;    int c, R;    opcode = parser_instr(val, 26, 31);    if (opcode == 0) {        function = parser_instr(val, 0, 5);        R = parser_instr(val, 21, 21);        c = matchR(function);        if (function == 2) {            if (R == 1)                return get_desc_id("ROTR");            else                return get_desc_id("SRL");        }        if (c == NO_MATCH)            return NO_MATCH;    }    else {        c = matchJI(opcode);        if (c == NO_MATCH)            return NO_MATCH;    }    return c;}int matchJI(uint opcode){	for (int i = 0 ; i < DESC_ARRAY_LENGTH; i++) {        if ((DESC_ARRAY+i)->opcode == opcode)            return i;    }    return NO_MATCH;}int matchR(uint function){	for (int i = 0 ; i < DESC_ARRAY_LENGTH; i++) {		if ((DESC_ARRAY+i)->function == function)            return i;    }    return NO_MATCH;}