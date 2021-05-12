/*
 C program mini project - Sudoku solver and game
    By 1MV19IS044 Pratham Pai BM
       1MV19IS047 Ravi Prakash Hegde
       1MV19IS011 Bharath GT
       1MV19IS012 Bharath TR
    Data Structures used: Array (2 dimensional) and Linked-Stacks
*/
#include <stdio.h>
//#include <conio.h> //Only for turbo c++
#include <time.h>
#include <stdlib.h> //Since using Linked-stack

#define N 9// N is the size of the N*N 2D matrix
#define p(x) printf(x);

struct node
{
    int data;
    struct node *link;
};

struct node *head_row=NULL;
struct node *head_col=NULL;
struct node *head_num=NULL;

struct node* create_node(int ele)
{
    struct node *temp;
    temp=malloc(sizeof(struct node));
    temp->data=ele;
    temp->link=NULL;
    return temp;
}

void push(int value,int n)
{
    struct node *temp;
    temp=create_node(value);
    if(n==1) // push for row linked-stack
    {
        if(head_row==NULL)
        {
            head_row=temp;
            return;
        }
        temp->link=head_row;
        head_row=temp;
    }
    else if(n==2) // push for col linked-stack
    {
        if(head_col==NULL)
        {
            head_col=temp;
            return;
        }
        temp->link=head_col;
        head_col=temp;
    }
    else if(n==3) // push for num linked-stack
    {
        if(head_num==NULL)
        {
            head_num=temp;
            return;
        }
        temp->link=head_num;
        head_num=temp;
    }
}

int pop(int n)
{
    struct node *temp;
    int value;
    if(n==1) // pop for row linked-stack
    {
        if(head_row==NULL)
        {
            return 0;
        }
        temp=head_row;
        head_row=head_row->link;
        value=temp->data;
        free(temp);
        return value;
    }
    else if(n==2) //pop for col linked-stack
    {
        if(head_col==NULL)
        {
            return 0;
        }
        temp=head_col;
        head_col=head_col->link;
        value=temp->data;
        free(temp);
        return value;
    }
    else if(n==3) //pop for num linked-stack
    {
        if(head_num==NULL)
        {
            return 0;
        }
        temp=head_num;
        head_num=head_num->link;
        value=temp->data;
        free(temp);
        return value;
    }
    return 0;
}

void line()
{
    p("---------------------\n");
}

void load_screen()
{
    int i;
    //clrscr();
    p("Loading");
    for(i=0;i<3;i++)
    {
        printf(".");
        sleep(1);//Delay
    }
    p("\n");
    //clrscr();
}

// Function to print the final solution
void print(int arr[N][N])
{
    int i,j;
    line();
    for(i=0;i<N;i++)
    {
        if(i==3 || i==6)
            p("\n");
        for(j=0;j<N;j++)
        {
            if(j==3 || j==6)
                p("\t");
            printf("%d ",arr[i][j]);
        }
        p("\n");
    }
}

// Checks whether it will be legal
// to assign the number to the given row, col block
int isSafe(int mat[N][N],int row,int col,int num)
{
    int x,i,j,subRow,subCol;

    // Checking the corresponding row
    for(x=0;x<=8;x++)//index 0-8
        if(mat[row][x]==num)
            return 0;

    // Checking the corresponding column
    for(x=0;x<=8;x++)//index 0-8
        if(mat[x][col]==num)
            return 0;

    // Checking the corresponding 3*3 sub-matrix
    subRow=row-row%3;
    subCol=col-col%3;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            if(mat[i+subRow][j+subCol]==num)
                return 0;
    return 1;
}

