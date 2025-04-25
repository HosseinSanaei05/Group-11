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
class column {
protected:
    string columnName;
    string dataType;

public:
//constructor for class column
    column(string Name, string Type) {  
        columnName = Name;
        dataType = Type;
        
    }

   
    string getColumnName() const {return columnName;} //برای دریافت اسم ستون ها  getter 

    
    string getDataType() const {return dataType;}//برای دریافت تایپ ستون ها  getter 
    
 
    friend class dbinfo;
};

class schema {
public:
    string tableName;
    vector<column> Columns;
//constructor for class schema 
    schema(string Name) {
        tableName = Name;
    }

     

// تابع برای ساخت ستون ها 
    void addColumn(string name, string type) {
        Columns.push_back(column(name, type));
    }
     

    friend class dbinfo;
};



class dbinfo   {
public:
    vector<schema> schemas;


    void addSchema(const schema& s) {   // استفاده از &  برای جلوگیری از کپی غیر ضروری
        schemas.push_back(s);
    }
   // تابع برای بررسی وجود جدول
    bool tableExists(string name) const {
        for (const auto& s : schemas) {
            if (s.tableName == name) 
            return true;
        }
        return false;
    }
   // تابع برای حذف جدول
    bool deleteTable(string name) {
        for (auto it = schemas.begin(); it != schemas.end(); ++it) {  // بررسی همه ی جدول ها تا پیدا کردن اسم جدول مورد نظر برای حذف
            if (it->tableName == name) {  //(*it).tableName = it->tableName 
                schemas.erase(it); // حذف میشود erase زمانی که جدول پیدا شد توسط دستور  
                return true;
            }
        }
        return false;
    }

     
   // تابع چاپ جدول ها به همراه ستون ها و تایپ هر ستون 
    void display_AllTable() {
        int test=1; // متغیر برای دادن پیام به کاربر در صورت وجود نداشتن هیچ جدولی
        cout << "\nAvailable Tables:\n"<<"========================\n";
        for (auto& s : schemas) { //   ریخته و سپس هر جز را جداگانه چاپ میکند s این حلقه تمام اطلاعات جدول ها رو داخل متغیر   
            cout << "Tablename: " << s.tableName << endl;
            cout << "  Columns:\n";
            // گرفته و چاپ میکند column  از کلاس getter میریزد و سپس اطلاعات هر ستون رو با استفاده از colاین حلقه تمام ستون ها  را داخل متغیر 
            for (const auto& col : s.Columns) { 
                cout << "=> " << col.getColumnName() << " (" << col.getDataType() << ")" << endl;
                test=0;
            }
            cout << "------------------------" << endl;
        }
           if(test)
           cout<<"No table found !!!";
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

        // پیدا کردن شماره ستون
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

        // ویرایش رکوردها
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
    int main() {
        dbinfo Q;
    

    schema student("student");
    student.addColumn("ID", "int");
    student.addColumn("Name", "string");
    student.addColumn("age", "int");
    Q.addSchema(student);

    schema teacher("teacher");
    teacher.addColumn("name", "string");
    teacher.addColumn("age", "int");
    teacher.addColumn("email", "string");
    Q.addSchema(teacher);

    DataBase DB;
    DB.setDBInfo(&Q); 

    DB.insertRecord("student", 1, "Ali", "21");
    DB.insertRecord("student", 2, "Behnam", "20");
    DB.insertRecord("teacher", "Hossein", "35", "hossein12@gmail.com");

    DB.findRecords("student", "Name", "Ali");
    DB.findRecords("teacher", "name", "Hossein");

    DB.updateRecord("student", "Name", "Ali", "Reza");  
    DB.updateRecord("teacher", "email", "hossein12@gmail.com", "hossein_updated@gmail.com");  

    DB.deleteRecord("student", 1);  

    Q.deleteTable("teacher");

    Q.display_AllTable();

    return 0;
    }
    
