/*
 *Sevval MEHDER
 *151044009
 *System Programing Homework 3
 */

#include <stdio.h>
#include <dirent.h> /* DIR* */
#include <stdlib.h> /*Exit*/
#include <string.h>
#include <unistd.h> /*fork*/
#include <sys/types.h> /*pid*/
#include <sys/wait.h> /*wait */
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>


#define OUTPUT_FILE "log.log" /*Output file name*/
#define MAX_PATH 255 /*Max path length*/
#define FAIL -1

/* Define boolean */
typedef enum{
	false = 0, true = 1
} bool;

/* Verilen directory içinde verilen stringi arar. Ve bulduğu total occurance
 * degerini log dosyasine yazar.
 *
 * Parametreler : target -> bulunması istenen string
 *                       -> stringin aranacagi directory
 */
void wrapper( const char *target, const char *directory);

/* Acilmis olarak verilen directory icerisinde toplam directory ve file sayisini
 * bulur.
 * Parametreler : dir -> arama yapilacak yer
 *				  numberOfFile -> toplam file sayisi
 *                numberOfDir -> toplam directory sayisi  
 */
void findAll(const char *dir, int *numberOfFile, int *numberOfDir);

/* Bu fonksiyon kendisine gelen isimdeki klasörün içerisindeki dosyalarda yine
 * parametre olarak verilen target stringini arar.
 *
 * Parametre : directory -> acilacak klasorun ismi
 * 			   target    -> aranacak string
 * Return : Bulunan toplam kelime sayisi
 */
int searchInDirectory( const char *target, const char *directory);

/* Bu fonksiyon kendisine parametre olarak verilen dosya ismi sayesinde dosyayi
 * acar ve yine parametre olarak verilen kelimeyi dosyanin icerisinde arar.
 * Bulundugu indisleri ekrana yazdirip totalde kac tane eslesme buldugunu 
 * return eder.
 * Parametreler : filename -> okunacak dosya
 *				  toSearch -> aranacak kelime
 * Return       : toplam eslesme sayisi
 */
int searchInFile(const char *toSearch, const char *fileName, char *inFile);


/* Bu fonksiyon kendisine gelen isimdeki dosyanin okunup okunmayacagina karar 
 * verir. Eger dosyanın sonunda '~' varsa false return eder.
 * Aksi her durum için true dondurur.
 * Parametre : filename -> okunacak dosyanin ismi
 * 
 * Return : Dosya ismine gore true ya da false
 */
bool isFileAvailable(const char *filename);

/* Bu fonksiyon fifo oluşturur ve fifo name ini array'e atar.
 * Parametreler : directory -> fork un icinde yapildigi directory
 *                arrFifo   -> fifo isimlerii tutan array
 */
void createFifos(const char *directory,char arrFifo[MAX_PATH][MAX_PATH] );

/* Bu fonksiyon kendisine gelen isimdeki dosyayı byte byte okuyarak icinde kac 
 * tane karakter oldugunu return eder.
 *
 * Parametre : filename -> acilacak dosyanin ismi
 *
 * Saydigi karakter sayisini return eder.
 */
int findFileSize(const char *filename);


pid_t flagPid;



/*
 * Mainin baslangici
 *
 */
int main(int argc, char **argv){
	/*Arguman kontrolu ve Usage*/
	if(argc!=3){
			
		fprintf(stderr, "Usage: ./withPipeandFIFO -target -directoryName\n");
		exit(0);
	}
	else{

		DIR *pdrDir = opendir(argv[2]);

		if(pdrDir == NULL){
			fprintf(stderr, "Directory %s cant open.\n", argv[2]);
			exit(0);
		}
		else
			closedir(pdrDir);
	}

	remove(OUTPUT_FILE);
	flagPid = getpid();

	wrapper(argv[1], argv[2]);

	return 0;
} 
/*
 * Mainin bitisi
 *
 */

 void wrapper( const char *target, const char *directory){

 	FILE *fp;
 	int totalOccurance = 0;

 	totalOccurance = searchInDirectory(target, directory);

 	/*Acip total yazilir*/
 	fp = fopen(OUTPUT_FILE, "a");

 	fprintf(fp, "%d %s were found in total\n", totalOccurance, target);

 	fclose(fp);

 	fp = NULL;
 }

