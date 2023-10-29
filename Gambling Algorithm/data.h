#pragma once
#ifndef DATA_H
#define DATA_H
#include<nlohmann/json.hpp>
#include<fstream>
#include "encryption.h"
#include<string>
using namespace std;
using json = nlohmann::json;
#define ll long long
std::string PRIV__SESSID = "";
std::string PRIV__USRID = "";
std::string PRIV__USRSCID = "";
class user{
private:
	bool isLogin = false;
	string userId;
	string sessionId;
	string pass;
	string usernme;
	int playedCount;
	int winCount;
	int money;
	ll totalBetted;
	int loseCount;
	json last10Matchs;
	json getDatas() {
		json __a;
		ifstream datajson("data.json");
		string aa;
		while (getline(datajson, aa)) {
			return json::parse(aa);
		}
		return __a;
	}
	bool writeNewData(json data) {
		try {
			string type = data["type"];
			json newData = data["data"];
			ofstream datajson("data.json");
			if (type == "newuser") {
				datajson << newData;
				datajson.close();
			}
			return true;
		}
		catch (string error) {
			cout << error << endl;
		}

	}
public:
	
	string login(const string& username, const string& password) {
		this->usernme = username;
		this->pass = password;
		json data = getDatas();
			string encded = encrypt(username + password);
		if (data["users"][encded] != nullptr) {
			string sesid = genString(35);
			PRIV__USRSCID = encded;
			json usr = data["users"][encded];
			PRIV__SESSID = sesid;
			PRIV__USRID = usr["userId"];
			this->isLogin = true;
			this->last10Matchs = usr["last10Matchs"];
			this->sessionId = sesid;
			this->playedCount = usr["playedCount"];
			this->money = usr["money"];
			this->totalBetted = usr["totalBetted"];
			this->userId = usr["userId"];
			this->winCount = usr["winCount"];
			this->loseCount = usr["loseCount"];
			cout << "Login Successfull" << endl;
			return sesid;
		}
		else {
			json a; 
			json data = getDatas();
			json newdata = data;
			string sesid = genString(35);
			string usrid = genString(30);
			string encded = encrypt(username + password);
			newdata["users"][encded]["userId"] = usrid;
			newdata["users"][encded]["sessionId"] = sesid;
			newdata["users"][encded]["money"] = 20000;
			newdata["users"][encded]["playedCount"] = 0;
			newdata["users"][encded]["totalBetted"] = 0;
			newdata["users"][encded]["winCount"] = 0;
			newdata["users"][encded]["loseCount"] = 0;
			newdata["users"][encded]["last10Matchs"] = a;
			this->sessionId = sesid;
			PRIV__USRSCID = encded;
			this->userId = usrid;
			this->last10Matchs = a;
			this->money = 20000;
			this->winCount = 0;
			this->loseCount = 0;
			this->totalBetted = 0;
			this->playedCount = 0;
			this->isLogin = true;
			json sendData;
			sendData["data"] = newdata;
			sendData["type"] = "newuser";
			writeNewData(sendData);
			cout << "Account created!" << endl;
			return sesid;
		}
	}
	bool updateInformations() {
		ifstream __afs("data.json");
		string line;
		json data;
		while (getline(__afs, line)) {
			data = json::parse(line);
		}
		/*
		this->sessionId = sesid;
			PRIV__USRSCID = encded;
			this->userId = usrid;
			this->last10Matchs = a;
			this->money = 20000;
			this->winCount = 0;
			this->loseCount = 0;
			this->totalBetted = 0;
			this->playedCount = 0;
			this->isLogin = true;*/
		this->money =  data["users"][PRIV__USRSCID]["money"];
		return true;
	}
	json getInformations(){
		json callback;
		if (!this->isLogin) {
			callback["status"] = "failure";
			callback["message"] = "Player is not logged in.";
			return callback;
		}
		else {
			json infrmtns;
			json privInfrm;
			infrmtns["winCount"] = this->winCount;
			privInfrm["sessionId"] = this->sessionId;
			infrmtns["loseCount"] = this->loseCount;
			infrmtns["last10Matchs"] = this->last10Matchs;
			privInfrm["userId"] = this->userId;
			callback["informations"] = infrmtns;
			callback["money"] = this->money;
			callback["privInfrm"] = privInfrm;
			return callback;
		}
	}
};

class usrdata {
private:
	string usrid;

public:
	json getDatas() {
		json __a;
		ifstream datajson("data.json");
		string aa;
		while (getline(datajson, aa)) {
			return json::parse(aa);
		}
		return __a;
	}
	bool addmoneyuser(int money){
		json datas= getDatas();
		json usrs = datas["users"][PRIV__USRSCID];
			json sonhal = datas;
			sonhal["users"][PRIV__USRSCID]["money"] = usrs["money"] + int(money);
			ofstream wTd("data.json");
			wTd << sonhal;
			wTd.close();
		return true;
	}
	bool deletemoneyuser(int money) {
		json datas = getDatas();
		json usrs = datas["users"][PRIV__USRSCID];
		json sonhal = datas;
		sonhal["users"][PRIV__USRSCID]["money"] = usrs["money"] - int(money);
		ofstream wTd("data.json");
		wTd << sonhal;
		wTd.close();
		return true;
	}
};
#endif