// FinalProject.cpp
// Brandon Pereira and Perves Muhammed
// This program executes the "Travelling Salesman Problem" which is to find the overall shortest distance travelled while going to each city once and returning to the home city.

#include <iostream> // Allows for the program to get information from the user and also print information back onto the screen.
#include <string>   // Allows the program to get the information from the text file which contains all cities and their values.
#include <vector>   // Allows the program to store the all the x and y values, distances, and city names.
#include <cmath>    // Allows the program to execute the distance formula to find the distance between two pairs of cities.
#include <fstream>  // Allows the program to find, open, and print the files information out to the user.
#include <iomanip>  // Allows the grid to be made that provides the user useful information in a clean sleek way.
#include <cctype>
#include <sstream>


using namespace std;

int main()
{
    ifstream infile("data.txt");// Allows the program to find and open the file containing the values and the cities names, also bypassing user error and stating the file name without user input.
    ofstream outfile("usercity.txt"); // Allows the program to put the new city in with the older city's in a text file to later be easily be stored in a vector.
    vector<string> CityName;    // Vector that stores all the city names.
    vector<int> XCoor;          // Vector that stores all of the cities x coordinates (Manipulated).
    vector<int> YCoor;          // Vector that stored all of the cities y coordinates (Manipulated).
    while (infile.good())       // Looping the action of opening the file and gathering all the useful data inside.
    {
        string City;            // Variable to be used as a place holder of each city's name.
        infile>>City;           // Gathering the word in this case the city's name.
        CityName.push_back(City); // Storing the city name in the respected vector.
        int Y;                  // Variable to be used as a place holder of the y coordinate in the file.
        infile>>Y;              // Gathering the y coordinate from the file.
        YCoor.push_back(Y);     // Storing the y coordinate in the respected vector.
        int X;                  // Variable to be used as a place holder of the x coordinate in the file.
        infile>>X;              // Gathering the x coordinate from the file.
        XCoor.push_back(X);     // Storing the x coordinate in the respected vector.
    }                           // End of the loop
    infile.close();             // Closing the file for fear of memory leak.
    int lenX=XCoor.size()-1;      // Finding the length of all the elements in the x coordinate vector.
    int lenY=YCoor.size()-1;      // Finding the length of all the elements in the y coordinate vector.
    int lenCity=CityName.size()-1;// Finding the length of all the elements in the city name vector.
    cout << endl;               // Spacing the title from the top of the console window making it look nice and easy to read.

    int UseryVal=34;             // Variable to be a place holder for the user's city y value.
    int UserxVal=-1;             // Variable to be a place holder for the user's city x value.
    string UserCityName;        // Variable to be used as a place holder for the user's city name.
    int UserCityNameLen=0;
    string UserxValStr, UseryValStr;
    char UserxValChar, UseryValChar;
    int lenStrx, lenStry=0;
    bool numericx, numericy=0;

    while (UserCityNameLen<1||UserCityNameLen>10)
    {
        cout << "Enter Your City Name Below! (Equal to or less than 10 characters)" << endl; // Allowing the user to input their city name.
        getline(cin,UserCityName);  // Getting the user's city name.
        UserCityNameLen=UserCityName.length();
    }
    while (numericx!=1 || UserxVal<1 || UserxVal>68)// If condition to only allow the user to make their city have a maximum of 70 as a x value
    {
        cout << "Enter Your City's X Value! (Less than 69)" << endl;  // Allowing the user to input their city's x value.
        getline(cin, UserxValStr);                                   // Getting the user x value.
        lenStrx=UserxValStr.length();

        for (int i=0; i<lenStrx; i++)
            UserxValChar=UserxValStr[i];
        if (isalpha(UserxValChar))
        {
            numericx=0;
            cout << "Please enter a numeric value" << endl;
        }
        else
            numericx=1;

        istringstream convert(UserxValStr);
        convert >> UserxVal;
            //UserxVal=UserxValStr;
    }

   while (numericy!=1 || UseryVal<1 || UseryVal>32)        // while loop to keep looping untill a number less or equal to 32 is met.
    {
        cout << "Enter Your City's Y Value! (Less than 32)" << endl;  // Allowing the user to imput their city's y value.
        getline(cin, UseryValStr);                                   // Getting the user x value.
        lenStry=UseryValStr.length();
        for (int i=0; i<lenStry; i++)
            UseryValChar=UseryValStr[i];
        if (isalpha(UseryValChar))
        {
            numericy=0;
            cout << "Please enter a numeric value" << endl;
        }
        else
            numericy=1;          // Getting the user's y value.
            istringstream convert(UseryValStr);
            convert >> UseryVal;
    }
    cout << "If your city lies on the same Y-Value as another city it will be printed on the next available line!" <<endl;
    int sumYVal=0;              // Variable to be used to find the text file's city actual y value
    int spot=0;                 // Variable to find out where the user's city cooresponds to the neighbor cities.
    for (int i=0; i<lenY; i++)  // looping condition to find where the user's y value compares with the other city's y value.
    {
        int val=YCoor[i];       // Variable to find each element in the file's y vlaues.
        sumYVal+=val;           // Adding all the file's y values to get the correct y value.
        if (sumYVal>UseryVal)
        {
            sumYVal=sumYVal-val;// subtracts one new value to have the correct sum.
            break;              // Breaks the loop.
        }
        else if (sumYVal<=UseryVal) // If condition to see if the overall y value is less than the user's y value to then keep adding one to find the position at which the overall is greater.
            spot++;             // Adding one to spot to find the y value of the city prior.
    }
    // adding one to spot to find where the user's city would be positioned on the graph
    //cout << spot << "spot"<<endl;
    //cout << sumYVal << "sum" <<endl;
    int dataCoor=UseryVal-sumYVal; // Making a variable to get the user's manipulated y value
    int upper=YCoor[spot]-dataCoor;// making a variable to get the manipulated neighbor city's y value compared to the user's city.
    int fileCoor=0;             // Making a variable to find how many times it goes through the loop.
    while(fileCoor<=12)         // Looping condition to reprint all of the citynames and their coordinates with the addition of a user city.
    {
        if (fileCoor==spot)     // if condition if the loop finally hits the pposition of where the city should be.
        {
            outfile<<UserCityName<<endl; // Prints out the user's city name.
            outfile<<dataCoor<<endl;     // Prints out the user's manipulated y coordinate.
            outfile<<UserxVal<<endl;     // Prints out the user's x value.
            outfile<<CityName[fileCoor]<<endl; // Prints the next neighbor's city name.
            outfile<<upper<<endl;              // Prints the neighbors manipulated y value.
            outfile<<XCoor[fileCoor]<<endl;    // Prints the neighbors x value.
        }
        else                            // Condition if the variable passes the user's city and neighbor too.
        {
            outfile<<CityName[fileCoor]<<endl;  // Prints out the city name.
            outfile<<YCoor[fileCoor]<<endl;     // prints out the city y value.
            outfile<<XCoor[fileCoor]<<endl;     // Prints out the city x value.
        }
        fileCoor++;             // Adding one to the variable to get to the next city.
    }

    CityName.clear();           // Clears all the elements in the vector.
    YCoor.clear();              // Clears all the elements in the vector.
    XCoor.clear();              // Clears all the elements in the vecotr.
    ifstream newFile("usercity.txt");// Allows the program to find and open the file containing the values and the cities names, also bypassing user error and stating the file name without user input.
    while (newFile.good())       // Looping the action of opening the file and gathering all the useful data inside.
    {
        string City;            // Variable to be used as a place holder of each city's name.
        newFile>>City;           // Gathering the word in this case the city's name.
        CityName.push_back(City); // Storing the city name in the respected vector.
        int Y;                  // Variable to be used as a place holder of the y coordinate in the file.
        newFile>>Y;              // Gathering the y coordinate from the file.
        YCoor.push_back(Y);     // Storing the y coordinate in the respected vector.
        int X;                  // Variable to be used as a place holder of the x coordinate in the file.
        newFile>>X;              // Gathering the x coordinate from the file.
        XCoor.push_back(X);     // Storing the x coordinate in the respected vector.
    }                           // End of the loop
    newFile.close();             // Closing the file for fear of memory leak.
    lenX=0;                   // Making the length 0 again.
    lenY=0;                   // Making the length 0 again.
    lenCity=0;                // Making the length 0 again.
    lenX=XCoor.size()-1;      // Finding the length of all the elements in the x coordinate vector.
    lenY=YCoor.size()-1;      // Finding the length of all the elements in the y coordinate vector.
    lenCity=CityName.size()-1;// Finding the length of all the elements in the city name vector.
    int maxCities=13;
    cout << "  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------"<<endl;
    cout << endl;               // Spacing the title with the distance help
    cout << "Each one unit represents 400km in distance!" << endl; // Telling the user that the numbers seen in the grid are reduced and should be known that are actually greater

    int num=0;                          // Variable to be used as a tool for determining what element to choose in each vector.
    for (int i=0; i<lenCity; i++)     // Looping condition to find all of the city names, x and y values, while printing them out to the screen as if on a graph.
    {
        for (int j=0; j<YCoor[num]; j++)// Nested loop to loop the y coordinate using a new line each time.
            cout<<endl;            // Printing out a new line.
        for (int k=0; k<XCoor[num]; k++)// Another nested loop to loop the x coordinate using a space each time.
            cout << " ";                // Printing a space.
        cout << "* "<<CityName[i]<<endl;// Printing the spot on the graph and the city name that corresponds to it.
        num++;                          // Adding one to 'num' to find the next element in all three vectors.
    }
    cout << endl;                       // Separating the graph from the grid of all possible distances from any pair of cities.
    cout << endl;                       // Separating the graph from the grid of all possible distances from any pair of cities.
    cout << "  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------"<<endl; // Telling the user that the next section is all the possible distances between any pair of cities.
    cout << endl;                       // Separating the graph from the grid of all possible distances from any pair of cities.
    cout << endl;                       // Separating the graph from the grid of all possible distances from any pair of cities.
    vector<int> RowMin;                 // Creating a vector that will store all of the possible distances from any pair of cities.

    for (int i=0; i<=maxCities; i++)           // Looping condition to ultimately make a 13 by 13 grid of distance
        cout << setw(5) << i;           // Listing numbers between 0 and 12 referring to as cities.
    cout << endl;                       // Creating a new line to make the grid look better.
    cout << endl;                       // Creating a new line to make the grid look better.

    for (int k=0; k<=maxCities; k++)           // Looping condition to get a city as one of the pairs.
    {
        cout << k;                      // Listing the city that is being used.
        int counter=0;                  // Variable to count the number of values in each row.
        for (int i=0; i<=maxCities; i++)       // Looping condition to find every other city in respect to the other city selected, and finding the distance between them.
        {
            double dist=0;              // Variable to be used as a place holder of the distance between the two cities.
            int trueYval=0;             // Making a variable to add each y value to get the overall y value for the next city because of the manipulated file values.
            for (int i=0; i<=k; i++)    // Looping condition to get the correct y value of the city being used.
            {
                trueYval+=YCoor[i];     // Adding the previous city's y value to get to the city wanted, this get the correct y value for the city being selected.
            }
            int citiesYval=0;           // Stating the other city's absolute y value.
            for (int s=0; s<=i; s++)    // Looping condition to get the correct y values of the city being used.
            {
                citiesYval+=YCoor[s];   // Adding the previous city's y value to get to the city wanted, this gets the correct y value for the city being selected.
            }
            dist=sqrt(pow(XCoor[k]-XCoor[i],2)+pow(trueYval-citiesYval,2)); // Finding the distance between the two selected cities.
            dist=ceil(dist);            // Rounding up the double to find a integer as a distance.
            RowMin.push_back(dist);     // Putting the distances into their respected vector.
            if (counter<=maxCities)            // Finding if the distances reached the end of the table, if not keep going.
                cout << setw(5) << dist;// Printing out the next distance on the grid's row.
            else                        //if they did reach the end then it will create a new line and start from 0 again
            {
                counter=0;              // Setting the variable to zero again to allow it to be able to hold 13 numbers like before.
                cout << endl;           // Making a new line on the grid.
            }

            counter++;                  // Adding another one to the variable telling it that their was another distance entered onto the grid.
        }
        cout << endl;                   // Making a line just to make the grid look presentable.
        cout << endl;                   // Making a line just to make the grid look presentable.
    }
    cout << "  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------"<<endl; // Telling the user that the next section is the route of which travelling the least distance.
    cout << endl;                       // Making a new line to start the new section.
    cout << endl;                       // Making a new line to start the new section.

    int lenRow=RowMin.size()-1;         // Finding the length of the elements in the vector.
    int sum=0;                          // Variable to be used as a place holder of the final accumulated distance travelled.

    int maximum=0;                      // Variable to be used as a place holder of the greatest value in the row.
    int position=0;                     // Variable to find the city in which this value occurs.
    for (int i=0; i<=13; i++)           // Looping condition to find each number in the row.
    {
        int big=RowMin[i];              // Creating a variable that has the value of a distance in the row.
        if(big>=maximum&&big!=0)        // If condition to see if there is any other number in the row that is greater that the greatest discovered so far.
        {
            maximum=big;                // Once one is found then set the new amount needed to beat in order to be considered the biggest value.
            position=i;                 // Finding the city that has the greatest distance.
        }
    }
    int R1=0;                           // Variable that tells the program that this starting city is the beginning and that later on no other city can come back until all other cities have been met with once.
    int lowest1=RowMin[position];       // Setting a new variable to the highest value.
    int counter1=0;                     // Variable that is a place holder of the city name that has the lowest value.
    for (int i=0; i<=13; i++)           // Looping condition that finds all the cities in the row.
    {
        int num=RowMin[i];              // Making a variable equal to one of the row's values
        if (num<=lowest1&&num!=0)       // If condition to see if the new variable is lower that the previous one discovered and it cant be zero. This cancels cities going to themselves.
        {
            lowest1=num;                // Once found a city with a lower distance then re-evaluate the requirement to become a lower distance possible.
            counter1=i;                 // Finding the city that had the lowest distance.
        }
    }
    cout << CityName[0] << " -> " << CityName[counter1] << endl; // Telling the user the route of which is the shortest distance able to travel.
    sum+=lowest1;                       // Adding the lowest distance to the 'sum' variable.

    int maximum2=0;
    int position2=0;
    for (int i=counter1*14; i<=counter1*14+13; i++) // Finding the next row start and finding the row end by using the previous lowest city and multiplying it by 13 to get the row, then adding 12 to find the upper bound.
    {
        int big2=RowMin[i];
        if(big2>=maximum2&&big2!=0)
        {
            maximum2=big2;
            position2=i;
        }
    }
    int counter2=0;
    int lowest2=RowMin[position2];

    for (int i=counter1*14; i<=counter1*14+13; i++) // Finding the row start and finding the row end by using the previous lowest city and multiplying it by 13 to get the row, then adding 12 to find the upper bound.
    {
        int num=RowMin[i];
        if (num<=lowest2&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]) // Condition that evaluates if the lowest distance found was already found before. (Not going back to a city already went to)
            {
                lowest2=num;
                counter2=i%14;
            }
        }
    }
    cout << CityName[counter1] << " -> " << CityName[counter2] << endl;
    sum+=lowest2;

    // THE REST OF THE CODE IS THE EXACT SAME AND IS JUST TRYING TO FIND THE NEXT LOWEST CITY DISTANCE WHILE ADDING THE DISTANCES TO CALCULATE THE OVERALL DISTANCE TRAVELLED.

    int maximum3=0;
    int position3=0;
    for (int i=counter2*14; i<=counter2*14+13; i++)
    {
        int big3=RowMin[i];
        if(big3>=maximum3&&big3!=0)
        {
            maximum3=big3;
            position3=i;
        }
    }
    int counter3=0;
    int lowest3=RowMin[position3];
    // finding the next set of values to choose from
    for (int i=counter2*14; i<=counter2*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest3&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2])
            {
                lowest3=num;
                counter3=i%14;
            }
        }
    }
    cout << CityName[counter2] << " -> " << CityName[counter3] << endl;
    sum+=lowest3;

    int maximum4=0;
    int position4=0;
    for (int i=counter3*14; i<=counter3*14+13; i++)
    {
        int big4=RowMin[i];
        if(big4>=maximum4&&big4!=0)
        {
            maximum4=big4;
            position4=i;
        }
    }
    int counter4=0;
    int lowest4=RowMin[position4];
    // finding the next set of values to choose from
    for (int i=counter3*14; i<=counter3*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest4&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3])
            {
                lowest4=num;
                counter4=i%14;
            }
        }
    }
    cout << CityName[counter3] << " -> " << CityName[counter4] << endl;
    sum+=lowest4;

    int maximum5=0;
    int position5=0;
    for (int i=counter4*14; i<=counter4*14+13; i++)
    {
        int big5=RowMin[i];
        if(big5>=maximum5&&big5!=0)
        {
            maximum5=big5;
            position5=i;
        }
    }
    int counter5=0;
    int lowest5=RowMin[position5];
    // finding the next set of values to choose from
    for (int i=counter4*14; i<=counter4*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest5&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4])
            {
                lowest5=num;
                counter5=i%14;
            }
        }
    }
    cout << CityName[counter4] << " -> " << CityName[counter5] << endl;
    sum+=lowest5;


    int maximum6=0;
    int position6=0;
    for (int i=counter5*14; i<=counter5*14+13; i++)
    {
        int big6=RowMin[i];
        if(big6>=maximum6&&big6!=0)
        {
            maximum6=big6;
            position6=i;
        }
    }
    int counter6=0;
    int lowest6=RowMin[position6];
    // finding the next set of values to choose from
    for (int i=counter5*14; i<=counter5*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest6&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4]&&CityName[i%14]!=CityName[counter5])
            {
                lowest6=num;
                counter6=i%14;
            }
        }
    }
    cout << CityName[counter5] << " -> " << CityName[counter6] << endl;
    sum+=lowest6;

    int maximum7=0;
    int position7=0;
    for (int i=counter6*14; i<=counter6*14+13; i++)
    {
        int big7=RowMin[i];
        if(big7>=maximum7&&big7!=0)
        {
            maximum7=big7;
            position7=i;
        }
    }
    int counter7=0;
    int lowest7=RowMin[position7];
    // finding the next set of values to choose from
    for (int i=counter6*14; i<=counter6*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest7&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4]&&CityName[i%14]!=CityName[counter5]&&CityName[i%14]!=CityName[counter6])
            {
                lowest7=num;
                counter7=i%14;
            }
        }
    }
    cout << CityName[counter6] << " -> " << CityName[counter7] << endl;
    sum+=lowest7;

    int maximum8=0;
    int position8=0;
    for (int i=counter7*14; i<=counter7*14+13; i++)
    {
        int big8=RowMin[i];
        if(big8>=maximum8&&big8!=0)
        {
            maximum8=big8;
            position8=i;
        }
    }
    int counter8=0;
    int lowest8=RowMin[position8];
    // finding the next set of values to choose from
    for (int i=counter7*14; i<=counter7*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest8&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4]&&CityName[i%14]!=CityName[counter5]&&CityName[i%14]!=CityName[counter6]&&CityName[i%14]!=CityName[counter7])
            {
                lowest8=num;
                counter8=i%14;
            }
        }
    }
    cout << CityName[counter7] << " -> " << CityName[counter8] << endl;
    sum+=lowest8;

    int maximum9=0;
    int position9=0;
    for (int i=counter8*14; i<=counter8*14+13; i++)
    {
        int big9=RowMin[i];
        if(big9>=maximum9&&big9!=0)
        {
            maximum9=big9;
            position9=i;
        }
    }
    int counter9=0;
    int lowest9=RowMin[position9];
    // finding the next set of values to choose from
    for (int i=counter8*14; i<=counter8*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest9&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4]&&CityName[i%14]!=CityName[counter5]&&CityName[i%14]!=CityName[counter6]&&CityName[i%14]!=CityName[counter7]&&CityName[i%14]!=CityName[counter8])
            {
                lowest9=num;
                counter9=i%14;
            }
        }
    }
    cout << CityName[counter8] << " -> " << CityName[counter9] << endl;
    sum+=lowest9;

    int maximum10=0;
    int position10=0;
    for (int i=counter9*14; i<=counter9*14+13; i++)
    {
        int big10=RowMin[i];
        if(big10>=maximum10&&big10!=0)
        {
            maximum10=big10;
            position10=i;
        }
    }
    int counter10=0;
    int lowest10=RowMin[position10];
    // finding the next set of values to choose from
    for (int i=counter9*14; i<=counter9*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest10&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4]&&CityName[i%14]!=CityName[counter5]&&CityName[i%14]!=CityName[counter6]&&CityName[i%14]!=CityName[counter7]&&CityName[i%14]!=CityName[counter8]&&CityName[i%14]!=CityName[counter9])
            {
                lowest10=num;
                counter10=i%14;
            }
        }
    }
    cout << CityName[counter9] << " -> " << CityName[counter10] << endl;
    sum+=lowest10;

    int maximum11=0;
    int position11=0;
    for (int i=counter10*14; i<=counter10*14+13; i++)
    {
        int big11=RowMin[i];
        if(big11>=maximum11&&big11!=0)
        {
            maximum11=big11;
            position11=i;
        }
    }
    int counter11=0;
    int lowest11=RowMin[position11];
    // finding the next set of values to choose from
    for (int i=counter10*14; i<=counter10*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest11&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4]&&CityName[i%14]!=CityName[counter5]&&CityName[i%14]!=CityName[counter6]&&CityName[i%14]!=CityName[counter7]&&CityName[i%14]!=CityName[counter8]&&CityName[i%14]!=CityName[counter9]&& CityName[i%14]!=CityName[counter10])
            {
                lowest11=num;
                counter11=i%14;
            }
        }
    }
    cout << CityName[counter10] << " -> " << CityName[counter11] << endl;
    sum+=lowest11;

    int maximum12=0;
    int position12=0;
    for (int i=counter11*14; i<=counter11*14+13; i++)
    {
        int big12=RowMin[i];
        if(big12>=maximum12&&big12!=0)
        {
            maximum12=big12;
            position12=i;
        }
    }
    int counter12=0;
    int lowest12=RowMin[position12];
    // finding the next set of values to choose from
    for (int i=counter11*14; i<=counter11*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest12&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&& CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4]&&CityName[i%14]!=CityName[counter5]&&CityName[i%14]!=CityName[counter6]&&CityName[i%14]!=CityName[counter7]&&CityName[i%14]!=CityName[counter8]&&CityName[i%14]!=CityName[counter9]&& CityName[i%14]!=CityName[counter10]&&CityName[i%14]!=CityName[counter11])
            {
                lowest12=num;
                counter12=i%14;
            }
        }
    }
    cout << CityName[counter11] << " -> " << CityName[counter12] << endl;
    sum+=lowest12;

    int maximum13=0;
    int position13=0;
    for (int i=counter12*14; i<=counter12*14+13; i++)
    {
        int big13=RowMin[i];
        if(big13>=maximum13&&big13!=0)
        {
            maximum13=big13;
            position13=i;
        }
    }
    int counter13=0;
    int lowest13=RowMin[position13];
    // finding the next set of values to choose from
    for (int i=counter12*14; i<=counter12*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest13&&num!=0)
        {
            if (CityName[i%14]!=CityName[R1]&&CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4]&&CityName[i%14]!=CityName[counter5]&&CityName[i%14]!=CityName[counter6]&&CityName[i%14]!=CityName[counter7]&&CityName[i%14]!=CityName[counter8]&&CityName[i%14]!=CityName[counter9]&& CityName[i%14]!=CityName[counter10]&&CityName[i%14]!=CityName[counter11]&& CityName[i%14]!=CityName[counter12])
            {
                lowest13=num;
                counter13=i%14;
            }
        }
    }
    cout << CityName[counter12] << " -> " << CityName[counter13] << endl;
    sum+=lowest13;

    int maximum14=0;
    int position14=0;
    for (int i=counter13*14; i<=counter13*14+13; i++)
    {
        int big14=RowMin[i];
        if(big14>=maximum14&&big14!=0)
        {
            maximum14=big14;
            position14=i;
        }
    }
    int counter14=0;
    int lowest14=RowMin[position13];
    // finding the next set of values to choose from
    for (int i=counter13*14; i<=counter13*14+13; i++)
    {
        int num=RowMin[i];
        if (num<=lowest14&&num!=0)
        {
            if (CityName[i%14]!=CityName[counter1]&&CityName[i%14]!=CityName[counter2]&&CityName[i%14]!=CityName[counter3] && CityName[i%14]!=CityName[counter4]&&CityName[i%14]!=CityName[counter5]&&CityName[i%14]!=CityName[counter6]&&CityName[i%14]!=CityName[counter7]&&CityName[i%14]!=CityName[counter8]&&CityName[i%14]!=CityName[counter9]&& CityName[i%14]!=CityName[counter10]&&CityName[i%14]!=CityName[counter11]&& CityName[i%14]!=CityName[counter12])
            {
                lowest14=num;
                counter14=i%14;
            }
        }
    }
    cout << CityName[counter13] << " -> " << CityName[counter14] << endl;
    sum+=lowest14;

    int sumALT=sum*400;     // Finding the more appropriate overall distance travelled because each ine unit is a distance of 400 kilometres.

    cout << endl;           // Spacing the routes with the overall distance travelled to make it look clean for the output.

    cout << "The shortest route consists of a distance of: " << sum << " units or " << sumALT << " km!" << endl; //Telling the user the overall distance travelled to each city.
    char userInput='a'; // Declares variable to get user input for the option of exporting to the text file

    while (userInput!='y' || userInput!='Y') // loops until the user
    {
        cout << "Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No" << endl; // asks the user whether they want to export the data to a tetx fiel or not
        cin >> userInput;
        if (userInput=='y' || userInput=='n' || userInput=='Y' || userInput=='N') // breaks out of the while loop if the user inputs any of the defined characters (such as 'y' or 'n')
            break;
    }

    if (userInput == 'y' || userInput == 'Y') // exports the data to the text file if the user enter 'y' or 'Y'
    {
        ofstream outfile("route.txt"); // creates if already not created text file named route.txt

        outfile << "  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------" << "\n"; //
        outfile << endl;
        outfile << CityName[0] << " -> " << CityName[counter1]<< endl; // exports the 1st destination
        outfile << CityName[counter1] << " -> " << CityName[counter2] << endl; // exports the 2nd destination
        outfile << CityName[counter2] << " -> " << CityName[counter3] << endl; // exports the 3rd destination
        outfile << CityName[counter3] << " -> " << CityName[counter4] << endl; // exports the 4th destination
        outfile << CityName[counter4] << " -> " << CityName[counter5] << endl; // exports the 5th destination
        outfile << CityName[counter5] << " -> " << CityName[counter6] << endl; // exports the 6th destination
        outfile << CityName[counter6] << " -> " << CityName[counter7] << endl; // exports the 7th destination
        outfile << CityName[counter7] << " -> " << CityName[counter8] << endl; // exports the 8th destination
        outfile << CityName[counter8] << " -> " << CityName[counter9] << endl; // exports the 9th destination
        outfile << CityName[counter9] << " -> " << CityName[counter10] << endl; // exports the 10th destination
        outfile << CityName[counter10] << " -> " << CityName[counter11] << endl; // exports the 11th destination
        outfile << CityName[counter11] << " -> " << CityName[counter12] << endl; // exports the 12th destination
        outfile << CityName[counter12] << " -> " << CityName[counter13] << endl; // exports the 13th destination
        outfile << CityName[counter13] << " -> " << CityName[counter14] << endl; // Exports the 14th destinatation
        outfile << endl;

        outfile << "The shortest distance travelled to each city is: " << sum << " or " << sumALT << " km!" << endl; // exports the overall destination of the route to the hext file
        outfile.close();

        cout << endl;
        cout << "The details of the route has been exported to 'route.txt' in the same folder as the cpp file" << endl; // prints out a statement telling the user the data has been exported to the file
    }
    else
        cout << "You can close the console window now" << endl;
    return 0;           // Ending the program.
}


