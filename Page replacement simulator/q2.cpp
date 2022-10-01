#include<bits/stdc++.h>
#define lll long long
using namespace std;

map <string,pair<lll,lll>> mapBtech; 
map <string,pair<lll,lll>> mapMtech;
map <string,pair<lll,lll>> mapPhD;

queue<string> qBtech; // We will use queue for FIFO in BTech
vector<string> pTray; // We will use vector for PhD

lll goback = 0; // To keep count of librarian going for searching in library
lll Tb,Tm,Tp; // Tray sizes
lll Nb,Nm,Np; // No of subjects.

lll mTraySize = 0; //Used for maintaining current tray size of MTech subjects

//Function to read the file
void readFile(vector<string> &issueSeq){

    string in_file;
    in_file = "input.txt";

    ifstream in_stream(in_file);

    in_stream>>Nb>>Nm>>Np;

    in_stream>>Tb>>Tm>>Tp;

    string temp;

    while(in_stream>>temp){
        issueSeq.push_back(temp);
    }
    cout<<"\nFollowing is the order of issue requests by studnets:"<<endl;
    for(lll i=0;i<issueSeq.size();i++){
        if(!i)
            cout<<issueSeq[i];
        else
            cout<<" "<<issueSeq[i];
    }

    cout<<"\n\nRead values are: "<<endl;
    cout<<"No of books for B.Tech :"<<Nb<<endl;
    cout<<"No of books for M.Tech :"<<Nm<<endl;
    cout<<"No of books for PhD :"<<Np<<endl;
    cout<<"\nTray size for B.Tech :"<<Tb<<endl;;
    cout<<"Tray size for M.Tech :"<<Tm<<endl;;
    cout<<"Tray size for PhD :"<<Tp<<endl;

    in_stream.close();

}

//Function to issue book to BTech Student
void bTech(string s){

    mapBtech[s].first += 1;
    //If subject is not available on the tray
    if(!mapBtech[s].second){
        //Increase go back as librarian will search library
        goback += 1;
        //if tray is not full
        if(qBtech.size() <= Tb - 1){
            qBtech.push(s);
            mapBtech[s].second = 1;    
        }
        //If tray is full then replace the new book with old book from tray in FIFO manner
        else{
            string temp= qBtech.front();
            mapBtech[temp].second=0;
            mapBtech[s].second=1; 
            qBtech.pop();
            qBtech.push(s);
        }
    }

}

//Function to issue book to MTech student
void mTech(string s){
    //Increase the times the book is issued i.e. frequency
    mapMtech[s].first += 1;

    //If book is not available add it to the tray
    if(!mapMtech[s].second){
        //Librarian has to go back so increase goback
        goback += 1;

        //If tray is not full
        if(mTraySize <= Tm-1){

            mTraySize += 1;
        }

        //If tray is full replace the book according to the least frequency rule
        else
        {   
            lll minFreq=INT_MAX;
            string minSubjectID=""; 
            
            for(auto i=mapMtech.begin();i!=mapMtech.end();i ++){
                
                if(minFreq>(i->second).first && (i->second).second==1){
                    lll temp = (i->second).first;
                    minFreq=temp;
                    minSubjectID=i->first;
                }
            }
            mapMtech[minSubjectID].second=0;
        }

        mapMtech[s].second = 1;
        
    }

}

// Function to issue book to PhD students
void phD(string s){

    mapPhD[s].first +=1 ;

    if(mapPhD[s].second==0){

        //If tray is not full
        if(pTray.size() <= Tp-1){
            pTray.push_back(s);
            
        }
        //If Tray is full replace new book with least recently used book 
        else{
            
            lll pTraySize=pTray.size();
            //Making space for new book
            for(lll i=0;i <= pTraySize-2;i += 1)
            {
                string tmp = pTray[i+1];
                pTray[i+1] = pTray[i];
                pTray[i] = tmp;
            }

            mapPhD[pTray[pTraySize-1]].second=0;
            pTray[pTraySize-1]=s;

            
        }
        mapPhD[s].second = 2-1;
        goback += 1;
    }

    else{
        long pTraySize = pTray.size();
        long stringIndex=0;
        //This loop will find the stringIndex
        for(lll i=0; i <= pTraySize-1;i++){
            if(pTray[i] == s){
                stringIndex=i;
                break;
            }
        }

        for(lll i = stringIndex; i <= pTraySize - 2; i++)
        {
            string tmp=pTray[i+1];
            pTray[i+1]=pTray[i];
            pTray[i]=tmp;
        }
    }
        
}

