// RBT22CB035      RBT22CB026
// SWAROOP SAIKAR  AKSHAY DHUKE

#include <iostream>
#include <bits/stdc++.h>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

class ATM
{
private:
    string password;
    string name;
    string aadhar;
    string pancard;
    double balance;

public:
    string acc_no;

    void create_acc();
    void display();
    void withdraw();
    void deposit();
    void feedback();
    void show_balance();
    void del()
    {
        cout << "\t\tCOLLECT YOUR MONEY : " << balance << endl;
    }

    int check_PIN(string pin)
    {
        if (password == pin)
            return 1;
        else
            return 0;
            
    }
};

string gen_acc()
{
    ATM b;
    long long int ac;
    string s;
    fstream fp;
label:

    fp.open("atm.txt");
    srand(time(0));
    ac = rand() % 8876543210 + 8876543210;
    s = to_string(ac);

    while (!fp.eof())
    {
        fp.read(reinterpret_cast<char *>(&b), sizeof(b));
        if (s == b.acc_no)
        {
            fp.close();
            goto label;
        }
    }

    return to_string(ac);
}

void ATM::create_acc()
{

    cout << "\t\tEnter Name                                       : ";
    cin >> name;

    cout << "\t\tEnter Aadhar Number                              : ";
    cin >> aadhar;

    cout << "\t\tEnter PAN Number                                 : ";
    cin >> pancard;

    // generate account no
    acc_no = gen_acc();
    cout << "\t\tYour Generated Account Number is                 : " << acc_no << endl;

    // password
    cout << "\t\tEnter The PIN To Set (4-digit only)              : ";
    cin >> password;
    string cpassword;

    cout << "\t\tConfirm PIN                                      : ";
    cin >> cpassword;

    while (password != cpassword)
    {
        cout << "\t\tPIN Does Not Match                             ";
        cout << "\n\t\tReenter The PIN                                : ";
        cin >> password;
        cout << "\t\tConfirm The PIN                                : ";
        cin >> cpassword;
    }
    cout << "\t\t         ******* PASSWORD CONFIRMED *******" << endl;

    cout << "\n\t\tEnter The Intial Amount(Minimum Amount Rs 500) : ";
    cin >> balance;

    while (balance < 500)
    {
        cout << "\t\t       ***Insufficient Balance***";
        cout << "\t\tReenter The Amount                               : ";
        cin >> balance;
    }

    cout << "\n\t***********************     YOUR ACCOUNT IS CREATED SUCCESSFULLY     ***********************" << endl;
}

void ATM::display()
{

    cout << "\t\tNAME               :" << name << endl;
    cout << "\t\tACCOUNT NUMBER     :" << acc_no << endl;
    cout << "\t\tAadhar number is   :" << aadhar << endl;
    cout << "\t\tPANCARD NUMBER IS  :" << pancard << endl;
    cout << "\t\tBALANCE IS         :" << balance << endl
         << endl;
}

void ATM::withdraw()
{

    cout << "\t\tEnter The Amount To Withdraw : ";
    double amt;
    cin >> amt;
    cout << endl;

    if (balance - amt < 0)
    {
        cout << "\t\t*** INSUFFICIENT AMOUNT ***" << endl;
    }
    else
    {
        balance = balance - amt;
        cout << "\t\t************* AMOUNT WITHDRAW SUCCESFULLY *************";
    }
}

void ATM::deposit()
{
    cout << "\t\tEnter The Amount To Deposit : ";
    double amt;
    cin >> amt;
    cout << endl;
    balance = balance + amt;
    cout << "\t\t************* AMOUNT DEPOSITED SUCCESFULLY *************";
}

void ATM::show_balance()
{
    cout << "\n\t\tYOUR CURRENT balance : " << balance << endl
         << endl;
}

void ATM::feedback()
{
    ofstream f;
    f.open("feedback.txt", ios::app);
    string userinput;
    int count = 0;
    cout << "\t\tDo you want to Feedback (yes or no) : ";
    cin >> userinput;
    if (userinput == "yes")
    {
        f << "Feedback from " << acc_no << " : " << endl;
        cout << "\t\tEnter your Feedback (enter '0' on new line to stop) :\n";
        while (userinput != "0")
        {
            getline(cin, userinput);
            f << "\t" << userinput << endl;
            cout << "\t\t\t";
        }
        f << "\n\n";
    }
    else
    {
        cout << "\n\t\t***************** THANK YOU FOR BANKING WITH US *****************\n";
    }
    f.close();
}

