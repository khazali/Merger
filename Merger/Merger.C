#define NO_OF_FILES	1000
#define NO_OF_ZEROS	4
#define MAX_STRING_LENGTH 256


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *inFile, *OutFile;
	register int i, j, n, r, m;
	char FilePath[MAX_STRING_LENGTH], FileName[MAX_STRING_LENGTH], Postfix[MAX_STRING_LENGTH], FullName[3 * MAX_STRING_LENGTH], FullNameOut[3 * MAX_STRING_LENGTH], ch;

	printf("Enter the file path: ");
	fgets(FilePath, MAX_STRING_LENGTH, stdin);
	printf("\nEnter the file prefix: ");
	fgets(FileName, MAX_STRING_LENGTH, stdin);
	printf("\n");

	m = 0;
	j = 0;
	while (FilePath[j]) {
		FullName[m] = FilePath[j];
		FullNameOut[m] = FilePath[j];
		m++;
		j++;
	}
	FullName[m - 1] = '\\';
	FullNameOut[m - 1] = '\\';
	
	j = 0;
	while (FileName[j]) {
		FullName[m] = FileName[j];
		FullNameOut[m] = FileName[j];
		m++;
		j++;
	}
	m--;
	FullNameOut[m] = '.';
	FullNameOut[m + 1] = 'd';
	FullNameOut[m + 2] = 'a';
	FullNameOut[m + 3] = 't';
	FullNameOut[m + 4] = '\0';

	if ((OutFile = fopen(FullNameOut, "wb")) == NULL) {
		printf("Can not Open Output File %s\n", FullNameOut);
		exit(EXIT_FAILURE);
	}


	for (i = 0; i < NO_OF_FILES; i++) {
		n = i;
		for (j = 0; j < NO_OF_ZEROS; j++) {
			r = n % 10;
			n /= 10;
			Postfix[NO_OF_ZEROS - j - 1] = (char)(r + 48);
		}
		Postfix[NO_OF_ZEROS] = '.';
		Postfix[NO_OF_ZEROS + 1] = 't';
		Postfix[NO_OF_ZEROS + 2] = 'x';
		Postfix[NO_OF_ZEROS + 3] = 't';
		Postfix[NO_OF_ZEROS + 4] = '\0';	

		j = 0;
		n = m;
		while (Postfix[j]) {
			FullName[n] = Postfix[j];
			n++;
			j++;
		}
		FullName[n] = '\0';

		if ((inFile = fopen(FullName, "rb")) == NULL) {
			printf("Can not Open Input File %s\n", FullName);
			exit(EXIT_FAILURE);
		}

		while (!feof(inFile)) {
			fread(&ch, 1, 1, inFile);
			if (ch!=EOF) fwrite(&ch, 1, 1, OutFile);
		}
		printf("%s Done!\n", FullName);

		fclose(inFile);
		fflush(OutFile);		
	}

	fclose(OutFile);
	return 0;
}