#include<cmath>
#include<iostream>
#include "encryption.h"
#include "blackjack.h"
#include "data.h"
#define ll long long
#define ld long double
using namespace std;

/*ld encryptNumber(const int& number) {
	ll sum = 1;
	if (number <= 0) return -1;
	for (int i = 0; i <= number; i++) {
		sum *= i;
	}
}*/

int main() {
	user a;
	string sessionid = a.login("sttrd", "kumarbaz");
	bj __a;
	__a.blckjck();
	__a.playgame(a);
	while(1){}
}