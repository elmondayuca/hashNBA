
/**********************************************************************
ibt004Project5Part2.c by Miguel A. Aviles Bonilla
Purpose:
This project stores and updates the win/loss records of the NBA teams
from the 2018-2019 season using a Hash Table.
**********************************************************************/
#include "HashTable.h"

int main()
{
	FILE *teamNameFile;
  teamNameFile = fopen("nbaTeamNames.csv", "r");
  if(teamNameFile == NULL)
  {
    perror("Error opening file");
    return -1;
  }

	FILE *winLossFile;
  winLossFile = fopen("nbaData2019.csv", "r");
  if(winLossFile == NULL)
  {
    perror("Error opening file");
    return -1;
  }

	char string[75];
	char line[30];
	char team1[30];
	char team2[30];
	int t1score, t2score, length;
	HashTable hash = newHashTable(100);


	while(fgets( string, 75, teamNameFile)!=NULL)
	{
		if(string[0] == '\n')
			continue;

		int ctr = 0;
		length = strlen(string);
		for(int i = 0; i < length; i++)
		{
			if(string[i] != '\n' && string[i] != '\r')
			{
				line[ctr] = string[i];
				ctr++;
			}
		}
		line[ctr] = '\0';

		Element e;
		e.wins = 0;
		e.losses = 0;
		strcpy(e.TeamName, line);
		put(hash, e);

	}

	while(fgets( string, 75, winLossFile)!=NULL)
	{
		if(string[0] == '\n')
			continue;

		int ctr = 0;
		char *line = strtok(string, ",");


		while(line)
		{
			if(ctr == 0)
				strcpy(team1, line);
			if(ctr == 1)
				t1score = atoi(line);
			if(ctr == 2)
				strcpy(team2, line);
			if(ctr == 3)
				t2score = atoi(line);

			line = strtok(NULL, ",");
			ctr++;
		}

		Element *e1;
		get(hash, team1, &e1);
		Element *e2;
		get(hash, team2, &e2);

		if(t1score > t2score)
		{
			e1->wins++;
			e2->losses++;
		}
		if(t2score > t1score)
		{
			e2->wins++;
			e1->losses++;
		}
	}


	rewind(teamNameFile);
	while(fgets( string, 40, teamNameFile)!=NULL)
	{
		if(string[0] == '\n')
			continue;

		int ctr = 0;
		length = strlen(string);
		for(int i = 0; i < length; i++)
		{
			if(string[i] != '\n' && string[i] != '\r')
			{
				line[ctr] = string[i];
				ctr++;
			}
		}
		line[ctr] = '\0';
		Element *e1;

		get(hash, line, &e1);

		printf("%s: %d Wins - %d Losses\n", e1->TeamName, e1->wins, e1->losses);

	}

	free(hash);
	fclose(teamNameFile);
	fclose(winLossFile);
	return 0;
}
