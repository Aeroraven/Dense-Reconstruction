#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace cv;

#pragma once

#include <cstdint>
#include <limits>

constexpr auto Invalid_Float = std::numeric_limits<float>::infinity();

typedef int8_t			sint8;		
typedef uint8_t			uint8;		
typedef int16_t			sint16;		
typedef uint16_t		uint16;		
typedef int32_t			sint32;		
typedef uint32_t		uint32;		
typedef int64_t			sint64;		
typedef uint64_t		uint64;		
typedef float			float32;	
typedef double			float64;	

/**
 * \brief Depth Filter类
*/
class DepthFilter
{
public:
	DepthFilter();
	~DepthFilter();

	/* 深度滤波器类型 */
	enum FilterType {
		Gaussion = 0,
		Even_Gaussion = 1,
	};

	/* 深度滤波器参数 */
	// 暂时只有滤波器类型，后续如果有必要升级为struct
	FilterType filter_type_; // 该深度滤波器的类型
	Mat depth_; // 深度图
	Mat depth_cov_; // 深度图方差

public:
	/**
	 * \brief 类的初始化，完成一些内存的预分配、参数的预设置等
	 * \param filter_type	输入，DepthFilter参数
	 */
	bool Initialize(const uint32& width, const uint32& height, double& mu_first, double& sigma_first, const FilterType& filter_type);
	/**
	 * \brief 更新深度分布
	 * \param mu	输入，根据SGM,得到的某一位置像素的深度mu
	 * \param sigma	输入，根据SGM,得到的某一位置像素的深度sigma
	 * \param mu_fuse	输出，根据深度滤波器，更新后的深度mu_fuse
	 * \param sigma_fuse	输出，根据深度滤波器，更新后的深度sigma_fuse
	 */
	bool UpdateDepth(const double* depthMap, const Mat left, const Mat right);

	/**
	* 返回Mat depth_，使用SGM已知深度矩阵赋初值
	*/
	Mat SetDepth(double* d_i);

	/**
	* 返回Mat depth_，作为最终的深度矩阵
	*/
	double* GetDepth();

private:
	/** \brief 是否初始化标志	*/
	bool is_initialized_;
	/* 图像的宽 */
	sint32 img_width_;
	/* 图像的长 */
	sint32 img_height_;
	/* 深度初始值 */
	double init_depth = 3.0;
	/* 方差初始值 */
	double init_cov2 = 3.0;
	/* 保存最近一次更新的mu */
	// double mu_latest_;
	/* 保存最近一次更新的sigma */
	// double sigma_latest_;

	/* 计算数组的模 */
	template<typename T>
	double arr_norm(T* arr, int arr_len);
	/* 计算数组的点积 */
	template<typename T>
	double arr_dot(T* arr1, T* arr2, int arr_len);
	/* 像素平面映射到相机平面 */
	void px2cam(const sint32* px, sint32* res); // 可能不能保证res数组中的所有数还是sint32类型

	/* 内存释放 */
	void Release();
	double arr_norm(double* arr, int arr_len);
	double arr_dot(double* arr1, double* arr2, int arr_len);
};
