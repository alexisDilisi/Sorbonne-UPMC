#include "droitsfichier.h"

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
	struct stat statFichier1;
	int droitsLecture = S_IRUSR | S_IRGRP | S_IROTH;
	int droitsLectureEcriture = droitsLecture | S_IWUSR | S_IWGRP | S_IWOTH;

	if (argc < 3)
	{
		printf("%s\n", "usage : ./droitsfichier <operation> <fichier 1> [nouveau nom] [droits]");
		return EXIT_FAILURE;
	}

	if(stat(argv[2], &statFichier1) != -1)
	{
		if (S_ISDIR(statFichier1.st_mode))
		{
			printf("%s, est un dossier\n", argv[2]);
			return EXIT_FAILURE;
		}

		switch (argv[1][0])
		{
			default: printf("%s\n", "mauvaise valeur d argument");
				return EXIT_FAILURE;
			case 'E':
			case 'e': unlink(argv[2]);
				break;
			case 'R':
			case 'r': if(argc > 3)
				{
					rename(argv[2], argv[3]);
					break;
				}
				printf("%s\n", "mauvaise valeur d argument");
				return EXIT_FAILURE;

			case 'C':
			case 'c': if (argc > 3)
				{
					if (argv[3][0] == 'R' || argv[3][0] == 'r')
					{
						chmod(argv[1], droitsLecture);
					}

					chmod(argv[1], droitsLectureEcriture);
					break;
				}

				printf("%s\n", "mauvaise valeur d argument");
				return EXIT_FAILURE;
		}
	}

	perror(argv[2]);
	return errno;
}