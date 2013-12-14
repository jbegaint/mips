/**
 * \author (c) Laurent Fesquet 2003,
 * \author (m) Matthieu Chabanas 2005
 * \author (m) François Portet 2013 <francois.portet@imag.fr>
 * \brief loading ELF file in memory.
 * A compiler avec "-DVERBOSE": pour trace d'execution
 *--------------------------------------------------------------------------
 * Ce fichier contient tout un ensemble de fonction pour la lecture d'un
 * fichier au format ELF.
 * Tout ce qui peut etre utile dans les autres modules est declare dans le
 * fichier mipself.h. Le contenu de ce fichier .c
 *
 * Vous trouverez dans mipself.c :
 *   - des routines d'acces a des champs ELF (differentes tables, ....)
 *   - des outils basés sur une table de hachage (qui permettent de retrouver
 *			l'adresse memoire a laquelle un symbole est defini).
 *   - des operations sur les zones memoires (sections) a lire.
 *     A la fin du projet, vous devrez avoir complete la fonction
 *	   relocZone pour effectuer la relocation d'une section!
 *   - la fonction mipsloader elle-meme qui lit le fichier ELF et en
 *     extrait les informations necessaires pour les charger en memoire.
 *
 * VOUS N'AVEZ PAS BESOIN DE TOUT COMPRENDRE DANS LES DETAILS!!
 * La fin du fichier (relocation + mipsloader) est la partie la plus
 * importante pour vous.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#include "elf/elfimport.h"
#include "elf/mipself.h"

#include "notify.h"
#include "utils.h"
#include "arch/arch.h"
#include "helpers.h"



/*--------------------------------------------------------------------------*/
/* Table des chaines pour les entetes de sections                           */
static char *Shstrtab = NULL;
static Elf32_Word Shstrtab_size;

/*--------------------------------------------------------------------------*/
/* Table des chaines (noms de symbole)                                      */
static char *StringTable = NULL;
static Elf32_Word StringTableSize;

/*--------------------------------------------------------------------------*/
/* Table des symboles                                                       */
static Elf32_Sym *SymbolTable = NULL;
static Elf32_Word SymbNum = 0;	/* nombre de symboles */
static Elf32_Word SymbInd;	/* index de la section table des symboles dans le elf */


/*--------------------------------------------------------------------------*/
/* Noms des types de relocation elf                                         */
char *relocName(unsigned char type)
{
	switch (type) {
	case R_MIPS_NONE:
		return "NONE";
	case R_MIPS_16:
		return "16";
	case R_MIPS_32:
		return "32";
	case R_MIPS_REL32:
		return "REL32";
	case R_MIPS_26:
		return "26";
	case R_MIPS_HI16:
		return "HI16";
	case R_MIPS_LO16:
		return "LO16";
	case R_MIPS_GPREL16:
		return "GPREL16";
	case R_MIPS_LITERAL:
		return "LITERAL";
	case R_MIPS_GOT16:
		return "GOT16";
	case R_MIPS_PC16:
		return "PC16";
	case R_MIPS_CALL16:
		return "CALL16";
	case R_MIPS_GPREL32:
		return "GPREL32";
	case R_MIPS_GOTHI16:
		return "GOTHI16";
	case R_MIPS_GOTLO16:
		return "GOTLO16";
	case R_MIPS_CALLHI16:
		return "CALLHI16";
	case R_MIPS_CALLLO16:
		return "CALLLO16";
	default:
		return "??";
	}
}


