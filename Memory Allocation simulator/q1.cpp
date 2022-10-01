#include<bits/stdc++.h>
using namespace std;

#define SINGLE_ROOM_COST 5000
#define DOUBLE_ROOM_COST 9000
#define TRIPLE_ROOM_COST 12500

int max_revenue=0;
string top_performer = "";

int aman_manager(int num_single_rooms, int num_double_rooms, int num_triple_rooms, vector<char> &room_required, ofstream &outputfile){
    /*AMAN ALLOCATES ROOMS AS FAST AS POSSIBLE
      THAT IS ON NEXT FIT BASIS
      PRIORITY: TRIPLE -> SINGLE -> DOUBLE rooms
    */
    int single_to_double =0; //number of double rooms alloted to single customers
    int single_to_triple =0; //number of triple rooms alloted to single  customers
    int double_to_triple =0; //number of triple rooms alloted to double  customers
    int total_revenue =0;
    int waste_revenue =0; //due to wrong allocation of rooms
    int rejected_requests =0; //due to wrong allocation of rooms
    int pending_triple_request =0;

    int limit = room_required.size();

    for(int i=0; i<limit; i++){
        char room_type = room_required[i];

        //All customers are alloted triple rooms irrespective of their requirement untill all triple rooms are booked
        if(num_triple_rooms > 0){
            //total_revenue += TRIPLE_ROOM_COST;
            num_triple_rooms--;

            //wrong allocation of triple room
            if(room_type == 'S'){
                single_to_triple++;
                total_revenue+= SINGLE_ROOM_COST;
            }
            else if(room_type == 'D'){
                double_to_triple++;
                total_revenue+= DOUBLE_ROOM_COST;
            }
            else{
                total_revenue+= TRIPLE_ROOM_COST;
            }
            continue;
        }

        //once all triple rooms are allocated, nearest are single rooms but they can be allocated to only single room requirement
        if(room_type == 'S'){
            if(num_single_rooms > 0){
                total_revenue += SINGLE_ROOM_COST;
                num_single_rooms--;
            }

            //if single rooms are all occupied, then double rooms shall be provided
            else if(num_double_rooms >0){
                //but these are wrong allocation
                single_to_double++;
                num_double_rooms--;
                total_revenue += SINGLE_ROOM_COST;
            }

            continue;
        }

        //Since first all triple rooms are alloted, they were all alloted
        //Here we will check if we still have double rooms or our request will be rejected
        if(room_type == 'D'){
            if(num_double_rooms > 0){
                num_double_rooms--;
                total_revenue += DOUBLE_ROOM_COST;
            }

            //No double rooms are left, so we check if this is due to wrong alloaction
            else if(single_to_double > 0){
                single_to_double--; 
                rejected_requests ++;
                waste_revenue += DOUBLE_ROOM_COST -SINGLE_ROOM_COST;
                //Since we alloted single customer double room, so he paid for single room cost, hence loss is difference of that
                //also no single rooms are left,since this is next fit
            }

            continue;
        }

        //Here room_type is "T"
        pending_triple_request++; 
        
    }

    //calculating the additional waste revenue due to pending triple requests
    while(pending_triple_request>0){
        if(single_to_triple > 0){
            if(num_single_rooms > 0){
                //single rooms are still available but wrong allocation
                waste_revenue += TRIPLE_ROOM_COST;
            }
            else{
                waste_revenue += TRIPLE_ROOM_COST -SINGLE_ROOM_COST;
                //Since single room were booked and they are paying
            }
            single_to_triple--;
            rejected_requests++;
        }
        else if(double_to_triple > 0){
            if(num_double_rooms >0){
                //Double rooms are still available but alloted in triple 
                waste_revenue += TRIPLE_ROOM_COST;
            }
            else{
                //Double rooms were booked , so they paid money for double rooms which otehrwise would be unalloted
                waste_revenue += TRIPLE_ROOM_COST -DOUBLE_ROOM_COST;
            }
            double_to_triple--;
            rejected_requests++;
        }

        pending_triple_request--;
    }

    cout<<"\n";
    cout<<"Total revenue made by AMAN: "<<total_revenue<<endl;
    cout<<"Number of customers rejected due to wrong alloaction of rooms: "<<rejected_requests<<endl;
    cout<<"Money wasted due to nature of AMAN: "<<waste_revenue<<endl;
    
    outputfile<<"\n";
    outputfile<<"Total revenue made by AMAN: "<<total_revenue<<"\n";
    outputfile<<"Number of customers rejected due to wrong alloaction of rooms: "<<rejected_requests<<"\n";
    outputfile<<"Money wasted due to nature of AMAN: "<<waste_revenue<<"\n";

    if(total_revenue > max_revenue){
        max_revenue = total_revenue;
        top_performer = "AMAN";
    }

    return total_revenue;
}

