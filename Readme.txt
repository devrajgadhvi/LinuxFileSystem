==> System requirements:
- System should have g++ compiler installed as well as C++ STL should be present.
- Also the system should give permission to the program for executing as well as performing file i/o operations.

----------------------------------------------------------------------
For File System:
----------------------------------------------------------------------
There are 6 input commands:
1. mf file-name "filecontents"
2. df file-name
3. rf file-name1 file-name2
4. pf file-name
5. ls
6. ex: for exit

Note: Please provide file name with functions which require them e.g. mf,pf,rf,etc, otherwise it may give error. Also,
      Give proper spacing between commands, filename, file-content.

We have used struct (Inode) to store the information of each file i.e. filename, Inode number and name of all the blocks which store the file contents.
These names are stored in int vector, from which we can later get the filename of these blocks.
Also for mapping , we have used two map functions:
1. map<string,INode_object> : This will store all the file information corresponding to the filename.
2. map<string,int>: This will store the inode number corresponding to the filename.

Output is displayed at the console.

----------------------------------------------------------------------
For Page replacement simulator
----------------------------------------------------------------------
==> Input:
- As specified in the problem statement all the inputs should be read from a file.
- Filename should be "input.txt"
- First line of the input file should be the number of subjects for each course separated by blank spaces. The order is [B.Tech] [M.Tech] [PhD] 
- Second line of the file should be the number of books per tray.The order is [B.Tech] [M.Tech] [PhD]
- Third line of the file should be the subject ids of the books that students have issued i.e. issue requests

Note: Make sure to give appropriate input otherwise program may give inappropriate results.

==> Output:
- All the required output will be provided on the console.
- Also the important output will also be stored in a file named "output.txt"
- Output will  highly depend on the input if the input has some flaws it will be reflected in output as well.

----------------------------------------------------------------------
For Memory Allocation Simulator:
----------------------------------------------------------------------
There are two input file named input1.txt and input2.txt. user can select the inputs from those options.
Output is displayed in the console as well as printed in the output.txt file.

Input is as follows:
1)In the first line of input file no. of single, double and triple occupancy rooms are given.
2)In the second line of input size of customer sequence is given.
3)In the third line of input customer sequnce is given with following symbols 'S'-> single,
'D'-> double, 'T'-> triple occupancy.

There are 3 managers and we have createed 3 functions to calculaye their perfomance.
For each of them we calculate the total_revenue made from bookings, waste reveneue due to inefficient allocation of rooms
and rejected customers requests which would otherwise be fullfilled.

Finally we calculate the best performing manager.

Aman: He allocates the room on Next fit basis i.e. First all the triple rooms, then the single rooms and finally the double rooms.
Raj: He is disloyal to the management and allocates on Worst fit basis. First all the tripple rooms, then the double rooms and finally the single rooms.
Alok: He is efficient in approach and alloacte the rooms on Best fit basis. 
