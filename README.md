## Quest 1. Sorting the binary file.

An src/state_sort.c program sorts records in the datasets/door_state_1 binary file in ascending order of their date and time. The file it self contains array of structures. Time structure is used to perform a conversion!

| Input | Output |
| ----- | ----- |
| datasets/door_state_1<br/>0| 2020 9 1 12 0 0 0 153<br/>2020 3 25 19 37 56 1 951<br/>2020 4 3 1 53 26 1 393<br/>...<br/> 1991 6 28 10 50 57 0 732<br/>1924 11 22 2 24 10 1 398 |
| datasets/door_state_1<br/>1| 1920 2 24 7 39 14 0 112<br/>1920 4 26 0 32 33 0 926<br/>1920 7 5 18 8 7 1 216<br/>...<br/> 2020 5 30 16 51 40 1 147<br/>2020 9 1 12 0 0 0 153 |
| datasets/door_state_1<br/>2<br/>2020 12 21 23 54 26 1 768| 1920 2 24 7 39 14 0 112<br/>1920 4 26 0 32 33 0 926<br/>1920 7 5 18 8 7 1 216<br/>...<br/> 2020 5 30 16 51 40 1 147<br/>2020 9 1 12 0 0 0 153<br/>2020 12 21 23 54 26 1 768 |

The executable file is build using makefile with appropriate target!

## Quest 2. Search.

An src/state_search.c program conducts a search by date in the binary file in the "DD.MM.YYYY" format. When launched, the program should receive the path to the file and the search string with a date.

| Input | Output |
| ----- | ----- |
| datasets/door_state_2<br/>01.09.2020 | 153 |

The executable file is build using makefile with appropriate target!