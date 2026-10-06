#include <iostream>
using namespace std;
const int MAX_SIZE = 100;
int m;
void powerset(int index, bool chosen[], char p[]) {
    //當處理完最後一個元素時
    if (index == m) {
        cout << "(";
        for (int i = 0; i < m; i++) {
            if (chosen[i]) {
                cout << p[i];
            }
        }
        cout << ") ";
        return;
    }
    chosen[index] = false;
    powerset(index + 1, chosen, p);

    chosen[index] = true;
    powerset(index + 1, chosen, p);
}
int main() {
    char p[MAX_SIZE];
    bool chosen[MAX_SIZE];
    cout << "請輸入元素數量 m: ";
    cin >> m;
    cout << "請輸入 " << m << " 個字元: ";
    for (int i = 0; i < m; i++) {
        cin >> p[i];
    }
    cout << "powerset(S) = { ";
    powerset(0, chosen, p);
    cout << "}\n";
    return 0;
}