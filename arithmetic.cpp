#include <stdlib.h> // 随机函数头文件
#include <iostream>
#include <cstdio>
#include <stack>  // 栈的头文件
#include <time.h> // 时间函数头文件
using namespace std;
const int up = 100; // 随机数产生的上界


/* 判断是否是小数的函数
返回1，则是小数，重新生成随机数
返回0，正常向后操作
 */
bool is_decimals(int a, int b){
	return (!b || (a % b)); // 如果除数为零，当成小数处理
}

/*
简单输出运算表达式
遇见数字就输出数字
遇见符号输出符号（0， 1， 2， 3）对应（+，-, *, /)
*/

/* symb是数组的长度， a[]保存数字及运算符号   奇数位保留运算符号，偶数位保留数字  */
void print_expression(int symb, int a[]){ //
	for(int i = 0; i < symb; i++){
		if(i%2){ // 奇数位保存运算符号，遇见做相应的输出
			if(a[i] == 0) cout << " + ";
			if(a[i] == 1) cout << " - ";
			if(a[i] == 2) cout << " * ";
			if(a[i] == 3) cout << " / ";
		}
		else cout << a[i]; // 偶数位保存符号，直接输出
	}
}


/*
四则运算此处采取栈来实现
* , / 和 +，-拥有不同的优先级
用sy栈保留+，-运算符
遇见*，/ 直接运算
*/

/* symb是数组的长度， a[]保存数字及运算符号   奇数位保留运算符号，偶数位保留数字  */
void print_answer(int symb, int a[]){
	stack<int> num; // 保留数字的栈
	stack<int> sy; // 保留运算符号的栈
	for(int i = 0; i < symb; i++){
		if(i % 2) sy.push(a[i]); // 如果是运算符号，直接加入sy符号栈
		else{ // 如果是数字
			/* 先判断前一个符号是什么，如果是* /, 那就取出该符号，做相应的运算
                注意 如果栈为空，即现在取的数字是第一个数，直接加入num数字栈，不能sy.top()操作
			*/
			if(!sy.empty()&& sy.top() > 1){
				int temp_sy = sy.top(); sy.pop(); // temp_sy 保留sy符号位的栈顶符号
				int temp_num = num.top(); num.pop(); // temp_num 保留num数字位的栈顶数字
				if(temp_sy == 2) num.push(temp_num * a[i]); // 如果是乘，两数相乘更新栈顶
				else num.push(temp_num / a[i]); // 如果是除，两数相除更新栈顶
			}
			else num.push(a[i]); // 其他情况直接将数字直接加入数字栈
		}
	}
	/* 上述已经把所有的*和/ 全部运算完，sy里面只保留了+，-
	同样级别的优先级先运算哪一个都一样 直接挨个操作即可  */
	int ans = num.top(); num.pop();
	while(!sy.empty()){
		int temp_sy = sy.top(); sy.pop();
		int temp_num = num.top(); num.pop();
		if(temp_sy == 0) ans = temp_num + ans;
		if(temp_sy == 1) ans = temp_num - ans;
	}
	cout << " = " << ans << endl; // 输出结果
}

/*
先用随机数生成所要运算的运算符号的数量
用数组保存所有的信息，这里 奇数位保留运算符号，偶数位保留数字
如果遇见除号，进行判断是否会产生小数。 会，就重新生成表达式
判断除号，不仅仅是前一个数和当前数做一个除法判断。应该是由前面由乘和除组成的数来除以当前的数字。
*/
bool expression(){
	/* 2 + rand()%2（产生2个或者3个运算符号） */
    int symb = (2 + rand()%2) * 2 + 1; // 总的长度为运算符号的数量*2 + 1
    int a[10]; // 保存数字及运算符号   奇数位保留运算符号，偶数位保留数字
    stack<int> st; // 主要功能 保留除号之前由乘和除得到的数字。
    for(int i = 0; i < symb; i++){
		if(i % 2) a[i] = rand()%4; // 随机生成运算符号， 这里0， 1， 2， 3）对应（+，-, *, /)
		else{
			a[i] = rand()%(up + 1); // 随机生成数字（100以内的正数）

			/* 如果数字前的符号是/ 号， 判断和前面的数运算起来是否是小数，如果是，重新生成表达式*/
			if(i && a[i-1]==3 && is_decimals(st.top(), a[i])) return 0;

			/*运算除号之前由*和/得到的数字。*/
			if(i){
				if(a[i - 1] < 2) st.push(a[i]);
				else {
					int x = st.top(); st.pop();
					if(a[i - 1] == 2) st.push(x * a[i]);
					if(a[i - 1] == 3) st.push(x / a[i]);
				}
			}else st.push(a[i]);
		}
	}
	print_expression(symb, a); cout << endl;// 输出表达式
	print_expression(symb, a); 
	print_answer(symb, a);  // 计算并输出结果
	cout << endl;
	return 1;
}

int main(int op, char *args[]){
	srand( (unsigned)time( NULL));
	int n = 1; // 保留表达式的数量
	if(op == 2) n = atoi(args[1]);
	freopen("subject.txt", "w", stdout);
	for(int i = 0; i < n;){
		if(expression()) i++; // 只有当表达式满足了才计数
	}
	return 0;
}
