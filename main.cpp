#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//in 'accounts' folder I save logs and in 'accounts-name' I save acc names and dept

std::string accountSelector( string );
void createAccount();
void editAccount();
void acclogs( string , int , int );
void modeSelector();


//......................................................................................................................................
void createAccount()
{
    string nameofNewAcc;

    cout << "Enter name of new account: ";
    cin >> nameofNewAcc;

    ofstream accountsname( "Accounts-name.txt", ios::app );
    if(accountsname.fail()){ cout << "ERROR!!! create account -> accountsname file = failed0"; exit(0); }
    
    accountsname << nameofNewAcc + ":0 " << endl;
    accountsname.close();
    acclogs(nameofNewAcc, 0 ,0);
}

//......................................................................................................................................
//select account and returns the name of account
std::string accountSelector( string orther )//orther = "read" or "edit"
{
    ifstream accounts( "Accounts-name.txt" );
    if(accounts.fail()){ cout << "ERROR!!! accountSelector -> accounts file = failed0"; exit(0); }
    string linePrint, choosenAcc;
    int i = 1, choosen; //counter and in the end chooser


    while( !accounts.eof() ) //print accounts names
    {
        getline( accounts, linePrint );

        cout << i << "." << linePrint << "\t";
        i++;
    }
    accounts.clear();
    accounts.seekg(0);
    cout << "\b\b\b\b\b\bback";

    cout << "\nwhich account do you want to " << orther << ": ";
    cin >> choosen;
    if (i == choosen + 1) return "back";
    i = 1;
    while( !accounts.eof() ) //select account
    {
        getline( accounts, choosenAcc );
        if ( i == choosen )
            break;
        i++;
    }
    accounts.close();
    return choosenAcc;
}

//......................................................................................................................................
void editAccount()
{
    string selectedAccount = accountSelector( "edit" );//function select and returns name of selected account and dept money
    if ( selectedAccount == "back" ) return;
    int receivedPaid;//money which you want to add
    int money;//money which already saved in account
    
    //money which paid or recieved
    cout << "1 = money paid \t 2 = money received ? ";
    do{
        cin >> receivedPaid;
        if ( receivedPaid == 1 ){
            cout << "how much? ";
            cin >> receivedPaid;
            break;
        }
        else if( receivedPaid == 2 ){
            cout << "how much? ";
            cin >> receivedPaid;
            receivedPaid *= (-1);
            break;
        }
        else cout << "Error!!! wrong input\nTry again...";
    }while (true);



    ifstream accName("Accounts-name.txt");
    if(accName.fail()){ cout << "ERROR!!! editAccount -> accName file = failed0"; exit(0); }
    std::string line, name, moneystring;
    char word= ' '; 
    vector<string> lines;
    while ( getline( accName, line ) )
    {
        if ( line == selectedAccount ){
            int i=0;
            while(word!=':'){
                name += line[i];
                i++;
                word = line[i];
            }
            while(word!=' '){
                i++;
                moneystring += line[i];
                word = line[i];
            }
            money = stoi(moneystring) + receivedPaid;
            moneystring = to_string(money);
            line = name +':'+ moneystring +" ";
        }
        lines.push_back(line);
    }
    accName.close();

    ofstream accNames("Accounts-name.txt");
    if(accNames.fail()){ cout << "ERROR!!! editAccount -> accNames file = failed0"; exit(0); }
    for (const string& j : lines) {
    accNames << j << "\n";
    }
    accNames.close();
    acclogs(name , money , receivedPaid);
}

//......................................................................................................................................
void acclogs( string name, int total, int recpaid )
{
    string year, month, day;
    if( recpaid == 0 )// create new acc 
    {
        ofstream acclog( "Accounts/"+name+".txt" );
        if(acclog.fail()){cout << "ERROR!!! acc logs function -> acclog file = failed0"; exit(0);}

        cout << "Enter date\n";
        cout<< "year: "; cin >> year;    cout<< "month: ";cin>>month;    cout << "day: ";cin>>day;
        acclog << year << "/" << month << "/" << day << endl << name << "'s account created.\n" << endl;
        acclog.close();
    }else // add log acc
    {
        ofstream acclog( "Accounts/"+name+".txt", ios::app );
        if(acclog.fail()){cout << "ERROR!!! acc logs function -> acclog file = failed1";exit(0);}

        cout << "Enter date\n";
        cout<< "year: "; cin >> year;    cout<< "month: ";cin>>month;    cout << "day: ";cin>>day;
        acclog << year << "/" << month << "/" << day << endl << to_string(recpaid) << "\nTotal:" <<to_string(total) << "\n" << endl;
        acclog.close();
    }
}

//......................................................................................................................................
void modeSelector()
{
    char mode='s';
    while( mode!='0' ){
        cout << "1.Create Account\t2.Edit Account\t0.Quit" << endl;
        cin >> mode;
        switch (mode)
        {
        case '1':
            createAccount();
            break;
        case '2':
            editAccount();
            break;
        case '0':
            exit(0);
        default:
            cout << "Wrong input!!!" << endl;
            break;
        }
    }
}

//_________________________________________________________________________________________________________________________________________

int main()
{
    modeSelector();

    return 0;
}