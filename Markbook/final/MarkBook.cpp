//============================================================================
// Name        : MarkBook.cpp
// Author      : Thomas Vu, Jean Jung, Nicholas Huston
// Version     : 0.2.0
// Copyright   : Your copyright notice
// Description : A MarkBook Version 2.0 from Lucas ICS4U1 team.
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define RED "\033[31m"
#define WHITE "\033[37m"
#define BLACK   "\033[30m"

/* Student class declaration */
class Student{
public:
    friend void Input(Student stu[]);
    friend void List(Student stu[]);
    friend void Delete(Student stu[]);
    friend void Sort(Student stu[]);
    friend void spelling(Student stu[], char *s);
    friend void lowercase(Student stu[]);
    friend void upper(Student stu[]);
    friend void modify(Student stu[]);
    friend void Search (Student stu[]);
    
	friend void Write(Student stu[],int n);
	friend int Read(Student stu[]);


private:    
    char class_code[8];
    int num; //Student's Number
    char name[25]; //Student's name
    float mark; //Student's mark
    int order;
}stu[200]; //Maximum 200 students

using namespace std;
/* Calling Function */
int menu();
int length(char *s);
void login();
string convertchartostring(char* a, int size);
void change(string s, int index, char newc);
int numcast();

/* Main Menu (back-end) */
int main() {
    login(); //Go to Login
    for (;;) {
        switch (menu()) {
           
        case 1:
        Input(stu);
        break;
       
        case 2:
        List(stu);
        break;
        
        case 3:
        Sort(stu);
        system("pause");
        break;
        
        case 4:
        Delete(stu);
        system("pause");
        break;
        
        case 5:
        lowercase(stu);
        system("pause");
        break;
        
        case 6:
        upper(stu);
        system("pause");
        break;
        
        case 7:
        modify(stu);
        system("pause");
        break;
        
        case 8:
        Search(stu);
        system("pause");
        break;

        case 0:
        cout << endl << "================Thank you for using the MarkBook System==============\n" << endl;
        exit(0);
        }
    }
    return 0;
}

/* Take the Information from the code and print to "score.txt" */
void Write(Student stu[], int n) {
	fstream myFile;
	myFile.open("score.txt", ios::out | ios::binary);
	if (!myFile) {
		cout << "score.txt can't open!" << endl;
		abort();
	}
	int count = n;
	myFile << count << endl<<endl;
	for (int i = 0; i < count; i++) {
	    //Check the spelling before writting information to the file "score.txt"
	    spelling(stu, stu[i].class_code);
	    spelling(stu, stu[i].name);
	    
		myFile << stu[i].class_code  << "\t"
			   << stu[i].num      << "\t"
			   << stu[i].name     << "\t"
			   << stu[i].mark  << endl;
	}
	myFile.close();
}

/* Take the Information from the file "score.txt" and put it in the code */
int Read(Student stu[]) {
	fstream myFile;
	myFile.open("score.txt", ios::in | ios::binary);
	if (!myFile) {
		cout << "score.txt can't open!" << endl;
		abort();
	}
	int count;
	myFile.seekg(0);
	myFile >> count;
	for (int i = 0; i <= count; i++) {
		myFile >> stu[i].class_code >> stu[i].num >> stu[i].name >> stu[i].mark;
		//After getting the information from the fi;e "score.txt" to the code, check the spelling
		spelling(stu, stu[i].class_code);
	    spelling(stu, stu[i].name);
	}
	myFile.close();
	return count;
}

/* Main Menu (front-end) */
int menu() {
    
    char c;
    do {
        system("cls");
        cout <<WHITE<< "**************************************************************" << endl;
        cout << "----------------Welcome to the MarkBook system----------------" << endl;
        cout << "    *            ① Enter Student Info                  *    " << endl;
        cout << "    *            ② List of Student Info                *    " << endl;
        cout << "    *            ③ Sort Student  Mark (High to Low)    *    " << endl;
        cout << "    *            ④ Delete Student Info                 *    " << endl;
        cout << "    *            ⑤ Lowercase all                       *    " << endl;
        cout << "    *            ⑥ Uppercase all                       *    " << endl;
        cout << "    *            ⑦ Modifying                           *    " << endl;
        cout << "    *            ⑧ Searching                           *    " << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "    *            ⓪ Exit the System                     *    " << endl;
        cout << "**************************************************************" << endl;
        cout << "Please Select your Function (0-8):" << endl;
        c = getchar();
    } while (c < '0' || c > '9');
    return (c - '0');
}

