
#include "HashTable.h"

HashTable newHashTable(int n)
{
  HashTable hash = malloc(sizeof(HashTableImp));

  hash->n = n;
  hash->hashTableM = (HashTableEntry *)malloc(n * sizeof(HashTableEntry));

  for(int i = 0; i < n; i++)
    hash->hashTableM[i].iChainIndex = -2;

  return hash;
}


void freeHashTable(HashTable h)
{
  free(h->hashTableM);
  free(h);
}


int stringToInt(char *szStringToConvert)
{
  int length = strlen(szStringToConvert);
  int var = 0;

  for(int i = 0; i < length; i++)
  {
    var = var + szStringToConvert[i];
    if(i == 3)
      var = var + szStringToConvert[i];
    if(i == 8)
        var = var + szStringToConvert[i];
  }

  return var;

}


int divisionMethod(int iKey, int n)
{
  return (iKey % n);
}


int midsquareMethod(int iKey, int n)
{
  int midL = floor(log10(iKey)) + 1;

  int iKey2 = iKey * iKey;
  int keyL2 = floor(log10(iKey2)) + 1;

  int k = (keyL2 / 2);

  int m = (midL / 2);
  for(int i = 0; i < (k - m); i++)
  {
    iKey2 = iKey2 / 10;
  }

  return (iKey2 % n);
}


void put(HashTable h, Element e)
{
  int iHash = midsquareMethod(stringToInt(e.TeamName), h->n);

  while(h->hashTableM[iHash].iChainIndex >= 0)
  {
    iHash = h->hashTableM[iHash].iChainIndex;
  }
  int chain = iHash;
  while(h->hashTableM[iHash].iChainIndex != -2)
  {
     iHash += 7;
     if(iHash >= h->n)
        iHash = iHash % (h->n);
  }

  if(iHash != chain)
    h->hashTableM[chain].iChainIndex = iHash;

  h->hashTableM[iHash].iChainIndex = -1;
  h->hashTableM[iHash].key = e;

}


void get(HashTable h, char *szTeamName, Element **e)
{
  int iHash = midsquareMethod(stringToInt(szTeamName), h->n);
  int ctr = 0;

  while(strcmp(h->hashTableM[iHash].key.TeamName, szTeamName) != 0)
  {
    iHash = h->hashTableM[iHash].iChainIndex;
    //printf("%d\n", ctr);
    if(ctr == 50)
      break;
    ctr++;
  }
  *e = &(h->hashTableM[iHash].key);

}
