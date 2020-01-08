#include "includes/biginteger.h"
#include <iostream>
#include <ctime>
#include <random>
#include <chrono>

using namespace std;
using namespace wide_integer::generic_template;

using bigint = uint8192_t;

unsigned int getted_bits;
unsigned int half_bits;

int default_primes[5] = {3, 5, 7, 11, 13};

bigint pow(bigint f, bigint s, bigint smth, int i)
{
	for (; ++i < s - 1;)
		smth = smth * f;
	return (smth * f);
}

void pow_mod(bigint &ret, bigint in_base, bigint power, bigint modulus)
{
    if (power == 0)
    {
        ret = 1;
        return ;
	}
	bigint y("1");
    bigint base = in_base;
    while (power - 1 > 0)
	{
        if (power % 2 == 0)
		{
            base = ((base % modulus) * (base % modulus));
			base = base % modulus;
            power = power / 2;
        } 
		else 
		{
            y = (y * base);
			y = y % modulus;
            base = ((base % modulus) * (base % modulus)) % modulus;
            power -= 1;
            power /= 2;
        }
    }
    ret = ((base % modulus) * (y % modulus)) % modulus;;
}

void random_bigint(bigint &gen_int, int half_bits, mt19937 &mt_rand)
{
	gen_int = gen_int + pow(2, half_bits - 1, "1", -1);
	int i = 0;
	for (; ++i < half_bits - 1;)
		if (mt_rand() % 2)
			gen_int += pow(2, half_bits - i - 1, "1", -1);
	gen_int += 1;
}

int check_default(bigint &n)
{
	for (int i = 0; i < 5; i++)
		if ((n % default_primes[i]) == 0)
			return (0);
	return (1);
}

int miller_rabin(int k, bigint n, mt19937 &mt_rand)
{
	bigint test_result;
	if (!check_default(n))
		return (0);
	bigint n_min_1 = n - 1;
	bigint s = 0;
	bigint d;
	for (d = n - 1; (d & 1) == 0; (s += 1), (d = d / 2))
		;
	for (; --k; )
	{
		bigint a = 0;
		random_bigint(a, half_bits - 2, mt_rand);
		pow_mod(test_result, a, d, n);
		if (test_result == 1 || test_result == n_min_1)
			continue;
		unsigned int j = 0;
		for (; j < s; j++)
		{
			pow_mod(test_result, test_result, 2, n);
			if (test_result == 1)
				return 0;
			if (test_result + 1 == n)
				break;
		}
		if (j == s)
			return 0;
	}
	return 1;
}

int go_cycle(bigint n, bigint *primes, int num, bigint maximum, int i, mt19937 &mt_rand)
{
	maximum =  pow(2, half_bits, "1", -1);
	for (; n < maximum;)
	{
		int ret = miller_rabin(10, n, mt_rand);
		if (ret)
		{
			primes[num] = n;
			cout << n << endl;
			return (1);
		}
		n += 2;
	}
	return (0);
}

void generate_primes(auto seed, mt19937 &mt_rand, int num, bigint *primes)
{
	bigint gen_int("0");
	random_bigint(gen_int, half_bits, mt_rand);
	if (!go_cycle(gen_int, primes, num, "0", -1, mt_rand))
	{
		generate_primes(seed, mt_rand, num, primes);
	}
}

void create_modules(bigint *modules, bigint *primes)
{
	modules[0] = primes[0] * primes[1];
	modules[1] = primes[2] * primes[3];
}

void create_pub(bigint *pub)
{
	pub[0] = 65537;
	pub[1] = 65537;
}

int extended_euclid(bigint a, bigint b, bigint &x, bigint &y, bigint &d, bigint q, bigint r, bigint x1, bigint x2, bigint y1, bigint y2)
{
	int flag = 0;
	if (!(int)b) 
	{
		x = 1;
		d = a;
		y = 0;
		return 2;
	}
	x2 = 1, x1 = 0, y2 = 0, y1 = 1;
	while (b > 0)
	{
		q = a / b, r = a - q * b;
		if (flag == 0)
		{
			x = x2 - q * x1;
			flag++;
		}
		else if (flag == 1)
		{
			x = q * x1 + x2;
			flag++;
		}
		else if (flag != 0 && flag != 1)
		{
			x = q * x1 + x2;
			flag -= 1;
		}
		y = y2 - q * y1;
		a = b, b = r;
		x2 = x1, x1 = x, y2 = y1, y1 = y;
	}
	d = a, x = x2, y = y2;
	return flag;
}

void	inverse_unsigned(bigint &ret, bigint a, bigint n)
{
  bigint d, x, y;
  int flag = extended_euclid(a, n, x, y, d, 0, 0, 0, 0, 0, 0);
  if (flag == 1)
  	x = n - x;
  if (d == 1)
  {
  	ret = x;
	  return ;
	}
  ret = 0;
}

void create_priv(bigint *priv, bigint *modules, bigint *primes)
{
	bigint euler1 = primes[0] - 1;
	bigint euler2 = primes[1] - 1;
	bigint euler = euler1 * euler2;
	inverse_unsigned(priv[0], "65537", euler);
	euler1 = primes[2] - 1;
	euler2 = primes[3] - 1;
	euler = euler1 * euler2;
	inverse_unsigned(priv[1], "65537", euler);
}

char	*itoa_base(bigint value, char *str, unsigned int size, bigint tmp)
{
	int 	base = 16;
	string	tab;

	tab = "0123456789abcdef";
	tmp = value;
	for (;(tmp /= base) > 0;)
		size++;
	size = size + 1;
	str = new char[size + 1];
	str[size] = '\0';
	for (;size > 0;)
	{
		str[size - 1] = tab[(int)(value % base)];
		size--;
		value = value / base;
	}
	return (str);
}

int main(void)
{
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	mt19937 mt_rand(seed);//seeding mersenn twister PRNG
	cout << "enter num of bits\n";
	cin >> getted_bits;
	half_bits = getted_bits / 2;
	bigint primes[4];
	bigint modules[2];
	bigint pub[2];
	bigint priv[2];
	for (int i = 0; i < 4; i++)
		generate_primes(seed, mt_rand, i, primes);
	create_modules(modules, primes);
	create_pub(pub);
	create_priv(priv, modules, primes);
	cout << "public exponent = " << itoa_base(pub[0], NULL, 0, 0) << endl;
	cout << "modulus = " << itoa_base(modules[0], NULL, 0, 0)<< " private exp = " << itoa_base(priv[0], NULL, 0, 0) << endl;
	cout << "public exponent = " << itoa_base(pub[1], NULL, 0, 0) << endl;
	cout << "modulus = " << itoa_base(modules[1], NULL, 0, 0) << " private exp = " << itoa_base(priv[1], NULL, 0, 0) << endl;
	bigint Msg;
	random_bigint(Msg, half_bits, mt_rand);
	cout << "Generated Msg = " << Msg << endl;
}
