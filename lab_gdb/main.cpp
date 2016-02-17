#include "list.h"
#include "blockpng.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

List<RGBAPixel> imageToList(PNG const& img)
{
    List<RGBAPixel> list;
    for (size_t i = 0; i < img.width(); i++) {
        for (size_t j = 0; j < img.height(); j++) {
            list.insertFront(*img(i, j));
        }
    }
    return list;
}

BlockPNG listToImage(List<RGBAPixel> const& list, size_t width, size_t height)
{
    BlockPNG ret;
    ret.resize(width, height);
    vector<RGBAPixel> v(list.begin(), list.end());
    size_t x = 0;
    size_t y = 0;
    for (size_t i = 0; i < v.size(); i++) {
        *ret(x, y) = v[i];
        y++;
        if (y == height) {
            y = 0;
            x++;
        }
    }
    return ret;
}

void checkSoln(string test, PNG out, string soln_file)
{
    PNG soln;
    soln.readFromFile(soln_file.c_str());

    if (!(soln == out))
        cerr << "[" << test << "]: Image does not match " << soln_file << endl;
    else
        cout << "[" << test << "]: Images match!" << endl;
}

void testInsertFront()
{
    cout << "[main]: " << __func__ << "()" << endl;

    // test insertFront
    List<int> list;
    for (int i = 1; i <= 10; i++)
        list.insertFront(i);

    cout << "[testInsertFront]: " << list << endl;
    cout << "[testInsertFront]: size: " << list.size() << endl;
    if (list.size() != 10)
        cout << "[testInsertFront]: Incorrect size" << endl;
}

void testInsertBack()
{
    cout << "[main]: " << __func__ << "()" << endl;

    // test insertBack
    List<int> list;
    for (int i = 1; i <= 10; i++)
        list.insertBack(i);

    cout << "[testInserts]: " << list << endl;
    cout << "[testInserts]: size: " << list.size() << endl;
    if (list.size() != 10)
        cout << "[testInserts]: Incorrect size" << endl;
}

void testReverse()
{
    cout << "[main]: " << __func__ << "()" << endl;
    PNG in("in.png");

    List<RGBAPixel> list = imageToList(in);
    list.reverse();

    PNG out = listToImage(list, in.width(), in.height());
    out.writeToFile("reverse.png");

    checkSoln(__func__, out, "soln_reverse.png");
}

void testShuffle()
{
    cout << "[main]: " << __func__ << "()" << endl;

    List<int> list;
    for (int i = 10; i > 0; i--)
        list.insertFront(i);
    cout << "[testShuffle]: before " << list << endl;
    list.shuffle();
    cout << "[testShuffle]: after " << list << endl;
}

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    if (argc == 1 || args[1] == "all") {
        testInsertFront();
        testInsertBack();
        testReverse();
        testShuffle();
    } else {
        if (args[1] == "front")
            testInsertFront();
        else if (args[1] == "back")
            testInsertBack();
        else if (args[1] == "reverse")
            testReverse();
        else if (args[1] == "shuffle")
            testShuffle();
    }

    return 0;
}

// int main() {

//     List<int> syTestList;
//     List<int> syTestListEmpty;

//     cout << "# Begin Test [lab_gdb] By SuY #" << endl;
//     // Test: insertFront
//     cout << "===Test: insertFront===" << endl;
//     for (int i=6; i>0; i--) {
//         syTestList.insertFront(i);
//     }
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 1 2 3 4 5 6 >" << endl;
//     cout << "Length : " << syTestList.size() << endl;
//     cout << "Correct: 6" << endl;

//     // Test: insertBack
//     cout << "===Test: insertBack===" << endl;
//     for (int i=7; i<=9; i++) {
//         syTestList.insertBack(i);
//     }
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 1 2 3 4 5 6 7 8 9 >" << endl;
//     cout << "Length : " << syTestList.size() << endl;
//     cout << "Correct: 9" << endl;

//     // Test: reverse
//     cout << "===Test: reverse===" << endl;
//     cout << "Test 1 : Empty list" << endl;
//     syTestListEmpty.reverse();
//     cout << "Test 2 : Normal value" << endl;
//     syTestList.reverse();
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 9 8 7 6 5 4 3 2 1 >" << endl;
//     cout << "Length : " << syTestList.size() << endl;
//     cout << "Correct: 9" << endl;

//     // Test: shuffle
//     cout << "===Test: shuffle===" << endl;
//     cout << "Test 1 : Empty list" << endl;
//     syTestListEmpty.shuffle();
//     cout << "Test 2 : Normal value" << endl;
//     syTestList.shuffle();
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 9 4 8 3 7 2 6 1 5 >" << endl;
//     cout << "length : " << syTestList.size() << endl;
//     cout << "Correct: 9" << endl;

//     return 0;
// }
