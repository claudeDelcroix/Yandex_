//excellent passe 47 test mais apres TL
#include <iostream>
#include <queue>
#include <vector>
int main() {
    int n,x;
    std::cin >> n >> x;
    std::queue<int> q;
    std::vector<int> v;
    int iter_v = 0;
    for (int i = 0; i < n; i++) {
        int prof ;//professionalisme
        std::cin >> prof;
        q.push(prof);
        v.push_back(prof);
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int query;
        std::cin >> query;
        switch (query) {
            case 1: {
                int prof;
                std::cin >> prof;
                q.push(prof);
                v.push_back(prof);
            }
                break;
            case 2: {
                q.pop();
                iter_v++;
            }
                break;
            case 3: {
                int s;
                std::cin >> s;
                if (s == 0) {
                    std::cout<<0<<std::endl;
                }else {
                    int count = 0;
                    auto it = v.begin() + iter_v;
                    int j = 0;
                    while (j < s) {
                        if (*it >= x) {
                            count++;
                        }
                        j++;
                        ++it;
                    }
                    std::cout<<count<<std::endl;
                }
            }
                break;
            default:
                break;
        }
    }
    return 0;
}

//optimisation correcte verdict : ok 
#include <iostream>
#include <vector>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, x;
    std::cin >> n >> x;

    
    std::vector<int> prefix_counts;

    prefix_counts.push_back(0); 

    int iter_v = 0; 
    int current_prof_count = 0;


    for (int i = 0; i < n; i++) {
        int prof;
        std::cin >> prof;
        if (prof >= x) {
            current_prof_count++;
        }
        prefix_counts.push_back(current_prof_count);
    }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int query;
        std::cin >> query;
        switch (query) {
            case 1: {
                int prof;
                std::cin >> prof;
                if (prof >= x) {
                    current_prof_count++;
                }
            
                prefix_counts.push_back(current_prof_count); 
            }
                break;
            case 2: { 
               
                iter_v++; 
            }
                break;
            case 3: { 
                int s;
                std::cin >> s;
                if (s == 0) {
                    std::cout << 0 << "\n";
                } else {
                   
                    int count = prefix_counts[iter_v + s] - prefix_counts[iter_v];
                    std::cout << count << "\n";
                }
            }
                break;
            default:
                break;
        }
    }
    return 0;
}
