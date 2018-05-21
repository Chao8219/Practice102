#include <iostream>
#include<fstream>
#include <chrono>
#include <thread>
using namespace std;

int i=0;
string selection,username,cellphone,zipcode,getUsername;
string line;
string number_instring;
int number;
ofstream WriteFile;
ifstream ReadFile;

class SimpleAccount
{
public:
    int ReadLine()
    {
        ReadFile.open ("Account.csv");
        if (ReadFile.is_open())
        {
            ReadFile.seekg(-3,ios::end);
            number_instring=ReadFile.get();
            number=stoi(number_instring,nullptr,0);
        }
        else
        {
            cout<<"\n"<<"Creating Account File Right Now..."<<endl;
            WriteFile.open("Account.csv");
            WriteFile<<"Username"<<","<<"Cellphone Number"<<","<<"Zip Code"<<","<<"No."<<endl;
            WriteFile.close();
            number=0;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout<<"Done! Now you can type in the service you may want!"<<endl;
        }
        ReadFile.close();
        return number;
    }

    void CreateEverything(string& name,string& cell,string& zip)
    {
        i++;
        WriteFile.open("Account.csv",fstream::app);
        WriteFile<<name<<","<<cell<<","<<zip<<","<<i<<endl;
        WriteFile.close();
    }
};

int main()
{
    SimpleAccount Account;
    while(1)
    {
        cout<<"Please select the service."<<endl;
        cout<<"1.Create a new account;"<<endl;
        cout<<"2.Read an account;"<<endl;
        cout<<"3.Exit."<<endl<<endl;
        cout<<"Please type in your selection: ";
        //cout<<Account.ReadLine();
        i=Account.ReadLine();
        getline(cin,selection);

        if(selection=="1")
        {
            cout<<"Please type in username: ";
            getline(cin,username);
            cout<<"Please type in cellphone number: ";
            getline(cin,cellphone);
            cout<<"Please type in your zipcode: ";
            getline(cin,zipcode);
            cout<<"Transmitting..."<<endl;
            Account.CreateEverything(username,cellphone,zipcode);
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout<<"You are all set!"<<endl<<endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout<<"What else can I help you?"<<endl<<endl;
        }
        else if(selection=="2")
        {
            bool findit=false;
            cout<<"Please type in the username: ";
            getline(cin,getUsername);
            ReadFile.open("Account.csv");
            if (ReadFile.is_open())
            {
                size_t pos;

                while(ReadFile.good())
                {
                    getline(ReadFile,line);
                    pos=line.find(getUsername);
                    if(pos!=string::npos)
                    {
                        findit=true;
                        cout<<"Found!"<<endl;
                        this_thread::sleep_for(std::chrono::milliseconds(500));
                        cout<<"User Info is as follow: ";
                        cout<<line<<endl<<endl;
                        this_thread::sleep_for(std::chrono::milliseconds(500));
                        break;
                    }
                }
            }
            else
            {
                cout<<"\n"<<"Creating Account File Right Now..."<<endl;
                WriteFile.open("Account.csv");
                WriteFile<<"Username"<<","<<"Cellphone Number"<<","<<"Zip Code"<<","<<"No."<<endl;
                WriteFile.close();
                this_thread::sleep_for(std::chrono::milliseconds(1000));
                cout<<"Done! Now you can type in the service you may want!"<<endl;
            }
            ReadFile.close();
            if(findit==false)
            {
                cout<<"No such name is found in the file."<<endl<<endl;
            }
        }
        else if(selection=="3")
        {
            break;
        }
        else
        {
            cout<<"Please select again."<<endl;
        }
    }
    WriteFile.close();
    ReadFile.close();
    return 0;
}
