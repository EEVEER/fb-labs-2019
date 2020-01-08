#include "includes/biginteger.h"
#include <iostream>

using namespace std;
using namespace wide_integer::generic_template;

using bigint = uint8192_t;

bigint msg ("269156294928672203297111376460261933569"); //¬ставл€ем сюда згенерированный меседж
char *my_modulus = "0xb95287e0fefd0bf818690afb514ca91b5d44669d607d6ad54479b6176d6d7d51";//—юда наш модуль
char *private_exp = "0x9b27ead54806e9ff73c876464521ceadc8edf4a58974d65bc0cb7f1447165d41";//—юда наш приватный ключ
char *site_modulus = "0xBB3AD5C9D4B0439509F243975D7AA3F27DA7A170AE3A5DBEA20A375E50392F61";//—юда модуль сайта
char *Key_site1 = "0x6828B73328A289981494F1ACA8EED02E2E33FC6291D92A48D717E5A2BB417B53";//—юда згенерированный ключ из сайта
char *Signature_site = "0xA586135FAA4763E444104C4F71CF1FAE660545FD9D866B47E4DA4BF9B0693F7B";//—юда Signature из сайта

// ќЅя«ј“≈Ћ№Ќќ добавл€ем 0x в начале, иначе капут

bigint pub("65537");

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

void encrypt(bigint &message, bigint e, bigint n)
{
	bigint ret;
	pow_mod(ret, message, e, n);
	message = ret;
}

bigint decrypt(bigint &encrypted, bigint d, bigint n)
{
	bigint ret;
	pow_mod(ret, encrypted, d, n);
	encrypted = ret;
}

bigint sign(bigint &message, bigint d, bigint n)
{
	bigint ret;
	pow_mod(ret, message, d, n);
	message = ret;
}

bigint verify(bigint &sign, bigint e, bigint n)
{
	bigint ret;
	pow_mod(ret, sign, e, n);
	sign = ret;
}

int receive_key(bigint &K, bigint &sign, bigint &my_d, bigint &my_n, bigint &pub_site, bigint &site_n)
{
	bigint copy_s = sign;
	decrypt(K, my_d, my_n);
	if (K == 0)
		return (0);
	decrypt(sign, my_d, my_n);
	verify(sign, pub_site, site_n);
	cout << "Podpis = " << sign << endl << "Key = " << K <<endl;
	return ((int)sign == (int)K);
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

void sendkey(bigint &mymod, bigint &priv, bigint &e2, bigint &n2)
{
	bigint Sign = msg;
	sign(Sign, priv, mymod);
	encrypt(Sign, e2, n2);
	encrypt(msg, e2, n2);
	cout << "Key = " << itoa_base(msg, NULL, 0, 0) << "\nSignature = " << itoa_base(Sign, NULL, 0, 0);
}

int main()
{
	bigint my_module(my_modulus);
	bigint my_priv(private_exp);
	bigint site_module(site_modulus);
	bigint Key_site(Key_site1);
	bigint Sign_site(Signature_site);
	cout << "variables initialized\n";
	cout << "baluemsya crypt-decrypt sign-verify\n";
	encrypt(msg, pub, my_module);
	cout << msg << endl;
	decrypt(msg, my_priv, my_module);
	cout << msg << endl;
	sign(msg, my_priv, my_module);
	cout << msg << endl;
	verify(msg, pub, my_module);
	cout << msg << endl;
	if (receive_key(Key_site, Sign_site, my_priv, my_module, pub, site_module))
		cout << "Successss!\n";
	else
		cout << "Failed\n";
	sendkey(my_module, my_priv, pub, site_module);
}