int main()
{
    ATM a;
    char c;
    int ch, ch1;
    bool flag;
    fstream fp, temp;
    string search_pass = "";
    string search_acc;

    do
    {
        cout << "\n\t ______________________________________________________________________________________________";
        cout << "\n\t|                                                                                              |";
        cout << "\n\t|                          WELCOME TO ||BANK OF SPAIN||                                        |";
        cout << "\n\t|                                                                                              |";
        cout << "\n\t|______________________________________________________________________________________________|";
        cout << "\n\t|                            | |                                                               |";
        cout << "\n\t|                            * Press<1> SIGNUP                                                 |";
        cout << "\n\t|                            * Press<2> LOGIN                                                  |";
        cout << "\n\t|                            * Press<3> DELETE ACCOUNT                                         |";
        cout << "\n\t|                            * Press<4> EXIT                                                   |";
        cout << "\n\t|                            | |                                                               |";
        cout << "\n\t|______________________________________________________________________________________________|";

        cout << "\n\n\tEnter Your Choice ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            fp.open("atm.txt", ios::app);
            a.create_acc();
            fp.write(reinterpret_cast<char *>(&a), sizeof(a));
            fp.close();
            break;

        case 2:
            fp.open("atm.txt");
            fp.seekg(0);

            cout << "\t\tENTER YOUR ACCOUNT NUMBER : ";
            cin >> search_acc;

            search_pass = "";
            cout << "\t\tENTER THE PASSWORD : ";
            for (int i = 0; i <= 4; i++)
            {
                c = _getch();
                if (i != 4)
                {
                    cout << "*";
                    search_pass = search_pass + c;
                }
            }
            cout << endl;

            flag = false;

            while (!fp.eof())
            {
                fp.read(reinterpret_cast<char *>(&a), sizeof(a));
                if (search_acc == a.acc_no)
                {
                    if (a.check_PIN(search_pass) == 1)
                        flag = true;
                    break;
                }
            }

            if (flag)
            {

                cout << "\n\t\t\t\t| |  LOGIN SUCCESSFULLY  | |";

                do
                {
                    cout << "\n\t ______________________________________________________________________________________________|";
                    cout << "\n\t|                                                                                              |";
                    cout << "\n\t|                          WELCOME TO ||BANK OF SPAIN||                                        |";
                    cout << "\n\t|                                                                                              |";
                    cout << "\n\t|______________________________________________________________________________________________|";
                    cout << "\n\t|                ----------------------------------------                                      | ";
                    cout << "\n\t|                |  |  |                                |                                      | ";
                    cout << "\n\t|                |  * Press<1> DISPLAY ACCOUNT DETAILS  |                                      |";
                    cout << "\n\t|                |  * Press<2> DEPOSIT AMOUNT IN ATM    |                                      |";
                    cout << "\n\t|                |  * Press<3> WITHDRAW AMOUNT          |                                      |";
                    cout << "\n\t|                |  * Press<4> DISPLAY BALANCE          |                                      |";
                    cout << "\n\t|                |  * Press<5> Exit                     |                                      |";
                    cout << "\n\t|                |  |  |                                |                                      |";
                    cout << "\n\t|                ----------------------------------------                                      |";
                    cout << "\n\t|______________________________________________________________________________________________|";

                    cout << "\n\n\tEnter Your Choice : ";
                    cin >> (ch1);

                    switch (ch1)
                    {
                    case 1:
                        a.display();
                        break;

                    case 2:
                        a.deposit();
                        break;

                    case 3:
                        a.withdraw();
                        break;

                    case 4:
                        a.show_balance();
                        break;

                    case 5:
                        a.feedback();
                        break;

                    default:
                        cout << "\t\t** INVALID OPTION **\n\n";
                    }

                } while (ch1 != 5);
            }
            else
            {
                cout << "\n\t\t*********** INCORRECT ACCOUNT NUMBER OR PASSWORD ***********\n";
            }

            temp.open("temp.txt", ios::app);
            temp.write(reinterpret_cast<char *>(&a), sizeof(a));
            fp.seekg(0);

            while (fp.read(reinterpret_cast<char *>(&a), sizeof(a)))
            {
                if (search_acc != a.acc_no)
                    temp.write(reinterpret_cast<char *>(&a), sizeof(a));
            }

            fp.close();
            temp.close();

            remove("atm.txt");
            rename("temp.txt", "atm.txt");

            break;
        case 3:
            cout << "\t\tENTER THE ACCOUNT NUMBER TO DELETE :";
            cin >> search_acc;
            flag = false;

            fp.open("atm.txt");

            while (!fp.eof())
            {
                fp.read(reinterpret_cast<char *>(&a), sizeof(a));
                if (a.acc_no == search_acc)
                {
                    flag = true;
                }
            }
            fp.close();

            if (flag)
            {
                fp.open("atm.txt");
                temp.open("temp.txt", ios::app);

                while (!fp.eof())
                {
                    fp.read(reinterpret_cast<char *>(&a), sizeof(a));
                    if (a.acc_no != search_acc)
                    {
                        temp.write(reinterpret_cast<char *>(&a), sizeof(a));
                    }
                }

                fp.close();
                temp.close();

                remove("atm.txt");
                rename("temp.txt", "atm.txt");

                a.del();

                cout << "\n\t\t************************* ACCOUNT DELETED SUCCESSFULLY *************************\n";
            }
            else
            {
                cout << "\t\t*********************** INCORRECT ACCOUNT NUMBER ***********************";
            }
            break;

        case 4:
            cout << "\n\t******************************    BANK CLOSED    ******************************\n\n";
            break;

        default:
            cout << "\t\t** INVALID OPTION **";
        }

    } while (ch != 4);
    return 0;

}
