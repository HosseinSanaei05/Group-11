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


int main() {
    dbinfo DATA;
    int choice;
    string tableName, columnName, columnType;
    char start;

    do {
        // منوی اصلی
        cout << "\nMain Menu:" << endl;
        cout << "1. Create new table" << endl;
        cout << "2. Display all tables" << endl;
        cout << "3. Add new record" << endl;
        cout << "4. Search records" << endl;
        cout << "5. Update record" << endl;
        cout << "6. Delete record" << endl;
        cout << "7. Delete table" << endl;
        cout << "8. Exit" << endl;

        // دریافت ورودی از کاربر
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                cout << "Enter table name: ";
                cin >> tableName;  //  دریافت اسم جدول از کاربر
                schema newTable(tableName);

                int columnsCount;
                cout << "Enter number of columns: ";// دریافت تعداد ستون ها 
                cin >> columnsCount;   // دریافت تعداد ستون ها از کاربر
                // حلقه برای دریافت ستون ها از کاربر
                for (int i = 0; i < columnsCount; ++i) {
                    cout << "Enter column " << i + 1 << " name: ";
                    cin >> columnName;
                    cout << "Enter column " << i + 1 << " data type: ";
                    cin >> columnType;
                    newTable.addColumn(columnName, columnType);
                }
                DATA.addSchema(newTable); // ساخت جدول
                cout << "Table created successfully!" << endl;
                break;
            }
            case 2:
                DATA.display_AllTable();  // اینجا تمام جداول و ستون‌ها نمایش داده می‌شود
                break;
            case 3:
                cout << "Add new record (not implemented)" << endl;
                break;
            case 4:
                cout << "Search records (not implemented)" << endl;
                break;
            case 5:
                cout << "Update record (not implemented)" << endl;
                break;
            case 6:
                cout << "Delete record (not implemented)" << endl;
                break;
            case 7:// دستور حذف جدول
                cout << "Enter table name to delete: ";
                cin >> tableName;
                if (DATA.deleteTable(tableName)) {
                    cout << "Table deleted successfully!" << endl;
                } else {
                    cout << "Table not found!" << endl; //در صورت موجود نبودن جدول
                }
                break;
            case 8:
                cout << "Exiting..." << endl; //پیام خروج از برنامه 
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        cout << "\nEnter key '+' to display main menu again, or any other key to exit: ";
        cin >> start;
    } while (choice != 8 && start == '+'); // دستور برای نمایش دوباره منو یا خاتمه برنامه

    return 0;
}