int raj_manager(int num_single_rooms, int num_double_rooms, int num_triple_rooms, vector<char> &room_required, ofstream &outputfile){
    /*RAJ ALLOCATES ROOMS ON WORST FIT BASIS
      THAT IS BEING DISLOYAL TO MANAGEMENT
      PRIORITY: TRIPLE -> DOUBLE -> SINGLE rooms
    */
    int worng_double_allot =0; //number of double rooms alloted to single customers
    int wrong_triple_allot =0; //number of triple rooms alloted to single or double customers
    int total_revenue =0;
    int waste_revenue =0; //due to wrong allocation of rooms
    int rejected_requests =0; //due to wrong allocation of rooms

    int limit = room_required.size();

    for(int i=0; i<limit; i++){
        char room_type = room_required[i];

        //All customers are alloted triple rooms irrespective of their requirement untill all triple rooms are booked
        if(num_triple_rooms > 0){
            //total_revenue += TRIPLE_ROOM_COST;
            num_triple_rooms--;

            //wrong allocation of triple room
            if(room_type == 'S'){
                wrong_triple_allot++;
                total_revenue+= SINGLE_ROOM_COST;
            }
            else if(room_type == 'D'){
                wrong_triple_allot++;
                total_revenue+= DOUBLE_ROOM_COST;
            }
            else{
                total_revenue+= TRIPLE_ROOM_COST;
            }
            continue;
        }

        //Single customers will first be alloted double rooms and then single rooms
        if(room_type == 'S'){
            if(num_double_rooms > 0){
                num_double_rooms--;
                worng_double_allot++;
                total_revenue+= SINGLE_ROOM_COST;
            }
            else if(num_single_rooms > 0){
                //double rooms are booked, only single rooms left
                num_single_rooms--;
                total_revenue+= SINGLE_ROOM_COST;
            }

            continue;
        }

        if(room_type == 'D'){
           //Triples are already booked , so will check double availability
           if(num_double_rooms> 0){
               num_double_rooms--;
               total_revenue+= DOUBLE_ROOM_COST;
            }
            else{ //calculate the lost revenue due to wrong allocation of double rooms
                if(worng_double_allot > 0){
                    worng_double_allot--;
                    rejected_requests++;
                    waste_revenue+= DOUBLE_ROOM_COST;
                }
            }

            continue;
        }

        //Here, room type is 'T'
        if(wrong_triple_allot > 0){
            wrong_triple_allot--;
            rejected_requests++;
            waste_revenue+= TRIPLE_ROOM_COST;
        }
    }

    cout<<"\n";
    cout<<"Total revenue made by RAJ: "<<total_revenue<<endl;
    cout<<"Number of customers rejected due to wrong alloaction of rooms: "<<rejected_requests<<endl;
    cout<<"Money wasted due to nature of RAJ: "<<waste_revenue<<endl;
    
    outputfile<<"\n";
    outputfile<<"Total revenue made by RAJ: "<<total_revenue<<"\n";
    outputfile<<"Number of customers rejected due to wrong alloaction of rooms: "<<rejected_requests<<"\n";
    outputfile<<"Money wasted due to nature of RAJ: "<<waste_revenue<<"\n";
    
    if(total_revenue > max_revenue){
        max_revenue = total_revenue;
        top_performer = "RAJ";
    }
    return total_revenue;
}

