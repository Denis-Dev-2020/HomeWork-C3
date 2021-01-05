#include <stdio.h>
#include <stdlib.h>
#define size 50

	
//  --------------------------------------------------------------------------------------  //
//  ---------------------------- HELP FUNCTIONS ------------------------------------------  //
void Swap (int *a,int *b){int t = *a;*a = *b;*b = t;}
void PrintArray (int *a,int s){printf("\n");for(int i = 0;i < s;i++){printf("%d,",*(a+i));}printf("\n");}
void ArrayCopy (int* a ,int* b, int s){for(int i = 0 ; i < s ; i++){*(a+i) = *(b+i) ;}}
//  --------------------------------------------------------------------------------------  //
//  --------------------------------------------------------------------------------------  //



void shift_element(int* arr, int i){
//  ---------------------- FIRST INITIALIZATION ------------------------------------------  //
int spacing = 1%i , temp [i] , * ptr = &temp[0]; ptr = (int*)malloc(sizeof(int*)*i);
//  --------------------------------------------------------------------------------------  //
// ------------------------- COPYING FROM THE END-----------------------------------  //
for (int j = spacing , k = i ; j >= 0 ; j = j-1 , k = k-1){*(ptr+j) = *(arr+k);}
//  --------------------------------------------------------------------------------------  //
//  ------------------------- SHIFT RIGHT "spacing" TIMES --------------------------------  //
for (int j = spacing, q = 0; j < i; j++ , q++){*(ptr+j) = *(arr+q);}
//  --------------------------------------------------------------------------------------  //
ArrayCopy(arr,ptr,i);}



void insertion_sort(int* arr , int len){
//  ------------------------- INSERTION USING SWAP ---------------------------------------  //	
 for (int i = 0; i < size; i++){
 	int j = i;
 	while ((j>0)&&(*(arr+j-1)>*(arr+j))) {
		Swap(arr+j,arr+j-1);
		j = j-1;}}}
//  --------------------------------------------------------------------------------------  //



void main () {

int array [size],* ptr = &array[0];
printf("\n___________________________________________\n\nPLEASE INSERT 50 INTEGERS :  \n___________________________________________\n\n");

//  ------------------- ASKS THE USER TO FILL THE ARRAY (USING POINTER)-------------------  //
for (int i = 0; i < size; i++){scanf("%d" , ptr+i);}
//  --------------------------------------------------------------------------------------  //


printf("\n		ORIGINAL ARRAY :\n");
PrintArray(ptr,size);
printf("\n		SHIFTING RIGHT FROM INDEX 7 :\n");
shift_element(ptr+6,size-6);
PrintArray(ptr,size);
printf("\n		INSERTION SORT :\n");
insertion_sort(ptr,size);
PrintArray(ptr,size);
printf("\n");

}