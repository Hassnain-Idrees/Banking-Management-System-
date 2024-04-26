#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<conio.h>
#include<sstream>
using namespace std;

class customer {
public:
	string login_id;
	string password;
public:
	customer()
	{
		login_id = "";
		password = "";
	} 
	customer(string id, string pass)
	{
		login_id = id;
		password = pass;
	}
	virtual bool login()
	{
		return true;
	} 
	virtual	void load_data()
	{}
};
class Transaction
{
public:
	int id;
	int day;
	int mon;
	int year;
	string type;
	int transfer_id;
	long long amount;
	Transaction(int ID = 0, int d = 0, int y = 0, int m = 0, string t = "", int t_id = 0, long long am = 0)
	{
		id = ID;
		day = d;
		mon = m;
		year = y;
		type = t;
		transfer_id = t_id;
		amount = am;
	}
};
class card
{
public:
	long long card_num;
	int pin;
	int serial;
public:
	card(long long card_n = 0, int p = 0,int s=0)
	{
		card_num = card_n;
		pin = p;
		serial = s;
	}
	void generate_num()
	{
		srand(time(0));
		for (int i = 0; i < 16; i++)
		{
			int d = rand() % 10;
			card_num = (card_num * 10) + d;
		}
	}
};
class User :public customer
{
public:
	int user_id;
	string name;
	string address;
	long long phone;
	long long cnic;
	int balance;
	long long withdrawal_limit;
	card card_detail;
	int pin_check;
	Transaction trans;
public:
	User(string login_id = "", string password = "",int id=0, string n = "", string add = "", long long ph = 0, long long CNIC = 0, int bal = 0, long long limit = 0, long long card_n = 0, int pin = 0,int pin_c = 3) :customer(login_id, password)
	{
		user_id = id;
		name = n;
		address = add;
		phone = ph;
		cnic = CNIC;
		balance = bal;
		withdrawal_limit = limit;
		pin_check = pin_c;
	}
	void load_data(User*& arr )   // for loading data from user.txt
	{
		ifstream file;
		file.open("User\\user.txt");
		int count = 0;
		string a,b;
		while (getline(file, b))
		{
			count++;
		}
		file.close();
		arr = new User[count];
		file.open("User\\user.txt");
		for (int i = 0; i < count; i++)
		{
			getline(file, a, ',');
			arr[i].user_id = stoi(a);
			getline(file, a, ',');
			arr[i].name = a;
			getline(file, a, ',');
			arr[i].address = a;
			getline(file, a, ',');
			arr[i].cnic = stoll(a);
			getline(file, a, ',');
			arr[i].login_id = a;
			getline(file, a, ',');
			arr[i].password = a;
			getline(file, a, ',');
			arr[i].withdrawal_limit = stoll(a);
			getline(file, a, ',');
			arr[i].pin_check = stoi(a);
			getline(file, a, '\n');
			arr[i].balance = stoi(a);
		}
		file.close();
	}
	bool login(User* arr, string id, string pass)
	{
		bool check = true;
		string a;
		ifstream f1;
		f1.open("User\\user.txt");
		int size_arr = 0;
		while (getline(f1, a))
		{
			size_arr++;
		}		
		f1.close();
		for (int i = 0; i < size_arr; i++)
		{
			if (arr[i].login_id == id)
			{
				if (arr[i].password == pass)
				{				
					check = false;
					return true;
				}
				else
				{
					cout << "\t******** ID and Password Does not match *********\n";				
					check = false;
					return false;
				}
			}		
		}
		if (check)
		{
			cout << "\t******* No user found ********\n";
			return false;
		}
	}
	void account_block(User*&arr ,int z)
	{
		ifstream read;
		read.open("User\\user.txt");
		string a;
		int count = 0;
		while (getline(read, a))
		{
			count++;
		}
		read.close();
		User* temp = new User[count - 1];
		for (int i = 0,k=0; i < count; i++)
		{
			if (i == z)
			{
				continue;
			}
			else
			{
				temp[k].user_id = arr[i].user_id;
				temp[k].name = arr[i].name;
				temp[k].address = arr[i].address;
				temp[k].cnic = arr[i].cnic;
				temp[k].login_id = arr[i].login_id;
				temp[k].password = arr[i].password;
				temp[k].withdrawal_limit = arr[i].withdrawal_limit;
				temp[k].pin_check = arr[i].pin_check;
				temp[k].balance = arr[i].balance;
				k++;
			}
		}
		ofstream write;
		write.open("User\\user.txt");
		for (int k = 0; k < count-1; k++)
		{
			write << temp[k].user_id << ",";
			write << temp[k].name << ",";
			write << temp[k].address << ",";
			write << temp[k].cnic << ",";
			write << temp[k].login_id << ",";
			write << temp[k].password << ",";
			write << temp[k].withdrawal_limit << ",";
			write << temp[k].pin_check << ",";
			write << temp[k].balance << "\n";
		}
		write.close();
		ofstream fraud;
		fraud.open("Bank\\user_blocked.txt",ios::app);	
			fraud << arr[z].user_id << ",";
			fraud << arr[z].name << ",";
			fraud << arr[z].address << ",";
			fraud << arr[z].cnic << ",";
			fraud << arr[z].login_id << ",";
			fraud << arr[z].password << ",";
			fraud << arr[z].withdrawal_limit << ",";
			fraud << arr[z].pin_check << ",";
			fraud << arr[z].balance << "\n";		
		fraud.close();
	}
	void save_data(User*& arr, int i)
	{
		ifstream read;
		read.open("User\\user.txt");
		string a;
		int count = 0;
		while (getline(read, a))
		{
			count++;
		}
		read.close();
		bool check = false;
		// if and else for modifying code for use in deposit money
		for (int j = 0; j < count; j++)
		{
			if (arr[j].user_id == arr[i].user_id)
			{
				if (arr[j].login_id == arr[i].login_id)
				{
					arr[j].pin_check = 3;
					arr[j].balance = arr[i].balance;
					check = true;
				}
			}		
		}
		if (check)
		{
			ofstream write;
			write.open("User\\user.txt");
			for (int k = 0; k < count; k++)
			{
				write << arr[k].user_id << ",";
				write << arr[k].name << ",";
				write << arr[k].address << ",";
				write << arr[k].cnic << ",";
				write << arr[k].login_id << ",";
				write << arr[k].password << ",";
				write << arr[k].withdrawal_limit << ",";
				write << arr[k].pin_check << ",";
				write << arr[k].balance << "\n";
			}
			write.close();
		}
		else
		{
			arr[i].user_id = count + 1;  //serial number
			ofstream write;
			write.open("User\\user.txt",ios::app);
			write << arr[i].user_id << ",";
			write << arr[i].name << ",";
			write << arr[i].address << ",";
			write << arr[i].cnic << ",";
			write << arr[i].login_id << ",";
			write << arr[i].password << ",";
			write << arr[i].withdrawal_limit << ",";
			write << arr[i].pin_check << ",";
			write << arr[i].balance << "\n";
			write.close();
		}
	}
	void save_new_data(User*& arr, int i)
	{
		ifstream read;
		read.open("User\\user.txt");
		string a;
		int count = 0;
		while (getline(read, a))
		{
			count++;
		}
		read.close();
	
			arr[i].user_id = count + 1;  //serial number
			ofstream write;
			write.open("User\\user.txt", ios::app);
			write << arr[i].user_id << ",";
			write << arr[i].name << ",";
			write << arr[i].address << ",";
			write << arr[i].cnic << ",";
			write << arr[i].login_id << ",";
			write << arr[i].password << ",";
			write << arr[i].withdrawal_limit << ",";
			write << arr[i].pin_check << ",";
			write << arr[i].balance << "\n";
			write.close();
	}
	void sign_up()
	{
		ifstream file;
		file.open("User\\user.txt");
		string temp;
		int serial = 1;
		while (getline(file, temp))
		{
			serial++;
		}
		file.close();
		user_id = serial;
		cout << "\tPlease enter your full name   e.g. Ali Ahmad " << endl;
		cin.ignore();
		getline(cin, name);
		cout << "\tPlease enter your user name   e.g. ali_ahmed786" << endl;
		getline(cin, login_id);
		cout << "\tPlease enter your password  " << endl;
		getline(cin, password);
		bool flag = false;
		while (!flag)
		{
			int count = 0;
			cout << "\tPlease enter your 13 digit cnic  (without dashes) " << endl;
			string cn;
			getline(cin, cn);
			for (int i = 0; cn[i] != '\0'; i++)
			{
				count++;
				if (int(cn[i]) < 48 || int(cn[i]) > 57) {
					flag = true;
				}

			}
			if (count != 13 || flag == true)
			{
				cout << "\n\tInvalid CNIC number (it must contain 13 digits and should be numeric only)! \n";;
				flag = false;
			}
			else
			{
				cnic = stoll(cn);
				flag = true;
			}
		}
		cout << "\tPlease enter your address " << endl;
		getline(cin, address);
		bool flag1 = false;
		while (!flag1)
		{
			int count = 0;
			cout << "\tPlease enter your 11 digit phone number " << endl;
			string p;
			getline(cin, p);
			for (int i = 0; p[i] != '\0'; i++)
			{
				count++;
				if (int(p[i]) < 48 || int(p[i]) > 57) {
					flag1 = true;
				}
			}
			if (count != 11 || flag1 == true)
			{
				cout << "\n\tInvalid Phone number (it must contain 11 digits and should be numeric only)! \n";;
				flag1 = false;
			}
			else
			{
				phone = stoll(p);
				flag1 = true;
			}
		}
		bool l_c = false;
		do {
			cout << "\tPlease select your estimated daily withdrwal limit " << endl;
			cout << "\n\t\t1 for  100,000 PKR      2 for  500,000 PKR   " << endl;
			char l;
			cin >> l;
			if (l == '1')
			{
				withdrawal_limit = 100000;
				l_c = false;
			}
			else if (l == '2')
			{
				withdrawal_limit = 500000;
				l_c = false;
			}		
			else 
			{
				cout << "\n\tPlease enter a valid choice ";
				l_c = true;
			}
		} while (l_c);
	}
	void  save_transaction(int user, int money, string type, int transfer_index)
	{
		ofstream save;
		save.open("Bank\\transactions.txt", ios::app);
		time_t now = time(0);
		struct tm localTime;
		localtime_s(&localTime, &now);
		int year = localTime.tm_year + 1900;
		int month = localTime.tm_mon + 1;     
		int day = localTime.tm_mday;
		if (transfer_index == 0)
		{
			save << day << "-" << month << "-" << year << ",";
			save << user << ",";
			save << money << ",";
			save << type << "\n";		
		}
		else
		{
			save << day << "-" << month << "-" << year << ",";
			save << user << ",";
			save << money << ",";
			save << type << ",";
			save << transfer_index << endl;
		}
		save.close();
	}
	void deposit_money(User*& arr, int i)
	{
		system("CLS");
		cout << "\n\t************ Deposit Money ***************\n\n";
		int money;	
		string pin;
		bool l_c = false;
		do {
			cout << "\n\tPlease enter your CARD's pin to confirm the deposit transaction \t";
			cin >> pin;
			istringstream iss(pin);
			int value;
			if (iss >> value)
			{
				if (stoi(pin) != arr[i].card_detail.pin)
				{
					cout << "\n\n\tPlease enter a valid pin number otherwise your account will be blocked\n\n ";
					arr[i].pin_check--;
					cout << "\n\t\t Your remaining TRY attemps is   =   " << arr[i].pin_check << endl;
					if (arr[i].pin_check == 0)
					{
						l_c = false;
						cout << "\n\n\t********** Sorry Your account has been blocked for security reasons ***********\n";
						account_block(arr, i);
						cout << "\n\n\n\n";
						exit(0);
					}
					else
					{
						l_c = true;
					}
				}
				else if (stoi(pin) == arr[i].card_detail.pin)
				{
					system("CLS");
					cout << "\n\t********  ACCESS GRANTED!!!! *********\n\n";
					cout << "Plese enter amount you want to deposit into your account\t";
					cin >> money;
					save_transaction(arr[i].user_id, money, "Deposit", 0);
					arr[i].balance += money;
					save_data(arr, i);
					l_c = false;
				}
			}
			else
			{
				cout << "\n\tPlease enter a valid PIN NUMBER \n";
				l_c = true;
			}
		} while (l_c);
	}
	void withdraw_money(User*&arr,int i)
	{
		system("CLS");
		cout << "\n\t************ Withdraw Money ***************\n\n";
		int money;
		string pin;
		bool l_c = false;
		do {
			cout << "\n\tPlease enter your CARD's pin to confirm the transaction \t";
			cin >> pin;
			istringstream iss(pin);
			int value;
			if (iss >> value)
			{
				if (stoi(pin) != arr[i].card_detail.pin)
				{
					cout << "\n\n\tPlease enter a valid pin number otherwise your account will be blocked\n\n ";
					arr[i].pin_check--;
					cout << "\n\t\t Your remaining TRY attemps is   =   " << arr[i].pin_check << endl;
					if (arr[i].pin_check == 0)
					{
						l_c = false;
						cout << "\n\n\t********** Sorry Your account has been blocked for security reasons ***********\n";
						account_block(arr, i);
						cout << "\n\n\n\n";
						break;
						exit(0);
						
					}
					else
					{
						l_c = true;
					}
				}
				else if (stoi(pin) == arr[i].card_detail.pin)
				{
					system("CLS");
					cout << "\n\t********  ACCESS GRANTED!!!! *********\n\n";
					bool c_check = false;
					do {
						cout << "\nPlese enter amount you want to withdraw from your account\t";
						cin >> money;						
						if (money>arr[i].withdrawal_limit )
						{
							cout << "\n\tDaily Withdrawal Limit exceeds\n\tEnter Amount Less than  your daily withdrawal limit i.e   " << arr[i].withdrawal_limit << endl;
							c_check = true;
						}
						else if ( money > arr[i].balance)
						{
							cout << "\n\tInsufficient Funds\n\tAccount Balance  is  " << arr[i].balance << endl;
							c_check = true;
						}
						else if (money > arr[i].withdrawal_limit && money > arr[i].balance)
						{
							cout << "\n\tInsufficient Funds    and   Daily Withdrawal limit is reached " << endl;
							cout << "\n\tPlease enter Amount with in limits \n";
							cout << "\tAccount Daily Withdrawal Limit           " << arr[i].withdrawal_limit << endl;
							cout << "\tAccount Balance            " << arr[i].balance << endl;

							c_check = true;
						}
						else
						{
							cout << "\n\t****** Moeny Withdrawing *******\n";
							save_transaction(arr[i].user_id, money, "Withdraw", 0);

							arr[i].balance -= money;
							arr[i].withdrawal_limit -= money;
							cout << "\tAccount Daily Withdrawal Limit           " << arr[i].withdrawal_limit << endl;
							cout << "\tAccount Balance            " << arr[i].balance << endl;
							c_check = false;
						}
					} while (c_check);				
					save_data(arr, i);
					l_c = false;
				}
			}
			else
			{
				cout << "\n\tPlease enter a valid PIN NUMBER \n";
				l_c = true;
			}
		} while (l_c);
	}
	void transfer_money(User*&arr,int i,int size_arr)
	{
		system("CLS");
		cout << "\n\t************ Transfer Money ***************\n\n";
		int money;
		string pin;
		bool l_c = false;
		do {
			cout << "\n\tPlease enter your CARD's pin to confirm the transaction \t";
			cin >> pin;
			istringstream iss(pin);
			int value;
			if (iss >> value)
			{
				if (stoi(pin) != arr[i].card_detail.pin)
				{
					cout << "\n\n\tPlease enter a valid pin number otherwise your account will be blocked\n\n ";
					arr[i].pin_check--;
					cout << "\n\t\t Your remaining TRY attemps is   =   " << arr[i].pin_check << endl;
					if (arr[i].pin_check == 0)
					{
						l_c = false;
						cout << "\n\n\t********** Sorry Your account has been blocked for security reasons ***********\n";
						account_block(arr, i);
						cout << "\n\n\n\n";
						exit(0);
					}
					else
					{
						l_c = true;
					}
				}
				else if (stoi(pin) == arr[i].card_detail.pin)
				{
					system("CLS");
					cout << "\n\t********  ACCESS GRANTED!!!! *********\n\n";
					int transfer_index;
					bool transfer_possible = false;
					bool t_check = false;
					do
					{
						cout << "\n\tPlease Enter The  User id number of the reciepient " << endl;
						string num;
						cin >> num;
						if (stoi(num) == arr[i].user_id)
						{
							cout << "\n\t******* You have entered your own user id *******\n";
							cout << "\n\t  You can't transfer funds to your own account \n";
							cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
							char a;
							cin >> a;
							if (a == '1')
							{
								t_check = true;
							}
							else
							{
								t_check = false;
							}
						}
						else if (stoi(num) > size_arr)
						{
							cout << "\n\tUser ID does not exist \n";
							cout << "\n\tPress 1 to enter again \n";
							char a;
							cin >> a;
							if (a == '1')
							{
								t_check = true;
							}
							else
							{
								t_check = false;
							}
						}
						else if (stoi(num) < size_arr)
						{
							for (int x = 0; x < size_arr; x++)
							{
								if (stoi(num) == arr[x].user_id)
								{
									transfer_index = x;
									transfer_possible = true;
								}
							}
							t_check = false;
						}
						else if (stoi(num) == size_arr)
						{
							transfer_index = size_arr-1;
							t_check = false;
							transfer_possible = true;
						}
						else
						{
							t_check = false;
						}
					} while (t_check);
					if (transfer_possible)
					{
						bool c_check = false;
						do {
							system("CLS");
							cout << "\nPlese enter amount you want to Transfer to account\t"<<arr[transfer_index].user_id<<endl;
							cin >> money;
							 if (money > arr[i].balance)
							{
								cout << "\n\tInsufficient Funds\n\tAccount Balance  is  " << arr[i].balance << endl;
								getchar();
								c_check = true;
							}
							else
							{
								 system("CLS");
								 system("pause");
								 cout << "\t****** Are you sure You want to transfer to Account Beneficiery *******\t\n\n";
								 cout << "\tName      :      " << arr[transfer_index].name << endl;
								 cout << "\tCNIC      :      " << arr[transfer_index].cnic << endl;
								 cout << "\tAmount    :      "<< money << endl;
								 cout << "\n\n\t******* Press 1 to Confirm *******\n";
								 char o;
								 cin >> o;
								 if (o == '1')
								 {
									 save_transaction(arr[i].user_id , money,"Transfer" , arr[transfer_index].user_id );
									 arr[transfer_index].balance += money;
									 arr[i].balance -= money;
									 cout << "\n\t****** Moeny Sent Successfully *******\n";
									 cout << "\tAccount Balance            " << arr[i].balance << endl;
								 }
								 else
								 {
									 cout << "\n\t****** Transfer Request Successfully Cancelled *******\n";
									 getchar();
								 }				
								c_check = false;
							}
						} while (c_check);
						save_data(arr, i);
						l_c = false;
					}
				}
			}
			else
			{
				cout << "\n\tPlease enter a valid PIN NUMBER \n";
				l_c = true;
			}
		} while (l_c);
	}
	void view_balance(User*&arr,int i)
	{
		system("CLS");
		cout << "\n\t************ Account Balance Check ***************\n\n";
		cout << "\tYour current account Balance     =    " << arr[i].balance << endl;
	}
	void save_card(User*&arr,int index)    // card creation code is in view menu function
	{
		ofstream write;
		write.open("Bank\\cards.txt",ios::app);
		write << arr[index].user_id << ",";
		write << arr[index].card_detail.card_num << ",";
		write << arr[index].card_detail.pin << "\n";
		write.close();
	}
	void view_transactions(int user_id)
	{
		Transaction* arr = nullptr;
		ifstream file;
		file.open("Bank\\transactions.txt");
		int count1 = 0;
		string a, b;
		while (getline(file, b))
		{
			count1++;
		}
		arr = new Transaction[count1];
		file.close();
		bool check = true;
		string c;
		int comma_count = 0;
		for (int i = 0; i < count1; i++)
		{
			file.open("Bank\\transactions.txt");
			for (int j = 0; j < i + 1; j++)
			{
				getline(file, c);
				comma_count = count(c.begin(), c.end(), ',');
			}
			file.close();
			file.open("Bank\\transactions.txt");
			for (int j = 0; j < i; j++)
			{
				getline(file, a);
			}
			if (comma_count == 3)
			{
				getline(file, a, '-');
				arr[i].day = stoi(a);
				getline(file, a, '-');
				arr[i].mon = stoi(a);
				getline(file, a, ',');
				arr[i].year = stoi(a);
				getline(file, a, ',');
				arr[i].id = stoi(a);
				getline(file, a, ',');
				arr[i].amount = stoll(a);
				getline(file, a, '\n');
				arr[i].type = a;
			}
			else if (comma_count == 4)
			{
				getline(file, a, '-');
				arr[i].day = stoi(a);
				getline(file, a, '-');
				arr[i].mon = stoi(a);
				getline(file, a, ',');
				arr[i].year = stoi(a);
				getline(file, a, ',');
				arr[i].id = stoi(a);
				getline(file, a, ',');
				arr[i].amount = stoll(a);
				getline(file, a, ',');
				arr[i].type = a;
				getline(file, a, '\n');
				arr[i].transfer_id = stoi(a);
			}
			file.close();
		}
		for (int i = 0; i < count1; i++)
		{
			if (arr[i].id == user_id)
			{
				check = false;
			}
		}
		if (check)
		{
			cout << "\n\t***** No Transaction History Available *******\n\n";
		}
		else
		{
			system("CLS");
			cout << "  \t Transaction Date \t     ID \t     Amount \t     Transaction Type \t     Transfer ID" << endl << endl;
			for (int i = 0; i < count1; i++)
			{
				if (arr[i].id == user_id)
				{
					cout << "  \t " << arr[i].day << "-" << arr[i].mon << "-" << arr[i].year;
					cout << "  \t\t    " << arr[i].id;
					cout << "  \t\t    " << arr[i].amount;
					cout << "  \t\t    " << arr[i].type;
					if (arr[i].transfer_id > 0)
					{
						cout << "  \t\t    " << arr[i].transfer_id << endl << endl;
					}
					else
					{
						cout << endl << endl;
					}
				}
			}
		}
	}
	void view_menu(User*&arr,string u,string p)
	{
		cout << "\nPress Any key to continue\n";
		getchar();
		system("CLS");
		string a;
		ifstream f1;
		f1.open("User\\user.txt");
		int size_arr = 0;
		while (getline(f1, a))
		{
			size_arr++;
		}
		f1.close();
		string b;
		ifstream f2;
		f2.open("Bank\\cards.txt");
		int c_size = 0;
		while (getline(f2, a))
		{
			c_size++;
		}
		f2.close();
		card* card_arr = new card[c_size];
		f2.open("Bank\\cards.txt");
		string t;
		for (int i = 0; i < c_size; i++)
		{
			getline(f2, t, ',');
			card_arr[i].serial = stoi(t);
			getline(f2, t, ',');
			card_arr[i].card_num = stoll(t);
			getline(f2, t, '\n');
			card_arr[i].pin = stoi(t);
		}
		f2.close();
		bool serial_check = true;
		int arr_index_num=0;
		for (int i = 0; i < size_arr; i++)
		{
			if (arr[i].login_id == u)
			{
				if (arr[i].password == p)
				{
					arr_index_num = i;

					int serial;
					serial = arr[i].user_id;
					for (int j = 0; j < c_size; j++)
					{
						if (arr[i].user_id == card_arr[j].serial)
						{
							arr[i].card_detail.serial = card_arr[j].serial;
							arr[i].card_detail.card_num = card_arr[j].card_num;
							arr[i].card_detail.pin = card_arr[j].pin;
							serial_check = false;
							break;
						}
					}
					if (serial_check)
					{
						arr[i].card_detail.generate_num();
						cout << "\t\t******* Welcome To our App for the 1st Time *********\n";
						cout << "\tThis is your debit card \t' " << arr[i].card_detail.card_num << " ' " << endl;
						arr[i].card_detail.serial = arr[i].user_id;
						bool b1 = false;
						do {
							cout << "\tPlease enter a 4 digit pin for your card number     ";
							string pin;
							cin >> pin;
							if (pin.length() == 4)
							{
								arr[i].card_detail.pin = stoi(pin);
								cout << "\n\n\t******* Pin successfully created ******** \n\n";
								save_card(arr, i);
								b1 = false;
							}
							else
							{
								cout << "\n\tPlease enter a valid Pin \n";
								b1 = true;
							}
						} while (b1);
					}
					break;
				}
			}
		}
		cout << "\nPress Any key to continue\n";
		getchar();
		bool l_c = false;
		do {			
			system("CLS");
			cout << "\n\tPlease select your choice" << endl;
			cout << "\n\t1) View Account Balance\n\t2) Transfer Funds to other accounts\n\t3) Withdraw money\n\t4) Deposit Money\n\t5) View Transaction History\n\t6) Exit\n\n";
			char l;
			cin >> l;
			if (l == '1')
			{
				view_balance(arr,arr_index_num);
				system("pause");
				cout << "\n\t******* Press any key to continue *********\n";
				getchar();
				l_c = true;
			}
			else if (l == '2')
			{
				transfer_money(arr, arr_index_num,size_arr);
				system("pause");
				cout << "\n\t******* Press any key to continue *********\n";
				 getchar(); 
				l_c = true;
			}
			else if (l == '3')
			{
				withdraw_money(arr, arr_index_num);
				system("pause");
				cout << "\n\t******* Press any key to continue *********\n";
				 getchar();
				l_c = true;
			}
			else if (l == '4')
			{
				deposit_money(arr, arr_index_num);
				cout << "\n\t*************** Money Added successfully **************\n";
				system("pause");
				cout << "\n\t******* Press any key to continue *********\n";
				 getchar();
				l_c = true;
			}
			else if (l == '5')
			{
				int id_number = arr[arr_index_num].user_id;
				view_transactions(id_number);
				system("pause");
				cout << "\n\t******* Press any key to continue *********\n";
				 getchar();
				l_c = true;
			}
			else if (l == '6')
			{
				cout << "\n\t*************** Have a Good Day **************\n";
				exit(0);
				l_c = false;
			}
			else
			{
				cout << "\n\tPlease enter a valid choice ";
				cout << "\n\t******* Press any key to continue *********\n";
				char o = getchar();
				l_c = true;
			}
		} while (l_c);
	}
};
class company :public customer
{
public:
	string c_name;
	string c_address;
	int c_tax_num;
	long int balance;
	long int withdrawal_limit;
	int c_user_id;
	card card_detail;
	int pin_check;
	long int loan;
public:
	company(string login_id = "", string password = "", int id = 0, string n = "", string add = "", int tax = 0,long int bal = 0, long int limit = 0,card d=0,int p=0, long int lo=0) :customer(login_id, password)
	{
		c_user_id = id;
		c_name = n;
		c_address = add;
		c_tax_num = tax;
		balance = bal;
		withdrawal_limit = limit;
		card_detail = d;
		pin_check = 3;
		loan = lo;
	}
	void load_data(company*& arr)   // for loading data from companies.txt
	{
		ifstream f;
		f.open("Company\\companies.txt");
		int count = 0;
		string a, b;
		while (getline(f, b))
		{
			count++;
		}
		f.close();
		arr = new company[count];
		f.open("Company\\companies.txt");
		for (int i = 0; i < count; i++)
		{
			getline(f, a, ',');
			arr[i].c_user_id = stoi(a);
			getline(f, a, ',');
			arr[i].c_name = a;
			getline(f, a, ',');
			arr[i].c_address = a;
			getline(f, a, ',');
			arr[i].c_tax_num = stoi(a);
			getline(f, a, ',');
			arr[i].login_id = a;
			getline(f, a, ',');
			arr[i].password = a;
			getline(f, a, ',');
			arr[i].withdrawal_limit = stoll(a);
			getline(f, a, ',');
			arr[i].pin_check = stoi(a);
			getline(f, a, '\n');
			arr[i].balance = stoll(a);
		}
		f.close();
	}
	bool login(company* arr, string id, string pass)
	{
		bool check = true;

		string a;
		ifstream f1;
		f1.open("Company\\companies.txt");

		int size_arr = 0;
		while (getline(f1, a))
		{
			size_arr++;
		}

		f1.close();
		for (int i = 0; i < size_arr; i++)
		{
			if (arr[i].login_id == id)
			{
				if (arr[i].password == pass)
				{

					check = false;
					return true;
				}
				else
				{
					cout << "\t******** ID and Password Does not match *********\n";
					check = false;
					return false;
				}
			}
		}
		if (check)
		{
			cout << "\t******* No user found ********\n";
			return false;
		}
	}
	void save_new_data(company*& arr, int i)
	{
		ifstream read;
		read.open("Company\\companies.txt");
		string a;
		int count = 0;
		while (getline(read, a))
		{
			count++;
		}
		read.close();
			arr[i].c_user_id = count + 1;  //serial number
			ofstream write;
			write.open("Company\\companies.txt", ios::app);
			write << arr[i].c_user_id << ",";
			write << arr[i].c_name << ",";
			write << arr[i].c_address << ",";
			write << arr[i].c_tax_num << ",";
			write << arr[i].login_id << ",";
			write << arr[i].password << ",";
			write << arr[i].withdrawal_limit << ",";
			write << arr[i].pin_check << ",";
			write << arr[i].balance << "\n";
			write.close();
	}
	void save_data(company*& arr, int i)
	{
		ifstream read;
		read.open("Company\\companies.txt");
		string a;
		int count = 0;
		while (getline(read, a))
		{
			count++;
		}
		read.close();
		bool check = false;
		// if and else for modifying code for use in deposit money
		for (int j = 0; j < count; j++)
		{
			if (arr[j].c_user_id == arr[i].c_user_id)
			{
				if (arr[j].login_id == arr[i].login_id)
				{
					arr[j].pin_check = 3;
					arr[j].balance = arr[i].balance;
					check = true;
				}
			}
		}
		if (check)
		{
			ofstream write;
			write.open("Company\\companies.txt");
			for (int k = 0; k < count; k++)
			{
				write << arr[k].c_user_id << ",";
				write << arr[k].c_name << ",";
				write << arr[k].c_address << ",";
				write << arr[k].c_tax_num << ",";
				write << arr[k].login_id << ",";
				write << arr[k].password << ",";
				write << arr[k].withdrawal_limit << ",";
				write << arr[k].pin_check << ",";
				write << arr[k].balance << "\n";
			}
			write.close();
		}
		else if(!check)
		{
			arr[i].c_user_id = count + 1;  //serial number

			ofstream write;
			write.open("Company\\companies.txt", ios::app);
			write << arr[i].c_user_id << ",";
			write << arr[i].c_name << ",";
			write << arr[i].c_address << ",";
			write << arr[i].c_tax_num << ",";
			write << arr[i].login_id << ",";
			write << arr[i].password << ",";
			write << arr[i].withdrawal_limit << ",";
			write << arr[i].pin_check << ",";
			write << arr[i].balance << "\n";
			write.close();
		}
	}
	void sign_up()
	{
		cout << "Please enter your company's Name " << endl;
		cin.ignore();
		getline(cin, c_name);
		cout << "Please enter your company's user name  " << endl;
		getline(cin, login_id);
		cout << "Please enter your company's password  " << endl;
		getline(cin, password);
		cout << "Please enter your company's Tax Number " << endl;
		cin >> c_tax_num;	
		cout << "Please enter your company's address " << endl;
		cin.ignore();
		getline(cin, c_address);
		
		bool l_c = false;
		do {
			cout << "Please select your estimated daily withdrwal limit " << endl;
			cout << "1 for  100,000 PKR      2 for  500,000 PKR   3 for  20,000,000 PKR" << endl;
			char l;
			cin >> l;
			if (l == '1')
			{
				withdrawal_limit = 100000;
				l_c = false;
			}
			else if (l == '2')
			{
				withdrawal_limit = 500000;
				l_c = false;
			}
			else if (l == '3')
			{
				withdrawal_limit = 20000000;
				l_c = false;
			}
			else
			{
				cout << "\n\tPlease enter a valid choice ";
				l_c = true;
			}
		} while (l_c);
	}

