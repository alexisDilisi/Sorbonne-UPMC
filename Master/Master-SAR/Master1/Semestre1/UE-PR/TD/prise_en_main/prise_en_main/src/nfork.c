#include "nfork.h"

#define _XOPEN_SOURCE 700

#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int nfork(int n)
{
	int returnVal;
	returnVal = -1;
	pid_t pidFils; /* je suis dans le pere */

	if((pidFils=fork()) == -1)
	{
		perror("erreur fork\n");
		return returnVal;
	}

	if(pidFils == 0)
	{
		/* je suis dans le fils */

		exit(0);
	}

	returnVal = 1;
	printf("je suis le pere, j ai cree %d fils\n", returnVal);
	
	while(returnVal <= n)
	{
		if ((pidFils = fork()) == -1)
		{
			perror("erreur fork\n");
			return returnVal;
		}

		if (pidFils == 0)
		{
			/* je suis dans le fils */

			printf("%s\n", "je suis un fils je retourne 0");
			exit(0);
		}

		printf("je suis le pere, j ai cree %d fils\n", returnVal);
		returnVal++;
	}

	printf("je suis le pere, j ai cree %d fils\n", returnVal);
	return returnVal;
}

int main(int argc, char** argv)
{
	int nbFork = atoi(argv[1]);

	if(argc != 2)
	{
		printf("%s\n", "usage : ./nfork <nb fils>");
		return EXIT_FAILURE;
	}

	nfork(nbFork);

	return EXIT_SUCCESS;
}