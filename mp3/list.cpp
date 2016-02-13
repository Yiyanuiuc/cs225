/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

#include "list.h"
#include <iostream>
using namespace std;

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
    if (length!=0) {
        while (head->next!=NULL) {
            ListNode * temp = head;
            head = head->next;
            head->prev = NULL;
            temp->next = NULL;
            delete temp;
            temp = NULL;
        }
        delete head;
        head = NULL;
    }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
    if (length!=0) {
        ListNode * temp = head;
        head = new ListNode(ndata);
        head->prev = NULL;
        head->next = temp;
        temp->prev = head;
        temp = NULL;
    }
    else {
        head = new ListNode(ndata);
        head->prev = NULL;
        head->next = NULL;
        tail = head;
    }
    length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    if (length!=0) {
        ListNode * temp = tail;
        tail = new ListNode(ndata);
        tail->next = NULL;
        tail->prev = temp;
        temp->next = tail;
        temp = NULL;
    }
    else {
        tail = new ListNode(ndata);
        tail->next = NULL;
        tail->prev = NULL;
        head = tail;
    }
    length++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1

    // When there are less than 2 Nodes
    if (startPoint == endPoint) return;

    // When there are more than 1 Nodes
    ListNode * tempStart = startPoint;
    ListNode * tempEnd = startPoint;

    ListNode * move = NULL;

    ListNode * beforeStart = NULL;
    if (startPoint->prev!=NULL) beforeStart = startPoint->prev;

    ListNode * afterEnd = NULL;
    if (endPoint->next!=NULL) afterEnd = endPoint->next;

    // When there are still more than 1 need to be moved
    while (tempEnd->next != endPoint) {
        // Mark the one to be moved
        move = tempEnd->next;  
        // Skip the marked one
        tempEnd->next = move->next;
        tempEnd->next->prev = tempEnd;
        // Modified the marked one
        move->prev = NULL;
        move->next = tempStart;
        tempStart->prev = move;
        // Renew the tempStart
        tempStart = move;
    }

    // When there is only 1 left
    // Mark the one to be moved
    move = tempEnd->next; 
    // Skip the marked one
    tempEnd->next = NULL;
    // Modified the marked one
    move->prev = NULL;
    move->next = tempStart;
    tempStart->prev = move;   
    // Renew the tempStart
    tempStart = move;
    // "The startPoint and endPoint pointers should point at the new start and end of the chain of linked memory."
    startPoint = tempStart;
    endPoint = tempEnd;
    move = NULL;

    // Modified two sides
    if (beforeStart != NULL) {
        startPoint->prev = beforeStart;
        beforeStart->next = startPoint;
        beforeStart = NULL;
    }
    else {
        startPoint->prev = NULL;
        head = startPoint;
    }
    if (afterEnd != NULL) {
        endPoint->next = afterEnd;
        afterEnd->prev = endPoint;
        afterEnd = NULL;
    }
    else {
        endPoint->next = NULL;
        tail = endPoint;
    }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
    if (n<=0) return;

    ListNode * startPoint = head;
    ListNode * endPoint = head;

    while (endPoint != tail) {
    
        for (int i=1; i<n; i++) {
            endPoint = endPoint->next;

            // "If the final block is not long enough to have nn elements, then just reverse what remains in the list. 
            // In particular, if nn is larger than the length of the list, this will do the same thing as reverse."
            if (endPoint == tail) {
                reverse(startPoint,endPoint);
                // Final cases
                startPoint = NULL;
                endPoint = NULL;
                return;
            }

        }
        reverse(startPoint,endPoint);
        
        startPoint = endPoint->next;
        endPoint = startPoint;
    }

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if (length==0) return;
    ListNode * startPoint = head;
    // There are at least 1 to move
    while (startPoint->next != NULL && startPoint->next->next!=NULL) {
        ListNode * move = startPoint->next;
        // Skip the moved one
        startPoint->next = move->next;
        startPoint->next->prev = startPoint;
        // Move it to the back
        tail->next = move;
        move->prev = tail;
        move->next = NULL;
        // Renew the startPoint & tail
        startPoint = startPoint->next;
        tail = move;
        move = NULL;
    }
    startPoint = NULL;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    return NULL; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    return NULL; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    return NULL; // change me!
}