/*--------------------------------------------------------------------------*/
/* Noms des types de section elf                                            */
char *shtName(Elf32_Word SectionType)
{
	switch (SectionType) {
	case SHT_NULL:
		return "SHT_NULL";
	case SHT_PROGBITS:
		return "SHT_PROGBITS";
	case SHT_SYMTAB:
		return "SHT_SYMTAB";
	case SHT_STRTAB:
		return "SHT_STRTAB";
	case SHT_RELA:
		return "SHT_RELA";
	case SHT_HASH:
		return "SHT_HASH";
	case SHT_DYNAMIC:
		return "SHT_DYNAMIC";
	case SHT_NOTE:
		return "SHT_NOTE";
	case SHT_NOBITS:
		return "SHT_NOBITS";
	case SHT_REL:
		return "SHT_REL";
	case SHT_SHLIB:
		return "SHT_SHLIB";
	case SHT_DYNSYM:
		return "SHT_DYNSYM";
	case SHT_NUM:
		return "SHT_NUM";
	case SHT_LOOS:
		return "SHT_LOOS";
	case SHT_GNU_verdef:
		return "SHT_GNU_verdef";
	case SHT_GNU_verneed:
		return "SHT_GNU_verneed";
	case SHT_GNU_versym:
		return "SHT_GNU_versym";
	case SHT_LOPROC:
		return "SHT_LOPROC";
	case SHT_HIPROC:
		return "SHT_HIPROC";
	case SHT_LOUSER:
		return "SHT_LOUSER";
	case SHT_HIUSER:
		return "SHT_HIUSER";
	default:
		return "??";
	}
}

/*--------------------------------------------------------------------------*/
/* Noms des types de symboles elf                                           */
char *stName(unsigned char t)
{
	switch (t) {
	case STT_NOTYPE:
		return "NOTYPE";
	case STT_OBJECT:
		return "OBJECT";
	case STT_FUNC:
		return "FUNC";
	case STT_SECTION:
		return "SECTION";
	case STT_FILE:
		return "FILE";
	case STT_NUM:
		return "NUM";
	default:
		return "??";
	}
}



//----------------------------------------------------------------------***/
//          FONCTIONS D'ACCES AUX DONNEES ELF                           ***/
//----------------------------------------------------------------------***/



/*--------------------------------------------------------------------------*/
/*
 * @param index indice de la section à récupérer dans la table des en-têtes ELF
 * @brief Acces au nom d'header d'une section à partir de l'index de la section ELF
 *
 */
char *getSectionHeaderName(Elf32_Word index)
{
	if (Shstrtab == NULL)
		ERROR_MSG("Table des noms de section inexistante");
	if (index >= Shstrtab_size) {
		ERROR_MSG("Num de section inexistant %d", (int) index);
	}
	return &Shstrtab[index];
}


/*--------------------------------------------------------------------------*/
/*
 * @param index indice de la chaine à récupérer dans la table des chaines ELF
 * @brief Acces à un nom dans la table des chaines ELF
 *
 */
char *getName(Elf32_Word index)
{
	char* name;
	if (StringTable == NULL)
		ERROR_MSG("Table des chaines inexistante");
	if (index >= StringTableSize) {
		ERROR_MSG("Num de chaine inexistant %d", (int) index);
	}

	name = &StringTable[index];
	return name;
}


/*--------------------------------------------------------------------------*/
/*
 * @param index indice du symbole à récupérer dans la table des symboles ELF
 * @brief Accès à un nom de symbole dans la table des symboles ELF
 *
 */
Elf32_Sym *getSymb(Elf32_Word index)
{
	if (SymbolTable == NULL)
		ERROR_MSG("Table des symboles inexistante");
	if (index >= SymbNum) {
		ERROR_MSG("Num. de symbole inexistant %d", index);
	}
	return &SymbolTable[index];
}


//----------------------------------------------------------------------***/
//          TABLE DE HACHAGE pour les symboles                          ***/
//          La cle de hachage est l'adresse des symboles.
//----------------------------------------------------------------------***/

// Ces opérations servent à retrouver si des symboles existent à une adresse donnée en mémoire

#define HASHSIZE 37

/*--------------------------------------------------------------------------*/
struct nodeSymbol {
	unsigned long adr;	// adresse memoire
	char *name;		// nom du symboles
	struct nodeSymbol *suiv;	// symbol suivante (liste chainee)
};

/*--------------------------------------------------------------------------*/
typedef struct nodeSymbol *listSymboles;

