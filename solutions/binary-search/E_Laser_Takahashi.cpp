#include <bits/stdc++.h>
using namespace std;
#define double long double

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    
    vector<tuple<int, int, int>> coords;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        coords.push_back(make_tuple(x, y, i + 1));
    }
    
    vector<pair<double, int>> sorted_coords;
    
    for (auto [x, y, i] : coords) {
        double angle = atan2l(y, x) * 180.0 / M_PI;
        if (angle < 0) {
            angle += 360.0;
        }
        sorted_coords.push_back({angle, i});
    }
    
    sort(sorted_coords.begin(), sorted_coords.end(), 
         [](const pair<double, int>& a, const pair<double, int>& b) {
             return a.first > b.first;
         });
    
    vector<double> sorted_coords_seedha;
    for (int i = sorted_coords.size() - 1; i >= 0; i--) {
        sorted_coords_seedha.push_back(sorted_coords[i].first);
    }
    
    map<int, pair<int, double>> mp;
    for (int index = 0; index < sorted_coords.size(); index++) {
        auto [angle, i] = sorted_coords[index];
        mp[i] = {index + 1, angle};
    }
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        
        auto [start, angle_a] = mp[a];
        auto [end, angle_b] = mp[b];
        
        if (angle_a >= angle_b) {
            swap(angle_a, angle_b);
            int ans = upper_bound(sorted_coords_seedha.begin(), sorted_coords_seedha.end(), angle_b) -
                      lower_bound(sorted_coords_seedha.begin(), sorted_coords_seedha.end(), angle_a);
            cout << ans << "\n";
        } else {
            double temp_angle_a = 0;
            double temp_angle_b = angle_a;
            
            int ans = upper_bound(sorted_coords_seedha.begin(), sorted_coords_seedha.end(), temp_angle_b) -
                      lower_bound(sorted_coords_seedha.begin(), sorted_coords_seedha.end(), temp_angle_a);
            
            temp_angle_a = angle_b;
            temp_angle_b = 360;
            ans += upper_bound(sorted_coords_seedha.begin(), sorted_coords_seedha.end(), temp_angle_b) -
                   lower_bound(sorted_coords_seedha.begin(), sorted_coords_seedha.end(), temp_angle_a);
            
            cout << ans << "\n";
        }
    }
    
    return 0;
}