/*
<-------------------------------TESTS all the possible errors & mistakes that might occur during User Input-------------------------->
Enter Your City Name Below!(Equal to or less than 10 characters) // The program continues to ask the user for input if they don't input anything

Enter Your City Name Below!(Equal to or less than 10 characters) // The program continues to ask for input if the user inputted city name is more than 10 characters
city123456789
Enter Your City Name Below!(Equal to or less than 10 characters)
city
Enter Your City's X Value!(Less than 69) // The program continues to ask for input if the inputted user x value is less than 0
-1
Enter Your City's X Value! (Less than 69) // The program contues to ask for input if the user inputted x value is left blank

Enter Your City's X Value!(Less than 69) // The program contues to ask for input if the use inputted x value is greater than 69
70
Enter Your City's X Value!(Less than 69) // The program contues to ask for input if the user inputs a non numeric value for the x value
abc
Please enter a numeric value // the program displays appripriate message if the user inputs a non numeric value for the x value
Enter Your City's X Value!(Less than 69)
35
Enter Your City's Y Value! (Less than 32) // the program continues to ask for input if the user inputs a value less than 1 for the y value
0
Enter Your City's Y Value! (Less than 32) // the program continues to ask for input if the user inputs nothing for the y value

Enter Your City's Y Value! (Less than 32) // the program continues to ask for input if the user inputs a value greater than 32 for the y value
33
Enter Your City's Y Value! (Less than 32) // the program continues to ask for input if the user inputs a non numeric valeu for the y value
zeee
Please enter a numeric value // the program displays appropriate message if the user inputs a non numeric valeu for the y value
Enter Your City's Y Value! (Less than 32)
7
If your city lies on the same y value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents a 400km distance!



    * Whitehorse


                                        * Iqaluit


             * Yellowknife
                                   * city






                                                                   * St.Johns




        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax






                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   37   10   32   64   15   17   25   55   30   44   52   57   42

1   37    0   28    6   29   35   41   26   24   25   21   24   27   29

2   10   28    0   22   55   12   17   16   45   21   35   42   47   33

3   32    6   22    0   33   29   36   21   26   20   20   25   29   27

4   64   29   55   33    0   60   66   48   16   44   28   22   19   40

5   15   35   12   29   60    0    7   13   48   19   35   43   49   30

6   17   41   17   36   66    7    0   19   54   24   41   49   54   35

7   25   26   16   21   48   13   19    0   36    6   23   31   36   18

8   55   24   45   26   16   48   54   36    0   31   14    6    4   25

9   30   25   21   20   44   19   24    6   31    0   18   26   31   13

10   44   21   35   20   28   35   41   23   14   18    0    9   14   13

11   52   24   42   25   22   43   49   31    6   26    9    0    6   19

12   57   27   47   29   19   49   54   36    4   31   14    6    0   23

13   42   29   33   27   40   30   35   18   25   13   13   19   23    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


Whitehorse -> Yellowknife
Yellowknife -> Edmonton
Edmonton -> Victoria
Victoria -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> St.Johns
St.Johns -> Iqaluit
Iqaluit -> city
city -> Whitehorse

The shortest distance travelled to each city is: 182 units or 72800 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
y

The details of the route has been exported to 'route.txt' in the cpp folder

Process returned 0 (0x0)   execution time : 13.078 s
Press any key to continue.
*********************************************************************************************************************************
<-----------------------------TESTS the minimum possible X & Y values that the user is allowed to input------------------------->

Enter Your City Name Below! (Equal to or less than 10 characters)
CityOfDreams
Enter Your City Name Below! (Equal to or less than 10 characters)
DreamCity
Enter Your City's X Value! (Less than 69)
1
Enter Your City's Y Value! (Less than 32)
1
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!

 * DreamCity


    * Whitehorse


                                        * Iqaluit


             * Yellowknife






                                                                   * St.Johns




        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax






                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0    4   40   14   68   18   19   28   59   34   48   56   60   46

1    4    0   37   10   64   15   17   25   55   30   44   52   57   42

2   40   37    0   28   29   35   41   26   24   25   21   24   27   29

3   14   10   28    0   55   12   17   16   45   21   35   42   47   33

4   68   64   29   55    0   60   66   48   16   44   28   22   19   40

5   18   15   35   12   60    0    7   13   48   19   35   43   49   30

6   19   17   41   17   66    7    0   19   54   24   41   49   54   35

7   28   25   26   16   48   13   19    0   36    6   23   31   36   18

8   59   55   24   45   16   48   54   36    0   31   14    6    4   25

9   34   30   25   21   44   19   24    6   31    0   18   26   31   13

10   48   44   21   35   28   35   41   23   14   18    0    9   14   13

11   56   52   24   42   22   43   49   31    6   26    9    0    6   19

12   60   57   27   47   19   49   54   36    4   31   14    6    0   23

13   46   42   29   33   40   30   35   18   25   13   13   19   23    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


DreamCity -> Whitehorse
Whitehorse -> Yellowknife
Yellowknife -> Edmonton
Edmonton -> Victoria
Victoria -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> St.Johns
St.Johns -> Iqaluit
Iqaluit -> DreamCity

The shortest route consists of a distance of: 188 units or 75200 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
Y

The details of the route has been exported to 'route.txt' in the cpp folder

Process returned 0 (0x0)   execution time : 78.766 s
Press any key to continue.
*********************************************************************************************************************************
<-----------------------------TESTS the maximum possible X & Y values that the user is allowed to input------------------------->

Enter Your City Name Below! (Equal to or less than 10 characters)
CSCity
Enter Your City's X Value! (Less than 69)
69
Enter Your City's X Value! (Less than 69)
68
Enter Your City's Y Value! (Less than 32)
31
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!



    * Whitehorse


                                        * Iqaluit


             * Yellowknife






                                                                   * St.Johns




        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax




                                                                    * CSCity


                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   37   10   64   15   17   25   55   30   44   52   57   70   42

1   37    0   28   29   35   41   26   24   25   21   24   27   39   29

2   10   28    0   55   12   17   16   45   21   35   42   47   61   33

3   64   29   55    0   60   66   48   16   44   28   22   19   19   40

4   15   35   12   60    0    7   13   48   19   35   43   49   62   30

5   17   41   17   66    7    0   19   54   24   41   49   54   68   35

6   25   26   16   48   13   19    0   36    6   23   31   36   50   18

7   55   24   45   16   48   54   36    0   31   14    6    4   16   25

8   30   25   21   44   19   24    6   31    0   18   26   31   44   13

9   44   21   35   28   35   41   23   14   18    0    9   14   27   13

10   52   24   42   22   43   49   31    6   26    9    0    6   19   19

11   57   27   47   19   49   54   36    4   31   14    6    0   14   23

12   70   39   61   19   62   68   50   16   44   27   19   14    0   36

13   42   29   33   40   30   35   18   25   13   13   19   23   36    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


Whitehorse -> Yellowknife
Yellowknife -> Edmonton
Edmonton -> Victoria
Victoria -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> CSCity
CSCity -> St.Johns
St.Johns -> Iqaluit
Iqaluit -> Whitehorse

The shortest route consists of a distance of: 200 units or 80000 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
y

The details of the route has been exported to 'route.txt' in the same folder as
the cpp file

Process returned 0 (0x0)   execution time : 29.336 s
Press any key to continue.
*********************************************************************************************************************************
<--------------------------User Inputtted City lies on the same cooridnates as a predefined city (Iqaluit)---------------------->

Enter Your City Name Below! (Equal to or less than 10 characters)
SameAsIqal
Enter Your City's X Value! (Less than 69)
40
Enter Your City's Y Value! (Less than 32)
5
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!



    * Whitehorse


                                        * Iqaluit
                                        * SameAsIqal


             * Yellowknife






                                                                   * St.Johns




        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax






                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   37   37   10   64   15   17   25   55   30   44   52   57   42

1   37    0    0   28   29   35   41   26   24   25   21   24   27   29

2   37    0    0   28   29   35   41   26   24   25   21   24   27   29

3   10   28   28    0   55   12   17   16   45   21   35   42   47   33

4   64   29   29   55    0   60   66   48   16   44   28   22   19   40

5   15   35   35   12   60    0    7   13   48   19   35   43   49   30

6   17   41   41   17   66    7    0   19   54   24   41   49   54   35

7   25   26   26   16   48   13   19    0   36    6   23   31   36   18

8   55   24   24   45   16   48   54   36    0   31   14    6    4   25

9   30   25   25   21   44   19   24    6   31    0   18   26   31   13

10   44   21   21   35   28   35   41   23   14   18    0    9   14   13

11   52   24   24   42   22   43   49   31    6   26    9    0    6   19

12   57   27   27   47   19   49   54   36    4   31   14    6    0   23

13   42   29   29   33   40   30   35   18   25   13   13   19   23    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


Whitehorse -> Yellowknife
Yellowknife -> Edmonton
Edmonton -> Victoria
Victoria -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> St.Johns
St.Johns -> SameAsIqal
SameAsIqal -> Whitehorse
Whitehorse -> Iqaluit

The shortest route consists of a distance of: 222 units or 88800 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
y

The details of the route has been exported to 'route.txt' in the same folder as
the cpp file

Process returned 0 (0x0)   execution time : 44.967 s
Press any key to continue.
*********************************************************************************************************************************
<----------------------------------TESTS the results of a user inputted Min X value & a Max Y Value----------------------------->

Enter Your City Name Below! (Equal to or less than 10 characters)
MaxYminX
Enter Your City's X Value! (Less than 69)
1
Enter Your City's Y Value! (Less than 32)
31
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!



    * Whitehorse


                                        * Iqaluit


             * Yellowknife






                                                                   * St.Johns




        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax




 * MaxYminX


                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   37   10   64   15   17   25   55   30   44   52   57   29   42

1   37    0   28   29   35   41   26   24   25   21   24   27   47   29

2   10   28    0   55   12   17   16   45   21   35   42   47   27   33

3   64   29   55    0   60   66   48   16   44   28   22   19   69   40

4   15   35   12   60    0    7   13   48   19   35   43   49   16   30

5   17   41   17   66    7    0   19   54   24   41   49   54   13   35

6   25   26   16   48   13   19    0   36    6   23   31   36   22   18

7   55   24   45   16   48   54   36    0   31   14    6    4   55   25

8   30   25   21   44   19   24    6   31    0   18   26   31   25   13

9   44   21   35   28   35   41   23   14   18    0    9   14   42   13

10   52   24   42   22   43   49   31    6   26    9    0    6   50   19

11   57   27   47   19   49   54   36    4   31   14    6    0   55   23

12   29   47   27   69   16   13   22   55   25   42   50   55    0   33

13   42   29   33   40   30   35   18   25   13   13   19   23   33    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


Whitehorse -> Yellowknife
Yellowknife -> Edmonton
Edmonton -> Victoria
Victoria -> MaxYminX
MaxYminX -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> St.Johns
St.Johns -> Iqaluit
Iqaluit -> Whitehorse

The shortest route consists of a distance of: 197 units or 78800 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
Y

The details of the route has been exported to 'route.txt' in the same folder as
the cpp file

Process returned 0 (0x0)   execution time : 136.053 s
Press any key to continue.
*********************************************************************************************************************************
<----------------------------------TESTS the results of a user inputted Min Y value & a Max X Value----------------------------->

Enter Your City Name Below! (Equal to or less than 10 characters)
MinYmaxX
Enter Your City's X Value! (Less than 69)
68
Enter Your City's Y Value! (Less than 32)
1
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!

                                                                    * MinYmaxX


    * Whitehorse


                                        * Iqaluit


             * Yellowknife






                                                                   * St.Johns




        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax






                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   65   29   56   13   63   69   52   26   49   36   31   30   48

1   65    0   37   10   64   15   17   25   55   30   44   52   57   42

2   29   37    0   28   29   35   41   26   24   25   21   24   27   29

3   56   10   28    0   55   12   17   16   45   21   35   42   47   33

4   13   64   29   55    0   60   66   48   16   44   28   22   19   40

5   63   15   35   12   60    0    7   13   48   19   35   43   49   30

6   69   17   41   17   66    7    0   19   54   24   41   49   54   35

7   52   25   26   16   48   13   19    0   36    6   23   31   36   18

8   26   55   24   45   16   48   54   36    0   31   14    6    4   25

9   49   30   25   21   44   19   24    6   31    0   18   26   31   13

10   36   44   21   35   28   35   41   23   14   18    0    9   14   13

11   31   52   24   42   22   43   49   31    6   26    9    0    6   19

12   30   57   27   47   19   49   54   36    4   31   14    6    0   23

13   48   42   29   33   40   30   35   18   25   13   13   19   23    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


MinYmaxX -> St.Johns
St.Johns -> Charlottetown
Charlottetown -> Halifax
Halifax -> Fredericton
Fredericton -> Quebec
Quebec -> Toronto
Toronto -> Winnipeg
Winnipeg -> Regina
Regina -> Edmonton
Edmonton -> Victoria
Victoria -> Yellowknife
Yellowknife -> Whitehorse
Whitehorse -> Iqaluit
Iqaluit -> MinYmaxX

The shortest route consists of a distance of: 193 units or 77200 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
yes

The details of the route has been exported to 'route.txt' in the same folder as
the cpp file

Process returned 0 (0x0)   execution time : 189.583 s
Press any key to continue.
*********************************************************************************************************************************
<-------------------------------TESTS what occurs if the user decides not export route to "route.txt"--------------------------->

Enter Your City Name Below! (Equal to or less than 10 characters)
NoExport
Enter Your City's X Value! (Less than 69)
66
Enter Your City's Y Value! (Less than 32)
16
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!



    * Whitehorse


                                        * Iqaluit


             * Yellowknife






                                                                   * St.Johns



                                                                  * NoExport

        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax






                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   37   10   64   64   15   17   25   55   30   44   52   57   42

1   37    0   28   29   29   35   41   26   24   25   21   24   27   29

2   10   28    0   55   54   12   17   16   45   21   35   42   47   33

3   64   29   55    0    4   60   66   48   16   44   28   22   19   40

4   64   29   54    4    0   59   65   47   14   42   26   19   16   38

5   15   35   12   60   59    0    7   13   48   19   35   43   49   30

6   17   41   17   66   65    7    0   19   54   24   41   49   54   35

7   25   26   16   48   47   13   19    0   36    6   23   31   36   18

8   55   24   45   16   14   48   54   36    0   31   14    6    4   25

9   30   25   21   44   42   19   24    6   31    0   18   26   31   13

10   44   21   35   28   26   35   41   23   14   18    0    9   14   13

11   52   24   42   22   19   43   49   31    6   26    9    0    6   19

12   57   27   47   19   16   49   54   36    4   31   14    6    0   23

13   42   29   33   40   38   30   35   18   25   13   13   19   23    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


Whitehorse -> Yellowknife
Yellowknife -> Edmonton
Edmonton -> Victoria
Victoria -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> NoExport
NoExport -> St.Johns
St.Johns -> Iqaluit
Iqaluit -> Whitehorse

The shortest route consists of a distance of: 183 units or 73200 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
n
You can close the console window now

Process returned 0 (0x0)   execution time : 30.148 s
Press any key to continue.
*********************************************************************************************************************************
<-------------------------------TESTS what occurs if the user decides not export route to "route.txt"--------------------------->
Enter Your City Name Below! (Equal to or less than 10 characters)
NoExportN
Enter Your City's X Value! (Less than 69)
21
Enter Your City's Y Value! (Less than 32)
11
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!



    * Whitehorse


                                        * Iqaluit


             * Yellowknife




                     * NoExportN


                                                                   * St.Johns




        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax






                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   37   10   19   64   15   17   25   55   30   44   52   57   42

1   37    0   28   20   29   35   41   26   24   25   21   24   27   29

2   10   28    0    9   55   12   17   16   45   21   35   42   47   33

3   19   20    9    0   47   15   21   11   37   14   26   33   38   26

4   64   29   55   47    0   60   66   48   16   44   28   22   19   40

5   15   35   12   15   60    0    7   13   48   19   35   43   49   30

6   17   41   17   21   66    7    0   19   54   24   41   49   54   35

7   25   26   16   11   48   13   19    0   36    6   23   31   36   18

8   55   24   45   37   16   48   54   36    0   31   14    6    4   25

9   30   25   21   14   44   19   24    6   31    0   18   26   31   13

10   44   21   35   26   28   35   41   23   14   18    0    9   14   13

11   52   24   42   33   22   43   49   31    6   26    9    0    6   19

12   57   27   47   38   19   49   54   36    4   31   14    6    0   23

13   42   29   33   26   40   30   35   18   25   13   13   19   23    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


Whitehorse -> Yellowknife
Yellowknife -> NoExportN
NoExportN -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> St.Johns
St.Johns -> Iqaluit
Iqaluit -> Edmonton
Edmonton -> Victoria
Victoria -> Whitehorse

The shortest route consists of a distance of: 185 units or 74000 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
N
You can close the console window now

Process returned 0 (0x0)   execution time : 34.976 s
Press any key to continue.
*********************************************************************************************************************************
<-----TESTS the looping that occurs that forces the user to decide whether they want to export route to "route.txt" or not"----->
Enter Your City Name Below! (Equal to or less than 10 characters)
ExportMust
Enter Your City's X Value! (Less than 69)
21
Enter Your City's Y Value! (Less than 32)
11
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!



    * Whitehorse


                                        * Iqaluit


             * Yellowknife




                     * ExportMust


                                                                   * St.Johns




        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax






                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   37   10   19   64   15   17   25   55   30   44   52   57   42

1   37    0   28   20   29   35   41   26   24   25   21   24   27   29

2   10   28    0    9   55   12   17   16   45   21   35   42   47   33

3   19   20    9    0   47   15   21   11   37   14   26   33   38   26

4   64   29   55   47    0   60   66   48   16   44   28   22   19   40

5   15   35   12   15   60    0    7   13   48   19   35   43   49   30

6   17   41   17   21   66    7    0   19   54   24   41   49   54   35

7   25   26   16   11   48   13   19    0   36    6   23   31   36   18

8   55   24   45   37   16   48   54   36    0   31   14    6    4   25

9   30   25   21   14   44   19   24    6   31    0   18   26   31   13

10   44   21   35   26   28   35   41   23   14   18    0    9   14   13

11   52   24   42   33   22   43   49   31    6   26    9    0    6   19

12   57   27   47   38   19   49   54   36    4   31   14    6    0   23

13   42   29   33   26   40   30   35   18   25   13   13   19   23    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


Whitehorse -> Yellowknife
Yellowknife -> ExportMust
ExportMust -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> St.Johns
St.Johns -> Iqaluit
Iqaluit -> Edmonton
Edmonton -> Victoria
Victoria -> Whitehorse

The shortest route consists of a distance of: 185 units or 74000 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
a
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
z
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
1
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
y

The details of the route has been exported to 'route.txt' in the same folder as
the cpp file

Process returned 0 (0x0)   execution time : 22.126 s
Press any key to continue.
*********************************************************************************************************************************
<-----TESTS the looping that occurs that forces the user to decide whether they want to export route to "route.txt" or not"----->
Enter Your City Name Below! (Equal to or less than 10 characters)
ExportMustN
Enter Your City Name Below! (Equal to or less than 10 characters)
ExportMust
Enter Your City's X Value! (Less than 69)
37
Enter Your City's Y Value! (Less than 32)
27
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!



    * Whitehorse


                                        * Iqaluit


             * Yellowknife






                                                                   * St.Johns




        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax
                                     * ExportMust






                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   37   10   64   15   17   25   55   30   44   52   57   41   42

1   37    0   28   29   35   41   26   24   25   21   24   27   23   29

2   10   28    0   55   12   17   16   45   21   35   42   47   32   33

3   64   29   55    0   60   66   48   16   44   28   22   19   34   40

4   15   35   12   60    0    7   13   48   19   35   43   49   31   30

5   17   41   17   66    7    0   19   54   24   41   49   54   36   35

6   25   26   16   48   13   19    0   36    6   23   31   36   19   18

7   55   24   45   16   48   54   36    0   31   14    6    4   19   25

8   30   25   21   44   19   24    6   31    0   18   26   31   13   13

9   44   21   35   28   35   41   23   14   18    0    9   14    6   13

10   52   24   42   22   43   49   31    6   26    9    0    6   14   19

11   57   27   47   19   49   54   36    4   31   14    6    0   18   23

12   41   23   32   34   31   36   19   19   13    6   14   18    0    8

13   42   29   33   40   30   35   18   25   13   13   19   23    8    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


Whitehorse -> Yellowknife
Yellowknife -> Edmonton
Edmonton -> Victoria
Victoria -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> ExportMust
ExportMust -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> St.Johns
St.Johns -> Iqaluit
Iqaluit -> Whitehorse

The shortest route consists of a distance of: 182 units or 72800 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
a
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
1
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
N
You can close the console window now

Process returned 0 (0x0)   execution time : 51.936 s
Press any key to continue.
*********************************************************************************************************************************
<----------------------------------------------------------ALL TEST CASES------------------------------------------------------->
Enter Your City Name Below! (Equal to or less than 10 characters)

Enter Your City Name Below! (Equal to or less than 10 characters)
123456789111
Enter Your City Name Below! (Equal to or less than 10 characters)
AllTests
Enter Your City's X Value! (Less than 69)
-1
Enter Your City's X Value! (Less than 69)
71
Enter Your City's X Value! (Less than 69)
a
Please enter a numeric value
Enter Your City's X Value! (Less than 69)
33
Enter Your City's Y Value! (Less than 32)
35
Enter Your City's Y Value! (Less than 32)
0
Enter Your City's Y Value! (Less than 32)
z
Please enter a numeric value
Enter Your City's Y Value! (Less than 32)
15
If your city lies on the same Y-Value as another city it will be printed on the
next available line!
  ----------------------THE TRAVELLING SALESMAN PROBLEM!----------------------

Each one unit represents 400km in distance!



    * Whitehorse


                                        * Iqaluit


             * Yellowknife






                                                                   * St.Johns


                                 * AllTests


        * Edmonton


  * Victoria


                    * Regina


                                                       * Charlottetown

                         * Winnipeg

                                          * Quebec

                                                  * Fredericton

                                                       * Halifax






                                 * Toronto


  -----------ALL POSSIBLE DISTANCES BETWEEN ANY PAIR OF CITIES!-----------


    0    1    2    3    4    5    6    7    8    9   10   11   12   13

0    0   37   10   64   32   15   17   25   55   30   44   52   57   42

1   37    0   28   29   13   35   41   26   24   25   21   24   27   29

2   10   28    0   55   22   12   17   16   45   21   35   42   47   33

3   64   29   55    0   35   60   66   48   16   44   28   22   19   40

4   32   13   22   35    0   26   32   15   24   13   14   21   26   18

5   15   35   12   60   26    0    7   13   48   19   35   43   49   30

6   17   41   17   66   32    7    0   19   54   24   41   49   54   35

7   25   26   16   48   15   13   19    0   36    6   23   31   36   18

8   55   24   45   16   24   48   54   36    0   31   14    6    4   25

9   30   25   21   44   13   19   24    6   31    0   18   26   31   13

10   44   21   35   28   14   35   41   23   14   18    0    9   14   13

11   52   24   42   22   21   43   49   31    6   26    9    0    6   19

12   57   27   47   19   26   49   54   36    4   31   14    6    0   23

13   42   29   33   40   18   30   35   18   25   13   13   19   23    0

  ----------------------THE BEST ROUTE TO ALL CITIES!----------------------


Whitehorse -> Yellowknife
Yellowknife -> Edmonton
Edmonton -> Victoria
Victoria -> Regina
Regina -> Winnipeg
Winnipeg -> Toronto
Toronto -> Quebec
Quebec -> Fredericton
Fredericton -> Halifax
Halifax -> Charlottetown
Charlottetown -> St.Johns
St.Johns -> Iqaluit
Iqaluit -> AllTests
AllTests -> Whitehorse

The shortest route consists of a distance of: 189 units or 75600 km!
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
a
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
1
Do you want to print the route to a text file? Enter 'Y' for yes or 'N' for No
Y

The details of the route has been exported to 'route.txt' in the same folder as
the cpp file

Process returned 0 (0x0)   execution time : 194.362 s
Press any key to continue.
*/




