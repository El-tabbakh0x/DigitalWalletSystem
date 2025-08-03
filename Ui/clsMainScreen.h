#pragma once
#include<iostream>
#include<iomanip>
#include"../Util/clsInputValidate.h"
#include"clsScreen.h"
#include"Screens/clsCreateNewWalletSCreen.h"
#include"Screens/clsAccessExistingWalletScreen.h"


class clsMainScreen:protected clsScreen
{
private:
	enum enMainMenueOptions
	{
		eCreateNewWallet=1, eAccessExistingWallet=2,eExit=3
	};
	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 3]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 3, "Enter Number between 1 to 3? ");
		return Choice;
	}
	static  void _GoBackToMainMenu()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowMainMenu();
	}

	static void _ShowCreateNewWalletScreen()
	{
		/*cout << "Create New Wallet Screen ";*/
		clsCreateNewWalletSCreen::CreateNewWalletSCreen();
	}
	static void _ShowAccessExistingWalletScreen()
	{
		//cout << "Access Existing Wallet Screen ";
		while (true)
		{
			if (!clsAccessExistingWalletScreen::AccessExistingWallet())
			{
				break;
			}
		}

	}
	static void _ShowExitScreen()
	{
		cout << "Exit Screen \n";
		cout << "Thank You \n";
	}

	static void _PerfromMainMenuOption(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMainMenueOptions::eCreateNewWallet:
			{
				system("cls");
				_ShowCreateNewWalletScreen();
				_GoBackToMainMenu();
				break;
			}
		case enMainMenueOptions::eAccessExistingWallet:
			{
				system("cls");
				_ShowAccessExistingWalletScreen();
				_GoBackToMainMenu();
				break;
			}
		case enMainMenueOptions::eExit:
			{
				system("cls");
				_ShowExitScreen();
				break;
			}

		}
	}
public:
	static void ShowMainMenu()
	{
		system("cls");
		string Title = "Digital Wallet System";
		_DrawScreenHeader(Title);

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "[1] Create New Wallet" << endl;
		cout << setw(37) << left << "" << "[2] Access Existing Wallet" << endl;
		cout << setw(37) << left << "" << "[3] Exit" << endl;
		cout << setw(37) << left << "" << "===========================================\n";
		_PerfromMainMenuOption((enMainMenueOptions)_ReadMainMenueOption());
	}
	


};

