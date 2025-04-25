#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

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
private:
    vector<schema> schemas;

public:
    void addSchema(const schema& s) {   // استفاده از &  برای جلوگیری از کپی غیر ضروری
        schemas.push_back(s);
    }
   // تابع برای بررسی وجود جدول
    bool tableExists(string name) {
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
