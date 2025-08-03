#pragma once
#include <iostream>
#include  <iomanip>
#include "../clsScreen.h"
#include "../../Core/clsWallet.h"
#include "../../Util/clsInputValidate.h"
#include "../../Core/Global.h"
class clsDepositMoneyScreen:protected clsScreen
{
private:

	static void _PrintWalletData(clsWallet CurrentWallet)
	{
		cout << setw(37) << left << "" << "FullName  :" << CurrentWallet.FullName() << "\n";
		cout << setw(37) << left << "" << "Wallet ID :" << CurrentWallet.WalletID() << "\n";
		cout << setw(37) << left << "" << "Balance   :" << CurrentWallet.AccountBalance << "\n";
	}
	static double _ReadAmunt()
	{
		double Amount = 0;
		cout << setw(37) << left << "" << "\nPlease Enter Deposit Amount? ";
		Amount = clsInputValidate::ReadDblNumber();
		return Amount;
	}
public:
	static void DepositMoney()
	{
		system("cls");
		string Title = " Deposit Money ";
		_DrawScreenHeader(Title);
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\t Deposit Money \n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PrintWalletData(CurrentClientWallet);
		cout << setw(37) << left << "" << "===========================================\n";
		double Amount = _ReadAmunt();
		cout  << "Are you sure you want to perform this transaction?  ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			CurrentClientWallet.Deposit(Amount);
			cout  << "Amount Deposited Successfully.\n";
			cout  << "New Balance Is: " << CurrentClientWallet.AccountBalance<<"\n";

		}
		else
		{
			cout << setw(37) << left << "" << "Operation was cancelled.\n";
		}		
	}

};

