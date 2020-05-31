#include<iostream>
#include "Booking_Events.cpp"
#include "open.cpp"


/**@file
@brief
Main file
*/
using namespace std;

int main()
{
	EventMangement em;
	Helper h1;
	Open o;
string input;
	do
	{
		cout << "CHOOSE THE OPTION YOU WANT\n";
		cout << "1.ADD AN EVENT\n" << "2.CHECK FREE SEATS\n" << "3.BOOK A SEAT\n" << "4.UNBOOK A SEAT\n" << "5.BUY SEATS\n";
		cout << "6.CHECK ALL BOOKINGS\n" << "7.SHOW REPORT\n" << "8. EXIT\n";
		
		getline(cin, input);
		
		int option = h1.strToInt(input);
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
			em.bookings();
		}
		else if (option == 7)
		{
			em.report();
		}
		else if (option == 8) {
			break;
		}
		else if (h1.compareStr(h1.firstWord(input), "open") == 0) {
			o.openF(input);
		}
		else if (input == "exit") {
			exit(0);
		}
		cin.ignore();
	} while (1);
	return 0;
}