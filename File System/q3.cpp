// Submission by: Mayank Singh Parmar and Devraj gadhvi
#include<bits/stdc++.h>
#include<algorithm>

using namespace std;

#define FILE_LENGTH 4

//Each file will have name, a number and points to all the blocks which conatins its content
struct Inode{
    string name;
    int inode_number;
    vector<int> block_number;
};

//map stores the name of files with its inode object
map<string,Inode> all_files;

//mapping filename with its inode number
map<string, int> list_of_file;

//Function to create a file
void create_file(string filename, string contents){
    //checking if file exists
    if(list_of_file.find(filename) != list_of_file.end()){
        cout<<"File with given name already exists"<<endl;
        return ;
    }

    srand(time(0));
    //creating new file
    Inode file_obj;
    file_obj.name = filename;
    file_obj.inode_number = rand();

    //update the map
    list_of_file.insert({filename, file_obj.inode_number});
    all_files.insert({filename, file_obj});

    int start=0;
    int limit = contents.length();
    while(start < limit){
        //create new disk block that stores the part of content of file
        string str = contents.substr(start,FILE_LENGTH);
        int disk_block_num = rand();    //randomly allocating the block number
        file_obj.block_number.push_back(disk_block_num);
        string disk_block_name = to_string(disk_block_num)+".txt";

        //Creating block files
        ofstream block_file(disk_block_name);
        block_file<<str;
        block_file.close();
        cout<<"Created file: "<<disk_block_name<<endl;

        start = start + FILE_LENGTH; //update the start pointer
    }

    all_files[filename] = file_obj;


    return;
}

//Function to rename the file name from all data structures
void rename(string old_file_name, string new_file_name){
    //check if the old file exists or not
    if(list_of_file.find(old_file_name)!= list_of_file.end()){
        //now, rename the file
        Inode obj = all_files[old_file_name];
        all_files.erase(old_file_name);
        all_files.insert({new_file_name, obj});

        //rename in other map STL
        int inode_num = list_of_file[old_file_name];
        list_of_file.erase(old_file_name);
        list_of_file.insert({new_file_name, inode_num});

        obj.name = new_file_name;
        cout<<"file with name:"<<old_file_name<<" renamed to "<<new_file_name<<endl;
    }
    else{
        //file does not exists
        cout<<"file with name: "<<old_file_name<<" does not exists"<<endl;
    }
    return;
}

//Function to display the contents of file by accessing/reading all the block files created earlier.
void display_file(string filename){
    //Check the existence of file
    auto itr1 = all_files.find(filename);

    //Checking if the file exists with given name
    if(itr1 == all_files.end()){
        cout<<"File "<<filename<<" does not exist"<<endl;
        return;
    }

    //find inode object with the filename
    Inode obj = all_files[filename];
    cout<<"filename: "<<filename<<endl;
    if(all_files[filename].block_number.empty())
        cout<<"Vector Empty"<<endl;
//    for(int i = 0; i<all_files[filename].block_number.size(); i++){
//        cout<<obj.block_number[i]<<endl;
//    }
    //iterate over the vector storing the disk blocks

    for(auto itr : obj.block_number){
        int block_num = itr;
        string str = to_string(block_num)+".txt"; //disk block file name
//        cout<<"BNlock no: "<< str<<endl;
        //read the file content
        ifstream disk_file;
        disk_file.open(str);
        string lines;
        getline(disk_file,lines);

        cout<<lines; //print file data to console
        disk_file.close();
    }
    cout<<endl;
    return;
}

//Function to delete the file and all the block files created with it.
void delete_file(string filename){
    //Check the existence of file
    auto itr1 = all_files.find(filename);

    if(itr1 == all_files.end()){
        cout<<"File "<<filename<<" does not exist"<<endl;
        return;
    }

    //find inode object with the filename
    Inode obj = all_files[filename];

    //iterate over the vector storing the disk blocks
    for(auto itr : obj.block_number){
        int block_num = itr;
        string str_new = to_string(block_num)+".txt"; //disk block file name
        char * str = new char [str_new.length()+1];
        strcpy(str,str_new.c_str());
        int result = remove(str);
        if(result != 0){
            cout<<"Error in deletion process of file: "<<str<<endl;
        }
    }

    //Delete file name from all map data structures
    all_files.erase(filename);
    list_of_file.erase(filename);
    cout<<"File: "<<filename<<" deleted successfully"<<endl;
    return;
}

//Function to display all the file names present in the system with thier Inodes.
void list_of_files(){
    map<string, int>::iterator it = list_of_file.begin();

    while(it != list_of_file.end()){
        string filename = it->first;
        int inode_num = it->second;

        cout<<"filename: "<<filename<<" -> inode number:"<<inode_num<<endl;
        it++;
    }
    return;
}

int main()
{
    
    string file_name;
    string content;

    bool flag = true;
    do{
        string command = "";
        cout<<">";
        getline(cin,command);
        string cmd = "";

        //Read the type of command from input
        for(int i=0;i<2;i++)
           cmd+=command[i];
        
        //if cmd is mf then we have to create file....
        if(cmd == "mf")
        {
            file_name = "";
            int index=0;
            for(int i = 3 ; i < command.length() ; i++)
            {
                if(command[i]==' ')
                    {
                        index=i;
                        break;
                    }
                file_name += command[i];
            }
            content = command.substr(index+2);
            content.resize(content.size()-1);

            create_file(file_name , content);
        }

		//if cmd is pf then we have to read the file.....
        else if(cmd == "pf")
        {
            
            string cmd = "";
            for(int i=3;i<command.size();i++)
                cmd+=command[i];
            display_file(cmd);
        }

		//if cmd is rf then we have to rename the file ....
        else if(cmd == "rf")
        {
            string file_1 = "";
            int index=0 ;
            for(int i = 3 ; i < command.length() ; i++)
            {
                if(command[i]==' ')
                {
                 index=i;
                 break;
                }   
                file_1 += command[i];
            }
            string file_2 = command.substr(index+1);
            rename(file_1 , file_2);
        }

		//if cmd is ls then we have to print all file in list.....
        else if(cmd == "ls")
        {
             list_of_files();
        }

		//if cmd is df then we have to delete file...
        else if(cmd == "df")
        {
            string dfile_name = command.substr(3);
            delete_file(dfile_name);
        }

		//if cmd if ex then we have to exit the program......
        else if(cmd == "ex")
        {
            flag = 0;
        }

        else
        {
            cout<<"Write a correct command"<<endl;
        }

    }while(flag);
    return 0;
}