/*--------------------------------------------------------------------------*/
/** SymbHashTable est la table de hachage initialisée à zéro au démarrage du programme*/
static listSymboles SymbHashTable[HASHSIZE] = { 0 };

/*--------------------------------------------------------------------------*/
/*
 *
 * @brief libere la memoire occupee par la table precedente
 *
 * on part du principe que la table a été correctement initialisée à zéro
 */
void freeHashTable()
{

	int i;
	listSymboles l, aux;
	for (i = 0; i < HASHSIZE; i++) {
		l = SymbHashTable[i];
		while (l != NULL) {
			aux = l->suiv;
			free(l->name);
			free(l);
			l = aux;
		}
		SymbHashTable[i] = NULL;
	}
}

/*--------------------------------------------------------------------------*/
int hashCode(unsigned long adr)
{
	return adr % HASHSIZE;
}

/*--------------------------------------------------------------------------*/
/*
 * @param adr	Adresse du symbole à ajouter
 * @param iden nom du symoble à ajouter
 * @brief Ajout d'un symbole (adresse, nom) a la table de hachage.
 * La cle de hachage est l'adresse.
 *
 * on ne verifie pas que l'adr est deja presente !
 * mais on verifie que le symbole est acceptable
 */
void addSymbol(unsigned long adr, char *ident)
{

	int h = hashCode(adr);
	listSymboles list = SymbHashTable[h];

	if (ident == NULL || !strcmp(ident, "")) {
		return;
	}
	SymbHashTable[h] = calloc(1, sizeof(struct nodeSymbol));
	SymbHashTable[h]->suiv = list;
	SymbHashTable[h]->adr = adr;
	SymbHashTable[h]->name = calloc(strlen(ident) + 1, 1);
	strcpy(SymbHashTable[h]->name, ident);
}


/*--------------------------------------------------------------------------*/
/*     Recherche du nom d'une adresse                                       */
/*--------------------------------------------------------------------------*/
/*
 * @param adr adresse
 * @return NULL si aucun symbole n'existe pour cette adresse
 *              sinon le symbole associé à cette adresse
 *              si plusieurs symboles a la meme adresse, retourne tjs le meme symbole
 * @brief recherche du nom d'une adresse
 */
char *getAddressName(unsigned long adr)
{
	listSymboles list;

	list = SymbHashTable[hashCode(adr)];
	while (list != NULL && adr != list->adr)
		list = list->suiv;
	if (list == NULL)
		return NULL;
	return (list->name);
}




/*--------------------------------------------------------------------------*/
/* @param section adresse de la section à afficher
 * @brief printELFSection : affiche le contenu d'une Section ELF à l'écran
 */
void printELFSection(SectionELF * section)
{
	WORD i, address;
	char *nom;

	if (!section) {
		WARNING_MSG("Pas de section a afficher! (null)");
		return;
	}

	DEBUG_MSG("Affichage de la section %s (%d octets)", section->name, section->size);

	for (i = 0; i < section->size; i++) {
		// adresse memoire du ieme octet de la zone
		address = section->start_addr + i;

		// Si un symbole est a cette adresse, on l'affiche avec l'adresse
		if ((nom = getAddressName(address)) != NULL) {
			fprintf(stderr, "\n<%s>\n %08x:\t", nom, address);
		}
		// Sinon, on affiche juste l'adresse, si elle est alignee sur 4 octets
		else if (!(address % 4))
			fprintf(stderr, "\n %08x:\t", address);

		// Affichage du ieme octet de la zone
		fprintf(stderr, "%02x ", section->data[i]);
	}
	fprintf(stderr, "\n\n");
}

/*--------------------------------------------------------------------------*/
/**
 * @param Zone segment de mémoire à initialiser
 * @param name nom de la zone à initialiser
 * @param section section à laquelle cette zone correspond (la section doit être allouée)
 * @param type type de la section (SHT_PROGBITS, SHT_NOBITS...)
 *
 * @brief Initialise une zone mémoire ELF et fait les liens entre la zone et la section
 */
