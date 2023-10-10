#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


struct stClient
{
	string Number;
	string pinCode;
	string name;
	string phone;
	double balance;
};

string readAccountNumber()
{
	string AccountNumber = "";
	cout << "\n Please Enter Account Number? ";
	cin >> AccountNumber;

	return AccountNumber;
}
char readAnswerToDeleteAccount()
{
	char confirmDelete;

	cout << "Are You sure to delete This Account?y/n ";
	cin >> confirmDelete;

	return confirmDelete;

}

vector <string> LineDataToVector(string line)
{//A150#//#1234#//#Gomaa ElSherbini#//#00925365232#//#5000.000000

	vector <string> vClient;
	string delim = "#//#";
	short pos = 0;
	string clientItem = "";

	while ((pos = line.find(delim)) != -1)
	{
		clientItem = line.substr(0, pos);
		if (clientItem != "")
		{
			vClient.push_back(clientItem);
		}
		line.erase(0, pos + delim.length());
	}
	if (line != "")
	{
		vClient.push_back(line);
	}
	return vClient;
}

stClient VectorDataToStClient(vector <string> vClient)
{
	stClient client;

	client.Number = vClient[0];
	client.pinCode = vClient[1];
	client.name = vClient[2];
	client.phone = vClient[3];
	client.balance = stod(vClient[4]);

	return client;
}

vector <string> vectorStringtAccounts(string fileName)
{
	fstream Clients;
	string line;
	vector <string> vStringClients;

	Clients.open(fileName, ios::in);

	if (Clients.is_open())
	{
		while (getline(Clients, line))
		{
			if (line != "")
			{
				vStringClients.push_back(line);
			}
		}
		Clients.close();
	}
	return vStringClients;
}

string convertStAccountToStringLine(stClient clientRecord)
{
	string recordAataLine;
	string delim = "#//#";

	recordAataLine = clientRecord.Number;
	recordAataLine += delim + clientRecord.pinCode;
	recordAataLine += delim + clientRecord.name;
	recordAataLine += delim + clientRecord.phone;
	recordAataLine += delim + to_string(clientRecord.balance);

	return recordAataLine;

}

void printStClientData(stClient client)
{
	cout << "\nThe following are the eclient details:\n\n";

	cout << " Account Number:  " << client.Number << endl;
	cout << " Pin Code:  " << client.pinCode << endl;
	cout << " Name:  " << client.name << endl;
	cout << " Phone: " << client.phone << endl;
	cout << " Balance: " << client.balance << endl;

}

bool findAccountWithAccountNumber(vector <string> vStringClients, string AccountNumber, stClient &client)
{
	vector <string> vClient;
	stClient sClient;;

	for (string line : vStringClients)
	{
		sClient = VectorDataToStClient(LineDataToVector(line));
		if (sClient.Number == AccountNumber)
		{
			client = sClient;
			return 1;
		}
	}
	return 0;
}

void deleteAccountWithAccountNumber(string fileName, vector <string> vFileContent, string lineToDelete)
{
	fstream myFile;
	myFile.open(fileName, ios::out);

	if (myFile.is_open())
	{
		for (string& line : vFileContent)
		{
			if(line != lineToDelete)
				myFile << line << "\n";
		}
		myFile.close();
	}
}

void askForDeletAccount(vector <string> vStringClients, string AccountNumber, stClient client, string filName)
{
	char confirmDelete;
	string accountToDelete;

	if (findAccountWithAccountNumber(vStringClients, AccountNumber, client))
	{
		printStClientData(client);
		confirmDelete = readAnswerToDeleteAccount();

		if (confirmDelete == 'y' || confirmDelete == 'Y')
		{
			accountToDelete = convertStAccountToStringLine(client);

			deleteAccountWithAccountNumber(filName, vStringClients, accountToDelete);
			cout << "Client deleted Successfully!\n";
		}
		else
			return;
	}
	else
		cout << "\n Client with account Number (" << AccountNumber << ") Not Found!\n";
}

int main()
{
	string fileName = "clientInfo.txt";
	stClient client;
	vector <string> vStringClients = vectorStringtAccounts(fileName);
	string AccountNumber = readAccountNumber();

	askForDeletAccount(vStringClients, AccountNumber, client, fileName);






	system("pause>0");
	return 0;
}