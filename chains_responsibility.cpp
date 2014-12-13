// chains_responsibility.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;
using namespace System;

ref class Currency {

private:
	int amount;

public:
	Currency(int amt){
		this->amount=amt;
	}

	int getAmount(){
		return this->amount;
	}
};

ref class DispenseChain abstract {
public:
	virtual void setNextChain(DispenseChain^ nextChain) = 0;
	virtual void dispense(Currency^ cur) = 0;
};

ref class Dollar50Dispenser :  DispenseChain {
private:
	DispenseChain^ chain;
public:
	virtual void setNextChain  (DispenseChain^ nextChain) override {
		this->chain=nextChain;
	}

	virtual void dispense(Currency^ cur) override {
		if(cur->getAmount() >= 50){
			int num = cur->getAmount()/50;
			int remainder = cur->getAmount() % 50;
			Console::Write("Dispensing ");
			Console::Write(num);
			Console::Write(" 50$ note\n");

			if(remainder !=0) this->chain->dispense(gcnew Currency(remainder));
		}else{
			this->chain->dispense(cur);
		}
	}
};

ref class Dollar20Dispenser : DispenseChain{

private:
	DispenseChain^ chain;
public:
	virtual void setNextChain (DispenseChain^ nextChain) override  {
		this->chain=nextChain;
	}

	virtual void dispense(Currency^ cur) override {
		if(cur->getAmount() >= 20){
			int num = cur->getAmount()/20;
			int remainder = cur->getAmount() % 20;
			Console::Write("Dispensing ");
			Console::Write(num);
			Console::Write(" 20$ note\n");
			if(remainder !=0) this->chain->dispense(gcnew Currency(remainder));
		}else{
			this->chain->dispense(cur);
		}
	}

};


ref class Dollar10Dispenser : DispenseChain {

private:
	DispenseChain^ chain;
public:
	virtual void setNextChain (DispenseChain^ nextChain) override  {
		this->chain=nextChain;
	}

	virtual void dispense(Currency^ cur) override {
		if(cur->getAmount() >= 10){
			int num = cur->getAmount()/10;
			int remainder = cur->getAmount() % 10;
			Console::Write("Dispensing ");
			Console::Write(num);
			Console::Write(" 10$ note\n");
			if(remainder !=0) this->chain->dispense(gcnew Currency(remainder));
		}else{
			this->chain->dispense(cur);
		}
	}
};

ref class ATMDispenseChain {

private:
public:
	DispenseChain^ c1;
	ATMDispenseChain() {
		this->c1 = gcnew Dollar50Dispenser();
		DispenseChain^ c2 = gcnew Dollar20Dispenser();
		DispenseChain^ c3 = gcnew Dollar10Dispenser();
		c1->setNextChain(c2);
		c2->setNextChain(c3);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	ATMDispenseChain^ atmDispenser = gcnew ATMDispenseChain();
	while (true) {
		int amount = 0;
		Console::WriteLine("Enter amount to dispense");
		amount = Int32::Parse(Console::ReadLine());
		if (amount % 10 != 0) {
			Console::WriteLine("Amount should be in multiple of 10s.");
			return 0;
		}
		atmDispenser->c1->dispense(gcnew Currency(amount));
	}

	return 0;
}

