CS300 Portfolio

This portfolio contains my final projects for CS300, Data Structures and Algorithms.
Project One covers the design and runtime analysis, and Project Two is the C++
course planner. The program reads a list of courses from a file, puts them in
order, and shows which courses are required before taking another one.

Coursework

My coursework includes assignments on linked lists, hash tables, and binary search
trees. Those programs use auction bids, with options to add, find, and remove a
bid. Although they work with the same type of information, each structure stores
it differently. The hash table uses linked lists when multiple bids belong in the
same bucket, while the binary search tree places bids according to their keys.

The project milestones cover a vector, a hash table, and a binary search tree for
the course planner. Project One brings those designs together and compares their
runtime and memory use. Project Two uses the vector design with the supplied
eight-course file. The files in this repository are the final projects and analysis.

Files

- ProjectTwo.cpp: the complete C++ program.
- data/CS 300 ABCU_Advising_Program_Input.csv: the supplied eight-course dataset.
- docs/Runtime and Memory Analysis.docx: the analysis extracted from the final Project
  One document.
- docs/Project One.docx: the final two-page design, including pseudocode, the runtime
  chart, and the recommendation.

Build and run

Open a terminal in this repository folder. Use a compiler that supports C++11.

c++ -std=c++11 -Wall -Wextra -Werror -pedantic ProjectTwo.cpp -o course_planner
./course_planner

Choose option 1. At the filename prompt, enter:

data/CS 300 ABCU_Advising_Program_Input.csv

The menu also offers option 2 to print all courses, option 3 to find a course, and
option 9 to exit. Course lookup accepts lowercase input, such as csci400.

The program reads the supplied unquoted CSV format. It ignores empty prerequisite fields
and checks that every listed prerequisite exists. A failed load keeps the previous
catalog. A successful reload replaces it.

What problem did the projects solve?

The projects were about organizing course information so someone could see the
available classes and what they needed to take first. The program needed to print
the full list in alphanumeric order and let someone search for a single course.
For example, searching for CSCI400 shows its title and the two prerequisites,
CSCI301 and CSCI350. Project One covers the design for those functions, while
Project Two puts that design into a working program.

How did I approach the problem?

My analysis compares the three structures based on the work the program has to
do, including loading the file, finding a course, and printing the list in order.
A hash table can make searching faster on average, but the program still needs
to sort the courses before printing them. The vector keeps the design simple
for a file with eight courses, which is why it is the recommendation in Project
One. Understanding the structures matters because a choice that works well for
one operation may add work somewhere else in the same program.

How did the project address roadblocks?

One issue with the course file is that some rows have empty prerequisite fields
at the end. Rejecting those rows would mean
rejecting valid courses. Another issue is that a prerequisite can appear further
down in the file, so checking for it too early would make it look like it was
missing. The program handles both by ignoring empty prerequisite fields and
checking the course references after the whole file has been read.

There is also a difference between the sample output and the written instructions.
The sample puts CSCI301 before CSCI300, but the instructions call for alphanumeric
order. The program follows the written instructions and places CSCI300 first.

How does this work affect my approach to software design?

The runtime analysis shows why the rest of the program needs to be considered
along with the data structure. Adding a course to the vector is only part of the
loading process, since the program also searches the courses already loaded to
check for a duplicate. Those repeated checks add more work as the file gets
larger. The vector is reasonable for this small catalog, but a larger project
would need another comparison based on how much information it stores and how
often it searches or sorts that information.

How does it support maintainable, readable, adaptable programs?

The course planner has separate functions for reading the file, loading the
courses, searching, printing, and handling the menu. That makes it easier to
follow what each part does and to change one part without rewriting the others.
If the file format changes, the parsing function is the place to start. The
program also checks a new set of courses before replacing the current set, so
a bad file does not erase information that was already loaded.

Validation and limits

The program passed strict C++11 builds and AddressSanitizer/UndefinedBehaviorSanitizer
checks. The test cases cover the supplied data, missing files, malformed records,
invalid menu input, forward references, repeated loads, and 2,000-course datasets.

The parser does not support quoted fields or multiline titles. It checks missing and
self-referencing prerequisites, but it does not detect cycles between different courses.
Linear lookup is suitable for this small catalog. A much larger catalog would need
another comparison of the data structures.
