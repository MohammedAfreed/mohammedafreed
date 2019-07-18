#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
using namespace std;
// defining of multiple classes
class student_data // base class ( class 1)
{
protected:int rollno;
	char name[50];
	int m1, m2, m3, m4, m5;
	double per;
	char grade;
	void calculate();
public:void getdata();
	virtual void m_student(int);// modify function made as virtual
	
};
class student : public student_data // derive class  (inheritance) (class 2)
{
public:
	friend void intro(student);  // friend fuction declaration
	void showdata(); 
	void show_tabular(); 
	int retrollno();
	void m_student(int);
};
void student_data::calculate()
{
	per=(m1+m2+m3+m4+m5)/5.0;
	if(per>=90)
		grade='S';
	else if(per>=80)
		grade='A';
	else if(per>=70)
		grade='B';
	else if(per>=60)
		grade='C';
	else if(per>=35)
		grade='P';
	else
		grade='F';
}
void student_data::getdata()
{
	cout<<"\nEnter The roll number of student :";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student :";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in Mathematics 4 out of 100 : ";
	cin>>m1;
	cout<<"\nEnter The marks in Micrprocessor out of 100 : ";
	cin>>m2;
	cout<<"\nEnter The marks in Computer Organization out of 100 : ";
	cin>>m3;
	cout<<"\nEnter The marks in C++ out of 100 : ";
	cin>>m4;
	cout<<"\nEnter The marks in Economics out of 100 : ";
	cin>>m5;
	calculate();
}
void student::showdata()
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Mathematics 4 is : "<<m1;
	cout<<"\nMarks in Microprocessor is : "<<m2;
	cout<<"\nMarks in Computer Organization is : "<<m3;
	cout<<"\nMarks in C++ is : "<<m4;
	cout<<"\nMarks in Economics is :"<<m5;
	cout<<"\nPercentage of student is  :"<<per;
	cout<<"\nGrade of student is :"<<grade;
}
void student::show_tabular()
{
	cout<<rollno<<setw(6)<<" "<<name<<setw(9)<<m1<<setw(5)<<m2<<setw(5)<<m3<<setw(5)
		<<m4<<setw(6)<<m5<<setw(10)<<per<<setw(5)<<grade<<endl;
}
int  student::retrollno()
{
	return rollno;
}
void write_student();
void display();
void display(int);	
void class_result();
void result();		
void entry_menu();

//main function creation execution starts from here	
int main()
{
	student s1; // (object 1)
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(4); 
	intro(s1);
	do
	{
		system("clear");
		cout<<"\n##########################################\n";
		cout<<"#\n#\n#\t01. RESULT MENU                  #";
		cout<<"\n#\n#\t02. ENTRY/EDIT MENU              #";
		cout<<"\n#\n#\t03. EXIT                         #";
		cout<<"\n#\n#\tPlease Select Your Option (1-3)  #";
		cout<<"\n##########################################\n";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		
		}
    }while(ch!='3');
	return 0;
}
void write_student()
{
	student st;  // (object 2)
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}
void display() // function overloading (polymorphism)
{
	student st; // (object 3)
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\t RECORDS ARE !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}
void display(int n) // function overloading (polymorphism)
{
	student st; // (object 4)
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}
void student_data::m_student(int n)
{
	bool found=false;
	student st;  // (object 5)
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student :"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}
void student::m_student(int n)//delets the record
{
	student st;  // (object 6)
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}
void class_result()
{
	student st;  // (object 7)
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"===============================================================\n";
	cout<<"R.No       Name        M4   MP   CO   C++   ECO   %age   Grade"<<endl;
	cout<<"===============================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}
void result()
{
	char ch;
	int rno;
	system("clear");
	cout<<"\n#####################################\n";
	cout<<"#\n#\tRESULT MENU                 #";
	cout<<"\n#\n#\n#\t1. Class Result             #";
	cout<<"\n#\n#\t2. Student Report Card      #";
	cout<<"\n#\n#\t3. Back to Main Menu        #";
	cout<<"\n#\n#\n#\tEnter Choice (1/2/3)?       #";
	cout<<"\n#####################################\n";
	cin>>ch;
	system("clear");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}
void intro(student s) // friend defination
{
	cout<<"\n###################################################\n";
	cout<<"#\n#\t\t   STUDENT                        #";
	cout<<"\n#\n#\t\t REPORT CARD                      #";
	cout<<"\n#\n#\t\t  SYSTEM                          #";
	cout<<"\n#\n#\n#\t MADE BY : MOHAMMED AFREED                #";
	cout<<"\n# COLLEGE : NEW HORIZON COLLEGE OF ENGINEERING    #"<<endl;
	cout<<"#\n###################################################\n";
	cin.get();
}
void entry_menu()
{
	student s;
	student_data *s1,s2;
	s1=&s2;
	char ch;
	int num;
	system("clear");
	cout<<"\n##########################################\n";
	cout<<"#\n#\n#\tENTRY MENU                       #";
	cout<<"\n#\n#\t1.CREATE STUDENT RECORD          #";
	cout<<"\n#\n#\t2.DISPLAY ALL STUDENTS RECORDS   #";
	cout<<"\n#\n#\t3.SEARCH STUDENT RECORD          #";
	cout<<"\n#\n#\t4.MODIFY STUDENT RECORD          #";
	cout<<"\n#\n#\t5.DELETE STUDENT RECORD          #";
	cout<<"\n#\n#\t6.BACK TO MAIN MENU              #";
	cout<<"\n#\n#\tPlease Enter Your Choice (1-6)   #";
	cout<<"\n##########################################\n";
	cin>>ch;
	system("clear");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display();
			 break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number :"; cin>>num;
			display(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number :"; cin>>num;
			s1->m_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number :"; cin>>num;
			s.m_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