static void initZone(MemZone * Zone, char *name, SectionELF * section, Elf32_Half type)
{
	Zone->scn = NULL;
	Zone->name = name;
	Zone->index = 0;
	Zone->type = type;
	Zone->rel_scn = NULL;
	Zone->rel_name = calloc(1, strlen(name) + 5);
	sprintf(Zone->rel_name, ".rel%s", name);
	Zone->size = 0;
	Zone->mem_start = 0;
	Zone->data = NULL;
	Zone->exportSection = section;
}

/*--------------------------------------------------------------------------*/
/**
 * @param Zone adresse de la zone qui acceuillera les données
 * @param from Adresse de début de section; les sections lues seront toutes séparées d'au moins une page
 *
 * @brief les préconditions sont que Zone->scn != NULL et Zone->exportSection != NULL
 * @brief chargement des données d'une zone à partir du fichier ELF
 */

static void loadZone(MemZone * Zone, WORD from)
{
	Elf_Data *data;		// donnee elf qq
	unsigned int i;

	// On charge dans le segment qui suit "from"
	Zone->mem_start = ((from % TAILLESEGMENT) == 0) ? from : (((from / TAILLESEGMENT) + 1) * TAILLESEGMENT);

	INFO_MSG("Chargement section %s a l'adresse %#x\n", Zone->name, Zone->mem_start);

	// Taille des donnees:
	data = elf_getdata(Zone->scn, NULL);
	Zone->size = data->d_size;
	// on verifie que ca rentre en memoire
	if (Zone->mem_start + Zone->size > TAILLEMEM) {
		DEBUG_MSG("Chargement de la zone %s impossible. Pas assez de place memoire\n", Zone->name);
	}
	// Remplissage des champs de la structure SectionELF
	Zone->exportSection->name = (char *) calloc((1 + strlen(Zone->name)), sizeof(char));
	strcpy(Zone->exportSection->name, Zone->name);
	Zone->exportSection->size = (WORD) Zone->size;
	Zone->exportSection->start_addr = (WORD) Zone->mem_start;


	// Lecture des donnees binaires a partir du fichier elf
	if (Zone->exportSection->data)
		free(Zone->exportSection->data);
	Zone->exportSection->data = (BYTE *) calloc(Zone->size, sizeof(BYTE));

	if (Zone->type == SHT_PROGBITS) {
		// zone text ou data : on recopie les donnees du fichier elf
		for (i = 0; i < Zone->size; i++)
			Zone->exportSection->data[i] = *(BYTE *) ((BYTE *) data->d_buf + data->d_off + i);
	} else {
		// zone bss: on rempli avec des zeros! (pas forcement utile...)
		for (i = 0; i < Zone->size; i++)
			Zone->exportSection->data[i] = 0;
	}
}


/*--------------------------------------------------------------------------  */
/**
 * @param Zone adresse de la zone à reloger
 * @param EnsZones adresse de l'ensemble des zones
 *
 * @brief Cette fonction effectue la relocation de la zone passée en parametres
 * @brief l'ensemble des zones (presentes) doit déjà avoir été chargé en memoire.
 * Pour chaque zone presente, on connait en particulier "mem_start" et "size"
 *
 * VOUS DEVEZ COMPLETER CETTE FONCTION POUR METTRE EN OEUVRE LA RELOCATION !!
 */
