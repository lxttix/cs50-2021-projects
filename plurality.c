#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winners = 0;
    string most_votes[candidate_count];
    int lVote = 0;
    int num = 0;

    // max it can hold is all of them (amount inputted)
    for (int i = 0; i < (candidate_count + 1); i++)
    {
        //prevents it from using memory not allocated --works fine
        if ((i + 1) > candidate_count)
        {
            //prints out winner(s)
            for (int j = 0; j < winners; j++)
            {
                if (strcmp(most_votes[j], "A") > 0) //so that it doesn't print null
                {
                    printf("%s\n", most_votes[j]);
                }
            }
            return;
        }
        //if it is larger
        if (candidates[i].votes > lVote)
        {
            lVote = candidates[i].votes;
            winners++;
            most_votes[num] = candidates[i].name;
        }
        //if it is the same
        else if (candidates[i].votes == lVote)
        {
            num++;
            winners++;
            most_votes[num] = candidates[i].name;
        }
        //if it is smaller then it skips
    }
}
