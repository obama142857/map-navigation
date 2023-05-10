#pragma region 头文件
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include"opengl1.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imconfig.h>
#include <imgui_internal.h>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <list>
#define PI 3.1415926535
#define maxv 100
#define maxd 1000
using namespace std;
#pragma endregion

void processInput(GLFWwindow* window, createwindow mywindow);
void mousefunction(double xpos, double ypos);

void mousescroll(double xoffset, double yoffset);

static void HelpMarker(const char* desc);


glm::vec3 cameraPos = glm::vec3(0.0f, 10.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
bool moveflag = true;
bool mousehide = false;
float contime = 0;
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

int modd;//绘制模式
bool addallow = true;
bool guifocus;
string suibian;
int hcount;
float starttime;
//其他变量------------------------
glm::mat4 model;
int menu = 0;
double scalef = 1.0f;
glm::vec3 transvec = glm::vec3(0, 14.0, 0);
bool test = false;
struct historyitem
{
	string name;
	string idata;
};
vector<historyitem> items;

glm::vec2 getScreenPos(double x, double y)
{
	double px, py;
	px = x * 2 * 6.016 - 6.016;
	py = y * 2 * 7.68 - 7.68;
	glm::vec4 a = glm::vec4(px, py, 0.0f, 1.0f);
	glm::vec4 b = model * a;

	return glm::vec2(b.x, b.y);
}
glm::vec2 getPicPos(double x, double y)
{
	glm::vec4 p(x, y, 0, 1.0f);
	glm::vec4 b = glm::inverse(model) * p;
	double px, py;
	px = (b.x + 6.016) / 2 / 6.016;
	py = (b.y + 7.68) / 2 / 7.68;
	return glm::vec2(px, py);
}
int N;
int startpoint;
vector<int> despoint;
int mod = 0;
static bool open = false;

vector<float> vertices;
unsigned int VAO, VBO;
bool hasVAO;
bool startready;
bool desready;
int stringtoint(string a)
{
	stringstream ss;
	ss << a;
	int b;
	ss >> b;
	return b;
}
class anchor
{
public:
	textRender a;
	string b;
	float x1, y1, x2, y2;
	float tx1, ty1, tx2, ty2;

	float x;
	float y;//在图片上的坐标

	float xp;
	float yp;//在屏幕上的坐标,单位1600,900

	float vertice[18];
	createwindow window;
	float sc;//在屏幕上的半径
	glm::vec3 tcolor;
	glm::vec3 bcolor;
	bool flag1;
	bool flag11;
	bool flag2;
	bool flag3;
	bool selected;
	int index;
public:
	int selectalbe;
	anchor(createwindow windowname, string name, float scale, float xPos, float yPos, glm::vec3 textcolor, glm::vec3 buttoncolor)
	{
		selectalbe = 1;
		window = windowname;

		b = name;

		xp = xPos;
		yp = yPos;

		x = getPicPos((xp - 800) / 800, (yp - 450) / 450).x;
		y = getPicPos((xp - 800) / 800, (yp - 450) / 450).y;

		tcolor = textcolor;
		bcolor = buttoncolor;

		sc = scale;
		vertice[0] = -sc; vertice[1] = -sc; vertice[2] = 0.01f;
		vertice[3] = sc; vertice[4] = -sc; vertice[5] = 0.01f;
		vertice[6] = sc; vertice[7] = sc; vertice[8] = 0.01f;
		vertice[9] = -sc; vertice[10] = -sc; vertice[11] = 0.01f;
		vertice[12] = sc; vertice[13] = sc; vertice[14] = 0.01f;
		vertice[15] = -sc; vertice[16] = sc; vertice[17] = 0.01f;
		flag11 = false;
		flag2 = false;
	}
	anchor(createwindow windowname, int ind, float scale, float xPos, float yPos, glm::vec3 textcolor, glm::vec3 buttoncolor)
	{
		selectalbe = 1;

		index = ind;
		selected = false;
		window = windowname;


		x = xPos;
		y = yPos;



		tcolor = textcolor;
		bcolor = buttoncolor;

		sc = scale;
		vertice[0] = -sc; vertice[1] = -sc; vertice[2] = 0.01f;
		vertice[3] = sc; vertice[4] = -sc; vertice[5] = 0.01f;
		vertice[6] = sc; vertice[7] = sc; vertice[8] = 0.01f;
		vertice[9] = -sc; vertice[10] = -sc; vertice[11] = 0.01f;
		vertice[12] = sc; vertice[13] = sc; vertice[14] = 0.01f;
		vertice[15] = -sc; vertice[16] = sc; vertice[17] = 0.01f;
		flag11 = false;
		flag2 = false;
	}
	void render(Shader& buttonshader)
	{
		if (glfwGetMouseButton(window.value(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
		{
			if (flag11)
			{
				flag1 = mouseposition();
			}
			flag11 = false;
		}
		else
		{
			if (flag1)
			{
				flag2 = true;
			}
			flag1 = false;
		}
		if (mouseposition() && glfwGetMouseButton(window.value(), GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
		{
			flag11 = true;
		}
		else
		{
			flag11 = false;
			flag2 = false;
		}

		glm::vec3 aaa;
		if (flag11)
		{
			aaa = glm::vec3(0.4, 0.4, -0.4);
		}
		else if (flag1)
		{
			aaa = glm::vec3(0.2, 0.2, 0.2);
		}
		else
		{
			aaa = glm::vec3(0, 0, 0);
		}

		glm::vec3 bbb;
		if (click())
		{
			cout << index << endl;

			selected = !selected;
		}

		if (selected)
			bbb = glm::vec3(0.4, 0.4, -0.5);
		else
			bbb = glm::vec3(0, 0.0, 0);

		basicdraw temp(vertice, sizeof(vertice));
		double size = 1;
		if (selected)
			size += 0.5;
		xp = getScreenPos(x, y).x;
		yp = getScreenPos(x, y).y;
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(xp, yp, 0));
		xp = xp * 800 + 800;
		yp = yp * 450 + 450;
		if (selectalbe)
		{
			buttonshader.use();
			buttonshader.setVec3("ourColor", bcolor + aaa + bbb);
			buttonshader.setMat4("model", model);
			buttonshader.setVec2("mypos", glm::vec2(xp, yp));
			buttonshader.setFloat("r", sc * scalef * size);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			temp.draw(buttonshader.id());
			glDisable(GL_BLEND);
		}

	}
	bool mouseposition()
	{
		float a = window.mousex() * 1600 / window.x();
		float b = (window.y() - window.mousey()) * 900 / window.y();
		float c = (a - xp) * (a - xp);
		float d = (b - yp) * (b - yp);
		return (c + d < sc * sc * scalef * scalef);
	}
	bool click()
	{
		if (flag2)
		{
			flag2 = false;
			return true;
		}
		return false;
	}
};
vector<anchor> anchors;
vector<anchor>::iterator anp;
string ttostring(float f)
{
	string s;
	stringstream ss;
	ss << f;
	ss >> s;
	return s;
}
string ttostring(int f)
{
	string s;
	stringstream ss;
	ss << f;
	ss >> s;
	return s;
}
#pragma region 问题的理论求解
class Floyd
{
private:
	int n; // 图中节点的数量
	int path[maxv][maxv];
	void getmindis()
	{
		int i, j, k;
		for (k = 0; k < n; k++)
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
				{
					if (d[i][k] + d[k][j] < d[i][j])
					{
						d[i][j] = d[i][k] + d[k][j];
						path[i][j] = path[i][k];
					}
				}
	}

public:
	int dest[maxv];       // 所有目的地的序号
	int start;            // 起点
	int n_d;              // 目的地的数量
	double d[maxv][maxv]; // 记录节点之间的最短距离
	string name[maxv];    // 记录节点的名称
	Floyd(int numN, int startp, vector<int> des)
	{
		n = numN;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == j)
					d[i][j] = 0;
				else
					d[i][j] = 1000.0;
				path[i][j] = j;
			}
		}
		ifstream ifs;
		ifs.open("edata.txt", ios::in);
		//if (ifs.is_open())
		//	cout << 1 << endl;
		string l;

		while (getline(ifs, l))
		{
			int i = l.find("-");
			int j = l.find(":");
			stringstream s1, s2, s3;
			string a1, a2, a3;
			a1 = l.substr(0, i);
			a2 = l.substr(i + 1, j - i - 1);
			a3 = l.substr(j + 1, l.length() - j);
			int t1, t2;
			double t3;
			s1 << a1;
			s2 << a2;
			s3 << a3;
			s1 >> t1;
			s2 >> t2;
			s3 >> t3;
			d[t1][t2] = t3;
			d[t2][t1] = t3;
		}


		n_d = des.size();
		start = startp;
		for (int i = 0; i < n_d; i++)
		{
			dest[i] = des[i];

		}

		getmindis();
	}

	void getpath(int start, int end)
	{
		int i = start;
		while (i != end)
		{
			cout << i << "->";
			suibian += ttostring(i);
			suibian += "+";
			hcount++;
			vertices.push_back(anchors[i].x);
			vertices.push_back(anchors[i].y);

			i = path[i][end];
		}
	}
};

typedef struct ArcBox
{
	int tailvex, headvex;
	struct ArcBox* hlink, * tlink;
	double info;
} ArcBox;

typedef struct VexNode
{
	int data;
	ArcBox* firstin, * firstout;
} VexNode;

typedef struct
{
	VexNode xlist[maxv];
	int vexnum, edgenum;
} OLGraph;

OLGraph G;

double up = 99; // 上界

class node
{
public:
	int st;         // 路径的起点
	int ed;         // 离开结点，当前路径的终点
	int k;          // 走过的结点数
	double sumv;    // 经过路径的总长度
	double lb;      // 每个分支的下界
	bool vis[maxv]; // 本路径中已经走过结点的标识
	int path[maxv]; // 记录经过的结点编号
	node()
	{
		st = 0;
		ed = 0;
		k = 0;
		sumv = 0;
		for (int i = 0; i < G.vexnum; i++)
		{
			vis[i] = 0;
		}
	}
	void clear()
	{
		st = 0; ed = 0; k = 0; sumv = 0; lb = 0;
		for (int i = 0; i < maxv; i++)
		{
			vis[i] = 0;
			path[i] = 0;
		}


	}
	void add(int ed_new, double w)
	{
		sumv = sumv + w;
		vis[ed_new] = 1;
		path[k] = ed_new;
		k++;
		ed = ed_new;
		lb = getlb();
	}
	void del(int w)
	{
		sumv = sumv - w;
		vis[ed] = 0;
		k--;
		ed = path[k - 1];
		lb = getlb();
	}
	double getlb()
	{
		double lb2 = 0;
		lb2 += sumv * 2;
		ArcBox* p = G.xlist[ed].firstout;
		while (p != NULL)
		{
			if (vis[p->headvex] == 0)
			{
				lb2 += p->info;
				break;
			}
			p = p->tlink;
		}
		p = G.xlist[st].firstin;
		while (p != NULL)
		{
			if (vis[p->tailvex] == 0)
			{
				lb2 += p->info;
				break;
			}
			p = p->hlink;
		}
		for (int i = 0; i < G.vexnum; i++)
		{
			if (vis[i] == 0)
			{
				p = G.xlist[i].firstout;
				lb2 += p->info;
				p = G.xlist[i].firstin;
				lb2 += p->info;
			}
		}
		return lb2 / 2;
	}

	bool operator<(const node& other) const
	{
		return lb > other.lb;
	}
};

void addedge(int start, int end, double w)
{
	ArcBox* p = new ArcBox;
	p->tailvex = start;
	p->headvex = end;
	p->info = w;

	ArcBox* q = G.xlist[start].firstout;
	if (q == NULL || q->info >= w)
	{
		p->tlink = q;
		G.xlist[start].firstout = p;
	}
	else
	{
		while (q->tlink != NULL && (q->tlink)->info < w)
		{
			q = q->tlink;
		}
		p->tlink = q->tlink;
		q->tlink = p;
	}

	q = G.xlist[end].firstin;
	if (q == NULL || q->info >= w)
	{
		p->hlink = q;
		G.xlist[end].firstin = p;
	}
	else
	{
		while (q->hlink != NULL && (q->hlink)->info < w)
		{
			q = q->hlink;
		}
		p->hlink = q->hlink;
		q->hlink = p;
	}
}
void creatG(Floyd& f)
{
	G.vexnum = f.n_d + 1;
	G.edgenum = G.vexnum * (G.vexnum - 1);
	G.xlist[0].data = f.start;
	G.xlist[0].firstin = NULL;
	G.xlist[0].firstout = NULL;
	for (int i = 1; i <= f.n_d; i++)
	{
		G.xlist[i].data = f.dest[i - 1];
		G.xlist[i].firstin = NULL;
		G.xlist[i].firstout = NULL;
	}
	for (int i = 0; i < f.n_d; i++)
	{
		if (fabs(f.d[f.start][f.dest[i]] - maxd) > 0.001)
			addedge(0, i + 1, f.d[f.start][f.dest[i]]);
		if (fabs(f.d[f.dest[i]][f.start] - maxd) > 0.001)
			addedge(i + 1, 0, f.d[f.dest[i]][f.start]);
	}
	for (int i = 1; i <= f.n_d; i++)
	{
		for (int j = 1; j <= f.n_d; j++)
		{
			if (i != j)
				if (fabs(f.d[f.dest[i - 1]][f.dest[j - 1]] - maxd) > 0.001)
					addedge(i, j, f.d[f.dest[i - 1]][f.dest[j - 1]]);
		}
	}
}

node ans_node;

double sum;
int visit[maxv];
bool flag = true;
void dfs(int num, int index)
{
	ArcBox* p = G.xlist[num].firstout;
	if (index == G.vexnum - 1)
	{
		while (p != NULL)
		{
			if (p->headvex == 0)
			{
				ans_node.add(p->headvex, p->info);
				flag = false;
				return;
			}
			p = p->tlink;
		}
	}
	else
	{
		while (p != NULL)
		{
			if (visit[p->headvex] == 0)
			{
				visit[p->headvex] = 1;
				ans_node.add(p->headvex, p->info);
				dfs(p->headvex, index + 1);
				if (!flag)
					return;
				visit[p->headvex] = 0;
				ans_node.del(p->info);
			}
			p = p->tlink;
		}
	}
}

int getup()
{
	sum = 0;
	visit[0] = 1;
	ans_node.add(0, 0);
	dfs(0, 0);
	up = ans_node.sumv;
	return sum;
}

priority_queue<node> q;

void bfs()
{
	while (!q.empty())
	{
		node temp = q.top();
		q.pop();
		if (temp.k == G.vexnum)
		{
			ArcBox* p = G.xlist[temp.ed].firstout;
			while (p != NULL)
			{
				if (p->headvex == temp.st)
				{
					double ans = temp.sumv + p->info;
					if (ans < up)
					{
						up = ans;
						temp.add(p->headvex, p->info);
						ans_node = temp;
					}
				}
				p = p->tlink;
			}
		}
		else if (temp.lb < up)
		{
			ArcBox* p = G.xlist[temp.ed].firstout;

			while (p != NULL)
			{
				if (temp.vis[p->headvex] == 0)
				{
					node temp2;
					temp2 = temp;
					temp2.add(p->headvex, p->info);
					q.push(temp2);
				}
				p = p->tlink;
			}
		}
	}
}
#pragma endregion


float testvertices[]
{
0.5,0.5,
-0.5,-0.5,
0.5,-0.5,
0,0.5,
-0.5,0.8,

};



void showans()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &(vertices[0]), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glBindVertexArray(0);
	starttime= glfwGetTime();
	hasVAO = true;
}
float mytime, mytime2, mytime3;
bool showmove;
double showx = 0.5, showy = 0.5;
string UTF8ToGB(const char* str)
{
	std::string result;
	WCHAR* strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

void drawhistory(historyitem hitem)
{
	string s = hitem.idata;
	cout << s << endl;
	int p1 = s.find(':');
	int p2 = s.find('+',p1);
	cout << p2 << endl;
	int n = stringtoint(s.substr(p1 + 1, p2 - p1 - 1));
	for (int i = 0; i < n; i++)
	{
		int p3 = s.find('+',p2 + 1);

		int a = stringtoint(s.substr(p2 + 1, p3 - p2 - 1));

		if (i == 0)
		{
			cout << "start:" << a << endl;
			anchors[a].bcolor = glm::vec3(1, 0.1, 0.1);
		}

		else
		{
			cout << "des:" << a << endl;
			anchors[a].bcolor = glm::vec3(0.8, 0.8, 0.0);
		}
		p2 = p3;
	}
	int p3 = p2;
	p2 = s.find( '+', p2 + 1);
	int m = stringtoint(s.substr(p3 + 1, p2 - p3 - 1));
	for (int i = 0; i < m; i++)
	{
		int p4 = s.find('+', p2 + 1);
		int a = stringtoint(s.substr(p2 + 1, p4 - p2 - 1));
		vertices.push_back(anchors[a].x);
		vertices.push_back(anchors[a].y);
		p2 = p4;
	}
	showans();
}

void gethisdata()
{
	ifstream fh;
	fh.open("history.txt", ios::in);
	if (!fh)
	{
		cout << "Failed to open the file." << endl;
		exit(0);
	}
	int count = 0;
	while (!fh.eof())
	{
		string s;
		getline(fh, s);
		s = UTF8ToGB(s.c_str());

		if (s.size() < 2)
			break;
		historyitem temp;

		int p1 = s.find(':');
		string nameitem = s.substr(0, p1);
		temp.name = nameitem;
		temp.idata = s;
		items.push_back(temp);
	}
	fh.close();
}
void savehisdata()
{
	ofstream f1;
	f1.open("history.txt", ios::out);
	if (!f1)
	{
		cout << "Failed to open the file." << endl;
		exit(0);
	}
	for (int i = 0; i < items.size(); i++)
	{
		f1 << items[i].idata << endl;
	}
	f1.close();
}

class edge
{
public:
	edge(int st, int ed, double d)
	{
		start = st;
		end = ed;
		dis = d;
	}
	int start;
	int end;
	double dis;

	bool operator<(const edge& other) const
	{
		return dis > other.dis;
	}
};

struct point
{
	point(double xx, double yy, int ii)
	{
		x = xx;
		y = yy;
		index = ii;
	}
	double x;
	double y;
	int index;
};

class minGtree
{
public:
	int N;
	vector<point> p;
	priority_queue<edge> q;
	vector<edge> ans;
	minGtree()
	{
		N = 0;
		p.clear();
	}
	void add(double x, double y, int i)
	{
		p.push_back(point(x, y, i));
		N++;
	}
	double getdis(int i, int j)
	{
		double x = (p[i].x - p[j].x) * (p[i].x - p[j].x);
		double y = (p[i].y - p[j].y) * (p[i].y - p[j].y);
		return sqrt(x + y);
	}
	void gen()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N && i != j; j++)
            {
                q.push(edge(i, j, getdis(i, j)));
            }
        }
        UnionFind f(100);
        int n = 0;
        while (n < N - 1)
        {
            edge temp = q.top();
            q.pop();
            if (f.find(temp.start) != f.find(temp.end))
            {
                ans.push_back(temp);
				f.unite(temp.start, temp.end);
				n++;
            }
           
        }
    }
	void output()
	{
		for (int i = 0; i < ans.size(); i++)
		{
			vertices.push_back(anchors[p[ans[i].start].index].x);
			vertices.push_back(anchors[p[ans[i].start].index].y);
			vertices.push_back(anchors[p[ans[i].end].index].x);
			vertices.push_back(anchors[p[ans[i].end].index].y);
		}
	}
};
bool disflag;
glm::vec2 mypos1, mypos2;


