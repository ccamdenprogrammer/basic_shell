#include <iostream>
#include <string>

using namespace std;


void display_help() {
    printf("*********************************************************\n");
    printf("\ncfc26s\n");
    printf("CSC360/660 Operating Systems\n");
    printf("Project #1: My Shell - Writing Your Own Shell\n");
    printf("This shell supports the following commands: help, exit, history\n");
    printf("//*********************************************************\n");
}

int main()
{
    string bearID = "cfc26s";
    string cmd;
    string errMSG = "||ERROR||~~~";
    
    while(1)
    {
        cout << bearID << "$ ";
        cin >> cmd;

        if(cmd == "exit")
        {
            break;
        }
        else if(cmd == "help")
        {
            display_help();
        }
        else
        {
            cout<< errMSG << "command not recognized" << endl;
        }


    }
    cout<< "Shell exited succesfully.";
    
    return 0;
}

