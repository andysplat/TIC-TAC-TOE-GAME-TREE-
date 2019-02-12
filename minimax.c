#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	int x;
	int y;
} pozitie;

typedef struct node {
	char **t;
	char z;
	int n;
	int m;
struct node **next;
} Tree;

void free_tree(Tree *T)
{
	int m,n;
	for(m=1;m<=T->n;m++)
		if(T->next[m]!=NULL)
			free_tree(T->next[m]);
	for(n=1;n<=3;n++)
		free(T->t[n]);
	free(T->t);
	if(T->n!=0)
		free(T->next);
	free(T);
}
	
int verifica(char **t, char u)
{
	int x,y,z,w,v=0,i,j,o;
	for(x=1;x<=3;x++)	
		for(y=1;y<=3;y++)
			if(t[x][y]=='-')
				v++;
	for(i=1;i<=3;i++)
	{
  		x=0;
  		y=0;
  		for(j=1;j<=3;j++)
  		{	
    		if(t[i][j]==u)
      			x=x+1;
    		if(t[j][i]==u)
      			y=y+1;
      	}
  		if(x==3||y==3)
    		v=-1;
    }
	z=0;
	w=0;
	for(o=1;o<=3;o++)
 		if(t[o][o]==u)
   	 		z=z+1;
	i=1;
	j=3;
	while(i<=3&&j>=1)
	{
  	if(t[i][j]==u)
   	 	w=w+1;
    i++;
    j--;
    }
    if(z==3||w==3)
    	v=-1;
   	return v;
}

pozitie *cauta(char **t, pozitie *v)
{
	pozitie u;
	int x,y,o=1,m,n;
	for(x=1;x<=3;x++)	
		for(y=1;y<=3;y++)
			if(t[x][y]=='-')
			{
				v[o].x=x;
				v[o].y=y;
				o++;
			}
	o=o-1;
	for(m=1;m<o;m++)
		for(n=m+1;n<=o;n++)
			if(v[n].x*3+v[n].y<v[m].x*3+v[m].y)
			{
				u=v[n];
				v[n]=v[m];
				v[m]=u;
			}
	return v;
}

void print(char **t, int n, FILE *g)
{
	int x,y,m;
	for(x=1;x<=3;x++)
	{
		for(m=1;m<=n;m++)
			fprintf(g,"\t");
		for(y=1;y<=3;y++)
			if(y<3)
				fprintf(g,"%c ",t[x][y]);
			else
				fprintf(g,"%c\n",t[x][y]);
	}
	fprintf(g,"\n");
}

void print_tree(Tree *T,int n,FILE *g)
{
	int m;
	print(T->t,n-T->n,g);
	for(m=1;m<=T->n;m++)
		if(T->next[m]!=NULL)
			print_tree(T->next[m],n,g);
}

Tree* insert(Tree *T,char **t,int n,char z,int x,int y)
{
	int m;
	char **u=(char**)malloc(4*sizeof(char*));
	for(m=1;m<=3;m++)
		u[m]=(char*)malloc(4*sizeof(char));
	pozitie *v=(pozitie*)malloc((n+1)*sizeof(pozitie));
	if(n>=0)
	{
		T=(Tree*)malloc(sizeof(Tree));
		T->t=(char**)malloc(4*sizeof(char*));
		for(m=1;m<=3;m++)
			T->t[m]=(char*)malloc(4*sizeof(char));
		if(x!=0&&y!=0)
			t[x][y]=z;
		for(x=1;x<=3;x++)
		for(y=1;y<=3;y++)
			T->t[x][y]=t[x][y];
		if(z=='X')
			T->z='O';
		else
			T->z='X';
		T->n=n;
		if(T->n!=0)
		{
		T->next=(Tree**)malloc((n+1)*sizeof(Tree*));	
		for(m=1;m<=n;m++)
			T->next[m]=NULL;
		}
	if(verifica(T->t,'X')==-1||verifica(T->t,'O')==-1)
	{
		for(m=1;m<=3;m++)
			free(u[m]);
		free(u);
		free(v);
		return T;
	}
	v=cauta(T->t,v);
	for(m=1;m<=n;m++)
	{
		for(x=1;x<=3;x++)
		for(y=1;y<=3;y++)
			u[x][y]=T->t[x][y];
		if(z=='X')
			T->next[m]=insert(T->next[m],u,n-1,'O',v[m].x,v[m].y);
		else
			T->next[m]=insert(T->next[m],u,n-1,'X',v[m].x,v[m].y);			
	}
	for(m=1;m<=3;m++)
			free(u[m]);
	free(u);
	free(v);
	return T;
	}	
	for(m=1;m<=3;m++)
			free(u[m]);
	free(u);
	free(v);
	return NULL;
}

void T_F(Tree *T,char z)
{
	int m,n,o=0,x,y;
	for(m=1;m<=T->n;m++)
		if(T->next[m]!=NULL)
			T_F(T->next[m],z);
	if(verifica(T->t,z)==-1)
		T->z='T';
	else
	if(z=='X'&&verifica(T->t,'O')==-1||z=='O'&&verifica(T->t,'X')==-1)
			T->z='F';	
	else
		if(T->n==0)
			T->z='F';
		else
		{
			
			for(n=1;n<=T->n;n++)
				if(T->next[n]->z=='T')
					o++;
			
			if(o==0)
				T->z='F';
			else
				if(o==T->n)
					T->z='T';
				else
					if(T->z==z)
						T->z='T';
					else
						T->z='F';
		}
}	

