
#include "properties.h"

#include <iostream>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <math.h>
#include <map>
#include <numeric>
#include "matplotlibcpp.h"

namespace properties {

using namespace std;
namespace plt = matplotlibcpp;

struct frame_data_ frame_data[10];

void printEvalData() {

    cout << "===============================================\n";
    cout << "Eval Data:\n";
    cout << "===============================================\n";
    cout << "Feature Detector  : " << keypoint_detector_type << endl;
    cout << "Feature Descriptor: " << feature_descriptor_type << endl;   
    cout << "No. of Feature in ROI: ";

    vector<float> ft_cnt;
    for (auto frame : frame_data) {
        //cout << frame.features_in_roi << ", ";
        ft_cnt.push_back(frame.features_in_roi);
    } 
    {
        float min = *min_element(ft_cnt.begin(), ft_cnt.end());
        float max = *max_element(ft_cnt.begin(), ft_cnt.end());
        float avg = accumulate(ft_cnt.begin(), ft_cnt.end(), 0) / ft_cnt.size();
        cout << " [min, max, avg] = [" << min << ", " << max << ", " << avg << "]\n";
    }

    cout << "Keypoint distribution: size (count avg):\n";
    map<float, int> size_distribution;
    map<float, vector<float>> ft_dist;
    for (auto frame : frame_data) {
        //unordered_set<float> size_set;
        set<float> size_set;
        for (auto size : frame.feature_size) {
            size_set.insert((size));
        }
        for (auto size : size_set) {
            int ft_count = count(frame.feature_size.begin(), frame.feature_size.end(), size);
            //cout << size << " (" << feature_count << "), ";
            // auto it = size_distribution.find(size);
            // if (it == size_distribution.end()) {
            //     size_distribution.insert(pair<float, int>(size, feature_count));
            //     cout << "key not found (" << size << "). adding count = " << feature_count << endl;
            // } else {  
            //     size_distribution[size] += feature_count;
            //     cout << "key found (" << size << "). adding count = " << feature_count << ". total: " << size_distribution[size] << endl;           
            // }
            size_distribution[size] += ft_count;
            auto it = ft_dist.find(size);
            if (it == ft_dist.end()) {
                ft_dist.insert(pair<float, vector<float>>(size, {static_cast<float>(ft_count)}));
            } else {
                it->second.push_back(static_cast<float>(ft_count));
            }
        }
        //cout << endl;
    } 
    //cout << endl;
    // int frame_count = sizeof(frame_data)/sizeof(frame_data[0]);
    // for (auto it=size_distribution.begin(); it!=size_distribution.end(); ++it) {
    //     cout << it->first << " (" << static_cast<float>(it->second)/frame_count << "), ";
    // }
    // cout << endl;

    for (auto it=ft_dist.begin(); it!=ft_dist.end(); ++it) {
        vector<float>& ft_cnt = it->second;
        float min = *min_element(ft_cnt.begin(), ft_cnt.end());
        float max = *max_element(ft_cnt.begin(), ft_cnt.end());
        float avg = accumulate(ft_cnt.begin(), ft_cnt.end(), 0) / ft_cnt.size();
        cout << it->first << " [" << min << ", " << max << ", " << avg << "]\n"; 
    }
    cout << endl;

    plt::plot({1,2,3,4});
    plt::show();


}

} // namespace properties