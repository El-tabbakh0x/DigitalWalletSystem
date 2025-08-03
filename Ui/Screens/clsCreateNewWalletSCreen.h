#include <iostream>
#include "../clsScreen.h"
#include "../../Core/clsWallet.h"
#include "../../Util/clsInputValidate.h"
#include <iomanip>

class clsCreateNewWalletSCreen: protected clsScreen
{
private:
    static void _ReadWalletInfo(clsWallet& Wallet)
    {
        cout << "\nEnter FirstName: ";
        Wallet.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Wallet.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Wallet.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Wallet.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        Wallet.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Wallet.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

    static void _PrintClient(clsWallet Wallet)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Wallet.FirstName;
        cout << "\nLastName    : " << Wallet.LastName;
        cout << "\nFull Name   : " << Wallet.FullName();
        cout << "\nEmail       : " << Wallet.Email;
        cout << "\nPhone       : " << Wallet.Phone;
        cout << "\nPassword    : " << Wallet.PinCode;
        cout << "\nBalance     : " << Wallet.AccountBalance;
        cout << "\n___________________\n";

    }

public:
	static void CreateNewWalletSCreen()
	{
		system("cls");
		string Title = "Create New Wallet SCreen";
		_DrawScreenHeader(Title);
        string WalletID;
        cout << "\nPlease Enter Wallet ID: ";
        WalletID = clsInputValidate::ReadString();
        while (clsWallet::IsWalletExist(WalletID))
        {
            cout << "\n Wallet ID Is Already Used, Choose another one:  ";
            WalletID = clsInputValidate::ReadString();
        }
        clsWallet NewWallet = clsWallet::GetCreateNewWalletObject(WalletID);
        _ReadWalletInfo(NewWallet);
        clsWallet::enSaveResults SaveResult;

        SaveResult = NewWallet.Save();

        switch (SaveResult)
        {
        case  clsWallet::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewWallet);
            break;
        }
        case clsWallet::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsWallet::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }
	}
};

