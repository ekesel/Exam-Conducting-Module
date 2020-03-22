#include <iostream>
#include <string> 
#include <fstream>
#include <cstdlib> 
#include <time.h>
using namespace std;
static string usern; //for getting the username
class user { //for the login system
	public:
		string username; 
		string password;
		string inputusername;
		string inputpassword;
		void userregdo() //for making the registration and appending in the user data file
		{
			ofstream usersFile("userdata.txt", ios::app); //appending the file
			if(!usersFile.is_open())
			{
				usersFile.open("userdata.txt");
			}
			usersFile<<username<<" "<<password<<endl; //storing the username and pass in a line
			::usern = username; //storing the username
			usersFile.close();
		}
		void userregister()
		{
			cout<<"Welcome, Please register\nEnter a username"<<endl;  //for processing the registration
			cin>>username;
			cout<<"Please enter a new Password";
			cin>>password;
		}
		void login() //for login
		{
			cout<<"Please enter your username"<<endl;
			cin>>inputusername;
			cout<<"\nPlease enter your password"<<endl;
			cin>>inputpassword;
			string userpass = inputusername+" "+inputpassword; //making the same pattern to match the file content
			bool found = false;
			string line;
			ifstream usersFile;
			usersFile.open("userdata.txt", ios::app);
			if(usersFile.is_open()) //opening the file
			{
				while(getline(usersFile,line) && !found) //checking for contents of file.
				{
					if(line.compare(userpass) == 0) //using the string compare function to get results.
					{
						::usern = inputusername;
						found = true; //if found the loop will stop.
					}
				}
				usersFile.close();
				if(found) //if found the login is successful and will move to next stage.
				{
					cout<<"Login Attempt successful"<<userpass<<endl;
				}
				else {
					cout<<"Login failed, Enter correct details"<<endl;
					login(); //if failed error will be displayed and recursively login function will be called again.
				}
			}	
		}
};
class tester { //this is the testing class
	public:
		int random(int min, int max) //range : (min, max) random function to throw random numbers in range
		{ //using this i will get random question from question pool file
		   static bool first = true;
		   if (first) 
		   {  
		      srand( time(NULL) ); //seeding for the first time only!
		      first = false;
		   }
		   return min + rand() % (( max + 1 ) - min); //formula for random generation
		}
		void test() //this function will generate test.
		{
			string line="Error"; //default initialization for reading file
			cout<<"Let's continue with the six questions for 30 marks. 5 marks each"<<endl;
			cout<<"Test will be generated in the same folder as the Program"<<endl;
			cout<<"Generated test will be a document file"<<endl;
			ifstream question1("questiondesc.txt"); //opening the descriptive question pool in read mode
			ofstream testgen("GeneratedTest.doc"); //opening the test file in write mode
			if(!question1) //checking for all the flags
			{
				question1.open("questiondesc.txt");
			}
			if(!testgen)
			{
				testgen.open("GeneratedTest.doc");
			}
			int i=0,num=0,prevnum=0;  //default initialization
		    for (i = 0; i < 2; i++) { 
		        num = random(1,12); //calling random function to get a digit in range from line 1 to line 12 as there are only 12 line in question pool file.
		        prevnum = num; //using previous num value so that the question does not get repeated
		        if(i==1) { //for non repetition of question
		        	while(prevnum==num)
		        	{
		        		num = random(1,12);		
					}
				}
		        for(int i =0;i<num;i++) //getting the line present on num value
		        {
		        	getline(question1,line);
				}
				question1.clear();
				question1.seekg(0, ios::beg); //placing the pointer back to beginning to reread file
				testgen<<line<<endl; //writing file with that line
				testgen<<endl;
			}
			ifstream question2("questionmcq.txt"); //now reading the mcq question file
			if(!question2) //checking for all flags.
			{
				question2.open("questionmcq.txt");
			}
			for (i = 0; i < 2; i++) {
				num = random(1,26); //here 26 lines are present in mcq file. 
				while(num%2==0) //i am taking odd num only because every even line in file has the options of mcq and every odd line has the question of mcq 
				{ 
		        num = random(1,26);
		    	}
		    	prevnum = num;
		        if(i==1) { //doing same checking for repetition
		        	while(prevnum==num)
		        	{
		        		num = random(1,26);
						while(num%2==0)
						{ 
				        num = random(1,26);
				    	}		
					}
				}
		        for(int i =0;i<num;i++) //getting the line from num value
		        {
		        	getline(question2,line);
				}
				testgen<<line<<endl; //writing question in file
				getline(question2,line); //getting the options also 
				testgen<<line<<endl; //writing the option in file
				testgen<<endl; //for clearity placing some spaces
				question2.clear(); //clearing the stream
				question2.seekg(0, ios::beg); //placing pointer back to re read file
			}
			ifstream question3("questionanalytical.txt"); //reading the analytical question file
			if(!question3) //checking for all flags
			{
				question3.open("questionanalytical.txt");
			}
			for (i = 0; i < 2; i++) { //same with the descriptive question file
		        num = random(1,12);
		        prevnum = num;
		        if(i==1) {
		        	while(prevnum==num)
		        	{
		        		num = random(1,12);		
					}
				}
		        for(int i =0;i<num;i++)
		        {
		        	getline(question3,line);
				}
				question3.clear();
				question3.seekg(0, ios::beg);
				testgen<<line<<endl;
				testgen<<endl;
			}
			cout<<"Test file generated, Go and give your test and then update your score here aftergetting it checked by teacher"<<endl;
			int choice; //after generation placing choices for the user to do
			cout<<"Enter 1 to go to live score updation menu"<<endl;
			cout<<"Enter 2 to exit";
			for(; ;)
			{
				cin>>choice;
				switch(choice)
				{
					case 1:scoreupdate(); //after giving test he can update his score
					break;
					case 2:exit(0); //or simply exit
					break;
					default:cout<<"Wrong choice, please input again"<<endl;
				}
			}
			
		}
		void livescore() { //this will show everyone's score who has registered
			string line;
			cout<<"Welcome to the live score panel, Below is the list of users with their scores."<<endl;
			cout<<"If you have not attempted any test, your name will not show here"<<endl;
			ifstream score("scoreusers.txt"); //opening the score file in read mode
			if(!score) //checking for flags
			{
				score.open("scoreusers.txt");
			}
			while(!score.eof()) //reading till it reached end of file
			{
				getline(score,line);
				cout<<line<<endl;
			}
		}
		void rewrite_line(int n,string rewrite) //function for rewriting a specific line in file
		{ 
		    ifstream filein("scoreusers.txt"); //opening file in read mode
		    ofstream fileout("temp.txt"); //making a temp file in write mode
		    if(!filein || !fileout) //checking for all flags
			{
		        cout << "Error opening files!" << endl;
		    }
		    string strTemp; //temp string
		    int lineno=1; //line counter
		 	while(filein >> strTemp) //reading file
		    {
		    	lineno++; //counting lines
		        if(lineno == n) //if line matches with desired line to change
				{
		            strTemp = rewrite; //then rewriting the data with new data
		        }
		        strTemp += "\n"; //going ahead
		        fileout << strTemp; //writing data 
		    }
		    filein.close(); //closing the files forcefully
		    fileout.close(); //closing the files forcefully
		    remove("scoreusers.txt"); //removing previous file
		    rename("temp.txt","scoreusers.txt"); //replacing with the new file
		} 
		void scoreupdate() { //score updating menu
			cout<<"Welcome, to the score updation menu"<<endl;
			cout<<"This menu is here for you to update your score, Dont use unfair means as this will only help you to compare how better your are among your friends"<<endl;
			cout<<"Call your teacher before you update the score, The teacher has to enter the master key for updating the score."<<endl;
			cout<<"This is done to verify that you are not using unfair means to increase your scroe"<<endl;
			string masterkey = "mastereke"; //master key to protect unfair means
			cout<<"Now, Enter master key"<<endl;
			string masteruser;
			cin>>masteruser; 
			for(; ;) //infinite loop till we get the exact masterkey
			{
				if(masteruser.compare(masterkey)!=0) //checking
				{
					cout<<"Enter correct master key to proceed"<<endl;
					continue;	
				}
				else
				{
					cout<<"Master key login successful"<<endl;
					break; //breaking the looop
				}
			}
			fstream score("scoreusers.txt",ios::in | ios::out| ios::app); //opening the file with append mode
			if(!score) //checking for all flags
			{
				score.open("scoreusers.txt");
			}
			bool found = false;
			string line="error"; //default initializations in case file fails to open
			string update="error"; //default initilization
			int countline=1; //line counter
			if(score) //if file is opened
			{
				while(getline(score,line) && !found) //while reading is possible and found is false
				{
					countline++; //counting lines
					if(line.compare(::usern) == 0) //if user is found who has logged in
					{
						getline(score,line); //getting one line ahead to get the score
						score.clear(); //clearing the stream
						cout<<"Your current score is - "<<line<<endl; //giving the current score
						cout<<"Enter new score"<<endl;
						cin>>update; //new score
						
						score.close(); //closing file forcefully instead of destructor of fstream class to let the rename and remove functions run
						rewrite_line(countline+1,update); //rewriting scores by calling that function
						found = true; //getting out of loop
					}
				}
			}
			if(!score) //again opening the file by checking all flag
			{
			score.open("scoreusers.txt");
			}
			if(!found) //if it is not found earlier that means new user is there
			{
				while(!score.eof()) //going to end of file
				{
					getline(score,update); //going to end of file means placing the pointer to end
				}
				score.clear(); //clearing the stream
				score<<::usern<<endl; //placing the user name in file
				cout<<"Enter new score"<<endl;
				cin>>update; //placing new score
				score<<update<<endl;
			}
			else {
				cout<<"Score updated, forwarding to live score panel"<<endl;
			}
			livescore(); //calling livescore function to exit from this function
		}
};
class count { //live counter to how many times this function was called written in C as it was easy with the scanf and printf functions
	public:
	int noofpeople() {
		int count=0;
	    FILE *fp; //creating file 
	    fp = fopen("count.txt", "r"); //opening file in read mode
	    if(fp!=NULL) //if file is not empty
	        fscanf(fp, "%d", &count); //placing the file content in count variable
	    fclose(fp); //closing file
	    fp = fopen("count.txt", "w"); //opening file again but in write mode
	    if(fp!=NULL) // if file isnt empty
	        fprintf(fp, "%d", count+1); //printing the count value incremented by 1 to file
	    fclose(fp); //closing the file
	    return count;        //returning value of count
	}
};
main()
{
	int pass=0,log;
	user uobj; //object of user class
	cout<<"Hello Paricipants, Welcome to Eke's Online Testing Platform."<<endl;
	cout<<"We have the login system to update the live scores between users so that you can track your progress"<<endl;
	cout<<"Enter 1 to signup"<<endl;
	cout<<"Enter 2 to login"<<endl;
	cout<<"Enter 3 to exit"<<endl;
	cin>>log;
	switch(log) //giving user choices to perform
	{
		case 1:uobj.userregister(); //user registration
		uobj.userregdo(); //process registration
		break;
		case 2:uobj.login(); //user login
		break;
		case 3:exit(0); //exit 
		break;
		default:cout<<"Wrong input, please input again"<<endl;
		break;
	}
	cout<<"There will be six questions for you to attempt."<<endl;
	cout<<"Happy Learning!"<<endl;
	count cobj; //count class object
	int counter = cobj.noofpeople(); //calling count function
	int c;
	cout<<"Test attempted uptill now on our platform - "<<counter<<endl; //showing how many times the test has been done
	while(pass==0) //loop till pass is zero
	{
		cout<<"Enter 1 to generate test."<<endl;
		cout<<"Enter 2 to check live score among your fellow mates"<<endl;
		cout<<"Enter 3 to update your score"<<endl;
		cout<<"Enter 4 to exit"<<endl;
		cin>>c;
		tester t; //tester class object
		switch(c)
		{
			case 1:t.test(); //calling test function
			break;
			case 2:t.livescore(); //calling livescore function
			break;
			case 3:t.scoreupdate(); //calling scoreupdate function
			break;
			case 4:pass=1; //to exit loop
			break;
			default:cout<<"Wrong input, please input again"<<endl;
		}
	}
}
