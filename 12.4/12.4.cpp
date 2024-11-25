#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

struct Note {
    char surname[50];  
    char name[50];    
    char phone[15];  
    int birthDate[3]; 
};

bool isValidPhone(const string& phone) {
    if (phone.length() < 10 || phone.length() > 15) return false;
    for (char c : phone) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

bool isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2024) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) return false;
    }
    return true;
}

void addNoteToFile(const string& filename) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file) {
        cerr << "������� �������� ����� ��� ������!" << endl;
        return;
    }

    Note person;
    cout << "������ �������: ";
    cin >> setw(50) >> person.surname;

    cout << "������ ��'�: ";
    cin >> setw(50) >> person.name;

    do {
        cout << "������ ����� �������� (10-15 ����): ";
        cin >> setw(15) >> person.phone;
        if (!isValidPhone(person.phone)) {
            cout << "����������� ����� ��������! ��������� �� ���." << endl;
        }
    } while (!isValidPhone(person.phone));

    do {
        cout << "������ ���� ���������� (���� ����� ��): ";
        cin >> person.birthDate[0] >> person.birthDate[1] >> person.birthDate[2];
        if (!isValidDate(person.birthDate[0], person.birthDate[1], person.birthDate[2])) {
            cout << "���������� ���� ����������! ��������� �� ���." << endl;
        }
    } while (!isValidDate(person.birthDate[0], person.birthDate[1], person.birthDate[2]));

    file.write((char*)&person, sizeof(Note));
    file.close();
}

void sortNotesInFile(const string& filename) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cerr << "������� �������� ����� ��� ����������!" << endl;
        return;
    }

    file.seekg(0, ios::end);
    int count = file.tellg() / sizeof(Note);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            Note note1, note2;

            file.seekg(j * sizeof(Note), ios::beg);
            file.read((char*)&note1, sizeof(Note));
            file.read((char*)&note2, sizeof(Note));

            if (strcmp(note1.phone, note2.phone) > 0) {
                file.seekp(j * sizeof(Note), ios::beg);
                file.write((char*)&note2, sizeof(Note));
                file.write((char*)&note1, sizeof(Note));
            }
        }
    }

    file.close();
    cout << "���������� ���������!" << endl;
}

void findNoteBySurname(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "������� �������� ����� ��� ������!" << endl;
        return;
    }

    string targetSurname;
    cout << "������ ������� ��� ������: ";
    cin >> targetSurname;

    Note person;
    bool found = false;

    while (file.read((char*)&person, sizeof(Note))) {
        if (targetSurname == person.surname) {
            cout << "�������: " << person.surname << endl;
            cout << "��'�: " << person.name << endl;
            cout << "�������: " << person.phone << endl;
            cout << "���� ����������: " << person.birthDate[0] << "."
                << person.birthDate[1] << "." << person.birthDate[2] << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "����� �� �������� \"" << targetSurname << "\" �� ��������." << endl;
    }

    file.close();
}

void displayAllNotes(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "������� �������� ����� ��� ��������� �����!" << endl;
        return;
    }

    Note person;
    int index = 1;
    cout << "\n��� � ���� \"" << filename << "\":\n";
    cout << "=================================\n";

    while (file.read((char*)&person, sizeof(Note))) {
        cout << "����� #" << index++ << ":\n";
        cout << "  �������: " << person.surname << endl;
        cout << "  ��'�: " << person.name << endl;
        cout << "  �������: " << person.phone << endl;
        cout << "  ���� ����������: " << person.birthDate[0] << "."
            << person.birthDate[1] << "." << person.birthDate[2] << endl;
        cout << "---------------------------------\n";
    }

    if (index == 1) {
        cout << "���� ������� ��� �� ������ ������� ������.\n";
    }

    file.close();
}

void menu() {
    string filename;
    cout << "������ ��'� �����: ";
    cin >> filename;

    char choice;
    do {
        cout << "\n����:\n";
        cout << "[1] - ������ ����� � ����\n";
        cout << "[2] - ��������� ������ �� ������� ��������\n";
        cout << "[3] - ����� �� ��������\n";
        cout << "[4] - �������� ��� ������ � ����\n";
        cout << "[0] - �����\n";
        cout << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case '1':
            addNoteToFile(filename);
            break;
        case '2':
            sortNotesInFile(filename);
            break;
        case '3':
            findNoteBySurname(filename);
            break;
        case '4':
            displayAllNotes(filename);
            break;
        case '0':
            cout << "���������� ��������." << endl;
            break;
        default:
            cout << "������� ����! ��������� �� ���." << endl;
        }
    } while (choice != '0');
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu();
    return 0;
}
