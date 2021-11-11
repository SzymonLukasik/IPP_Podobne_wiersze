# IPP similar lines - task specification

## Create a program searching for groups of similar lines in a text.

<hr>

## Definitions

###  Line
Line consists of words separated with white spaces.
White spaces can occur at the beggining and at the end of a line. \
A word consists of sequence of characters with ASCII codes ranging from 33 to 126. \
White spaces are the characters represented in C language as  ' ', '\t', '\n', '\v', '\f', '\r', that is characters with ASCII codes respectively 32, 9, 10, 11, 12, 13. \
A line ends with (at most cases) with a new line character i.e. '\n' character.

### Word

A word can be a number or nonnumber. A word is a number iff it represents an integer:
  - in a decimal format from range [-9223372036854775808, 18446744073709551615],\
  for example: 42, -1, 09, +2, 0, -0, +0, -02;
  - in a hexadecimal format from range [0, 18446744073709551615],\
  for example: 0X0001, 0XABC; 
  - in an octal format from range [0, 18446744073709551615],\
  for example 0177, 0001;

or a floating point number, for example:  0.25, .33, -1E-1, INF, -INF.

If a word is not a number, it is a nonnumber. \
Warning: nan, as the name suggests, is a nonnumber.


### Similarity

Two numbers are similar iff they represent the same number or are indistinguishable in a computer's arithmetic.\
Two nonnumbers are similar iff they represent the same word.\
Whereas small capitals are indistinguishable from capitals.\
Two lines are similar iff they contain the same multisets of numbers and nonnumbers.

## Program's overview

Program reads one line at a time from the standard input.\
Program ignores lines starting with **#** character and not containing any words.\
After reading and processing all lines from the input, program writes to the standard output groups of similar lines, one group in each line.\
Output should be sorted ascending by the lines' numbers.\
Lines are numbered starting with 1.
All lines are numbered, also those ignored and wrong.

## Errors handling and termination

If the line contains an illegal character, then it's a wrong line and the program writes to the standard error:\
**ERROR nr\n**, where nr is the number of the line.
Program doesn't process wrong lines.

Program terminates after precessing all lines from the input.
Program should free the whole allocated memory and terminate with 0 exit code if no critical errors occur, otherwise it should terminate with exit code 1.