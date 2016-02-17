#include "list.h"
#include "blockpng.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

List<RGBAPixel> imageToList(PNG const& img, bool reverse = false)
{
    List<RGBAPixel> list;
    for (size_t i = 0; i < img.width(); i++) {
        for (size_t j = 0; j < img.height(); j++) {
            if (reverse)
                list.insertFront(*img(i, j));
            else
                list.insertBack(*img(i, j));
        }
    }
    return list;
}

BlockPNG listToImage(List<RGBAPixel> const& list, int width, int height)
{
    BlockPNG ret;
    ret.resize(width, height);
    vector<RGBAPixel> v(list.begin(), list.end());
    int x = 0;
    int y = 0;
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
}

void testInserts()
{
    cout << "Hi! I'm your friendly `" __FILE__ "`. You should edit me to enable the insertion tests." << endl;
    cout << endl;
    cout << "Guess what? You can also add your own!" << endl;
    cout << endl;
    cout << "Most of the tests for this MP use images, and those can be hard to debug." << endl;
    cout << "You should add some tests that use integer lists!" << endl;
    cout << endl;
    cout << "Start by uncommenting lines " << (__LINE__ + 3) << " through " << (__LINE__ + 26) << "." << endl;

    /* uncomment the below */
    
    cout << "[main]: " << __func__ << "()" << endl;
    List<int> list;

    // test insertFront
    for (size_t i = 1; i <= 10; i++)
        list.insertFront(i);

    cout << "[testInserts]: " << list << endl;
    cout << "[testInserts]: size: " << list.size() << endl;
    if (list.size() != 10)
        cout << "[testInserts]: Incorrect size" << endl;

    List<int> list2;

    // test insertBack
    for (size_t i = 1; i <= 10; i++)
        list2.insertBack(i);

    cout << "[testInserts]: " << list2 << endl;
    cout << "[testInserts]: size: " << list2.size() << endl;
    if (list2.size() != 10)
        cout << "[testInserts]: Incorrect size" << endl;
}

void testReverse()
{
    cout << "[main]: " << __func__ << "()" << endl;
    PNG in("in_02.png");

    List<RGBAPixel> list = imageToList(in);
    list.reverse();

    PNG out = listToImage(list, in.width(), in.height());
    out.writeToFile("reverse.png");

    checkSoln(__func__, out, "soln_reverse.png");
}

void testReverseNth()
{
    cout << "[main]: " << __func__ << "()" << endl;
    PNG in("in_03.png");

    List<RGBAPixel> list = imageToList(in);
    list.reverseNth(in.height() * 20);

    PNG out = listToImage(list, in.width(), in.height());
    out.writeToFile("reverseNth_01.png");

    checkSoln(__func__, out, "soln_reverseNth_01.png");

    in.readFromFile("in_04.png");
    list = imageToList(in);
    list.reverseNth(in.height() * 61);
    out = listToImage(list, in.width(), in.height());
    out.writeToFile("reverseNth_02.png");

    checkSoln(__func__, out, "soln_reverseNth_02.png");
}

void testWaterfall()
{
    cout << "[main]: " << __func__ << "()" << endl;
    PNG in("in_05.png");

    List<RGBAPixel> list = imageToList(in);
    list.waterfall();

    PNG out = listToImage(list, in.width(), in.height());
    out.writeToFile("waterfall_01.png");

    checkSoln(__func__, out, "soln_waterfall_01.png");

    in.readFromFile("in_06.png");
    list = imageToList(in);
    list.waterfall();
    out = listToImage(list, in.width(), in.height());
    out.writeToFile("waterfall_02.png");

    checkSoln(__func__, out, "soln_waterfall_02.png");
}

