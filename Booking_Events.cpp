#include<iostream>
#include<math.h>
#include<iomanip>
#include<time.h>
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
		cout << "Give me the date(in dd/mm/yy format) and hall and the name of the event to be created" << endl;
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
		cout << "Give the correct name and date(format dd/mm/yy) of the event to check if either available in the system\n";
		cin >> name;
		cin >> date;
		fstream check("BookTickets.txt");
		bool found = false;
		if (!check.good())
		{
			cout << "There is not a single event in the system to add an event use addevent option\n";
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
	void book()
	{
		string rows, seat, date, name;
		cout << "Give the correct name and date(format dd/mm/yy) of the event to check if either available in the system\n";
		cin >> name;
		cin >> date;
		string lines[100] = { "" };
		string bookinginfo = "";
		fstream check("BookTickets.txt", fstream::in);
		int i = 0;
		bool found = false;
		if (!check.good())
		{
			cout << "There is not a single event in the system to add an event use addevent option\n";
			check.close();
		}
		else
		{
			while (!check.eof())
			{
				string line = "";
				getline(check, line);
				string check_hall = line;
				string del = ",";
				string event_name = check_hall.substr(0, check_hall.find(","));
				check_hall.erase(0, check_hall.find(del) + 1);
				string event_date = check_hall.substr(0, check_hall.find(","));
				if (name == event_name && date == event_date)
				{
					string row = "";
					string seat = "";
					cout << "Choose row number from 1-5" << endl;
					cin >> row;
					if (stoi(row) < 0 || stoi(row) > 5)
					{
						cout << "This row doesn't exist";
						return;

					}

					else
					{
						found = true;
						cout << "Choose seat number from 0-6\n";
						cin >> seat;
						if (stoi(seat) < 0 || stoi(seat) > 6)
						{
							cout << "Wrong Seat Number";
							return;
						}
						/*	int startingseat = line.find("R" + row)+2;
							int lastseat = line.find(line.find("R" + row), line.find(" "));	*/
						string row_number = "R" + row;

						string whole_row = line.substr(line.find(row_number) + 2, 8);
						if (whole_row[stoi(seat)] == '1')
						{
							cout << "Sorry already booked or bought\n";
						}
						else if (whole_row[stoi(seat)] == '0')
						{
							whole_row[stoi(seat)] = '1';
							cout << "Ticket Booked\n";
							string new_row = row_number + whole_row;
							line.replace(line.find(row_number), new_row.length(), new_row);
							bookinginfo = "Row" + row + "," + "Seat" + seat + "," + name + "," + date + "," + "TICKET BOOKED UNTILL TOMORROW";
						}
					}



				}
				lines[i] = line;
				i++;
			}
			check.close();


			if (found == false)
			{
				cout << "There is no such event.";
			}
			else
			{
				int count = 0;
				if (lines[count] != "")
				{
					ofstream out("Booktickets.txt");
					while (lines[count] != "")
					{
						out << lines[count] << endl;
						count++;
					}
					out.close();
				}
				if (bookinginfo != "")
				{
					fstream book("BookedTickets.txt", fstream::out | fstream::app);
					book << bookinginfo << endl;
					book.close();
				}
			}
		}
	}
	void unbook()
	{

		string rows, seat, date, name;
		cout << "Give the correct name and date(format dd/mm/yy) of the event to Unbook your ticket\n";
		cin >> name;
		cin >> date;
		string lines[100] = { "" };
		string booked[100] = { "" };
		fstream check("BookTickets.txt", fstream::in);
		fstream tickets("BookedTickets.txt", fstream::in);
		ofstream ostrm("BookedTickets1.txt");
		int i = 0;
		int count = 0;
		bool found = false;
		if (!tickets.good())
		{
			cout << "There are no booked tickets yet." << endl;
			tickets.close();
			check.close();
			return;
		}
		else
		{
			string row, seat;
			cout << "Row number from 1-5" << endl;
			cin >> row;
			if (stoi(row) < 1 || stoi(row) > 5)
			{
				cout << "Wrong Row number , this doesn't exist";
				return;

			}
			cout << "Seat number from 0-6\n";
			cin >> seat;
			if (stoi(seat) < 0 || stoi(row) > 6)
			{
				cout << "Wrong Seat number , this doesn't exist";
				return;
			}

			while (!check.eof())
			{
				string line = "";
				getline(check, line);
				string check_hall = line;
				string del = ",";
				string event_name = check_hall.substr(0, check_hall.find(","));
				check_hall.erase(0, check_hall.find(del) + 1);
				string event_date = check_hall.substr(0, check_hall.find(","));
				if (name == event_name && date == event_date)
				{

					found = true;

					/*	int startingseat = line.find("R" + row)+2;
					int lastseat = line.find(line.find("R" + row), line.find(" "));	*/
					string row_number = "R" + row;

					string whole_row = line.substr(line.find(row_number) + 2, 8);
					if (whole_row[stoi(seat)] == '0')
					{
						cout << "Seat not unbooked\n";
					}
					else if (whole_row[stoi(seat)] == '1')
					{
						whole_row[stoi(seat)] = '0';
						cout << "Ticket Unbooked\n";
						string new_row = row_number + whole_row;
						line.replace(line.find(row_number), new_row.length(), new_row);

					}



				}
				lines[i] = line;
				i++;

			}
			string res_row = "Row" + row;
			string res_seat = "Seat" + seat;
			while (!tickets.eof())
			{

				string tick;
				getline(tickets, tick);
				string del = ",";
				string chek_tick = tick;
				string check_row = tick.substr(0, tick.find(","));
				chek_tick.erase(0, chek_tick.find(del) + del.length());
				string check_seat = chek_tick.substr(0, chek_tick.find(","));
				if (res_row != check_row || res_seat != check_seat)
				{
					ostrm << tick << endl;
					booked[count] = tick;
					count++;
				}
			}
			check.close();
			tickets.close();
			ostrm.close();
			if (remove("BookedTickets.txt") != 0) {
				cout << "Cant delete file." << endl;
			}
			if (rename("BookedTickets1.txt", "BookedTickets.txt") != 0) {
				cout << "Cant rename files." << endl;
			}
			if (found == false)
			{
				cout << "No such event ever made in the system";
				return;
			}
			else
			{


				int count = 0;
				if (lines[count] != "")
				{
					ofstream out("BookTickets.txt");
					while (lines[count] != "")
					{
						out << lines[count] << endl;
						count++;
					}
					out.close();
				}

				count = 0;
				if (booked[count] != "")
				{
					ofstream tickets("BookedTickets.txt");
					while (booked[count] != "")
					{
						tickets << booked[count] << endl;
						count++;
					}
					tickets.close();
				}
			}
		}

	}
	void buy()
	{
		string row, seat, date, name;
		cout << "Give the correct name and date(format dd/mm/yy) of the event to Buy those tickets\n";
		cin >> name;
		cin >> date;

		string lines[100] = { "" };
		string soldticket = "";
		fstream check("BookTickets.txt");
		ifstream ifstrm("BookedTickets.txt");
		ofstream ostrm("BookedTickets1.txt");
		int i = 0;
		bool found = false;
		if (!check.good())
		{
			cout << "There is not a single event in the system to add an event use addevent option\n";
			check.close();
		}
		else
		{
			while (!check.eof())
			{
				string line = "";
				getline(check, line);
				string check_hall = line;
				string del = ",";
				string event_name = check_hall.substr(0, check_hall.find(","));
				check_hall.erase(0, check_hall.find(del) + 1);
				string event_date = check_hall.substr(0, check_hall.find(","));
				if (name == event_name && date == event_date)
				{


					cout << "Рow number from 1-5" << endl;
					cin >> row;
					if (stoi(row) < 0 || stoi(row) > 5)
					{
						cout << "Wrong Row number , this doesn't exist";
						return;
					}

					else
					{
						found = true;
						cout << "Give me the Seat number from 0-6\n";
						cin >> seat;
						if (stoi(seat) < 0 || stoi(seat) > 6)
						{
							cout << "Wrong Seat number , this doesn't exist";
							return;
						}
						/*	int startingseat = line.find("R" + row)+2;
						int lastseat = line.find(line.find("R" + row), line.find(" "));	*/
						string row_number = "R" + row;

						string whole_row = line.substr(line.find(row_number) + 2, 8);
						if (whole_row[stoi(seat)] == '0')
						{
							cout << "Sorry First Book your Ticket\n";
						}
						else if (whole_row[stoi(seat)] == '1')
						{
							whole_row[stoi(seat)] = '2';
							cout << "Ticket Sold\n";
							string new_row = row_number + whole_row;
							line.replace(line.find(row_number), new_row.length(), new_row);
							soldticket = "R" + row + "," + "S" + seat + "," + name + "," + date + "\n";
						}

					}

				}
				lines[i] = line;
				i++;

			}
			string res_row = "Row" + row;
			string res_seat = "Seat" + seat;
			while (!ifstrm.eof()) {
				string tick;
				getline(ifstrm, tick);
				string del = ",";
				string chek_tick = tick;
				string check_row = tick.substr(0, tick.find(","));
				chek_tick.erase(0, chek_tick.find(del) + del.length());
				string check_seat = chek_tick.substr(0, chek_tick.find(","));
				if (res_row != check_row || res_seat != check_seat)
				{
					ostrm << tick << endl;
				}
			}

			check.close();
			ostrm.close();
			ifstrm.close();
			if (remove("BookedTickets.txt") != 0) {
				cout << "Cant delete file." << endl;
			}
			if (rename("BookedTickets1.txt", "BookedTickets.txt") != 0) {
				cout << "Cant rename files." << endl;
			}
			if (found == false)
			{
				cout << "No such event" << endl;
			}
			else
			{

				if (soldticket != "")
				{
					fstream buy("SOLD_TICKETS.txt", fstream::out | fstream::app);
					buy << soldticket;
					buy.close();
				}

				int count = 0;
				if (lines[count] != "")
				{
					ofstream update("BookTickets.txt");

					while (lines[count] != "")
					{
						update << lines[count] << endl;
						count++;
					}
					update.close();
				}
			}
		}
	}