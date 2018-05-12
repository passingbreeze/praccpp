#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> // 소수점 결정을 위한 headerfile

using namespace std;

class student {
	char name[20];
	unsigned age;
	char dept[20];
	float score;
public:
	student(){}

	int str_to_int(string s){
		istringstream iss(s);
		int n = 0;

		iss >> n;
		return n;
	}

	double str_to_double(string s){
		istringstream iss(s);
		iss.setf(ios::fixed | ios::showpoint);
		double f = 0.0;
	
	
		iss >> setprecision(2) >> f;
	
		return f;
	}

	string int_to_str(int n){
		ostringstream oss;
	
		oss << n;

		return oss.str();
	}

	string float_to_str(float f){
		ostringstream oss;
		oss.setf(ios::fixed | ios::showpoint);

		oss << setprecision(2) << f;
		return oss.str();
	}

	int readFromText(char* filename, student** students) {
		int n = 0;
		char std_age[3], std_score[5];
		
		ifstream ifs(filename);

		if(!(ifs.is_open())){
			cerr << "No Input File." << endl;
			return -1;
		}
		ifs >> n; // the number of records
	
		for (int i = 0; i < n; ++i){
			ifs.read((*students)[i].name, 20);			
			ifs.read(std_age, 3);
			(*students)[i].age = (unsigned)str_to_int(std_age);
			
			ifs.read((*students)[i].dept, 20);			
			ifs.read(std_score, 5); // include newline character
			(*students)[i].score = (float)str_to_double(std_score);
			cout << (*students)[i].score << endl;
		}
		ifs.close();
		return n;
	}

	void writeToBinary(char* filename, int n, student* students){
		ofstream ofs(filename, ios::binary); // Ubuntu Linux / Max OS X에서는 ofs.binary도 가능.
		string strage, strscore;

		if(!(ofs.is_open())){
			cerr << "No Output File." << endl;
			return;
		}

		ofs << n;
		for (int i = 0; i < n; ++i)
		{
			strage = int_to_str(students[i].age);
			strscore = float_to_str(students[i].score);
			ofs.write(students[i].name,20);
			ofs.write(&strage[0],3);
			ofs.write(students[i].dept,20);
			ofs.write(&strscore[0], 5);
		}
		ofs.close();
	}

	int readFromBinary(char* filename, student** students){
		int n = 0;
		char std_age[3], std_score[5];
		
		ifstream ifs(filename, ios::binary); // Ubuntu Linux / Max OS X에서는 ifs.binary도 가능.
		
		if(!(ifs.is_open())){
			cerr << "No Input File." << endl;
			return -1;
		}
		ifs >> n; // the number of records
		
		for (int i = 0; i < n; ++i){
			ifs.read((*students)[i].name, 20);			
			ifs.read(std_age, 3);
			(*students)[i].age = (unsigned)str_to_int(std_age);
			
			ifs.read((*students)[i].dept, 20);			
			ifs.read(std_score, 5);
			(*students)[i].score = (float)str_to_double(std_score);
			cout << (*students)[i].score << endl;
		}
		ifs.close();
		return n;
	}
	void writeToText(char* filename, int n, student* students){
		ofstream ofs(filename);
		string strage, strscore;

		if(!(ofs.is_open())){
			cerr << "No Output File." << endl;
			return;
		}

		ofs << n;
		for (int i = 0; i < n; ++i)
		{
			strage = int_to_str(students[i].age);
			strscore = float_to_str(students[i].score);
			ofs.write(students[i].name,20);
			ofs.write(&strage[0],3);
			ofs.write(students[i].dept,20);
			ofs.write(&strscore[0], 5);
		}
		ofs.close();
	}

};

int main()
{
	student* std = new student[100]; // get heap address
	int stdnum1 = 0, stdnum2=0;
	char txtfile[512] = "\0";
	char binfile[512] = "\0";

	cout << "Enter Input Text File name : ";
	cin >> txtfile;
	stdnum1 = std->readFromText(txtfile, &std);
	cout << "the number of students from textfile : " << stdnum1 << endl;

	cout << "Enter Output Binary File name : ";
	cin >> binfile;
	std->writeToBinary(binfile, stdnum1, std);

	stdnum2 = std -> readFromBinary(binfile, &std);
	cout << "the number of students from binfile : " << stdnum2 << endl;

	cout << "Enter Output Text File name : ";
	cin >> txtfile;
	std->writeToText(txtfile, stdnum2, std);

	delete[] std;
	return 0;
}
