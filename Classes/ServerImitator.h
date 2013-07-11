/*
 * ServerImitator.h
 *
 *  Created on: 09-Jul-2013
 *      Author: sramanujan
 */

#ifndef SERVERIMITATOR_H_
#define SERVERIMITATOR_H_

class ServerImitator
{
	static int** _ticketCards;
	static bool isInitComplete;
	static bool _numbersCalledArray[75];
	static int _numbersCalled;
	static int _remainingNumbers[75];

public:
	ServerImitator()
	{

	}

	static int callOutNumber()
	{
		int index = (rand()%(75 - ServerImitator::_numbersCalled));
		int num = ServerImitator::_remainingNumbers[index];

		ServerImitator::_numbersCalledArray[num] = true;

		for (int j = index; j < (75 - ServerImitator::_numbersCalled); j++)
			ServerImitator::_remainingNumbers[j] = ServerImitator:: _remainingNumbers[j + 1];

		ServerImitator::_numbersCalled++;
		return num;
	}

	static void getTicketNumbers(int numTickets, int** ticketCards)
	{
		if(!ServerImitator::isInitComplete)
		{
			srand (time(NULL));
			populate75(_remainingNumbers);
		}
		for(int i = 0; i < numTickets; i ++)
		{
			getRandom24(ticketCards[i]);
		}
		ServerImitator::_ticketCards = ticketCards;
	}

	static void getRandom24(int* arr)
	{
		int arr75[75], len = 75, index, i, j;
		populate75(arr75);

		for(i = 0;i < 25;i++)
		{
			if(i == 12)
			{
				arr[i] = 0;
				continue;
			}
			index = (rand()%len);
			arr[i] = arr75[index];

			for (j = index; j < len; j++)
				arr75[j] = arr75[j + 1];
			len--;
		}
	}

	static void populate75(int* arr)
	{
		for(int i = 0; i < 75; i++)
		{
			arr[i] = i + 1;
		}
	}

	static bool checkForBingo(int k)
	{
		_ticketCards[k];
		for(int i = 0; i < 5; i++)
		{
			if(checkRowForBingo(_ticketCards[k], i)) return true;
		}
		for(int j = 0; j < 5; j++)
		{
			if(checkColumnForBingo(_ticketCards[k], j)) return true;
		}
		if(checkDiagonalSWForBingo(_ticketCards[k])) return true;
		if(checkDiagonalSEForBingo(_ticketCards[k])) return true;

		return false;
	}

	static bool checkRowForBingo(int* ticket, int row)
	{
		for(int i = 0;i < 5; i++)
		{
			if(!ServerImitator::_numbersCalledArray[ticket[5*row + i]]) return false;
		}
		return true;
	}

	static bool checkColumnForBingo(int* ticket, int column)
	{
		for(int i = 0;i < 5; i++)
		{
			if(!ServerImitator::_numbersCalledArray[ticket[5*i + column]]) return false;
		}
		return true;
	}

	static bool checkDiagonalSWForBingo(int* ticket)
	{
		for(int i = 0;i < 5; i++)
		{
			if(!ServerImitator::_numbersCalledArray[ticket[4*i]]) return false;
		}
		return true;
	}

	static bool checkDiagonalSEForBingo(int* ticket)
	{
		for(int i = 0;i < 5; i++)
		{
			if(!ServerImitator::_numbersCalledArray[ticket[6*i]]) return false;
		}
		return true;
	}

};

int** ServerImitator::_ticketCards = NULL;
bool ServerImitator::isInitComplete = false;
int ServerImitator::_numbersCalled = 0;
bool ServerImitator::_numbersCalledArray[75] = {};
int ServerImitator::_remainingNumbers[75] = {};


#endif /* SERVERIMITATOR_H_ */
