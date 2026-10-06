# 41143135

作業一

## Problem 1: 阿克曼函數 (Ackermann's Function)

### 解題說明
實現遞迴與非遞迴（自訂 Stack 與動態擴充記憶體）兩種方式來計算阿克曼函數。

### 程式實作

以下為主要程式碼：

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