	void save_card(company*& arr, int index)    // card creation code is in view menu function
	{
		ofstream write;
		write.open("Company\\cards.txt", ios::app);
		write << arr[index].c_user_id << ",";
		write << arr[index].card_detail.card_num << ",";
		write << arr[index].card_detail.pin << "\n";
		write.close();
	}
	void view_account_balance(company*& arr, int i)
	{
		system("CLS");
		cout << "\n\t************ Account Balance Check ***************\n\n";
		cout << "\tYour current account Balance     =    " << arr[i].balance << endl;
	}
	void  save_transaction(int user, int money, string type, int transfer_index)
	{
		ofstream save;
		save.open("Bank\\company_transactions.txt", ios::app);
		time_t now = time(0);
		struct tm localTime;
		localtime_s(&localTime, &now);
		int year = localTime.tm_year + 1900;
		int month = localTime.tm_mon + 1;
		int day = localTime.tm_mday;
		if (transfer_index == 0)
		{
			save << day << "-" << month << "-" << year << ",";
			save << user << ",";
			save << money << ",";
			save << type << "\n";

		}
		else
		{
			save << day << "-" << month << "-" << year << ",";
			save << user << ",";
			save << money << ",";
			save << type << ",";
			save << transfer_index << endl;
		}
		save.close();
	}
	void withdraw_money(company*& arr, int i)
	{
		system("CLS");
		cout << "\n\t************ Withdraw Money ***************\n\n";
		int money;
		string pin;
		bool l_c = false;
		do {
			cout << "\n\tPlease enter your CARD's pin to confirm the transaction \t";
			cin >> pin;
			istringstream iss(pin);
			int value;
			if (iss >> value)
			{
				if (stoi(pin) != arr[i].card_detail.pin)
				{
					cout << "\n\n\tPlease enter a valid pin number otherwise your account will be blocked\n\n ";
					arr[i].pin_check--;
					cout << "\n\t\t Your remaining TRY attemps is   =   " << arr[i].pin_check << endl;
					if (arr[i].pin_check == 0)
					{
						l_c = false;
						cout << "\n\n\t********** Sorry Your account has been blocked for security reasons ***********\n";
						account_block(arr, i);
						cout << "\n\n\n\n";
						exit(0);
					}
					else
					{
						l_c = true;

					}
				}
				else if (stoi(pin) == arr[i].card_detail.pin)
				{
					system("CLS");
					cout << "\n\t********  ACCESS GRANTED!!!! *********\n\n";
					bool c_check = false;
					do {

						cout << "\nPlese enter amount you want to withdraw from your account\t";
						cin >> money;

						if (money > arr[i].withdrawal_limit)
						{
							cout << "\n\tDaily Withdrawal Limit exceeds\n\tEnter Amount Less than  your daily withdrawal limit i.e   " << arr[i].withdrawal_limit << endl;
							c_check = true;
						}
						else if (money > arr[i].balance)
						{
							cout << "\n\tInsufficient Funds\n\tAccount Balance  is  " << arr[i].balance << endl;
							c_check = true;
						}
						else if (money > arr[i].withdrawal_limit && money > arr[i].balance)
						{
							cout << "\n\tInsufficient Funds    and   Daily Withdrawal limit is reached " << endl;
							cout << "\n\tPlease enter Amount with in limits \n";
							cout << "\tAccount Daily Withdrawal Limit           " << arr[i].withdrawal_limit << endl;
							cout << "\tAccount Balance            " << arr[i].balance << endl;

							c_check = true;
						}
						else
						{
							cout << "\n\t****** Moeny Withdrawing *******\n";
							save_transaction(arr[i].c_user_id, money, "Withdraw", 0);

							arr[i].balance -= money;
							arr[i].withdrawal_limit -= money;
							cout << "\tAccount Daily Withdrawal Limit           " << arr[i].withdrawal_limit << endl;
							cout << "\tAccount Balance            " << arr[i].balance << endl;
							c_check = false;
						}
					} while (c_check);
					save_data(arr, i);
					l_c = false;
				}
			}
			else
			{
				cout << "\n\tPlease enter a valid PIN NUMBER \n";
				l_c = true;
			}
		} while (l_c);
	}
	void account_block(company*& arr, int z)
	{
		ifstream read;
		read.open("Company\\companies.txt");
		string a;
		int count = 0;
		while (getline(read, a))
		{
			count++;
		}
		read.close();
		company* temp = new company[count - 1];
		for (int i = 0, k = 0; i < count; i++)
		{
			if (i == z)
			{
				continue;
			}
			else
			{
				temp[k].c_user_id = arr[i].c_user_id;
				temp[k].c_name = arr[i].c_name;
				temp[k].c_address = arr[i].c_address;
				temp[k].c_tax_num = arr[i].c_tax_num;
				temp[k].login_id = arr[i].login_id;
				temp[k].password = arr[i].password;
				temp[k].withdrawal_limit = arr[i].withdrawal_limit;
				temp[k].pin_check = arr[i].pin_check;
				temp[k].balance = arr[i].balance;
				k++;
			}
		}
		ofstream write;
		write.open("Company\\companies.txt");
		for (int k = 0; k < count - 1; k++)
		{
			write << temp[k].c_user_id << ",";
			write << temp[k].c_name << ",";
			write << temp[k].c_address << ",";
			write << temp[k].c_tax_num<< ",";
			write << temp[k].login_id << ",";
			write << temp[k].password << ",";
			write << temp[k].withdrawal_limit << ",";
			write << temp[k].pin_check << ",";
			write << temp[k].balance << "\n";
		}
		write.close();

		ofstream fraud;
		fraud.open("Bank\\company_blocked.txt", ios::app);

		fraud << arr[z].c_user_id << ",";
		fraud << arr[z].c_name << ",";
		fraud << arr[z].c_address << ",";
		fraud << arr[z].c_tax_num << ",";
		fraud << arr[z].login_id << ",";
		fraud << arr[z].password << ",";
		fraud << arr[z].withdrawal_limit << ",";
		fraud << arr[z].pin_check << ",";
		fraud << arr[z].balance << "\n";
		fraud.close();
	}
	void transfer_money(company*& arr, int i, int size_arr)
	{
		system("CLS");
		cout << "\n\t************ Transfer Money ***************\n\n";
		int money;
		string pin;
		bool l_c = false;
		do {
			cout << "\n\tPlease enter your CARD's pin to confirm the transaction \t";
			cin >> pin;
			istringstream iss(pin);
			int value;
			if (iss >> value)
			{
				if (stoi(pin) != arr[i].card_detail.pin)
				{
					cout << "\n\n\tPlease enter a valid pin number otherwise your account will be blocked\n\n ";
					arr[i].pin_check--;
					cout << "\n\t\t Your remaining TRY attemps is   =   " << arr[i].pin_check << endl;
					if (arr[i].pin_check == 0)
					{
						l_c = false;
						cout << "\n\n\t********** Sorry Your account has been blocked for security reasons ***********\n";
						account_block(arr, i);
						cout << "\n\n\n\n";
						exit(0);
					}
					else
					{
						l_c = true;
					}
				}
				else if (stoi(pin) == arr[i].card_detail.pin)
				{
					system("CLS");
					cout << "\n\t********  ACCESS GRANTED!!!! *********\n\n";
					int transfer_index=0;
					int transfer_id = 0;
					bool transfer_possible = false;
					bool t_check = false;
					ifstream r;
					r.open("Company\\companies_employees.txt");
					string z,y;
					int s = 0;
					while(getline(r,z))
					{
						s++;
					}
					r.close();
					int** emp_arr = new int* [s];
					for (int k = 0; k < s; k++)
					{
						emp_arr[k] = new int[2];
					}
					r.open("Company\\companies_employees.txt");
					for (int a = 0; a < s; a++)
					{
						for (int b = 0; b < 2;b++ )
						{
							getline(r, y, ',');
							emp_arr[a][b] = stoi(y);
							b++;
							getline(r, y, '\n');
							emp_arr[a][b] = stoi(y);
						}
					}
					r.close();
					do
					{
						cout << "\n\tPlease Enter The  User id number of the reciepient " << endl;
						string num;
						cin >> num;
						for (int a = 0; a < s; a++)
						{
							if (stoi(num) == emp_arr[a][0])
							{
								if (arr[i].c_user_id == emp_arr[a][1])
								{
									transfer_id = emp_arr[a][0];
									transfer_possible = true;
									break;
								}
							}							
						}
					if (transfer_possible)
					{
						bool c_check = false;
						do {
							system("CLS");
							User* arr2 = nullptr;
							User object;
							object.load_data(arr2);
							ifstream temp;
							temp.open("User\\user.txt");
							string tem;
							int size_arr2 = 0;
							while(getline(temp,tem))
							{
								size_arr2++;
							}
							temp.close();
							for (int p = 0; p < size_arr2 ; p++)
							{
								if (transfer_id == arr2[p].user_id)
								{
									transfer_index = p;
									break;
								}
							}
							cout << "\nPlese enter amount you want to Transfer to account\t" << arr2[transfer_index].user_id << endl;
							cin >> money;
							if (money > arr[i].balance)
							{
								cout << "\n\tInsufficient Funds\n\tAccount Balance  is  " << arr[i].balance << endl;
								getchar();
								c_check = true;
							}
							else
							{
								system("CLS");
								cout << "\t****** Are you sure You want to transfer to Uer client Account Beneficiery *******\t\n\n";
								cout << "\tName      :      " << arr2[transfer_index].name << endl;
								cout << "\tCNIC      :      " << arr2[transfer_index].cnic << endl;
								cout << "\tAmount    :      " << money << endl;
								cout << "\n\n\t******* Press 1 to Confirm *******\n";
								char o;
								cin >> o;
								if (o == '1')
								{
									save_transaction(arr[i].c_user_id, money, "Transfer", arr2[transfer_index].user_id);
									arr2[transfer_index].balance += money;
									arr[i].balance -= money;
									cout << "\n\t****** Moeny Sent Successfully *******\n";
									cout << "\tAccount Balance            " << arr[i].balance << endl;
									User o;
									o.save_data(arr2, transfer_index);
								}
								else
								{
									cout << "\n\t****** Transfer Request Successfully Cancelled *******\n";
									getchar();
								}
								c_check = false;
							}
						} while (c_check);

						t_check = false;
						save_data(arr, i);
						l_c = false;
					}
					else
					{
						cout << "\n\tUser ID does not exist with Company \n";
						cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
						char a;
						cin >> a;
						if (a == '1')
						{
							cout << "\n\tPlease enter a valid ID number (only 1 Digit) ";
							t_check = true;
						}
						else
						{
							t_check = false;
						}
					}
					} while (t_check);
				}
			}
			else
			{
				cout << "\n\tPlease enter a valid PIN NUMBER \n";
				l_c = true;
			}
		} while (l_c);
		
	}
	void deposit_money(company*& arr, int i)
	{
		system("CLS");
		cout << "\n\t************ Deposit Money ***************\n\n";
		int money;

		string pin;
		bool l_c = false;
		do {
			cout << "\n\tPlease enter your CARD's pin to confirm the deposit transaction \t";
			cin >> pin;
			istringstream iss(pin);
			int value;
			if (iss >> value)
			{
				if (stoi(pin) != arr[i].card_detail.pin)
				{
					cout << "\n\n\tPlease enter a valid pin number otherwise your account will be blocked\n\n ";
					arr[i].pin_check--;
					cout << "\n\t\t Your remaining TRY attemps is   =   " << arr[i].pin_check << endl;
					if (arr[i].pin_check == 0)
					{
						l_c = false;
						cout << "\n\n\t********** Sorry Your account has been blocked for security reasons ***********\n";
						account_block(arr, i);
						cout << "\n\n\n\n";
						exit(0);
					}
					else
					{
						l_c = true;

					}
				}
				else if (stoi(pin) == arr[i].card_detail.pin)
				{
					system("CLS");
					cout << "\n\t********  ACCESS GRANTED!!!! *********\n\n";
					cout << "Plese enter amount you want to deposit into your account\t";
					cin >> money;
					save_transaction(arr[i].c_user_id, money, "Deposit", 0);
					arr[i].balance += money;
					save_data(arr, i);
					l_c = false;
				}
			}
			else
			{
				cout << "\n\tPlease enter a valid PIN NUMBER \n";
				l_c = true;
			}
		} while (l_c);
	}
	void view_transactions(int user_id)
	{
		Transaction* arr = nullptr;
		ifstream file;
		file.open("Bank\\company_transactions.txt");
		int count1 = 0;
		string a, b;
		while (getline(file, b))
		{
			count1++;
		}
		arr = new Transaction[count1];
		file.close();
		bool check = true;
		string c;
		int comma_count = 0;

		for (int i = 0; i < count1; i++)
		{
			file.open("Bank\\company_transactions.txt");
			for (int j = 0; j < i + 1; j++)
			{
				getline(file, c);
				comma_count = count(c.begin(), c.end(), ',');
			}
			file.close();
			file.open("Bank\\company_transactions.txt");
			for (int j = 0; j < i; j++)
			{
				getline(file, a);
			}
			if (comma_count == 3)
			{
				getline(file, a, '-');
				arr[i].day = stoi(a);
				getline(file, a, '-');
				arr[i].mon = stoi(a);
				getline(file, a, ',');
				arr[i].year = stoi(a);
				getline(file, a, ',');
				arr[i].id = stoi(a);
				getline(file, a, ',');
				arr[i].amount = stoll(a);
				getline(file, a, '\n');
				arr[i].type = a;

			}
			else if (comma_count == 4)
			{
				getline(file, a, '-');
				arr[i].day = stoi(a);
				getline(file, a, '-');
				arr[i].mon = stoi(a);
				getline(file, a, ',');
				arr[i].year = stoi(a);
				getline(file, a, ',');
				arr[i].id = stoi(a);
				getline(file, a, ',');
				arr[i].amount = stoll(a);
				getline(file, a, ',');
				arr[i].type = a;
				getline(file, a, '\n');
				arr[i].transfer_id = stoi(a);
			}
			file.close();
		}
		for (int i = 0; i < count1; i++)
		{
			if (arr[i].id == user_id)
			{
				check = false;
			}
		}
		if (check)
		{
			cout << "\n\t***** No Transaction History Available *******\n\n";
		}
		else
		{
			system("CLS");
			cout << "  \t Transaction Date \t     ID \t     Amount \t     Transaction Type \t     Transfer ID" << endl << endl;
			for (int i = 0; i < count1; i++)
			{
				if (arr[i].id == user_id)
				{
					cout << "  \t " << arr[i].day << "-" << arr[i].mon << "-" << arr[i].year;
					cout << "  \t\t    " << arr[i].id;
					cout << "  \t\t    " << arr[i].amount;
					cout << "  \t\t    " << arr[i].type;
					if (arr[i].transfer_id > 0)
					{
						cout << "  \t\t    " << arr[i].transfer_id << endl << endl;
					}
					else
					{
						cout << endl << endl;
					}
				}
			}
		}
	}
	void loan_request(company*& arr, int index)
	{
		cout << "\nPress Any key to continue\n";
		getchar();
		system("CLS");
		cout << "\n\tPlease enter Loan Amount      " ;
		long int amount;
		cin >> amount;
		cout << "\n\t******** Your Request For Loan Has been sent To Admin For Approval ********\n\n";
		ofstream obj;
		obj.open("Bank\\loan_req.txt", ios::app);
		obj << arr[index].c_user_id << ",";
		obj << arr[index].c_name << ",";
		obj << amount << "\n";
		obj.close();
	}
	void view_menu(company*& arr, string u, string p)
	{
		cout << "\n******* Press Any key to continue ********\n";
		getchar();
		system("CLS");
		string a;
		ifstream f1;
		f1.open("Company\\companies.txt");

		int size_arr = 0;
		while (getline(f1, a))
		{
			size_arr++;
		}
		f1.close();

		string b;
		ifstream f2;
		f2.open("Company\\cards.txt");
		int c_size = 0;
		while (getline(f2, b))
		{
			c_size++;
		}
		f2.close();

		card* card_arr = new card[c_size];
		f2.open("Company\\cards.txt");
		string t;
		for (int i = 0; i < c_size; i++)
		{
			getline(f2, t, ',');
			card_arr[i].serial = stoi(t);
			getline(f2, t, ',');
			card_arr[i].card_num = stoll(t);
			getline(f2, t, '\n');
			card_arr[i].pin = stoi(t);
		}
		f2.close();
		bool serial_check = true;
		int index_number = 0;
		for (int i = 0; i < size_arr; i++)
		{
			if (arr[i].login_id == u)
			{

				if (arr[i].password == p)
				{
					index_number = i;
					int serial;
					serial = arr[i].c_user_id;
					for (int j = 0; j < c_size; j++)
					{
						if (arr[i].c_user_id == card_arr[j].serial)
						{
							arr[i].card_detail.serial = card_arr[j].serial;
							arr[i].card_detail.card_num = card_arr[j].card_num;
							arr[i].card_detail.pin = card_arr[j].pin;
							serial_check = false;
							break;
						}
					}
					if (serial_check)
					{
						arr[i].card_detail.generate_num();
						cout << "\t\t******* Welcome To our App for the 1st Time *********\n";
						cout << "\tThis is your debit card \t' " << arr[i].card_detail.card_num << " ' " << endl;
						arr[i].card_detail.serial = arr[i].c_user_id;
						bool b1 = false;
						do {
							cout << "\tPlease enter a 4 digit pin for your card number     ";
							string pin;
							cin >> pin;
							if (pin.length() == 4)
							{
								arr[i].card_detail.pin = stoi(pin);
								cout << "\n\n\t******* Pin successfully created ******** \n\n";
								save_card(arr, i);
								b1 = false;
							}
							else
							{
								cout << "\n\tPlease enter a valid Pin \n";
								b1 = true;
							}
						} while (b1);
					}
					break;
				}
			}
		}
		bool l_c = false;
		do {
			cout << "\nPress Any key to continue\n";
			getchar();
			system("CLS");
			cout << "\n\tPlease select your choice" << endl;
			cout << "\n\t1) View Account Balance\n\t2) Transfer Funds to Client's account\n\t3) Withdraw money\n\t4) Deposit Money\n\t5) View Transaction History\n\t6) Request Loan \n\t7)Exit \n\n";
			char l;
			cin >> l;
			if (l == '1')
			{
				view_account_balance(arr, index_number);
				char o;
				o = getchar();
				l_c = true;
			}
			else if (l == '2')
			{
				transfer_money(arr, index_number, size_arr);
				char o;
				o = getchar();
				l_c = true;
			}
			else if (l == '3')
			{
				withdraw_money(arr, index_number);
				char o;
				o = getchar();
				l_c = true;
			}
			else if (l == '4')
			{
				deposit_money(arr, index_number);;
				cout << "\n\t*********** Money Deposited Successfully ************\n";
				char o;
				o = getchar();
				l_c = true;
			}
			else if (l == '5')
			{
				int id_number = arr[index_number].c_user_id;
				view_transactions(id_number);
				char o;
				o = getchar();
				l_c = true;
			}
			else if (l == '6')
			{
				loan_request(arr,index_number);
				char o;
				o = getchar();
				l_c = true;
			}
			else if (l == '7')
			{
				system("CLS");
				cout << "\n\t******* Have a good Day **********\n";
				exit(0);
				l_c = false;
			}
			else
			{
				cout << "\n\You have entered an Invalid choice ";
				char o;
				cout << "\n\tEnter 1 to exit     OR    Press any key to go to view menu again \n";
				cin >> o;
				if (o == '1')
				{
					cout << "\n\t******* Have a good Day **********\n";
					l_c = false;
				}
				else
				{
					l_c = true;
				}
			}
		} while (l_c);
	}
};
class bank_employee :public customer
{
public:
	company comp;  // composition
		User obj;
		Transaction trans;
public:
	void load_data(bank_employee*& arr)   
	{
		ifstream f;
		f.open("Bank\\admin.txt");
		int count = 0;
		string a, b;
		while (getline(f, b))
		{
			count++;
		}
		f.close();
		arr = new bank_employee[count];
		f.open("Bank\\admin.txt");
		for (int i = 0; i < count; i++)
		{
			getline(f, a, ',');
			arr[i].login_id = a;
			getline(f, a, '\n');
			arr[i].password = a;
		}
		f.close();
	}
	bool login(bank_employee* arr, string id, string pass)
	{
		bool check = true;
		string a;
		ifstream f1;
		f1.open("Bank\\admin.txt");
		int size_arr = 0;
		while (getline(f1, a))
		{
			size_arr++;
		}
		f1.close();
		for (int i = 0; i < size_arr; i++)
		{
			if (arr[i].login_id == id)
			{
				if (arr[i].password == pass)
				{
					check = false;
					return true;
				}
				else
				{
					cout << "\t******** ID and Password Does not match *********\n";
					check = false;
					return false;
				}
			}
		}
		if (check)
		{
			cout << "\t******* No user found ********\n";
			return false;
		}
	}
	void view_transactions(int user_id)
	{
		Transaction *arr=nullptr;
		ifstream file;
		file.open("Bank\\transactions.txt");
		int count1 = 0;
		string a, b;
		while (getline(file, b))
		{
			count1++;
		}
		arr = new Transaction[count1];
		file.close();
		bool check = true;
		string c;
		int comma_count = 0;		
		for (int i = 0; i < count1; i++)
		{
			file.open("Bank\\transactions.txt");
			for (int j = 0; j < i+1; j++)
			{
				getline(file, c);
					comma_count = count(c.begin(), c.end(), ',');
			}
			file.close();
				file.open("Bank\\transactions.txt");
				for (int j = 0; j < i;j++)
				{
					getline(file, a);
				}
				if (comma_count == 3)
				{
					getline(file, a, '-');
					arr[i].day = stoi(a);
					getline(file, a, '-');
					arr[i].mon = stoi(a);
					getline(file, a, ',');
					arr[i].year = stoi(a);
					getline(file, a, ',');
					arr[i].id = stoi(a);
					getline(file, a, ',');
					arr[i].amount = stoll(a);
					getline(file, a, '\n');
					arr[i].type = a;
				
				}
				else if (comma_count == 4)
				{
					getline(file, a, '-');
					arr[i].day = stoi(a);
					getline(file, a, '-');
					arr[i].mon = stoi(a);
					getline(file, a, ',');
					arr[i].year = stoi(a);
					getline(file, a, ',');
					arr[i].id = stoi(a);
					getline(file, a, ',');
					arr[i].amount = stoll(a);
					getline(file, a, ',');
					arr[i].type = a;
					getline(file, a, '\n');
					arr[i].transfer_id = stoi(a);
				}
				file.close();
		}		
		for (int i = 0; i < count1; i++)
		{
			if (arr[i].id == user_id)
			{
				check = false;
			}
		}
		if (check)
		{
			cout << "\n\t***** No Transaction History Available *******\n\n";
		}
		else
		{
			system("CLS");
			cout << "  \t Transaction Date \t     ID \t     Amount \t     Transaction Type \t     Transfer ID" << endl << endl;
			for(int i=0;i<count1 ;i++)
			{
				if (arr[i].id == user_id)
				{
					cout << "  \t " << arr[i].day << "-" << arr[i].mon << "-" << arr[i].year;
					cout << "  \t\t    " << arr[i].id;
					cout << "  \t\t    " << arr[i].amount;
					cout << "  \t\t    " << arr[i].type;
					if(arr[i].transfer_id>0)
					{
						cout << "  \t\t    " << arr[i].transfer_id << endl << endl;
					}
					else
					{
						cout<< endl << endl;
					}				
				}
			}
		}
	}
	void delete_company_data(company*& arr, string id)
	{
		ifstream obj;
		obj.open("Bank\\company_req.txt");
		int c = 0;
		string a;
		while (getline(obj, a))
		{
			c++;
		}
		obj.close();
		company* temp = new company[c - 1];
		for (int i = 0, j = 0; j < c; j++)
		{
			if (id == arr[j].login_id)
			{
				continue;
			}
			else
			{
				temp[i].c_user_id = arr[j].c_user_id;
				temp[i].c_name = arr[j].c_name;
				temp[i].c_address = arr[j].c_address;
				temp[i].c_tax_num = arr[j].c_tax_num;
				temp[i].login_id = arr[j].login_id;
				temp[i].password = arr[j].password;
				temp[i].withdrawal_limit = arr[j].withdrawal_limit;
				i++;
			}
		}
		ofstream req;
		req.open("Bank\\company_req.txt");
		for (int i = 0; i < c - 1; i++)
		{
			req << temp[i].c_user_id << ",";
			req << temp[i].c_name << ",";
			req << temp[i].c_address << ",";
			req << temp[i].c_tax_num << ",";
			req << temp[i].login_id << ",";
			req << temp[i].password << ",";
			req << temp[i].withdrawal_limit << "\n";
		}
		req.close();
	}
	void delete_user_data(User*& arr,string id)
	{
		ifstream obj;
		obj.open("Bank\\user_req.txt");
		int c = 0;
		string a;
		while (getline(obj, a))
		{
			c++;
		}
		obj.close();
		User* temp = new User[c-1];
		for (int i = 0,j=0; j < c; j++)
		{
			if (id == arr[j].login_id)
			{
				continue;
			}
			else
			{
				temp[i].user_id = arr[j].user_id;
				temp[i].name = arr[j].name;
				temp[i].address = arr[j].address;
				temp[i].cnic = arr[j].cnic;
				temp[i].login_id = arr[j].login_id;
				temp[i].password = arr[j].password;
				temp[i].phone = arr[j].phone;
				temp[i].withdrawal_limit = arr[j].withdrawal_limit;
				i++;
			}
		}
		ofstream req;
		req.open("Bank\\user_req.txt");
		for (int i = 0; i < c - 1; i++)
		{
			req << temp[i].user_id << ",";
			req << temp[i].name << ",";
			req << temp[i].address << ",";
			req << temp[i].cnic << ",";
			req << temp[i].login_id << ",";
			req << temp[i].password << ",";
			req << temp[i].phone << ",";
			req << temp[i].withdrawal_limit << "\n";
		}
		req.close();
		
	}
	void view_request_of_new_account()
	{
		view_again:
		system("CLS");
		bool check = false;
		do {
			cout << "\t For which account Type you want to View Requests " << endl;
			cout << "\t\tSelect your choice" << endl;
			cout << "\n\t\t1 for  User Accounts      2 for  Company Accounts   " << endl;
			char l;
			cin >> l;
			if (l == '1')
			{
				system("CLS");
				ifstream obj;
				obj.open("Bank\\user_req.txt");
				int c = 0;
				string a,b;
				while (getline(obj, b))
				{
					c++;
				}
				obj.close();
				User* arr = new User[c];
				obj.open("Bank\\user_req.txt");
				cout << "  \t Name\t     Address\t     CNIC\t     UserName\t     Password\t    Phone\t     WIthdrawal Limit" << endl<<endl;
				for (int i = 0; i < c; i++)
				{
					
					getline(obj, a,',');
					arr[i].user_id = stoi(a);
					cout << (i+1) << ")    ";
					getline(obj, a, ',');
					arr[i].name = a;
					cout << a << "\t   ";
					getline(obj, a, ',');
					arr[i].address = a;
					cout << a << "\t   ";
					getline(obj, a, ',');
					arr[i].cnic = stoll(a);
					cout << a << "\t   ";
					getline(obj, a, ',');
					arr[i].login_id = a;
					cout << a << "\t   ";
					getline(obj, a, ',');
					arr[i].password = a;
					cout << a << "\t   ";
					getline(obj, a, ',');
					arr[i].phone = stoll(a);
					cout << a << "\t   ";
					getline(obj, a, '\n');
					arr[i].withdrawal_limit = stoll(a);
					cout << a << "\n";
					cout << endl;
				}

				obj.close();
				login_input:
				cout << "\n\tPlease enter the User Name from the above to Accept/reject the Reqeust \n";
				string id;
				cin.ignore();
				getline(cin, id);

				for (int i = 0; i < c; i++)
				{
					if (id == arr[i].login_id)
					{
						bool l_c=false;
						do {
							cout << "\n\tPlease select your choice" << endl;
							cout << "\n\tPree 1 to accept Request     Press 2 To Reject Rquest \n";
							char l;
							cin >> l;
							if (l == '1')
							{
								User save_obj;
								save_obj.save_new_data(arr, i);
								system("CLS");
								cout << "\n\n\t\t********** User's Account has been created Successfullyy ***********\n\n";
								bank_employee obj;
								obj.delete_user_data(arr,id);
								bool new_check = false;
								do {
									cout << "\n\tPlease select your choice" << endl;
									cout << "\tPress 1 to view again    and    Press Any key to go to menu\n";
									char us;
									cin >> us;
									if (us == '1')
									{
										goto view_again;
										new_check = false;
									}
									else
									{
										new_check = false;
									}
								} while (new_check);
								
								l_c = false;
							}
							else if (l == '2')
							{
								system("CLS");
								cout << "\n\n\t\t********** User's Request has been Rejected Successfullyy ***********\n\n";
								bank_employee obj;
								obj.delete_user_data(arr, id);
								bool new_check = false;
								do {
									cout << "\n\tPlease select your choice" << endl;
									cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
									char us;
									cin >> us;
									if (us == '1')
									{
										goto view_again;
										new_check = false;
									}
									else
									{
										new_check = false;
									}
								} while (new_check);
								l_c = false;
							}
							else
							{
								cout << "\n\tPlease enter a valid choice ";
								l_c = true;
							}
						} while (l_c);
						break;
					}
					else if (i == c - 1 )
					{
						cout << "\n\t**** Invalid LOGIN ID ****\n\n";
						
						bool che = false;
						do {
							cout << "\n\tPlease select your choice" << endl;
							cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
							char l;
							cin >> l;
							if (l == '1')
							{
								goto login_input;
								che = false;
							}
							else
							{
								che = false;
							}
						} while (che);
					}
				}
				check = false;
			}
			else if (l == '2')
			{
				system("CLS");
				ifstream obj;
				obj.open("Bank\\company_req.txt");
				int c = 0;
				string a;
				while (getline(obj, a))
				{
					c++;
				}
				obj.close();
				company* arr = new company[c];

				obj.open("Bank\\company_req.txt");
				cout << "       Company Name   \tCompany Address   \tCompany Tax Number    \tCompany UserName     \tPassword    \tWIthdrawal Limit" << endl << endl;
				for (int i = 0; i < c; i++)
				{
					getline(obj, a, ',');
					arr[i].c_user_id = stoi(a);
					cout << i+1  << ")   ";
					getline(obj, a, ',');
					arr[i].c_name = a;
					cout <<"\t" << a << "\t\t";
					getline(obj, a, ',');
					arr[i].c_address = a;
					cout << a << "\t\t\t";
					getline(obj, a, ',');
					arr[i].c_tax_num = stoi(a);
					cout << a << "\t\t\t";
					getline(obj, a, ',');
					arr[i].login_id = a;
					cout << a << "\t\t\t";
					getline(obj, a, ',');
					arr[i].password = a;
					cout << a << "\t\t\t";
					getline(obj, a, '\n');
					arr[i].withdrawal_limit = stoll(a);
					cout << a << "\n";
					cout << endl;
				}
				obj.close();
				c_input:

				cout << "\n\tPlease enter the Company User Name from the above to Accept/reject the Request \n";
				string id;
				cin.ignore();
				getline(cin, id);

				for (int i = 0; i < c; i++)
				{
					if (id == arr[i].login_id)
					{
						bool l_c = false;
						do {
							cout << "\n\tPlease select your choice" << endl;
							cout << "\n\tPree 1 to accept Request     Press 2 To Reject Rquest \n";
							char l;
							cin >> l;
							if (l == '1')
							{
								company save_obj;
								save_obj.save_new_data(arr, i);
								system("CLS");
								cout << "\n\n\t\t********** User's Account has been created Successfullyy ***********\n\n";

								bank_employee obj;
								obj.delete_company_data(arr, id);

								bool new_check = false;
								do {
									cout << "\n\tPlease select your choice" << endl;
									cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
									char us;
									cin >> us;
									if (us == '1')
									{
										goto view_again;
										new_check = false;
									}
									else
									{
										new_check = false;
									}
								} while (new_check);
								l_c = false;
							}
							else if (l == '2')
							{
								system("CLS");
								cout << "\n\n\t\t********** User's Request has been Rejected Successfullyy ***********\n\n";
								bank_employee obj;
								obj.delete_company_data(arr, id);
								bool new_check = false;
								do {
									cout << "\n\tPlease select your choice" << endl;
									cout << "\tPress 1 to view again    and    Press Any key to go to menu\n";
									char us;
									cin >> us;
									if (us == '1')
									{
										goto view_again;
										new_check = false;
									}
									else
									{
										new_check = false;
									}
								} while (new_check);
								l_c = false;
							}
							else
							{
								cout << "\n\tPlease enter a valid choice ";
								l_c = true;
							}
						} while (l_c);
						break;
					}
					else if (i == c - 1)
					{
						cout << "\n\t**** Invalid LOGIN ID ****\n\n";

						bool che = false;
						do {
							cout << "\n\tPlease select your choice" << endl;
							cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
							char l;
							cin >> l;
							if (l == '1')
							{
								goto c_input;
								che = false;
							}
							else
							{
								che = false;
							}
						} while (che);
					}

				}

				check = false;
			}
			else
			{
				cout << "\n\tPlease enter a valid choice ";
				check = true;
			}
		} while (check);
	}
	void new_req_user(User temp)
	{
		obj = temp;
		ofstream req;
		req.open("Bank\\user_req.txt", ios::app);
		req << obj.user_id << ",";
		req << obj.name << ",";
		req << obj.address << ",";
		req << obj.cnic << ",";
		req << obj.login_id << ",";
		req << obj.password << ",";
		req << obj.phone << ",";
		req << obj.withdrawal_limit << "\n";
		req.close();
		system("CLS");
		cout << "\n\t\t********* THANKS FOR SIGNING UP ***********" << endl;
		cout << "\t\t\tYour reqeust has been received\n";
		cout << "\t\tWait for approval by Bank's Admin " << endl;
	}
	void new_req_company(company temp)
	{
		comp = temp;
		ofstream req;
		req.open("Bank\\company_req.txt", ios::app);
		req << comp.c_user_id<< ",";
		req << comp.c_name << ",";
		req << comp.c_address << ",";
		req << comp.c_tax_num << ",";
		req << comp.login_id << ",";
		req << comp.password << ",";
		req << comp.withdrawal_limit << "\n";
		req.close();
		system("CLS");
		cout << "\n\t\t********* THANKS FOR SIGNING UP ***********" << endl;
		cout << "\t\t\tYour reqeust has been received\n";
		cout << "\t\tWait for approval by Bank's Admin " << endl;
	}
	void close_account()
	{
	view_a:
		system("CLS");
		ifstream obj;
		obj.open("Bank\\user_blocked.txt");
		int c = 0;
		string a, b;
		while (getline(obj, b))
		{
			c++;
		}
		obj.close();
		obj.open("Bank\\user_blocked.txt");
		if (c == 0)
		{
			cout << "\n\t***** No Accounts data *****\n\n";
			getchar();
		}
		else
		{
			bool check = false;
			do {
				cout << "\n\tPlease select your choice" << endl;
				cout << "\n\tPress 1 to Close Blocked Accounts Permenently       \n";
				cout << "\n\tPress 2 to Restore Blocked Accounts       \n";

				char l;
				cin >> l;
				if (l == '1')
				{
					system("CLS");

					User* arr = new User[c];
					cout << "  \tUser ID     \t Name\t     Address\t     CNIC\t     UserName\t     Balance\t     Reason" << endl << endl;
					for (int i = 0; i < c; i++)
					{

						getline(obj, a, ',');
						arr[i].user_id = stoi(a);
						cout << "\t   " << arr[i].user_id << "\t      ";
						getline(obj, a, ',');
						arr[i].name = a;
						cout << a << "\t      ";
						getline(obj, a, ',');
						arr[i].address = a;
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].cnic = stoll(a);
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].login_id = a;
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].password = a;
						getline(obj, a, ',');
						arr[i].withdrawal_limit = stoll(a);
						getline(obj, a, ',');
						arr[i].pin_check = stoi(a);
						getline(obj, a, '\n');
						arr[i].balance = stoll(a);
						cout << a << "\t";
						cout << "Wrong Card Pin" << endl;
						cout << endl;
					}

					obj.close();
				login_input:

					cout << "\n\tPlease enter the User ID from the above to Close the account \n";
					string id;
					cin.ignore();
					getline(cin, id);

					for (int i = 0; i < c; i++)
					{
						if (stoi(id) == arr[i].user_id)
						{

							cout << "\n\t**** Are you sure *****" << endl;
							cout << "\n\tPress 1 Continue        Press anykey to Cancel\n";
							char us;
							cin >> us;
							if (us == '1')
							{
								cout << "\n\t********** Account Successfully Closed  ************\n\n";
								User* temp = new User[c - 1];
								for (int x = 0, j = 0; j < c ; j++)
								{
									if (j == i)
									{
										continue;
									}
									else
									{
										temp[x].user_id = arr[j].user_id;
										temp[x].address = arr[j].address;
										temp[x].balance = arr[j].balance;
										temp[x].cnic = arr[j].cnic;
										temp[x].name = arr[j].name;
										temp[x].withdrawal_limit = arr[j].withdrawal_limit;
										temp[x].password = arr[j].password;
										temp[x].login_id = arr[j].login_id;
										temp[x].pin_check = arr[j].pin_check;
										x++;

									}
								}

								ofstream fraud;
								fraud.open("Bank\\user_blocked.txt");
								for (int z = 0; z < c - 1; z++)
								{
									fraud << temp[z].user_id << ",";
									fraud << temp[z].name << ",";
									fraud << temp[z].address << ",";
									fraud << temp[z].cnic << ",";
									fraud << temp[z].login_id << ",";
									fraud << temp[z].password << ",";
									fraud << temp[z].withdrawal_limit << ",";
									fraud << temp[z].pin_check << ",";
									fraud << temp[z].balance << "\n";
								}
								fraud.close();
								close_account();
							}
							else
							{
								cout << "\n\t********** Request Cancelled  ************\n\n";
								close_account();

							}
							break;
						}

						else if (i == c - 1)
						{
							cout << "\n\t**** Invalid LOGIN ID ****\n\n";

							bool che = false;
							do {
								cout << "\n\tPlease select your choice" << endl;
								cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
								char l;
								cin >> l;
								if (l == '1')
								{
									goto login_input;
									che = false;
								}
								else
								{
									che = false;
								}
							} while (che);
						}
					}
					check = false;
				}
				else if (l == '2')
				{
					system("CLS");

					User* arr = new User[c];
					cout << "  \tUser ID     \t Name\t     Address\t     CNIC\t     UserName\t     Balance\t     Reason" << endl << endl;
					for (int i = 0; i < c; i++)
					{

						getline(obj, a, ',');
						arr[i].user_id = stoi(a);
						cout << "\t   " << arr[i].user_id << "\t      ";
						getline(obj, a, ',');
						arr[i].name = a;
						cout << a << "\t      ";
						getline(obj, a, ',');
						arr[i].address = a;
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].cnic = stoll(a);
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].login_id = a;
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].password = a;
						getline(obj, a, ',');
						arr[i].withdrawal_limit = stoll(a);
						getline(obj, a, ',');
						arr[i].pin_check = stoi(a);
						getline(obj, a, '\n');
						arr[i].balance = stoll(a);
						cout << a << "\t";
						cout << "Wrong Card Pin" << endl;
						cout << endl;
					}

					obj.close();
				again_input:

					cout << "\n\tPlease enter the User ID from the above to Restore account \n";
					string id;
					cin.ignore();
					getline(cin, id);

					for (int i = 0; i < c; i++)
					{
						if (stoi(id) == arr[i].user_id)
						{

							cout << "\n\t**** Are you sure *****" << endl;
							cout << "\n\tPress 1 Continue        Press anykey to Cancel\n";
							char us;
							cin >> us;
							
							if (us == '1')
							{
								arr[i].pin_check = 3;
								cout << "\n\t********** Account Successfully Restored  ************\n\n Press any key to continue\n\n";
								getchar();
								User* temp = new User[c - 1];
								for (int x = 0, j = 0; j < c; j++)
								{
									if (j == i)
									{
										continue;
									}
									else
									{
										temp[x].user_id = arr[j].user_id;
										temp[x].address = arr[j].address;
										temp[x].balance = arr[j].balance;
										temp[x].cnic = arr[j].cnic;
										temp[x].name = arr[j].name;
										temp[x].withdrawal_limit = arr[j].withdrawal_limit;
										temp[x].password = arr[j].password;
										temp[x].login_id = arr[j].login_id;
										temp[x].pin_check = arr[j].pin_check;
										x++;
									}
								}

								ofstream fraud;
								fraud.open("Bank\\user_blocked.txt");
								for (int z = 0; z < c - 1; z++)
								{
									fraud << temp[z].user_id << ",";
									fraud << temp[z].name << ",";
									fraud << temp[z].address << ",";
									fraud << temp[z].cnic << ",";
									fraud << temp[z].login_id << ",";
									fraud << temp[z].password << ",";
									fraud << temp[z].withdrawal_limit << ",";
									fraud << temp[z].pin_check << ",";
									fraud << temp[z].balance << "\n";
								}
								fraud.close();
								ofstream write;
								write.open("User\\user.txt", ios::app);
								write << arr[i].user_id << ",";
								write << arr[i].name << ",";
								write << arr[i].address << ",";
								write << arr[i].cnic << ",";
								write << arr[i].login_id << ",";
								write << arr[i].password << ",";
								write << arr[i].withdrawal_limit << ",";
								write << arr[i].pin_check << ",";
								write << arr[i].balance << "\n";
								write.close();
								close_account();
							}
							else
							{
								cout << "\n\t********** Request Cancelled  ************\n\n";
								close_account();

							}
							break;
						}

						else if (i == c - 1)
						{
							cout << "\n\t**** Invalid LOGIN ID ****\n\n";

							bool che = false;
							do {
								cout << "\n\tPlease select your choice" << endl;
								cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
								char l;
								cin >> l;
								if (l == '1')
								{
									goto again_input;
									che = false;
								}
								else
								{
									che = false;
								}
							} while (che);
						}
					}
					check = false;
				}
				else
				{
					cout << "\n\tPlease enter a valid choice ";
					check = true;
				}

			} while (check);
		}
	}
	void close_account_company()
	{
	view_a:
		system("CLS");
		ifstream obj;
		obj.open("Bank\\company_blocked.txt");
		int c = 0;
		string a, b;
		while (getline(obj, b))
		{
			c++;
		}
		obj.close();
		obj.open("Bank\\company_blocked.txt");
		if (c == 0)
		{
			cout << "\n\t***** No Accounts data *****\n\n";
			getchar();
		}
		else
		{
			bool check = false;
			do {
				cout << "\n\tPlease select your choice" << endl;
				cout << "\n\tPress 1 to Close Blocked Accounts Permenently       \n";
				cout << "\n\tPress 2 to Restore Blocked Accounts       \n";

				char l;
				cin >> l;
				if (l == '1')
				{
					system("CLS");

					company* arr = new company[c];
					cout << "  \tUser ID     \t Name\t     Address\t     Tax Number\t     UserName\t     Balance\t     Reason" << endl << endl;
					for (int i = 0; i < c; i++)
					{
						getline(obj, a, ',');
						arr[i].c_user_id = stoi(a);
						cout << "\t   " << arr[i].c_user_id << "\t      ";
						getline(obj, a, ',');
						arr[i].c_name = a;
						cout << a << "\t      ";
						getline(obj, a, ',');
						arr[i].c_address = a;
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].c_tax_num = stoll(a);
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].login_id = a;
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].password = a;
						getline(obj, a, ',');
						arr[i].withdrawal_limit = stoll(a);
						getline(obj, a, ',');
						arr[i].pin_check = stoi(a);
						getline(obj, a, '\n');
						arr[i].balance = stoll(a);
						cout << a << "\t";
						cout << "Wrong Card Pin" << endl;
						cout << endl;
					}

					obj.close();
				login_input:

					cout << "\n\tPlease enter the User ID from the above to Close the account \n";
					string id;
					cin.ignore();
					getline(cin, id);

					for (int i = 0; i < c; i++)
					{
						if (stoi(id) == arr[i].c_user_id)
						{

							cout << "\n\t**** Are you sure *****" << endl;
							cout << "\n\tPress 1 Continue        Press anykey to Cancel\n";
							char us;
							cin >> us;
							if (us == '1')
							{
								cout << "\n\t********** Account Successfully Closed  ************\n\n";
								company* temp = new company[c - 1];
								for (int x = 0, j = 0; j < c; j++)
								{
									if (j == i)
									{
										continue;
									}
									else
									{
										temp[x].c_user_id = arr[j].c_user_id;
										temp[x].c_address = arr[j].c_address;
										temp[x].balance = arr[j].balance;
										temp[x].c_tax_num = arr[j].c_tax_num;
										temp[x].c_name = arr[j].c_name;
										temp[x].withdrawal_limit = arr[j].withdrawal_limit;
										temp[x].password = arr[j].password;
										temp[x].login_id = arr[j].login_id;
										temp[x].pin_check = arr[j].pin_check;
										x++;

									}
								}

								ofstream fraud;
								fraud.open("Bank\\company_blocked.txt");
								for (int z = 0; z < c - 1; z++)
								{
									fraud << temp[z].c_user_id << ",";
									fraud << temp[z].c_name << ",";
									fraud << temp[z].c_address << ",";
									fraud << temp[z].c_tax_num << ",";
									fraud << temp[z].login_id << ",";
									fraud << temp[z].password << ",";
									fraud << temp[z].withdrawal_limit << ",";
									fraud << temp[z].pin_check << ",";
									fraud << temp[z].balance << "\n";
								}
								fraud.close();
								close_account_company();
							}
							else
							{
								cout << "\n\t********** Request Cancelled  ************\n\n";
								close_account_company();
							}
							break;
						}

						else if (i == c - 1)
						{
							cout << "\n\t**** Invalid LOGIN ID ****\n\n";
							bool che = false;
							do {
								cout << "\n\tPlease select your choice" << endl;
								cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
								char l;
								cin >> l;
								if (l == '1')
								{
									goto login_input;
									che = false;
								}
								else
								{
									che = false;
								}
							} while (che);
						}
					}
					check = false;
				}
				else if (l == '2')
				{
					system("CLS");

					company* arr = new company[c];
					cout << "  \tUser ID     \t Name\t     Address\t     Tax Number\t     UserName\t     Balance\t     Reason" << endl << endl;
					for (int i = 0; i < c; i++)
					{

						getline(obj, a, ',');
						arr[i].c_user_id = stoi(a);
						cout << "\t   " << arr[i].c_user_id << "\t      ";
						getline(obj, a, ',');
						arr[i].c_name = a;
						cout << a << "\t      ";
						getline(obj, a, ',');
						arr[i].c_address = a;
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].c_tax_num = stoll(a);
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].login_id = a;
						cout << a << "\t     ";
						getline(obj, a, ',');
						arr[i].password = a;
						getline(obj, a, ',');
						arr[i].withdrawal_limit = stoll(a);
						getline(obj, a, ',');
						arr[i].pin_check = stoi(a);
						getline(obj, a, '\n');
						arr[i].balance = stoll(a);
						cout << a << "\t";
						cout << "Wrong Card Pin" << endl;
						cout << endl;
					}
					obj.close();
				again_input:

					cout << "\n\tPlease enter the User ID from the above to Restore account \n";
					string id;
					cin.ignore();
					getline(cin, id);
					for (int i = 0; i < c; i++)
					{
						if (stoi(id) == arr[i].c_user_id)
						{

							cout << "\n\t**** Are you sure *****" << endl;
							cout << "\n\tPress 1 Continue        Press anykey to Cancel\n";
							char us;
							cin >> us;
							if (us == '1')
							{
								arr[i].pin_check = 3;
								cout << "\n\t********** Account Successfully Restored  ************\n\n Press any key to continue\n\n";
								getchar();
								company* temp = new company[c - 1];
								for (int x = 0, j = 0; j < c; j++)
								{
									if (j == i)
									{
										arr[j].pin_check = 3;
										continue;
									}
									else
									{
										temp[x].c_user_id = arr[j].c_user_id;
										temp[x].c_address = arr[j].c_address;
										temp[x].balance = arr[j].balance;
										temp[x].c_tax_num = arr[j].c_tax_num;
										temp[x].c_name = arr[j].c_name;
										temp[x].withdrawal_limit = arr[j].withdrawal_limit;
										temp[x].password = arr[j].password;
										temp[x].login_id = arr[j].login_id;
										temp[x].pin_check = arr[j].pin_check;
										x++;
									}
								}
								ofstream fraud;
								fraud.open("Bank\\company_blocked.txt");
								for (int z = 0; z < c - 1; z++)
								{
									fraud << temp[z].c_user_id << ",";
									fraud << temp[z].c_name << ",";
									fraud << temp[z].c_address << ",";
									fraud << temp[z].c_tax_num << ",";
									fraud << temp[z].login_id << ",";
									fraud << temp[z].password << ",";
									fraud << temp[z].withdrawal_limit << ",";
									fraud << temp[z].pin_check << ",";
									fraud << temp[z].balance << "\n";
								}
								fraud.close();
								ofstream write;
								write.open("Company\\companies.txt", ios::app);
								write << arr[i].c_user_id << ",";
								write << arr[i].c_name << ",";
								write << arr[i].c_address << ",";
								write << arr[i].c_tax_num << ",";
								write << arr[i].login_id << ",";
								write << arr[i].password << ",";
								write << arr[i].withdrawal_limit << ",";
								write << arr[i].pin_check << ",";
								write << arr[i].balance << "\n";
								write.close();
								close_account_company();
							}
							else
							{
								cout << "\n\t********** Request Cancelled  ************\n\n";
								close_account_company();
							}
							break;
						}
						else if (i == c - 1)
						{
							cout << "\n\t**** Invalid LOGIN ID ****\n\n";

							bool che = false;
							do {
								cout << "\n\tPlease select your choice" << endl;
								cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
								char l;
								cin >> l;
								if (l == '1')
								{
									goto again_input;
									che = false;
								}
								else
								{
									che = false;
								}
							} while (che);
						}
					}
					check = false;
				}
				else
				{
					cout << "\n\tPlease enter a valid choice ";
					check = true;
				}

			} while (check);
		}
	}
	void view_account_details()
	{
	view_again:
		system("CLS");
		bool check = false;
		do {
			cout << "\t For which account Type you want to View Details " << endl;
			cout << "\t\tSelect your choice" << endl;
			cout << "\n\t\t1 for  User Accounts      2 for  Company Accounts   " << endl;
			char l;
			cin >> l;
			if (l == '1')
			{
				system("CLS");
				ifstream obj;
				obj.open("User\\user.txt");
				int c = 0;
				string a, b;
				while (getline(obj, b))
				{
					c++;
				}
				obj.close();
				User* arr = new User[c];
				obj.open("User\\user.txt");
				cout << "User ID    \tName\t      Address\t     CNIC\t      UserName\t     Password\t   Balance" << endl << endl;
				for (int i = 0; i < c; i++)
				{
					getline(obj, a, ',');
					arr[i].user_id = stoi(a);
					cout << a << "\t      ";
					getline(obj, a, ',');
					arr[i].name = a;
					cout << a << "\t       ";
					getline(obj, a, ',');
					arr[i].address = a;
					cout << a << "\t     ";
					getline(obj, a, ',');
					arr[i].cnic = stoll(a);
					cout << a << "\t    ";
					getline(obj, a, ',');
					arr[i].login_id = a;
					cout << a << "\t      ";
					getline(obj, a, ',');
					arr[i].password = a;
					cout << a << "\t        ";
					getline(obj, a, ',');
					getline(obj, a, ',');
					getline(obj, a, '\n');
					arr[i].withdrawal_limit = stoll(a);
					cout << a << "\n";
					cout << endl;
				}

				obj.close();
				bool new_check = false;
				do {
					cout << "\n\tPlease select your choice" << endl;
					cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
					char us;
					cin >> us;
					if (us == '1')
					{
						goto view_again;
						new_check = false;
					}
					else
					{
						new_check = false;
					}
				} while (new_check);
			}
			else if (l == '2')
			{
				system("CLS");
				ifstream obj;
				obj.open("Company\\companies.txt");
				int c = 0;
				string a;
				while (getline(obj, a))
				{
					c++;
				}
				obj.close();
				company* arr = new company[c];

				obj.open("Company\\companies.txt");
				cout << "User ID     Company Name     \tCompany Address   \tCompany Tax Number    \tCompany UserName     \tPassword    \tBalance" << endl << endl;
				for (int i = 0; i < c; i++)
				{
					getline(obj, a, ',');
					cout << a << "          ";
					getline(obj, a, ',');
					cout  << a << "\t\t     ";
					getline(obj, a, ',');
					cout << a << "\t\t  ";
					getline(obj, a, ',');
					cout << a << "\t\t         ";
					getline(obj, a, ',');
					cout << a << "\t\t     ";
					getline(obj, a, ',');
					cout << a << "\t\t     ";
					getline(obj, a, ',');
					getline(obj, a, ',');
					getline(obj, a, '\n');
					cout << a << "\n";
					cout << endl;
				}
				obj.close();
				bool new_check = false;
				do {
					cout << "\n\tPlease select your choice" << endl;
					cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
					char us;
					cin >> us;
					if (us == '1')
					{
						goto view_again;
						new_check = false;
					}
					else
					{
						new_check = false;
					}
				} while (new_check);
				check = false;
			}
			else
			{
				cout << "\n\tPlease enter a valid choice ";
				check = true;
			}
		} while (check);

	}
	void delete_loan_req(company*& temp, int id)
	{
		ifstream read;
		read.open("Bank\\loan_req.txt");
		string a;
		int count = 0;
		while (getline(read, a))
		{
			count++;
		}
		read.close();
		company* arr = new company[count - 1];
		for (int i = 0,j=0; i < count; i++)
		{
			if (id == temp[i].c_user_id)
			{
				continue;
			}
			else
			{
				arr[j].c_user_id = temp[i].c_user_id;
				arr[j].c_name = temp[i].c_name;
				arr[j].loan = temp[i].loan;
				j++;
			}
		}
		ofstream write;
		write.open("Bank\\loan_req.txt");
		string b;
		for (int i = 0; i < count - 1; i++)
		{
			write << arr[i].c_user_id << ",";
			write << arr[i].c_name << ",";
			write << arr[i].loan << "\n";
		}
		write.close();

	}
	void loan_req(company*& arr )
	{
		ifstream read;
		read.open("Bank\\loan_req.txt");
		string f,a;
		int count = 0;
		while (getline(read, f))
		{
			count++;
		}
		read.close();
		int size_arr = 0;
		ifstream obj;
		obj.open("Company\\companies.txt");
		string b;
		while (getline(obj, b))
		{
			size_arr++;
		}
		obj.close();
		read.open("Bank\\loan_req.txt");
		bool temp_check = true;
		company* temp = new company[count ];
		for (int k = 0; k < count; k++)
		{
			getline(read, a, ',');
			for (int i = 0; i < size_arr; i++)
			{
				if (stoi(a) == arr[i].c_user_id)
				{
					temp[k].c_user_id = arr[i].c_user_id;
					temp[k].c_name = arr[i].c_name;
					temp[k].c_address = arr[i].c_address;
					temp[k].c_tax_num = arr[i].c_tax_num;
					temp[k].login_id = arr[i].login_id;
					temp[k].password = arr[i].password;
					temp[k].withdrawal_limit = arr[i].withdrawal_limit;
					temp[k].pin_check = arr[i].pin_check;
					temp[k].balance = arr[i].balance;
					getline(read, a, ',');
					getline(read, a, '\n');
					temp[k].loan = stoll(a);
					temp_check = false;
				}
			}
			if (temp_check)
			{
				getline(read, a, ',');
				getline(read, a, '\n');
			}
		}
		read.close();
		cout << "User ID     Company Name     \tCompany Address   \tCompany Tax Number    \tCompany UserName     \t Loan Ammount Requested" << endl << endl;
		for (int i = 0; i < size_arr; i++)
		{
			cout << temp[i].c_user_id << ")   ";
			cout << "\t" << temp[i].c_name << "\t\t";
			cout << temp[i].c_address << "\t\t\t";
			cout << temp[i].c_tax_num << "\t\t\t";
			cout << temp[i].login_id << "\t\t\t";
			cout << temp[i].loan << "\n";
			cout << endl;
		}
	c_input:
		cout << "\n\tPlease enter the Company User ID from the above to Accept/reject the Request \n";
		string id;
		cin.ignore();
		getline(cin, id);

		for (int i = 0; i < count; i++)
		{
			if (stoi(id) == temp[i].c_user_id)
			{
				bool l_c = false;
				do {
					cout << "\n\tPlease select your choice" << endl;
					cout << "\n\tPree 1 to accept Request     Press 2 To Reject Rquest \n";
					char l;
					cin >> l;
					if (l == '1')
					{
						for (int q = 0; q < size_arr; q++)
						{
							if (stoi(id) == arr[q].c_user_id)
							{
								arr[q].balance += temp[i].loan;
								company save_obj;
								save_obj.save_data(arr, q);
								break;
							}
						}
						system("CLS");
						cout << "\n\n\t\t********** Loan Amount added to Company's Account Successfully ***********\n\n";
						bank_employee obj;
						obj.delete_loan_req(temp, stoi(id));
						bool new_check = false;
					
					}
					else if (l == '2')
					{
						system("CLS");
						cout << "\n\n\t\t********** User's Loan Request has been Rejected Successfullyy ***********\n\n";
						bank_employee obj;
						obj.delete_loan_req(temp, stoi(id));
						bool new_check = false;
						l_c = false;
					}
					else
					{
						cout << "\n\tPlease enter a valid choice ";
						l_c = true;
					}
				} while (l_c);
				break;
			}
			else if (i == count - 1)
			{
				cout << "\n\t**** Invalid LOGIN ID ****\n\n";
				bool che = false;
				do {
					cout << "\n\tPlease select your choice" << endl;
					cout << "\tPress 1 to enter again    and    Press Any key to go to menu\n";
					char l;
					cin >> l;
					if (l == '1')
					{
						goto c_input;
						che = false;
					}
					else
					{
						che = false;
					}
				} while (che);
			}
		}
	}
	void view_transactions_company(int user_id)
	{
		Transaction* arr = nullptr;
		ifstream file;
		file.open("Bank\\company_transactions.txt");
		int count1 = 0;
		string a, b;
		while (getline(file, b))
		{
			count1++;
		}
		arr = new Transaction[count1];
		file.close();
		bool check = true;
		string c;
		int comma_count = 0;

		for (int i = 0; i < count1; i++)
		{
			file.open("Bank\\company_transactions.txt");
			for (int j = 0; j < i + 1; j++)
			{
				getline(file, c);
				comma_count = count(c.begin(), c.end(), ',');
			}
			file.close();
			file.open("Bank\\company_transactions.txt");
			for (int j = 0; j < i; j++)
			{
				getline(file, a);
			}
			if (comma_count == 3)
			{
				getline(file, a, '-');
				arr[i].day = stoi(a);
				getline(file, a, '-');
				arr[i].mon = stoi(a);
				getline(file, a, ',');
				arr[i].year = stoi(a);
				getline(file, a, ',');
				arr[i].id = stoi(a);
				getline(file, a, ',');
				arr[i].amount = stoll(a);
				getline(file, a, '\n');
				arr[i].type = a;

			}
			else if (comma_count == 4)
			{
				getline(file, a, '-');
				arr[i].day = stoi(a);
				getline(file, a, '-');
				arr[i].mon = stoi(a);
				getline(file, a, ',');
				arr[i].year = stoi(a);
				getline(file, a, ',');
				arr[i].id = stoi(a);
				getline(file, a, ',');
				arr[i].amount = stoll(a);
				getline(file, a, ',');
				arr[i].type = a;
				getline(file, a, '\n');
				arr[i].transfer_id = stoi(a);
			}
			file.close();
		}
		for (int i = 0; i < count1; i++)
		{
			if (arr[i].id == user_id)
			{
				check = false;
			}
		}
		if (check)
		{
			cout << "\n\t***** No Transaction History Available *******\n\n";
		}
		else
		{
			system("CLS");
			cout << "  \t Transaction Date \t     ID \t     Amount \t     Transaction Type \t     Transfer ID" << endl << endl;
			for (int i = 0; i < count1; i++)
			{
				if (arr[i].id == user_id)
				{
					cout << "  \t " << arr[i].day << "-" << arr[i].mon << "-" << arr[i].year;
					cout << "  \t\t    " << arr[i].id;
					cout << "  \t\t    " << arr[i].amount;
					cout << "  \t\t    " << arr[i].type;
					if (arr[i].transfer_id > 0)
					{
						cout << "  \t\t    " << arr[i].transfer_id << endl << endl;
					}
					else
					{
						cout << endl << endl;
					}
				}
			}
		}
	}
	void emplyee_menu()
	{
		bool l_c = false;
		do {
			cout << "\n******* Press Any key to continue ********\n";
			getchar();
			system("CLS");
			cout << "\n\tPlease select your choice" << endl;
			cout << "\n\t1) View List of all clients Accounts\n";
			cout << "\n\t2) View New Accounts Requests\n";
			cout << "\n\t3) View Transaction History \n";
			cout << "\n\t4) Restore and close Blocked Accounts\n";
			cout << "\n\t5) View Loan Requests \n";
			cout << "\n\t6) Exit\n";
			char l;
			cin >> l;
			 if (l == '1')
			{
				system("CLS");
				view_account_details();
				l_c = true;
			}
			else if (l == '2')
			{
				view_request_of_new_account();
				l_c = true;
			}
			else if (l == '3')
			{
				 bool inner_check = false;
				 system("CLS");
				 do {
					 cout << "\n\t1) View Company CLients Transaction History\n\t2) View User Clients Transaction History\n\n";
					 char l;
					 cin >> l;
					 if (l == '1')
					 {
						 cout << "\n\tPlease enter the Company ID to check their Transaction history      ";
						 int id;
						 cin >> id;
						 cout << "\n\t***** Press any key to continue *******\n";
						 getchar();
						 system("CLS");
						 view_transactions_company(id);
						 inner_check = false;
					 }
					 else if (l == '2')
					 {
						 cout << "\n\tPlease enter the USER ID of the user to check his Transaction history      ";
						 int id;
						 cin >> id;
						 cout << "\n\t***** Press any key to continue *******\n";
						 getchar();
						 system("CLS");
						 view_transactions(id);
						 inner_check = false;
					 }
					 else
					 {
						 cout << "\n\tPlease enter a valid choice ";
						 inner_check = true;
					 }
				 } while (inner_check);
				l_c = true;
			}
			else if (l == '4')
			{
				bool inner_check = false;
				system("CLS");
				do {
					cout << "\n\t1) Close/Restore Company CLients Accounts \n\t2) Close/Restore User Clients Accounts\n\n";
					char l;
					cin >> l;
					if (l == '1')
					{
						cout << "\n\t***** Press any key to continue *******\n";
						getchar();
						system("CLS");
						close_account_company();
						inner_check = false;
					}
					else if (l == '2')
					{
						cout << "\n\t***** Press any key to continue *******\n";
						getchar();
						system("CLS");
						close_account();
						inner_check = false;
					}
					else
					{
						cout << "\n\tPlease enter a valid choice ";
						inner_check = true;
					}
				} while (inner_check);
				l_c = true;
			}
			else if (l == '5')
			 {
				 system("CLS");
				 company obj;
				 company* arr;
				 obj.load_data(arr);
				 loan_req(arr);
				 l_c = true;
			 }
			else if (l == '6')
			 {
				 system("CLS");
				 cout << "\n\t********** Have a Good Day **********\n\n";
				 exit(0);
				 l_c = false;
			 }
			else
			{
				cout << "\n\tPlease enter a valid choice ";
				l_c = true;
			}
		} while (l_c);
	}
};
void login_menu()
{
	system("CLS");
	cout << "\t\t1) Login as User client\n";
	cout << "\t\t2) Login as Company client\n";
	cout << "\t\t3) Login as Banking Employee\n";
}
void main_menu()
{
	cout << "\n\t\t********** Welcome to ABC Bank Pvt Limited Banking Application **********\n\n";
	cout << "\t\t1) Login \n";
	cout << "\t\t2) SignUP\n";
	cout << "\t\t3) Exit\n";
}
int check_dual_login(User* arr, string u, string p)
{
	string a;
	ifstream f1;
	f1.open("User\\user.txt");
	int size_arr = 0;
	while (getline(f1, a))
	{
		size_arr++;
	}
	f1.close();
	bool check = false;
	ifstream r;
	r.open("Company\\companies_employees.txt");
	string y,z;
	int s = 0;
	while (getline(r, z))
	{
		s++;
	}
	r.close();
	int** emp_arr = new int* [s];
	for (int k = 0; k < s; k++)
	{
		emp_arr[k] = new int[2];
	}
	r.open("Company\\companies_employees.txt");
	for (int a = 0; a < s; a++)
	{
		for (int b = 0; b < 2; b++)
		{
			getline(r, y, ',');
			emp_arr[a][b] = stoi(y);
			b++;
			getline(r, y, '\n');
			emp_arr[a][b] = stoi(y);
		}
	}
	r.close();
	int company_id;
	for (int i = 0; i < size_arr; i++)
	{
		if (arr[i].login_id == u)
		{
			if (arr[i].password == p)
			{
				for (int a = 0; a < s; a++)
				{
					if (arr[i].user_id == emp_arr[a][0])
					{		
						company_id = emp_arr[a][1];
						check = true;
						break;
					}
				}
			}
		}
	}
	if (check)
	{
		return company_id;
	}
	else
	{
		return 0;
	}
}
void login_code()
{
	char choice;
	login_menu();
	string u, p;
	bool choice_check = false;
	do {
		cout << "\t\tEnter your choice\n";
		cin >> choice;
		// choice 1 USER LOGIN
		if (choice == '1')
		{
			system("CLS");

			cout << "\n\tPlease enter your Username \t";
			cin >> u;
			cout << "\n\tPlease enter your Password \t";
			cin >> p;
			User* arr = nullptr;
			User obj;
			int size_arr = 0;
			obj.load_data(arr);
			bool login_check = obj.login(arr, u,p );
			if (login_check)
			{
			successfulY_logged_in:
				cout << "\n\t\t******* SUCCESSFULLY LOGGED IN ******** \n";
				int company_id = check_dual_login(arr, u, p);
				if (company_id!=0)
				{
					cout << "\n\t***** Press any key to continue *******\n";
					getchar();
					system("CLS");
					bool p_check = false;
					do {
						cout << "\n\t1) Login As User Client\n\t2) Login as Company Client\n";
						char choice_x;
						cin >> choice_x;
						if (choice_x == '1')
						{
							User obj;
							obj.view_menu(arr, u, p);
							p_check = false;
						}
						else if (choice_x == '2')
						{
							company* arr_com = nullptr;
							company obj_com;
							obj_com.load_data(arr_com);
							string m;
							ifstream f11;
							f11.open("Company\\companies.txt");
							int size_com_arr = 0;
							while (getline(f11, m))
							{
								size_com_arr++;
							}
							f11.close();
							string log_in,pass_word;
							for (int k = 0; k < size_com_arr; k++)
							{
								if (arr_com[k].c_user_id == company_id)
								{
									log_in = arr_com[k].login_id;
									pass_word = arr[k].password;
									break;
								}
							}
							obj_com.view_menu(arr_com, log_in, pass_word);
							p_check = false;
						}
						else
						{
							cout << "\n\tPlease enter a valid choice\n\t";
							p_check = true;
						}

					} while (p_check);
				}

				else
				{
					User obj;
					obj.view_menu(arr, u, p);
				}
			}
			else
			{
				do {
					cout << "\n\tPlease enter 1 to login again    and       Enter 2 to return to menu \n";
					char again;
					cin >> again;
					if (again == '1')
					{
						system("CLS");
						cout << "\n\t******* Please enter your credentials again \t\n";
						cout << "\n\tPlease enter your Username \t";
						cin >> u;
						cout << "\n\tPlease enter your Password \t";
						cin >> p;
						login_check = obj.login(arr, u, p);
						if (login_check)
						{
							goto successfulY_logged_in;
						}
					}
					else if (again == '2')
					{
						system("CLS");
						login_check = true;
					}
					else
					{
						cout << "\n\tPlease enter a valid choice ";
					}
				} while (!login_check);
			}
			choice_check = false;
		}
		// choice 2 COMPSNY LOGIN
		else if (choice == '2')
		{
			system("CLS");

			cout << "\n\tPlease enter Company's Username \t";
			cin >> u;
			cout << "\n\tPlease enter Company's Password \t";
			cin >> p;
			company* arr = nullptr;
			company obj;
			int size_arr = 0;
			obj.load_data(arr);
			bool login_check = obj.login(arr, u, p);
			if (login_check)
			{
			company_logged_in:
				cout << "\n\t\t******* SUCCESSFULLY LOGGED IN ******** \n";
				company obj;
				obj.view_menu(arr, u, p);
			}
			else
			{
				do {
					cout << "\n\tPlease enter 1 to login again      and      Enter 2 to return to menu \n";
					char again;
					cin >> again;
					if (again == '1')
					{
						system("CLS");
						cout << "\n\t******* Please enter your credentials again \t\n";
						cout << "\n\tPlease enter your Username \t";
						cin >> u;
						cout << "\n\tPlease enter your Password \t";
						cin >> p;
						login_check = obj.login(arr, u, p);
						if (login_check)
						{
							goto   company_logged_in;
						}
					}
					else if (again == '2')
					{
						system("CLS");
						login_check = true;
					}
					else
					{
						cout << "\n\tPlease enter a valid choice ";
					}
				} while (!login_check);
			}
			choice_check = false;
		}
		// choice 3 BANK's EMPLOYEEE LOGIN
		else if (choice == '3')
		{
			system("CLS");

			cout << "\n\tPlease enter your Bank's Username \t";
			cin >> u;
			cout << "\n\tPlease enter your  Password \t";
			cin >> p;
			bank_employee* arr = nullptr;
			bank_employee obj;
			int size_arr = 0;
			obj.load_data(arr);
			bool login_check = obj.login(arr, u, p);
			if (login_check)
			{
			bank_logged_in:
				cout << "\n\t\t******* SUCCESSFULLY LOGGED IN ******** \n";
				bank_employee obj;
				obj.emplyee_menu();
			}
			else
			{
				do {
					cout << "\n\tPlease enter 1 to login again      and      Enter 2 to return to menu\n";
					char again;
					cin >> again;
					if (again == '1')
					{
						system("CLS");
						cout << "\n\t******* Please enter your credentials again \t\n";
						cout << "\n\tPlease enter your Bank's Username \t";
						cin >> u;
						cout << "\n\tPlease enter your Password \t";
						cin >> p;
						login_check = obj.login(arr, u, p);
						if (login_check)
						{
							goto bank_logged_in;
						}
					}
					else if (again == '2')
					{
						system("CLS");
						login_check = true;
					}
					else
					{
						cout << "\n\tPlease enter a valid choice ";

					}
				} while (!login_check);
			}

			choice_check = false;
		}
		// wrong choice  
		else
		{
			cout << "\n\tPlease enter a valid choice\t\n";

			choice_check = true;
		}
	} while (choice_check);
}
void signup_code()
{
	cout << "\n\t****** FOR WHICH TYPE YOU WANT TO SIGN UP \n\n";
	cout << "\t\t1) Sign Up as User client\n";
	cout << "\t\t2) Sign Up as Company client\n";
	char choice1;
	bool choice_check1 = false;
	do
	{
		cout << "\t\tEnter your choice\n";
		cin >> choice1;
		if (choice1 == '1')
		{
			system("CLS");
			User obj;
			obj.sign_up();
			bank_employee req;
			req.new_req_user(obj);
			choice_check1 = false;
			getchar();
		}
		else if (choice1 == '2')
		{

			system("CLS");
			company obj;
			obj.sign_up();
			bank_employee req;
			req.new_req_company(obj);
			choice_check1 = false;
			getchar();
		}
		else
		{
			cout << "\n\tPlease enter a valid choice\t\n";

			choice_check1 = true;
		}
	} while (choice_check1);
}
int main()
{
	char choice1;
	bool choice_check1 = false;
	do
	{
		main_menu();
		cout << "\t\tEnter your choice\n";
		cin >> choice1;
		if (choice1 == '1')
		{
			system("CLS");
			login_code();
			cout << "\n\t***** Press any key to continue *******\n";
			getchar();
			system("CLS");
			choice_check1 = true;
		}
		else if (choice1 == '2')
		{
			system("CLS");
			signup_code();
			cout << "\n\t***** Press any key to continue *******\n";
			getchar();
			system("CLS");
			choice_check1 = true;
		}
		else if (choice1 == '3')
		{
			cout << "\n\t******** Thanks for Using Our Banking App *********";
			choice_check1 = false;
		}
		else
		{
			cout << "\n\tPlease enter a valid choice\t\n";

			choice_check1 = true;
		}
	} while (choice_check1);
}