#pragma once
#pragma once
#include<stack>
#include <iostream>
#include<vector>
using namespace std;
//class Edge
//{
//public:
//	Edge(int w = 0, int a = 0, int b = 0)
//	{
//		this->a = a;
//		this->b = b;
//		this->w = w;
//	}
//	auto getW()
//	{
//		return w;
//	}
//	auto getA()
//	{
//		return a;
//	}
//	auto getB()
//	{
//		return b;
//	}
//	//private:
//		//float w;
//	int a, b;
//	int w;
//};

typedef struct
{
	int a;
	int b;
	float w;

	//bool operator <(const Edge &x)const
	//{
	//	return w < x.w; //升序排列
	//}

}Edge;

bool operator<(const Edge &a, const Edge &b) 
{
	return a.w < b.w;
}

//bool comparison(const Edge &a, const Edge &b)
//{
//	return a.w < b.w;
//}

//class Edge
//{
//public:
//	Edge(float w = 0.0, int a = 0, int b = 0)
//	{
//		this->a = a;
//		this->b = b;
//		this->w = w;
//	}
//	auto getW()
//	{
//		return w;
//	}
//	auto getA()
//	{
//		return a;
//	}
//	auto getB()
//	{
//		return b;
//	}
//	//private:
//	float w;
//	int a, b;
//};


class Union_element
{
public:
	Union_element(int rank = 0, int p = 0, int size = 0)
	{
		this->rank = rank;
		this->p = p;
		this->size = size;
	}
	int getRank()
	{
		return rank;
	}
	int getP()
	{
		return p;
	}
	int getSize()
	{
		return size;
	}
	//private:
	int rank, p, size;
};

class Universe
{
public:
	Universe(int elements)
	{
		num = elements;
		//Union_element* elt;
		elts = new Union_element[num];
		for (int i = 0; i < num; i++)
		{
			this->elts[i] = Union_element(0, i, 1);
		}
	}
	auto join(int x, int y)
	{
		if (this->elts[x].rank > this->elts[x].rank)
		{
			this->elts[y].p = x;
			this->elts[x].size += this->elts[y].size;
		}
		else
		{
			this->elts[x].p = y;
			this->elts[y].size += this->elts[x].size;
			if (this->elts[x].rank == this->elts[y].rank)
			{
				this->elts[y].rank += 1;
			}
		}
		this->num -= 1;
	}
	int getNum()
	{
		return num;
	}
	int size(int x)
	{
		return elts[x].size;
	}
	auto find(int x)
	{
		int y = x;
		while (y != this->elts[y].p)
		{
			y = this->elts[y].p;
		}
		this->elts[x].p = y;  //x的老大找到了，是y。而且x直接去隶属于他的老大y了。
		return y;
	}
	//private:
	int num;
	Union_element* elts;
};



float threshold(int size, float c)
{
	return float(c / size);
}





int partition1(Edge v[], int left, int right)
{
	int prev = left - 1;
	int cur = left;
	Edge key = v[right - 1];

	while (cur < right)
	{
		if (v[cur].w < key.w && ++prev != cur)
			std::swap(v[cur], v[prev]);
		cur++;
	}

	if (v[++prev].w != key.w)
		std::swap(v[prev], v[right - 1]);
	return prev;
}

void QiockSortNor(Edge v[], int left, int right)
{
	if (left >= right)
		return;
	stack<int> s;
	s.push(left);
	s.push(right);

	while (!s.empty())
	{
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();
		if (left < right)
		{
			int boundary = partition1(v, left, right);
			// 左区间
			s.push(left);
			s.push(boundary);
			// 右区间
			s.push(boundary + 1);
			s.push(right);
		}

	}
}








