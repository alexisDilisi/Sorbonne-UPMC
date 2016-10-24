#include "memefichier.h"

#define _XOPEN_SOURCE 700

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	struct stat statFichier1, statFichier2;

	stat(argv[1], &statFichier1);
	stat(argv[2], &statFichier2);

	if(statFichier1.st_ino == statFichier2.st_ino && statFichier1.st_dev == statFichier2.st_dev)
	{
		printf("c est le meme fichier \n");
		return EXIT_SUCCESS;
	}

	printf("les fichiers sont differents \n");
	return EXIT_FAILURE;

}