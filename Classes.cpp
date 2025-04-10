#include <iostream>
#include<map>
#include<string>
#include<vector>
using namespace std;

class column
{
protected:
string columnName;
string dataType ;
bool isValide;
public:
column (string col_Name , string  dt_Type)
{
   columnName=col_Name;
    dataType=dt_Type;
}

public:
    string getColumnName() {
        return columnName;
    }
    string getdataType() {
        return dataType;
    }
    string getDataType() {
        return dataType;
    }
    
    friend class dbinfo;

};

class schema
{
    public:
    
    string tableName;
    int number_columns; ;
    vector<column> Columns;

   schema (string  Name , int number )
   {
    tableName=Name ;
    number_columns=number;
    
   }

   void addColumn(string name, string type) {
    Columns.push_back(column(name, type));
}



void display (string name) {
    if (tableName == name) {
        cout << "Table: " << tableName << "\n-------------------"<<endl;
        cout << "Columns:" << endl;
        for (int i = 0; i < Columns.size(); ++i) {
            cout << "-------------------\n " << Columns[i].getColumnName()
                 << " (" << Columns[i].getDataType() << ")" <<endl;
        }
       
    cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~" <<endl;}
     else {
        cout << "No table found with name: " << name << endl;
    }
}

friend class dbinfo;

  

};