/* Log in */
void login(){
    
    cout<<BLACK<<endl;
    FILE *fPtr;
    bool valid = false;
    
    // fopen() returns NULL on failure
    if ((fPtr = fopen("userandpass.txt", "r")) == NULL && !valid) { // The file "userandpass.txt" has to be created to open. Example of a password file is in the zip folder.
        printf("Error opening file\n");
    }
    
    char a[50], b[50];
    
    // fgets() returns NULL on failure
    if ((fgets(a, 50, fPtr) == NULL) || (fgets(b, 50, fPtr) == NULL) && !valid) {
        printf("Error reading file\n");
    }
    
    printf("%s %s\n", a, b);
    
    // fclose() returns 0 on successful completion
    if (fclose(fPtr) != 0 && !valid) {
        printf("Error closing file\n");
    }
    
    
    int a_size = sizeof(a) / sizeof(char);
    int b_size = sizeof(b) / sizeof(char);
    
    string s_a = convertchartostring(a, a_size);
    string s_b = convertchartostring(b, b_size);
    
    cout<<WHITE<<"Enter username, then password."<<endl;
    cout<<"Enter 'CONTACT' in the username section if you need contact information"<<endl;
    string user;
    string password;
    cout<<"Enter User Now: ";
    cin>>user;
    cout<<"Enter Password Now: ";
    cin>>password;
    
    
    change(user, 28, '!');
    
    if(user == "CONTACT"){
        cout<<"\n\nContact Information:"<<endl;
        cout<<"MarkBook 2.0"<<endl;
        cout<<"656 Tennent Ave, London, ON N5X 1L8"<<endl;
        cout<<"help@markbook2.ca"<<endl;
        cout<<"226-236-0772"<<endl;
    }
    
    if(s_a == user + "\n" && s_b == password + "\n"){
        cout<<RED<<"PASSWORD VERIFIED"<<endl;
        valid = true;
    }else{
        login();
    }
    
}

void change(string s, int index, char newc){
    s[index]=newc;
}


string convertchartostring(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; a[i] != '\0'; i++) {
        s = s + a[i];
    }
    return s;
}

/* Inputing student(s)' information into the code */
void Input(Student stu[]){
    bool valid = true;
    system("cls");
    string classcode;
    string name;
    char stunum[10];
    char stumark[10];
    int i = 0;
    int flag;
    char sign = '0';
    cout << endl << "=====>>    Please Enter Student Mark   <<=====" << endl;
    
    while (sign != 'n' && sign != 'N'){
        
        cout << "Class Code: ";
        cin >> stu[i].class_code;
        spelling(stu, stu[i].class_code);//Check spelling of class_code;
        
        do{
            valid = true;
            cout << "Student Number: ";
            stu[i].num = numcast();
            
            int c = 0;
            while(c<i && valid == true){
                c++;
                if (stu[i].num == stu[i-c].num){
                   cout << "The student number you entered already exists! please enter again." << endl;
                }
            }
        }while(!valid);
        
        cout << "Name: ";
        cin >> stu[i].name;
        spelling(stu, stu[i].name); //Check spelling of name;
        
        do {
            flag = 0;
            cout << "Student Mark: ";
            stu[i].mark = numcast();
            
            if (stu[i].mark > 100 || stu[i].mark < 0) {
                cout << " Please enter a mark between 0 and 100! \n";
                flag = 0;
            }
            else{
                flag = 1;
            }
            
        }while (flag == 0);
        
        cout << "======>>    * Whether to continue entering student marks? * (y/n) ";
        cin >> sign;
        i++;
    }
    Write(stu, i);
}

/* Output the list of information into the fromt-end */
void List(Student stu[]) {
    system("cls");
    int n = Read(stu);
    cout << endl << "======>>    Output Student Information    <<======\n" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Class Code" << "\t" << "Student Number" << "\t\t" << "Name" << "\t" << "Mark" << endl;
    for (int i = 0; i < n; i++)
        printf("%10.10s\t %14.14i\t %10.20s\t %3.2f\t\n", stu[i].class_code, stu[i].num, stu[i].name, stu[i].mark);
    cout << "---------------------------------------" << endl;
    Write(stu, n);

}

