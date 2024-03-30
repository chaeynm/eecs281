#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Column
{
public:
    string name;
    string type;
    Column(string n, string t) : name(n), type(t) {}
};

class Table
{
public:
    string name;
    vector<Column> columns;
    Table() = default;
    Table(string n, vector<Column> cols) : name(n), columns(cols) {}
};

class Database
{
public:
    unordered_map<string, Table> tables;

    void createTable(const string &cmd)
    {
        stringstream ss(cmd);
        string action, tableName;
        ss >> action >> tableName;

        int colCount;
        ss >> colCount;

        vector<Column> cols;
        for (int i = 0; i < colCount; ++i)
        {
            string colName, colType;
            ss >> colType >> colName;
            cols.emplace_back(colName, colType);
        }

        auto result = tables.insert({tableName, Table(tableName, cols)});
        if (!result.second)
        {
            cout << "Table " << tableName << " already exists." << endl;
        }
        else
        {
            cout << "New table " << tableName << " created with column(s) ";
            for (const auto &col : cols)
            {
                cout << col.name << " " << col.type << " ";
            }
            cout << endl;
        }
    }

    void removeTable(const string &tableName)
    {
        if (tables.erase(tableName) == 0)
        {
            cout << "Table " << tableName << " does not exist." << endl;
        }
        else
        {
            cout << "Table " << tableName << " removed." << endl;
        }
    }
};

void processCommand(Database &db, const string &cmd)
{
    if (cmd.empty() || cmd[0] == '#')
        return;

    stringstream ss(cmd);
    string action;
    ss >> action;

    if (action == "CREATE")
    {
        db.createTable(cmd);
    }
    else if (action == "REMOVE")
    {
        string tableName;
        ss >> tableName;
        db.removeTable(tableName);
    }
    else if (action == "QUIT")
    {
        cout << "Thanks for being silly!" << endl;
        exit(0);
    }
    else
    {
        cout << "Invalid command." << endl;
    }
}

int main()
{
    Database db;
    string cmd;

    while (true)
    {
        cout << "% ";
        getline(cin, cmd);

        // Exit condition
        if (cmd == "QUIT")
        {
            cout << "% Thanks for being silly!" << endl;
            break; // Exiting the loop and program
        }

        // Skip comments and empty lines
        if (!cmd.empty() && cmd[0] != '#')
        {
            processCommand(db, cmd);
        }
    }

    return 0;
}
