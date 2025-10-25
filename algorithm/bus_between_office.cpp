/*
У компании открылся второй офис и для перемещения сотрудников между офисами было решено организовать автобусные рейсы, которые будут ездить по расписанию из первого офиса во второй и обратно. Расписание уже готово, но непонятно, каким минимальным количеством автобусов удастся обслужить все рейсы.

Расписание состоит из 
N
N рейсов из первого офиса во второй и 
M
M обратных рейсов. Для каждого рейса известно время отправления и время прибытия с точностью до минуты. Любой рейс полностью выполняется в течение одних календарных суток (с 00:00 до 23:59 включительно), никакой рейс не прибывает на следующий день после отправления. Каждый рейс занимает как минимум одну минуту, то есть ни один рейс не прибывает к офису назначения в ту же минуту, в которую он отправился. После прибытия автобус готов в ту же минуту отправиться в обратный рейс. Одновременно возле офиса может находиться, отправляться или прибывать любое количество автобусов. Автобусы не могут перемещаться вне расписания в течение дня. Вам не нужно учитывать подготовку к выполнению расписания следующего дня — необходимо только определить минимальное количество автобусов для обслуживания рейсов в течение одного дня.

Формат ввода
В первой строке находится число 
N
N (
1
≤
N
≤
100000
1 ≤N≤ 100000) — количество рейсов из первого офиса во второй. В следующих 
N
N строках находятся описания рейсов, по одному на строке: время отправления и время прибытия, разделенные дефисом («-»). И время прибытия, и время отправления записаны в формате HH:MM, где HH — час (число от 0 до 23, при необходимости, дополненное ведущим нулем до двух цифр), MM — минута (число от 0 до 59, при необходимости, дополненное ведущим нулем до двух цифр).

В 
N
+
2
N+ 2-й строке находится число 
M
M (
1
≤
M
≤
100000
1 ≤M≤ 100000) — количество рейсов из второго офиса в первый. В следующих 
M
M строках находятся описания этих рейсов в том же формате.

Формат вывода
Выведите единственное число — минимально возможное количество автобусов, достаточное для обслуживания всех рейсов.


*/

//the solution of the probleme
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int toMinutes(const string &s) {
    int h = stoi(s.substr(0, 2));
    int m = stoi(s.substr(3, 2));
    return h * 60 + m;
}

struct Trip {
    int depart, arrive;
    bool fromA; // true = A→B, false = B→A
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N;

    vector<Trip> fromA(N), fromB;
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        fromA[i].depart = toMinutes(s.substr(0, 5));
        fromA[i].arrive = toMinutes(s.substr(6, 5));
        fromA[i].fromA = true;
    }

    cin >> M;
    fromB.resize(M);
    for (int i = 0; i < M; ++i) {
        string s;
        cin >> s;
        fromB[i].depart = toMinutes(s.substr(0, 5));
        fromB[i].arrive = toMinutes(s.substr(6, 5));
        fromB[i].fromA = false;
    }

    sort(fromA.begin(), fromA.end(), [](auto &a, auto &b){ return a.depart < b.depart; });
    sort(fromB.begin(), fromB.end(), [](auto &a, auto &b){ return a.depart < b.depart; });

    // Listes triées des heures d'arrivée vers chaque bureau
    vector<int> arrivalsAtA, arrivalsAtB;
    for (auto &t : fromA) arrivalsAtB.push_back(t.arrive);
    for (auto &t : fromB) arrivalsAtA.push_back(t.arrive);

    sort(arrivalsAtA.begin(), arrivalsAtA.end());
    sort(arrivalsAtB.begin(), arrivalsAtB.end());

    int iA = 0, iB = 0; // pointeurs sur les arrivées
    int availableA = 0, availableB = 0;
    int neededA = 0, neededB = 0;

    // fusion des deux listes de départs triées
    vector<Trip> all = fromA;
    all.insert(all.end(), fromB.begin(), fromB.end());
    sort(all.begin(), all.end(), [](auto &a, auto &b){ return a.depart < b.depart; });

    for (auto &t : all) {
        // Libérer les bus arrivés avant ce départ
        while (iA < (int)arrivalsAtA.size() && arrivalsAtA[iA] <= t.depart) {
            availableA++;
            iA++;
        }
        while (iB < (int)arrivalsAtB.size() && arrivalsAtB[iB] <= t.depart) {
            availableB++;
            iB++;
        }

        if (t.fromA) {
            if (availableA > 0) availableA--;
            else neededA++;
        } else {
            if (availableB > 0) availableB--;
            else neededB++;
        }
    }

    cout << neededA + neededB << "\n";
}


