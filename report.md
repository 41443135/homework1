# 41143263

作業一

---

## Problem 1: Ackermann's Function

### 解題說明

本題要求實作阿克曼函數（Ackermann's function）$A(m, n)$，分別使用**遞迴（Recursive）**與**非遞迴（Non-recursive）**兩種方式來計算結果。

### 解題策略

1. **遞迴版本**：
   根據數學定義設定三個分支條件：
   - 當 $m = 0$ 時，返回 $n + 1$。
   - 當 $n = 0$ 時，遞迴呼叫 $A(m - 1, 1)$。
   - 其他情況，遞迴呼叫 $A(m - 1, A(m, n - 1))$。

2. **非遞迴版本**：
   利用 `std::stack` 資料結構模擬系統呼叫堆疊（Call Stack），將 $m$ 依序壓入堆疊中，藉由迴圈逐步解開遞迴結構。

### 程式實作

```cpp
#include <iostream>
#include <stack>

using namespace std;

// 遞迴版本
int ackermannRecursive(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return ackermannRecursive(m - 1, 1);
    } else {
        return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
    }
}

// 非遞迴版本（使用 Stack）
int ackermannNonRecursive(int m, int n) {
    stack<int> st;
    st.push(m);

    while (!st.empty()) {
        m = st.top();
        st.pop();

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            st.push(m - 1);
            n = 1;
        } else {
            st.push(m - 1);
            st.push(m);
            n = n - 1;
        }
    }
    return n;
}

int main() {
    int m = 2, n = 1;
    cout << "Ackermann Recursive (" << m << ", " << n << "): " << ackermannRecursive(m, n) << '\n';
    cout << "Ackermann Non-Recursive (" << m << ", " << n << "): " << ackermannNonRecursive(m, n) << '\n';
    return 0;
}
```

---

## Problem 2: Powerset

### 解題說明

本題要求編寫一個遞迴函數來計算並輸出集合 $S$ 的**冪集（powerset）**，即包含 $S$ 所有可能子集的集合。

### 解題策略

1. **遞迴分解**：
   對於集合中的每一個元素，都有兩種選擇：**「不選」** 或 **「選」**。
2. **狀態紀錄**：
   使用布林陣列 `chosen[]` 紀錄每個元素的選擇狀態。
3. **結束條件（Base Case）**：
   當處理索引 `index == m` 時，代表已決定好所有元素，走訪 `chosen[]` 陣列印出目前的子集組合。

### 程式實作

```cpp
#include <iostream>

using namespace std;

const int MAX_SIZE = 100;
int m;

// 遞迴求解 Powerset
void powerset(int index, bool chosen[], char p[]) {
    // Base Case：處理完所有元素後輸出子集
    if (index == m) {
        cout << "(";
        bool first = true;
        for (int i = 0; i < m; i++) {
            if (chosen[i]) {
                if (!first) {
                    cout << ",";
                }
                cout << p[i];
                first = false;
            }
        }
        cout << ") ";
        return;
    }

    // 選擇 1：不包含當前元素
    chosen[index] = false;
    powerset(index + 1, chosen, p);

    // 選擇 2：包含當前元素
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
```

