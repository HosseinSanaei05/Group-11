#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct MetaData {
    bool isDeleted;
    string tableName;
  
 };
 class Record
 {
 public:
 MetaData MetaData; 
 vector<string> data; 
 
  Record(string table, vector<string> data){
     MetaData.tableName = table;
     MetaData.isDeleted = false;
     this->data = data;
  }
  
 };
 template <typename T>
string to_string_custom(const T& value) {
    return std::to_string(value);
}

string to_string_custom(const char* value) {
    return string(value);
}

string to_string_custom(const string& value) {
    return value;
}

class DataBase
{
private:
map<string, vector<Record>> records;
dbinfo* info = nullptr;

public:
void setDBInfo(dbinfo* dbInfo) {
    info = dbInfo;
}
template <typename... Args>
    void insertRecord(const string& table, Args... args) {
    if (records.find(table) == records.end()) {
            records[table] = {};
     }

    vector<string> data = { to_string_custom(args)... };
      records[table].push_back(Record(table, data));
           cout << "Record inserted successfully!" << endl;
    }

  void deleteRecord(const string& table, int valuekey) {
    if (records.find(table) != records.end()) {
            for (auto& record : records[table]) {
              if (stoi(record.data[0]) == valuekey && record.MetaData.isDeleted == false) {
                 record.MetaData.isDeleted = true;
                cout << "Record with id " << valuekey << " has been deleted." << endl;
                return;
         }
         }
            cout << "Record with id " << valuekey << " not found in table " << table << endl;
     } else {
            cout << "Table " << table << " does not exist." << endl;
    }
    }
    void findRecords(const string& table, const string& columnName, const string& targetValue) {
        if (!info || !info->tableExists(table)) {
            cout << "Table '" << table << "' does not exist." << endl;
            return;
        }

  int columnIndex = -1;
   for (const auto& schema : info->schemas) {
     if (schema.tableName == table) {
     for (size_t i = 0; i < schema.Columns.size(); ++i) {
       if (schema.Columns[i].getColumnName() == columnName) {
             columnIndex = i;
             break;
 }
  }
  }
    }

        if (columnIndex == -1) {
            cout << "Column '" << columnName << "' not found in table '" << table << "'." << endl;
            return;
        }

        bool found = false;
        for (const auto& record : records[table]) {
            if (!record.MetaData.isDeleted && record.data[columnIndex] == targetValue) {
                found = true;
                cout << ">> ";
                for (const auto& val : record.data) {
                    cout << val << " ";
                }
                cout << endl;
            }
        }

        if (!found) {
            cout << "No matching records found." << endl;
        }
    }
    void updateRecord(const string& table, const string& columnName, const string& oldValue, const string& newValue) {
        if (!info || !info->tableExists(table)) {
            cout << "Table '" << table << "' does not exist." << endl;
            return;
        }

    int columnIndex = -1;
    for (const auto& schema : info->schemas) {
      if (schema.tableName == table) {
         for (size_t i = 0; i < schema.Columns.size(); ++i) {
         if (schema.Columns[i].getColumnName() == columnName) {
          columnIndex = i;
          break;
       }
     }
    }
    }

        if (columnIndex == -1) {
            cout << "Column '" << columnName << "' not found in table '" << table << "'." << endl;
            return;
        }

  bool updated = false;
     for (auto& record : records[table]) {
        if (!record.MetaData.isDeleted && record.data[columnIndex] == oldValue) {
            record.data[columnIndex] = newValue;
                updated = true;
                cout << "Record updated successfully." << endl;
            }
 }

        if (updated==false) {
            cout << "record not found to update." << endl;
        }
    }

    

    };
