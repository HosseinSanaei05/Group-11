#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class column {
protected:
    string columnName;
    string dataType;
    bool isValide;

public:
    column(string Name, string Type) {
        columnName = Name;
        dataType = Type;
        isValide = true;  // مقداردهی اولیه به isValide
    }

    //برای دریافت اسم ستون ها  gettr 
    string getColumnName() const {
        return columnName;
    }

    //برای دریافت تایپ ستون ها  gettr 
    string getDataType() const {
        return dataType;
    }

    bool getIsValide() const {
        return isValide;
    }

    friend class dbinfo;
};

class schema {
public:
    string tableName;
    vector<column> Columns;

    schema(string Name) {
        tableName = Name;
    }

    void addColumn(string name, string type) {
        Columns.push_back(column(name, type));
    }

    void display()
     { 
        cout << "Table: " << tableName << "\n-------------------" << endl;
        cout << "Columns:" << endl;
        for (const auto& COLUMN : Columns) {
            cout<< COLUMN.getColumnName()
                 << " (" << COLUMN.getDataType() << ")" << endl;
        }
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    friend class dbinfo;
};

class dbinfo {
private:
    vector<schema> schemas;

public:
    void addSchema(const schema& s) {
        schemas.push_back(s);
    }

    bool tableExists(string name) {
        for (const auto& s : schemas) {
            if (s.tableName == name) return true;
        }
        return false;
    }

    bool deleteTable(string name) {
        for (auto it = schemas.begin(); it != schemas.end(); ++it) {
            if (it->tableName == name) {
                schemas.erase(it);
                return true;
            }
        }
        return false;
    }

    void displayTable(string name) {
        for (auto& s : schemas) {
            if (s.tableName == name) {
                s.display();  
                return;
            }
        }
        cout << "No table found with name: " << name << endl;
    }

    void listTables() {
        cout << "\nAvailable Tables:\n";
        for (auto& s : schemas) {
            cout << "- " << s.tableName << endl;
            cout << "  Columns:\n";
            for (const auto& col : s.Columns) {
                cout << "   * " << col.getColumnName() << " (" << col.getDataType() << ")" << endl;
            }
            cout << "------------------------" << endl;
        }
    }
    
};

int main() {
    dbinfo Q;
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
                cin >> tableName;
                schema newTable(tableName);

                int columnsCount;
                cout << "Enter number of columns: ";
                cin >> columnsCount;

                for (int i = 0; i < columnsCount; ++i) {
                    cout << "Enter column " << i + 1 << " name: ";
                    cin >> columnName;
                    cout << "Enter column " << i + 1 << " data type: ";
                    cin >> columnType;
                    newTable.addColumn(columnName, columnType);
                }
                Q.addSchema(newTable);
                cout << "Table created successfully!" << endl;
                break;
            }
            case 2:
                Q.listTables();  // اینجا تمام جداول و ستون‌ها نمایش داده می‌شود
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
            case 7:
                cout << "Enter table name to delete: ";
                cin >> tableName;
                if (Q.deleteTable(tableName)) {
                    cout << "Table deleted successfully!" << endl;
                } else {
                    cout << "Table not found!" << endl;
                }
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        cout << "\nEnter key '+' to display main menu again, or any other key to exit: ";
        cin >> start;
    } while (choice != 8 && start == '+'); // دستور برای نمایش دوباره منو یا خاتمه برنامه

    return 0;
}
