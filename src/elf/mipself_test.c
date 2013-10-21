/**
 * \author (c) Laurent Fesquet 2003,
 * \author (m) Matthieu Chabanas 2005
 * \author (m) François Portet 2013 <francois.portet@imag.fr>
 * \brief test main for loading ELF file in memory.
 * A compiler avec "-DVERBOSE": pour trace d'execution
 *--------------------------------------------------------------------------
 * Ce fichier contient un programme principal qui permet d'utiliser le chargeur de
 *     maniere autonome (en dehors du simulateur)
 */
#include<stdio.h>
#include<stdlib.h>
#include"mipself.h"


int main (int argc, char *argv[]) {
    SectionELF *textSection;
    SectionELF *dataSection;
    SectionELF *bssSection;

    if ((argc < 2) || (argc > 2)) {
        printf("Usage: %s <fichier elf> \n", argv[0]);
        exit(1);
    }

    /* Ne pas oublier d'allouer les differentes sections */
    textSection = (SectionELF *) malloc(sizeof(SectionELF));
    dataSection = (SectionELF *) malloc(sizeof(SectionELF));
    bssSection  = (SectionELF *) malloc(sizeof(SectionELF));


    if (mipsloader(argv[1], textSection, dataSection, bssSection)) {
        fprintf(stderr,"**** ERREUR");
        exit(1) ;
    }


    printf("\n------ Fichier ELF \"%s\" : sections lues lors du chargement ------\n", argv[1]) ;
    printELFSection(textSection);
    printELFSection(dataSection);
    printELFSection(bssSection);

    /* Faire le ménage avant de sortir */
    free(textSection);
    free(dataSection);
    free(bssSection);

    return 0;
}
