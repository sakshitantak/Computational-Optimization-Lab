#include <iostream>
using namespace std;

void printProblem(int M[10][10],int n,int m, int Z[10], int prb, char ob, char v);

int main()
{

	int m,n,Z[10],W[10],prb, AT[5][5];
	int M[10][10], Md[10][10];
	char str[4][30]={"","CONSTRAINTS","VARIABLES",""};


	cout<<"\nENTER \n\t1->MAXIMIZATION\n\t2->MINIMIZATION\n-> ";			//prb stores the type of problem
	cin>>prb;

	//input
	cout<<"\n\tENTER NUMBER OF VARIABLES -> ";
	cin>>n;
	cout<<"\n\tENTER NUMBER OF CONSTRAINTS -> ";
	cin>>m;

	//1st row of analysis table
	AT[0][0]=m;			//0th col : no.of constraints
	AT[0][1]=n;			//1st col : no.of decision variables
	AT[0][2]=prb;		//2nd col : the problem

	//2nd row of analysis table
	AT[1][0]=n;
	AT[1][1]=m;
	if(AT[0][2]==1)
		AT[1][2]=2;
	else
		AT[1][2]=1;


	//input objective function and store it in Z array
	cout<<"\nENTER THE OBJECTIVE FUNCTION Z ->";
	for(int i=0; i<n; i++)
	{
		cout<<"\nCOEFFICIENT X#"<<i+1<<"->";
		cin>>Z[i];
	}

	//initialize matrix with 0
	for(int i=0; i<m; i++)
		for(int j=0; j<(n+m+1); j++)
			M[i][j]=0;

	//input constraints and store it in matrix M
	for(int i=0; i<m; i++)
	{
		cout<<"\nENTER COEFFICIENTS FOR CONSTRAINT "<<i+1<< " : ";
		for(int j=0; j<n; j++)
		{
			cout<<"\n\tCOEFFICIENT X#"<<j+1<<"->";
			cin>>M[i][j];
		}
		cout<<"\n\tENTER RHS OF CONSTRAINT "<<i+1<<"->";
		cin>>M[i][n];					//last column of matrix stores the solution
	}

	//printing the primal problem
	cout<<"\nPRIMAL PROBLEM->\n";
	printProblem(M,AT[0][1],AT[0][0],Z,AT[0][2],'Z','x');
	
	//analysis table
	cout<<endl<<endl;
	/*
	cout<<"SOLUTION->\n";
	for(int i=0; i<4; i++)
	{
		cout<<str[i]<<"\t";
	}
	for(int i=0; i<2; i++)
	{
		cout<<endl;
		if(i==0)
			cout<<"PRIMAL";
		else
			cout<<"DUAL";
		for(int j=0; j<2; j++)
		{
			cout<<"\t\t"<<AT[i][j];
		}
		if(AT[i][2]==1)
			cout<<"\t\tMax";
		else if(AT[i][2]==2)
			cout<<"\t\tMin";
	}
	*/
	//assigning W
	for(int i=0; i<AT[1][1]; i++)
	{
		W[i]=M[i][n];
	}

	//assigning new constraints
	for(int i=0; i<AT[1][0]; i++)
	{
		for(int j=0; j<AT[1][1]; j++)
		{
			Md[i][j]=M[j][i];
		}
		Md[i][AT[1][1]]=Z[i];
	}

	//printing the dual problem
		cout<<"THE DUAL PROBLEM->\n";
		printProblem(Md,AT[1][1],AT[1][0],W,AT[1][2],'W','y');
		

	return 0;
}

void printProblem(int M[10][10],int n,int m, int Z[10], int prb, char ob, char v)
{
	if(prb==1)
		cout<<"\nMax \t"<<ob<<" = ";
	else if(prb==2)
		cout<<"\nMin \t"<<ob<<" = ";

	for(int i=0; i<n; i++)
	{
		cout<<Z[i]<<v<<i+1;
		if(i==(n-1))
			cout<<"";
		else
			cout<<" + ";
	}

	cout<<"\nSubject to";
	for(int i=0; i<m; i++)
	{
		cout<<"\n\t";
		for(int j=0; j<n; j++)
		{
			cout<<M[i][j]<<v<<j+1;
			if(j==(n-1))
				cout<<"";
			else
				cout<<" + ";
		}
		if(prb==1)
			cout<<" <= ";
		else if(prb==2)
			cout<<" >= ";
		cout<<M[i][n];
	}

}
