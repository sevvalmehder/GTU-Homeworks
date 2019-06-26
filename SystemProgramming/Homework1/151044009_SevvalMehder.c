#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Bu fonksiyon kendisine gelen isimdeki dosyayı byte byte okuyarak icinde kac 
 * tane karakter oldugunu return eder.
 *
 * Parametre : filename -> acilacak dosyanin ismi
 *
 * Saydigi karakter sayisini return eder.
 */
int findFileSize(const char *filename);


/* Bu fonksiyon kendisine parametre olarak verilen dosya ismi sayesinde dosyayi
 * acar ve yine parametre olarak verilen kelimeyi dosyanin icerisinde arar.
 * Bulundugu indisleri ekrana yazdirip totalde kac tane eslesme buldugunu 
 * return eder.
 * Parametreler : filename -> okunacak dosya
 *				  toSearch -> aranacak kelime
 * Return       : toplam eslesme sayisi
 */
int searchInFile(const char *toSearch, const char *filename);

/* Type define enum */
typedef enum {
    false = 0, true = 1
} boolean ; 

/*
 * Mainin baslangici
 *
 */

int main( int argc , char* argv[] ){
	
	/* Usage */
	if( argc != 3 ){
		fprintf(stderr, "Usage: ./list -target -fileName\n");
	}

	if( strcmp(argv[0] , "./list") != 0 ){
		fprintf(stderr, "Usage: ./list -target -fileName\n");
	}

	printf("Total occurance of '%s' : %d times\n", 
			argv[1] , searchInFile( argv[1], argv[2] ) );

	
	return 0;
}

/*
 * Mainin bitisi
 *
 */

int searchInFile(const char *toSearch, const char *fileName){

	int indexOfChars, /*charsInFile arrayinde gezecek olan index */
		indexOfTarget, /*toSearch arrayinde gezecek index*/
		tempIndex,  /*Ilk eslesmeden sonra charsInFile'ı gezecek gecici index*/
		lenOfTarget,  /*toSearch arayinin size'ı*/
		currentRow = 1,
		currentCol = 1,
		match = 0,   
		count = 0,   /*Toplam eslesmeyi tutacak ve return edilecek sayac*/
		fileSize;    /*Dosyadaki byte sayisi*/

	char *charsInFile;

	FILE *fpToRead;

	boolean isMatch = true;

	if (NULL == (fpToRead = fopen(fileName, "r"))) {
		fprintf(stderr, "\"%s\" cannot found.\n", fileName);
        exit(1);
    }

	lenOfTarget = strlen(toSearch);

	
	fileSize = findFileSize(fileName);

	charsInFile = (char*)malloc(sizeof(char) * fileSize);

	if(charsInFile == NULL){
		fprintf(stderr, "Memory allocation error. Program will be closed");
		exit(1);
	}

	for(indexOfChars = 0; indexOfChars < fileSize; ++indexOfChars)
		fscanf(fpToRead, "%c", &charsInFile[indexOfChars]);


	for(indexOfChars = 0 ; indexOfChars < fileSize; ++indexOfChars, ++currentCol){
		
		if( lenOfTarget <= fileSize){

			if(charsInFile[indexOfChars] == toSearch[0] ){

				indexOfTarget = 1;
				tempIndex = indexOfChars + 1;
				while( (indexOfTarget < lenOfTarget) && (tempIndex < fileSize) ){
					
					if(charsInFile[tempIndex] != ' ' && charsInFile[tempIndex] != '\t' 
						&& charsInFile[tempIndex] != '\n' ){
						
						if(charsInFile[tempIndex] != toSearch[indexOfTarget] ){
							
							isMatch = false;

						}
						else
							++match;

						++indexOfTarget;

					}
					++tempIndex;
				
				}
				if(isMatch == true && match == lenOfTarget-1){
					printf("[%d - %d] konumunda ilk karakter bulundu\n", currentRow, currentCol);
					count ++;

				}

				isMatch = true;
				match = 0;
				
			}
			
			if(charsInFile[indexOfChars] == '\n'){

				currentCol = 1;

				++currentRow;

			}
		}
		
	}
	fclose(fpToRead);
	free(charsInFile);
	return count;

}

int findFileSize( const char* filename){
	FILE *fpReadFile;
	char indexOfTarget;
	int i = 0;

	if (NULL == (fpReadFile = fopen(filename, "r"))) {
		fprintf(stderr, "\"%s\" cannot found.\n", filename);
        exit(1);
    }

	while(fscanf(fpReadFile,"%c",&indexOfTarget)!=EOF)	
		++i;

	fclose(fpReadFile);
	return i;
}
