#include <iostream>
#define MAXSIZE 100
using namespace std;

double A[MAXSIZE][MAXSIZE]; // ��ʼ��ϵ������
double U[MAXSIZE][MAXSIZE]; // ��Ϊ�����Ǿ�������в�����Uϵ������
double L[MAXSIZE][MAXSIZE]; // ͬ��L����
double B[MAXSIZE]; // �ұߵĳ���������
double Z[MAXSIZE]; // ��Ϊ�����Ǿ�����ϵ������
double X[MAXSIZE]; // ��Ĵ�ŵ�Ԫ
int n = 0;
int methodType = 0;

void input();
void select();
void back();

int main() {
	input();
	select();
}

void input() {
	cout << "�����뷽�������";
	cin >> n;
	cout << "�����뷽������������" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> A[i][j];
		}
		cin >> B[i];
	}
}

void select() {
	cout << "��ѡ������ʹ�õķ���" << endl;
	cout << "1.��˹��Ԫ��" << endl;
	cout << "2.��������Ԫ��" << endl;
	cout << "3.ƽ������" << endl;
	cout << "4.����Ԫ�ط�" << endl;
	cin >> methodType;
}

// �ش������Ǿ������
void back() {

}