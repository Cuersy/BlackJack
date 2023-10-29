#pragma once
#ifndef BLACKJACK_H
#define BLACKJACK_H
#include<time.h>
#include<stdlib.h>
#include <cwchar>
#include <windows.h>
#include "data.h"
#include<thread>
#include<chrono>
#include<string>
#include<iostream>
#include<nlohmann/json.hpp>
using namespace std;
user PRIV__USR;
class bj {
public:
	void blckjck() {
		srand(time(0));
		krElSize = 0;
		plrElSize = 0;
		krElSum = 0;
		plrElSum = 0;
		plrDone = false;
		krDone = false;
	};
	void playgame(user usr) {
		PRIV__USR = usr;
		json inf = usr.getInformations();
		cout << "BlackJack'e hosgeldin!" << endl << "Suanki paran : " + std::to_string(int(inf["money"])) << endl << "Bahis girin: ";
		cin >> this->bahis; cin.ignore();
		if (this->bahis <= 0) {
			cout << "Para 0 veya 0'dan kucuk olamaz!";
			while (1){}
		}
		else if (this->bahis > int(inf["money"])) {
			cout << "Paran yok la";
			while (1){}
		}
		addKrCard();
		addPlrCard();
		addPlrCard();
		sumHands();
		printHand();
		if (krElSum == 21) {
			win("kr");
			return;
		}
		if (plrElSum == 21) {
			win("plr");
			return;
		}
		if (plrEl[0] == 10 && plrEl[0] == plrEl[1]) {
		cout << "1: Stand, 2: Hit, 3: Double, 4: Split" << endl;
		cout << "Enter : ";
		int __Secim;
		cin >> __Secim; cin.ignore();
		if (__Secim == 1) {
			stand("plr");
		}
		else if (__Secim == 2) {
			addPlrCard();
			sumHands();
			printHand();
			cout << "1: Stand, 2: Hit" << endl;
			cout << "Enter : ";
			int __secim;
			cin >> __secim; cin.ignore();
			if (__secim == 1) {
				stand("plr");
			}
			else if (__secim == 2) {
				addPlrCard();
				sumHands();
				printHand();
				cout << "1: Stand, 2: Hit" << endl;
				cout << "Enter : ";
				int _secim;
				cin >> _secim; cin.ignore();
				if (_secim == 1) {
					stand("plr");
				}
				else if (__Secim == 2) {
					addPlrCard();
					sumHands();
					printHand();
				}
			}
		}
		}
		else {

		cout << "1: Stand, 2: Hit, 3: Double" << endl;
		cout << "Enter : ";
		int __Secim;
		cin >> __Secim; cin.ignore();
		if (__Secim == 1) {
			stand("plr");
		}
		else if (__Secim == 2) {
			addPlrCard();
			sumHands();
			printHand();
			if (!(int(this->getSums()["plr"]) > 21)) {
				cout << "1: Stand, 2: Hit" << endl;
				cout << "Enter : ";
				int __ssecim;
				cin >> __ssecim; cin.ignore();
				if (__ssecim == 1) {
					stand("plr");
				}
				else if (__ssecim == 2) {
					addPlrCard();
					sumHands();
					printHand();
					if (!(this->getSums()["plr"] > 21)) {
						cout << "1: Stand, 2: Hit" << endl;
						cout << "Enter : ";
						int __secim;
						cin >> __secim; cin.ignore();
						if (__secim == 1) {
							stand("plr");
						}
						else if (__secim == 2) {
							addPlrCard();
							sumHands();
							printHand();
							if (!(this->getSums()["plr"] > 21)) {
								cout << "1: Stand, 2: Hit" << endl;
								cout << "Enter : ";
								int _secim;
								cin >> _secim; cin.ignore();
								if (_secim == 1) {
									stand("plr");
								}
								else if (_secim == 2) {
									addPlrCard();
									sumHands();
									printHand();
									if (!(this->getSums()["plr"] > 21)) {
										cout << "1: Stand, 2: Hit" << endl;
										cout << "Enter : ";
										int _secim;
										cin >> _secim; cin.ignore();
										if (_secim == 1) {
											stand("plr");
										}
										else if (_secim == 2) {
											addPlrCard();
											sumHands();
											printHand();
											if (!(this->getSums()["plr"] > 21)) {
												cout << "1: Stand, 2: Hit" << endl;
												cout << "Enter : ";
												int _secim;
												cin >> _secim; cin.ignore();
												if (_secim == 1) {
													stand("plr");
												}
												else if (_secim == 2) {

												}
											}
											else {
												cout << "Kumarbaz Kaybetti.";
												win("kr");
											}
										}
									}
									else {
										cout << "Kumarbaz Kaybetti.";
										win("kr");
									}
								}
							}
							else {
								cout << "Kumarbaz Kaybetti.";
								win("kr");
							}
						}
					}
					else {
						cout << "Kumarbaz Kaybetti.";
						win("kr");
					}

				}
			}
			else {
				cout << "Kumarbaz Kaybetti.";
				win("kr");
			}
		}
		}
	};
private:
	int plrEl[10];
	int krupiyeEl[10];
	int krElSize;
	int plrElSize;
	int krElSum;
	int bahis;
	int plrElSum;
	int pHit;
	int pStand;
	bool plrDone;
	bool krDone;
	
