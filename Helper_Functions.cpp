#include<iostream>
#include<sstream>
#include<algorithm>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<fstream>
using namespace std;
/**@file
@brief
Helper Functions file*/
class Helper {
	/**Class for all the side functions I made to help me with the main ones*/
public:
	bool compareStr(string str, const char* ch)
		/**custom strcmp() to compare a string to a keyword because I had problems with strcmp()*/
	{
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		const char* compArr = str.c_str();
		return strcmp(ch, compArr);
	}
	string removeFirstWord(string str)
		/**removes the first word of a string (until it meets a whitespace) and returns the rest of the string */
	{
		return str.substr(str.find_first_of(" \t") + 1);
	}
	string firstWord(string str)
		/**returns only the first word of a string*/
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

	int strToInt(string str)
		/**custom stoi() because again, I had problems with it. Converts the string into an int if it's a number. */
	{
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
	//void openF(string str)
	//	/**the open/edit(insert line, edit line, delete line), close, save, save as commands work through this function. */
	//{
	//	str = removeFirstWord(str);
	//	cout << endl << str << endl;
	//	string fileName = firstWord(str);
	//	fstream myS;
	//	string line;
	//	int i = 0;
	//	myS.open(fileName);
	//	while (!myS.eof()) {
	//		getline(myS, line);
	//		lines[i] = line;
	//		cout << i + 1 << ". " << lines[i] << endl;
	//		i++;
	//	}
	//	myS.close();

	//	string inp;
	//	int addcounter = 0;
	//	cout << "1. remove a line\n 2. change a line\n 3. insert a line\n Close = exit open function.\n";
	//	do {


	//		getline(cin, inp);
	//		int ins = strToInt(inp);
	//		if (ins == 1) {
	//			int nrLine;
	//			cout << "Enter the number of the line you want to remove.\n";
	//			cin >> nrLine;
	//			lines[nrLine - 1] = "";
	//		}
	//		else if (ins == 2) {
	//			int nrLine;
	//			cout << "Enter the number of the line you want to change.\n";
	//			cin >> nrLine;
	//			string change;
	//			cout << "Type the new line.\n";
	//			cin.ignore();
	//			getline(cin, change);
	//			cout << change << endl;
	//			lines[nrLine - 1] = change;
	//		}
	//		else if (ins == 3) {
	//			addcounter++;
	//			cout << "Enter the number of the line you want to insert after.\n";
	//			int nrLine;
	//			cin >> nrLine;
	//			if (nrLine > i + 1) {
	//				return;
	//			}
	//			string addline;
	//			cout << "Enter your line: ";
	//			cin.ignore();
	//			getline(cin, addline);
	//			for (int j = 0; j < i - nrLine + 1; j++) {
	//				lines[i - j + 1] = lines[i - j];
	//			}
	//			lines[nrLine] = addline;
	//		}
	//		else if (compareStr(firstWord(inp), "close") == 0) {
	//			for (int o = 0; o < 100; o++) {
	//				lines[o] = "";
	//				system("CLS");
	//				cout << "\nUse open again to access files.\n";
	//				return;
	//			}
	//		}
	//		else if (compareStr(firstWord(inp), "save") == 0) {
	//			myS.open("temp.txt", ios::out | ios::app);
	//			for (int k = 0; k < i + addcounter; k++) {
	//				int l = 0;
	//				if (lines[k] == "") {
	//					l++;
	//					continue;
	//				}
	//				lines[k - l] = lines[k];
	//				myS << lines[k] << endl;
	//			}
	//			myS.close();
	//			if (remove(fileName.c_str()) != 0) {
	//				cout << "Can't remove file.\n";
	//			}
	//			if (rename("temp.txt", fileName.c_str()) != 0) {
	//				cout << "Can't rename file.\n";

	//			}
	//		}
	//		else if (compareStr(firstWord(inp), "save as") == 0) {
	//			cout << "\n save as \n";
	//			string inp1 = removeFirstWord(removeFirstWord(inp));
	//			myS.open(inp1, ios::out | ios::app);
	//			for (int k = 0; k < i + addcounter; k++) {
	//				int l = 0;
	//				if (lines[k] == "") {
	//					l++;
	//					continue;
	//				}
	//				lines[k - l] = lines[k];
	//				myS << lines[k] << endl;
	//			}
	//			myS.close();
	//		}
	//		else if (compareStr(firstWord(inp), "help") == 0) {
	//			system("CLS");
	//			cout << "\n open <file>	opens <file> \nclose			closes currently opened file \nsave			saves the currently open file\nsave as <file>	saves the currently open file in <file> \nhelp			prints this information";
	//		}
	//		else if (compareStr(firstWord(inp), "exit") == 0) {
	//			exit(0);
	//		}
	//	} while (true);

	//}
};