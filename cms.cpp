#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

enum group {
    FAMILY,
    FRIENDS,
    WORK
};

class contact{
private:
    char fName[50], lName[50], address[50], email[50];
    long long phNo;
    group contactGroup;

public:
    void createContact() {
        cout << "Enter your first name: ";
        cin >> fName;
        cout << "Enter your last name: ";
        cin >> lName;

        while (true) {
            cout << "Enter phone: ";
            cin >> phNo;

            string phoneStr = to_string(phNo);
            if (phoneStr.length() == 10 && regex_match(phoneStr, regex("^[0-9]+$"))) {
                break;
            } else {
                cout << "Invalid phone number. Please enter a 10-digit number." << endl;
            }
        }

        cout << "Enter address: ";
        cin >> address;
        cout << "Enter email: ";
        cin >> email;

        int groupChoice;
        cout << "Enter the group for this contact (1 for family, 2 for friends, 3 for work): ";
        cin >> groupChoice;

        while (groupChoice < 1 || groupChoice > 3) {
            cout << "Invalid group choice. Please enter a number between 1 and 3: ";
            cin >> groupChoice;
        }

        contactGroup = (group) (groupChoice - 1);
    }

    void showContact() {
        cout << "Name: " << fName << " " << lName << endl;
        cout << "Phone: " << phNo << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
        cout << "Group: ";
        switch (contactGroup) {
            case FAMILY:
                cout << "Family";
                break;
            case FRIENDS:
                cout << "Friends";
                break;
            case WORK:
                cout << "Work";
                break;
        }
        cout << endl;
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

        cout << "Contact has been Successfully Created...";
        f1.close();
    }

    void readFromFile() {
        ifstream f2;
        f2.open("CMS.dat", ios::binary);

        cout << "\n================================\n";
        cout << "LIST OF CONTACTS";
        cout << "\n================================\n";

        while (!f2.eof()) {
            if (f2.read(reinterpret_cast<char*>(this), sizeof(*this))) {
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
            if