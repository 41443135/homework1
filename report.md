# 41143135

作業一

---

## Problem 1: 阿克曼函數 (Ackermann's Function)

### 1. 解題說明
本題要求實現阿克曼函數（Ackermann's Function）$A(m, n)$ 的計算。阿克曼函數是一個非原始遞迴函數（non-primitive recursive function），其增長速度極快。本題需分別以「遞迴」與「非遞迴」兩種方式實作：
- **遞迴版本**：直接依據數學定義進行條件判斷與自我呼叫。
- **非遞迴版本**：自行利用動態陣列模擬 Stack（堆疊），並實現動態擴充記憶體機制以處理遞迴呼叫的狀態。

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

### 3. 效能分析

- **時間複雜度：阿克曼函數的成長速度極快，其時間複雜度為 $O(A(m, n))$。當 $m \ge 4$ 時，計算量會爆炸性成長。
- **空間複雜度：遞迴呼叫堆疊的最大深度為 $m$，加上記錄選擇狀態的 chosen 陣列，空間複雜度為 $O(m)$。

### 4. 測試與驗證

- **測試案例 1：輸入 m = 3，字元為 a b c
	- **輸出結果：powerset(S) = { () (c) (b) (bc) (a) (ac) (ab) (abc) }