int main()
{
	
	createwindow pwindow(1600, 900, "Hitwh TSP Navigator");
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	//加载IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	io.Fonts->AddFontFromFileTTF("Dengb.ttf", 20.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
	ImGui_ImplGlfw_InitForOpenGL(pwindow.value(), true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsLight();
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = style.ChildRounding = style.FrameRounding = style.PopupRounding = style.ScrollbarRounding = style.GrabRounding = style.LogSliderDeadzone = style.TabRounding = 12.0f;
	style.Alpha = 0.9;
	//加载文字并设置
	Shader textshader("myfile/text.vs", "myfile/text.fs");//文本着色器
	glm::mat4 projectiontext = glm::ortho(0.0f, pwindow.x(), 0.0f, pwindow.y());
	textshader.use();
	glUniformMatrix4fv(glGetUniformLocation(textshader.id(), "projection"), 1, GL_FALSE, glm::value_ptr(projectiontext));
	textRender Text;
	//加载着色器
	Shader rectangleshader("myfile/rectan.vs", "myfile/rectan.fs");
	Shader buttonshader("myfile/button.vs", "myfile/button.fs");//按钮着色器
	Shader onetexture3d("myfile/onetexture.vs", "myfile/onetexture.fs");
	Shader anchorshader("myfile/anchor.vs", "myfile/anchor.fs");
	Shader lineshader("myfile/line.vs", "myfile/line.fs", "myfile/line.gs");
	Shader treeshader("myfile/edge.vs", "myfile/edge.fs", "myfile/edge.gs");
	Shader trishader("myfile/triangle.vs", "myfile/triangle.fs");
	Shader disline("myfile/disline.vs", "myfile/disline.fs", "myfile/disline.gs");
	onetexture3d.use();
	onetexture3d.setInt("texture1", 0);
	onetexture3d.setInt("texture2", 1);
	//按钮
	button back(pwindow, "BACK", 0.5, 1452, 10, 1585, 56, glm::vec3(0, 0.4, 0.8), glm::vec3(0.3, 0.9, 0.3));
	button start(pwindow, "START", 1.0, 640, 500 - 175-30, 961, 576 - 175-30, glm::vec3(0.6, 1, 0.6), glm::vec3(0, 0.6, 0.8));
	button navigate(pwindow, "Navigate", 0.5, 1200, 10, 1400, 56, glm::vec3(0.6, 1, 0.6), glm::vec3(0.2, 0.8, 1));
	
	//锚点
	anchor testanchor(pwindow, "test", 50, 1200, 450, glm::vec3(0, 204.0 / 255, 1.0), glm::vec3(0, 0.4, 0.8));
	char testtext[100];

	//图片
	textureRGB mappicture("myfile/map.jpg");

	//锚点数据加载
	ifstream f2;
	f2.open("data.txt", ios::in);
	if (!f2)
	{
		cout << "Failed to open the file." << endl;
		exit(0);
	}

	gethisdata();
	int count = 0;
	while (!f2.eof())
	{
		string s;
		getline(f2, s);
		s = UTF8ToGB(s.c_str());
		if (s.size() < 3)
			break;
		int p1 = s.find(','); int p2 = s.find('-'); int p3 = s.find('*');

		if (p3 == -1)
		{
			string s1 = s.substr(0, p1);
			string s2 = s.substr(p1 + 1, p2);
			string s3 = s.substr(s.length() - 1, 1);
			stringstream ss1;
			stringstream ss2;
			stringstream ss3;
			ss1 << s1; ss2 << s2;
			float d1, d2;
			ss1 >> d1; ss2 >> d2;
			ss3 << s3;
			int d3;
			ss3 >> d3;

			anchor temp(pwindow, count++, 60, d1, d2, glm::vec3(0, 204.0 / 255, 1.0), glm::vec3(0, 0.4, 0.8));
			temp.selectalbe = d3;
			anchors.push_back(temp);
		}
		else
		{
			int p4 = s.find('+');
			string name = s.substr(p3 + 1, p4 - p3 - 1);

			string s1 = s.substr(0, p1);
			string s2 = s.substr(p1 + 1, p2);
			string s3 = s.substr(p2 + 1, 1);
			stringstream ss1;
			stringstream ss2;
			stringstream ss3;
			ss1 << s1; ss2 << s2;
			float d1, d2;
			ss1 >> d1; ss2 >> d2;
			ss3 << s3;
			int d3;
			ss3 >> d3;
			anchor temp(pwindow, count++, 60, d1, d2, glm::vec3(0, 204.0 / 255, 1.0), glm::vec3(0, 0.4, 0.8));
			temp.selectalbe = d3;
			temp.b = name;

			anchors.push_back(temp);
		}


	}
	f2.close();
	N = count;

	float myver[] = {
		-0.10f, 0.30f,0.0f, // left  
		 0.10f, 0.30f,0.0f,  // right 
		 0.0f,  0.0f,0.0  // top   
	};
	basicdraw tri1(myver, sizeof(myver));

	//menu=1
	float mapshowerv[] = {
		 6.016f, 7.68f,0.0f,1.0f,1.0f,
		 6.016f,-7.68f,0.0f,1.0f,0.0f,
		-6.016f,-7.68f,0.0f,0.0f,0.0f,
		-6.016f, 7.68f,0.0f,0.0f,1.0f
	};
	unsigned int mapshoweri[] = {
		0,1,2,
		0,2,3
	};
	unsigned int mapVBO, mapVAO, mapEBO;
	glGenVertexArrays(1, &mapVAO);
	glGenBuffers(1, &mapVBO);
	glGenBuffers(1, &mapEBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(mapVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mapVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mapshowerv), mapshowerv, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mapEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mapshoweri), mapshoweri, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glm::mat4 view, projection;
	projection = glm::perspective(glm::radians(45.0f), pwindow.x() / pwindow.y(), 0.1f, 100.0f);
	glEnable(GL_BLEND);


	functiondrawer ballxtex(1600, 900);

	glBindFramebuffer(GL_FRAMEBUFFER, ballxtex.framebuffer);
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(pwindow.value()))
	{
		glLineWidth(50 * scalef);
		mousehide = false;

		if (guifocus)
		{
			if(!showmove)
				pwindow.yset = scalef;
			mousescroll(0.0, pwindow.mousescroll());
			moveflag = false;
			lastX = pwindow.mousex();
			lastY = pwindow.mousey();
		}
		else
		{
			moveflag = true;

			processInput(pwindow.value(), pwindow);
			mousefunction(pwindow.mousex(), pwindow.mousey());
			mousescroll(0.0, pwindow.mousescroll());

		}
		mytime++; mytime2++;

		if (!showmove)
		{
			mytime3 = 0;
			if (mytime > 100000)
				mytime = 0;
			if (mytime2 > 100000)
				mytime2 = 0;
		}
		else
		{
			mytime = 0;
			mytime2 = 0;
			mytime3++;
		}

		if (menu == 0)
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;



			start.render(textshader, buttonshader);
			if (start.click())
			{
				mytime = 0;
				mytime2 = 0;
				menu = 1;
			}
			sprintf_s(testtext, "Hitwh Multiple Des Navigator");
			Text.RenderText(textshader, testtext, 185,550, 1.0f, glm::vec3(0.4,1,1));
			if (test)
			{
				sprintf_s(testtext, "(%.2f,%.2f),pos:(%.2f,%.2f,%.2f),Front:(%.2f,%.2f,%.2f),Up:(%.2f,%.2f,%.2f),", pwindow.mousex(), 900 - pwindow.mousey(), cameraPos.x, cameraPos.y, cameraPos.z, cameraFront.x, cameraFront.y, cameraFront.z, cameraUp.x, cameraUp.y, cameraUp.z);
				Text.RenderText(textshader, testtext, 2.0f, 2.0f, 0.25f, glm::vec3(1.0f, 1.0f, 102 / 255.0));
			}

			glfwSwapBuffers(pwindow.value());
			glfwPollEvents();
		}

		if (menu == 1)
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			cameraFront = glm::normalize(glm::vec3(0, -0.99, 0.001));

			model = glm::mat4(1.0f);

			model = glm::scale(model, glm::vec3(0.9f * scalef, 1.6f * scalef, scalef));
			model = glm::translate(model, transvec);


			double left, right, up, down;
			left = getScreenPos(0, 0).x;
			right = getScreenPos(1, 1).x;
			up = getScreenPos(1, 1).y;
			down = getScreenPos(0, 0).y;

			if (!showmove)
			{
				if (glfwGetMouseButton(pwindow.value(), GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
				{
					if (right - left < 2)
					{
						if (fabs(transvec.x) < 0.001)
							mytime = 0;
						transvec.x = transvec.x - transvec.x * (1 - pow(1.02, -mytime / 100.0));
					}
					else
					{
						if (left > -1.0f)
						{
							transvec.x = transvec.x - (left + 1.0f) * (1 - pow(1.02, -mytime / 100.0));
						}

						else if (right < 1.0f)
						{

							transvec.x = transvec.x + (1.0f - right) * (1 - pow(1.02, -mytime / 100.0));
						}
						if (left < -0.999 && right>0.999)
							mytime = 0;

					}
					if (up - down > 2)
					{
						if (up < 1.0)
							transvec.y = transvec.y + (1.0 - up) * (1 - pow(1.02, -mytime2 / 100.0));
						if (down > -1.0)
							transvec.y = transvec.y - (down + 1.0) * (1 - pow(1.02, -mytime2 / 100.0));
						if (up > 0.999 && down < -0.999)
							mytime2 = 0;

					}
					else
					{
						if (fabs(transvec.y) < 0.001)
							mytime2 = 0;

						transvec.y = transvec.y - transvec.y * (1 - pow(1.02, -mytime2 / 100.0));

					}
				}
				else
					mytime = mytime2 = 0;
			}

			if (showmove)
			{
				glm::vec2 temp = getPicPos(0, 0);
				transvec.x = transvec.x - (showx - temp.x) * (1 - pow(1.21, -mytime3 / 100.0));
				transvec.y = transvec.y - (showy - temp.y) * (1 - pow(1.21, -mytime3 / 100.0));
				pwindow.yset += (0.4 - pwindow.yset) * 0.1 * (1 - pow(1.11, -mytime3 / 100.0));
				if (fabs(temp.x - showx) < 0.001 && fabs(temp.y - showy) < 0.001)
				{
					mytime3 = 0;
					showmove = false;
				}
			}

			if (glfwGetMouseButton(pwindow.value(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
			{
				float a = pwindow.mousex();
				float b = 900 - pwindow.mousey();
				glm::vec2 temp = getPicPos((a - 800) / 800, (b - 450) / 450);
				ballxtex.renderframe((temp.x-0.5)*2, (temp.y-0.5)*2);
			}

			
			
			onetexture3d.use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mappicture.id);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, ballxtex.texColorBuffer);
			onetexture3d.setMat4("model", model);
			glBindVertexArray(mapVAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			if (disflag)
			{
				
				
				double x1 = getScreenPos(mypos1.x, mypos1.y).x;
				double y1 = getScreenPos(mypos1.x, mypos1.y).y;
				double x2 = getScreenPos(mypos2.x, mypos2.y).x;
				double y2 = getScreenPos(mypos2.x, mypos2.y).y;
				
				

				

				disline.use();
				disline.setVec2("mypos1", glm::vec2(x1,y1));
				disline.setVec2("mypos2", glm::vec2(x2, y2));
				glBindVertexArray(tri1.VAO);
				glDrawArrays(GL_LINES, 0,2);
				sprintf_s(testtext, "%lf", sqrt(glm::length(mypos1 - mypos2)) * 100.0);
				Text.RenderText(textshader, testtext, (x1 + x2) / 2 * 800 + 800, (y1 + y2) / 2 * 450 + 450, 1.5f * scalef, glm::vec3(0.9,0.3,0.9));

				trishader.use();
				glm::mat4 model2, model3;
				model2 = glm::translate(model2, glm::vec3(x1, y1, 0));
				model2 = glm::scale(model2, glm::vec3(scalef, scalef, scalef));
				model3 = glm::translate(model3, glm::vec3(x2, y2, 0));
				model3 = glm::scale(model3, glm::vec3(scalef, scalef, scalef));
				trishader.setMat4("model", model2);
				trishader.setVec3("mycolor", glm::vec3(1, 51.0 / 255, 0));
				tri1.draw(trishader.id());
				trishader.setMat4("model", model3);
				trishader.setVec3("mycolor", glm::vec3(0, 204.0 / 255, 1));
				tri1.draw(trishader.id());
			}
			if (glfwGetMouseButton(pwindow.value(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
			{
				float a = pwindow.mousex();
				float b = 900 - pwindow.mousey();
				glm::vec2 temp = getPicPos((a - 800) / 800, (b - 450) / 450);
				ballxtex.renderframe((temp.x - 0.5) * 2, (temp.y - 0.5) * 2);
			}
			if (hasVAO)
			{
				if (modd == 1)
				{
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					float timeValue = glfwGetTime() - starttime;
					timeValue = timeValue / vertices.size() * 5;
					timeValue = timeValue - (int)timeValue;
					lineshader.use();
					lineshader.setFloat("time1", timeValue);
					lineshader.setMat4("model", model);
					lineshader.setFloat("sc", scalef);
					lineshader.setInt("mysum", vertices.size() / 2);
					glBindVertexArray(VAO);
					glDrawArrays(GL_LINE_STRIP, 0, vertices.size() / 2);
				}

				if (modd == 2)
				{
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					
					
					treeshader.use();
					treeshader.setMat4("model", model);
					glBindVertexArray(VAO);
					glDrawArrays(GL_LINES, 0, vertices.size() / 2);
				}

			}

			for (anp = anchors.begin(); anp != anchors.end(); anp++)
			{
				anp->render(anchorshader);
			}

			//IMGUI
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			io.FontGlobalScale = 1.0f;
			
			if (open)
			{
				ImGui::Begin(u8"导航设置", &open, ImGuiWindowFlags_AlwaysAutoResize);

				if (startready)
				{
					ImGui::Text(u8"设置完毕");
				}
				else
					ImGui::Text(u8"请设置起点");
				ImGui::SameLine();
				if (ImGui::Button(u8"设置起点"))
				{
					cout << "开始设置起点:" << endl;

					for (anp = anchors.begin(); anp != anchors.end(); anp++)
					{
						if (anp->selected && anp->selectalbe)
						{
							startpoint = anp->index;
							startready = true;
						}
					}
					if (startready)
					{
						anchors[startpoint].bcolor = glm::vec3(1, 0.1, 0.1);
						cout << "起点为:" << startpoint << endl;
					}
					
					for (anp = anchors.begin(); anp != anchors.end(); anp++)
					{
						anp->selected = false;

					}
				}
				ImGui::SameLine();
				HelpMarker(u8"将当前选中的点设为起点");
				if (desready)
				{
					ImGui::Text(u8"设置完毕");
				}
				else
				ImGui::Text(u8"请设置目的地");
				ImGui::SameLine();
				if (ImGui::Button(u8"设置目的地"))
				{
					cout << "开始设置目的地" << endl;

					for (anp = anchors.begin(); anp != anchors.end(); anp++)
					{
						if (anp->selected && anp->selectalbe)
						{
							despoint.push_back(anp->index);
							anp->bcolor = glm::vec3(0.8, 0.8, 0.0);
							desready = true;
						}

					}
					if (desready)
					{
						cout << "目的地设置完毕" << endl;
					}
					for (anp = anchors.begin(); anp != anchors.end(); anp++)
					{
						anp->selected = false;
					}
				}
				ImGui::SameLine();
				HelpMarker(u8"将当前选中的点设为目的地");
				ImGui::Text(u8"铺设地下管道:");
				ImGui::SameLine();
				static bool errorwindow;
				if (ImGui::Button(u8"最小生成树"))
				{
					if (hasVAO)
					{
						hasVAO = false;
						vertices.clear();
						glDeleteVertexArrays(1, &VAO);
						glDeleteBuffers(1, &VBO);
					}
					


					modd = 2;
					minGtree t;
					for (anp = anchors.begin(); anp != anchors.end(); anp++)
					{
						if (anp->selected && anp->selectalbe)
						{
							t.add(anp->x, anp->y, anp->index);
						}
					}
					if (t.N <= 1)
					{
						errorwindow = true;
					}
					else
					{
						t.gen();
						t.output();
						showans();
					}
					
				}
				if (errorwindow)
				{
					ImGui::OpenPopup(u8"注意");

					ImVec2 center = ImGui::GetMainViewport()->GetCenter();
					ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

					if (ImGui::BeginPopupModal(u8"注意", NULL, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(u8"请选择至少两个点!");

						ImGui::Separator();
						if (ImGui::Button(u8"确定", ImVec2(320, 0))) { errorwindow = false; ImGui::CloseCurrentPopup(); }

						ImGui::EndPopup();
					}
				}
				static char buf[32] = "";
				ImGui::InputText(u8"输入名字", buf, IM_ARRAYSIZE(buf));
				ImGui::SameLine();
				if (ImGui::Button(u8"搜索"))
				{
					string s = UTF8ToGB(buf);
					for (anp = anchors.begin(); anp != anchors.end(); anp++)
					{
						int ptemp = -1;
						if (s != "")
						{
							if (anp->b.find(s) != -1)
							{
								showx = anp->x;
								showy = anp->y;
								if (anp->selectalbe)
									anp->selected = true;
								showmove = true;
								break;
							}
						}

					}


				}
				if (ImGui::Button(u8"清空"))
				{
					buf[0] = '\0';
					up = 99;
					for (anp = anchors.begin(); anp != anchors.end(); anp++)
					{
						anp->selected = false;
						anp->bcolor = glm::vec3(0, 0.4, 0.8);
					}
					hasVAO = false;
					glDeleteVertexArrays(1, &VAO);
					glDeleteBuffers(1, &VBO);
					vertices.clear();
					despoint.clear();
					ans_node.clear();
					for (int i = 0; i < maxv; i++)
						visit[i] = 0;
					ArcBox* p5, * q;
					for (int i = 0; i < G.vexnum; i++)
					{
						p5 = G.xlist[i].firstout;
						while (p5 != NULL)
						{
							q = p5;
							p5 = p5->tlink;
							delete[]q;
						}
					}
					for (int i = 0; i < G.vexnum; i++)
					{
						G.xlist[i].firstout = NULL;
						G.xlist[i].firstin = NULL;
					}
					startready = false;
					desready = false;
					//cout << "清空完毕" << endl;
				}
				ImGui::SameLine();
				static int item_current_idx = 0; // Here we store our selection data as an index.
				
				
				if (ImGui::Button(u8"删除涂鸦"))
				{
					ballxtex.clear();
				}
				if (startready && desready)
				{
					ImGui::SameLine();
					
					if (ImGui::Button(u8"开始规划"))
					{
						hcount = 0;
						suibian = "";
						string hname = ttostring((int)items.size() + 1);
						historyitem temp;
						temp.name = hname;

						hname += ":";
						int nn = despoint.size();
						hname += ttostring(nn + 1) + "+" + ttostring(startpoint) + "+";
						for (int i = 0; i < despoint.size(); i++)
						{

							hname += ttostring(despoint[i]);
							hname += "+";
						}


						Floyd f(N, startpoint, despoint);
						creatG(f);
						getup(); // 求上界

						node start;
						start.add(0, 0);
						q.push(start);
						bfs();

						int pre = ans_node.path[0];
						for (int i = 1; i <= G.vexnum; i++)
						{
							int a = ans_node.path[i];
							f.getpath(G.xlist[pre].data, G.xlist[a].data);
							pre = a;
						}
						cout << f.start << endl;
						suibian += ttostring(f.start) + "+";
						hcount++;
						vertices.push_back(anchors[f.start].x);
						vertices.push_back(anchors[f.start].y);
						modd=1;
						showans();
						hname += ttostring(hcount) + "+" + suibian + "+";
						temp.idata = hname;
						items.push_back(temp);
						item_current_idx = items.size() - 1;
						cout << ans_node.sumv << endl;
						startready = false;
						desready = false;

					}
				}
				ImGui::SameLine();
				ImGui::Checkbox(u8"距离测量", &disflag);
				ImGui::SameLine();
				HelpMarker(u8"按Z和X设置标点");
				bool testf=false;
				ImGui::Separator();
				if (ImGui::BeginListBox(u8"历史记录"))
				{
					for (int n = 0; n < items.size(); n++)
					{
						const bool is_selected = (item_current_idx == n);
						if (ImGui::Selectable(items[n].name.c_str(), is_selected))
							item_current_idx = n;
						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndListBox();
				}
				if (ImGui::Button(u8"绘制"))
				{
					modd = 1;
					for (anp = anchors.begin(); anp != anchors.end(); anp++)
					{
						anp->selected = false;
						anp->bcolor = glm::vec3(0, 0.4, 0.8);
					}
					hasVAO = false;
					vertices.clear();
					glDeleteVertexArrays(1, &VAO);
					glDeleteBuffers(1, &VBO);
					drawhistory(items[item_current_idx]);
				}
				ImGui::SameLine();
				if (ImGui::Button(u8"删除"))
				{
					if (items.size()>0&& item_current_idx>=0&& item_current_idx<items.size())
					{
						vector<historyitem>::iterator p;
						p = items.begin();
						for (int i = 0; i < item_current_idx; i++)
						{
							p++;
						}
						items.erase(p);
					}

					
				}
				if (!open)
				{
					
					guifocus = false;
				}
					
				else
					guifocus = ImGui::IsWindowHovered() || ImGui::IsAnyItemHovered();

				ImGui::End();
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			}
			if (glfwGetMouseButton(pwindow.value(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
			{
				float a = pwindow.mousex();
				float b = 900 - pwindow.mousey();
				glm::vec2 temp = getPicPos((a - 800) / 800, (b - 450) / 450);
				ballxtex.renderframe((temp.x - 0.5) * 2, (temp.y - 0.5) * 2);
			}
			//Back按钮的绘制----------------------------------------
			navigate.render(textshader, buttonshader);
			if (navigate.click())
				open = true;
			back.render(textshader, buttonshader);
			if (back.click())
				menu = 0;
			if (test)
			{
				sprintf_s(testtext, "(%.2f,%.2f),pos:(%.2f,%.2f,%.2f),Front:(%.2f,%.2f,%.2f),Up:(%.2f,%.2f,%.2f),", pwindow.mousex(), 900 - pwindow.mousey(), cameraPos.x, cameraPos.y, cameraPos.z, cameraFront.x, cameraFront.y, cameraFront.z, cameraUp.x, cameraUp.y, cameraUp.z);
				Text.RenderText(textshader, testtext, 2.0f, 2.0f, 0.25f, glm::vec3(0.0f, 0.0f, 102 / 255.0));
			}
			savehisdata();
			if (disflag&&glfwGetKey(pwindow.value(), GLFW_KEY_Z) == GLFW_PRESS)
			{
				double mx = pwindow.mousex();
				double my = 900-pwindow.mousey();
				mypos1 = getPicPos((mx-800)/800,(my-450)/450);
			}
			if (disflag && glfwGetKey(pwindow.value(), GLFW_KEY_X) == GLFW_PRESS)
			{
				double mx = pwindow.mousex();
				double my = 900 - pwindow.mousey();
				mypos2 = getPicPos((mx - 800) / 800, (my - 450) / 450);
			}
			glfwSwapBuffers(pwindow.value());
			glfwPollEvents();
		}
	}
	return 0;
}

bool addflag = false;
bool printflag = false;
bool posflag;
string stemp;
bool mapmove = false;
void processInput(GLFWwindow* window, createwindow mywindow)
{

	float cameraSpeed = 4.0f * deltaTime;
	if (moveflag)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			transvec.y -= cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			transvec.y += cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			transvec.x += cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			transvec.x -= cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			scalef -= 0.5 * cameraSpeed * scalef;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			scalef += 0.5 * cameraSpeed * scalef;
	}
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		mapmove = true;

		//addflag = true;
	}
	else
	{
		firstMouse = true;
		mapmove = false;
	}

	if (menu == 0)
		addflag = false;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
	{
		if (addflag)
		{
			anchor p(mywindow, "111", 50, mywindow.mousex(), 900 - mywindow.mousey(), glm::vec3(0, 204.0 / 255, 1.0), glm::vec3(0, 204.0 / 255, 1.0));
			anchors.push_back(p);
			addflag = false;
		}
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		posflag = true;
	}
	if (posflag && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
	{

		float a = mywindow.mousex();
		float b = 900 - mywindow.mousey();
		glm::vec2 temp = getPicPos((a - 800) / 800, (b - 450) / 450);
		cout << temp.x << "," << temp.y << endl;
		posflag = false;
	}


	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		printflag = true;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
	{
		if (printflag)
		{
			stemp = "";
			float a1, a2, b1, b2;
			int ia, ib;
			int num = 0;
			for (anp = anchors.begin(); anp != anchors.end(); anp++)
			{
				if (anp->selected)
				{
					if (num == 0)
					{
						a1 = anp->x;
						a2 = anp->y;
						ia = anp->index;
						num = 1;
					}
					else if (num == 1)
					{
						b1 = anp->x;
						b2 = anp->y;
						ib = anp->index;
						num = 0;
					}
				}
			}
			cout << ia << "-" << ib << ":" << sqrt((a1 - b1) * (a1 - b1) + (a2 - b2) * (a2 - b2)) << endl;

			printflag = false;
		}
	}

}
void mousefunction(double xpos, double ypos)
{

	if (firstMouse)
	{

		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	if (mapmove)
	{
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;
		double a; double b;
		a = (getPicPos(1.0, 0).x - getPicPos(0, 0).x) / 800;
		b = (getPicPos(0, 1).y - getPicPos(0, 0).y) / 450;
		transvec.x += xoffset * 6.016 * a * 2;
		transvec.y += yoffset * 7.68 * b * 2;

	}




}
static double lastsco = 0;
void mousescroll(double xoffset, double yoffset)
{
	scalef = yoffset;
}
static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}