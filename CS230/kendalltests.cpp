/*
 * Kendall Lundschen
 * ScatterDataMain.cpp - testing ints
 */

#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;
#include "ScatterData.h"

//used in testing functions:
ScatterData<int> i1;
ScatterData<int> i2;

//this function tests the constructors
void TestConstructors()
{
    //point constructor
    ScatterData<int>::Point p1(3,5);
    ScatterData<int>::Point p2;
    
    //default
    ScatterData<int> t1;
    cout << t1 << endl;
    
    //ScatterData x and y constructor
    int x[5] = {1,2,3,4,5};
    int y[5] = {6,7,8,9,10};
    ScatterData<int>t2(x,y,5);
    cout << t2 << endl;
    
    //ScatterData point constructor
    ScatterData<int>::Point pList1[5] = {ScatterData<int>::Point(1,2),
          ScatterData<int>::Point(3,4),ScatterData<int>::Point(5,6),
          ScatterData<int>::Point(7,8),ScatterData<int>::Point(9,10)};
    ScatterData<int> t3(pList1,5);
    cout << t3 << endl;
    
    //ScatterData istream constructor
    ScatterData<int> t4(cin);
    cout << t4 << endl;
    
    //ScatterData string constructor
    string s = "[(5,6),(3,5),(2,3),(1,3),(5,2)]";
    ScatterData<int> t5(s);
    cout << t5 << endl;
}

//this function tests the inserts & removes
void TestInserts()
{
    //insert(x,y)
    i1.insert(1,1);
    i1.insert(2,2);
    i1.insert(3,3);
    i1.insert(4,4);
    i1.insert(5,5);
    i1.insert(6,0);
    i1.insert(7,7);
    i1.insert(8,8);
    i1.insert(9,9);
    i1.insert(10,10);
    i1.insert(11,11);
    i1.insert(12,12);
    i1.insert(1,13);
    cout << "i1: " << i1;
    
    //insert(p)
    ScatterData<int>::Point p1(1,1);
    ScatterData<int>::Point p2(2,3);
    ScatterData<int>::Point p3(1,3);
    ScatterData<int>::Point p4(1,4);
    ScatterData<int>::Point p5(1,3);
    ScatterData<int>::Point p6(1,6);
    ScatterData<int>::Point p7(1,7);
    ScatterData<int>::Point p8(1,3);
    ScatterData<int>::Point p9(1,9);
    ScatterData<int>::Point p10(2,1);
    ScatterData<int>::Point p11(2,3);
    ScatterData<int>::Point p12(2,3);
    ScatterData<int>::Point p13(2,3);
    ScatterData<int>::Point p14(2,5);
    ScatterData<int>::Point p15(2,6);
    ScatterData<int>::Point p16(2,7);
    ScatterData<int>::Point p17(2,8);
    ScatterData<int>::Point p18(2,9);
    ScatterData<int>::Point p19(3,1);
    ScatterData<int>::Point p20(3,2);
    ScatterData<int>::Point p21(3,3);
    
    i2.insert(p1);
    i2.insert(p2);
    i2.insert(p3);
    i2.insert(p4);
    i2.insert(p5);
    i2.insert(p6);
    i2.insert(p7);
    i2.insert(p8);
    i2.insert(p9);
    i2.insert(p10);
    i2.insert(p11);
    i2.insert(p12);
    i2.insert(p13);
    i2.insert(p14);
    i2.insert(p15);
    i2.insert(p16);
    i2.insert(p17);
    i2.insert(p18);
    i2.insert(p19);
    i2.insert(p20);
    i2.insert(p21);
    cout << endl <<"i2: " << i2 << endl;
       
   /* //indexOfPoints
    int *array;
    array = new int[21];
    int n;
    //i2.indexOfPoints(array, n, 2,3);
    assert(array[0] == 1);
    assert(array[1] == 10);
    assert(array[2] == 11);
    assert(array[3] == 12);*/
    
    bool removePoints = true;
    
    if(!removePoints)
    {
        //remove(x,y)
        i2.remove(2,3);
        cout << endl << "i2 after remove(2,3): " << i2 << endl;
        
        i2.remove(3,3);
        cout << endl << "i2 after remove(3,3): " << i2 << endl;
        
        i2.remove(1,1);
        cout << endl << "i2 after remove(1,1): " << i2 << endl;
    }
    else
    {
        //remove(p)
        i2.remove(p2);
        cout << endl << "i2 after remove(2,3): " << i2 << endl;
        
        i2.remove(p21);
        cout << endl << "i2 after remove(3,3): " << i2 << endl;
        
        i2.remove(p1);
        cout << endl << "i2 after remove(1,1): " << i2 << endl;
    }
}

