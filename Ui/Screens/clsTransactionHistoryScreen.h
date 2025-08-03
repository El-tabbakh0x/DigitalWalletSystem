#pragma once
#include <iostream>
#include <iomanip>
#include"../clsScreen.h"
#include "../../Core/clsWallet.h"
#include "../../Core/Global.h"

class clsTransactionHistoryScreen :protected clsScreen
{
private:

    static void PrintTransactionHistoryRecordLine(clsWallet::stTrnsferLogRecord TransactionHistor)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransactionHistor.DateTime;
        cout << "| " << setw(8) << left << TransactionHistor.SourceWallet;
        cout << "| " << setw(8) << left << TransactionHistor.DestinationWallet;
        cout << "| " << setw(8) << left << TransactionHistor.Amount;
        cout << "| " << setw(10) << left << TransactionHistor.srcBalanceAfter;
        cout << "| " << setw(10) << left << TransactionHistor.destBalanceAfter;
    }

public:
    static void ShowTransactionHistoryScreen()
    {


        vector <clsWallet::stTrnsferLogRecord> vTransactionHistor = clsWallet::GetTransfersLogList();

        string Title = "\tTransaction History List Screen";
        string SubTitle = "\t    (" + to_string(vTransactionHistor.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Wallet";
        cout << "| " << left << setw(8) << "d.Wallet";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransactionHistor.size() == 0)
            cout << "\t\t\t\tNo Transaction Histor Available In the System!";
        else
            for (clsWallet::stTrnsferLogRecord Record : vTransactionHistor)
            {
                PrintTransactionHistoryRecordLine(Record);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

};

