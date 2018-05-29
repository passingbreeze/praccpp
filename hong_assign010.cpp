#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip> // header for set precision

using namespace std;

class student {
	char name[20];
	unsigned age;
	char dept[20];
	float score;
public:
	student() {}

	int str_to_int(string s) {
		istringstream iss(s);
		int n = 0;

		iss >> n;
		return n;
	}

	double str_to_double(string s) {
		istringstream iss(s);
		iss.setf(ios::fixed | ios::showpoint);
		double f = 0.0;

		iss >> setprecision(2) >> f;

		return f;
	}

	string int_to_str(int n) {
		ostringstream oss;
		oss << n;
		return oss.str();
	}

	string float_to_str(float f) {
		ostringstream oss;
		oss.setf(ios::fixed | ios::showpoint);

		oss << setprecision(2) << f;
		return oss.str();
	}

	int readFromText(char* filename, student** students) {
		int n = 0;

		ifstream ifs(filename);

		if (!(ifs.is_open())) {
			cerr << "No Input File." << endl;
			return -1;
		}
		ifs >> n; // the number of records

		for (int i = 0; i < n; ++i)
			ifs >> (*students)[i];
		ifs.close();
		return n;
	}

	void writeToBinary(char* filename, int n, student* students) {
		ofstream ofs(filename, ios::binary);
		// in Ubuntu Linux / Max OS X, "ifs.binary" can be used instead of "ios::binary".

		if (!(ofs.is_open())) {
			cerr << "No Output File." << endl;
			return;
		}

		ofs << n;
		for (int i = 0; i < n; ++i) {
			ofs << students[i];
		}
		ofs.close();
	}

	int readFromBinary(char* filename, student** students) {
		int n = 0;

		ifstream ifs(filename, ios::binary);
		// in Ubuntu Linux / Max OS X, "ifs.binary" can be used instead of "ios::binary".

		if (!(ifs.is_open())) {
			cerr << "No Input File." << endl;
			return -1;
		}
		ifs >> n; // the number of records

		for (int i = 0; i < n; ++i)
			ifs >> (*students)[i];
		ifs.close();
		return n;
	}

	void writeToText(char* filename, int n, student* students) {
		ofstream ofs(filename);

		if (!(ofs.is_open())) {
			cerr << "No Output File." << endl;
			return;
		}

		ofs << n;
		for (int i = 0; i < n; ++i) {
			ofs << students[i];
		}
		ofs.close();
	}

	friend istream& operator>>(istream& is, student& s) {
		char std_age[3], std_score[5];
		is.read(s.name, 20);
		is.read(std_age, 3);
		s.age = (unsigned)(s.str_to_int(std_age));
		is.read(s.dept, 20);
		is.read(std_score, 5);
		s.score = (float)(s.str_to_double(std_score));
		return is;
	}

	friend ostream& operator<<(ostream& os, student& s) {
		string strage, strscore;

		strage = (s.int_to_str(s.age));
		strscore = (s.float_to_str(s.score));
		os.write(s.name, 20);
		os.write(&strage[0], 3);
		os.write(s.dept, 20);
		os.write(&strscore[0], 4);
		return os;
	}
};

int main()
{
	student* std = new student[100]; // get heap address
	int stdnum1 = 0, stdnum2 = 0;
	char txtfile[512] = "\0";
	char binfile[512] = "\0";

	cout << "Enter Input Text File name : ";
	cin >> txtfile;
	stdnum1 = std->readFromText(txtfile, &std);
	cout << "the number of students from textfile : " << stdnum1 << endl;

	cout << "Enter Output Binary File name : ";
	cin >> binfile;
	std->writeToBinary(binfile, stdnum1, std);

	stdnum2 = std->readFromBinary(binfile, &std);
	cout << "the number of students from binfile : " << stdnum2 << endl;

	cout << "Enter Output Text File name : ";
	cin >> txtfile;
	std->writeToText(txtfile, stdnum2, std);

	delete[] std;
	return 0;
}