int solve(int mat[N][N],int row,int col)
{
    int num;
    // If final position in matrix is reached
    // Which is when row=8 and column=9
    // Condition for exiting the solve
    if(row==N-1&&col==N)
        return 1;
    // If last column is reached(in any row other than final row)
    // Then move onto the next row
    if(col==N)
    {
        row++;
        col=0;
    }
    // If the current position already contains a value>0
    // we move onto the next column
    if(mat[row][col]>0)
        return solve(mat,row,col+1);
    for(num=1;num<=N;num++)
    {
	// check if the number(1-9) is valid
	// in the current row, column space
        if(isSafe(mat,row,col,num)==1)
        {
            // if valid then assign that number in the current row,col
            mat[row][col]=num;
            // move onto the next block
            if(solve(mat,row,col+1)==1)
                return 1;
        }
	// Removing the number since our assumption was wrong
	// and moving onto the next possibility value of number
        mat[row][col] = 0;
    }
    return 0;
}

int playMode(int arr[N][N],int ans[N][N])
{
    int ch,row,col,num,r,c,n,time_int;
    double time_spent = 0.0;
    clock_t begin = clock();//Clock count begin
    while(1)
    {
        //clrscr();
        p("------Play mode------\n");
        print(arr);
        line();
        p("\nEnter the choice: 1)Input  2)Check  3)Get-answer  4)Undo  5)Exit\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: p("\nEnter the row, col, and number\n");
                    scanf("%d%d%d",&row,&col,&num);
                    push(row,1); //1 for row stack
                    push(col,2); //2 for column stack
                    push(arr[row-1][col-1],3); //3 for num stack
                    arr[row-1][col-1]=num;
                    break;

            case 2: p("\nEnter the row, col, and number\n");
                    scanf("%d%d%d",&row,&col,&num);
                    if(ans[row-1][col-1]==num)
                        printf("Success - The number is correct for this position\n");
                    else
                        printf("Failure - The number is wrong for this position\n");
                    p("Press enter to continue\n");
                    getch();
                    break;

            case 3: p("Enter which row and column:");
                    scanf("%d%d",&row,&col);
                    printf("The number in this position must be %d\n",ans[row-1][col-1]);
                    p("Press enter to continue\n");
                    getch();
                    break;

            case 4: r=pop(1); //1 for row stack
                    c=pop(2); //2 for col stack
                    n=pop(3); //3 for num stack
                    if(r==0 || c==0)
                    {
                        p("No undo's left\nPress enter to continue\n");
                        getch();
                        break;
                    }
                    arr[r-1][c-1]=n;
                    break;

            case 5: break;

            default: p("Wrong choice,try again\n");
                     getch();
        }
        if(ch==5)//To end the clock count down
        {
            clock_t end = clock();
            time_spent += (double)(end-begin)/CLOCKS_PER_SEC;
            time_int=time_spent;
            printf("\nTime taken(in Play mode): %d seconds\n\n",time_int);
            //Amount of time spent in play mode
            return 0;
        }
    }
}

