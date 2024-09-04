#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

void display_help() {
    cout << "*********************************************************\n";
    cout << "\ncfc26s\n";
    cout << "CSC360/660 Operating Systems\n";
    cout << "Project #1: My Shell - Writing Your Own Shell\n";
    cout << "This shell supports the following commands: help, exit, history\n";
    cout << "*********************************************************\n";
}

void display_history(int history[], int count) 
{
    for (int i = 0; i < count; ++i) 
    {
        cout << history[i] << endl;     //a simple for loop to display the history array which contains the 5 most recent processes
    }
}

int main() {
    string bearID = "cfc26s";
    string cmd; 
    int history[5];         //initialization of history array
    int history_count = 0;

    while (1) //infinite command line loop
    {
        cout << bearID << "$ ";
        getline(cin, cmd); //user command input 

        if (cmd.empty()) //if there is no command, I print the prompt again
        { 
            continue;
        }

    if (cmd == "exit") //"exit", does just that. exits!
        {
            cout << "Shell Exit" << endl;
            break;
        }

        if (cmd == "help") //help calls the display help function to display all relevant info
        {
            display_help();
            continue;
        }

        if (cmd == "history") // history calls the display history function from earlier
        {  
            display_history(history, history_count);
            continue;
        }
        
        
        //command line parsing section: help was found at: https://stackoverflow.com/questions/30415663/c-using-strtok-to-parse-command-line-inputs
        //but this has been modified to fit my own program and commented out (probably too much), for my own understanding.
        char* args[100];    //a char* array is initialized to 100 pointers
        int i = 0;  //i is set to 0
        char* tok = strtok(&cmd[0], " ");       //using strok function to convert the commands to tokens each followed by a space
        while (tok != NULL) //while the token is NOT null...
        {
        args[i++] = tok;    //I set the argument to the token and increment it.
        tok = strtok(NULL, " "); //strtok is called again to let it know to continue
        }   
        args[i] = NULL;     //The end of the array must be set to a null pointer in oder for the execvp funtion to work properly

        

        pid_t pid = fork();     //here Im creating a child process with the fork() function
        if (pid == 0) 
        {
            execvp(args[0], args);
            cout << "Error executing command" << endl; 
        }

        waitpid(pid, NULL, 0);  //parent waiting for child

        if (history_count < 5) 
        {
            history[history_count++] = pid;  
        } 
        else 
        {
            for (int i = 1; i < 5; ++i) 
            {
                history[i - 1] = history[i];  //scootching over history array to make room for new and most recent PID
            }
            history[4] = pid;
        }
        
    }

    return 0;
}