//this function tests the count functions
void TestCounts()
{
    //count()
    int i1NumPoints = i1.count();
    cout << "Number of points in i1 = " << i1NumPoints << endl;
    assert(i1NumPoints == 13);
    
    int i2NumPoints = i2.count();
    cout << "Number of points in i2 = " << i2NumPoints << endl;
    assert(i2NumPoints == 15);
    
    //count(x,y)
    int i1NumPoints13 = i1.count(1,3);
    cout << "Num of occurences of (1,3) in i1: " << i1NumPoints13 << endl;
    assert(i1NumPoints13 == 0);
    
    int i2NumPoints13 = i2.count(1,3);
    cout << "Num of occurences of (1,3) in i2: " << i2NumPoints13 << endl;
    assert(i2NumPoints13 == 3);
    
    assert(i2.count(1,1) == 0);
    assert(i2.count(1,6) == 1);
    
    //count(p)
    ScatterData<int>::Point p1(1,3);
    ScatterData<int>::Point p2(1,1);
    ScatterData<int>::Point p3(1,6);
    
    int i1NumPointsP1 = i1.count(p1);
    cout << endl <<"Num of occurences of (1,3) in i1: " << i1NumPointsP1 << endl;
    assert(i1NumPointsP1 == 0);
    
    int i2NumPointsP1 = i2.count(p1);
    cout << "Num of occurences of (1,3) in i2: " << i2NumPointsP1 << endl;
    assert(i2NumPointsP1 == 3);
    
    assert(i2.count(p2) == 0);
    assert(i2.count(p3) == 1);
}

//this function tests operator=
void TestAssignment()
{
    //= istream
    ScatterData<int> equalTester;
    cout << "EqualTester: " << equalTester << endl;
    equalTester = cin;
    cout << "EqualTester: " << equalTester << endl;
    
    //= ScatterData<int>
    ScatterData<int> equalTester2(cin);
    cout << "equalTester2: " << equalTester2 << endl;
    ScatterData<int> equalTester2Copy;
    equalTester2Copy = equalTester2;
    cout << "equalTester2Copy: " << equalTester2Copy << endl;
}

//this function tests istream >> A
void TestReadingInput()
{
    //cin >> A
    ScatterData<int> CinTest;
    cin >> CinTest;
    cout << "CinTest: " << CinTest << endl;
}

//this function tests topLeft() and bottomRight()
void TestBoundingBox()
{
    //test topLeft()
    ScatterData<int>::Point topLeft = i1.topLeft();
    cout << endl << "Top Left: (" << topLeft.x << "," << topLeft.y << ")." << endl;
    assert(topLeft.x == 1 && topLeft.y == 13);
    
    //test topLeft() with null values
    ScatterData<int> nothing;
    ScatterData<int>::Point topLeftNothing = nothing.topLeft();
    cout << "Top Left of nothing: (" << topLeftNothing.x << "," 
        << topLeftNothing.y << ")." << endl;
    assert(topLeftNothing.x == 0 && topLeftNothing.y == 0);
        
    //test bottomRight()
    ScatterData<int>::Point bottomRight = i1.bottomRight();
    cout << endl << "Bottom Right: (" << bottomRight.x << "," << bottomRight.y << ")." << endl;
    assert(bottomRight.x == 12 && bottomRight.y == 0);
    
    //test bottomRight()
    ScatterData<int>::Point bottomRightNothing = nothing.bottomRight();
    cout << "Bottom Right of nothing: (" << bottomRightNothing.x << "," 
        << bottomRightNothing.y << ")." << endl;
    assert(bottomRightNothing.x == 0 && bottomRightNothing.y == 0);
}