int searchInDirectory( const char *target, const char *directory){
	DIR *pDir = NULL;
	DIR *pDirTemp = NULL;
	struct dirent *pDirent = NULL;

	int numberOfFile = 0,
		numberOfDir = 0,
		temp = 0, /*En basta pipe a yazacagimiz toplam deger*/
		stat, /*Olen cocuklarin dondurduklerini kontrol eden degisken*/
		i =0;
	int fd[2];

	int tempCountFromFile = 0,
		countFromFile = 0,
		tempCountFromDir = 0,
		countFromDir = 0,
		totalOccurrance = 0; /*Verilen directorydeki tum bulunan stringler*/

	int readFifo, /*Okumak icin acarken kullanilacak*/
	    writeFifo; /*Yazmak icin acarken kullanilacak*/

	pid_t child;

	char /*FIFONames[MAX_PATH][MAX_PATH],*/
		 fifoName[MAX_PATH],
		 subDirectoryPath[MAX_PATH],
		 tempPathName[MAX_PATH],
		 dName[MAX_PATH];

	const char ch[2] = "/";
	char *token = NULL;
	char keepDirName[MAX_PATH];

	char FIFONames[MAX_PATH][MAX_PATH] = {{0}};




	/*Directory ve file sayisini bul*/
	findAll(directory,&numberOfFile,&numberOfDir);

	/*Make fifos*/
	createFifos(directory, FIFONames);

	/*Make pipe*/
	if(numberOfFile > 0){
		if( pipe(fd) == FAIL){
			fprintf(stderr, "Failed to open pipe. Errno : %s\n",strerror(errno));
			exit(FAIL);
		}

		write(fd[1], &temp, sizeof(temp));

	}

	/* Open the directory */
	if ( (pDir = opendir(directory)) == NULL){
		fprintf(stderr, " '%s' couldn't open\n", directory);
		exit(FAIL);
	}

	while( (pDirent = readdir(pDir)) != NULL ){

		/*Ozel durum kontrolu*/
		if( strcmp(pDirent->d_name,".") != 0 && strcmp(pDirent->d_name,"..") != 0 ){

			/*dosyanin adinin path e donusturulmesi */
			sprintf(subDirectoryPath, "%s/%s", directory , pDirent->d_name);
			
			/*Directory mu file mi ?*/
			if((pDirTemp = opendir(subDirectoryPath)) != NULL ){
				closedir(pDirTemp);	

				child = fork();

				if(child == 0){

					searchInDirectory(target, subDirectoryPath);

					exit(1);
				}
			}
			else if( isFileAvailable(subDirectoryPath) == true ){

				child = fork();

				if(child == 0){
					strcpy(tempPathName, pDirent->d_name);
					/*Kelimenin bu file da kac kere gectigini ogren*/
					tempCountFromFile = searchInFile(target,subDirectoryPath, tempPathName );

					/*Pipe'dan toplam sayiyi ogren*/
					read(fd[0], &countFromFile, sizeof(countFromFile));

					/*Toplam sayiyla file'da kac kere gectigini topla*/
					countFromFile += tempCountFromFile;

					/*Yeni toplami dosyaya yaz*/
					write(fd[1], &countFromFile, sizeof(countFromFile) );

					exit(1);

				}
			}
		}
	}

	closedir(pDir);

	/*Read for fifo*/
	for(i = 0; i < numberOfDir; ++i){

		sprintf(fifoName, "%s", FIFONames[i]);
		if( (readFifo = open(fifoName, O_RDONLY)) != FAIL ){
			/*Fifoya yazılanı count u oku*/
			read(readFifo, &tempCountFromDir, sizeof(tempCountFromDir));
			close(readFifo);

			unlink(fifoName);

			/*Toplam count ile topla*/
			countFromDir += tempCountFromDir;

		}
	}

	while(wait(&stat) != FAIL){

		if(stat == FAIL)
			fprintf(stderr, "There is an error in fork process. \n");

	}


	/*pipe ile geleni oku*/
	if(numberOfFile > 0){
		read(fd[0], &tempCountFromDir, sizeof(tempCountFromDir));
	}

	/*Tum total tekrari hesapla*/
	totalOccurrance = tempCountFromDir + countFromDir;

	if(getpid() != flagPid) {

		/*directory constant oldugu icin strtok ile kullanilamaz*/
		strcpy(keepDirName, directory); 

		token = strtok(keepDirName, ch);

		while(token != NULL){
			strcpy( dName, token);

			token = strtok(NULL, ch);
		}

		sprintf(fifoName, "%d-%s.fifo", getppid(), dName);
		/*Yazmak uzere ac*/
		writeFifo = open(fifoName, O_WRONLY);
		/*total i yaz*/
		write(writeFifo, &totalOccurrance, sizeof(totalOccurrance));
		close(writeFifo);
	}
	pDirent = NULL;
	pDir = NULL;
	pDirTemp = NULL;
	token = NULL;
	return totalOccurrance;
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
        exit(FAIL);
    }

    if((fpLogFile = fopen(OUTPUT_FILE, "a")) == NULL){
		
		fprintf(stderr, "Log file %s couldn't open.\n", OUTPUT_FILE);
		exit(FAIL);
	}

	lenOfTarget = strlen(toSearch);

	fileSize = findFileSize(fileName);

	charsInFile = (char*)malloc(sizeof(char) * fileSize);

	if(charsInFile == NULL){
		fprintf(stderr, "Memory allocation error. Program will be closed");
		exit(FAIL);
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

void createFifos(const char *directory,char arrFifo[MAX_PATH][MAX_PATH] ){

	DIR *pDir = NULL;
	DIR *dpTemp = NULL; /*Director olup olmadiginin kontrolu*/
	struct dirent *pDirent = NULL;
	char subDirectoryPath[MAX_PATH],
		fifoName[MAX_PATH];
	int i = 0;

	if( (pDir = opendir(directory)) == NULL ){

		fprintf(stderr,"Failed to open: '%s'.\n",directory);
    	exit(FAIL);
	} 
	
	while( ( pDirent = readdir(pDir)) != NULL){

		/*Ozel durum kontrolu*/
		if( strcmp(pDirent->d_name,".") != 0 && strcmp(pDirent->d_name,"..") != 0 ){

			/*dosyanin adinin path e donusturulmesi */
			sprintf(subDirectoryPath, "%s/%s", directory , pDirent->d_name);

			/*file mi directory mu ?*/
			if((dpTemp = opendir(subDirectoryPath)) != NULL ){
				closedir(dpTemp);	

				sprintf(fifoName, "%d-%s.fifo", getpid(), pDirent->d_name);
				strcpy(arrFifo[i],fifoName); /*Array'e gönder*/
				i++;

				if( mkfifo(fifoName, 0666) == FAIL ){
					fprintf(stderr, "Failed to create FIFO...\n");
					exit(FAIL);
				}
			}

		}

	}

	closedir(pDir);
}

bool isFileAvailable(const char *filename){
	int length = strlen(filename);
	if( filename[length-1] == '~' )
		return false;

	return true;
}

void findAll(const char *dir, int *numberOfFile, int *numberOfDir){
	DIR *pdir = NULL;
	DIR *dpTemp = NULL;
	struct dirent *dirent = NULL;
	char subPath[MAX_PATH];

	pdir = opendir(dir);

	while( (dirent = readdir(pdir) ) != NULL ){

		if( strcmp(dirent->d_name,".") != 0 && strcmp(dirent->d_name,"..") != 0 ){

			sprintf(subPath, "%s/%s", dir , dirent->d_name);
			
			if((dpTemp = opendir(subPath)) != NULL){
				closedir(dpTemp);
				++(*numberOfDir);
				findAll(subPath, numberOfFile, numberOfDir);
			}

			else if( isFileAvailable(subPath) == true )
				++(*numberOfFile);
				
		}	
	}
	closedir(pdir);
	pdir = NULL;
	dpTemp = NULL;
	dirent = NULL;

}