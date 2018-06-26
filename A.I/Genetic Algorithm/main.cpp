//Justen McLean
//Genetic Algorithm
//Artificial Intelligence
//2017
//Main

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>


using namespace std;

struct sample
{
	string code;
	int value;
	int eval;
};

// Function Declarations
void showSamples(vector<sample> samplesIn);
int toInt(string sampleIn);
int evaluate(int valueIn);
void crossover(vector<sample>& samplesIn);
void mutate(vector<sample>& samplesIn);

// Variables
int candidates = 6;
int candidateSize = 5;
float keep = 0.5;
float mutateRate = 0.2;

int main()
{
	srand(time(NULL));
	cout << "Genetic Algorithm" << endl;
	vector<sample> samples;
	// vector<string> samples;

	// Generate sample population
	for (int i = 0; i < candidates; i++)
	{
		sample tempSample;
		tempSample.code = "";
		tempSample.value = 0;
		tempSample.eval = -1;
		//string tempSample = "";
        
        // Generate strings of 1's and 0's
		for (int j = 0; j < candidateSize; j++)
		{
			int chance = rand() % 100;
			if (chance >= 50)
				tempSample.code += "1";
			else
				tempSample.code += "0";
		}

		samples.push_back(tempSample);
		//cout<<"Sample " << i << " : " << testSample << endl;
	}

	int generations = 10;
	while (generations-- > 0)
	{
        cout << "Generation " << 10 - generations << endl;
        
        // Get the decimal values of the samples
		for (unsigned int i = 0; i < samples.size(); i++)
		{
			samples[i].value = toInt(samples[i].code);
			//toInt(samples[i]);
		}
        
        // Gets the squared value of the sample
		for (unsigned int i = 0; i < samples.size(); i++)
		{
			samples[i].eval = evaluate(samples[i].value);
		}

		showSamples(samples);       // Print the sample values to the console

        // Sort the samples
		for (int i = 0; i < samples.size() - 1; i++)
		{
			for (int j = i; j < samples.size(); j++)
			{
				if (samples[i].eval < samples[j].eval)
				{
					// switch the samples
					sample temp = samples[i];
					samples[i] = samples[j];
					samples[j] = temp;
				}
			}
		}

		cout << "Sorted....." << endl;
		showSamples(samples);
		crossover(samples);
		cout << endl << "After Crossover" << endl;
		showSamples(samples);
		mutate(samples);
		cout << endl << "After Mutate" << endl;
	}
    
	return 0;
}

void crossover(vector<sample>& samplesIn)
{
	vector<sample> results;

	for ( int i = 0; i < (candidates * keep); i++)
	{
		
		//Two of the top keep samples
		sample one = samplesIn[(rand() % candidates) * keep];
		sample two = samplesIn[(rand() % candidates) * keep];

		sample result1;
		sample result2;

		// Choose a random cut location
		int cut = rand() % candidateSize;

		// Create empty samples from the result
		result1.code = "";
		result2.code = "";

        // Take part of one sample and combine with part of another
		for (int j = 0; j < candidateSize; j++)
		{
			if (j < cut)
			{
				result1.code += one.code[j];
				result2.code += two.code[j];
			}
			else
			{
				result2.code += one.code[j];
				result1.code += two.code[j];
			}
		}
        
        // Add the two new results to the results vector
		results.push_back(result1);
		results.push_back(result2);
	}

	// Replace the original results from samplesIn with the newely created results 
	for (int i = 0; i < results.size(); i++)
	{
		samplesIn[i] = results[i];
	}

	return;
}

// Applies random mutations to samples
void mutate(vector<sample>& samplesIn)
{
	for (int i = 0; i < samplesIn.size(); i++)          // For every sample
	{
		if (((rand() % 10) / (float)10) < mutateRate)   // If the random value is less than the mutateRate
		{
			int mutateIndex = rand() % candidateSize;   // Get a random mutate position

            // Flip the bit at the random position
			if (samplesIn[i].code[mutateIndex] == '0')
				samplesIn[i].code[mutateIndex] = '1';
			else
				samplesIn[i].code[mutateIndex] = '0';
		}
	}
}

// Prints the sample to the console
void showSamples(vector<sample> sampleIn)
{
	for (unsigned int i = 0; i < sampleIn.size(); i++)
	{
		cout << "Sample " << i << " : " << sampleIn[i].code << " =>\t " << sampleIn[i].value << " =>\t " << sampleIn[i].eval <<  endl;
	}
    
	return;
}

// Gets the decimal value of the sample
int toInt(string sampleIn)
{
	int value = 0;
	int power = 0;

	for (int i = sampleIn.size() - 1; i >= 0; i--)
	{
		value += (pow(2, power++)* (sampleIn[i] - '0'));
	}

	cout << sampleIn << " = " << value << endl;
    
	return value;
}

// Gets the squared value of the sample
int evaluate(int valueIn)
{
	return pow(valueIn, 2);
}