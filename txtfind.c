#include <stdio.h>
#include <stdlib.h>
#define LINE 256
#define WORD 30
//////// Flag For Option , Global Variable For Size Of The First Word , Copying Function (bug reducer) /////////////
int AorB = 0;
int count_lines = 0;
static int wordsize = 0;
void CopyArray (char *a,char *b,int size){for (int i = 0; i < size; i++){*(a+i) = *(b+i);}}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////// Getting char and decides if raise flag A or B , 1 or 2 //////////////////////////
static void AorBFunction (char a) {
if (a == 65 || a == 97){AorB = 1;}
else if (a == 66 || a == 98){AorB = 2;}
else {AorB = 0;}}
/////////////////////////////////////////////////////////////////////////////////////////////
///////// Getting Line by Line , Im Freeing the malloc inside "AnalysingFirstLine" Function so don't worry //////////
char* getline1(){
char *LinePtr = (char*)malloc(sizeof(char*)*LINE);
int i = 0;
for ( ; (*(LinePtr+i) = getc(stdin)) != '\n' ; i++){}
*(LinePtr+i) = '\0';
return LinePtr;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////// Get all the Data from first line : word , word size , pointer to the word    //////////////////////////
/////////// Im freeing the malloc inside the main don't worry                            //////////////////////////
static char* AnalysingFirstLine (){
char *ptr = (char*)malloc(sizeof(char*)*LINE);
ptr = getline1();
char FirstWord [LINE];
int i = 0;
for ( ; *(ptr+i) != 32 ; i++){ FirstWord[i] = *(ptr+i); }
wordsize = i;
char Option = *(ptr+i+1);
FirstWord[i] = '\0';
char *word = (char*)malloc(sizeof(char*)*wordsize+1);
word = &FirstWord[0];
AorBFunction(Option);
free(ptr);
return word;}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////// Basicly it goes one by one multiply by wordsize so   O(nk) //////////////////////////////////////////////
//////// relying on counter == wordsize to know when we have full word , for small words this  ///////////////////
//////// algorithm basicly make it in O(n) , even for large words like 20 chars it'll be O(20*n)=O(n) ////////////
static int isWordInsideSentenceA (char* Word, char* sentence ) {
int flagIn = 0;
char word [wordsize];
char Sentence[LINE];
for (int i = 0; i < wordsize; i++){word[i] = *(Word+i);}         
for (int i = 0; i < LINE; i++){Sentence[i] = *(sentence+i);}
for (int j = 0 , counter = 0 ; j < (LINE-wordsize) ; j++){
for (int i = 0 ; i < wordsize; i++){
	if (word[i]==Sentence[j+i]){counter++;}}
	if (counter == wordsize){flagIn = 1;break;}else{flagIn = 0;}counter = 0;}
return flagIn;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////// PRINTS OPTION B ONLY EXACT WORDS AND EXACT+1CHAR AT THE END ////////////////////////////////////
static void RegularB(char* Word, char* sentence){
char WordFi[wordsize+1];
int counter = 0;
char word [wordsize+1];
char WordEx[wordsize+1];
int LineIndex = 0;
for (int i = 0; i < wordsize; i++){word[i] = 32;}
for (int i = 0; i < wordsize; i++){word[i] = *(Word+i);}
WordEx[0] = 32;
for (int i = 0; i < wordsize+1; i++){WordEx[i+1] = word[i];}
while (*(sentence+LineIndex) != '\0'){
for (int i = 0 , counter = 0; i < wordsize+2 ; i++){
	if (   WordEx[i]==*(sentence+LineIndex+i)   ){
	counter++;
	}
	if ((wordsize+1)==counter)
	{
	for (int i = 0; i < wordsize+1; i++)
	{
		WordFi[i] = *(sentence+LineIndex+i+1);
	}
	printf("%s\n",WordFi);
	counter = 0;
	}
}
LineIndex++;
}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////// Same algorithm from above but rely on counter == (wordsize-1) , minus 1 char of accuraty , and //////////
///////// print directly from here and doesn't return anything      , O(nk)                              //////////
static void isWordInsideSentenceB (char* Word, char* sentence ) {

char SimilarWord1 [wordsize];
char WordScan [WORD+1];
char WordEx[wordsize+2];
char word [wordsize];
char Sentence[LINE];
for (int i = 0; i < wordsize; i++){word[i] = *(Word+i);}
for (int i = 0; i < LINE ; i++){Sentence[i] = *(sentence+i);}
for (int j = 0; j < (WORD+1) ; j++){WordScan[j] = '\0';}

int LineIndex = 0;
int SimilarityCounter = 0;

//printf("%s\n", Sentence);

while (*(sentence+LineIndex+1) != '\0'){

///////////////////////////////////////////////////////////////////////////////////////////
	for (int j = 0 , SimilarityCounter = 0; j < wordsize; j++){
	if (*(Word+j) == *(sentence+LineIndex+j)){SimilarityCounter++;}
	if ((SimilarityCounter == wordsize-1)&&(                     (          (      (*(sentence+LineIndex+wordsize) == 32)         &&        (*(sentence+LineIndex-2) == 32)             )   ||     ((*(sentence+LineIndex-1) == 32) &&  (*(sentence+LineIndex+wordsize+1) == 32))        ))){
for (int j = 0; j < wordsize+1 ; j++){WordScan[j] = *(sentence+LineIndex+j-1) ;}
	if (WordScan[0]==32){
		for (int i = 0; i < wordsize+1; i++){
			WordScan[i] = *(sentence+LineIndex+i);
		}
	}
printf("%s\n", WordScan );
			SimilarityCounter = 0;
		}
}
////////////////////////////////////////////////////////////////////////////////////////////

for (int j = 0; j < (WORD+1) ; j++){WordScan[j] = '\0';}

///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

LineIndex++;
}

LineIndex = 0;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////// Count how many lines , for future loop stop /////////////////////////////////////////////////////
static void linecounter(){
FILE *fileptr;
int count = 0;
char chr;
fileptr = fopen("input.txt", "r");
chr = getc(fileptr);
while (chr != EOF){
if (chr == '\n'){count = count + 1;}
chr = getc(fileptr);}
fclose(fileptr);
count_lines = count;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~                      MAIN FUNCTION                      ~~~~~~~~~~~~~~~~~~~~~//
void main () {
//////////////////////////// Variables initialization ///////////////////////////////////////////////////////
linecounter();
char *temp = AnalysingFirstLine();
char *ptr = (char*)malloc(sizeof(char*)*wordsize);
char *ptrr ;
CopyArray(ptr , temp , wordsize );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////// Simple 3 way if statements for options : 1 , 2 , Else ////////////////////////////////
/////////////////////// it goes line by line                                  ////////////////////////////////
if (AorB==1){
	char A[LINE];
    for (int j = 0; j < count_lines-1 ; j++){
		ptrr = getline1();
		for (int i = 0; i < LINE; i++){
			A[i] = *(ptrr+i);}
			if (isWordInsideSentenceA(ptr , ptrr)==1){
				printf("%s\n" , A );
			}
	}	
}else if (AorB==2){
char B[LINE];
for (int j = 0; j < count_lines-1 ; j++){
	ptrr = getline1();
	for (int i = 0; i < LINE; i++){
		B[i] = *(ptrr+i);}
    	isWordInsideSentenceB(ptr , ptrr);
    	RegularB(ptr , ptrr);
}



}else {printf("Please Write Option a or b .\n");}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
free(ptr);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~         END OF PROGRAMM          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//             