static void relocZone(MemZone * Zone, MemZone * EnsZones)
{
	Elf32_Rel *reloc_table;
	Elf32_Shdr *shdr;	// entete de section elf
	Elf_Data *data;		// donnee elf qq
	int type, sym;
	long elt_num_to_relloc;
    uint32_t AHL, AHI, ALO;
	uint32_t S, A, A1, V, P;

	if (Zone->rel_scn == NULL)
		return;		// zone abstente, on ne fait rien

	INFO_MSG("--------------Relocation de %s-------------------\n", Zone->rel_name);

	data = elf_getdata(Zone->rel_scn, NULL);
	shdr = elf32_getshdr(Zone->rel_scn);

	if (SymbolTable == NULL)
		ERROR_MSG("Pas de table des symboles trouvees");

	if (Zone->scn == NULL)
		ERROR_MSG("zone %s a reloger et manquante\n", Zone->name);

	elt_num_to_relloc = data->d_size / shdr->sh_entsize;

	//verification d'hypotheses faites sur le ELF
	if ((shdr->sh_info != Zone->index) || (shdr->sh_link != SymbInd)) {
		ERROR_MSG("info: %d vs %d. link: %d vs %d.\n", shdr->sh_info, Zone->index, shdr->sh_link, SymbInd);
	}
	INFO_MSG("Nombre de symboles a reloger: %ld\n", elt_num_to_relloc);


	/* 
	 * just in case an R_MIPS_LO16 happens before R_MIPS_HI16
	 * (should never happens according to specs, but still)
	 */

	AHL = 0;

	if (data->d_size > 0) {

		reloc_table = (Elf32_Rel *) data->d_buf;

		for (int i = 0; i < elt_num_to_relloc; i++) {
			type = ELF32_R_TYPE((reloc_table + i)->r_info);
			sym = ELF32_R_SYM((reloc_table + i)->r_info);
			P = (uint32_t) (reloc_table + i)->r_offset;

			S = (EnsZones[sym - 1].exportSection)->start_addr;
			A = get_word(Zone->exportSection->data + P);

			switch (type) {
			case R_MIPS_32:
				DEBUG_MSG("R_MIPS_32");
				V = S + A;
				break;

			case R_MIPS_26:
				DEBUG_MSG("R_MIPS_26");
				V = ((A << 2) | ((P & 0xf0000000) + S)) >> 2;
				V = (A & 0xfc000000) + (V & 0x2ffffff);
				break;

			case R_MIPS_HI16:
				DEBUG_MSG("R_MIPS_HI16");

				A1 = get_word(Zone->exportSection->data + 4 + P);

				/* get 4 least significant bytes */
				AHI = (A & 0xffff);
				ALO = (A1 & 0xffff);
				AHL = (AHI << 16) + (short) ALO;

				V = (AHL + S - (short) (AHL + S)) >> 16;
				V = (A & 0xffff0000) + (V & 0xffff);
				break;

			case R_MIPS_LO16:
				DEBUG_MSG("R_MIPS_LO16");

				/* 
                 * as a LO16 is always preceded by a HI16, 
                 * AHL has been calculated last loop increment 
                 */

				V = AHL + S;
				V = (A & 0xffff0000)  + (V & 0xffff);

				break;

			default:
				DEBUG_MSG("non-implemented reloc type");
				return;
			}
			set_word((Zone->exportSection)->data + P, V);
		}
	}
}



//----------------------------------------------------------------------
//          CHARGEMENT DU FICHIER ELF
//----------------------------------------------------------------------


/*
* ENTREES :
* @param filename nom du fichier a charger
*
*SORTIES :
* @param textSection adresse des données de la section text
* @param dataSection adresse des données de la section data
* @param bssSection adresse des données de la section bss
*
* @return 0 si le chargement chargement s'est bien passé
*
* @brief mipsloader : charge un fichier ELF et renvoie les données contenues
*!  Cette fonction lit le fichier ELF nommé "filename" et en extrait
*  les informations sur les sections .text, .data et .bss (les données,
*  leur taille, où les mettre en mémoire).
*  Si une section ne contient pas de données après le chargement,
*  son champ "size" est égal à zéro. Sinon, le tableau "data" de cette
*  section contient "size" octets, qui doivent être placés dans la mémoire
*  à partir de l'adresse "start_addr".
*
*  !!!! ATTENTION !!!!
*      La version actuelle de cette fonction n'effectue pas de relocation!
*      Les données des trois sections seront toujours lues, mais elles n'auront
*      pas été mises à jours si une relocation était nécessaire! Le programme
*      ne pourra donc pas être utilisé correctement!!
*      1. Dans un premier temps, ne chargez que des programmes sans relocation.
*         Si le fichier contient des sections de relocations, elle ne seront pas
*         traitées et un message d'erreur sera renvoyé.
*      2. Ensuite, ce sera à vous de gérer la relocation pour toujours renvoyer
*         un programme exécutable par le simulateur.
*
*/

