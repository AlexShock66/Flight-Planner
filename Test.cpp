//
// Created by Alex Shockley on 9/17/2020.
//

//
// Created by Alex Shockley on 9/15/2020.
//
#include "Stack.h"
#include <iostream>
#include "catch.hpp"
#include "SString.h"
#include "cstring"
#include "DSList.h"
#include "DSVector.h"
#include "AList.h"
using namespace std;
TEST_CASE("SString test file") {
    SString a = SString("Yes");
    SString b = SString();
    SString c = SString("Multi Words");
    SString d = SString("For some reason this works?");

    SECTION("Testting get data function...") {
        CHECK(strcmp(a.getData(), "Yes") == 0);
        CHECK(strcmp(b.getData(), "\0") == 0);
        CHECK(strcmp(c.getData(), "Multi Words") == 0);
    }
    SECTION("Testing .contains function") {
        CHECK(a.contains("Yes"));
        CHECK(c.contains("Words"));
        CHECK(c.contains("Word"));

    }
    SECTION("Testing wordAt function") {
        CHECK(strcmp(a.wordAt(0).getData(),  "Yes") == 0);
        CHECK(strcmp(c.wordAt(1).getData(),"Words") == 0);
        CHECK(strcmp(c.wordAt(0).getData(), "Multi") == 0);
       // CHECK(strcmp(d.wordAt(2).getData(),"reason") == 0);
        cout << c.wordAt(0).getData() <<endl;
        cout << d.wordAt(2).getData() <<endl;

    }
    SECTION("Testing set string function") {
        b.setString("New String");
        c.setString("Single Word");
        CHECK(strcmp(b.getData(), "New String") == 0);
        CHECK(strcmp(c.getData(), "Single Word") == 0);
    }
    SECTION("Testing = operator") {
        b = c;
        CHECK(strcmp(b.getData(), "Multi Words") == 0);
        b = a;
        CHECK(strcmp(b.getData(), "Yes") == 0);
        CHECK(strcmp(c.getData(),"Multi Words") == 0);

    }
    SECTION("Testing GetNumWords function") {
        b.setString("This string has 5 words");
        CHECK(b.getNumWords() == 5);
        CHECK(a.getNumWords() == 1);
        CHECK(c.getNumWords() == 2);
    }
    SECTION("testing remove punct function") {
        a.setString("Data!!!!");
        b.setString("Yes");
        c.setString("Structures is cool yes ()!!");
        a.removePunct();
        b.removePunct();
        c.removePunct();
        CHECK(strcmp(a.getData(),"Data") == 0);
        CHECK(strcmp(b.getData(),"Yes") == 0);
        CHECK(strcmp(c.getData(),"Structures is cool yes ") == 0);
    }
    SECTION("Testing to upper and to lower") {
        a.setString("tHiS sTrIng iS bAd");
        a.toLower();
        CHECK(strcmp(a.getData(), "this string is bad") == 0);
        cout << a.getData() <<endl;
        a.toUpper();
        CHECK(strcmp(a.getData(),"THIS STRING IS BAD") == 0);
        cout << a.getData() <<endl;
    }
    SECTION("moveBetweenToFront function") {
        a.setString("[b+ tree](tree)");
        b.setString("[hopefully this](it did)");
        a.moveWordBetweenToFront('(',')');
        b.moveWordBetweenToFront('(',')');
        CHECK(strcmp(a.getData(),"(tree)[b+ tree]") == 0);
        cout <<"a: " << a.getData() <<endl;
        CHECK(strcmp(b.getData(),"(it did)[hopefully this]") == 0);
        cout <<"b: " << b.getData() <<endl;
    }
    SECTION("Testing += function") {
        a.setString("I");
        a+= " love";
        a+= " data";
        a+= " structures!";
        CHECK(strcmp(a.getData(), "I love data structures!") == 0);

    }
    SECTION("Testing remove char function") {
        a.setString("[b+ tree](tree)");
        a.removeChar('[');
        b.setString("[b+ tree](tree)");
        b.removeChar(']');
        CHECK(strcmp(a.getData(), "b+ tree](tree)") == 0);
        CHECK(strcmp(b.getData(), "[b+ tree(tree)") == 0);
        CHECK(b.getSize() == 15);
        CHECK(a.getSize() == 15);
        cout << b.getData() <<endl;
    }
    SECTION("Testing remove until function") {
        a.setString("tree)b+ tree");
        a.removeUntil(')');
        CHECK(strcmp(a.getData(),"b+ tree") == 0);
        CHECK(a.getSize() == 7);
        cout << a.getData() <<endl;
    }
}
TEST_CASE("DSList testing") {
    DSList<int> a = DSList<int>();
    DSList<SString> b = DSList<SString>();
    DSList<SString *> c = DSList<SString *>();
    SECTION("Testing push_back Function AND overloaded [] operator") {
        a.push_back(2);
        a.push_back(5);

        a.push_back(65);
        a.push_back(25);
        b.push_back(SString("Test"));
        c.push_back(new SString("Test2"));

        CHECK(a[0] == 2);
        CHECK(a[1] == 5);
        CHECK(strcmp(b[0].getData(), "Test") == 0 );
        CHECK(strcmp(c[0]->getData(), "Test2") == 0);
        CHECK(a[3] == 25);

    }
    SECTION("Testing getSize function") {
        a.push_back(45);
        a.push_back(45);
        a.push_back(45);
        a.push_back(45);
        a.push_back(45);
        a.push_back(45);
        CHECK(a.getSize() == 6);
    }
    SECTION("Testing Pop Front function") {
        a.push_back(45);
        a.push_back(55);
        CHECK(a.getSize() == 2);
        a.pop_Front();
        CHECK(a.getSize() == 1);
        CHECK(a[0] == 55);

    }
    SECTION("Testing delete at index") {
        a.push_back(15);
        a.push_back(25);
        a.push_back(35);
        a.push_back(45);
        a.deleteAtIndex(2);
        CHECK(a[2] == 45);
        a.deleteAtIndex(0);
        //a.deleteAtIndex(2);
        CHECK(a[0] == 25);

    }
    SECTION("Testing pop back function") {
        a.push_back(15);
        a.push_back(25);
        a.push_back(35);
        a.push_back(45);
        a.pop_Back();
        CHECK(a.getSize() == 3);
        CHECK(a[2] == 35);
        CHECK(a[3] == 15);
    }
    SECTION("Testing overloaded = operator") {
        DSList<int> test;
        a.push_back(15);
        a.push_back(25);
        a.push_back(35);
        a.push_back(45);
        test = a;
        CHECK(a[0] == test[0]);
        CHECK(a[1] == test[1]);
        CHECK(a[2] == test[2]);
        CHECK(a[3] == test[3]);
        CHECK(test.getSize() == a.getSize());


    }
    SECTION("Testing sort function") {
        a.push_back(15);
        a.push_back(95);
        a.push_back(75);
        a.push_back(45);
        a.push_back(25);
        a.push_back(57);
        a.push_back(68);
        a.push_back(40);
        a.print();
        a.sort();
        CHECK(a[0] == 15);
        CHECK(a[7] == 95);
        for(int i = 0; i < a.getSize(); i ++) {
            cout << a[i] <<endl;
        }
    }
    SECTION("testing iterator") {
        DSList<int> test5;
        for(int i = 0; i < 5; i ++) {
            test5.push_back(i);
        }

        for(int j = 0; j < test5.getSize(); j++) {
            CHECK(test5.getNext() == test5[j]);
            test5.moveItr();
        }

    }

}
TEST_CASE("Testing DSVector class") {
    DSVector<int> a;
    DSVector<int*> b;
    DSVector<SString> c;
    DSVector<SString*> d;

    SECTION("Testing pushback function AND overloaded[]") {
        a.push_Back(0);
        a.push_Back(1);
        a.push_Back(2);
        a.push_Back(3);
        a.push_Back(4);
        a.push_Back(5);
        a.push_Back(6);
        a.push_Back(7);
        a.push_Back(8);
        a.push_Back(9);
        a.push_Back(10);
        a.push_Back(11);
        CHECK(a[11] == 11);
        CHECK(a[4] == 4);
        CHECK(a[0] == 0);
        CHECK(a.getMaxSize() == 20);
        CHECK(a.getCurrSize() == 12);
        CHECK(a[500] == 0);

    }
    SECTION("Testing sort function") {
        a.push_Back(34);
        a.push_Back(67);
        a.push_Back(7);
        a.push_Back(45);
        a.push_Back(1);
        a.push_Back(34);
        a.push_Back(80);
        a.push_Back(78);
        a.push_Back(4);
        a.push_Back(54);
        a.push_Back(14);
        a.push_Back(13);
        a.sort();
        CHECK(a[0] == 1);
        for(int i = 0; i < a.getCurrSize(); i ++) {
            cout << a[i] << endl;
        }
        c.push_Back(SString("H"));
        c.push_Back(SString("Hello"));
        c.push_Back(SString("Hel"));
        c.push_Back(SString("Hell"));
        c.push_Back(SString("He"));
        c.sort();
        for(int i = 0; i < c.getCurrSize(); i ++) {
            cout << c[i].getData() << endl;
        }
        DSVector<pair<SString,int>> f;
        pair<SString,int> test;
        for(int i = 0; i < 5; i ++) {
            test.first = c[i];
            test.second = i;
            f.push_Back(test);
        }
        f.sort();
        for(int i = 0; i < 5; i ++) {
            cout << f[i].first.getData() <<", " <<f[i].second <<endl;
        }

    }
    SECTION("Testing remove at index function") {
        a.push_Back(34);
        a.push_Back(67);
        a.push_Back(7);
        a.push_Back(45);
        a.push_Back(1);
        a.push_Back(34);
        a.push_Back(80);
        a.push_Back(78);
        a.push_Back(4);
        a.push_Back(54);
        a.push_Back(14);
        a.push_Back(13);
        a.removeAtIndex(1);
        CHECK(a[1] == 7);
        CHECK(a[10] == 13);
        CHECK(a.getCurrSize() == 11);
        a.print();
    }
    SECTION("Testing swap function") {
        a.push_Back(45);
        a.push_Back(15);
        a.push_Back(25);
        a.push_Back(35);
        a.swap(0,1);
        CHECK(a[0] == 15);
        CHECK(a[1] == 45);
        a.swap(0,a.getCurrSize() - 1);
        CHECK(a[0] == 35);
        CHECK(a[3] == 15);
    }
}
TEST_CASE("TESTING ALIST FUNCTIONS") {
    AList<double> a;
    AList<SString> b;
    a.pushMain(0);
    a.pushMain(2);
    a.pushMain(4);
    a.pushAdj(0,0.1);
    a.pushAdj(0,0.2);
    a.pushAdj(2,2.1);
    a.pushAdj(4,4.1);
    a.pushAdj(4,4.2);
    a.pushAdj(4,4.3);
    SECTION("Testing getadjNodes") {
        a.moveItr(0);
        CHECK(a.getAdjNodes(0).getNext() == 0.2);
        CHECK(a.getAdjNodes(0)[0] == 0.1);
    }
    SECTION("Testing find function") {
        CHECK(a.getSize() == 3);
        CHECK(a.find(2) == 1);
        CHECK(a.getMainNode(0) == 0);
    }
    a.printList();
}
TEST_CASE("TESTING STACK FUNCTIONS") {
    Stack<int> a;
    Stack<SString> b;
    Stack<int*> c;
    CHECK(a.isEmpty());
    a.push(0);
    a.push(1);
    a.push(2);
    a.push(3);
    b.push(SString("test"));
    b.push(SString("Nexy"));
    b.push(SString("Yes"));
    c.push(new int(5));
    c.push(new int(4));
    c.push(new int(3));
    SECTION("Testing pop function") {
        CHECK(a.pop() == 3);
        CHECK(a.pop() == 2);
        CHECK(b.pop() == SString("Yes"));
        CHECK(*c.pop() == 3);
    }
    SECTION("Testing peek") {
        CHECK(a.peek() == 3);
        CHECK(a.peek() == 3);
        CHECK(*c.peek() == 3);
        CHECK(b.peek() == SString("Yes"));
    }
    SECTION("Testing contains function") {
        CHECK(a.contains(2));
        CHECK(!a.contains(45));
        CHECK(a.getSize() == 4);
    }

}