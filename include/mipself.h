/**
 * \author (c) Laurent Fesquet 2003,
 * \author (m) Matthieu Chabanas 2005
 * \author (m) Fran�ois Portet 2013 <francois.portet@imag.fr>
 * @file mipself.h
 * @brief interface du chargement en memoire d'un fichier ELF.
 *
 * interface du chargement en memoire d'un fichier ELF.
 */

#ifndef _MIPSELF_H_
#define _MIPSELF_H_

#include "elfimport.h"
#include "global.h"	// Types BYTE, WORD, constantes...


#define NUMZONE 3    /* Nombre de zones: text, data et bss  */


/**
 * @brief Type de donn�es SectionELF
 *! Definition des informations d'une section ELF :
 * (nom, donn�es, taille des donn�es, adresse m�moire de la section, ...)
 * Cette structure d'�change, quasi-�quivalente � la structure MemZone
 * d�finie dans mipsloader.c, est ind�pendante de la librairie ELF.
 * Elle est est utilis�e pour les interfaces avec le shell!
 */


typedef struct {
    char  *name ;         // Nom de la section
    WORD   size;          // Taille de la section (en nombre de BYTE)
    BYTE  *data;          // Les donn�es contenues dans la section, sous forme d'un tableau de 'size' octets.
    WORD   startAddress;  // Adresse du d�but la section en memoire
} SectionELF ;


/*--------------------------------------------------------------------------*/
/**
 * @brief Type de donn�es zone
 *! Definition des informations d'une section ELF :
 * (nom, donn�es, taille des donn�es, adresse m�moire de la section, ...)
 * + acces aux differentes sections du fichier ELF.
 * Cette structure de donn�es est completement d�pendante de la librairie ELF.
 */

typedef struct
{
    Elf_Scn       *scn ;       	// section elf correspondante,
    // doit valoir NULL si section absente
    char          *name ;      	// nom de la zone
    Elf32_Half     index ;    	// index de la section elf correspondante
    Elf32_Half     type ;      	// type elf de la section: SHT_PROGBITS ou SHT_NOBITS
    Elf32_Word     size ;      	// taille de la section
    Elf32_Word     mem_start ; 	// debut de la zone en memoire
    Elf_Scn       *rel_scn ;   	// section elf de relocation correspondante,
    // doit valoir NULL si section absente
    char          *rel_name ;  	// nom de la zone de reloc
    unsigned char *data ;      	// tableau des donnees (octets) lues dans le fichier ELF

    SectionELF    *exportSection; // attribut SectionELF associ� (ind�pendant de libelf),
    // qui sera export� dans la fonction mipsloader.
    // Contient notamment les donn�es binaires de la zone!
} MemZone ;


void printELFSection(SectionELF *section);

char *relocName (unsigned char type);

char *shtName (Elf32_Word SectionType);

char *stName (unsigned char t);

char *getSectionHeaderName(Elf32_Word index);

char *getName(Elf32_Word index);

Elf32_Sym *getSymb(Elf32_Word index);

void freeHashTable();

int hashCode(unsigned long adr);

void addSymbol (unsigned long adr, char *ident);

char *getAddressName (unsigned long adr);


int mipsloader(const char *filename, SectionELF *textSection, SectionELF *dataSection, SectionELF *bssSection);


#endif
