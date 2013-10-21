#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define PARSING_FILE_EXIT_EOF 3
#define PARSING_FILE_NON_CMD_LINE 2

#include "desc/desc.h"

const DESC* DESC_ARRAY;
const int DESC_ARRAY_LENGTH;
const char* DESC_DIR = "./descs/"; 

const char* REG_NAMES[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};

/***----------------------------------------------------------------------***/
/***          TYPES DE DONNEES                                            ***/
/***----------------------------------------------------------------------***/

/* ATTENTION: les tailles de (unsigned char) et (unsigned int) ne sont pas
 * forcément les mêmes sur toutes les machines!!
 * Vérifiez le bien (avec sizeof) si vous travaillez en dehors de l'école*/

/* Type de donnee representant un octet (8 bits) */
typedef unsigned char BYTE;

/* Type de donnee representant un mot de 32 bits */
typedef unsigned int WORD;



/***----------------------------------------------------------------------***/
/***          CONSTANTES                                                  ***/
/***----------------------------------------------------------------------***/

/* Taille d'un segment de mémoire du simulateur (en nombre d'octets) */
#define TAILLESEGMENT 4096

/* Taille totale de la mémoire du simulateur (en nombre d'octets) */
/*     1Mo = 256 segments de 4096 octets                          */
#define TAILLEMEM TAILLESEGMENT*256

#endif