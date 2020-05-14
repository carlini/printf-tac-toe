# printf-tac-toe

A c implementation of tic-tac-toe in a single call to printf. Written for IOCCC 2020.

```c
#include <stdio.h> 

#define N(a)       "%"#a"$hhn"
#define O(a,b)     "%10$"#a"d"N(b)
#define U          "%10$.*37$d"
#define G(a)       "%"#a"$s"
#define H(a,b)     G(a)G(b)
#define T(a)       a a 
#define s(a)       T(a)T(a)
#define A(a)       s(a)T(a)a
#define n(a)       A(a)a
#define D(a)       n(a)A(a)
#define C(a)       D(a)a
#define R          C(C(N(12)G(12)))
#define o(a,b,c)   C(H(a,a))D(G(a))C(H(b,b)G(b))n(G(b))O(32,c)R
#define SS         O(78,55)R "\n\033[2J\n%26$s";
#define E(a,b,c,d) H(a,b)G(c)O(253,11)R G(11)O(255,11)R H(11,d)N(d)O(253,35)R
#define S(a,b)     O(254,11)H(a,b)N(68)R G(68)O(255,68)N(12)H(12,68)G(67)N(67)

char* fmt = O(10,39)N(40)N(41)N(42)N(43)N(66)N(69)N(24)O(22,65)O(5,70)O(8,44)N(
            45)N(46)N    (47)N(48)N(    49)N( 50)N(     51)N(52)N(53    )O( 28,
            54)O(5,        55) O(2,    56)O(3,57)O(      4,58 )O(13,    73)O(4,
            71 )N(   72)O   (20,59    )N(60)N(61)N(       62)N (63)N    (64)R R
            E(1,2,   3,13   )E(4,    5,6,13)E(7,8,9        ,13)E(1,4    ,7,13)E
            (2,5,8,        13)E(    3,6,9,13)E(1,5,         9,13)E(3    ,5,7,13
            )E(14,15,    16,23)    E(17,18,19,23)E(          20, 21,    22,23)E
            (14,17,20,23)E(15,    18,21,23)E(16,19,    22     ,23)E(    14, 18,
            22,23)E(16,18,20,    23)R U O(255 ,38)R    G (     38)O(    255,36)
            R H(13,23)O(255,    11)R H(11,36) O(254    ,36)     R G(    36 ) O(
            255,36)R S(1,14    )S(2,15)S(3, 16)S(4,    17 )S     (5,    18)S(6,
            19)S(7,20)S(8,    21)S(9    ,22)H(13,23    )H(36,     67    )N(11)R
            G(11)""O(255,    25 )R        s(C(G(11)    ))n (G(          11) )G(
            11)N(54)R C(    "aa")   s(A(   G(25)))T    (G(25))N         (69)R o
            (14,1,26)o(    15, 2,   27)o   (16,3,28    )o( 17,4,        29)o(18
            ,5,30)o(19    ,6,31)o(        20,7,32)o    (21,8,33)o       (22 ,9,
            34)n(C(U)    )N( 68)R H(    36,13)G(23)    N(11)R C(D(      G(11)))
            D(G(11))G(68)N(68)R G(68)O(49,35)R H(13,23)G(67)N(11)R C(H(11,11)G(
            11))A(G(11))C(H(36,36)G(36))s(G(36))O(32,58)R C(D(G(36)))A(G(36))SS

#define arg d+6,d+8,d+10,d+12,d+14,d+16,d+18,d+20,d+22,0,d+46,d+52,d+48,d+24,d\
            +26,d+28,d+30,d+32,d+34,d+36,d+38,d+40,d+50,(scanf(d+126,d+4),d+(6\
            -2)+18*(1-d[2]%2)+d[4]*2),d,d+66,d+68,d+70, d+78,d+80,d+82,d+90,d+\
            92,d+94,d+97,d+54,d[2],d+2,d+71,d+77,d+83,d+89,d+95,d+72,d+73,d+74\
            ,d+75,d+76,d+84,d+85,d+86,d+87,d+88,d+100,d+101,d+96,d+102,d+99,d+\
            67,d+69,d+79,d+81,d+91,d+93,d+98,d+103,d+58,d+60,d+98,d+126,d+127,\
            d+128,d+129

char d[538] = {1,0,10,0,10};

int main() {
    while(*d) printf(fmt, arg);
}
```

