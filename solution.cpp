//Reference: https://github.com/WellyWong/content/blob/master/HW0.ipynb

//Simulate the opening of a "goat door" (revealedDoor) that doesn't contain the prize,
//and is different from the contestants guess
void revealedGoatDoor(std::vector<int>& doorWithPrize, std::vector<int>& guess, std::vector<int>& revealedDoor)
{
	int n = (int)doorWithPrize.size();
	std::random_device rd;
	std::mt19937 gen(rd());	
	std::uniform_int_distribution<> distr(1, 3);
	int index = 0;
	while (index < n)
	{
		int temp = distr(gen);
		if (temp != doorWithPrize[index] && temp != guess[index])
		{
			revealedDoor[index] = temp;
			index++;
		}
	}
}

//The strategy that always switches a guess after the goat door is revealed
//The new door after switching, should be different from both guesses and revealedDoor(goat door)
void switchGuess(std::vector<int>& guess, std::vector<int>& revealedDoor)
{
	int n = (int)guess.size();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 3);
	int index = 0;
	while (index < n)
	{
		int temp = distr(gen);
		if (temp != revealedDoor[index] && temp != guess[index])
		{
			guess[index] = temp;
			index++;
		}
	}
}

double montyHallSim(int n, bool switchDoor)
{
	std::random_device rd;		//obtain a random number from hardware
	std::mt19937 gen(rd());		//seed the generator
	std::uniform_int_distribution<> distr(1, 3);	//define the range

	std::vector<int> doorWithPrize(n);
	std::vector<int> guess(n);
	std::vector<int> revealedDoor(n);

  //Simulate door with prize:
  //Generate a random array of 1s, 2s, and 3s, representing
  //hiding a prize between door 1, door 2, and door 3
  
  //and Simulate random guess on which door a prize is behind. 
	for (int i = 0; i < n; ++i)
	{
		doorWithPrize[i] = distr(gen);
		guess[i] = distr(gen);
	}

	if (switchDoor)
	{
		revealedGoatDoor(doorWithPrize, guess, revealedDoor);
		switchGuess(guess, revealedDoor);
	}

	int win = 0;
	for (int i = 0; i < n; ++i)
	{
		if (guess[i] == doorWithPrize[i])
			win += 1;
	}

	double winPercentage = ((double)win /(double) n) * 100;
	return winPercentage;
}

int main()
{
	std::cout << montyHallSim(10000, true) << " %";
  return 0;
}
