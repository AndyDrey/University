#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void lineToMass(unsigned char Mass[3][9], string s);
void shifrAndSwap(unsigned char Mass[3][9], int shifr);
void deshifrAndSwap(unsigned char Mass[3][9], int shifr);
void init(const char *name);
bool check(const char *name);

int shifr;
string s;
int hash_k = 10;
fstream of;
unsigned char Mass[3][9];
int main(){
	setlocale(LC_ALL, "Russian");
	of.open("D:\\rgr\\shifr.txt");
	cout << "Представтесь, пожалуйста!\n";
	getline(cin, s);
	int switcher;
	do
	{
		cout << "Что вы хотите сделать?(введите 1,2 или 0) \n1. Зашифровать файл \n2. Расшифровать файл\n3. Проверить файл на неприкосновенность\n0. Выход\n";
		cin >> switcher;
		switch (switcher)
		{
			//Выход
		case 0:
			cout << "До новых встреч, " << s;
			break;
			//Шифрование
		case 1:
			lineToMass(Mass, s);
			//Заносим в файл полученую строку
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					of << Mass[j][i];
				}
			}
			of.close();
			cout << "Введите ключ/кодовое слово: \n";
			cin >> shifr;
			shifrAndSwap(Mass, shifr);
			//Очищаем файл от незашифрованой строки
			of.open("D:\\rgr\\shifr.txt");
			//Заносим в файл зашифрованую строку
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					of << Mass[j][i];
				}
			}
			of.close();
			init("D:\\rgr\\out.txt");
			break;
			//Расшифровка
		case 2:
			deshifrAndSwap(Mass, shifr);
			//Очищаем файл
			of.open("D:\\rgr\\shifr.txt");
			//Заносим в файл расшифрованую строку
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					of << Mass[j][i];
				}
			}
			of.close();
			break;
		case 3:
			if (!check("D:\\rgr\\out.txt"))
			{
				cout << "Файл был подвержен изменениям!!! Прекратите работу программы\n";
			}
			break;
			//Несуществующее число
		default:
			cout << "Нет такого варианта!!!\n";
			break;
		}
	} while (switcher != 0);
	of.close();
	return 0;
}

void lineToMass(unsigned char Mass[3][9], string s){
	for (int i = 0, k = 0; i < 9 && k < s.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Mass[j][i] = s[k];
			k++;
		}
	}
	cout << "Ваш текст: \n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << Mass[i][j] << " ";
		}
		cout << endl;
	}
}

void shifrAndSwap(unsigned char Mass[3][9], int shifr){
	unsigned char tempM[3][9];
	while (shifr)
	{
		for (int j = 8; j >= 0; j--)
		{
			for (int i = 0; i < 3; i++)
			{
				tempM[i][(shifr % 10) - 1] = Mass[i][j];
			}
			shifr = shifr / 10;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Mass[i][j] = tempM[i][j];
		}
	}
	cout << "Ваш текст после шифрования: \n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << Mass[i][j] << " ";
		}
		cout << endl;
	}
}

void deshifrAndSwap(unsigned char Mass[3][9], int shifr){
	unsigned char tempM[3][9];
	while (shifr)
	{
		for (int j = 8; j >= 0; j--)
		{
			for (int i = 0; i < 3; i++)
			{
				tempM[i][j] = Mass[i][(shifr % 10) - 1];
			}
			shifr = shifr / 10;
		}
	}
	cout << "Ваш текст после дешифрования: \n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << tempM[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Mass[i][j] = tempM[i][j];
		}
	}
}

void init(const char *name)
{
	ifstream fs(name);
	ofstream ofs("D:\\rgr\\out.txt", ios::trunc | ios::out);
	char tm;
	while (!fs.eof())
	{
		fs >> tm;
		ofs << tm << char(tm%hash_k);
	}

	fs.close();
	ofs.close();
}

bool check(const char *name)
{
	bool norm = true;
	ifstream fs("D:\\rgr\\out.txt");
	char tm, ans;
	while (!fs.eof())
	{
		fs >> tm >> ans;
		if (tm%hash_k != ans)
		{
			norm = false;
			break;
		}
	}

	fs.close();
	return norm;
}
