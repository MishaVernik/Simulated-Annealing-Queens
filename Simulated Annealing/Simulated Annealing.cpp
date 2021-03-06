#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

const int MAX		= 1000;
const double T0		= 200;
const double ALPHA	= 0.998;

typedef struct solution 
{
	int positionQueens[MAX];
	int cost;
};

solution curr, next, best;
double T = T0;
int filedSize;


/*
	Function: SetCost
	Sets the cost to each queen on the desk
	Costs are determined by the number of intersections 

	@params curr, type solution - current position queens map

*/
void SetCost(solution& curr)
{
	curr.cost = 0;
	for (int i = 0; i < filedSize; ++i)
		for (int j = i + 1; j < filedSize; ++j)
			if (abs(i - j) == abs(curr.positionQueens[i] - curr.positionQueens[j]))
				curr.cost += 1;
}

/*
	Function: SetNext
	Change k times the position of queens on the map
	k - filendSize * (TEMPERATURE / START_TEMPERATURE) + 1
	After, establish costs

	@params next, type solution - creates a new location for queens
*/
void SetNext(solution& next) 
{
	next = curr;
	int k = filedSize * T / T0 + 1;
	for (int i = 0; i < k; ++i) {
		int rnd1 = int(double(rand()) / RAND_MAX * filedSize);
		int rnd2 = int(double(rand()) / RAND_MAX * filedSize);
		std::swap(next.positionQueens[rnd1], next.positionQueens[rnd2]);
	}
	SetCost(next);
}

/*
	Function: Admit
	Determines the probability of a change in the queens position.
	(current will be equal to the next) 

	@params dF, type int - the difference between current and next
	@return bool - will be changed or not
*/
bool Admit(int dF) 
{
	return dF < 0 || exp(double(-dF) / T) >(double(rand()) / RAND_MAX / 2);
}


/*
	Function: Display
	Show location map of queens
	Q - in this position we have a queen
	. - empty cell

	@params best, type solution - visualizing the best solution
*/
void Display(solution best) 
{
	for (int i = 0; i < filedSize; ++i)
	{
		for (int j = 0; j < best.positionQueens[i]; ++j)
			cout << ".";
		cout << "Q";
		for (int j = best.positionQueens[i] + 1; j < filedSize; ++j)
			cout << ".";
		cout << std::endl;
	}
}



int main() 
{

	cin >> filedSize;

	/*
		Determining the position of queens by type ( 0 , 1 , 2 ...)
	*/
	for (int i = 0; i < filedSize; i++)
		curr.positionQueens[i] = i;

	/*
		Determine the initial cost
		and let the best solution be equal to the current
	*/
	SetCost(curr);
	best = curr;

	while (best.cost > 0) 
	{
		SetNext(::next);
		if (Admit(::next.cost - curr.cost))
		{
			curr = ::next;
			if (::next.cost < best.cost)
			{
				best = ::next;
			}
		}
		T *= ALPHA;
	}

	for (int i = 0; i < filedSize; ++i)
		cout << best.positionQueens[i] + 1 << " ";

	cout << std::endl;
	cout << "Number of intersections : " << best.cost << std::endl;
	Display(best);

	return 0;
}

