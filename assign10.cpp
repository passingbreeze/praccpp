#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
	char name[20];
	unsigned int age;
	char dept[20];
	float score;
public:
	Student(void)
		:age(0), score(0.0f) {}	
	friend istream& operator >> (istream& is, Student& s) {
		string str;
		getline(is,str);
		int i,digit,num;
		
		for(i=0;i<20;++i) {
			s.name[i] = str[i];
		}
		s.name[i-1] = '\0';
		
		for(i=0;i<3;++i) {
			if(str[20+i]==' ')
				break;	
			num = str[20+i]-'0';	
			s.age*=10;	
			s.age+=num;
		}
		
		for(i=0;i<20;++i) 
			s.dept[i] = str[23+i];
		s.dept[i-1]='\0';

		for(i=0;i<4;++i) {
			if(str[43+i]=='.')
				digit = 3-i;
			else {
				num = str[43+i]-'0';
				s.score*=10;
				s.score+=num;
			}
		}

		while(digit>0) {
			digit--;
			s.score/=10;
		}
		return is;
				
	}
	friend ostream& operator << (ostream& os, const Student& s) {
		os << s.name << ' ' << s.age << ' ';
		return os << s.dept << ' ' << s.score;
	}
};

int readFromTextFile(const char* fileName, Student **students)
{
	ifstream ifs(fileName,ios::in);
	if(!ifs.is_open()) {
		cerr << "Input File Error." << endl;
		return 0;
	}
	
	int N;
	ifs >> N;
	*students = new Student[N];
	
	ifs.seekg(3);
	int num=0;
	while(num<N && ifs >> (*students)[num])  
		num++;			
	
	return num;	
}

int readFromBinaryFile(const char* fileName, Student **students)
{
	ifstream ifs(fileName,ios::binary);
	if(!ifs.is_open()) {
		cerr << "Input File Error." << endl;
		return 0;
	}
	
	int N;
	ifs >> N;
	*students = new Student[N];
	
	ifs.seekg(3);
	int num=0;
	while(num<N && ifs >> (*students)[num]) 
		num++;
	
	return num;
}

void writeToBinaryFile(const char* fileName, int n, Student *students)
{
	ofstream ofs(fileName,ios::binary);
	if(!ofs.is_open()) {
		cerr << "Output File Error." << endl;
		return ;
	}
	
	ofs << n << '\r' << endl;
	for(int i=0;i<n;++i) 
		ofs << students[i] << '\r' << endl;
	
	if(students!=NULL) 
		delete[] students;
	ofs.close();	
}

void writeToTextFile(const char* fileName, int n, Student *students) 
{
	ofstream ofs(fileName,ios::out);
	if(!ofs.is_open()) {
		cerr << "Output File Error." << endl;
		return ;
	}
	
	ofs << n << endl;
	for(int i=0;i<n;++i) 
		ofs << students[i] << endl;
	
	if(students!=NULL) 
		delete[] students;
	ofs.close();
}

int main(void)
{
	Student* students;
	readFromBinaryFile("input.txt",&students);
	writeToBinaryFile("output.txt",2,students);
	return 0;
}