void print_T_F(Tree *T,int n,FILE *g)
{
	int m,o;
	for(o=1;o<=n-T->n;o++)
		fprintf(g,"\t");
	fprintf(g,"%c\n",T->z);	
	for(m=1;m<=T->n;m++)
		if(T->next[m]!=NULL)
			print_T_F(T->next[m],n,g);
}

int min(Tree *T)
{
	int m,n;
	m=T->next[1]->m;
	for(n=2;n<=T->n;n++)
		if(T->next[n]->m<m)
			m=T->next[n]->m;
	return m;
}

int max(Tree *T)
{
	int m,n;
	m=T->next[1]->m;
	for(n=2;n<=T->n;n++)
		if(T->next[n]->m>m)
			m=T->next[n]->m;
	return m;
}
		

void tree_minimax(Tree *T, int n, int m)
{
	int o;
	if(n>2)
	{
	for(o=1;o<=T->n;o++)
		if(m==1)
			tree_minimax(T->next[o],n-1,-1);
		else
			tree_minimax(T->next[o],n-1,1);
	if(T->n!=0)
	if(m==1)
		T->m=max(T);
	else
		T->m=min(T);
	}
	else
	{
	if(T->n!=0)
	if(m==1)
		T->m=max(T);
	else
		T->m=min(T);
	}
}	
void print_tree_minimax(Tree *T,int n,FILE *g)
{
	int m,o;
	for(o=1;o<=n;o++)
		fprintf(g,"\t");
	fprintf(g,"%d\n",T->m);
	for(m=1;m<=T->n;m++)
		if(T->next[m]!=NULL)
			print_tree_minimax(T->next[m],n+1,g);
}


int main(int argc, char *argv[])
{
Tree *T=NULL;
Tree **P=NULL;
Tree **Q=NULL;
FILE *f;
FILE *g;
char *o,*k;
char z;
int x=1,y,w=1,n,m,v,u,l,q,p,r,s=1;
o=(char*)malloc(1000000*sizeof(char));
k=(char*)malloc(1000000*sizeof(char));
f=fopen(argv[argc-2],"r");
g=fopen(argv[argc-1],"w");
char **t=(char**)malloc(4*sizeof(char*));
for(m=1;m<=3;m++)
	t[m]=(char*)malloc(4*sizeof(char));
while(fgets(o,1000000,f)!=NULL)
{
	if(strlen(o)<=3)
		if(atoi(o)!=0)
		{
			p=atoi(o);
		}
		else
			z=o[0];
	else
	{
		if(argv[s][2]=='1'||argv[s][2]=='2')
		{
			
			for(y=0;y<3;y++)
			{
				t[x][y+1]=o[2*y];
			}
			x++;
		}
		else
		{
		if(T==NULL)
		{
			T=(Tree*)malloc(sizeof(Tree));
			T->n=atoi(o+1);
			T->next=(Tree**)malloc((T->n+1)*sizeof(Tree*));
			P=(Tree**)malloc(2*sizeof(Tree*));
			P[1]=T;	
			w=1;
		}
		else
		{
		l=0;
		for(v=1;v<=w;v++)
			l=l+P[v]->n;
		Q=(Tree**)realloc(Q,(l+1)*sizeof(Tree));	
		q=1;
		    		
		k = strtok (o," ");
		while (k != NULL)
  		{
    		if(k[0]=='(')
    		{
    			Q[q]=(Tree*)malloc(sizeof(Tree));
    			Q[q]->n=atoi(k+1);
    			Q[q]->m=0;
    			Q[q]->next=(Tree**)malloc((Q[q]->n+1)*sizeof(Tree*));
    		}
    		else
    		{
    			Q[q]=(Tree*)malloc(sizeof(Tree));
    			Q[q]->m=atoi(k+1);
    			Q[q]->n=0;
    		}
    		q++;
    		k = strtok (NULL, " ");
    	}		
    	q--;
    	l=0;
		for(v=1;v<=w;v++)
		{
			
			for(u=1;u<=P[v]->n;u++)
			{
				P[v]->next[u]=Q[l+u];
			}
			l=l+P[v]->n;
		}
		w=q;
		P=(Tree**)realloc(P,(w+1)*sizeof(Tree));
		for(v=1;v<=w;v++)
			P[v]=Q[v];	
		}
		}
	}
}
w=1;
if(argv[w][1]=='c')
{
	if(argv[w][2]=='1'||argv[w][2]=='2')
	{
		for(w=1;w<argc-2;w++)
		{
		if(z=='X')
			z='O';
		else
			z='X';
		n=verifica(t,'X');
		n=verifica(t,'O');
		T=insert(T,t,n,z,0,0);
		if(argv[w][2]=='1')
		{
			print_tree(T,T->n,g);
		}
		if(argv[w][2]=='2')
		{
			T_F(T,T->z);
			print_T_F(T,T->n,g);
		}
		}
		free_tree(T);
		for(m=1;m<=3;m++)
			free(t[m]);
		free(t);
	}
	else
		{
		tree_minimax(T,p,1);
		print_tree_minimax(T,0,g);
		}
}
free(o);
fclose(f);
fclose(g);
return 0;	
}