	void addPlrCard() {
		if (!this->plrDone) {
			if (plrElSize <= 5) {
				this->plrEl[this->plrElSize] = 1 + (rand() % 10);
				this->plrElSize++;
			}
			else {
				cout << "Daha fazla kart cekemezsin bebegim";
				return;
			}
		}
		else {
			cout << "Player kart cekemez";
		}
		
	};
	void win(string who) {
		if (who == "plr") {
			usrdata s;
			if (s.addmoneyuser(this->bahis) && PRIV__USR.updateInformations()) {
				std::this_thread::sleep_for(chrono::milliseconds(1200));
				cout << endl << "Player Kazandi! Kazandiginiz para : " << this->bahis * 2 << " Toplam paraniz : " << PRIV__USR.getInformations()["money"];
			}
		}
		else if (who == "kr") {
			usrdata s;
			if (s.deletemoneyuser(this->bahis) && PRIV__USR.updateInformations()) {
				std::this_thread::sleep_for(chrono::milliseconds(1500));
			cout << endl << "Krupiyer kazandi! Kaybettigin para : " << this->bahis << " Toplam paraniz : " << PRIV__USR.getInformations()["money"];
			}
		}
	}
	int krsum = 0;
	void addKrCard() {
		if (!this->krDone && this->plrDone) {
			if (krElSize <= 5) {
				this->krupiyeEl[this->krElSize] = 1 + (rand() % 10);
				this->krElSize++;
			}
			else {
				cout << "Daha fazla kart cekemezsin bebegim";
			}
		}
		else {
			if (this->krsum == 0) {
				this->krsum++;
				if (krElSize <= 5) {
					this->krupiyeEl[this->krElSize] = 1 + (rand() % 10);
					this->krElSize++;
				}
				else {
					cout << "Daha fazla kart cekemezsin bebegim";
				}
			}
		}
	};
	json getSums() {
		json ret;
		int sum = 0;
		int sum2 = 0;
		for (int i = 0; i < krElSize; i++)
		{
			sum += krupiyeEl[i];
		}
		for (int i = 0; i < plrElSize; i++)
		{
			sum2 += plrEl[i];
		}
		ret["kr"] = sum;
		ret["plr"] = sum2;
		return ret;
	}
	
	void printHand() {
		cout << "Krupiyerin suanki eli...\n";
		int sum = 0; // krupiyer
		int sum1 = 0; // plr
		for (int j = 0; j < krElSize; j++)
		{
			sum += krupiyeEl[j];
			cout << "    -" << krupiyeEl[j] << "-    \n\n";
		}
		cout << "Krupiyerin kartlerinin toplami : " << sum << "\n\n";
		cout << "Kumarbazin suanki eli...\n";
		
		for (int i = 0; i < plrElSize; i++)
		{
			sum1 += plrEl[i];
			cout << "    -" << plrEl[i] << "-    \n\n";
		}
		cout << "Kumarbazin kartlerinin toplami : " << sum1 << "\n\n";
		sum = 0;
		sum1 = 0;
		
	};
	void sumHands() {
		//kr
		for (int i = 0; i <= krElSize; i++) {
			krElSum += krupiyeEl[i];
		}
		//plr
		for (int i = 0; i <= plrElSize; i++) {
			plrElSum += plrEl[i];
		}
	};
	void stand(string who) {
			if (!this->plrDone) {
				this->plrDone = true;
				while(1) {
					this->addKrCard();
					this->sumHands();
					this->printHand();
					json msms = this->getSums();
					if (msms["kr"] > msms["plr"] || msms["kr"] >= 21 ) break;
					this_thread::sleep_for(chrono::milliseconds(1500));
				}
				json sms = this->getSums();
				if (sms["plr"] > 21){
					win("kr");
				}
				else if (sms["kr"] <= 21 && sms["kr"] > sms["plr"]) {
					win("kr");
				}
				else if (sms["plr"] <= 21 && sms["kr"] < sms["plr"]) {
					win("plr");
				}
				else if (sms["kr"] > 21 || sms["plr"] < 22) {
					win("plr");
				}
				else if (sms["plr"] > 21 || sms["kr"] < 22) {
					win("kr");
				}
				else {
					cout << sms << endl;
					cout << "idk";
					exit(0);
				}
		}
	}

};
#endif