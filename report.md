# 41143135

作業一

---

## Problem 1: 阿克曼函數 (Ackermann's Function)

### 1. 解題說明

#### 問題描述
本題要求實現阿克曼函數（Ackermann's Function）A(m, n)的計算。阿克曼函數是一個非原始遞迴函數（non-primitive recursive function），
其增長速度極快。本題需分別以「遞迴」與「非遞迴」兩種方式實作：
- **遞迴版本**：直接依據數學定義進行條件判斷與自我呼叫。
- **非遞迴版本**：自行利用動態陣列模擬 Stack（堆疊），並實現動態擴充記憶體機制以處理遞迴呼叫的狀態。

#### 解題策略
1. **遞迴版本**：依據邊界條件（m=0 或 $n=0$）與遞迴式進行條件分流。
2. **非遞迴版本**：手動維護一個堆疊，將狀態依序放入。遇到雙層呼叫 $A(m-1, A(m, n-1))$ 時將兩層參數推入 Stack，並設置容量不足時的動態
擴充機制（容量翻倍）。

### 2. 程式實作

```cpp
#include<iostream>
using namespace std;
//recursive
int Ackerman(int m,int n){
	if (m == 0) {
		return n + 1;
	}
	else if(n==0){
		return Ackerman(m - 1, 1);
	}
	else {
		return Ackerman(m - 1, Ackerman(m, n - 1));
	}
};
//nonrecursive
int ackerman(int m,int n) {
	int capacity = 100;//預設容量大小
	int* stack = new int[capacity];
	int top = -1;//top=-1表示Stack目前是空的
	top++;
	stack[top] = m;//放入m
	while (top >= 0) {
		m = stack[top];//m=最上面的值
		top--;
		if (m == 0) {
			n += 1;
		}
		else if (n == 0) {
			if (top + 1 >= capacity) {//再放入之前確認是否還有空間 不夠就補
				int newcapacity = capacity * 2;
				int* newstack = new int[newcapacity];
				for (int i = 0; i <= top; i++) {
					newstack[i] = stack[i];
				}
				delete[] stack;// 釋放舊記憶體
				stack = newstack;
				capacity = newcapacity;
			}
			top++;
			stack[top] = m - 1;
			n = 1;
		}
		else {
			if (top + 2 >= capacity) {//再放入之前確認是否還有空間 不夠就補
				int newCapacity = capacity * 2;
				int* newStack = new int[newCapacity];
				for (int i = 0; i <= top; i++) {
					newStack[i] = stack[i];
				}
				delete[] stack; // 釋放舊記憶體
				stack = newStack;
				capacity = newCapacity;
			}
			top++;
			stack[top] = m - 1;
			top++;//這裡會做兩層 一層是A(m-1,A(m,n-1))的 一層是A(m,n-1)的
			stack[top] = m;
			n -= 1;
		}
	}
	delete[] stack;
	return n;
};
int main() {
	int m, n;
	cout << "請輸入m跟n的值:";
	cin >> m >> n;
	cout<<"遞迴的ackermann's function結果:A("<<m<<','<<n<<") =" << Ackerman(m, n) << endl;
	cout<<"非遞迴的ackermann's function結果:A(" << m << ',' << n << ") = " << ackerman(m, n);
	return 0;
}
```

### 3. 效能分析

- **時間複雜度**：阿克曼函數的成長速度極快，其時間複雜度為 $O(A(m, n))$。當 $m \ge 4$ 時，計算量會爆炸性成長。
- **空間複雜度**：
	- **遞迴版本**:使用 Call Stack，空間複雜度取決於最大遞迴深度，為 $O(A(m, n))$。
    - **非遞迴版本**:使用自訂 Stack 陣列，空間複雜度同樣為 $O(\text{Stack 最大深度})$，最壞情況下與遞迴深度相當。

### 4. 測試與驗證

| 測試案例 | 輸入參數 m、$n$ | 遞迴輸出 | 非遞迴輸出 |
|----------|--------------|----------|----------|
| 測試一   | m跟n的值:1、2  |A(1,2) =4 |A(1,2) =4 |
| 測試二   | m跟n的值:2、2  |A(2,2) =7 |A(2,2) =7 |
| 測試三   | m跟n的值:3、2  |A(3,2) =29 |A(3,2) =29 |

### 5. 申論及開發報告

在實作非遞迴版本時，最大的挑戰在於如何模擬系統的 Call Stack。阿克曼函數在 $m > 0, n > 0$ 時會產生雙層遞迴呼叫 $A(m-1, A(m, n-1))$，
因此手動 Stack 中必須一次放入兩層狀態。為避免 Stack 溢位，程式中加上了動態擴充記憶體（重新配置二倍大容量）的機制，確保遇到較深層的呼叫
時不會造成記憶體區段錯誤（Segmentation Fault）。

作業二

---

## Problem 2: 冪集 (Powerset)

### 1. 解題說明
#### 問題描述
本題要求撰寫一個遞迴函式，計算並輸出一個包含 $m$ 個元素的集合 $S$ 之所有可能子集（冪集 Powerset）。

#### 解題策略
對於集合中的每一個元素，都有「選」與「不選」兩種可能，透過深度優先搜尋（DFS）與回溯（Backtracking）觀念遍歷所有組合。先將當前元素的選取
狀態設為 false 並遞迴下一個，再設為 true 並遞迴下一個，當處理完 $m$ 個元素時印出組合結果。

### 2. 程式實作

```cpp
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
```

### 3. 效能分析

- **時間複雜度**：O(m \cdot 2^m)
對於 $m$ 個元素，每個元素都有 2 種選擇（選或不選），生成的所有子集數量為 $2^m$。Base Case 輸出每個子集需花費
$O(m)$，故總時間複雜度為 O(m \cdot 2^m)。
- **空間複雜度**：O(m)
遞迴呼叫堆疊的最大深度為 m，加上記錄選擇狀態的 chosen 陣列，空間複雜度為 O(m)。

### 4. 測試與驗證

- **測試案例 1**:輸入 m = 3，字元為 a b c
	- 輸出結果：powerset(S) = { () (c) (b) (bc) (a) (ac) (ab) (abc) }
- **測試案例 2**:輸入 m = 2，字元為 1 2
	- 輸出結果：powerset(S) = { () (2) (1) (12) }

### 5. 申論及開發報告

本題採用了標準的回溯（Backtracking）觀念，透過布林陣列 chosen[] 來維護狀態。先遞迴呼叫 chosen[index] = false 表示不選擇當前元素，再
呼叫 chosen[index] = true 表示選擇當前元素。這種二分樹狀的遞迴呼叫能夠完整且不重複地列舉出 $2^m$ 個子集。利用固定陣列與全域變數 $m$，
程式碼精簡且能清楚展示遞迴結構。
