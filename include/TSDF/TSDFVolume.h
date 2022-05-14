#pragma once
#include "../Utility/Log.h"

#include <opencv2/opencv.hpp>

namespace TSDF{
    class TSDFVolume{
        private:
            cv::Mat _bound;
            double _voxSize;
            double _trunc;
            double _volOrigin[3];
            double _volDim[3];
            cv::Mat _worldPts;

            double*** _tsdf;
            double*** _weight;
            double*** _color;

            // _coordNum*3
            int** _coords;
            int _coordNum;

            bool checkInFrustum(int pix_x, int pix_y, double pix_z);
            bool checkValid();
            void integrateTSDF(double* tsdfVals, double* validDist, double* wOld, int length, double obsWeight, double* tsdfVolNew, double* wNew);

        public:
            TSDFVolume(cv::Mat bound, double voxSiz=0.02);
            void integrate(cv::Mat img, cv::Mat depth, cv::Mat intr, cv::Mat extr, double obsWeight=1.0);
    };
};