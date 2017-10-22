#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#define ZERO 1E-6

using namespace std;

/* ʮ����ת������ */

/* �������� */
void db_integer(long n)
{
	if (n > 0)
	{
		db_integer(n / 2);
		cout << n%2;
	}
}
/* С������ */
void db_decimal(double m)
{
	if (m > ZERO)
	{
		m = m * 2;
		cout << (long)m;
		db_decimal(m - (long)m);
	}
}

void dec_to_bin(double num)
{
	db_integer((long)num);
	if (num - (long)num > ZERO)			//�ж��Ƿ���С��
	{
		putchar('.');
		db_decimal(num - (long)num);
	}
	cout << endl;
}

/* ������תʮ���� */
void bin_to_dec()
{
	double integer = 0.0;	//��������
	double decimal = 1.0;		//С������
	int signal = 1;			//������
	int flag = 0;				//״̬��־
	while (flag != 3)
	{
		switch (flag)
		{
		case 0:				/* flag==0����һ���ַ��������Ǹ��Ż�С���㣬Ҳ������0��1  */
			switch (getchar())
			{
			case '1':
				flag = 1;
				integer = 1;
				break;
			case '0':
				flag = 1;
				break;
			case '-':
				flag = 1;
				signal = -1;
				break;
			case '.':
				flag = 2;
				break;
			default:
				flag = 3;		/* ���Ƿ��ַ��������س�����������	 */
			}
			break;
		case 1:				/* flag==1���������֣�������0��1��Ҳ������С����	 */
			switch (getchar())
			{
			case '1':
				integer = integer * 2 + 1;
				break;
			case '0':
				integer = integer * 2;
				break;
			case '.':
				flag = 2;
				break;
			default:
				flag = 3;		/* ���Ƿ��ַ��������س����������� */
			}
			break;
		case 2:				/* flag==2��С�����֣�������0��1 */
			decimal = decimal / 2;
			switch (getchar())
			{
			case '1':
				integer += decimal;
				break;
			case '0':
				break;
			default:
				flag = 3;		/* ���Ƿ��ַ��������س�����������	 */
			}
		}
	}
	cout << integer * signal << endl;
}

int main()
{
	while (1)
	{
		cout << "1. ʮ���� -> ������\n2. ������ -> ʮ����\n0. �˳�\n��ѡ��" << endl;
		int s;
		cin >> s;
		switch (s)
		{
		case 1:
			double num;
			cout << "������һ��ʮ��������";
			cin >> num;
			while (cin.fail())
			{
				while (getchar() != '\n')
					continue;
				cin.clear();
				cout << "����������������룺";
				cin >> num;
			}
			if (num < 0)
			{
				putchar('-');
				num = -num;
			}
			cout << "ת���ɶ�������Ϊ��";
			dec_to_bin(num);
			break;
		case 2:
			cout << "���������������";
			while (getchar() != '\n')					//�̵����з�
				continue;
			bin_to_dec();
			break;
		case 0:
			exit(0);
			return 0;
		default:
			while (getchar() != '\n')
				continue;
			cin.clear();
			cout << "Error!" << endl;
			break;
		}
		cout << endl;
	}
}
