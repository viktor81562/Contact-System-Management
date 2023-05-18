#include "contact.h"
#include <conio.h>
#include <fstream>
#include <iostream>
using namespace std;

class contact {
private:
	char fName[50], lName[50], address[50], email[50];
	long long phNo;

public:
	void createContact() {
		cout << "Enter your first name: ";
		cin >> fName;
		cout << "Enter your last name: ";
		cin >> lName;
		cout << "Enter phone: ";
		cin >> phNo;
		cout << "Enter address: ";
		cin >> address;
		cout << "Enter email: ";
		cin >> email;
	}

	void showContact() {
		cout << "Name: " << fName << " " << lName << endl;
		cout << "Phone: " << phNo << endl;
		cout << "Address: " << address << endl;
		cout << "Email: " << email << endl;
	}

	void writeOnFile() {
		char ch;
		ofstream f1;
		f1.open("CMS.dat", ios::binary | ios::app);

		do {
			createContact();
			f1.write(reinterpret_cast<char*>(this), sizeof(*this));
			cout << "Do you have next data?(y/n)";
			cin >> ch;
		} while (ch == 'y');

		cout << "Contact has been Sucessfully Created...";
		f1.close();
	}

	void readFromFile() {
		ifstream f2;
		f2.open("CMS.dat", ios::binary);

		cout << "\n================================\n";
		cout << "LIST OF CONTACTS";
		cout << "\n================================\n";

		while (!f2.eof()) {
			if (f2.read(reinterpret_cast<char*>(this), sizeof(*this)))
			{
				showContact();
				cout << "\n================================\n";
			}
		}
		f2.close();
	}

	void searchOnFile() {
		ifstream f3;
		long long phone;
		cout << "Enter phone no.: ";
		cin >> phone;
		f3.open("CMS.dat", ios::binary);

		while (!f3.eof()) {
			if (f3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (phone == phNo) {
					showContact();
					return;
				}
			}
		}
		cout << "\n\n No record not found";
		f3.close();
	}

	void deleteFromFile() {
		long long num;
		int flag = 0;
		ofstream f4;
		ifstream f5;

		f5.open("CMS.dat", ios::binary);
		f4.open("temp.dat", ios::binary);

		cout << "Enter phone no. to delete: ";
		cin >> num;

		while (!f5.eof()) {
			if (f5.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (phNo != num) {
					f4.write(reinterpret_cast<char*>(this), sizeof(*this));
				}
				else
					flag = 1;
			}
		}
		f5.close();
		f4.close();
		remove("CMS.dat");
		rename("temp.dat", "CMS.dat");

		flag == 1 ?
			cout << endl << endl << "\tContact Deleted..." :
			cout << endl << endl << "\tContact Not Found...";
	}

	void editContact() {
		long long num;
		fstream f6;

		cout << "Edit contact";
		cout << "\n===============================\n\n";
		cout << "Enter the phone number to be edit: ";
		cin >> num;

		f6.open("CMS.dat", ios::binary | ios::out | ios::in);

		while (!f6.eof()) {
			if (f6.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (phNo == num) {
					cout << "Enter new record\n";
					createContact();
					int pos = -1 * sizeof(*this);
					f6.seekp(pos, ios::cur);
					f6.write(reinterpret_cast<char*>(this), sizeof(*this));
					cout << endl << endl << "\t Contact Successfully Updated...";
					return;
				}
			}
		}
		cout << "\n\n No record not found";
		f6.close();
	}
};