#pragma once
#include<iostream>
#include<iomanip>
#include"../clsScreen.h"
#include "../../Core/clsWallet.h"
#include"clsWalletOperationsMenuScreen.h"
#include "../../Core/Global.h"



class clsAccessExistingWalletScreen : protected clsScreen
{
private:

	static  bool _Login()
	{
		bool LoginFaild = false;
		short FaildLoginCount = 0;

		string WalletID, Password;
		do
		{
			if (LoginFaild)
			{
				FaildLoginCount++;

				cout << "\nInvlaid WalletID/Password!";
				cout << "\nYou have " << (3 - FaildLoginCount)
					<< " Trial(s) to login.\n\n";
			}
			if (FaildLoginCount == 3)
			{
				cout << "\nYour are Locked after 3 faild trails \n\n";
				return false;
			}
			cout << "Enter Wallet ID? \n";
			cin >> WalletID;

			cout << "Enter Password? \n";
			cin >> Password;
			CurrentClientWallet = clsWallet::Find(WalletID, Password);
			LoginFaild = CurrentClientWallet.IsEmpty();

		} while (LoginFaild);
		clsWalletOperationsMenuScreen::WalletOperationsMenu();
		return true;
	}

public:
	static bool AccessExistingWallet()
	{
		system("cls");
		string Title = "Access Existing Wallet SCreen";
		_DrawScreenHeader(Title);
		return _Login();
	

	}
};






