/* Homework 2 - Assembly Fizzbuzz
 Your program must print the numbers from 1 to 100, except when:
   1) If the number is divisible by 15, print FizzBuzz instead, if not:
   2) If the number is divisible by 3, print Fizz instead
   3) If the number is divisible by 5, print Buzz instead
 I have provided you functions that will do the printing, you just need
 to do the control logic.

 Don't modify the C file at all, or your house will lose 50 points.

 Don't use R0 through R3 in this function (except in the one example below)
 They get overwritten every time you call a function.
 So use R4 through R10 for your logic

Any line marked with DM ("Don't Modify") should probably be left alone.
The rest of the source code is just example source code and can be deleted or changed.
*/

	.global fizzbuzz     @DM - Don't modify
fizzbuzz:                @DM - Don't modify
	PUSH {LR}            @DM: Preserve LR for the calling function
	PUSH {R4-R12}        @DM: This preserves the R4 through R12 from the calling function

	MOV R4, #1			// Start w/ 1

main_loop:	
	MOV R5, R4			// Copy Total count to for 5
	MOV R6, R4			// Copy Total count to for 3
	MOV R7, R4			// Copy Total count to for 15

	BL loop_15
	
	BAL return           @Return back to main()

// Fizzbuzz Work
loop_15:

	SUBS R7, R7, #15	// Subtract 15, Flagged expecting a negative, compare to 0
	BGT loop_15			// It is greater than 15, repeat to -15
	ADDMI R7, R7, #15	// -15 and made negative number, add 15 back
	BEQ print_FB		// Subtracted 15 and was == 0, print FizzBuzz
	
	CMP R7, #15			// Is it less than 15 (but positive)?
	BLT loop_5			// See if divisble by 5

// Buzz Work
loop_5:
	SUBS R5, R5, #5		// Subtract 5, Flagged expecting a negative, compare to 0
	BGT loop_5			// Is it greater than 0 < 5 < 15?
	ADDMI R5, R5, #5	// -5 and made negative number, add 5 abck
	BEQ print_B			// Subtracted 5 and was == 0, print Fizz
	
	CMP R7, #5			// Is it less than 5 (but positive)?
	BLT loop_3			// See if divisible by 3

//Fizz work
loop_3:
	SUBS R6, R6, #3		// Subtract 3, flagged expecting a negative, compare to 0
	BGT loop_3			// It is greater than 0 < 3 < 5
	ADDMI R6, R6, #3	// -3 and made negative number, add 3 back
	BEQ print_F			// Subtracted 3 and was == 0, print Buzz

	BL print_num		// F*ck it, print the number

print_FB:
	BL print_fizzbuzz    @How to print "FizzBuzz"
	ADD R4, R4, #1		// Incriment by 1
	BAL main_loop
print_F:
	BL print_fizz        @How to print "Fizz"
	ADD R4, R4, #1		// Incriment by 1
	BAL main_loop
print_B:
	BL print_buzz        @How to print "Buzz"
	ADD R4, R4, #1		// Incriment by 1
	CMP R4, #101		// Have we gone past 100?
	BEQ return			// Quit
	BLT main_loop		// Otherwise, back to main
print_num:
	MOV R0, R4
	ADD R4, R4, #1		// Incriment by 1
	BL print_number      @How to print "3" or whatevs
	BAL main_loop

return:
	POP {R4-R12}         @DM: Restore R4 through R12 for the calling function
	POP {PC}             @DM: Return from a function
	@BX LR               @This is another way to return from a function, but it is commented out

@You shouldn't need this function for this assignment, but hey it's there for you
quit:
	MOV R7,#1
	SWI 0

