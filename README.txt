CS300 Portfolio

This portfolio contains my final projects for CS300, Data Structures and Algorithms.
Project One compares three ways to store course information, including their
runtime and memory use. Project Two uses that analysis in a C++ course planner.
The program reads courses from a file, prints them in order, and shows the
prerequisites for each course.

Coursework

My coursework includes linked lists, hash tables, and binary search trees. The
assignments use auction bids, with options to add, find, and remove a bid. Each
structure handles that information differently. The hash table groups bids into
buckets and uses a linked list when bids share a bucket. The binary search tree
places bids according to their keys, which determine their position in the tree.

The course-planner milestones compare a vector, a hash table, and a binary search
tree. Those designs become part of Project One, which recommends a vector for
the supplied eight-course catalog. Project Two implements that design. This
repository contains the final projects and analysis.

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

The remaining menu options are:

- 2: Print all courses.
- 3: Find a course.
- 9: Exit.

Course lookup accepts lowercase input, such as csci400.

The program reads the supplied unquoted CSV format. It ignores empty prerequisite
fields and checks that every listed prerequisite exists in the catalog. A failed
load keeps the previous catalog. A successful reload replaces it.

What problem did the projects solve?

Both projects organize course information so someone can find a class and see
what they need to take first. The program prints the full list in alphanumeric
order and lets the user search for one course. For example, searching for
CSCI400 shows its title and the prerequisites, CSCI301 and CSCI350. Project One
compares designs for those tasks, while Project Two implements the vector design.

How did I approach the problem?

My analysis compares how each structure loads the file, finds a course, and
prints the list in order. A hash table can find courses faster on average, but
it still needs a separate sorting step to print them in order. For eight courses,
the vector keeps storage simple and avoids the extra buckets or tree nodes.
That is why Project One recommends it. Comparing the structures matters because
the choice affects both the search and the work needed to produce the output.

How did the project address roadblocks?

The course file contains blank prerequisite fields, and rejecting every blank
would exclude valid courses. Some prerequisites also appear later in the file
than the courses that require them. Checking those references too early would
make a valid prerequisite look missing. The loader handles both cases by ignoring
blank prerequisite fields and checking the references after it reads the whole file.

There is also a difference between the sample output and the written instructions.
The sample puts CSCI301 before CSCI300, but the instructions call for alphanumeric
order. The program follows the written instructions and places CSCI300 first.

How does this work affect my approach to software design?

The runtime analysis covers the whole loading process. Before adding a course,
the program searches the existing records to check for a duplicate. Those repeated
searches add work as the file grows, even though adding the record itself is
straightforward. The design therefore needs to account for the checks as well
as the storage. A vector is reasonable for this small catalog. A larger program
would need another comparison based on its size and how often it searches or
sorts the data.

How does it support maintainable, readable, adaptable programs?

The course planner separates parsing, loading, searching, printing, and menu
handling into functions. Each function has a specific job, which makes the code
easier to follow and gives changes a clear starting point. For example, a change
to the file format starts with the parsing function. The loader also checks a
temporary set of courses before replacing the current set. If the new file fails
those checks, the program keeps the courses it already loaded.

Validation and limits

The program passed strict C++11 builds and AddressSanitizer/UndefinedBehaviorSanitizer
checks. The test cases cover the supplied data, missing files, malformed records,
invalid menu input, forward references, repeated loads, and 2,000-course datasets.

The parser does not support quoted fields or multiline titles. It checks missing and
self-referencing prerequisites, but it does not detect cycles between different courses.
Linear lookup is suitable for this small catalog. A much larger catalog would need
another comparison of the data structures.
