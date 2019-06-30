/*
 *Sevval MEHDER
 *151044009
 *System Programing Homework 2
 */

#include <stdio.h>
#include <dirent.h> /* DIR* */
#include <stdlib.h> /*Exit*/
#include <string.h>
#include <unistd.h> /*fork*/
#include <sys/types.h> /*pid*/
#include <sys/wait.h> /*wait */


/* Define boolean */
typedef enum{
	false = 0, true = 1
} bool;
 

#define OUTPUT_FILE "log.log" /*Output file name*/
#define MAX_PATH 255 /*Max path length*/

/* Bu fonksiyon kendisine gelen isimdeki dosyayı byte byte okuyarak icinde kac 
 * tane karakter oldugunu return eder.
 *
 * Parametre : filename -> acilacak dosyanin ismi
 *
 * Saydigi karakter sayisini return eder.
 */
int findFileSize(const char *filename);

/* Bu fonksiyon kendisine gelen isimdeki dosyada kac adet '\n' oldugunu sayar.
 * Bu sayede de kac tane target bulunduguna ulasabiliriz.
 *
 * Parametre : filename -> acilacak dosyanin ismi
 *
 * Saydigi '\n' sayisini return eder.
 */
int totalOccurance(const char *filename);

/* Bu fonksiyon kendisine parametre olarak verilen dosya ismi sayesinde dosyayi
 * acar ve yine parametre olarak verilen kelimeyi dosyanin icerisinde arar.
 * Bulundugu indisleri ekrana yazdirip totalde kac tane eslesme buldugunu 
 * return eder.
 * Parametreler : filename -> okunacak dosya
 *				  toSearch -> aranacak kelime
 * Return       : toplam eslesme sayisi
 */
int searchInFile(const char *toSearch, const char *fileName, char *inFile);

/* Bu fonksiyon kendisine gelen isimdeki klasörün içerisindeki dosyalarda yine
 * parametre olarak verilen target stringini arar.
 * Actigi klasörde fork yapar ve child processin dondurdugu degere gore de
 * islemler yapar. 
 * Eger directory icinde directory varsa recursive olarak kendini cagirir.
 * Parametre : directory -> acilacak klasorun ismi
 * 			   target    -> aranacak string
 */
void searchInDirectory( const char *target, const char *directory);

/* Bu fonksiyon kendisine gelen isimdeki dosyanin okunup okunmayacagina karar 
 * verir. Eger dosyanın sonunda '~' varsa false return eder.
 * Aksi her durum için true dondurur.
 * Parametre : filename -> okunacak dosyanin ismi
 * 
 * Dosya ismine gore true ya da false
 */
bool isFileAvailable(const char *filename);


/*
 * Mainin baslangici
 *
 */
int main(int argc, char **argv){
	FILE *fPointer;
	
	/*Arguman kontrolu / Usage*/
	if(argc!=3){
			
		fprintf(stderr, "Usage: ./list -target -directoryName\n");
		exit(1);
	}

	/* erase previous log file */
	remove(OUTPUT_FILE);

	searchInDirectory(argv[1], argv[2]);

	fPointer = fopen(OUTPUT_FILE , "a");
	fprintf(fPointer, "%d '%s' were found in total\n", 
			totalOccurance(OUTPUT_FILE) , argv[1]);	

	fclose(fPointer);

	return 0;
} 
/*
 * Mainin bitisi
 *
 */

void searchInDirectory( const char *target, const char *directory){
	struct dirent *pdirent;
	DIR *pdir = NULL;
	DIR *dpTemp = NULL; /*Directory olup olmadigi kontrol edilecek*/
	char subDirectoryPath[MAX_PATH],
	     tempName[MAX_PATH]; 
	int childNumber = 0, /*Yavru process sayisi*/
		i; /*Loop yardımcısı*/
	pid_t pidChild; /*Yavru process pidi*/
	
	/*Error check*/     
	if(( pdir = opendir(directory) ) == NULL ){
		
		fprintf(stderr, "Failed to open directory %s\n", directory);
		exit(1);
	}

	/*Acilabilir dosya olup olmadiginin kontrolu*/
	while( ( pdirent = readdir(pdir)) != NULL){

		/*Ozel durum kontrolu*/
		if( strcmp(pdirent->d_name,".") != 0 && strcmp(pdirent->d_name,"..") != 0 ){

			/*dosyanin adinin path e donusturulmesi */
			sprintf(subDirectoryPath, "%s/%s", directory , pdirent->d_name);

			pidChild = fork();
		
			if(pidChild == 0){

				/* check directory or file */
			
				if((dpTemp = opendir(subDirectoryPath)) != NULL){
					closedir(dpTemp);
					/*Yeni bir directory oldugu icin recursive cagri*/
					searchInDirectory(target, subDirectoryPath);
				}

				else if( isFileAvailable(subDirectoryPath) == true){
					strcpy(tempName , pdirent->d_name);
					searchInFile(target, subDirectoryPath, tempName);
				}

				else 
					break;

				pdirent = NULL;
				dpTemp = NULL;
				exit(1);
			}
			
			else
				childNumber++;

		}
		/* cocuklari bekle */
		for(i = 0; i < childNumber; ++i)
			wait(NULL);

	}
	
    pdirent=NULL;
    dpTemp = NULL;
    closedir(pdir);
	return;
}

bool isFileAvailable(const char *filename){
	int length = strlen(filename);
	if( filename[length-1] == '~' )
		return false;

	return true;
}

int searchInFile(const char *toSearch, const char *fileName, char *inFile){

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

	FILE *fpLogFile, *fpToRead;


	bool isMatch = true;

	if ( (fpToRead = fopen(fileName, "r")) == NULL ) {
		fprintf(stderr, "\"%s\" cannot found.\n", fileName);
        exit(1);
    }

    if((fpLogFile = fopen(OUTPUT_FILE, "a")) == NULL){
		
		fprintf(stderr, "Log file %s couldn't open.\n", OUTPUT_FILE);
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
					fprintf(fpLogFile, "%s: ", inFile);	
					fprintf(fpLogFile, "[%d - %d] konumunda ilk karakter "
					        "bulundu\n", currentRow, currentCol);
					count ++;

				}

				isMatch = true;
				match = 0;
				
			}
			
			if(charsInFile[indexOfChars] == '\n'){

				currentCol = 0;

				++currentRow;

			}
		}
		
	}
	fclose(fpToRead);
	fclose(fpLogFile);
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

int totalOccurance(const char *filename){
	int count = 0;
	FILE *fPointer;
	char chTemp;
	fPointer = fopen(filename, "r");

	while( ( chTemp = getc(fPointer))  != EOF){
		if(chTemp =='\n')
			count++;
	}
	fclose(fPointer);
	return count;
}