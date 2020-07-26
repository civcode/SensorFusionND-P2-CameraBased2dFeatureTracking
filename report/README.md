# Sensor Fusion Nanodegree

## Project 2 - Camera Based 2d Feature Tracking
This project compares several feature detectors and feature descriptors from the OpenCV library in terms of coputing- and matching performance. 

|Type	|Method	|
|---	|---	|
|Detector	|'AKAZE', 'BRISK', 'HARRIS', 'ORB', 'SHITOMASI', 'SIFT', 'SURF'	|
|Descriptor	|'AKAZE', 'BRIEF', 'BRISK', 'FREAK', 'ORB', 'SIFT', 'SURF'		|

Performance parameters such as number of keypoints, processing time and number of features matches were written to a json file for each pairing of detectors and descriptors. Performance evaluation was done in the Jupyter Notebook _performance_evaluation.ipynb_.

---

[//]: # (Image References)

[img01]: ./img/img01.png " "
[img02]: ./img/img02.png " "
[img03]: ./img/img03.png " "
[img04]: ./img/img04.png " "
[img05]: ./img/img05.png " "
[img06]: ./img/img06.png " "
[img07]: ./img/img07.png " "
[img08]: ./img/img08.png " "


### MP.1 Data Buffer

_Implement a vector for dataBuffer objects whose size does not exceed a limit (e.g. 2 elements). This can be achieved by pushing in new elements on one end and removing elements on the other end._

If the data buffer exceeds the size defind in _dataBufferSize_, the first element is erased.

/src/MidTermProject_Camera_Student.cpp <br/>line 69ff:

```c++
if (dataBuffer.size() > dataBufferSize)
	dataBuffer.erase(dataBuffer.begin());
dataBuffer.push_back(frame);
```

### MP.2 Keypoint Detection

_Implement detectors HARRIS, FAST, BRISK, ORB, AKAZE, and SIFT and make them selectable by setting a string accordingly._

The file _/src/properties.h_ stores parameters such as the desired feature detection- and description method. Feature detectors 'HARRIS' and 'SHITOMASI' have their own functions in _/src/matching2D_Student.cpp_, the other methods can be called with a wrapper class which is done in the function _detKeypointsModern(...)_.

Selecting the appropriate function is done in _/src/MidTermProject_Camera_Student.cpp_ in lines 91 to 107.

### MP.3 Keypoint Removal

_Remove all keypoints outside of a pre-defined rectangle and only use the keypoints within the rectangle for further processing._


Picking the features within the ROI defined by _vehicleRect_ is done with the member function cv::Rect::contains(...).


_/src/MidTermProject_Camera_Student.cpp_ <br/> line 114ff

```c++
// only keep keypoints on the preceding vehicle
bool bFocusOnVehicle = properties::use_focus_keypoints_on_vehicle;
cv::Rect vehicleRect(535, 180, 180, 150);
if (bFocusOnVehicle)
{
	vector<cv::KeyPoint> keypoints_tmp; 
	for (auto point : keypoints) {
		if (vehicleRect.contains(point.pt)) {
			point.size = static_cast<float>(round(point.size*10)/10);
			keypoints_tmp.push_back(point);
				
			properties::frame_data[imgIndex].feature_size.push_back((point.size));
		}
	}

	keypoints.swap(keypoints_tmp);
	properties::frame_data[imgIndex].features_in_roi =  keypoints.size();
	cout << "Number of keypoint in ROI =" << keypoints.size() << endl;
}
```

### MP.4 Keypoint Descriptors

_Implement descriptors BRIEF, ORB, FREAK, AKAZE and SIFT and make them selectable by setting a string accordingly._

The file _/src/properties.h_ stores parameters such as the desired feature description method. All descriptors can be conveniently instantiated with the the wrapper class _cv:DescriptorExtractor_, which is done in function _descKeypoints(..)_ in _/src/matching2D_Student.cpp_ line 66ff. 


### MP.5 Descriptor Matching

_Implement FLANN matching as well as k-nearest neighbor selection. Both methods must be selectable using the respective strings in the main function._

The FLANN and k-nearest neighbor feature matching methods are implemented in the function _matchDescriptors(...)_ in _/src/matching2D_Student.cpp_ line 8ff.

For the brute force matching, the applied norm was set to the following values:

|Norm	|Feature Descriptor|
|---	|---	|
|cv::NORM_L2		|'SIFT', 'SURF'								|
|cv::NORM_HAMMING	|'AKAZE', 'BRIEF', 'BRISK', 'FREAK', 'ORB'	| 

When the FLANN method is used, the descriptor matrices have to be converted to CV_32F data type.

```c++
if (descSource.type() != CV_32F || descRef.type() != CV_32F)
{ // OpenCV bug workaround: convert binary descriptors to floating point due to a bug in current OpenCV implementation
	descSource.convertTo(descSource, CV_32F);
	descRef.convertTo(descRef, CV_32F);
}
```

### MP.6 Descriptor Distance Ratio

_Use the K-Nearest-Neighbor matching to implement the descriptor distance ratio test, which looks at the ratio of best vs. second-best match to decide whether to keep an associated pair of keypoints._

The distance ratio test is implemented in _/src/matching2D_Student.cpp_ line 46ff. 


```c++
...
else if (selectorType.compare("SEL_KNN") == 0)
{ // k nearest neighbors (k=2)

	vector<vector<cv::DMatch>> knn_matches;
	matcher->knnMatch(descSource, descRef, knn_matches, 2);

	double dist_ratio_min = 0.8;
	for (auto it=knn_matches.begin(); it!=knn_matches.end(); ++it) {
		if ((*it)[0].distance < dist_ratio_min * (*it)[1].distance) {
			matches.push_back((*it)[0]);
		}
	}
}
```

### MP.7 Performance Evaluation 1

_Count the number of keypoints on the preceding vehicle for all 10 images and take note of the distribution of their neighborhood size. Do this for all the detectors you have implemented._

The following graph shows the number of features within the image ROI for all detectors. The Harris detector is less consistent then the others.


![][img01]


The next graph shows the distribution of the feature neighborhood (aka feature size) for each detector. Harris and Shitomasi use only as single feature size. SIFT and SURF have very fine-grained variations in feature size. SURF feature sizes stretch over a very long range.  

![][img02]

### MP.8 Performance Evaluation 2

_Count the number of matched keypoints for all 10 images using all possible combinations of detectors and descriptors. In the matching step, the BF approach is used with the descriptor distance ratio set to 0.8._


The following tables shows the averager number of feature matches within the ROI over all images, and the ten highest ranking combinations of detector and descriptor.

![][img03]

![][img04]


### MP.9 Performance Evaluation 3

_Log the time it takes for keypoint detection and descriptor extraction. The results must be entered into a spreadsheet and based on this data, the TOP3 detector / descriptor combinations must be recommended as the best choice for our purpose of detecting keypoints on vehicles._

#### Processing Time

The following tables show the processing time for feature detection and feature descriptions, as well as the ten highest ranking combinations of detector and descriptor.

![][img05]

![][img06]

#### Feature Matches per Processing Time

For the following table the average number of feature matches per image was divided by the average processing time for feature detection and description per image. The ten highest ranking combinations of detector and descriptor are shown as well.

![][img07]

![][img08]

### Results

According to the measured processing time, the top three combinations are:

|Rank|Detector|Descriptor|Processing time in ms|
|---		|---|---|---|
|1|ORB		|BRIEF|21|
|2|ORB		|BRISK|24|
|3|HARRIS	|BRISK|30| 

If we look at the best performance in terms of feature matches per time unit we get the following top three. The Harris detector loses its position because of the computationally expensive gradient calculation. 

|Rank|Detector|Descriptor|Milliseconds per feature match|
|---		|---|---|---|
|1|ORB		|BRISK	|0.096155|
|2|ORB		|BRIEF	|0.117097|
|3|ORB		|ORB	|0.130858| 

Considering the number of feature matches within the ROI per image, which should be as high as possible, the combination of ORB detector and BRISK descriptor performs best with 253 matches, followed by the combination of ORB detector and ORB descriptor with 248 matches. The combination of ORB and BRIEF achieves only 180 matches.    









