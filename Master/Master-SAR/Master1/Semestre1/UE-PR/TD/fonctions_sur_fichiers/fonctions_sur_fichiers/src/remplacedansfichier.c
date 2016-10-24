#include "remplacedansfichier.h"

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
	int fichier1;
	char* bufFichier1;
	int nbMots;

	if (argc != 3)
	{
		printf("%s\n", "usage : ./remplacedansfichier <fichier 1> <mot> <suite de mots>");
		return EXIT_FAILURE;
	}

	if ((fichier1 = open(argv[1], O_RDWR | O_CREAT | _O_EXCL | O_SYNC | O_TRUNC)) != -1)
	{
		for (nbMots = 3; nbMots < argc; nbMots++)
		{
			write(fichier1, argv[nbMots], strlen(argv[nbMots]));
			printf("%s\n", argv[nbMots]);
			write(fichier1, " ", sizeof(char));
			printf("%s\n", " ");
			lseek(fichier1, 0, SEEK_SET);
		}

		bufFichier1 = malloc(strlen(argv[3]));
		read(fichier1, bufFichier1, strlen(argv[3]));
		lseek(fichier1, SEEK_CUR + 1, SEEK_SET);
		write(fichier1, argv[2], strlen(argv[2]));

		close(fichier1);
		return EXIT_SUCCESS;
	}
	perror(argv[1]);
	return errno;
}