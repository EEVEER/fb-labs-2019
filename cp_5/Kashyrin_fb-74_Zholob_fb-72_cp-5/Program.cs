using System;
using System.Numerics;
using System.Text;
using System.Globalization;

namespace ConsoleApp1
{
    class RSA_funcs
    {
        public static void encrypt(ref BigInteger Msg, BigInteger pub, BigInteger mod)
        {
            Msg = BigInteger.ModPow(Msg, pub, mod);
        }
        public static void decrypt(ref BigInteger Msg, BigInteger priv, BigInteger mod)
        {
            Msg = BigInteger.ModPow(Msg, priv, mod);
        }
        public static void sign(ref BigInteger Msg, BigInteger pub, BigInteger mod)
        {
            Msg = BigInteger.ModPow(Msg, pub, mod);
        }
        public static bool verify(ref BigInteger Msg, BigInteger pub, BigInteger mod, BigInteger cp)
        {
            Msg = BigInteger.ModPow(Msg, pub, mod);
            if (Msg == cp)
                return (true);
            else
                return (false);
        }
    }

    class Program
    {
        static readonly BigInteger pub = 65537;
        static bool IsPrime(BigInteger n, BigInteger odin)
        {
            Random rand = new Random();
            BigInteger n_min_1 = n - 1;
            BigInteger s = 0;
            BigInteger d;
            for (d = n - 1, s = 0; (d & odin) == 0;)
            {
                d /= 2;
                s += 1;
            }
            for (int i = 0; i < 10; i++)
            {
                BigInteger res = 0;
                BigInteger a = 0;
                a |= (odin << 0);
                for (int l = 1; l < 255; l++)
                {
                    if (rand.Next(0, 2) == 1)
                        a |= (odin << l);
                }
                a |= (odin << 255);
                res = BigInteger.ModPow(a, d, n);
                if (res == odin || res == (n - 1))
                    continue;
                if (res == n - 1)
                    continue;
                BigInteger j;
                for (j = 0; j < s; j++)
                {
                    res = BigInteger.ModPow(res, 2, n);
                    if (res == odin)
                        return false;
                    if (res == n - 1)
                        break;
                }
                if (j == s)
                    return false;
            }
            Console.WriteLine(n + "is IsPrime");
            return true;
        }
        static BigInteger modInverse(BigInteger a, BigInteger n)
        {
            BigInteger i = n, v = 0, d = 1;
            while (a > 0)
            {
                BigInteger t = i / a, x = a;
                a = i % x;
                i = x;
                x = d;
                d = v - t * x;
                v = x;
            }
            v %= n;
            if (v < 0) v = (v + n) % n;
            return v;
        }

