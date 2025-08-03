#pragma once
#include <iostream>
#include  <iomanip>
#include "../clsScreen.h"
#include "../../Core/clsWallet.h"
#include "../../Util/clsInputValidate.h"
#include "../../Core/Global.h"

class clsTransferScreen :protected clsScreen
{
private:
    static void _PrintWalletData(clsWallet CurrentWallet)
    {
        cout << setw(37) << left << "" << "FullName  :" << CurrentWallet.FullName() << "\n";
        cout << setw(37) << left << "" << "Wallet ID :" << CurrentWallet.WalletID() << "\n";
        cout << setw(37) << left << "" << "Balance   :" << CurrentWallet.AccountBalance << "\n";
    }
    static float _ReadAmount(clsWallet CurrentWallet)
    {
        float Amount;
        cout << "\nEnter Transfer Amount? ";
        Amount = clsInputValidate::ReadFloatNumber();
        while (Amount > CurrentWallet.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }
    static string _ReadWalletID()
    {
        string WalletID;
        cout << "\nPlease Enter Wallet ID to Transfer to: ";
        WalletID = clsInputValidate::ReadString();
        while (!clsWallet::IsWalletExist(WalletID))
        {
            cout << "\nWallet ID is not found, choose another one: ";
            WalletID = clsInputValidate::ReadString();
        }
        return WalletID;
    }

public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\tTransfer Screen");
        _PrintWalletData(CurrentClientWallet);
        clsWallet DestinationWallet = clsWallet::Find(_ReadWalletID());
        _PrintWalletData(DestinationWallet);
        float Amount = _ReadAmount(CurrentClientWallet);
        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (CurrentClientWallet.Transfer(Amount, DestinationWallet))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }
        _PrintWalletData(CurrentClientWallet);
        cout << setw(37) << left << "" << "----------------------" << "\n";

        _PrintWalletData(DestinationWallet);
    }
};

