#include "memefichier.h"

#define _XOPEN_SOURCE 700

#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	struct stat statFichier1, statFichier2;

	if (lstat(argv[1], &statFichier1) == -1)
	{
		perror(argv[1]);
		return errno;
	}

	if(lstat(argv[2], &statFichier2) == -1)
	{
		perror(argv[2]);
		return errno;
	}

	if(statFichier1.st_ino == statFichier2.st_ino && statFichier1.st_dev == statFichier2.st_dev)
	{
		printf("c est le meme fichier \n");
		return EXIT_SUCCESS;
	}

	printf("les fichiers sont differents \n");
	return EXIT_SUCCESS;

}