//can't use Counting sort ...
//Edge* CountSort(Edge* a, int num_edge)
//{
//	assert(a);
//
//	int minValue = 0;
//	int maxValue = 441;   //max=sqrt(255^2*3)=441.6
//	int range = maxValue - minValue + 1;
//
//	int* tmp = new int[range];
//	//memset(tmp, 0, sizeof(int)*range);
//
//	for (int i = 0; i < range; i++)
//	{
//		tmp[i] = 0;
//	}
//
//
//	int index = 0;
//
//	while (index < num_edge) // count the num of each in container.
//	{
//		//tmp[a[index].w - minValue]++;
//		tmp[a[index].w]++;
//		//cout << tmp[a[index].w] << endl;
//		++index;
//	}
//
//	//int m = 0;//统计非零个数
//	//for (int i = 0; i < range; i++)
//	//{
//	//	if (tmp[i] != 0)
//	//	{
//	//		m += 1;
//	//	}
//	//	
//	//}
//	//int* tmp11 = new int[m];
//	//int s = 0;
//	//for (int i = 0; i < range; i++)
//	//{
//	//	if (tmp[i] != 0)
//	//	{
//	//		tmp11[s] = tmp[i];
//	//		s += 1;
//	//	}
//
//	//}
//
//
//
//
//	Edge* tmp2 = new Edge[num_edge];
//	int* tmp3 = new int[range];
//	//tmp3[0] = 0;
//	for (int i = 0; i < range; i++)
//	{
//		tmp3[i] = 0;
//	}
//
//	for (int i = 1; i < range; i++)
//	{
//		int j = i;
//		while (j  > 0) 
//		{
//			tmp3[i] += tmp[j - 1];
//			j--;
//		}
//		//cout << tmp3[i] << endl;
//	}
//
//
//
//	for (int i = 0; i < num_edge; i++)
//	{
//		for (int j = 0; j < range; j++)
//		{
//			if (a[i].w == j)
//			{
//				tmp2[tmp3[j]] = a[i];
//				tmp3[j] += 1;
//				break;
//			}
//		}
//		cout << i << endl;
//	}
//
//	delete[] tmp,tmp3;
//	return tmp2;
//}


//Edge* CountSort2(Edge* a, int num_edge)
//{
//	assert(a);
//
//	int minValue = 0;
//	int maxValue = 441;   //max=sqrt(255^2*3)=441.6
//	int range = maxValue - minValue + 1;
//
//	vector<Edge>* tmp = new vector<Edge>[range];
//
//	int index = 0;
//
//	while (index < num_edge) // count the num of each in container.
//	{
//		tmp[a[index].w].insert(tmp[a[index].w].end(), a[index]);
//		++index;
//	}
//
//
//	Edge* tmp2 = new Edge[num_edge];
//	//tmp3[0] = 0;
//
//	int m = 0;
//	for (int j = 0; j < range; j++)
//	{
//		for (int i = 0; i < tmp[j].size(); i++)
//		{
//			tmp2[m] = (tmp[j])[i];
//			m += 1;
//		}
//	}
//
//
//	delete[] tmp;
//	return tmp2;
//}














//segment a graph and return a disjoint set forest 
auto segment_graph(int num_v, int num_edge, Edge edges[], int c)
{
	Edge* temp;
	temp = new Edge[num_edge];
	for (int i = 0; i < num_edge; i++)
	{
		temp[i] = edges[i];
	}
	Edge temp_change;
	cout << "hehe111" << endl;
	cout << "num_edge: " << num_edge << endl;
	//int m = 0;
	//for(i=0;i<num_edge-1;i++)   //升序冒泡    nondecreaseing bubble sort
	//	for(j=0;j<num_edge-1-i;j++)
	//		if (temp[j].w > temp[j + 1].w)
	//		{
	//			temp_change = temp[j];
	//			temp[j] = temp[j + 1];
	//			temp[j + 1] = temp_change;
	//			cout << ++m << endl;
	//		}
	//Qsort(temp, 0, num_edge-1);
	//Quick(temp, 0, num_edge - 1);

	std::sort(temp, temp + num_edge);

	//QiockSortNor(temp, 0, num_edge - 1);//quick sort    n*log(n)
	//temp = CountSort(temp, num_edge);//   k=442         n*k      My first try on counts sort 

	//temp = CountSort2(temp, num_edge);//                  n       My second try on counts sort
									 //               got some proposal from QQgroup:496800184
	cout << "hehe112" << endl;
	for (int i = 0; i < num_edge; i++)
	{
		edges[i] = temp[i];
	}
	cout << "hehe113" << endl;
	//make a dis-joint set universe 
	Universe u = Universe(num_v);//isolated point 
	float* Threshold;
	//cout << num_v;
	Threshold = new float[num_v];
	for (int i = 0; i < num_v; i++)
	{
		Threshold[i] = threshold(1, c);
	}
	cout << "hehe114" << endl;
	for (int i = 0; i < num_edge; i++)
	{
		Edge edge_temp = edges[i];//find a edge,a and b are the connected points.
		int a = u.find(edge_temp.a);
		int b = u.find(edge_temp.b);
		if (a != b)   //a and b have different boss.
		{
			//at the beginning,the internal difference is zero,so 0 plus the threshold. 
			if (edge_temp.w <= Threshold[a] && edge_temp.w <= Threshold[b])
			{
				u.join(a, b);    //unite a and b.
				a = u.find(a);   //a=a'boss    just the in this example.
								//but in others, another boss of a and b' union.
				Threshold[a] = edge_temp.w + threshold(u.size(a), c);
			}
		}
	}
	cout << "hehe115" << endl;
	return u;
}