        static void Main(string[] args)
        {
            int res = 0;
            Console.WriteLine("enter mode\n");
            res = Convert.ToInt32(Console.ReadLine());
            if (res == 1)
            {
                BigInteger msg = BigInteger.Parse("0014403d4565eb012929d34aeff3", NumberStyles.AllowHexSpecifier);
                BigInteger my_modulus = BigInteger.Parse("0092815357e083394274b4e0f28cb3a2157c8bc65d26e20ad8d2c963170bc16e15660238147be20a1a6adfd3e1192eafe66c0e199137bbde057f8f348385c85c77", NumberStyles.AllowHexSpecifier);
                BigInteger private_exp = BigInteger.Parse("00282184d2ed8d04824fb5bc68b46200642259a75c9cea0e4e966ed3d5dc428004af697efa085f8f134106f1d303a3f37f87fb2b1ad5b5b3e7b258a383057eb101", NumberStyles.AllowHexSpecifier);
                BigInteger site_modulus = BigInteger.Parse("00932AB34B0F3AEBE4A3AEDECBF336CE85A422150DF1A5148873D52BC15741D5E811150A919E6DF34F21CB3FC20B6DEB750EBEE3C7015DBAE9A1AA31E0B759008D", NumberStyles.AllowHexSpecifier);
                BigInteger Key = BigInteger.Parse("008AD88480536415DE108B1F108D08830F17C3BB27204DD4DB1B03D6BB395A9F122454E360EB2765139EFFC7BBB6D102AC57115E59E82F9611604E4DFF0C7EB0EF", NumberStyles.AllowHexSpecifier);
                BigInteger Sign = BigInteger.Parse("005F78E1794CAB3DBEC7CD88C532088BEDE3D68EBE52205E1598CEEC9BEE4A59F95620D925C0E4357CAC1E0FE4B88CC83A9B0DB074516AB831A22C59E9B884DF2F", NumberStyles.AllowHexSpecifier);
                BigInteger copy_s = Sign;
                Console.WriteLine("Key is" + Key);
                Console.WriteLine("Sign is " + Sign);
                Console.WriteLine("priv is " + private_exp);
                Console.WriteLine("modul is " + my_modulus);
                RSA_funcs.decrypt(ref Key, private_exp, my_modulus);
                Console.WriteLine("Key is " + Key);
                RSA_funcs.decrypt(ref Sign, private_exp, my_modulus);
                Console.WriteLine("Sign is " + Sign);
                RSA_funcs.verify(ref Sign, pub, site_modulus, copy_s);
                Console.WriteLine("Podpis = " + Sign + "\nKey = " + Key);
                if (Sign == Key)
                    Console.WriteLine("Verification Done");
                else
                    Console.WriteLine("Verification Failed!!!!!!!!!!!!!!!!");
                Sign = msg;
                RSA_funcs.sign(ref Sign, private_exp, my_modulus);
                RSA_funcs.encrypt(ref Sign, pub, site_modulus);
                RSA_funcs.encrypt(ref msg, pub, site_modulus);
                Console.WriteLine("Key = " + msg.ToString("x") + "\nSign = " + Sign.ToString("x"));
                return;
            }
            else
            {
                BigInteger[] ints = new BigInteger[4];
                Random rand = new Random();
                BigInteger odin = 1;
                BigInteger max = BigInteger.Parse("115792089237316195423570985008687907853269984665640564039457584007913129639935");
                for (int i = 0; i < 4; i++)
                {
                    ints[i] |= (odin << 0);
                    for (int l = 1; l < 255; l++)
                    {
                        if (rand.Next(0, 2) == 1)
                            ints[i] |= (odin << l);
                    }
                    ints[i] |= (odin << 255);
                    while (ints[i] < max)
                    {
                        if (ints[i] % 3 == 0 || ints[i] % 5 == 0 || ints[i] % 7 == 0 || ints[i] % 11 == 0 || ints[i] % 13 == 0)
                        {
                            ints[i] += 2;
                            continue;
                        }
                        if (IsPrime(ints[i], odin))
                            break;
                        ints[i] += 2;
                    }
                    if (ints[i] >= max)
                        i--;
                }
                BigInteger moduleA = ints[0] * ints[1];
                BigInteger moduleB = ints[2] * ints[3];
                BigInteger privateA = modInverse(pub, (ints[0] - 1) * (ints[1] - 1));
                BigInteger privateB = modInverse(pub, (ints[2] - 1) * (ints[3] - 1));
                Console.WriteLine("moduleA = " + moduleA.ToString("x") + "\nprivateA = " + privateA.ToString("x"));
                Console.WriteLine("moduleB = " + moduleB.ToString("x") + "\nprivateB = " + privateB.ToString("x"));
                BigInteger Msg = 0;
                Msg |= (odin << 0);
                for (int l = 1; l < 100; l++)
                {
                    if (rand.Next(0, 2) == 1)
                        Msg |= (odin << l);
                }
                Msg |= (odin << 100);
                Console.WriteLine(Msg.ToString("x"));
                BigInteger cp = Msg;
                RSA_funcs.encrypt(ref Msg, pub, moduleA);
                Console.WriteLine(Msg.ToString("x"));
                RSA_funcs.decrypt(ref Msg, privateA, moduleA);
                Console.WriteLine(Msg.ToString("x"));
                RSA_funcs.sign(ref Msg, privateB, moduleB);
                Console.WriteLine(Msg.ToString("x"));
                if (RSA_funcs.verify(ref Msg, pub, moduleB, cp))
                    Console.WriteLine("DEBUG: all fine");
                Console.WriteLine(Msg.ToString("x"));
            }
        }
    }
}
