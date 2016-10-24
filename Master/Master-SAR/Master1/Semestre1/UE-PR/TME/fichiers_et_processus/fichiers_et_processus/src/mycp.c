#include "mycp.h"

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
	int fichier1, fichier2;
	int readVal;
	struct stat statFichier1;
	char* bufFichier1;
	
	if (argc != 3)
	{
		printf("%s\n", "usage : ./mycp <fchier 1> <fichier 2>");
		return EXIT_FAILURE;
	}

	if(stat(argv[1], &statFichier1) == 0)
	{
		if (S_ISREG(statFichier1.st_mode))
		{
			if ((fichier1 = open(argv[1], O_RDONLY)) != -1)
			{
				if ((fichier2 = open(argv[2], O_RDWR | O_CREAT | O_EXCL | O_SYNC, S_IRUSR | S_IWUSR)) != -1)
				{
					bufFichier1 = malloc(statFichier1.st_size);
					while ((readVal = read(fichier1, bufFichier1, statFichier1.st_size)) != 0)
					{
						if (readVal == -1)
						{
							close(fichier1);
							close(fichier2);
							free(bufFichier1);
							bufFichier1 = NULL;
							perror(argv[1]);
							return errno;
						}

						if (write(fichier2, bufFichier1, statFichier1.st_size) == -1)
						{
							close(fichier1);
							close(fichier2);
							free(bufFichier1);
							bufFichier1 = NULL;
							perror(argv[2]);
							return errno;
						}
					}
					
					free(bufFichier1);
					bufFichier1 = NULL;
					close(fichier1);
					close(fichier2);

					return EXIT_SUCCESS;
				}

				close(fichier1);
				perror(argv[2]);
				return errno;
				}

			}
		}

	perror(argv[1]);
	return errno;
}
