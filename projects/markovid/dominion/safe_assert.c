/*
 *Dylan Markovic
 *CS362
 *safe_assert.h
 */
 //safe assert informs tester of bad input without crashing the program
 
 #include "safe_assert.h"
 
 int safe_assert(int x){
	 if(x){
		 printf(" TEST PASSED\n");
		 return 0;
	 } else {
		 printf(" TEST FAILED!!!!!\n");
		 return 1;
	 }
 }