int alok_manager(int num_single_rooms, int num_double_rooms, int num_triple_rooms, vector<char> &room_required, ofstream &outputfile){
    /*ALOK ALLOCATES ROOMS ON BEST FIT BASIS
      THAT IS BEING LOYAL TO MANAGEMENT AND MAXIMISING THE REVENUE
    */
    int total_revenue =0;
    int waste_revenue =0; //due to wrong allocation of rooms
    int rejected_requests =0; //due to wrong allocation of rooms
    int pending_double_request =0;
    int pending_single_request =0;
    int limit = room_required.size();

    for(int i=0; i<limit; i++){
        char room_type = room_required[i];

        //Allocate the triple room requests
        if(room_type == 'T' && num_triple_rooms >0){
            total_revenue+= TRIPLE_ROOM_COST;
            num_triple_rooms--;

            continue;
        }

        if(room_type == 'D'){
            if(num_double_rooms > 0){
                num_double_rooms--;
                total_revenue+= DOUBLE_ROOM_COST;
            }
            else{
                //double rooms are all booked.
                pending_double_request++;
            }

            continue;
        }

        if(room_type == 'S'){
            if(num_single_rooms > 0){
                num_single_rooms--;
                total_revenue+= SINGLE_ROOM_COST;
            }
            else{
                pending_single_request++;
            }
        }
    }

    //pending requests of double rooms can be allocated triple rooms , if available
    for(int j=pending_double_request; j>=1; j--){
        if(num_triple_rooms == 0){
            break;  //double room requests can not be scheduled
        }

        num_triple_rooms--; //allot triple room
        total_revenue+= DOUBLE_ROOM_COST;    
    }

    //pending requests of single rooms can be allocated triple rooms or double rooms , if available
    for(int k=pending_single_request; k>=1; k--){
        if(num_double_rooms > 0){
             //double room requests can  be scheduled
            total_revenue+= SINGLE_ROOM_COST;
            num_double_rooms--;
        }
        else if(num_triple_rooms > 0){
            //allot triple rooms
            total_revenue+= SINGLE_ROOM_COST;
            num_triple_rooms--;
        }
        else{
            break;
        }
    }

    cout<<"\n";
    cout<<"Total revenue made by ALOK: "<<total_revenue<<endl;
    cout<<"Number of customers rejected due to wrong alloaction of rooms: "<<rejected_requests<<endl;
    cout<<"Money wasted due to nature of ALOK: "<<waste_revenue<<endl;

    outputfile<<"\n";
    outputfile<<"Total revenue made by ALOK: "<<total_revenue<<"\n";
    outputfile<<"Number of customers rejected due to wrong alloaction of rooms: "<<rejected_requests<<"\n";
    outputfile<<"Money wasted due to nature of ALOK: "<<waste_revenue<<"\n";
    
    if(total_revenue > max_revenue){
        max_revenue = total_revenue;
        top_performer = "ALOK";
    }
    return total_revenue;
}

int main(){
    //read input from file
    int num_single_rooms=0, num_double_rooms=0, num_triple_rooms=0;
    string input_file_name;
    int total_bookings=0; 
    int file_num=0; //select the input file
    int flag = 1;
    do{
        cout<<"Select the input test file"<<endl;
        cout<<"Press 1 for test case 1"<<endl;
        cout<<"Press 2 for test case 2"<<endl;
        cin>>file_num;

        switch(file_num){
            case 1:
                input_file_name = "input1.txt";
                flag = 0;
                break;
            case 2:
                input_file_name = "input2.txt";
                flag =0;
                break;
            default:
                cout<<"Enter number 1 or 2"<<endl;
                flag = 1;
        }
    }while(flag);
    
    ifstream inputfile(input_file_name);
    inputfile>>num_single_rooms>>num_double_rooms>>num_triple_rooms;
    inputfile>>total_bookings;

    //read the type of bookings from input file
    char room_type;
    vector<char> room_required; //store the type of room required to customer at time of enquiry
    for(int i=0; i<total_bookings; i++){
        inputfile>>room_type;
        room_required.push_back(room_type);
    }

    //closing the input file
    inputfile.close();

    //test the data read from file
    cout<<"number of single rooms :"<<num_single_rooms<<endl;
    cout<<"number of double rooms :"<<num_double_rooms<<endl;
    cout<<"number of triple rooms :"<<num_triple_rooms<<endl;
    cout<<"total bookings inquiry :"<<total_bookings<<endl;
    cout<<"type of rooms required :";

    for(int i =0; i< room_required.size(); i++){
        cout<<room_required[i]<<" ";
    }
    cout<<" \n";

    //create output file
    ofstream outputfile;
    outputfile.open("output.txt");

    //call functions
    int revenue_aman = aman_manager(num_single_rooms,num_double_rooms,num_triple_rooms,room_required,outputfile);
    int revenue_raj = raj_manager(num_single_rooms,num_double_rooms,num_triple_rooms,room_required,outputfile);
    int revenue_alok = alok_manager(num_single_rooms,num_double_rooms,num_triple_rooms,room_required,outputfile);

    cout<<"revenue_aman: "<<revenue_aman<<endl;
    cout<<"revenue_raj: "<<revenue_raj<<endl;
    cout<<"revenue_alok: "<<revenue_alok<<endl;

    cout<<endl;
    cout<<"maximum revenue: "<<max_revenue<<endl;
    outputfile<<"maximum revenue: "<<max_revenue<<"\n";

    cout<<"Top performer: "<<top_performer<<endl;
    outputfile<<"Top performer: "<<top_performer<<"\n";

    outputfile.close();
    return 0;
}