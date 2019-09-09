# Big Integer Library
Simple implementation of a Big integer class using strings

This is a simple implementation of a Big integer class
(similar to BigInteger in Java and int in Python)
which supports almost all functionality of normal integers
(it was in largely inspired and takes from [this article](http://lightoj.com/article_show.php?article=1004))

### Pretext
We know that machines are inherently limited in the largest integer it can store and manipulate. For most systems it is around 
2<sup>64</sup> - 1 (64 bits). Although many languages like Java and Python have built in libraries which can be used to circumvent this
restriction, sadly C++ does not (yet). 

### Components:
It uses a string to store the digits of the number in base 10.
So the largest value it can hold is about 10 ^ `std::string::max()`.
It also has a standard integer to hold the sign of the number

### Operators:
Most operators that apply to integers have been overloaded for this class,
 * Assignment operator (numerical types and string types)
 * Arithmetic operators (binary, unary)
 * Comparison operators
 * Typecast operators
 * C++ stream insertion and extraction operators (for IO)

Few auxillary functions such as pow, abs, to_string have been overloaded
to mimic their corresponding functionality for standard numerical types

### Memory:
It takes approximately 
<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\lceil&space;log_{10}(n)&space;\rceil" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\lceil&space;log_{10}(n)&space;\rceil" title="\lceil log_{10}(n) \rceil" /></a> 
 bytes where n is the integer stored

### Note:
The arithmetic operations are done with naive grade school algorithms
and can be done faster with more complex algorithms (might implement in future).
The storage technique used is also not the most efficient,
better memory efficiency might be achieved by storing the numbers in higher base (less digits)
or storing a variable length array of integers

### Usage:
You are free to use or modify this code fully or partially for any project or contest.
Giving credit is not required (although wouldn't mind if you do :3)

#### TLDR: 
It can do almost anything a normal integer can do
with numbers larger than what you'll probably ever need
