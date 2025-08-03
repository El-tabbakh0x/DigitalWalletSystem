#pragma once
#include<iostream>
#include<iomanip>
#include"../clsScreen.h"
#include "../../Util/clsInputValidate.h"
#include "../../Core/clsWallet.h"
#include "../../Core/Global.h"
#include "clsViewWalletDataScreen.h"
#include  "clsDepositMoneyScreen.h"
#include "clsTransferScreen.h"
#include  "clsTransactionHistoryScreen.h"

class clsWalletOperationsMenuScreen:protected clsScreen
{
private:
	enum enWalletMenuOptin
	{
		eViewBalance=1, eDepositMoney=2,eTransferMoney =3,
		eViewTransactionHistory=4,eReturntoAccessExistingWalletSCreen =5
	};
	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}
	static  void _GoBackToWalletMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Wallet Menu ...\n";

		system("pause>0");
		WalletOperationsMenu();
	}
	
	static void _ShowBalanceAndWalletDataScreen ()
	{
		//cout << "View Balance   \n ";
		clsViewWalletDataScreen::ViewWalletDataAndBalance();
	}
	static void _ShowDepositMoneyScreen()
	{
		/*cout << "Deposit Money   \n ";*/
		clsDepositMoneyScreen::DepositMoney();
	}
	static void _ShowTransferMoneyScreen()
	{
		//cout << "Transfer Money \n ";
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowViewTransactionHistorySdreen()
	{
		//cout << "View Transaction History \ ";
		clsTransactionHistoryScreen::ShowTransactionHistoryScreen();
	}
	static void _ShowReturntoMainMenuScreen() 
	{
		//ReturntoMainMenuScreen
	}
	static void _PerformWalletMenueOptions(enWalletMenuOptin WalletMenuOptin)
	{
		switch (WalletMenuOptin)
		{
		case enWalletMenuOptin::eViewBalance:
		{
			system("cls");
			_ShowBalanceAndWalletDataScreen();
			_GoBackToWalletMenue();
			break;
		}
		case enWalletMenuOptin::eDepositMoney:
		{
			system("cls");
			_ShowDepositMoneyScreen();
			_GoBackToWalletMenue();
			break;
		}
		case enWalletMenuOptin::eTransferMoney:
		{
			system("cls");
			_ShowTransferMoneyScreen();
			_GoBackToWalletMenue();
			break;
		}
		case enWalletMenuOptin::eViewTransactionHistory:
		{
			system("cls");
			_ShowViewTransactionHistorySdreen();
			_GoBackToWalletMenue();
			break;
		}
		case enWalletMenuOptin::eReturntoAccessExistingWalletSCreen:
		{
			//eReturntoAccessExistingWalletSCreen;
			break;

		}
		}
	}
public:
	static void WalletOperationsMenu()
	{
		system("cls");
		string Title = "Wallet Menu Screen";
		_DrawScreenHeader(Title);
		
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << " " << "\t\t\t Wallet Operations\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tWelcome, "<< CurrentClientWallet.FullName()
			<<"/ Wallet ID: " << CurrentClientWallet.WalletID() << "\n";
		cout << setw(37) << left << "" << "[1] View Balance & Wallet Data \n";
		cout << setw(37) << left << "" << "[2] Deposit Money   \n";
		cout << setw(37) << left << "" << "[3] Transfer Money \n";
		cout << setw(37) << left << "" << "[4] View Transaction History \n";
		cout << setw(37) << left << "" << "[5] Return to Access Existing Wallet SCreen\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerformWalletMenueOptions((enWalletMenuOptin)_ReadMainMenueOption());


		

	}
};


