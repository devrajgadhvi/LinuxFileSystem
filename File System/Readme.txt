For File System:
----------------------------------------------------------------------------------------------
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