//the second approch 
//good but the complexity is not ok 
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int toMinutes(const string &s) {
    int h = stoi(s.substr(0, 2));
    int m = stoi(s.substr(3, 2));
    return h * 60 + m;
}

struct Trip {
    int depart, arrive;
    bool fromA; // true = A→B, false = B→A
};

int main() {
    int N, M;
    cin >> N;
    vector<Trip> trips;

    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        int depart = toMinutes(s.substr(0, 5));
        int arrive = toMinutes(s.substr(6, 5));
        trips.push_back({depart, arrive, true});
    }

    cin >> M;
    for (int i = 0; i < M; ++i) {
        string s;
        cin >> s;
        int depart = toMinutes(s.substr(0, 5));
        int arrive = toMinutes(s.substr(6, 5));
        trips.push_back({depart, arrive, false});
    }

    sort(trips.begin(), trips.end(),
         [](const Trip &a, const Trip &b) { return a.depart < b.depart; });

    int availableA = 0, availableB = 0;
    int neededA = 0, neededB = 0;

    vector<pair<int, bool>> arrivals; // (time, destination)
    for (auto &t : trips) {
        // Ajouter toutes les arrivées avant ce départ
        for (auto it = arrivals.begin(); it != arrivals.end();) {
            if (it->first <= t.depart) {
                if (it->second) availableA++;
                else availableB++;
                it = arrivals.erase(it);
            } else ++it;
        }

        if (t.fromA) {
            if (availableA > 0)
                availableA--;
            else
                neededA++;
            arrivals.push_back({t.arrive, false}); // Arrive à B
        } else {
            if (availableB > 0)
                availableB--;
            else
                neededB++;
            arrivals.push_back({t.arrive, true}); // Arrive à A
        }
    }

    cout << neededA + neededB << endl;
}


//that approch dont really solve the probleme because it's give the number of bus
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Fonction pour convertir l'heure HH:MM en minutes depuis minuit
int timeToMinutes(int hour, int minute) {
    return hour * 60 + minute;
}
// true = A→B, false = B→A
// Structure pour un événement (départ ou arrivée)
struct Event {
    int time;  // Temps de l'événement en minutes
    bool isDeparture;  // true si départ, false si arrivée
};

int main() {
    int N, M;
    cin >> N;

    vector<Event> events;

    // Lire les départs du bureau 1 vers le bureau 2
    for (int i = 0; i < N; ++i) {
        int hour, minute, end_hour, end_minute;
        cin >> hour >> minute >> end_hour >> end_minute;

        int departTime = timeToMinutes(hour, minute);
        int arriveTime = timeToMinutes(end_hour, end_minute);

        events.push_back({departTime, true});  // Ajout du départ
        events.push_back({arriveTime, false}); // Ajout de l'arrivée
    }

    cin >> M;

    // Lire les départs du bureau 2 vers le bureau 1
    for (int i = 0; i < M; ++i) {
        int hour, minute, end_hour, end_minute;
        cin >> hour >> minute >> end_hour >> end_minute;

        int departTime = timeToMinutes(hour, minute);
        int arriveTime = timeToMinutes(end_hour, end_minute);

        events.push_back({departTime, true});  // Ajout du départ
        events.push_back({arriveTime, false}); // Ajout de l'arrivée
    }

    // Trier les événements par temps, avec départs avant arrivées si même heure
    sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
        if (a.time == b.time) {
            return a.isDeparture > b.isDeparture; // Si même minute, départs avant arrivées
        }
        return a.time < b.time;
    });

    int buses = 0, maxBuses = 0;

    // Traiter les événements pour trouver le nombre maximal de bus nécessaires
    for (const auto &event : events) {
        if (event.isDeparture) {
            buses++;  // Un bus commence un trajet
            maxBuses = max(maxBuses, buses);  // On garde la trace du maximum
        } else {
            buses--;  // Un bus termine son trajet
        }
    }

    // Afficher le nombre de bus nécessaires
    cout << maxBuses << endl;

    return 0;
}
