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
    string table;
    cout << "Enter table name to insert record into: ";
    cin >> table;
  
    if (db.tableExists(table)==false) {
        cout <<"eror!\n" <<"Table not found!" << endl;
        return;
    }
  
    vector<string> data;
    string value;
    cout << "Enter data for the record (type 'end' to finish):\n";
  
    while (true) {
        cout << "Enter value (or 'end'): ";
        cin >> value;
        if (value == "end") break;
        data.push_back(value);
    }
  
    records[table].push_back(Record(table, data));
    cout << "Record inserted successfully!" << endl;
      }

    };
