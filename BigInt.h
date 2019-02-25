/*
 * Created by Raheeb Hassan, 2nd year, University of Dhaka
 *
 * This is a simple implementation of a Big integer class
 * ( similar to BigInteger in Java and int in Python )
 * which supports almost all functionality of normal integers
 * (it was in largely inspired and takes from
 * http://lightoj.com/article_show.php?article=1004 )
 *
 * Components:
 * It uses a string to store the digits of the number in base 10
 * so the largest value it can hold is about 10 ^ std::string::max()
 * It also has a standard integer to hold the sign of the number
 *
 * Operators:
 * Most operators that apply to integers have been overloaded for this class,
 * * Assignment operator (numerical types and string types)
 * * Arithmetic operators (binary, unary)
 * * Comparison operators
 * * Typecast operators
 * * C++ stream insertion and extraction operators (for IO)
 *
 * Few auxillary functions such as pow, abs, to_string have been overloaded
 * to mimic their corresponding functionality for standard numerical types
 *
 * Memory:
 * It takes approximately ceil(log10(n)) bytes where n is the integer stored
 *
 * Note:
 * The arithmetic operations are done with naive grade school algorithms
 * and can be done faster with more complex algorithms (might implement in future)
 * The storage technique used is also not the most efficient,
 * better memory efficiency might be achieved by storing the numbers in higher base (less digits)
 * or storing a variable length array of integers
 *
 * Usage:
 * You are free to use or modify this code fully or partially for any project or contest
 * Giving credit is not required (although wouldn't mind if you do :3)
 *
 * TLDR: It can do almost anything a normal integer can do
 * with numbers larger than what you'll probably ever need
 *
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>


#ifndef BIGINT_LIBRARY_BIGINT_H
#define BIGINT_LIBRARY_BIGINT_H

namespace rxh
{
    class BigInt {
    public:
        // constructors based on assignment operator
        BigInt() { (*this) = 0; }
        template <class T> BigInt(T a) { (*this) = a; }

        // returns the number of digits in base 10
        inline size_t digits() const { return num.size(); }

        // assignment operators
        // for numerical types (int, long)
        template <class T> BigInt& operator = (T a);
        // for string types
        BigInt& operator = (std::string a);
        BigInt& operator = (const char* a);

        // unary operators
        inline BigInt operator - () const { return BigInt(*this).inverseSign(); }
        inline BigInt operator + () const { return (*this); }

        // binary operators
        BigInt operator + (const BigInt &a) const;
        BigInt operator - (const BigInt &a) const;
        BigInt operator * (BigInt a) const;
        BigInt operator / (BigInt a) const;
        BigInt operator % (BigInt a) const;

        // exponentiation operator
        inline BigInt operator ^ (unsigned int exp) { return pow(*this, exp); }

        inline BigInt& operator += (const BigInt& a) { (*this) = (*this) + a; return (*this); }
        inline BigInt& operator -= (const BigInt& a) { (*this) = (*this) - a; return (*this); }
        inline BigInt& operator *= (const BigInt& a) { (*this) = (*this) * a; return (*this); }
        inline BigInt& operator /= (const BigInt& a) { (*this) = (*this) / a; return (*this); }
        inline BigInt& operator %= (const BigInt& a) { (*this) = (*this) % a; return (*this); }

        // pre-increment operators
        inline BigInt& operator ++ () { return (*this) += 1; }
        inline BigInt& operator -- () { return (*this) -= 1; }
        // post-increment operators
        inline BigInt operator ++ (int) { BigInt c(*this); ++(*this); return c; }
        inline BigInt operator -- (int) { BigInt c(*this); --(*this); return c; }

        // comparison operators
        inline bool operator < (const BigInt& a) const;
        inline bool operator > (const BigInt& a) const {return a < (*this);}

        inline bool operator == (const BigInt& a) const { return sign == a.sign && num == a.num; }
        inline bool operator != (const BigInt& a) const { return sign != a.sign || num != a.num; }

        inline bool operator <= (const BigInt& a) const { return (*this) < a || (*this) == a; }
        inline bool operator >= (const BigInt& a) const { return (*this) > a || (*this) == a; }

        // typecast operator (for numerical types)
        template <class T> inline operator T();

        void print();

        // auxillary funcions
        friend inline BigInt pow(const BigInt& a, unsigned int exp);
        friend inline BigInt abs(const BigInt& a) { return BigInt(a).normalize(1); }
        friend inline std::string to_string(BigInt a);

        // I/O functions (using C++ I/O streams)
        friend std::ostream & operator << (std::ostream &out, const BigInt &c);
        friend std::istream & operator >> (std::istream &in, BigInt &c);

    private:
        std::string num;
        int sign;

        // remove leading zeroes and fix sign
        BigInt normalize(int newSign);
        BigInt inverseSign() { sign *= -1; return (*this); }
    };

    BigInt BigInt::normalize(int newSign) {
        for(long long i = num.size() - 1; i > 0 && num[i] == '0'; i--)
            num.erase(num.begin() + i);
        sign = (num.size() == 1 && num[0] == '0') ? 1 : newSign;
        return (*this);
    }

    template <class T>
    BigInt& BigInt::operator =(T a) {
        return (*this) = std::to_string(a);
    }

    BigInt& BigInt::operator =(std::string b) {
        this->num = b[0] == '-' ? b.substr(1) : b;
        auto dotPos = this->num.find(".");
        if (dotPos != std::string::npos) this->num.erase(dotPos);
        std::reverse(this->num.begin(), this->num.end());
        this->normalize(b[0] == '-' ? -1 : 1);
        return (*this);
    }

    BigInt& BigInt::operator =(const char* b) {
        return (*this) = std::string(b);
    }

    bool BigInt::operator <(const BigInt &a) const {
        if (sign != a.sign) return sign < a.sign;
        if (num.size() != a.num.size())
            return sign == 1 ? num.size() < a.num.size() : num.size() > a.num.size();
        for (size_t i = digits(); i --> 0; )
            if (num[i] != a.num[i])
                return sign == 1 ? num[i] < a.num[i] : num[i] > a.num[i];
        return false;
    }

    BigInt BigInt::operator +(const BigInt &a) const {
        if (sign != a.sign) return (*this) - (-a);
        BigInt c; c.num.clear();
        for (long long i = 0, carry = 0; i<num.size() || i<a.digits() || carry; i++ ) {
            carry+=(i<num.size() ? num[i]-48 : 0)+(i<a.num.size() ? a.num[i]-48 : 0);
            c.num += (carry % 10 + 48);
            carry /= 10;
        }
        return c.normalize(sign);
    }

    BigInt BigInt::operator -(const BigInt &a) const {
        if (sign != a.sign) return (*this) + (-a);
        int s = sign; // sign = a.sign = 1;
        if (abs(*this) < abs(a)) return ((abs(a) - abs(*this)).inverseSign()).normalize(-s);
        BigInt c; c.num.clear();
        for (long long i = 0, borrow = 0; i < num.size(); i++) {
            borrow = num[i] - borrow - (i < a.digits() ? a.num[i] : 48);
            c.num += borrow >= 0 ? borrow + 48 : borrow + 58;
            borrow = borrow >= 0 ? 0 : 1;
        }
        return c.normalize(s);
    }

    BigInt BigInt::operator *(BigInt a) const {
        BigInt c("0");
        for (long long i = 0, k = num[i] - 48; i < num.size(); i++, k = num[i] - 48) {
            while(k--) c = c + a;
            a.num.insert(a.num.begin(), '0');
        }
        return c.normalize(sign * a.sign);
    }

    BigInt BigInt::operator /(BigInt a) const {
        if (a.digits() == 1 && a.num[0] == '0') a.num[0] /= ( a.num[0] - 48 );
        BigInt c("0"), d;
        for(long long j = 0; j < num.size(); j++) d.num += "0";
        int dSign = sign * a.sign; a.sign = 1;
        for (size_t i = digits(); i --> 0; ) {
            c.num.insert( c.num.begin(), '0');
            c = c + num.substr( i, 1 );
            while(!( c < a )) c = c - a, d.num[i]++;
        }
        return d.normalize(dSign);
    }

    BigInt BigInt::operator %(BigInt a) const {
        if (a.digits() == 1 && a.num[0] == '0') a.num[0] /= ( a.num[0] - 48 );
        BigInt c("0");
        a.sign = 1;
        for (size_t i = digits(); i --> 0; ) {
            c.num.insert( c.num.begin(), '0');
            c = c + num.substr( i, 1 );
            while(!( c < a )) c = c - a;
        }
        return c.normalize(sign);
    }

    void BigInt::print() {
        if (sign == -1) putchar('-');
        for (size_t i = digits(); i --> 0; ) putchar(num[i]);
    }

    std::ostream & operator << (std::ostream &out, const BigInt &c) {
        if (c.sign == -1) out << '-';
        for (auto i = c.num.rbegin(); i != c.num.rend(); i++) out << *i;
        return out;
    }

    std::istream & operator >> (std::istream &in, BigInt &c) {
        std::string temp; in >> temp;
        c = temp;
        return in;
    }

    BigInt pow(const BigInt& a, unsigned int exp) {
        BigInt temp = 1;
        for (size_t i = 1; i <= exp; i++) temp *= a;
        return temp;
    }

    template<class T>
    BigInt::operator T() {
        T temp = 0;
        for (size_t i = digits(); i --> 0; ) {
            temp = (temp * 10 + (num[i] - '0'));
        }
        return temp * this->sign;
    }

    std::string to_string(BigInt a) {
        std::string temp(a.num);
        if (a.sign == -1) temp += '-';
        std::reverse(temp.begin(), temp.end());
        return temp;
    }
}


#endif //BIGINT_LIBRARY_BIGINT_H
