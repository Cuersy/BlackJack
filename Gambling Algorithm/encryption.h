#pragma once
#ifndef CRSY_ENCR
#define CRSY_ENCR
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cmath>
#include<nlohmann/json.hpp>
#include<random>
#include "../../../../Desktop/C++/globalfuncs.h"
#include "../../../../Desktop/C++/globalfuncs.cc"
using namespace std;
string encrypt(string str){
	return nlohmann::json::parse(httpget("https://api.hashify.net/hash/sha256/hex?value=" + str))["Digest"];
}
string genString(int length) {
	string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, charset.length() - 1);
	string randomString;
	for (int i = 0; i < length; i++) {
		int index = dist(gen);
		randomString += charset[index];
	}

	return randomString;
}
#endif