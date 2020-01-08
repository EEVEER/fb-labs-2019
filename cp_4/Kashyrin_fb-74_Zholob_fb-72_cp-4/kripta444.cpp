#include <iostream>  
#include <cstring>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <strings.h>

using namespace std;
 
void process_n_gram(char *mas, int &T, int grams, int *num, int cur_num)
{
	if (cur_num != grams)
		for (int l = 0; l < 2; l++)
		{
			*(num + cur_num) = l;
			process_n_gram(mas, T, grams, num, cur_num + 1);
		}
	else
	{
		int *n = new int[5];
		for (int l = 0; l < 5; l++)
			n[l] = num[l];
		for (int l = -1; ++l < grams;)
		{
			cout << num[l];
			cout << " ";
		}
		long int counter = 0;
		for (int i = 0 - grams; (i = i + grams) < T-T % grams; )
						{
							int m[5];
							int j;
							for (int l = 0; l < grams; l++)
							{
								m[l] = mas[i + l];
							}
							if (!memcmp(n, m, sizeof(int) * grams))
								counter++;
						}
		cout << counter << endl;
		delete[] n;
	}
}

void	make_step(char* &mas, int &T, int size, int *def, int *var)
{
	int i;
	int suma;
	mas[T]= *def;
	i = -1;
	suma = 0;
	for (; size > ++i; )
	{
		suma = suma + (*(var + i) * *(def + i));
	}
	i = -1;
	for (; size - 1 > ++i; )
	{
		*(def + i) = *(def + i + 1);
	}
	*(def + size - 1) = suma % 2;
	T += 1;
}

void	create_t(int *var, int *def, int *dif, int size, int &T, char* &mas)
{
	int suma = 0;
	int malloc_size = 100000000;
	int i;
	mas = new char[malloc_size];
	make_step(mas, T, size, def, var);
	//sdvig
	//while (equal(def, def+size, dif) == 0)
	while (memcmp(def, dif, size * sizeof(int)))
		make_step(mas, T, size, def, var);
   cout<<"T = "<<T<<endl;
}

void	custom_bzero(void *mem, int size)
{
	unsigned char *m = (unsigned char *)mem;
	for (int i = 0; i < size; i++)
		m[i] = 0;
}

void	process_polinom(int *var, int size)
{
	int *def = new int[size];
	int *dif = new int[size];
	custom_bzero(def, size * sizeof(int));
	custom_bzero(dif, size *sizeof(int));
	def[size - 1] = 1;
	dif[size - 1] = 1;
	char *mas;
	int T = 0;
	create_t(var, def, dif, size, T, mas);
	int *mas_int = new int[5];
	for (int i = 2; i <= 5; i++)
	{
		cout << "processing " << i <<"-gram\n";
		process_n_gram(mas, T, i, mas_int, 0);
	}
	cout << "calculating correlation\n";
	int k = 0;
	int i = -1;
	for (int d = -1; 10 >= ++d; (k = 0) || (i = -1))
	{
		cout << d << " ";
		k = 0;
		i = -1;
		for (i = -1; ++i < T; )
		{
			int temp = mas[i];
			temp += *(mas + ((i + d) % T));
			k += temp % 2;
		}
		cout << k << endl;
	}
	delete[] mas_int;
	delete[] mas;
	delete[] def;
	delete[] dif;
}



int		main()
{
	cout << "processing 2nd polinom\n";
	int var2[20] = {1,1,1,1,0,1,0,1,0,1,0,0,0,0,1,1,0,1,0,0};
	process_polinom(var2 , 20);
	cout << "processing 1st polinom\n";
	int var[24] = {1,1,1,0,1,0,0,0,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0};
	process_polinom((var), 24);
}