/* Sorting the list based on the marks of students */
void Sort(Student stu[]) {
    system("cls");
    int k;
    float s;
    char *t;
    t = new char[10];
    cout << endl << "======>>    Descending Sort    <<======" << endl;
    int n = Read(stu);
    printf("stu[0].num is: %i\n", stu[0].num);
    printf("stu[1].num is: %i\n", stu[1].num);
    printf("stu[2].num is: %i\n", stu[2].num); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (stu[j].mark < stu[j + 1].mark) {
                
                //Class Code
                for (int h = 0; h < 10; h++){
                    t[h] = stu[j + 1].class_code[h];
                    stu[j + 1].class_code[h] = stu[j].class_code[h];
                    stu[j].class_code[h] = t[h];
                }
                
                //Name
                strncpy(t, stu[j + 1].name, 10);
                strncpy(stu[j + 1].name, stu[j].name, 10);
                strncpy(stu[j].name, t, 10);
        
                //Mark
                s = stu[j + 1].mark;
                stu[j + 1].mark = stu[j].mark;
                stu[j].mark = s;
            }
        }
    }
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "Class Code" << "\t" << "Student Number" << "\t" << "Name" << "\t" << "Mark" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        stu[i].order = i + 1;
        printf("%10.10s\t %14.14i\t %10.20s\t %3.2f\t\n", stu[i].class_code, stu[i].num, stu[i].name, stu[i].mark);
    }
    Write(stu, n);
}

/* Delete student(s)' information based on student's number*/
void Delete(Student stu[]) {
    system("cls");
    int n = Read(stu);
    int s;
    int i = 0;
    int j;
    cout << "======>>    Delete Student Information    <<======" << endl;
    cout << "Please enter the student number of the student you want to delete: ";
    cin >> s;
    while ((stu[i].num - s) != 0 && i < n)
        i++;
    if (i == n) {
        cout << "======>>    The student could not be found...    <<======" << endl;
    } else {
        for (j = i; j < n; j++) {
            strcpy(stu[j].class_code,stu[j + 1].class_code);
            stu[j].num = stu[j + 1].num;
            strcpy(stu[j].name, stu[j + 1].name);
            stu[j].mark = stu[j + 1].mark;
        }
        cout << "======>>    *The Information is deleted sucessfully!* " << endl;
    }
    Write(stu, n - 1);
}

/* Check Spelling (back-end) */
void spelling(Student stu[], char *s){

    for (int i = 0; s[i] != '\0'; i++){
        if(i > 0 && s[i] > 64 && s[i] < 91){ //if uppercase then make it lowercase
            s[i] += 32;
        }
        
        if (s[i] < 123 && s[i] > 96){ //if lowercase then make it uppercase
            if (i == 0 || s[i - 1] == 44){
                s[i] -= 32;
            }
        }
    }
}

/* Lowercase all of the class_code and name */
void lowercase(Student stu[]){
    int n = Read(stu);
    for (int i = 0; i < n; i++){
        for (int k = 0; k < 10; k++){
            if (stu[i].class_code[k] > 64 && stu[i].class_code[k] < 91 && stu[i].class_code[k] != '\0'){
                stu[i].class_code[k] += 32;
            }
            if (stu[i].name[k] > 64 && stu[i].name[k] < 91 && stu[i].name[k] != '\0'){
                stu[i].name[k] += 32;
            }
        }
    }
    
    system("cls");
    cout << endl << "======>>    Output Student Information    <<======\n" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Class Code" << "\t" << "Student Number" << "\t\t" << "Name" << "\t" << "Mark" << endl;
    for (int i = 0; i < n; i++)
        printf("%10.10s\t %14.14i\t %10.20s\t %3.2f\t\n", stu[i].class_code, stu[i].num, stu[i].name, stu[i].mark);
    cout << "---------------------------------------" << endl;
}

