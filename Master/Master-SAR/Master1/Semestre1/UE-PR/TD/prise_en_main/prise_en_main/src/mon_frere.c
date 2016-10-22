#include "mon_frere.h"

#define _XOPEN_SOURCE 700

#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int mon_frere(void)
{
	int returnVal;
	int nbFils;
	pid_t pidFils; /* je suis dans le pere */
	pid_t pidFils1; /* je suis dans le pere */
	returnVal = -1;
	

	if((pidFils1 = fork()) == -1)
	{
		perror("erreur fork\n");
		return returnVal;
	}

	if(pidFils1 == 0)
	{
		/* je suis dans le fils 1 */

		pid_t pidFils11; /* je suis dans le pere 1 */
		int nbFork = 1;

		printf("je suis le fils 1 mon pid est : %d, mon ppid est %d\n", getpid(), getppid());

		if((pidFils11 = fork()) == -1)
		{
			printf("%s\n", "je suis le fils 1, je n ai pas pu cree de fils");
			perror("erreur fork\n");
			exit(0);
		}

		if(pidFils11 == 0)
		{
			/* je suis dans le fils 1.1 */

			printf("je suis le fils 1.1 mon pid est : %d, mon ppid est %d, je n ai pas de fils\n", getpid(), getppid());
			exit(0);
		}

		/* je suis dans le pere 1 */

		printf("je suis le fils 1, j ai cree %d fils\n", nbFork);
		wait(NULL);
		exit(0);
	}

	/* je suis dans le pere */

	returnVal = 1;
	printf("je suis le pere, j ai cree %d fils\n", returnVal);
	
	if ((pidFils = fork()) == -1)
	{
		perror("erreur fork\n");
		return returnVal;
	}

	if (pidFils == 0)
	{
		pid_t pidFils12; /* je suis dans le pere 2 */
		int nbFork = 1;

		printf("je suis le fils 2 mon pid est : %d, mon ppid est %d, le pid de mon frere est %d\n", getpid(), getppid(), pidFils1);

		if ((pidFils12 = fork()) == -1)
		{
			printf("%s\n", "je suis le fils 2, je n ai pas pu cree de fils");
			perror("erreur fork\n");
			exit(0);
		}

		if (pidFils12 == 0)
		{

			/* je suis dans le fils 2.1 */

			printf("je suis le fils 2.1 mon pid est : %d, mon ppid est %d, je n ai pas de fils\n", getpid(), getppid());
			exit(0);
		}

		/* je suis dans le pere 2 */

		printf("je suis le fils 2, j ai cree %d fils\n", nbFork);
		wait(NULL);
		exit(0);
	}

	/* je suis dans le pere */

	for (nbFils = 1; nbFils <= 2; nbFils++)
	{
		wait(NULL);
	}

	printf("je suis le pere, j ai cree %d fils\n", ++returnVal);
	return returnVal;
}

int main(void)
{
	mon_frere();

	return EXIT_SUCCESS;
}