//test Concatenate
void TestConcatenate()
{
    //concatenate func
    cout << "i1: " << i1 << endl;
    cout << "i2: " << i2 << endl;
    ScatterData<int> i12 = i1 + i2;
    cout << "i1.i2: " << i12 << endl;
    
    //A+B
    ScatterData<int> one("[(0,1),(0,2),(0,3)]");
    ScatterData<int> two("[(3,4),(3,5),(3,6)]");
    ScatterData<int> onePlusTwo = one+two;
    cout << "one: " << one << endl;
    cout << "two: " << two << endl;
    cout << "onePlusTwo: " << onePlusTwo << endl;
    
    //A+=B
    cout << "one: " << one << endl;
    one += two;
    cout << "one += two: " << one << endl;
    
    //A+a
    ScatterData<int>::Point p1225(12,25);
    ScatterData<int> i1PlusP1225 = i1 + p1225;
    cout << "i1PlusP1225: " << i1PlusP1225 << endl;
    
    //a+A
    ScatterData<int> P1225Plusi1 = p1225 + i1;
    cout << "P1225Plusi1: " << P1225Plusi1 << endl;
    
    //A+=a
    cout << "i1: " << i1 << endl;
    i1 += p1225;
    cout << "i1 += p1225: " << i1 << endl;
}

//this function tests A[i]
void TestIthPoint()
{
    int i1NumElems = i1.count();
    cout << "i1: " << i1 << endl;
    
    //i=0
    ScatterData<int>::Point i1First = i1[0];
    cout << "first: (" << i1First.x << "," << i1First.y << ")" << endl;
    
    //i=numElems
    ScatterData<int>::Point i1OutOfBounds = i1[i1NumElems];
    cout << "out of bounds: (" << i1OutOfBounds.x << "," << i1OutOfBounds.y << ")" << endl;
    
    //i=numElems-1
    ScatterData<int>::Point i1Last = i1[i1NumElems-1];
    cout << "last: (" << i1Last.x << "," << i1Last.y << ")" << endl;
    
    //i=numElems/2
    ScatterData<int>::Point i1Middle = i1[(int)(i1NumElems/2)];
    cout << "middle: (" << i1Middle.x << "," << i1Middle.y << ")" << endl;
    
}

//this function tests the A == B function
void TestEqual()
{
    ScatterData<int> empty;
    ScatterData<int> one("[(1,2)]");
    ScatterData<int> twoA("[(1,2),(2,3)]");
    ScatterData<int> twoB("[(1,2),(2,4)]");
    ScatterData<int> threeA("[(1,2),(2,4),(1,2)]");
    ScatterData<int> threeB("[(2,4),(1,2),(1,2)]");
    ScatterData<int> threeC("[(1,2),(2,4),(1,2)]");
    
    bool works;
    
    //size compatibility
    works = empty == one;
    cout << empty << " == " << one << " " << works << endl;
    
    //different points
    works = twoA == twoB;
    cout << twoA << " == " << twoB << " " << works << endl;
    
    //different size, same points
    works = twoB == threeA;
    cout << twoB << " == " << threeA << " " << works << endl;
    
    //same size, same points, diff order
    works = threeA == threeB;
    cout << threeA << " == " << threeB << " " << works << endl;
    
    //same size, same points, same order
    works = threeA == threeC;
    cout << threeA << " == " << threeC << " " << works << endl;
    
}

//this functions tests the A!=B function
void TestNotEqual()
{
    ScatterData<int> empty;
    ScatterData<int> one("[(1,2)]");
    ScatterData<int> twoA("[(1,2),(2,3)]");
    ScatterData<int> twoB("[(1,2),(2,4)]");
    ScatterData<int> threeA("[(1,2),(2,4),(1,2)]");
    ScatterData<int> threeB("[(2,4),(1,2),(1,2)]");
    ScatterData<int> threeC("[(1,2),(2,4),(1,2)]");
    
    bool works;
    
    //size compatibility
    works = empty != one;
    cout << empty << " != " << one << " " << works << endl;
    
    //different points
    works = twoA != twoB;
    cout << twoA << " != " << twoB << " " << works << endl;
    
    //different size, same points
    works = twoB != threeA;
    cout << twoB << " != " << threeA << " " << works << endl;
    
    //same size, same points, diff order
    works = threeA != threeB;
    cout << threeA << " != " << threeB << " " << works << endl;
    
    //same size, same points, same order
    works = threeA != threeC;
    cout << threeA << " != " << threeC << " " << works << endl;
}

int main()
{  
    TestConstructors();
    TestInserts();
    TestCounts();
    TestAssignment();
    TestReadingInput();
    TestBoundingBox();
    TestConcatenate();
    TestIthPoint();
    TestEqual();
    TestNotEqual();
}