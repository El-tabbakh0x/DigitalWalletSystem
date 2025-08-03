#pragma once
#include <iostream>
#include <iomanip>
#include"../clsScreen.h"
#include "../../Core/clsWallet.h"
#include "../../Core/Global.h"


class clsViewWalletDataScreen:protected clsScreen
{
private:
	static void _PrintWalletData(clsWallet CurrentWallet)
	{
		cout << setw(37) << left << "" << "FullName  :" << CurrentWallet.FullName() <<"\n";
		cout << setw(37) << left << "" << "Wallet ID :" << CurrentWallet.WalletID() <<"\n";
		cout << setw(37) << left << "" << "Phone     :" << CurrentWallet.Phone <<"\n";
		cout << setw(37) << left << "" << "Emaile    :" << CurrentWallet.Email <<"\n";
		cout << setw(37) << left << "" << "Password  : " << CurrentWallet.PinCode << "\n";
		cout << setw(37) << left << "" << "Balance   :" << CurrentWallet.AccountBalance <<"\n";

	}
public:
	static void ViewWalletDataAndBalance()
	{
		system("cls");
		string Title = " Wallet Data Screen ";
		_DrawScreenHeader(Title);

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << " " << "\t\t\t Wallet Data & Balance\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PrintWalletData(CurrentClientWallet);
		cout << setw(37) << left << "" << "===========================================\n";
	}
};