void testSplit()
{
    cout << "[main]: " << __func__ << "()" << endl;

    PNG in("in_07.png");
    List<RGBAPixel> list1;
    for (size_t i = 0; i < in.width(); i++)
        for (size_t j = 0; j < in.height(); j++)
            list1.insertBack(*in(i, j));
    List<RGBAPixel> list2 = list1.split(400 * 240);
    List<RGBAPixel> list3 = list2.split(400 * 240);

    vector<RGBAPixel> im1vect(list1.begin(), list1.end());
    vector<RGBAPixel> im2vect(list2.begin(), list2.end());
    vector<RGBAPixel> im3vect(list3.begin(), list3.end());

    PNG out1(400, 240);
    int x = 0;
    for (size_t i = 0; i < im1vect.size(); i++) {
        int y = i % 240;
        *out1(x, y) = im1vect[i];
        if (y == 239)
            x++;
    }
    out1.writeToFile("split_01.png");
    checkSoln(__func__, out1, "soln_split_01.png");

    PNG out2(400, 240);
    x = 0;
    for (size_t i = 0; i < im2vect.size(); i++) {
        int y = i % 240;
        *out2(x, y) = im2vect[i];
        if (y == 239)
            x++;
    }
    out2.writeToFile("split_02.png");
    checkSoln(__func__, out2, "soln_split_02.png");

    PNG out3(400, 240);
    x = 0;
    for (size_t i = 0; i < im3vect.size(); i++) {
        int y = i % 240;
        *out3(x, y) = im3vect[i];
        if (y == 239)
            x++;
    }
    out3.writeToFile("split_03.png");
    checkSoln(__func__, out3, "soln_split_03.png");
}

void testMerge()
{
    cout << "[main]: " << __func__ << "()" << endl;

    PNG im1("in_08.png");
    PNG im2("in_09.png");
    PNG out(600, 400);

    vector<RGBAPixel> v1;
    for (size_t i = 0; i < im1.width(); i++)
        for (size_t j = 0; j < im1.height(); j++)
            v1.push_back(*im1(i, j));
    vector<RGBAPixel> v2;
    for (size_t i = 0; i < im2.width(); i++)
        for (size_t j = 0; j < im2.height(); j++)
            v2.push_back(*im2(i, j));
    List<RGBAPixel> l1(v1.begin(), v1.end());
    List<RGBAPixel> l2(v2.begin(), v2.end());
    l1.mergeWith(l2);
    vector<RGBAPixel> merged(l1.begin(), l1.end());
    int x = 0;
    for (size_t i = 0; i < merged.size(); i++) {
        int y = i % 400;
        *out(x, y) = merged[i];
        if (y == 399)
            x++;
    }
    out.writeToFile("merge.png");

    checkSoln(__func__, out, "soln_merge.png");
}

inline vector<int> buildVector(BlockPNG const& b, int d)
{
    vector<int> v;
    for (size_t i = 1; i <= (b.width() * b.height()) / (d * d); i++)
        v.push_back(i);

    return v;
}

void testSort()
{
    cout << "[main]: " << __func__ << "()" << endl;

    srand(225);

    // read in image to be shuffled
    BlockPNG b;
    b.readFromFile("in_01.png");

    int d = 60;
    vector<int> v = buildVector(b, d);
    random_shuffle(v.begin(), v.end());

    // generate shuffled image (done for you already)
    //PNG b2 = b.genImg(v, d);
    //b2.writeToFile("in_01_shuffled_60.png");

    // make list and sort it
    List<int> img_srt(v.begin(), v.end());
    img_srt.sort();

    // vectorize and rebuild image
    vector<int> v2(img_srt.begin(), img_srt.end());

    PNG b3 = b.genImg(v2, d);
    b3.writeToFile("unshuffled_60.png");

    checkSoln("testSort", b3, "in_01.png");

    d = 1;
    v = buildVector(b, d);
    random_shuffle(v.begin(), v.end());

    //PNG q = b.genImg(v, d);
    //q.writeToFile("in_01_shuffled_1.png");

    List<int> q_srt(v.begin(), v.end());
    q_srt.sort();

    v2 = vector<int>(q_srt.begin(), q_srt.end());

    b3 = b.genImg(v2, d);
    b3.writeToFile("unshuffled_1.png");

    checkSoln("testSort", b3, "in_01.png");
}

void testMP31()
{
    testInserts();
    testReverse();
    testReverseNth();
    testWaterfall();
}

void testMP32()
{
    testSplit();
    testMerge();
    testSort();
}

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    if (argc == 1 || args[1] == "all") {
        testMP31();
        testMP32();
    } else {
        if (args[1] == "mp3.1" || args[1] == "mp31")
            testMP31();
        else if (args[1] == "mp3.2" || args[1] == "mp32")
            testMP32();
        else if (args[1] == "inserts")
            testInserts();
        else if (args[1] == "reverse") {
            testReverse();
            testReverseNth();
        } else if (args[1] == "waterfall" || args[1] == "waterFall")
            testWaterfall();
        else if (args[1] == "split")
            testSplit();
        else if (args[1] == "merge")
            testMerge();
        else if (args[1] == "sort" || args[1] == "mergesort"
                 || args[1] == "mergeSort")
            testSort();
    }

    return 0;
}

