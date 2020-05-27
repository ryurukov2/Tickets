#include<iostream>
#include<string>
#include<fstream>



#define capacity "R10000000 R20000000 R30000000 R40000000 R50000000"
using namespace std;
class EventMangement
{


public:
	EventMangement()
	{

	}
	void addevent()

	{
		string date = "";
		string hall = "";
		string event_name = "";
		cout << "Give me the date(in yyyy/mm/dd format) and hall and the name of the event to be created" << endl;
		cin >> date;
		cin >> hall;
		cin >> event_name;
		ifstream is("Events.txt");
		if (!is.good())
		{

			ofstream out("Events.txt");
			ofstream newEvent("BookTickets.txt");
			string line;
			cout << "No such file Creating one\n";

			line = date + "," + hall + "," + event_name;
			//newEvent << "\n" << event_name << " " << date << " " << capacity;


			//cout << line;
			out << line;
			line = event_name + "," + date + "," + capacity;
			newEvent << line;
			newEvent.close();
			out.close();
			is.close();
		}
		else
		{

			string line = "";

			int count = 0;
			while (!is.eof())
			{
				getline(is, line);

				if (line.find(hall) != string::npos && line.find(date) != string::npos)
				{
					cout << "This hall is booked for that day" << endl;
					count = 1;
					break;
				}
				if (line.find(event_name) != string::npos && line.find(date) != string::npos) {
					cout << "Artist is busy that day" << endl;
					count = 1;
					break;
				}
			}
			if (count == 0)
			{
				ofstream out("Events.txt", ios::app);

				line = "\n" + date + "," + hall + "," + event_name;
				cout << endl << line << endl;
				out << line;
				ofstream newEvent("BookTickets.txt", ofstream::out | ofstream::app);
				line = "\n" + event_name + "," + date + "," + capacity;
				newEvent << line;
				cout << "New Line added" << endl;
				newEvent.close();
				out.close();
			}
			is.close();

		}

	}
	void freeseats()
	{
		string date, name;
		cout << "Give the correct name and date(format yyyy/mm/dd) of the event to check if either available in the system\n";
		cin >> name;
		cin >> date;
		fstream check("BookTickets.txt");
		bool found = false;
		if (!check.good())
		{
			cout << "There arent any events.\n";
			check.close();
		}
		else
		{
			while (!check.eof())
			{
				string line = "";
				getline(check, line);
				if (line.find(name) != string::npos && line.find(date) != string::npos)
				{
					found = true;
					for (int i = 1; i <= 5; i++)
					{
						cout << "Row " << i << ": ";
						string row_number = "R" + to_string(i);
						string rowSeats = line.substr(line.find(row_number) + 2, 8);
						for (int seats = 0; seats < 7; seats++)
						{
							if (rowSeats[seats] == '0')
							{
								cout << "SeatNo: " << seats << "   ";
							}
						}
						cout << endl;
					}
				}
				else
				{
					continue;
				}
			}
			check.close();
			if (found == false)
			{
				cout << "There is no such event occuring on that date.\n";
			}
		}
	}