int mipsloader(const char *filename, SectionELF * textSection, SectionELF * dataSection, SectionELF * bssSection, ARCH arch)
{

	// Sections qui nous interessent
	MemZone EnsZones[NUMZONE];
	MemZone *Text = EnsZones;
	MemZone *Data = EnsZones + 1;
	MemZone *Bss = EnsZones + 2;

	// variables auxiliaires
	Elf *elf;		// fichier elf
	Elf32_Ehdr *ehdr;	// entete elf
	Elf_Scn *scn;		// section qq
	Elf32_Shdr *shdr;	// entete de section qq
	Elf_Data *data;		// donnee qq
	Elf32_Sym *psymb;	// symbole a reloger
	long fd;		// descr. de fichier
	unsigned long cnt, i;
	MemZone *zone;


	// initialisation
	initZone(Text, ".text", textSection, SHT_PROGBITS);
	initZone(Data, ".data", dataSection, SHT_PROGBITS);
	initZone(Bss, ".bss", bssSection, SHT_NOBITS);
	StringTable = NULL;
	Shstrtab = NULL;
	SymbolTable = NULL;
	freeHashTable();

	INFO_MSG("------------------Trace d'execution--------------------------\n");


	// Lecture du fichier ELF, ouverture/fermeture avec les fonctions bas niveau open/close (contrainte de la lib elf)
	if ((fd = open(filename, O_RDONLY)) == -1) {
		ERROR_MSG("Fichier %s inexistant\n", filename);
	}

	elf_version(EV_CURRENT);
	if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
		ERROR_MSG("%s", elf_errmsg(elf_errno()));

	// Extraction des noms des sections
	if (((ehdr = elf32_getehdr(elf)) == NULL) || ((scn = elf_getscn(elf, ehdr->e_shstrndx)) == NULL) || ((data = elf_getdata(scn, NULL)) == NULL)) {
		ERROR_MSG("%s", elf_errmsg(elf_errno()));
	}
	Shstrtab = (char *) data->d_buf;
	Shstrtab_size = data->d_size;

	if (ehdr->e_machine != EM_MIPS)
		ERROR_MSG("Fichier ELF processeur autre que MIPS");

	if (ehdr->e_type != ET_REL)
		ERROR_MSG("Fichier ELF non relogeable");

	INFO_MSG("Parcours des sections...\n");


	// EXTRACTION des sections qui nous interessent !!!
	for (cnt = 1, scn = NULL; (scn = elf_nextscn(elf, scn)); cnt++) {

		// Entete de la section
		if ((shdr = elf32_getshdr(scn)) == NULL)
			ERROR_MSG("%s", elf_errmsg(elf_errno()));

		INFO_MSG("section %ld: %s (type=%s)\n", cnt, getSectionHeaderName(shdr->sh_name), shtName(shdr->sh_type));


		switch (shdr->sh_type) {
		case SHT_STRTAB:
			if (!strcmp(getSectionHeaderName(shdr->sh_name), ".strtab")) {
				/* Table des chaines */
				data = elf_getdata(scn, NULL);
				StringTable = (char *) ((BYTE *) data->d_buf + data->d_off);
				StringTableSize = data->d_size;
#ifdef VERBOSE
				fprintf(stderr, "Table des chaines");
				for (i = 0; i < StringTableSize; i++) {
					putc(StringTable[i], stderr);
					if (StringTable[i] == 0) {
						putc(' ', stderr);
					}
				}
				putc('\n', stderr);
#endif
			}
			break;

		case SHT_PROGBITS:	// Sections text, data ...
		case SHT_NOBITS:	// ... ou section bss
			for (i = 0; i < NUMZONE; i++) {
				if (!strcmp(getSectionHeaderName(shdr->sh_name), EnsZones[i].name)) {
					if (EnsZones[i].scn != NULL) {
						DEBUG_MSG("2 sections %s trouvees", EnsZones[i].name);
					}
					if (EnsZones[i].type != shdr->sh_type) {
						ERROR_MSG("section %s du (mauvais) type %s", EnsZones[i].name, shtName(shdr->sh_type));
					}
					INFO_MSG("section %s trouvee\n", EnsZones[i].name);

					EnsZones[i].scn = scn;
					EnsZones[i].index = cnt;
					break;
				}
			}
			break;

		case SHT_SYMTAB:
			if (!strcmp(getSectionHeaderName(shdr->sh_name), ".symtab")) {
				if (SymbolTable != NULL) {
					INFO_MSG("2 tables de symboles trouvees !");
				}
				INFO_MSG("section symtab trouvee\n");

				data = elf_getdata(scn, NULL);
				SymbolTable = (Elf32_Sym *) ((BYTE *) data->d_buf + data->d_off);
				SymbInd = cnt;
				SymbNum = data->d_size / shdr->sh_entsize;
			}
			break;

		case SHT_REL:	// sections de relocations
			for (i = 0; i < NUMZONE; i++) {
				if (!strcmp(getSectionHeaderName(shdr->sh_name), EnsZones[i].rel_name)) {
					if (EnsZones[i].rel_scn != NULL) {
						DEBUG_MSG("2 sections %s trouvees", (char *)
							  EnsZones[i].rel_scn);
					}
					INFO_MSG("section %s trouvee\n", EnsZones[i].rel_name);

					EnsZones[i].rel_scn = scn;
					break;
				}
			}
			break;
		}
	}

#ifdef VERBOSE
	fprintf(stderr, "Table des symboles");
	if (SymbolTable != NULL && StringTable != NULL) {
		for (i = 0; i < SymbNum; i++) {
			fprintf(stderr, "%s ", getName(getSymb(i)->st_name));
		}
		putc('\n', stderr);
	} else {
		fprintf(stderr, "???\n");
	}
#endif

	// CHARGEMENT EN MEMOIRE DES ZONES
	for (zone = EnsZones, cnt = 0; zone < EnsZones + NUMZONE; zone++) {
		if (zone->scn != NULL) {	// si la zone est bien présente dans le fichier.
			loadZone(zone, cnt);

			// dernière adresse (pour déterminer le début de la zone suivante)
			cnt += zone->mem_start + zone->size;
		}
	}

	// CREATION DE LA TABLE adresse -> symbole
	if (SymbolTable != NULL && StringTable != NULL) {
		for (i = 0; i < SymbNum; i++) {
			psymb = getSymb(i);
			if (ELF32_ST_TYPE(psymb->st_info) == STT_NOTYPE) {
				for (cnt = 0; cnt < NUMZONE; cnt++) {
					if (psymb->st_shndx == EnsZones[cnt].index) {
						addSymbol(EnsZones[cnt].mem_start + psymb->st_value, getName(psymb->st_name));
						break;
					}
				}
			}
		}
	}
	// RELOCATIONS
	relocZone(Text, EnsZones);
	relocZone(Data, EnsZones);
	// on ignore les relocations en Bss

	/* copy symbol table */
	arch->symbols = (Elf32_Sym*) calloc(SymbNum, sizeof(*SymbolTable));
	arch->symbols_num = SymbNum;
	memcpy(arch->symbols, SymbolTable, SymbNum * sizeof(*SymbolTable));

	arch->symbols_names = (char*) calloc(StringTableSize, sizeof(char));
	memcpy(arch->symbols_names, StringTable, StringTableSize);

	/* FREE THE MALLOCS */
	free(Text->rel_name);
	free(Data->rel_name);
	free(Bss->rel_name);
	elf_end(elf);

#ifdef VERBOSE
	printELFSection(textSection);
	printELFSection(dataSection);
	printELFSection(bssSection);
#endif

	close(fd);
	return 0;
}