int main()
{
    int i,j,ch,x,y,ans[N][N];
    //int mat[N][N];
    // 0 is for initial empty cells

    //To set input before runtime, during initialization:
    int mat[N][N] =  { { 4, 0, 0,   3, 0, 7,   0, 0, 6 },
                       { 0, 3, 0,   4, 0, 5,   0, 0, 0 },
                       { 0, 0, 0,   9, 0, 0,   0, 4, 0 },

                       { 2, 8, 0,   0, 0, 0,   4, 0, 0 },
                       { 0, 0, 5,   0, 0, 0,   0, 6, 0 },
                       { 3, 4, 9,   0, 0, 0,   7, 0, 0 },

                       { 9, 7, 0,   8, 2, 0,   0, 0, 0 },
                       { 0, 0, 0,   0, 0, 0,   0, 7, 4 },
                       { 6, 2, 0,   0, 0, 0,   9, 8, 0 } };

    //clrscr();
    p("----SUDOKU puzzle----\n");
    /*
    // To give the input during runtime:
    printf("Enter the numbers as a %d*%d matrix\n",N,N);
    printf("(Enter zeros(0) for initial empty slots)\n");
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            scanf("%d",&mat[i][j]);
	printf("Input taken successfully, press enter to continue\n");
	getch();
    */

    //Play mode - we can solve the sudoku as a game
    //Solution mode - directly prints final solution
    p("Main menu:\n")
    p("1)Play mode  2)Solution mode  3)Instructions  4)Exit\nEnter the choice: ");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1: load_screen();
                //array copy:
                for(x=0;x<N;x++)
                    for(y=0;y<N;y++)
                        ans[x][y]=mat[x][y];

                if(solve(ans,0,0)!=1)//row=0,col=0
                     printf("No solution exists for the given sudoku\n");
                else
                     playMode(mat,ans);
                break;
        case 2: load_screen();
                if(solve(mat,0,0)==1)//row=0,col=0
                {
                    p("The Solution is\n");
                    print(mat);
                }
                else
                    p("No solution exists");
                line();
                break;
        case 3: //clrscr();
                p("Instructions:\n\n")
                p("Choosing solution mode, prints the solved solution(if exists) of the sudoku\n");
                p("Choosing play mode, brings up a game type environment to solve the sudoku by yourself\n\n");
                p("Play mode gives 5 choices:\n");
                p("1)Input: input any number in any cell, by entering the row, column and the number\n");
                p("2)Check: ask whether a particular number is correct for a given cell, by entering row and column\n");
                p("3)Get-answer: directly get the correct number in a particular cell by entering the row and column\n");
                p("4)Undo: can perform undo unlimited number of times until it comes back to initial data\n");
                p("5)Exit: exit the play mode\n");
                break;
        case 4: exit(0);
                break;
        default: p("Wrong choice,try again\n");
    }
    p("\nPress enter to continue\n");
    getch();
    main();
    return 0;
}
//End of program---------------------------------------------

/*
example 1:   { { 0, 0, 0,   0, 4, 0,   3, 0, 5 },
		       { 7, 0, 3,   8, 0, 6,   1, 0, 0 },
		       { 2, 0, 0,   0, 0, 0,   0, 6, 0 },

		       { 6, 0, 5,   0, 0, 7,   2, 0, 0 },
		       { 4, 0, 8,   0, 0, 0,   9, 0, 6 },
		       { 0, 0, 9,   3, 0, 0,   4, 0, 7 },

		       { 0, 8, 0,   0, 0, 0,   0, 0, 4 },
		       { 0, 0, 1,   8, 0, 5,   7, 0, 8 },
		       { 9, 0, 7,   0, 8, 0,   0, 0, 0 } };

example 2:   { { 4, 0, 0,   0, 3, 2,   0, 0, 8 },
		       { 0, 7, 3,   0, 6, 1,   0, 0, 0 },
		       { 0, 0, 0,   0, 0, 0,   3, 7, 0 },

		       { 0, 9, 2,   1, 0, 0,   0, 0, 0 },
		       { 0, 4, 0,   0, 0, 0,   5, 0, 0 },
		       { 0, 0, 0,   2, 0, 9,   0, 8, 0 },

		       { 0, 0, 0,   0, 0, 5,   7, 0, 0 },
		       { 5, 0, 4,   0, 0, 0,   0, 0, 2 },
		       { 0, 0, 1,   0, 0, 0,   4, 0, 0 } };
special-
example 3:   { { 0, 0, 0,   0, 0, 0,   0, 0, 0 },
		       { 0, 0, 0,   0, 0, 0,   0, 0, 0 },
		       { 0, 0, 0,   0, 0, 0,   0, 0, 0 },

		       { 0, 0, 0,   0, 0, 0,   0, 0, 0 },
		       { 0, 0, 0,   0, 0, 0,   0, 0, 0 },
		       { 0, 0, 0,   0, 0, 0,   0, 0, 0 },

		       { 0, 0, 0,   0, 0, 0,   0, 0, 0 },
		       { 0, 0, 0,   0, 0, 0,   0, 0, 0 },
		       { 0, 0, 0,   0, 0, 0,   0, 0, 0 } };
*/
