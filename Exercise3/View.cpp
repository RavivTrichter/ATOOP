//
// Created by Admin on 19/06/2018.
//

#include "View.h"


//returns program to default params
void View::defaultParam() {
    size = 25;
    scale = 2.0;
    setAxis(Point(-10.00, -10.00));
}


void View::show() {
    int spaces = 0, tmp , ToPrint;
    string empty = ". ";
    const int NumOfTimesToPrintNumber = 3, NumOfSpacesInMap = 4, NumOfSpacesAtEnd = 6;
    int diff =int(((size-1)*scale)); // difference between the axis.y and the top limit size of the map

    cout << "Display size : " << size << ", scale: " << scale <<", origin : ";
    axis.print();
    cout << endl;


    /*  double for loop is responsible for printing the map */
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if(x == 0 ) {
                if (diff % NumOfTimesToPrintNumber == 0) { // every three points printing the number on left side of map
                    ToPrint = int(diff+axis.y); // the number we need to print
                    tmp = HowManyChars(ToPrint); // checking how many characters it has
                    spaces = NumOfSpacesInMap - tmp; // subtracting the number of spaces that are expected in this part
                    while(spaces--) // printing the spaces (There is a difference between number with 2 digits and a number with 3 or 1 digits)
                        cout << " ";
                    cout << ToPrint << " "; // printing the number
                } else
                    cout << "     "; //5 spaces // printing the expected number of spaces
            }
                /*The next row is a calculated square of the the current point and the point on right from her.
                 * every step in the loop calculates according to x and y the exact square and checks the ship and port data structures if there is a point
                 * in the current square -> by function BullsEye */
                cout << Model::getInstance().BullsEye (Point(axis.x + x*scale,(size - 1 - y)*scale + axis.y), Point(axis.x + ((x+1)*scale),(size - 1 - y + 1)*scale + axis.y));
        } //X loop
        diff -= scale; // subtracting every '\n' the scale of the diff variable that describes our Y position
        cout << endl;
    } // Y loop

    spaces = NumOfSpacesAtEnd - HowManyChars(int(axis.x)); // the first number of the X axis
    while(spaces--)
        cout << " ";
    cout << axis.x;
    /* This For Loop is printing all the bottom numbers of the map*/
    for (int x = 1; x < size; ++x) {
        if( x % NumOfTimesToPrintNumber == 0 ) {
            ToPrint =  axis.x + (scale * x);
            spaces = NumOfSpacesAtEnd - HowManyChars(ToPrint);
            while(spaces--)
                cout << " ";
            cout << ToPrint;
        }
    }


cout << endl;
}



int View::HowManyChars(int num) {

    string str = "";
    int count = num < 0 ? 1 : 0; // if it is negative, adds one because of '-' character

    while(num){
        num /= 10;
        count++;
    }
    return count;
}

/** Setters**/

void View::setSize(int size) {
    View::size = size;
}

void View::setScale(double scale) {
    View::scale = scale;
}

void View::setAxis(const Point &axis) {
    View::axis = axis;
}
