#include <iostream>
#include <vector>
using namespace std;







// دالة لطباعة المصفوفة
void printTableau(const vector<vector<double>>& tableau) {
       cout << "--------------------------\n";
    for (const vector<double>& row : tableau) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
    cout << "--------------------------\n";
}






// دالة للبحث عن العمود المناسب للاختيار كعامود بيفوت
int findPivotColumn(const vector<vector<double>>& tableau) {
    const vector<double>& objectiveRow = tableau[tableau.size() - 1];
    int pivotColumn = -1;
    double minCoefficient = 0;

    for (int j = 0; j < objectiveRow.size() - 1; j++) {
        if (objectiveRow[j] < minCoefficient) {
            minCoefficient = objectiveRow[j];
            pivotColumn = j;
        }
    }

    return pivotColumn;
}









// دالة للبحث عن الصف المناسب للاختيار كصف بيفوت
int findPivotRow(const vector<vector<double>>& tableau, int pivotColumn) {
    int pivotRow = -1;
    double minRatio = numeric_limits<double>::max();

    for (int i = 0; i < tableau.size() - 1; i++) {
        if (tableau[i][pivotColumn] > 0) {
            double ratio = tableau[i][tableau[0].size() - 1] / tableau[i][pivotColumn];
            if (ratio < minRatio) {
                minRatio = ratio;
                pivotRow = i;
            }
        }
    }

    return pivotRow;
}









// دالة لتنفيذ العملية المستدورة لتحديث المصفوفة
void pivotElement(vector<vector<double>>& tableau, int pivotRow, int pivotColumn) {
    int m = tableau.size();
    int n = tableau[0].size();

    double pivotElement = tableau[pivotRow][pivotColumn];

    for (int j = 0; j < n; j++) {
        tableau[pivotRow][j] /= pivotElement;
    }

    for (int i = 0; i < m; i++) {
        if (i != pivotRow) {
            double multiplier = tableau[i][pivotColumn];
            for (int j = 0; j < n; j++) {
                tableau[i][j] -= multiplier * tableau[pivotRow][j];
            }
        }
    }
}









int main() {

  int rows, columns;
    string objective_function;
    cout<<"enter objective function [max/min] : ";
    cin>>objective_function;
    // الحصول على عدد الصفوف والأعمدة من المستخدم
    cout << "please enter number of entry: ";
    cin >> rows;
    rows++;
    columns=2*rows-1;

    // إنشاء المصفوفة مع الأبعاد المدخلة
    vector<vector<double>> tableau(rows, vector<double>(columns));

if(objective_function=="min"){
    // جمع القيم من المستخدم
    for (int i = 0; i < rows; i++) {
        if(i==rows-1)
cout << "Please enter the objective function  :   ";       else
cout << "Please enter the entry" << i+1<< "  :   ";
    for (int j = 0; j < columns; j++) {  
            cin >> tableau[i][j];
        }
    }
}
else{
    for (int i = 0; i < rows; i++) {
        if(i==rows-1)
cout << "Please enter the objective function  :   ";       else
cout << "Please enter the entry" << i+1<< "  :   ";
    for (int j = 0; j < columns; j++) {  
            cin >> tableau[i][j];
            if(i==rows-1)
            tableau[i][j]*=-1;
        }
    } 
}

    int m = tableau.size(); // عدد الصفوف
    int n = tableau[0].size() - 1; // عدد الأعمدة (عدد المتغيرات)

    // بدء الحلقة الرئيسية للخوارزمية البسيطة
    cout<<"\n\n\n          خطوات الحل\n";
    while (true) {
        printTableau(tableau);
        int pivotColumn = findPivotColumn(tableau);
        if (pivotColumn == -1) {
            break; // جميع الأعداد في الصف الهدف غير إيجابية
        }

        int pivotRow = findPivotRow(tableau, pivotColumn);
        if (pivotRow == -1) {
            throw runtime_error("المشكلة غير محدودة.");
        }

        pivotElement(tableau, pivotRow, pivotColumn);
        
    }
    // نهاية الحلقة الرئيسية

    cout<<"\n\n\n            الناتج\n";
    for(int i=0;i<m;i++){
        if(i==m-1)
    cout<<objective_function<<"(z) : "<<tableau[i][n]<<"\n"; 
    else
    cout<<"x"<<i+1<<" : "<<tableau[i][n]<<"\n";}

    // تعديل الدالة الهدف لحساب Min(z)
    tableau[m - 1][0] = -tableau[m - 1][0];
    tableau[m - 1][1] = -tableau[m - 1][1];

    // بدء الحلقة الثانية لحساب Min(z)
    while (true) {
        int pivotColumn = findPivotColumn(tableau);
        if (pivotColumn == -1) {
            break;
        }

        int pivotRow = findPivotRow(tableau, pivotColumn);
        if (pivotRow == -1) {
            throw runtime_error("المشكلة غير محدودة.");
        }

        pivotElement(tableau, pivotRow, pivotColumn);
    }
    // نهاية الحلقة الثانية
    return 0;
}
