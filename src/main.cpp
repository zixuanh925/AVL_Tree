#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "AVL.h"

//helper to validate Name: only alphabets and spaces
bool isValidName(string name)
{
    for (char c : name)
    {
        if (!isalpha(c) && !isspace(c))
        {
            return false;
        }
    }
    return !name.empty();
}

//helper to validate ID: exactly 8 digits
bool isValidID(string id)
{
    if (id.length() != 8)
    {
        return false;
    }
    for (char c : id)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    AVL tree;
    string line;
    getline(cin, line);

    if (line.empty())
    {
        return 0;
    }

    int numCommands = stoi(line);

    for (int i = 0; i < numCommands; i++)
    {
        getline(cin, line);
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "insert")
        {
            //extract name between quotes
            size_t firstQuote = line.find('"');
            size_t lastQuote = line.find('"', firstQuote + 1);

            if (firstQuote != string::npos && lastQuote != string::npos)
            {
                string name = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);
                string idStr = line.substr(lastQuote + 1);

                if (isValidName(name) && isValidID(idStr))
                {
                    tree.insert(name, stoi(idStr));
                }
                else
                {
                    cout << "unsuccessful" << endl;
                }
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else if (command == "remove")
        {
            string idStr;
            ss >> idStr;
            if (isValidID(idStr))
            {
                tree.remove(stoi(idStr));
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else if (command == "search")
        {
            string argument;
            ss >> ws;
            getline(ss, argument);

            if (argument.front() == '"' && argument.back() == '"')
            {
                //search Name
                string name = argument.substr(1, argument.length() - 2);
                tree.searchName(name);
            }
            else if (isValidID(argument))
            {
                //search ID
                tree.searchID(stoi(argument));
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else if (command == "printInorder")
        {
            tree.printInorder();
        }
        else if (command == "printPreorder")
        {
            tree.printPreorder();
        }
        else if (command == "printPostorder")
        {
            tree.printPostorder();
        }
        else if (command == "printLevelCount")
        {
            tree.printLevelCount();
        }
        else if (command == "removeInorder")
        {
            int n;
            if (ss >> n)
            {
                tree.removeInorder(n);
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }
        else
        {
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}
