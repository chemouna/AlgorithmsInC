//
// Created by Mouna Cheikhna on 18/03/2017.
//

#include <vector>
#include <iostream>
#include <queue>
#include <iterator>

using namespace std;

struct Node {
    Node(int weapons, int shots)
            : weapons_(weapons), shots_(shots) {}

    int weapons_;
    int shots_;
};

// reverse condition to put on top of the priority queue the minimum
bool operator<(const Node &n1, const Node &n2) {
    if (n1.shots_ < n2.shots_) return false;
    return true;
}


int leastShots(const vector<string> &damageChart, const vector<int> &bossHealth) {

    const int n = (const int) damageChart.size();
    const int numWeapons = (const int) damageChart[0].size();
    vector<bool> visited(32768, false);
    priority_queue<Node> pq;
    pq.push(Node(0, 0));

    while (!pq.empty()) {
        Node top = pq.top();

        if (visited[top.weapons_]) continue;
        visited[top.weapons_] = true;

        //check if target reached : all bosses defeated which is equivalent to having all the weapons
        if (top.weapons_ == (1 << numWeapons) - 1) {
            return top.shots_;
        }

        //relax step
        for (int i = 0; i < damageChart.size(); i++) {
            if ((i << numWeapons) & 1) continue;

            // Figure out what the best amount of time that we can destroy this boss is, given the weapons we have.
            // We initialize this value to the boss's health, as that is our default (with KiloBuster).
            // this equivalent to the step where we compare distances in classic Dijkstra and pick the min one

            int best = bossHealth[i];

            for (int j = 0; j < damageChart.size(); j++) {

                if (i == j) continue; // ?

                //if i've got this weapon (its bit is set on my weapons field) and it has power (its not '0')
                //then i can use it
                if (((j << top.weapons_) & 1) && damageChart[j][i] != '0') {
                    //we have the weapon so lets defeat the boss with it
                    int shotsNeeded = bossHealth[i] / (damageChart[j][i] - '0'); //?
                    if (bossHealth[i] % damageChart[j][i] != '0') { // ?
                        shotsNeeded++;
                    }
                    best = min(best, shotsNeeded);
                }
            }
            // Decrease operation : Add the new node to be searched, showing that we defeated boss i and so we have
            //  his weapons now (==> we union weapons bits field with 1 << i) and we used 'best' shots to defeat him.
            pq.push(Node(top.weapons_ | 1 << i, top.shots_ + best));
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
    vector<string> damageChart(3);
    damageChart[0] = "070";
    damageChart[1] = "500";
    damageChart[2] = "140";

    vector<int> bossHealth(3);
    bossHealth[0] = 150;
    bossHealth[1] = 150;
    bossHealth[2] = 150;

    leastShots(damageChart, bossHealth); // it should be: 218;
}
