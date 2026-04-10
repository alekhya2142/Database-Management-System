#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

class Record{
    public:
        vector<string> fields;

        Record(vector<string> values) {
            fields = values;
        }

        void display(const vector<string>& columns) const{
            for(size_t i = 0; i < fields.size(); i++){
                cout << columns[i] << ": " << fields[i] << " ";
            }
            cout << endl;
        }
};

class Table{
    public:
        string name;
        vector<string> columns;
        vector<Record> records;
        
        Table(string tableName, vector<string> cols){
            name = tableName;
            columns = cols;
        }

        void insertRecord(vector<string> values){
            if(values.size() != columns.size()) {
                cout << "Error: Column count mismatch!" << endl;
                return;
            }
            records.push_back(Record(values));
            cout << "Record inserted successfully!" << endl;
        }

        void display() {
            cout << "\n--- Table: " << name <<" ---\n";
            for(auto& rec: records){
                rec.display(columns);
            }
        }

        void search(string column, string value){
            int colIndex = -1;
            for(size_t i = 0; i < columns.size(); i++){
                if(columns[i] == column) {
                    colIndex = i;
                    break;
                }
            }
            if(colIndex == -1){
                cout << "Column not found!" << endl;
                return;
            }

            cout << "\n--- Search Results ---\n";
            bool found = false;
            for(auto& rec: records) {
                if(rec.fields[colIndex] == value) {
                    rec.display(columns);
                    found = true;
                }
            }
            if(!found) cout << "No matching records found!" << endl;
        }
};

class Database{
    public:
        vector<Table> tables;

        void createTable(string name, vector<string> cols){
            tables.push_back(Table(name, cols));
        cout << "Table ' " << name << " ' created successfully!" << endl;
        }

        Table* getTable(string name) {
            for(auto& t : tables){
                if(t.name ==  name) return &t;
            }
            cout << "Table not found!" << endl;
            return nullptr;
        }
};

int main(){
    Database db;
    int choice;

    do{
        cout << "\n********************************************\n";
        cout << "Databases Mangement System\n";
        cout << "\n********************************************\n";
        cout << "1. Create Table\n";
        cout << "2. Insert Records\n";
        cout << "3. Display Table\n";
        cout << "4. Search Records\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if(choice == 1){
            string tableName;
            int colCount;
            cout << "Enter table name: ";
            getline(cin, tableName);
            cout << "Enter number of columns: ";
            cin >> colCount;
            cin.ignore();

            vector<string> cols;
            for(int i = 0; i < colCount; i++){
                string col;
                cout << "Enter column" << i+1 << " name: ";
                getline(cin, col);
                cols.push_back(col);
            }
            db.createTable(tableName, cols);

        } else if(choice == 2){
            string tableName;
            cout << "Enter table name: ";
            getline(cin, tableName);
            Table* t = db.getTable(tableName);
            if(t){
                vector<string> values;
                for(auto& col : t->columns){
                    string val;
                    cout << "Enter value for " << col << ": ";
                    getline(cin, val);
                    values.push_back(val);
                }
                t->insertRecord(values);
            }
        } else if(choice == 3){
            string tableName;
            cout << "Enter table name: ";
            getline(cin, tableName);
            Table* t = db.getTable(tableName);
            if(t) t->display();

        } else if(choice == 4){
            string tableName, column, value;
            cout << "Enter table name: ";
            getline(cin, tableName);
            Table* t = db.getTable(tableName);
            if(t){
                cout << "Enter column name to search: ";
                getline(cin,column);
                cout << "Enter value to search: ";
                getline(cin, value);
                t->search(column, value);
            }
        } else if(choice == 5){
            cout << "Exiting program..." << endl;
        } else {
            cout << "Invalid choice!" << endl;
        }
    } while(choice != 5);

    return 0;
}
