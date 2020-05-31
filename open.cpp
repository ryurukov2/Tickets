#include "Helper_Functions.cpp"
/**@file
@brief
file for the "open, close, save, save as, exit commands*/

static Helper h;
class Open{
	/**Another helper class just for the open/edit.close,save,save as commands*/
public:
	/**storing the lines of the file*/
	string lines[100];
void openF(string str)
/**the open/edit(insert line, edit line, delete line), close, save, save as commands work through this function. */
{

	str = h.removeFirstWord(str);
	cout << endl << str << endl;
	string fileName = h.firstWord(str);
	fstream myS;
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

	string inp;
	int addcounter = 0;
	cout << "1. remove a line\n 2. change a line\n 3. insert a line\n Close = exit open function.\n";
	do {


		getline(cin, inp);
		int ins = h.strToInt(inp);
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
			for (int j = 0; j < i - nrLine + 1; j++) {
				lines[i - j + 1] = lines[i - j];
			}
			lines[nrLine] = addline;
		}
		else if (h.compareStr(h.firstWord(inp), "close") == 0) {
			for (int o = 0; o < 100; o++) {
				lines[o] = "";
				system("CLS");
				cout << "\nUse open again to access files.\n";
				return;
			}
		}
		else if (h.compareStr(h.firstWord(inp), "save") == 0) {
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
		else if (h.compareStr(h.firstWord(inp), "save as") == 0) {
			string inp1 = h.removeFirstWord(h.removeFirstWord(inp));
			myS.open(inp1, ios::out | ios::app);
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
		}
		else if (h.compareStr(h.firstWord(inp), "help") == 0) {
			system("CLS");
			cout << "\n open <file>	opens <file> \nclose			closes currently opened file \nsave			saves the currently open file\nsave as <file>	saves the currently open file in <file> \nhelp			prints this information";
		}
		else if (h.compareStr(h.firstWord(inp), "exit") == 0) {
			exit(0);
		}
	} while (true);

}
};