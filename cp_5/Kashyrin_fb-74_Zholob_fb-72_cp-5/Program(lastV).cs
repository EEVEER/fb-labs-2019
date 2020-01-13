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
        static bool IsPrime(BigInteger n, BigInteger odin, int bits)
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
                for (int l = 1; l < bits - 1; l++)
                {
                    if (rand.Next(0, 2) == 1)
                        a |= (odin << l);
                }
                a |= (odin << bits - 1);
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

        static void receive_key(BigInteger Sign, BigInteger private_exp, BigInteger my_modulus, BigInteger Key, BigInteger pub_exp_my, BigInteger site_modulus)
        {
            BigInteger copy_s = Sign;
            Console.WriteLine("Key is" + Key);
            Console.WriteLine("Sign is " + Sign);
            Console.WriteLine("priv is " + private_exp);
            Console.WriteLine("modul is " + my_modulus);
            RSA_funcs.decrypt(ref Key, private_exp, my_modulus);
            Console.WriteLine("Key is " + Key);
            RSA_funcs.decrypt(ref Sign, private_exp, my_modulus);
            Console.WriteLine("Sign is " + Sign);
            RSA_funcs.verify(ref Sign, pub_exp_my, site_modulus, copy_s);
            Console.WriteLine("Podpis = " + Sign + "\nKey = " + Key);
            if (Sign == Key)
                Console.WriteLine("Verification Done");
            else
                Console.WriteLine("Verification Failed!!!!!!!!!!!!!!!!");
        }

        static void send_key(BigInteger msg, BigInteger private_exp, BigInteger my_modulus, BigInteger site_modulus, BigInteger pub_exp_site)
        {
            BigInteger Sign = msg;
            RSA_funcs.sign(ref Sign, private_exp, my_modulus);
            RSA_funcs.encrypt(ref Sign, pub_exp_site, site_modulus);
            RSA_funcs.encrypt(ref msg, pub_exp_site, site_modulus);
            Console.WriteLine("Key = " + msg.ToString("x") + "\nSign = " + Sign.ToString("x"));
        }
        static BigInteger nod(BigInteger n1, BigInteger m1)
        {
            BigInteger n = n1;
            BigInteger m = m1;
            BigInteger p = n % m;
            while (p != 0)
            {
                n = m;
                m = p;
                p = n % m;
            }
            return m;
        }

        static void get_prime(int num, ref BigInteger ints)
        {
            Random rand = new Random();
            BigInteger odin = 1;
            BigInteger max = 0;
            for (int i = 0; i < num / 2; i++)
            {
                max |= (odin << i);
            }
            ints |= (odin << 0);
            for (int l = 2; l < num / 2 - 2; l++)
            {
                if (rand.Next(0, 2) == 1)
                    ints |= (odin << l);
            }
            ints |= (odin << num / 2 - 2);// перенес бит сюда
            ints |= (odin << num / 2 - 1);
            while (ints < max)
            {
                if (ints % 3 == 0 || ints % 5 == 0 || ints % 7 == 0 || ints % 11 == 0 || ints % 13 == 0)
                {
                    ints += 2;
                    continue;
                }
                if (IsPrime(ints, odin, num / 2))
                    break;
                ints += 2;
            }
            if (ints >= max)
                get_prime(num, ref ints);
        }

            static void generateKeyPair(int num, out BigInteger module, out BigInteger pub, out BigInteger priv)
        {
            BigInteger[] ints = new BigInteger[2];
            Random rand = new Random();
            BigInteger odin = 1;
            get_prime(num, ref ints[0]);
            get_prime(num, ref ints[1]);
            module = ints[0] * ints[1];
            pub = rand.Next(100000, 1000000);
            pub |= (odin << 0);// делаем pub непарным
            while (true)
            {
                if (nod(pub, (ints[0] - 1) * (ints[1] - 1)) == 1)
                    break;
                pub += 2;
            }
            priv = modInverse(pub, (ints[0] - 1) * (ints[1] - 1));
        }

        static void Main(string[] args)
        {
            int res = 0;
            Console.WriteLine("enter mode\n");
            res = Convert.ToInt32(Console.ReadLine());
            BigInteger first = 0;
            BigInteger second = 0;
            BigInteger odin = 1;
            first |= (odin << 0);
            first |= (odin << 31);
            first |= (odin << 30);
            second |= (odin << 31);
            second |= (odin << 0);
            second |= (odin << 30);
            Console.WriteLine(first);
            Console.WriteLine(second);
            Console.WriteLine(first * second);
            if (res == 1)
            {
                BigInteger msg = BigInteger.Parse("0014403d4565eb012929d34aeff3", NumberStyles.AllowHexSpecifier);
                BigInteger my_modulus = BigInteger.Parse("0092815357e083394274b4e0f28cb3a2157c8bc65d26e20ad8d2c963170bc16e15660238147be20a1a6adfd3e1192eafe66c0e199137bbde057f8f348385c85c77", NumberStyles.AllowHexSpecifier);
                BigInteger private_exp = BigInteger.Parse("00282184d2ed8d04824fb5bc68b46200642259a75c9cea0e4e966ed3d5dc428004af697efa085f8f134106f1d303a3f37f87fb2b1ad5b5b3e7b258a383057eb101", NumberStyles.AllowHexSpecifier);
                BigInteger site_modulus = BigInteger.Parse("00932AB34B0F3AEBE4A3AEDECBF336CE85A422150DF1A5148873D52BC15741D5E811150A919E6DF34F21CB3FC20B6DEB750EBEE3C7015DBAE9A1AA31E0B759008D", NumberStyles.AllowHexSpecifier);
                BigInteger Key = BigInteger.Parse("008AD88480536415DE108B1F108D08830F17C3BB27204DD4DB1B03D6BB395A9F122454E360EB2765139EFFC7BBB6D102AC57115E59E82F9611604E4DFF0C7EB0EF", NumberStyles.AllowHexSpecifier);
                BigInteger Sign = BigInteger.Parse("005F78E1794CAB3DBEC7CD88C532088BEDE3D68EBE52205E1598CEEC9BEE4A59F95620D925C0E4357CAC1E0FE4B88CC83A9B0DB074516AB831A22C59E9B884DF2F", NumberStyles.AllowHexSpecifier);
                BigInteger pub_site = BigInteger.Parse("65537");
                BigInteger pub_my = BigInteger.Parse("65537");
                receive_key(Sign, private_exp, my_modulus, pub_my, Key, site_modulus);
                send_key(msg, private_exp, my_modulus, site_modulus, pub_site);
                return;
            }
            else
            {
                Random rand = new Random();
                generateKeyPair(256, out BigInteger moduleA, out BigInteger pubA, out BigInteger privA);
                generateKeyPair(256, out BigInteger moduleB, out BigInteger pubB, out BigInteger privB);
                Console.WriteLine("moduleA = " + moduleA.ToString("x") + "\nprivateA = " + privA.ToString("x") + "\npubA = " + pubA.ToString("x"));
                Console.WriteLine("moduleB = " + moduleB.ToString("x") + "\nprivateB = " + privB.ToString("x") + "\npubB = " + pubB.ToString("x"));           
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
                RSA_funcs.encrypt(ref Msg, pubA, moduleA);
                Console.WriteLine(Msg.ToString("x"));
                RSA_funcs.decrypt(ref Msg, privA, moduleA);
                Console.WriteLine(Msg.ToString("x"));
                RSA_funcs.sign(ref Msg, privB, moduleB);
                Console.WriteLine(Msg.ToString("x"));
                if (RSA_funcs.verify(ref Msg, pubB, moduleB, cp))
                    Console.WriteLine("DEBUG: all fine");
                Console.WriteLine(Msg.ToString("x"));
            }
        }
    }
}
