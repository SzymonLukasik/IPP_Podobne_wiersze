# IPP similar lines

## Program searching for groups of similar lines in a text.

### [Exact specification of the task](https://github.com/SzymonLukasik/IPP_similar_lines/blob/master/PROBLEM_STATEMENT.md)

## Implementation's overview

- Informations about lines are represented in objects of type *line*,
which are kept in a dynamic array. \
- In a log-linear time with respect to the size of the input we sort words in each line and then we sort the vector of *line* objects.
- As a result, we are able to partition sorted lines into groups of similar lines in the linear time.
- Then, we sort vector of obtained groups with respect to the specification of the task and print out the answer.

## Program's structure

Program similar_lines is using seven libraries that provides:

- safealloc.h - functions that allocate memory and in case of failure, terminate program abnormally.
- vector.h - <b>polimorphic dynamic </b> arrays.
- lines.h - *line* type, handling of vector of *line* objejcts, reading input and conversing it  to *line* objects.
- parsing.h - conversion of words to numerical types
- groups.h - handling of result represented as vector of vectors of unsigned integers (identifiers of lines partitioned into groups)
and printing it out
- solve.h - function that creates the partition of sorted lines into similar groups
- sorth.h - functions that compare and sort objects of various types:
  - numbers
  - strings
  - *line* objects
  - vectors of unsigned integers (representing groups of similar lines)

## Usage

Commands should be executed from root of the repository. 
- Check for compilation errors with <code>./scripts/compilation_test.sh</code>
- Create the executable with <code> make </code>
- Test the program with <code> ./scripts/test.sh similar_lines tests </code>
- Clean the repository with <code> make clean </code>