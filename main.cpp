#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "segment.hpp"
#include<math.h>
#include <windows.h> 
using namespace cv;
using namespace std;
const int T = 500;//The max of capacity the component container.
struct colour
{
	int comp;
	//int num = 0;
};

int diff(const Mat &img, int x1, int y1, int x2, int y2)
{
	auto a = img.at<Vec3b>(y1, x1);
	auto b = img.at<Vec3b>(y2, x2);
	return int(sqrt(pow((a[0] - b[0]), 2) + pow((a[1] - b[1]), 2) + pow((a[2] - b[2]), 2)));
}

int find(int comp, colour maker[])
{
	for (int i = 1; i < T; i++)
	{

		if (comp == maker[i].comp)
		{
			return i;
		}
		else
		{
			if (i == T - 1)
			{
				return 0;
			}
		}
	}
}


int seg_img(Mat &imgInd, const Mat &img, float sigma = 0.5, int c = 200, int min_size = 50)
{
	int width = img.cols;
	int height = img.rows;

	Mat img_Gauss;
	GaussianBlur(img, img_Gauss, Size(3, 3), sigma, sigma, 1);
	Edge* edges;
	edges = new Edge[width*height * 4];
	int num = 0;
	cout << 123;
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			if (x < (width - 1))
			{
				edges[num].a = y * width + x;
				edges[num].b = y * width + x + 1;
				edges[num].w = diff(img, x, y, x + 1, y);
				//cout << edges[num].w << endl;
				num += 1;
			}
			if (y < (height - 1))
			{
				edges[num].a = y * width + x;
				edges[num].b = (y + 1) * width + x;
				edges[num].w = diff(img, x, y, x, y + 1);
				//cout << edges[num].w << endl;
				num += 1;
			}
			if (x < (width - 1) && y < (height - 1))
			{
				edges[num].a = y * width + x;
				edges[num].b = (y + 1) * width + x + 1;
				edges[num].w = diff(img, x, y, x + 1, y + 1);
				//cout << edges[num].w << endl;
				num += 1;
			}
			if (x < (width - 1) && y > 0)
			{
				edges[num].a = y * width + x;
				edges[num].b = (y - 1) * width + x + 1;
				edges[num].w = diff(img, x, y, x + 1, y - 1);
				//cout << edges[num].w << endl;
				num += 1;
			}

		}
	std::cout << "hehe11" << endl;
	auto u = segment_graph(width*height, num, edges, c);
	//post process small components
	std::cout << "hehe12" << endl;
	for (int i = 0; i < num; i++)
	{
		int a = u.find(edges[i].a);
		int b = u.find(edges[i].b);
		if (a != b && (u.size(a) < min_size || u.size(b) < min_size))
		{
			u.join(a, b);
		}
	}
	std::cout << "hehe13" << endl;
	//pick random colors for each components

	colour maker[T];
	//for (int i = 0; i < 40000; i++)
	//{
	//	maker[i].comp = 40001;
	//}

	imgInd = Mat::zeros(img.rows, img.cols, CV_8U);

	int idx_num = 0;
	int s = 1;
	std::cout << "hehe131" << endl;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int comp = u.find(y*width + x);
			//cout << "y="<< y << ",x=" << x << endl;
			//cout << comp << endl;
			if (!find(comp, maker))
			{
				//cout << find(comp, maker) << endl;
				maker[s].comp = comp;
				s += 1;
				//cout << maker[s-1].comp << endl;
				//cout << "s=" << s<<endl;
			}
			imgInd.at<uchar>(y, x) = find(comp, maker);
		}
	}
	std::cout << "hehe14" << endl;
	return s;
	//return 0;
}






int main()

{
	//test for the run time.Part I
	LARGE_INTEGER BegainTime;
	LARGE_INTEGER EndTime;
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&BegainTime);
	//test for the run time.Part I


	//读取本地的一张图片便显示出来
	Mat img = imread("G:\\img\\test2.jpg");

	//Mat img2,img3;
	//GaussianBlur(img, img2, Size(0, 0), 1,1,1);
	//GaussianBlur(img, img3, Size(0, 0), 1,1,0);
	Mat imgInd;
	cout << "hehe1" << endl;
	int num = seg_img(imgInd, img, 0.5, 500, 100);
	cout << num << endl;
	//seg_img(imgInd, img, 0.5, 300, 50);
	cout << "hehe2" << endl;
	Vec3b* colors;
	//int num = 30;
	colors = new Vec3b[num];
	for (int i = 1; i < num; i++)
	{

		colors[i] = Vec3b(int(rand() * 255), int(rand() * 255), int(rand() * 255));
		//cout << colors[i];
	}
	cout << "hehe3" << endl;

	Mat showimg = Mat::zeros(img.rows, img.cols, CV_8UC3);
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			showimg.at<Vec3b>(y, x) = colors[imgInd.at<uchar>(y, x) % (num - 1)];
		}
	}





	imshow("original_img", img);
	imshow("output_img", showimg);



	//test for the run time.Part II
	QueryPerformanceCounter(&EndTime);
	cout << "run time(s): " << (double)(EndTime.QuadPart - BegainTime.QuadPart) / Frequency.QuadPart << endl;
	//test for the run time.Part II

	waitKey(-1);
	return 0;
}