// int main() {

//     List<int> syTestList;
//     List<int> syTestListEmpty;

//     cout << "# Begin Test [mp3] By SuY #" << endl;
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
//     List<int> syTestListLength1;
//     cout << "===Test: reverse===" << endl;
//     cout << "Test 1 : Empty list" << endl;
//     syTestListEmpty.reverse();
//     cout << "Test 2 : Normal value" << endl;
//     syTestList.reverse();
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 9 8 7 6 5 4 3 2 1 >" << endl;
//     cout << "Length : " << syTestList.size() << endl;
//     cout << "Correct: 9" << endl;
//     cout << "Test 3 : Extreme value" << endl;
//     syTestListLength1.insertFront(0);
//     syTestListLength1.reverse();
//     cout << "After  : " << syTestListLength1 << endl;
//     cout << "Correct: < 0 >" << endl;
//     cout << "Length : " << syTestListLength1.size() << endl;
//     cout << "Correct: 1" << endl;

//     // Test: reverseNth
//     cout << "===Test: reverseNth===" << endl;
//     cout << "Test 1 : N = 3" << endl;
//     syTestList.reverseNth(3);
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 7 8 9 4 5 6 1 2 3 >" << endl;
//     cout << "length : " << syTestList.size() << endl;
//     cout << "Correct: 9" << endl;
//     cout << "Test 2 : N = 4" << endl;
//     syTestList.reverseNth(4);
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 4 9 8 7 2 1 6 5 3 >" << endl;
//     cout << "length : " << syTestList.size() << endl;
//     cout << "Correct: 9" << endl;
//     cout << "Test 3 : N = 1" << endl;
//     syTestList.reverseNth(1);
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 4 9 8 7 2 1 6 5 3 >" << endl;
//     cout << "length : " << syTestList.size() << endl;
//     cout << "Correct: 9" << endl;
//     cout << "Test 4 : N = 0" << endl;
//     syTestList.reverseNth(0);
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 4 9 8 7 2 1 6 5 3 >" << endl;
//     cout << "length : " << syTestList.size() << endl;
//     cout << "Correct: 9" << endl;
//     cout << "Test 5 : Empty list" << endl;
//     syTestListEmpty.reverseNth(5);

//     // Test: waterfall
//     cout << "===Test: waterfall===" << endl;
//     cout << "Test 1 : Empty list" << endl;
//     syTestListEmpty.waterfall();
//     cout << "Test 2 : Normal value" << endl;
//     syTestList.waterfall();
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 4 8 2 6 3 7 5 1 9 >" << endl;
//     cout << "length : " << syTestList.size() << endl;
//     cout << "Correct: 9" << endl;    

//     // Test: split & mergesort
//     List<int> syTestSplit;
//     cout << "===Test: split===" << endl;

//     cout << "Test 1 : splitPoint too small" << endl;
//     syTestSplit = syTestList.split(0);
//     cout << "After 1: " << syTestList << endl;
//     cout << "After 2: " << syTestSplit << endl;
//     cout << "Correct: < 4 8 2 6 3 7 5 1 9 >" << endl;
//     syTestList = syTestSplit;

//     cout << "Test 2 : splitPoint too big" << endl;
//     syTestSplit = syTestList.split(10);
//     cout << "After 1: " << syTestList << endl;
//     cout << "Correct: < 4 8 2 6 3 7 5 1 9 >" << endl;
//     cout << "After 2: " << syTestSplit << endl;

//     cout << "Test 3 : Normal value" << endl;
//     syTestSplit = syTestList.split(8);
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 4 8 2 6 3 7 5 1 >" << endl;
//     cout << "length : " << syTestList.size() << endl;
//     cout << "Correct: 8" << endl;   
//     cout << "After  : " << syTestSplit << endl;
//     cout << "Correct: < 9 >" << endl;
//     cout << "length : " << syTestSplit.size() << endl;
//     cout << "Correct: 1" << endl; 


//     // Test: mergesort
//     cout << "===Test: mergesort===" << endl;
//     cout << "Test 1 : Empty list" << endl;
//     syTestListEmpty.sort();
//     cout << "Test 2 : Normal case" << endl;
//     syTestList.sort();
//     cout << "After  : " << syTestList << endl;
//     cout << "Correct: < 1 2 3 4 5 6 7 8 >" << endl;

//     return 0; 
// }

