#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "arch/arch.h"

#include "desc/desc.h"

#include "instr/parser_instru.h"
#include "instr/affiche_instru.h"

int affichage_instr(uint val, DESC *R, DESC *JI)
{
    uint opcode;
    uint function;
    int c;



    opcode=parser_instr(val,26,31);
    if (opcode == 0)
    {
        function=parser_instr(val,0,5);

        c=matchR(function , R);
        afficher_typeR(R,c,val);
    }
    else
    {
        c=matchJI(opcode , JI);
        if ( JI[c].type == 'I' )
        {
            afficher_typeI(JI, c,val);
        }
        else
        {
            afficher_typeJ(JI,c,val);
        }
    }

    return 1;
}

int afficher_typeR( DESC *R, int c, uint val)
{
    uint rs;
    uint rt;
    uint rd;
    uint sa;
    int B;

    parser_typeR(val,&rs,&rt,&rd,&sa);

    switch (R[c].function)
    {
        case 32: case 36 : case 37: case 42: case 34: case 38: //ADD AND OR SLT SUB XOR
        fprintf(stdout,"%s $%u,$%u,$%u\n",R[c].name,rd,rs,rt);
        break;

        case 26: case 24: //DIV MULT
        fprintf(stdout,"%s $%u,$%u\n",R[c].name,rs,rt);
        break;

        case 16: case 18: //MFHI MFLO
        fprintf(stdout,"%s $%u\n",R[c].name,rd);
        break;

        case 8: //JR
        fprintf(stdout,"%s $%u\n",R[c].name,rs);
        break;

        case 2: //RTOR SRL
        B=parser_instr(val,21,21);
        if (B==1)
        {
            fprintf(stdout,"RTOR $%u,$%u,$%u\n",rd,rt,sa);
        }
        else
        {
            fprintf(stdout,"SRL $%u,$%u,$%u\n",rd,rt,sa);
        }
        break;

        case 0: //SLL NOP
        if (rs==0 && rt==0 && rd==0 && sa==0)
        {
            fprintf(stdout,"NOP\n");
        }
        else
        {
            fprintf(stdout,"%s $%u,$%u,$%u\n",R[c].name,rd,rt,sa);
        }
        break;

        default :
        fprintf(stderr,"erreur function inexistant\n");
        return -1;
    }
    return 1;
}

int afficher_typeI(DESC *JI, int c, uint val)
{
    uint rs;
    uint rt;
    uint immediate;
    parser_typeI(val,&rs,&rt,&immediate);

    switch (JI[c].opcode)
    {
        case 8: //ADDI
        fprintf(stdout,"%s $%u,$%u,%u\n",JI[c].name,rt,rs,immediate);
        break;

        case 4: case 5: //BEQ BNE
        fprintf(stdout,"%s $%u,$%u,%u\n",JI[c].name,rs,rt,immediate);
        break;

        case 7: case 6: //BGTZ BLEZ
        fprintf(stdout,"%s $%u,%u\n",JI[c].name,rs,immediate);
        break;

        case 15: //LUI
        fprintf(stdout,"%s $%u,%u\n",JI[c].name,rt,immediate); // normalement le immediate doit être en base 16 comment faire?
        break;

        case 35: case 43: //LW SW
        fprintf(stdout,"%s $%u,%u($%u)\n",JI[c].name,rt,immediate,rs);
        break;

        default :
        fprintf(stderr,"erreur opcode inexistant\n");
        return -1;

    }
    return 1;
}

int afficher_typeJ(DESC *JI, int c, uint val)
{
    uint target;
    parser_typeJ(val,&target);
    fprintf(stdout,"%s %u\n",JI[c].name,target); // normalement le target doit etre en base 2 comment faire?
    return 1;
}

int matchJI(uint opcode, DESC *JI )
{
    int c = 0;

    while (c<12)
    {
        if ( (JI+c)->opcode == opcode )
        {
            return c;
        }
        else
        {
            c++;
        }
    }
    return -1; //erreur : l'opcode n'existe pas dans le tableau
}

int matchR(uint function, DESC *R)
{
    int c = 0;

    while (c<14)
    {
        if ( (R+c)->function == function )
        {
            return c;
        }
        else
        {
            c++;
        }
    }
     return -1; //erreur : le function n'existe pas dans le tableau
}
