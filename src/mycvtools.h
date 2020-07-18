#ifndef MY_CV_TOOLS_H_
#define MY_CV_TOOLS_H_

#include <opencv2/core.hpp>

namespace mycv {

void _prepareImgAndDrawKeypoints( InputArray img1, const std::vector<KeyPoint>& keypoints1,
                                         InputArray img2, const std::vector<KeyPoint>& keypoints2,
                                         InputOutputArray _outImg, Mat& outImg1, Mat& outImg2,
                                         const Scalar& singlePointColor, DrawMatchesFlags flags );

void drawMatches( InputArray img1, const std::vector<KeyPoint>& keypoints1,
                  InputArray img2, const std::vector<KeyPoint>& keypoints2,
                  const std::vector<DMatch>& matches1to2, InputOutputArray outImg,
                  const Scalar& matchColor, const Scalar& singlePointColor,
                  const std::vector<char>& matchesMask, DrawMatchesFlags flags );

}
#endif //MY_CV_TOOLS_H_