#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

set<char> Alphabet = { '�', '�', '�', '�', '�', '�', '�',
						'�', '�', '�', '�', '�', '�', '�', '�', '�',
						'�', '�', '�', '�', '�', '�', '�', '�', '�',
						'�', '�', '�', '�', '�', '�', '�', '�' };

void Filter(string FilePath, set<char> Alphabet, string Destination) {
	ifstream fin(FilePath);
	ofstream fout(Destination);
	string buffer;
	if (fin.is_open()) {
		while (fin.peek() != EOF) {
			getline(fin, buffer);
			fin.seekg(fin.tellg());
			//cout << buffer << endl;
			for (int i = 0; i < buffer.length(); i++) {
				if (Alphabet.count(char(tolower(buffer[i])))) {
					//cout << buffer[i] << "\t";
					fout << char(tolower(buffer[i]));
				}
				else {
					continue;
				}
			}
			buffer.clear();
		}

	}
	fin.close();
	fout.close();

}

void FillingMonoMap(string FilePath, map<char, double>&MonoMap, double &LetterAmount) {
	ifstream fin(FilePath);
	string buffer;
	if (fin.is_open()) {
		while (fin.peek() != EOF) {
			getline(fin, buffer);
			fin.seekg(fin.tellg());
			//cout << buffer << endl;
			for (int i = 0; i < buffer.length(); i++) {
				if (MonoMap.count(buffer[i])) { // MonoMap.count([��������]) � ������ ������� �������� ���������� 1, ����� - 0
					MonoMap.at(buffer[i])++;
					LetterAmount++;
				}
				else {
					MonoMap.emplace(buffer[i], 1); //emplace ��������� ���� ����:�������� � map
					LetterAmount++;
				}
			}
			buffer.clear();
		}

	}
	fin.close();
} //�������, ������� ��������� map ������ ������ : ���-�� ������� � ������
double MonoEntropy(map<char, double>MonoMap, double LetterAmount) {
	double Entropy = 0;
	for (auto it = MonoMap.cbegin(); it != MonoMap.cend(); it++) {
		Entropy += -(it->second / LetterAmount)*log2(it->second / LetterAmount);
	}
	return Entropy;
} // �������, ������� ������� �������� ��� ���������
void ShowMap(map<char, double>MonoMap, double LetterAmount) {
	for (auto it = MonoMap.cbegin(); it != MonoMap.cend(); it++) {
		cout << it->first << " " << setprecision(6) << it->second / LetterAmount << endl;
	}
} //�������, ������� ���������� ���������� map ��� ���������

void FillingBigramMap(string FilePath, map<string, double>&BiMap, double &BigramAmount, bool bIntersection) { 
	ifstream fin(FilePath);
	string buffer;
	string TempBigram;
	if (fin.is_open()) {
		while (fin.peek() != EOF) {
			getline(fin, buffer);
			fin.seekg(fin.tellg());
			//cout << buffer << endl;
			for (int i = 0; i < buffer.length(); i += 1 + bIntersection) {
				TempBigram.push_back(buffer[i]);
				TempBigram.push_back(buffer[i + 1]);
				//cout << TempBigram << endl;
				if (BiMap.count(TempBigram)) {
					BiMap.at(TempBigram) += 1;
					BigramAmount++;
					//cout << TempBigram << endl;
					TempBigram.clear();
				}
				else {
					BiMap.emplace(TempBigram, 1);
					BigramAmount++;
					TempBigram.clear();
					//cout << TempBigram << endl;
				}
			}
			buffer.clear();
		}

	}
	fin.close();
}
void ShowMap(map<string, double>BiMap, double BigramAmount) {
	for (auto it = BiMap.cbegin(); it != BiMap.cend(); it++) {
		cout << it->first << " " << setprecision(6) << it->second  << endl;
	}
}

double BigramEntropy(map<string, double>BiMap, double BigramAmount) {
	double Entropy = 0;
	for (auto it = BiMap.cbegin(); it != BiMap.cend(); it++) {
		Entropy += -(it->second / BigramAmount)*log2(it->second / BigramAmount);
	}
	return Entropy;
}
double Amount(map<string, double>BiMap) {
	double Amount = 0;
	for (auto it = BiMap.cbegin(); it != BiMap.cend(); it++) {
		Amount += it->second;
	}
	return Amount;
}
int main() {
	setlocale(LC_ALL, "rus");
	//string FilePath = "..\\..\\����������������.txt";
	//bool SpaceAv = 0; // ������� ������� � ������
	//if (SpaceAv) {
	//	Alphabet.insert(' ');
	//	string Destination = "D:\\Dyn\\�����\\���\\CryptoLabs 2019\\fb-labs-2019\\cp_1\\kashyrin_fb-74_cp1\\FilteredTextWithSpace.txt";
	//	Filter(FilePath, Alphabet, Destination);

	//}
	//else {
	//	string Destination = "D:\\Dyn\\�����\\���\\CryptoLabs 2019\\fb-labs-2019\\cp_1\\kashyrin_fb-74_cp1\\FilteredTextWithoutSpace.txt";
	//	Filter(FilePath, Alphabet, Destination);
	//}
	/*map<char, double>MonoMap;
	double MonoLetterAmount = 0;
	FillingMonoMap("..\\..\\FilteredTextWithoutSpace.txt", MonoMap, MonoLetterAmount);
	ShowMap(MonoMap, MonoLetterAmount);
	cout << "Monogram entropy: " << MonoEntropy(MonoMap, MonoLetterAmount) << endl;*/

	map<string, double>BiMap;
	double BigramAmount = 0;
	FillingBigramMap("..\\..\\FilteredTextWithSpace.txt", BiMap, BigramAmount, 1);
	ShowMap(BiMap, BigramAmount);
	cout << "Bigram entropy: " << BigramEntropy(BiMap, BigramAmount) << endl;
	cout << BigramAmount << endl;
	//cout << Amount(BiMap) << endl;
	system("pause");
	return 0;
}