/* Uppercase all of the class_code and name */
void upper(Student stu[]){
    int n = Read(stu);
    for (int i = 0; i < n; i++){
        for (int k = 0; k < 10; k++){
            if (stu[i].class_code[k] > 96 && stu[i].class_code[k] < 123 && stu[i].class_code[k] != '\0'){
                stu[i].class_code[k] -= 32;
            }
            if (stu[i].name[k] > 96 && stu[i].name[k] < 123 && stu[i].name[k] != '\0'){
                stu[i].name[k] -= 32;
            }
        }
    }
    
    
    system("cls");
    cout << endl << "======>>    Output Student Information    <<======\n" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Class Code" << "\t" << "Student Number" << "\t\t" << "Name" << "\t" << "Mark" << endl;
    for (int i = 0; i < n; i++)
        printf("%10.10s\t %14.14i\t %10.20s\t %3.2f\t\n", stu[i].class_code, stu[i].num, stu[i].name, stu[i].mark);
    cout << "---------------------------------------" << endl;
}

/* Changing student's information by selecting their students' number */
void modify(Student stu[]) {
	int n = Read(stu);
	int s;
	int i = 0;
	int len;
	char name[25];
	char classcode[8];
    int flag;
    
	cout << endl << "======>>    Change Student Information    <<======" << endl;
	cout << "Please Enter The Student Number of The Student You Want to Change：";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)i++;
	if (i == n) {
		cout << "======>>    The student Information could not be found    <<======" << endl;
	}
	else {
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "class Code" << "\t" << "Student Number"  << "\t\t" << "Name" << "\t\t" << "Mark" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < n; i++)
            printf("%10.10s\t %14.14i\t %10.20s\t %3.2f\t\n", stu[i].class_code, stu[i].num, stu[i].name, stu[i].mark);
            
		cout << endl << "Please Re-enter This Student's Information： " << endl;
		
		cout << "Class Code: ";
        cin >> classcode;
        strncpy(stu[i].class_code, classcode, 8);
        spelling(stu, stu[i].class_code); //Check the spelling of the class_code
        
        cout << "Student Number: ";
        stu[i].num = numcast(); // Casting from array of characters to numeral
        
        
        cout << "Name: ";
        cin >> name;
        strncpy(stu[i].name, name, 25);
        spelling(stu, stu[i].name); //Check the spelling of the student's name  

		do {
			flag = 0;
			cout << "Mark: ";
			stu[i].mark = numcast(); // Casting from array of characters to number
			if (stu[i].mark > 100 || stu[i].mark < 1) {
                cout << " Please enter a mark between 0 and 100! \n";
			}
			
			else {
				flag = 1;
			}
		} while (flag == 0);

		char c;
		cout << "======>>    Whether to save the Information? (y/n) ";
		cin >> c;
		if (c != 'n' && c != 'N')
			Write(stu, n);
	}
	
	for (int i = 0; i < n; i++)
        printf("%10.10s\t %14.14i\t %10.10s\t %3.2f\t\n", stu[i].class_code, stu[i].num, stu[i].name, stu[i].mark);
}

/* Output the length of the array of characters */
int length(char *s){
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++){
        count++;
    }
    return count;
}

/* Output the student's info of a specific student based on his/her/their student's number */
void Search (Student stu[]) {
    int n = Read(stu);
    int j;
    int i = 0;
    cout << "=====>>    Search Student Info   <<=====" << endl;
    cout << "Please enter the student number: " << endl;
    cin >> j;
	while ((stu[i].num - j) != 0 && i < n)
	i++;
	
	if (i == n) {
        cout << "=====>>   The student could not be found   <<=====" << endl;
    }
    else {
        cout << "---------------------------------------" << endl;
        cout << "Class Code: " << stu[i].class_code << endl;
        cout << "Student Number: " << stu[i].num << endl;
        cout << "Name: " << stu[i].name << endl;
        cout << "Mark: " << stu[i].mark << endl;
    }
}

/* Casting from characters to integer */
int numcast(){
    int x;
    bool valid;
    char input[10];
    do{
        valid = true;
        cin >> input;
        for (int i = 0; input[i] != '\0'; i++){
            if (!isdigit(input[i])){
                printf("Please enter the numerical characters: ");
                valid = false;
                break;
            }else{
                x = atoi(input);
                break;
            }
        }
    } while(!valid);
    
    return x;
}