If this is the kind of thing that you enjoy, you might also like [printbf](https://github.com/HexHive/printbf).


## USAGE

    gcc -o prog prog.c
    ./prog

Alternates between P1 and P2. Enter a digit [1-9] to move:

    1 | 2 | 3
    ---------
    4 | 5 | 6
    ---------
    7 | 8 | 9

The game ends if:
- A player completes three in a row; that player wins
- All squares are taken; neither player wins
- A player makes an illegal move; their opponent wins


## WHY?

[IOCCC](http://ioccc.org)


## OBFUSCATION

The entirety of the program consists of a single call to printf.

    int main() {
        while(*d) printf(fmt, arg);
    }

Here, `fmt` is a single string, and `arg` is a series of arguments to printf.

While its primary purpose is to serve as The One True Debugger, printf also happens
to be Turing complete. (See "Control-Flow Bending: On the Effectiveness of Control-Flow
Integrity" where we introduced this in an actual, published, academic paper. The
things you can get away with sometimes.)

We ab^H^Huse this fact to implement a the logic of tic-tac-toe entirely within
this one printf call (and a call to scanf() to read user input).

Here's (briefly) how it works.

### Preliminaries

This program uses three printf format specifiers.
- `%d` takes an integer argument and prints it
- `%s` takes a string argument and prints it
- `%n` takes a pointer and writes (!!) the number of bytes printed so far.

Okay, everyone probably knows this. Let's get a bit more advanced.

Format specifiers can take extra "arguments".
- `"%hhn"`: store the number of bytes written mod 256 to the char pointer
- `"%2$d"`: print argument 2 to printf (and not the sequentially next argument)
- `"%8d"`: pad the printed integer to 8 characters
- `"%3$.*4$d"`: print argument 3 to printf with as many zeros as in argument 4.

For example, the following expression

    printf("%1$.*2$d%3$hhn", 5, 10, &x)

will have the same effect as if we had written

    x = 10;

because it will print out `0000000005` (5 padded to size 10) and then write the
number of bytes written to x.

### Printf Oriented Programming

Alright, now we can get to the real fun.

We perform arbitrary computation with printf treating memory as a binary
array---one bit per pair of bytes:
- The zero bit is represented by the sequence `00 00`
- The one-bit is represented by the sequence `xx 00` where `xx` is any non-zero byte.

We can use format strings to compute the OR/NOT of arbitrary "bits".

We'll start with the simplest, OR:

    printf("%1$s%2$s%3$hhn", a, b, c)

will compute

    *c = strlen(a) + strlen(b)

but given that strlen(x) is 1 for a 1-bit and 0 for a 0-bit, we have

    *c = a | b

Computing the NOT of a single value is also easy:

    printf("%1$255d%1$s%hhn", a, b)

will compute

    *b = (strlen(a)+255)%256 = strlen(a)-1

and again, because `strlen(x)` is either `1` or `0` we have

    *c = !b

From here we can compute any binary circuit. Doing something efficient,
though, still takes work.

### Tic-Tac-Toe

The game itself is represented as a board of 18 bits, 9 bits per player, along
with a turn counter that alternates between player 1 and player 2.

To detect who has won, we implement the following logic. Let A, B, and C be
pointers to three squares in a row to test, and D be where to save if there is a
win or not.

    "%A$s%B$s%C$s%1$253d%11$hhn" // r11 = !(*A & *B & *C)
    ZERO
    "%11$s%1$255d%11hhn" // r11 = !r11
    ZERO
    "%11$s%D$s%D$hhn" // *D = *D | r11

That is, we set `*D` to `1` if there is a three-in-a-row. We repeat this for all
possible three-in-a-row configurations, for both players.

The ZERO macro ensures that the number of bytes written out is 0 mod 256 with
the following expression

    "%1$hhn%1$s" (repeated 256 times)

where argument 1 is a pointer to a temporary variable followed by a null byte.

This works because if the current count is 0 mod 256, then "%1$hhn" will write
zero to argument 1 and then "%1$s" will never emit any text. If, on the other
hand, the count is not 0 mod 256, a length-1 string will be written to argument
1, and then "%1$s" will increment the count by one. By repeating this 256
times we're eventually going to reach 0 mod 256.

Checking if there has been an invalid move is achieved similarly.

In order to decide what to print out, we have to cast the "in-memory" array of
bits to Xs and Os to print out. This is actually rather straightforward. Given
in 1$ the pointer to player 1's square, and 2$ the pointer to player 2's, and
in 3$ the pointer to the board string, we can compute

    "%1$s" (repeated 47 times) "%2$s" (repeated 56 times) %1$32d%3$hhn"

which will, in effect, compute

    *r3 = (*r1) * 47 + (*r2) * 56 + 32

which will output ' ' if neither are true, 'X' if r1 is, or 'O' if r2 is.


### Further Obfuscations

In order to be able to finally display the board, while still only using one
printf statement, we finish the statement with

    "\n\033[2J\n%26$s"

which is the escape sequence to clear the screen, and then prints argument 26.
Argument 26 is a pointer to a char* in memory, that initially is undefined,
but within the printf statement we will construct this string to look like a
tic-tac-toe board.

After the board, we need to print one of the following strings:

    P1>_
    P2>_
    P1 WINS
    P2 WINS
    P1 TIES
    P2 TIES

Depending on if it's P1 or P2's turn to move, the game is over and someone
won, or the game is over and it is a draw.

This turns out not to be as hard as it might look. Using the same trick as
before, we set byte for to be

    *byte4 = is_win * 'W' + is_tie * 'T'

The byte `'I'` and `'S'` can always be the same, and we do the same for `'E'`/`'N'`.

We do this same on-the-fly creation of the `scanf()` format string, but for a
different reason. We first want to run `printf()` to show the first board, and
then alternate between runs to `scanf()` and `printf()` reading and then displaying
moves. importantly, we *do not* want a final scanf when the game ends. It should
just exit.

One option would be to implement the logic as

    printf()
    while (*ok) {
        scanf();
        printf();
    }

but this would DOUBLE the number of calls to printf we require. So instead we
implement it like this

    while (*ok) {
        scanf();
        printf();
    }

(In reality we actually pass `scanf()` as an argument to avoid the extra
statement, but it has the same effect.)

Notice there is now no initial `printf()`. In order make sure the program doesn't
block before the first `printf()`, but we initialize the `scanf()` format to the null
string so that it returns right away without blocking. The first time the `printf()`
call runs, it writes out `"%hhd"` to create the create the `scanf()` format string.


## LICENSE

This program is clearly some groundbreaking achievement the likes of which have
never been seen before. Therefore, if you would like to use this program in
anything, it's licensed under the GPL v3.

This program is free software: you can redistribute it and/or modify  
it under the terms of the GNU General Public License as published by  
the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
General Public License for more details.

You should have received a copy of the GNU General Public License 
along with this program. If not, see <http://www.gnu.org/licenses/>.
