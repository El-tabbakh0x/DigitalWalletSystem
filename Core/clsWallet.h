#pragma once
#include <iostream>
#include <string>
#include "clsUtil.h"
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

class clsWallet:public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string  _WalletID;
    string  _PinCode;
    float  _AccountBalance;
    bool   _MarkedForDelete = false;

    static clsWallet _ConvertLinetoWalletObject(string Line, string Seperator = "#//#")
    {
        vector<string> vWalletData;
        vWalletData = clsString::Split(Line, Seperator);

        return clsWallet(enMode::UpdateMode, vWalletData[0], vWalletData[1], vWalletData[2],
            vWalletData[3], clsUtil::DecryptText(vWalletData[4]), vWalletData[5], stod(vWalletData[6]));

    }

    static string _ConverWalletObjectToLine(clsWallet WalletData, string Seperator = "#//#")
    {

        string stWalletDataRecord = "";
        stWalletDataRecord += WalletData.FirstName + Seperator;
        stWalletDataRecord += WalletData.LastName + Seperator;
        stWalletDataRecord += WalletData.Email + Seperator;
        stWalletDataRecord += WalletData.Phone + Seperator;
        stWalletDataRecord += clsUtil::EncryptText (WalletData.PinCode) + Seperator;
        stWalletDataRecord+= WalletData.WalletID() + Seperator;
        stWalletDataRecord += to_string(WalletData.AccountBalance);

        return stWalletDataRecord;

    }

    static  vector <clsWallet> _LoadWalletsDataFromFile()
    {

        vector <clsWallet> vWallets;

        fstream MyFile;
        MyFile.open("WalletsData.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsWallet Wallet = _ConvertLinetoWalletObject(Line);

                vWallets.push_back(Wallet);
            }

            MyFile.close();

        }

        return vWallets;

    }

    static void _SaveWalletsDataToFile(vector <clsWallet> vClients)
    {

        fstream MyFile;
        MyFile.open("WalletsData.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsWallet C : vClients)
            {
                if (C.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverWalletObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsWallet> _vWallet;
        _vWallet = _LoadWalletsDataFromFile();

        for (clsWallet& W : _vWallet)
        {
            if (W.WalletID() == WalletID())
            {
                W = *this;
                break;
            }

        }
        _SaveWalletsDataToFile(_vWallet);
    }
    void _AddNew()
    {
        _AddDataLineToFile(_ConverWalletObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("WalletsData.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }
    static clsWallet _GetEmptyClientObject()
    {
        return clsWallet(enMode::EmptyMode, "", "", "", "", "","", 0);
    }
   
    struct stTrnsferLogRecord;

    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTrnsferLogRecord TrnsferLogRecord;

        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceWallet = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationWallet = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);

        return TrnsferLogRecord;

    }


    string _PrepareTransferLogRecord(float Amount, clsWallet DestinationWallet, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += WalletID() + Seperator;
        TransferLogRecord += DestinationWallet.WalletID() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationWallet.AccountBalance) + Seperator;
        return TransferLogRecord;
    }
 
   void _RegisterTransferLog(float Amount, clsWallet DestinationWallet)
    {
        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationWallet);
        fstream MyFile;
        MyFile.open("TransfersLog.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }    

public:
    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceWallet;
        string DestinationWallet;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
    };
    clsWallet(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string PinCode, string WalletID,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _PinCode = PinCode;
        _WalletID = WalletID;
        _AccountBalance = AccountBalance;
    }
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    string WalletID()
    {
        return _WalletID;
    }
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    
    static clsWallet Find(string WalletID)
    {
        fstream MyFile;
        MyFile.open("WalletsData.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsWallet Wallet= _ConvertLinetoWalletObject(Line);
                if (Wallet.WalletID() == WalletID)
                {
                    MyFile.close();
                    return Wallet;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
   
    static clsWallet Find(string WalletID, string PinCode)
    {
        fstream MyFile;
        MyFile.open("WalletsData.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsWallet Wallet = _ConvertLinetoWalletObject(Line);
                if (Wallet.WalletID() == WalletID && Wallet.PinCode == PinCode)
                {
                    MyFile.close();
                    return Wallet;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }
        case enMode::UpdateMode:
        {
            _Update();
           return enSaveResults::svSucceeded;
            break;
        }
        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsWallet::IsWalletExist(_WalletID))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
        }
    }

    static bool IsWalletExist(string WaiietID)
    {

        clsWallet Wallet1 = clsWallet::Find(WaiietID);
        return (!Wallet1.IsEmpty());
    }
    static bool IsWalletExist(string WaiietID,string PinCode)
    {

        clsWallet Wallet1 = clsWallet::Find(WaiietID, PinCode);
        return (!Wallet1.IsEmpty());
    }

    bool Delete()
    {
        vector <clsWallet> _vWallet;
        _vWallet = _LoadWalletsDataFromFile();

        for (clsWallet& W : _vWallet)
        {
            if (W.WalletID() == _WalletID)
            {
                W._MarkedForDelete = true;
                break;
            }

        }

        _SaveWalletsDataToFile(_vWallet);

        *this = _GetEmptyClientObject();

        return true;

    }

    static clsWallet GetCreateNewWalletObject(string WalletID)
    {
        return clsWallet(enMode::AddNewMode, "", "", "", "","", WalletID, 0);
    }

    static vector <clsWallet> GetClientsList()
    {
        return _LoadWalletsDataFromFile();
    }


    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }


    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
        }

    }

    static double GetTotalBalances()
    {
        vector <clsWallet> vWallet = clsWallet::GetClientsList();

        double TotalBalances = 0;

        for (clsWallet Wallet : vWallet)
        {

            TotalBalances += Wallet.AccountBalance;
        }

        return TotalBalances;
    }
  
    bool Transfer(float Amount, clsWallet& DestinationWallet)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationWallet.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationWallet);
        return true;
    }
    
    static  vector <stTrnsferLogRecord> GetTransfersLogList()
    {
        vector <stTrnsferLogRecord> vTransferLogRecord;
        fstream MyFile;
        MyFile.open("TransfersLog.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            stTrnsferLogRecord TransferRecord;
            while (getline(MyFile, Line))
            {
                TransferRecord = _ConvertTransferLogLineToRecord(Line);
                vTransferLogRecord.push_back(TransferRecord);
            }
            MyFile.close();
        }
        return vTransferLogRecord;
    }
    
    
  
};

