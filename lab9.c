#include <stdio.h>

#define HASH_TABLE 23

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* data;
	struct HashType* next;
};

// Compute the hash function
int hash(int x)
{
	return x%HASH_TABLE;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		printf("index %d ->", i);
		struct HashType temp=&pHashArray[i];

		while(temp!=NULL)
		{
			printf("%d %c %d ->", temp->data.id, temp->data.name, temp->data.order);
			temp=temp->next;
		}
		printf("\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	struct HashType HashTable[HASH_TABLE];
	int i;

	for(i=0;i<recordSz;i++)
		HashTable[i].next=NULL;

	for(i=0;i<recordSz;i++)
	{
		struct RecordType record=pRecord[i];
		int idx=hash(data.id);

		struct HashType* temp=&HashTable[i];

		while(temp->next!=NULL)
			temp=temp->next;

		struct HashType* new=(struct HashType*)malloc(sizeof(struct HashType));
		new->data=record;
		new->next=NULL;
		temp->next=new;
	}

	displayRecordsInHash(HashTable, HASH_TABLE);

	for(i=0;i<recordSz;i++)
		free(&pRecord[i]);

	return 0;
}