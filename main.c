#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define INFINITY			65535
#define MAX_VERTEX_NUM		20
#define OK					1
#define ERROR				0


typedef	char		VertexType;
typedef int 		VRType; 
typedef int 		Status; 

//定义辅助数组，记录顶点U到V-U大的代价最小的边 
struct {
	int	adjvex;
	VRType		lowcost;
}closeedge[MAX_VERTEX_NUM]; 

//------------图的数组（邻接矩阵）存储表示---------------// 
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];				//顶点向量 
	VRType	arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//邻接矩阵 
	int     vernum,arcnum;							//顶点和弧数 
}MAGraph;

int visited[MAX_VERTEX_NUM];

//构造无向网
Status CreateUDN(MAGraph *g){
	
	int i,j;
	int start ,end ,num;
	printf("请输入图的顶点数和弧数！(要求顶点数小于二十)\n");
	scanf("%d %d", &g->vernum, &g->arcnum ); 	
	printf("图的顶点数：%d和弧数：%d\n", g->vernum, g->arcnum );
	printf("请输入图的顶点的值\n");
	
	for(i = 0; i < g->vernum ; i++){
		getchar();
		scanf("%c", &g->vexs[i]);
		printf("第%d个顶点的值是：%c\n", i , g->vexs[i]);
	} 
	
	//初始化邻接矩阵 
	for(i = 0; i < g->vernum ; i++){
		for(j = 0; j < g->vernum ; j++){
			g->arcs[i][j] = INFINITY ;
		}
	}
	printf("请输入弧关联的顶点和权值！\n");
	for( i = 0 ; i < g->arcnum ; i++ ){
		getchar();		
		scanf("%d %d %d", &start, &end ,&num );

		g->arcs[start][end] = num ;
		g->arcs[end][start] = g->arcs[start][end] ;
		printf("顶点%c到顶点%c的权值是%d\n", g->vexs[start] , g->vexs[end] , num);
	} 
	
	printf("无向图初始化成功！\n");
	return OK;
} 

//以邻接矩阵的形式输出无向图 
void MAGraphPrint(MAGraph *g){
	
	int i,j;
	for(i = 0; i < g->vernum ; i++){
		for(j = 0; j < g->vernum ; j++){
			printf("%7d  ", g->arcs[i][j]);
		}
		printf("\n");
	}
}

int min(MAGraph *g){
	
	int i;
	int index = -1;
	int min = INFINITY;
	for(i = 0 ; i < g->vernum ; i++ ){
		if(visited[i] == 0 && closeedge[i].lowcost < min){
			min = closeedge[i].lowcost;
			index = i;
		}
		
	}
	return index;
}

void MiniSpanTree_PTIM(MAGraph *g, int v){
	
	int i,j;
	for(i = 0 ; i < g->vernum ; i++){						//辅助数组初始化 ，初始化之后closeedge[i]数组表示图中下标为i的顶点距离顶点下表为v的权值 
		if (i != v){
			visited[i] = 0;
			closeedge[i].adjvex = v;						//v表示顶点向量的下标， 
			closeedge[i].lowcost = g->arcs[v][i];			//g->arcs[v][i]表示两定点的权值。 
		}
	}
	visited[v] = 1;
	closeedge[v].lowcost = MAX_VERTEX_NUM;
	printf("普鲁姆算法求出的最小生成树：\n");
	for( i = 1 ; i < g->vernum ; i++ ){
		v = min(g);												//找出最小权值的顶点下标 
		if(v == -1)
			break;
		printf("顶点 %c 到顶点 %c 的权值为：%d\n",g->vexs[closeedge[v].adjvex], g->vexs[v], closeedge[v].lowcost );
		
		visited[v] = 1;
		closeedge[v].lowcost = INFINITY ;
		for(j = 0; j < g->vernum ; j++){
			if(visited[j] == 0 && g->arcs[v][j] < closeedge[j].lowcost){
				closeedge[j].adjvex = v;													//在这里改变了closeedge数组的相对的顶点 
				closeedge[j].lowcost = g->arcs[v][j];										// 在这里改变了closeedge数组的相对的顶点的权值 
			}
		}
		
	} 
	
	
} 

int main(int argc, char *argv[]) {
	
	MAGraph *g;
	
	g = (MAGraph *)malloc(sizeof(MAGraph));
	CreateUDN(g);
	MAGraphPrint(g);
	MiniSpanTree_PTIM(g, 0);
	return 0;
}
