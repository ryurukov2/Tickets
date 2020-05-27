#include<iostream>

int main()
{

	while (1)
	{
		cout << "CHOOSE THE OPTION YOU WANT";
		cout << "1.ADD AN EVENT\n" << "2.CHECK FREE SEATS\n" << "3.BOOK A SEAT\n" << "4.UNBOOK A SEAT\n" << "5.BUY SEATS\n";
		cout << "6.CHECK ALL BOOKINGS\n" << "7.SHOW REPORT\n";
		int option = 0;
		std::cin >> option;
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
		else {
			cout << "Invalid input. Press 1-8.\n";
			continue;
		}

	}
	return 0;
}