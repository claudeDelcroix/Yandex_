//premiere approche 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>


int sum(const std::vector<int>& v,const int start,const int end) {
    int sum = 0;
    std::cout<<"start "<<start<<"end "<<end<<std::endl;
    for (int i = start; i < end; i++) {
        std::cout << v[i] << " ";
        sum += v[i];
    }
    std::cout<<"sortie de sum \n";
    return sum;
}
int main() {
    int n ;
    std::cin >> n ;
    int min_diff = INT_MAX;
    //n >= 2 && n<=10^6
    std::vector<int> table(n);
    for (int i = 0; i < n; i++) {
        std::cin >> table[i];
    }
    int l_v = 0,r_m = 0;
    int l = 0,r = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int sum_v = sum(table,i,j);
            int sum_m = sum(table,j,n);
            int diff = abs(sum_v - sum_m);
            std::cout<<"Debug : diff "<<diff<<" sum_v : "<<sum_v<<" sum_m : "<<sum_m<<std::endl;
            if (diff == 1) {
                std::cout <<diff<< " "<<i+1<<" " <<j+1<<std::endl;
                return 0;
            }
            if (diff < min_diff) {
                min_diff = diff;
                l_v = i+1;
                r_m = j+1;
            }
        }
    }

    std::cout << min_diff << " "<<l_v<<" "<<r_m<<std::endl;
    return 0;
}

//approche de "deux pointers " 
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n) || n < 2) {
        return 0;
    }

    
    std::vector<long long> table(n); 
    for (int i = 0; i < n; i++) {
        std::cin >> table[i];
    }


    int vasya_idx = 0;
    int masha_idx = n - 1; 


    long long vasya_sum = table[vasya_idx];
    long long masha_sum = table[masha_idx];
    

    long long min_diff = std::abs(vasya_sum - masha_sum);
    int best_l = vasya_idx + 1;
    int best_r = masha_idx + 1;
    

    while (vasya_idx < masha_idx - 1) { 
        

        long long current_diff = std::abs(vasya_sum - masha_sum);
        if (current_diff < min_diff) {
            min_diff = current_diff;
            
            best_l = vasya_idx + 1;
            best_r = masha_idx + 1;
        }

        
        if (vasya_sum <= masha_sum) {
            vasya_idx++;
            vasya_sum += table[vasya_idx];
        } else {
            masha_idx--;
            masha_sum += table[masha_idx];
        }
    }
    
  
    long long final_diff = std::abs(vasya_sum - masha_sum);
    if (final_diff < min_diff) {
        min_diff = final_diff;
        best_l = vasya_idx + 1;
        best_r = masha_idx + 1;
    }
    std::cout << min_diff << " " << best_l << " " << best_r << std::endl;

    return 0;
}
