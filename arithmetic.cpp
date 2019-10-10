#include <stdlib.h> // �������ͷ�ļ�
#include <iostream>
#include <cstdio>
#include <stack>  // ջ��ͷ�ļ�
#include <time.h> // ʱ�亯��ͷ�ļ�
using namespace std;
const int up = 100; // ������������Ͻ�


/* �ж��Ƿ���С���ĺ���
����1������С�����������������
����0������������
 */
bool is_decimals(int a, int b){
	return (!b || (a % b)); // �������Ϊ�㣬����С������
}

/*
�����������ʽ
�������־��������
��������������ţ�0�� 1�� 2�� 3����Ӧ��+��-, *, /)
*/

/* symb������ĳ��ȣ� a[]�������ּ��������   ����λ����������ţ�ż��λ��������  */
void print_expression(int symb, int a[]){ //
	for(int i = 0; i < symb; i++){
		if(i%2){ // ����λ����������ţ���������Ӧ�����
			if(a[i] == 0) cout << " + ";
			if(a[i] == 1) cout << " - ";
			if(a[i] == 2) cout << " * ";
			if(a[i] == 3) cout << " / ";
		}
		else cout << a[i]; // ż��λ������ţ�ֱ�����
	}
}


/*
��������˴���ȡջ��ʵ��
* , / �� +��-ӵ�в�ͬ�����ȼ�
��syջ����+��-�����
����*��/ ֱ������
*/

/* symb������ĳ��ȣ� a[]�������ּ��������   ����λ����������ţ�ż��λ��������  */
void print_answer(int symb, int a[]){
	stack<int> num; // �������ֵ�ջ
	stack<int> sy; // ����������ŵ�ջ
	for(int i = 0; i < symb; i++){
		if(i % 2) sy.push(a[i]); // �����������ţ�ֱ�Ӽ���sy����ջ
		else{ // ���������
			/* ���ж�ǰһ��������ʲô�������* /, �Ǿ�ȡ���÷��ţ�����Ӧ������
                ע�� ���ջΪ�գ�������ȡ�������ǵ�һ������ֱ�Ӽ���num����ջ������sy.top()����
			*/
			if(!sy.empty()&& sy.top() > 1){
				int temp_sy = sy.top(); sy.pop(); // temp_sy ����sy����λ��ջ������
				int temp_num = num.top(); num.pop(); // temp_num ����num����λ��ջ������
				if(temp_sy == 2) num.push(temp_num * a[i]); // ����ǳˣ�������˸���ջ��
				else num.push(temp_num / a[i]); // ����ǳ��������������ջ��
			}
			else num.push(a[i]); // �������ֱ�ӽ�����ֱ�Ӽ�������ջ
		}
	}
	/* �����Ѿ������е�*��/ ȫ�������꣬sy����ֻ������+��-
	ͬ����������ȼ���������һ����һ�� ֱ�Ӱ�����������  */
	int ans = num.top(); num.pop();
	while(!sy.empty()){
		int temp_sy = sy.top(); sy.pop();
		int temp_num = num.top(); num.pop();
		if(temp_sy == 0) ans = temp_num + ans;
		if(temp_sy == 1) ans = temp_num - ans;
	}
	cout << " = " << ans << endl; // ������
}

/*
���������������Ҫ�����������ŵ�����
�����鱣�����е���Ϣ������ ����λ����������ţ�ż��λ��������
����������ţ������ж��Ƿ�����С���� �ᣬ���������ɱ��ʽ
�жϳ��ţ���������ǰһ�����͵�ǰ����һ�������жϡ�Ӧ������ǰ���ɳ˺ͳ���ɵ��������Ե�ǰ�����֡�
*/
bool expression(){
	/* 2 + rand()%2������2������3��������ţ� */
    int symb = (2 + rand()%2) * 2 + 1; // �ܵĳ���Ϊ������ŵ�����*2 + 1
    int a[10]; // �������ּ��������   ����λ����������ţ�ż��λ��������
    stack<int> st; // ��Ҫ���� ��������֮ǰ�ɳ˺ͳ��õ������֡�
    for(int i = 0; i < symb; i++){
		if(i % 2) a[i] = rand()%4; // �������������ţ� ����0�� 1�� 2�� 3����Ӧ��+��-, *, /)
		else{
			a[i] = rand()%(up + 1); // ����������֣�100���ڵ�������

			/* �������ǰ�ķ�����/ �ţ� �жϺ�ǰ��������������Ƿ���С��������ǣ��������ɱ��ʽ*/
			if(i && a[i-1]==3 && is_decimals(st.top(), a[i])) return 0;

			/*�������֮ǰ��*��/�õ������֡�*/
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
	print_expression(symb, a); cout << endl;// ������ʽ
	print_expression(symb, a); 
	print_answer(symb, a);  // ���㲢������
	cout << endl;
	return 1;
}

int main(int op, char *args[]){
	srand( (unsigned)time( NULL));
	int n = 1; // �������ʽ������
	if(op == 2) n = atoi(args[1]);
	freopen("subject.txt", "w", stdout);
	for(int i = 0; i < n;){
		if(expression()) i++; // ֻ�е����ʽ�����˲ż���
	}
	return 0;
}
