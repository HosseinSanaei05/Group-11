#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;


struct MetaData {
   vector<string> data; 
};
class Record
{
public:

string tableName;
MetaData MetaData; 
bool isValide; 

Record(string table, vector<string> data)
: tableName(table), isValide(false) {
MetaData.data = data;
}

void displayRecord() const {
 if (!isValide) {
    cout << "Record in table '" << tableName << "': ";
      for (const auto& value : MetaData.data) {
           cout << value << " | ";
       }
       cout << endl;
   } else {
       cout << "Record is deleted." << endl;
   }
}
 
};

class DataBase
{
private:
 map<string, vector<Record>> records;

public:
void insertRecord(const dbinfo& db) {
        string table, input;

        cout << "Enter table name to insert record into: ";
        cin >> table;
        cin.ignore();

        if (!db.tableExists(table)) {
            cout << "Error! Table not found!" << endl;
            return;
        }

        vector<string> data;
        cout << "Enter record data separated by commas(,)\n";
        getline(cin, input);

        stringstream ss(input);
        string value;

        while (getline(ss, value, ',')) {
            data.push_back(value);
        }

        records[table].push_back(Record(table, data));
        cout << "Record inserted successfully!" << endl;
    }

    };
