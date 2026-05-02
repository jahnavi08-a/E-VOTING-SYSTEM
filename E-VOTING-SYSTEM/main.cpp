#include <iostream>
#include <fstream>
using namespace std;
class Voter {
public:
    int id;
    string name;
    int hasVoted;
};
class Candidate {
public:
    int id;
    string name;
    int votes;
};
Voter voters[100];
Candidate candidates[10];
int voterCount = 0;
int candidateCount = 0;
void loadVoters() {
    ifstream file("voters.txt");
    while (file >> voters[voterCount].id >> voters[voterCount].name >> voters[voterCount].hasVoted) {
        voterCount++;
    }
    file.close();
}
void loadCandidates() {
    ifstream file("candidates.txt");
    while (file >> candidates[candidateCount].id >> candidates[candidateCount].name >> candidates[candidateCount].votes) {
        candidateCount++;
    }
    file.close();
}
void saveVoters() {
    ofstream file("voters.txt");
    for (int i = 0; i < voterCount; i++) {
        file << voters[i].id << " " << voters[i].name << " " << voters[i].hasVoted << endl;
    }
    file.close();
}
void saveCandidates() {
    ofstream file("candidates.txt");
    for (int i = 0; i < candidateCount; i++) {
        file << candidates[i].id << " " << candidates[i].name << " " << candidates[i].votes << endl;
    }
    file.close();
}
int findVoter(int id) {
    for (int i = 0; i < voterCount; i++) {
        if (voters[i].id == id) {
            return i;
        }
    }
    return -1;
}
void castVote() {
    int id;
    cout << "Enter Voter ID(100-200): ";
    cin >> id;
    int index = findVoter(id);
    if (index == -1) {
        cout << "Invalid voter!\n";
        return;
    }
    if (voters[index].hasVoted == 1) {
        cout << "You already voted!\n";
        return;
    }
    cout << "\nCandidates:\n";
    for (int i = 0; i < candidateCount; i++) {
        cout << candidates[i].id << ". " << candidates[i].name << endl;
    }
    int choice;
    cout << "Enter candidate ID: ";
    cin >> choice;
    for (int i = 0; i < candidateCount; i++) {
        if (candidates[i].id == choice) {
            candidates[i].votes++;
            voters[index].hasVoted = 1;
            cout << "Vote cast successfully!\n";
            return;
        }
    }
    cout << "Invalid candidate!\n";
}
void showResults() {
    cout << "\n--- Voting Results ---\n";
    for (int i = 0; i < candidateCount; i++) {
        cout << candidates[i].name << " : " << candidates[i].votes << " votes\n";
    }
}
int main() {
    loadVoters();
    loadCandidates();
    int choice;
    do {
        cout << "\n--- E-Voting System ---\n";
        cout << "1. Vote\n";
        cout << "2. View Results\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            castVote();
        }
        else if (choice == 2) {
            showResults();
        }
    } while (choice != 3);
    saveVoters();
    saveCandidates();
    return 0;
}