//This function finds the frequency of the subject(s) which is issued the most
lll maxFrequency(map <string,pair<lll,lll>> subjectMap){
    
    lll maximumFreq=INT_MIN;
    
    for(auto i=subjectMap.begin();i!=subjectMap.end();i++){
        if(maximumFreq <= (i->second).first){
            lll temp = (i->second).first;
            maximumFreq = temp;
        }
    }

    return maximumFreq;
}

//This function will print the vector on screen and file
void printVector(vector<string> v,ofstream& out_fs){
    int vecSize = v.size();
    for(lll i=0;i<vecSize;i++){
        if(i != vecSize-1)
            cout<<v[i]<<" ";
        else 
            cout<<v[i];
        out_fs<<v[i]<<" ";
    }
}

int main(){


    cout << "\n\n|-------------------------------------------------------------------------------------------|\n";
    cout << "|   This Code is authored by Devraj Gadhvi (214101017) and Mayank Singh Parmar (214101027)  |\n";
    cout << "|-------------------------------------------------------------------------------------------|\n";

    vector<string> issues;
    readFile(issues);

    ofstream out_fs;//File output stream
    out_fs.open("output.txt", ofstream::out | ofstream::trunc);

    
    
    //We will handle all the issue requests using their respective functions
    for(lll i=0;i<issues.size();i++){
        if (issues[i][0] == 'B')
            bTech(issues[i]);
        else if (issues[i][0] == 'M')
            mTech(issues[i]);
        else if (issues[i][0] == 'P')
            phD(issues[i]);
        else
        {
            printf("\nInput is not in proper format please check input and try again.\n");
            exit(0);
        }
    }

    printf("\nNo. of times the librarian searched the library: %lld\n\n",goback);
    out_fs<<"\nNo. of times the librarian searched the library: "<<goback;
    out_fs<<"\n\n";
    printf("\n\n <<------- Subject ids of most issued books ------->>\n");
    out_fs<<"\n\n <<------- Subject ids of most issued books ------->>\n";
    vector<string> maxIds;
    lll maxFreq = INT_MIN;

    //Printing max issued subject i.e. subjects which are issued maximum number of time
    for(lll i=0;i<3;i++){

        switch(i){
            
            case 0: 
                if(!mapMtech.empty())
                    {
                        cout<<"\n-----------: For B.Tech students :-----------\n";
                        out_fs<<"\n-----------: For B.Tech students :-----------\n";
                        maxFreq = maxFrequency(mapBtech);
                        for(auto i=mapBtech.begin();i!=mapBtech.end();i++){
                            if(maxFreq==(i->second).first)
                                maxIds.push_back(i->first);
                        }
                        printVector(maxIds,out_fs);
                        maxIds.clear();
                        maxFreq = INT_MIN;
                    }
                else
                    {
                        cout<<"\nNo details to show about B.Tech students."<<endl;
                        out_fs<<"\nNo details to show about B.Tech students."<<endl;
                    }
                    break;
            
            case 1: 
                    if(!mapMtech.empty())
                    {
                        cout<<"\n-----------: For M.Tech students :-----------\n";
                        out_fs<<"\n-----------: For M.Tech students :-----------\n";
                        maxFreq = maxFrequency(mapMtech);
                        for(auto i=mapMtech.begin();i!=mapMtech.end();i++){
                            if(maxFreq==(i->second).first)
                                maxIds.push_back(i->first);
                        }
                        printVector(maxIds,out_fs);
                        maxIds.clear();
                        maxFreq = INT_MIN;
                    }
                    else
                    {
                        cout<<"\nNo details to show about M.Tech students."<<endl;
                        out_fs<<"\nNo details to show about M.Tech students."<<endl;
                    }
                    break;   

            case 2: 
                    if(!mapPhD.empty())
                    {
                        cout<<"\n-----------: For PhD students :-----------\n";
                        out_fs<<"\n-----------: For PhD students :-----------\n";
                        maxFreq = maxFrequency(mapPhD);
                        for(auto i=mapPhD.begin();i!=mapPhD.end();i++){
                            if(maxFreq==(i->second).first)
                                maxIds.push_back(i->first);
                        }
                        printVector(maxIds,out_fs);
                        maxIds.clear();
                        maxFreq = INT_MIN;
                    }
                    else
                    {
                        cout<<"\nNo details to show about PhD students."<<endl;
                        out_fs<<"\nNo details to show about PhD students."<<endl;
                    }
                    break;   

            default: cout<<"\nSome Error Occured";
                     out_fs<<"\nSome Error Occured";
                     break;
        }

        // out_fs<<"\n\n";
        // cout<<"\n\n";
    }

    printf("\n\n<<------- Details of the book present after the simulation ------->>\n");
    out_fs<<"\n\n<<------- Details of the book present after the simulation ------->>\n";


    //Displays the subject present in the trays of each course
    bool avail_phd = false;
    bool avail = false;
    for(lll x=0;x<3;x++){
        switch(x){
            case 0: 
                    if(!qBtech.empty())
                    {
                        cout<<"\n-----------: B.Tech Tray :------------\n";
                        out_fs<<"\n-----------: B.Tech Tray :-----------\n";
                        printf("\nBook id\tSubject id\n");
                        out_fs<<"\nBook id\tSubject id\n";
                        while(!qBtech.empty()){
                            cout<<mapBtech[qBtech.front()].first+1<<"\t"<<qBtech.front()<<"\n";
                            out_fs<<mapBtech[qBtech.front()].first+1<<"\t"<<qBtech.front()<<"\n";
                            qBtech.pop();
                        }
                    }
                    else{
                        cout<<"\nNo books available on the tray of B.Tech."<<endl;
                        out_fs<<"\nNo books available on the tray of B.Tech."<<endl;
                    }
                    break;
            case 1:
                    avail = false;
                        cout<<"\n-----------: M.Tech Tray :-----------\n";
                        out_fs<<"\n-----------: M.Tech Tray :-----------\n";
                    printf("\nBook id\tSubject id\n");
                    out_fs<<"\nBook id\tSubject id\n";
                    for(auto i=mapMtech.begin();i!=mapMtech.end();i++){
                        if((i->second).second==1){
                            avail = true;
                            cout<<(i->second).first+1<<"\t"<<i->first<<"\n";
                            out_fs<<(i->second).first+1<<"\t"<<i->first<<"\n";
                        }
                    }
                    if(!avail)
                    {
                        cout<<"\nNo books available on the tray of M.Tech."<<endl;
                        out_fs<<"\nNo books available on the tray of M.Tech."<<endl;
                    }
                    avail = false;
                    break;
            
            case 2:
                    avail_phd = false;
                    cout<<"\n-----------: PhD Tray :-----------\n";
                    out_fs<<"\n-----------: PhD Tray :-----------\n";
                    printf("\nBook id\tSubject id\n");
                    out_fs<<"\nBook id\tSubject id\n";
                    for(auto i=mapPhD.begin();i!=mapPhD.end();i++){
                        if((i->second).second==1){
                            avail_phd = true;
                            cout<<(i->second).first+1<<"\t"<<i->first<<"\n";
                            out_fs<<(i->second).first+1<<"\t"<<i->first<<"\n";
                        }
                    }
                    if(!avail_phd)
                    {
                        cout<<"\nNo books available on the tray of PhD"<<endl;
                        out_fs<<"\nNo books available on the tray of PhD"<<endl;
                    }
                    avail_phd = false;
                    break;
            
            default:
                     printf("\nSome error occured please try again.\n");
                     out_fs<<"\nSome error occured please try again.\n";
                     break;
        }
        // printf("\n\n");
        // out_fs<<"\n\n";
    }

    out_fs.close();

    return 0;
}