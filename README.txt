ABCU Course Planner

This project helps an academic adviser find courses and their prerequisites. It also
prints the full course list in alphanumeric order. The catalog includes computer science
courses and MATH201.

My work across the course

My CS300 coursework includes linked lists, hash tables, and binary search trees for
storing and finding auction bids. Those assignments cover adding records, searching
for a bid, removing it, and reading data from CSV files. The hash-table assignment
uses linked lists to handle collisions, while the tree assignment includes traversal
and removal.

The course-planner milestones compare a vector, a hash table, and a binary search
tree before bringing those designs into Project One. The final analysis considers
runtime, memory use, and the tradeoffs for an eight-course catalog. Project Two
puts the vector design into a working C++ program. It loads courses, prints them
in order, and finds a course with its prerequisites. The files here contain the
final projects and analysis.

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

The adviser needs two views of the same data: the complete course list, and the details
for one course. Project One compares a vector, a hash table, and a binary search tree
for those two jobs. Project Two builds the vector design. Look up CSCI400, for example,
and it returns the course title along with the numbers and titles of its prerequisites,
CSCI301 and CSCI350.

How did I approach the problem?

I started with what the adviser actually needs to do. A fast search is useful, but the
program also has to load the records, check them, and put them in order. For eight
courses, a vector keeps storage simple. Comparing the three structures helped me connect
the choice to the amount of data and the work the program has to do.

How did the project address roadblocks?

The real CSV has empty trailing fields, and some prerequisites show up later in the file
than the courses that list them. A loader that rejected every empty field would throw
out valid records. Checking references during the first pass would have the same problem
with valid course relationships. So the loader ignores empty prerequisite fields and
waits until it has read the whole file before it checks references.

The sample output was another issue. It lists CSCI301 before CSCI300, even though the
written requirement asks for alphanumeric order. The program follows the written
requirement. The tests compare all eight course records with the source data and check
that a failed reload keeps the previous catalog.

How does this work affect my approach to software design?

The runtime analysis gives me a reason to look at the complete operation before picking
a structure. A vector append is cheap, but the duplicate check still scans the earlier
courses, and that makes the full load quadratic under the stated assumptions. On future
projects, I'd compare the validation and output requirements right alongside insertion
and lookup costs.

How does it support maintainable, readable, adaptable programs?

The program keeps parsing, loading, lookup, printing, and menu handling separate. That
makes each function easier to check, and it gives input changes an obvious place to go.
The loader builds a temporary catalog before it replaces the current one. I'd reuse that
pattern anywhere a partial update could leave a program with unusable data.

Validation and limits

The program passed strict C++11 builds and AddressSanitizer/UndefinedBehaviorSanitizer
checks. The test cases cover the supplied data, missing files, malformed records,
invalid menu input, forward references, repeated loads, and 2,000-course datasets.

The parser does not support quoted fields or multiline titles. It checks missing and
self-referencing prerequisites, but it does not detect cycles between different courses.
Linear lookup is suitable for this small catalog. A much larger catalog would need
another comparison of the data structures.
