#include<iostream>
#include<sstream>
#include "Booking_Events.cpp"
#include<algorithm>
#include<stdio.h>
#include<string>
#include<stdlib.h>
using namespace std;
string lines[100];
bool compareStr(string str, const char* ch) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	const char* compArr = str.c_str();
	return strcmp(ch, compArr);
}
string removeFirstWord(string str) {
	return str.substr(str.find_first_of(" \t") + 1);
}
string firstWord(string str)
{
	string saveAs = "save as";
	string word = "", word2 = "";
	for (auto x : str)
	{
		if (x == ' ' || x == '*')
		{
			if (compareStr(word, "save") == 0) {
				string secondW = removeFirstWord(str);
				for (char y : secondW)
				{
					if (y == ' ')
					{
						if (compareStr(word2, "as") == 0) {
							return saveAs;
						}
					}
					else
					{
						word2 = word2 + y;

					}
				}
			}
			if (compareStr(word2, "as") == 0) {
				return saveAs;
			}
			else {
				return word;

			}
		}
		else
		{
			word = word + x;
		}
	}
	return word;
}

int strToInt(string str) {
	int result = 0;
	for (auto x : str) {
		if (x == '*') {
			break;
		}
		else if (x >= '0' && x <= '9') {
			result = 10 * result + (x - '0');
		}
		else {
			return NULL;
		}
	}
	return result;
}
void openF(string str) {
	str = removeFirstWord(str);
	cout << endl << str << endl;
	string fileName = firstWord(str);
	fstream myS;
	cout << fileName << endl;
	string line;
	int i = 0;
	myS.open(fileName);
	while (!myS.eof()) {
		getline(myS, line);
		lines[i] = line;
		cout << i + 1 << ". " << lines[i] << endl;
		i++;
	}
	myS.close();
	cout << "1. remove a line\n 2. change a line\n 3. insert a line\n Anything else = exit open function.\n";
	string inp;
	int addcounter = 0;
	do {
		getline(cin, inp);
		int ins = strToInt(inp);
		if (ins == 1) {
			int nrLine;
			cout << "Enter the number of the line you want to remove.\n";
			cin >> nrLine;
			lines[nrLine - 1] = "";
		}
		else if (ins == 2) {
			int nrLine;
			cout << "Enter the number of the line you want to change.\n";
			cin >> nrLine;
			string change;
			cout << "Type the new line.\n";
			cin.ignore();
			getline(cin, change);
			cout << change << endl;
			lines[nrLine - 1] = change;
		}
		else if (ins == 3) {
			addcounter++;
			cout << "Enter the number of the line you want to insert after.\n";
			int nrLine;
			cin >> nrLine;
			if (nrLine > i + 1) {
				return;
			}
			string addline;
			cout << "Enter your line: ";
			cin.ignore();
			getline(cin, addline);
			cout << "asd " << addline << " asd" << endl;
			for (int j = 0; j < i - nrLine + 1; j++) {
				lines[i - j + 1] = lines[i - j];
				cout << lines[j];
			}
			lines[nrLine] = addline;
		}
		else if (compareStr(firstWord(inp), "close") == 0) {
			for (int o = 0; o < 100; o++) {
				lines[o] = "";
				system("CLS");
				cout << "\nUse open again to access files.\n";
				return;
			}
		}
		else if (compareStr(firstWord(inp), "save") == 0) {
			myS.open("temp.txt", ios::out | ios::app);
			for (int k = 0; k < i + addcounter; k++) {
				int l = 0;
				if (lines[k] == "") {
					l++;
					continue;
				}
				lines[k - l] = lines[k];
				myS << lines[k] << endl;
			}
			myS.close();
			if (remove(fileName.c_str()) != 0) {
				cout << "Can't remove file.\n";
			}
			if (rename("temp.txt", fileName.c_str()) != 0) {
				cout << "Can't rename file.\n";

			}
		}
		else if (compareStr(firstWord(inp), "save as") == 0) {
			cout << "\n save as \n";
			string inp1 = removeFirstWord(removeFirstWord(inp));
			myS.open(inp1, ios::out | ios::app);
			for (int k = 0; k < +addcounter; k++) {
				int l = 0;
				if (lines[k] == "") {
					l++;
					continue;
				}
				lines[k - l] = lines[k];
				myS << lines[k] << endl;
			}
			myS.close();
		}
		else if (compareStr(firstWord(inp), "help") == 0) {
			system("CLS");
			cout << "\n open <file>	opens <file> \nclose			closes currently opened file \nsave			saves the currently open file\nsave as <file>	saves the currently open file in <file> \nhelp			prints this information";
		}
		else if (compareStr(firstWord(inp), "exit") == 0) {
			exit(0);
		}
	} while (true);

}
int main()
{
	EventMangement em;

	while (1)
	{
		cout << "CHOOSE THE OPTION YOU WANT\n";
		cout << "1.ADD AN EVENT\n" << "2.CHECK FREE SEATS\n" << "3.BOOK A SEAT\n" << "4.UNBOOK A SEAT\n" << "5.BUY SEATS\n";
		cout << "6.CHECK ALL BOOKINGS\n" << "7.SHOW REPORT\n" << "8. EXIT\n";
		string input;
		getline(cin, input);
		int option = strToInt(input);
		if (option == 1)
		{
			em.addevent();
		}
		else if (option == 2)
		{

			em.freeseats();
		}
		else if (option == 3)
		{
			em.book();
		}
		else if (option == 4)
		{
			em.unbook();
		}
		else if (option == 5)
		{
			em.buy();
		}
		else if (option == 6)
		{
			//em.bookings();
		}
		else if (option == 7)
		{
			//em.report();
		}
		else if (option == 8) {
			break;
		}
		else if (compareStr(firstWord(input), "open") == 0) {
			openF(input);
		}
		else if (input == "exit") {
			exit(0);
		}
		else {
			cout << "Invalid input. Press 1-8.\n";
			continue;
		}

	}
	return 0;
}