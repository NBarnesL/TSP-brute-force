#include <iostream>
#include <cmath>


using namespace std;

int array[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; //used to generate permutations
double cities[20][20]={0}; //initial declaration of cities and allocate memory. Any higher than this would be too resource intensive
double smallest=999999; //used to compare each of the paths
bool debug_flag=0;

void permute(int k,int& size, int* order);
void filterArray(int& size,int* order);
void swap(int x, int y);
void calculatecost(int* order, int& size);


/*
Main:

Accepts input from the user for the number of cities to be calculated, as well as their locations in x and y coordinates.
An input of 0 activates a debug mode which displays all possible routes and their cost.
An input of 1 only has one possible path, so it calls the only possible path: {City 1}.
An input greater than 6 in debug mode will display a warning tells the user that processing time will be drastically increased
due to the output of all possible routes. The distance: sqrt((x2-x1)^2+(y2-y1)^2) is calculated between each city, stored
in a two dimensional array, cities[x][y]. Finally, using a recursive function permute(), all routes are calculated, with the one with the lowest
cost between cities outputted at the end of the program.


*/




int main()
{

   double location_x[20];
   double location_y[20];


   int order[21];

   int num_cities;
   int a; //number of cities
   int i; int j;//counters


   Prompt:
   cout<<"Please enter the number of cities to be calculated. (Max 10)"<<endl; //Prompt user to enter number of cities to calculate.
   cin>>num_cities;





   a = num_cities;//makes it easier to call

   if (num_cities == 0) //Activates a debug prompt, which shows all possible routes and the calculations used to calculate their costs.
   {
      if(debug_flag==1)
      {
         cout<<"debug inactive"<<endl<<endl;
         debug_flag=0;
         goto Prompt;

      }

      debug_flag=1;
      cout<<"debug active"<<endl<<endl;

      goto Prompt;
   }

   if (num_cities == 1) //Case: 1
   {
      cout<<"Only one possible path exists\n\n1\n";
      goto Prompt;
   }

   if (num_cities>6)
   {
      if (num_cities>10){
         cout<<"num cities greater than 10"<<endl<<endl;

      }

      if (debug_flag==1){ //Disclaimer for the amount of time it can take to output large quantities of data.
         cout<<"For general purposes, this program can handle up to ten cities.\n\nHowever, during debugging, as the number of cities increases,"<<
         "the amount of time it will take will be much\nlonger in order to display each possible combination.\n\n\n"<<
         "Please take care not to use too many cities when using the debugging function.\n\n";


      }


   }


   for (i=0; i<a; i++) //accept coordinates from user
   {
      cout<<"Please enter the coordinates of city "<<i+1<<": \n x: ";
      cin>>location_x[i];
      cout<<" y: ";
      cin>> location_y[i];


   }
   if (debug_flag==1)
   {
      cout<<endl<<endl<<"[Debug] The following is a list of coordinates of the cities you have provided"<<endl;

      for (i=0; i<a; i++)
      {

         cout<<"City "<<i+1<<": ("<<location_x[i]<<", "<<location_y[i]<<") "<<endl;


      }

      cout<<endl<<endl<<"[Debug] What follows will be a calculation of the distances between each city."<<endl;

   }

   ///Use the distance formula to calculate the distances between each city
   for (i=0; i<a; i++)
   {

      for (j=0; j<a; j++)
      {
         if (i!=j)
         {


            cities[i][j]= sqrt(pow(location_y[j]-location_y[i], 2) + pow(location_x[j]-location_x[i],2) );
            if (debug_flag==1)
               cout<<cities[i][j]<<endl;

         }
         else
            cities[i][j]=0;

      }
   }

   if (debug_flag==1)
   {
      cout<<endl<<endl<<"[Debug] The following is a a matrix of distances between the cities you have provided."<<endl;
      for (i=0; i<a; i++)
      {
         cout<<endl;
         for (j=0; j<a; j++)
         {
            cout<<cities[i][j]<<" ";
         }
      }
   }
   ///compare each of the distances and provide an optimal route

   ///city 1 is the starting point

   ///given a list of distances between each city, provide an optimal path
   ///*each city must be visited only once except to return to the original location
   ///*complete brute force. calculate all possible routes and choose the best one
   ///Starting with city 1

   ///recursive function that generates permutations**************
   if (debug_flag==1)
      cout<<endl<<endl<<"Debug: A recursive function is used to generate permutations based on the number of cities provided"<<endl;

   permute(a,a,order);


   cout<<endl<<endl<<"The following is the proposed order"<<endl;
   for (i=0; i<a; i++)
   {
      cout<< order[i]<<" ";
   }
   cout<<1;


   //end of program
}


/*
swap:

A swap function is implemented to generate permutations in the permute() function.
The array value in an x position is swapped with a value in the y position.

*/

void swap(int x, int y){ //Swap function
   int temp = array[x];
   array[x]=array[y];
   array[y]=temp;

   return;
}

/*
filterArray:

This function takes the possible route generated by permute() and
determines whether to calculate the cost based on the value in the [0]
position. If 1, filterArray calls a function that calculates the cost of the route.

*/


void filterArray(int& size, int* order){ //Only calculates cities with 1 as its starting position.

   if (array[0]==1)
   {
      calculatecost(order,size);
      if(debug_flag==1)
      cout<<"-------------------------------------------------";
   }




   return;
}

/*
permute:

permute() is a recursive function generates permutations from an array order,
calling a swap function to swap positions of values in the array.

*/

void permute(int k,int& size, int* order){ //Recursive function that calls itself enough to calculate all possible routes (n-1)!
   int i;
   if (k==0)
      filterArray(size,order);
   else{
      for (i=k-1;i>=0;i--){
         swap(i,k-1);
         permute(k-1,size,order);
         swap(i,k-1);
      }
   }

   return;
}

/*
calculatecost:

This function calculates the cost for an inputted route array[]. The cost between cities are called for each
position in the array, and the total cost is the sum of each position called, in addition to the distance
between the final position and position [0]. The cost is compared to the smallest cost calculated - its stored
if the cost is smaller, discarded if not. The order of the current optimal array is stored in order[n];

*/


void calculatecost(int* order, int& size){ //Calculates the cost of each possible route.
   int k;
   double cost=0;
   int temporder[20];
   int j; int i;



   for (k=0;k<size; k++)
   {
      temporder[k]=array[k];

   }
   if (debug_flag==1){
      cout<<endl<<"The following is an order "<<": ";


      for (k=0;k<size; k++)
      {
         cout<<temporder[k]<<" ";

      }
      cout<<1;
      cout<<endl;
   }
   for(k=0;k<size-1;k++)
   {

      cost+=cities[temporder[k]-1][temporder[k+1]-1];
      if (debug_flag==1)
         cout<<cities[temporder[k]-1][temporder[k+1]-1]<<" + ";


   }
   if (debug_flag==1){
      cout<<cities[array[size-1]-1][0]<<endl;
   }
   cost+=cities[array[size-1]-1][0];


   if (cost<smallest)
   {
      smallest=cost;
      for (k=0;k<size; k++)
      {
         order[k]=temporder[k];

      }
   }


   if (debug_flag==1){
      cout<<endl<<"And its cost: "<<cost;
      cout<<endl;
   }
}
