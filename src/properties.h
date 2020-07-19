#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <string>
#include <vector>



namespace properties {

using namespace std;

const int output_window_pos_x = 20;
const int output_window_pos_y = 20;
const int output_window_width = 1000;
const int output_window_height = 700;


const bool use_focus_keypoints_on_vehicle = true;

const bool use_matches_max_count = false;
const int matches_max_count = 1000;

// set feature type
//const string keypoint_detector_type = "SHITOMASI";
//const string keypoint_detector_type = "HARRIS";
const string keypoint_detector_type = "BRISK";
//const string keypoint_detector_type = "ORB";
//const string keypoint_detector_type = "SIFT";
//const string keypoint_detector_type = "SURF"; // not part of assignment
//const string keypoint_detector_type = "AKAZE";

// set descriptor type
const string feature_descriptor_type =  "BRISK";
//const string feature_descriptor_type =  "BRIEF";
//const string feature_descriptor_type =  "ORB";
//const string feature_descriptor_type =  "FREAK";
//const string feature_descriptor_type =  "AKAZE";
//const string feature_descriptor_type =  "SIFT";
//const string feature_descriptor_type =  "SURF"; // not part of assignment

// set matcher type
//const string feature_matcher_type = "MAT_BF";
const string feature_matcher_type = "MAT_FLANN";

// set descriptor representation type
const string descriptor_representation_type = "DES_BINARY";
//const string descriptor_representation_type = "DES_HOG";

// set match selector type
//const string match_selector_type = "SEL_NN";
const string match_selector_type = "SEL_KNN";


struct frame_data_ {
    int features_in_roi;
    vector<float> feature_size;
};

extern struct frame_data_ frame_data[];



void printEvalData();


// enum class DetectorType {
//     SHITOMASI,
//     HARRIS,
//     FAST, 
//     BRISK, 
//     ORB, 
//     FREAK,
//     AKAZE, 
//     SIFT
// };
// DetectorType d_type = DetectorType::SHITOMASI;

// string detector_name;

// switch (d_type) {
//     case DetectorType::SHITOMASI:
//         detector_name = "SHITOMASI"; break;
// }


} // namespace properties

#endif// PROPERTIES_H_
