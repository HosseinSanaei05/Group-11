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
public:

   void insertRecord(){}
   void findRecords(){}
   void updateRecord (){}
   void deleteRecord(){}

    
};
