/* printf-tac-toe: tic-tac-toe in a single call to printf
 * Copyright (C) 2020 Nicholas Carlini.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

// So you know how sometimes you'll see some program that has a small
// section where there's a "here be dragons" note?
// Because there's this one piece that's kind of ugly?
// Well, that starts now.
// <herebedragons>

// So in order to keep ourself a little bit sane we're going to use
// macros to define the common format specifiers we will use.

// This is our write op. We use %hhn that writes out just one byte:
// the number of characters printed so far, mod 256.
#define P(A) "%"#A"$hhn"

// This writes the constant A to position B
#define W(A,B) "%10$"#A"d"P(B)

// ... we'll get to this later. 
#define u "%10$.*37$d"

// Print out a given string.
#define s(A) "%"#A"$s"

// Do that, but twice. It's shorter.
#define t(A,B) s(A)s(B)

// Repeat the expression some number of times
#define x2(S) S S 
#define x4(S) x2(S)x2(S) 
#define x7(S) x4(S)x2(S)S
#define x8(S) x7(S)S
#define x15(S) x8(S)x7(S)
#define x16(S) x15(S)S

// Zero out the current "accumulator" to be 0 mod 256
#define ZERO x16(x16(P(12)s(12)))
#define b x4(P(12)s(12))

// Convert from 1/0 to X/O for printing to the board
#define CASTPR(A,B,C) x16(t(A,A))x15(s(A)) x16(t(B,B)s(B))x8(s(B)) W(32,C) ZERO

// Check if someone has won the game
#define TEST(A,B,C,D) t(A,B)s(C)W(253,11)b s(11)W(255,11)b t(11,D)P(D)W(253,35)b

// Look for both P1 and P2 on the same square
#define INVALID(A,B) W(254,11)t(A,B)P(68)ZERO s(68)W(255,68)P(12)t(12,68)s(67)P(67)


// Okay so here's our array.
// dat[0] stores whether or not we should continue looping.
// dat[2] stores the current turn counter, decremented by one every turn.
// dat[4] gets filled by scanf() to be the user's entered integer.
// dat[6:40] stores the bit-vector for P1 and P2s moves
// dat[66:102] stores the ascii version of the array to print out
// dat[126:129] stores the format specifier
char dat[18*2+2+500] = {1, 0, 10, 0, 10};

int main() {
  while (*dat)
    printf(W(10,39)
           // Okay so let's start out by constructing the actual board in memory
           // (and also the scanf format string)
           // 10: newline (board)
           P(40)P(41)P(42)P(43)P(66)P(69)P(24)
	   // 32: space (baord)
	   W(22,65)
	   //37: % (scanf)
	   W(5,70)
	   //45: - (board)
	   W(8,44)P(45)P(46)P(47)P(48)P(49)P(50)P(51)P(52)P(53)
	   //73: I (board)
	   W(28,54)
	   //78: (board)
	   W(5,55)
	   //80: (board)
	   W(2,56)
	   //83: (board)
	   W(3,57)
	   //87: (board)
	   W(4,58)
	   //100: d (scanf)
	   W(13,73)
	   //104: h (scanf)
	   W(4,71) P(72)
	   //124: (board)
	   W(20,59)P(60)P(61)P(62)P(63)P(64)
           ZERO

           // check if P1 has won in any way
           TEST(1,2,3,13)
           TEST(4,5,6,13)
           TEST(7,8,9,13)
           TEST(1,4,7,13)
           TEST(2,5,8,13)
           TEST(3,6,9,13)
           TEST(1,5,9,13)
           TEST(3,5,7,13)

           // check if P2 has won in any way
           TEST(14,15,16,23)
           TEST(17,18,19,23)
           TEST(20,21,22,23)
           TEST(14,17,20,23)
           TEST(15,18,21,23)
           TEST(16,19,22,23)
           TEST(14,18,22,23)
           TEST(16,18,20,23)
           ZERO

           // T -= 1
           u W(255,38)
           ZERO

           // r36 <- !T (is it a tie)
           s(38) W(255,36)
           ZERO

	   // r11 <- !(has someone won)
	   t(13,23) W(255, 11)
	   ZERO

	   // 36 <- !(has someone won) and tie
	   t(11,36) W(254, 36)
	   ZERO
	   s(36) W(255, 36)
	   ZERO
	   

           // Check if someone moved on top of another person
	   INVALID(1,14)
	   INVALID(2,15)
	   INVALID(3,16)
	   INVALID(4,17)
	   INVALID(5,18)
	   INVALID(6,19)
	   INVALID(7,20)
	   INVALID(8,21)
	   INVALID(9,22)
           
           // If either person won end the game
           // r11 <- dat wins (r13) | p2 wins (r23)| tie (r11) | invalid (r67)
           t(13,23)t(36,67) P(11)
           
           ZERO

           // go (r25) <- !r11 
           s(11) W(255, 25)

	   ZERO
           // put \0 or 'I' not in order to show the game-over person that won 
           x4(x16(s(11)))x8(s(11)) s(11) P(54)
	   
	   ZERO
	   // write either a space or a > token
	   x16("aa") x4(x7(s(25))) x2(s(25)) P(69)
	   
           ZERO

           // Convert the board array to Xs and Os for printing out all pretty like.
           CASTPR(14,1,26)
           CASTPR(15,2,27)
	   CASTPR(16,3,28)
           CASTPR(17,4,29)
	   CASTPR(18,5,30)
           CASTPR(19,6,31)
	   CASTPR(20,7,32)
           CASTPR(21,8,33)
	   CASTPR(22,9,34)

           // put 1 or 2 for the winner
	   // r68 <- T%2
	   x8(x16(u)) P(68)
	   ZERO

	   // r11 <- p1 wins or p2 wins or ties
	   t(36,13)s(23)P(11)
	   ZERO

           // If there's a winner, then flip the bit for which player we're on
	   // r68 <- r68 XOR r11
	   x16(x15(s(11)))x15(s(11)) s(68) P(68)
	   ZERO
	   
	   // print 1 or 2 for the person whose turn it is
           s(68) W(49,35)
           ZERO

	   t(13,23)s(67) P(11)
	   ZERO
	   
           // put space or 'W' for either 'P1> 'or 'P1 W', or a "T" for tie
	   x16(t(11,11)s(11))x7(s(11))
           x16(t(36,36)s(36))x4(s(36))
	   W(32,58)
	   ZERO

           // put N if not a tie, otherwise E if it is
	   x16(x15(s(36)))x7(s(36))
	   W(78,55)
	   ZERO

           // Hide the fact we just spewed garbage to the screen, and show the board
           "\n\033[2J\n%26$s"

           ,
           dat+6, dat+6+2, dat+6+4,
           dat+6+6, dat+6+8, dat+6+10,
           dat+6+12, dat+6+14, dat+6+16,
           0, // 10: zero byte
           dat+6+40, // 11: tmp byte for if the current row worked
           dat+6+40+6, // 12: used to zero things,
           dat+6+40+2, // 13: OR of any of the rows for P1

           // 14-22: P2 positions
           dat+6+18, dat+6+18+2, dat+6+18+4,
           dat+6+18+6, dat+6+18+8, dat+6+18+10,
           dat+6+18+12, dat+6+18+14, dat+6+18+16,
            
           dat+6+40+4, // 23: OR of any of the rows for P2

           // Okay so this is the one part that I'm not really happy about.
           // I do some math here to convert the integer that the user entered
           // to a board location.
           // It's possible to do it without this math, (by making the printf string
           // run twice for every scanf(), the first time doing the conversion, and
           // the second time doing the real work), but I ran out of time for IOCCC,
           // and decided I would just leave this the way it was.
           (scanf(dat+6+120, dat+4),dat+(6-2)+18*(1-dat[2]%2)+dat[4]*2), // 24: move to make
           dat, // 25, keep going

           // 26-34: board printf positions
           dat+6+60+0, dat+6+60+2, dat+6+60+4,
           dat+6+60+0+12, dat+6+60+2+12, dat+6+60+4+12,
           dat+6+60+0+24, dat+6+60+2+24, dat+6+60+4+24,

           // 35: P1/P2 win number
           dat+6+60+31,

           // 36: is the game a tie?
           dat+6+40+8,

           // 37: T
           dat[2],

           // 38: &T
           dat+2,

           // 39-43: newline
           dat+6+60+5+6*0,
           dat+6+60+5+6*1,
           dat+6+60+5+6*2,
           dat+6+60+5+6*3,
           dat+6+60+5+6*4,

           
           // 44-53: dashes
           dat+6+60+6+0,
           dat+6+60+6+1,
           dat+6+60+6+2,
           dat+6+60+6+3,
           dat+6+60+6+4,

           dat+6+60+6*3+0,
           dat+6+60+6*3+1,
           dat+6+60+6*3+2,
           dat+6+60+6*3+3,
           dat+6+60+6*3+4,

           // 54: I
           dat+6+60+34,

           // 55: N
           dat+6+60+35,

           // 56: P
           dat+6+60+30,

           // 57: S
           dat+6+60+36,

           // 58: W
           dat+6+60+33,

           // 59-64: |
           dat+6+60+1,
           dat+6+60+3,
           dat+6+60+12+1,
           dat+6+60+12+3,
           dat+6+60+24+1,
           dat+6+60+24+3,

           // 65: ' '
           dat+6+60+32,

           // 66: final newline
           dat+6+60+37,

           // 67: invalid move was made
           dat+6+40+12,
           // 68: scratch space
           dat+6+40+14,

           // 69: either space or > token
           dat+6+60+32,

           // 70-73: scanf %hhd
           dat+6+120+0,
           dat+6+120+1,
           dat+6+120+2,
           dat+6+120+3
           );
}

// Well. That happened.
// </herebedragons>
