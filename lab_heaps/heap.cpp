/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

/**
 * Helper function that returns the root index of this heap.
 * Required for grading purposes! (This function should be
 * ridiculously easy: either return 0 if you plan to store the root
 * at index 0, or 1 if you plan on storing it at index 1).
 *
 * @return The index of the root node of the heap.
 */
template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

/**
 * Helper function that returns the index of the left child of a
 * node in the heap. Required for grading purposes! (And it should
 * be useful to you as well).
 *
 * @param currentIdx The index of the current node.
 * @return The index of the left child of the current node.
 */
template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    if (2*currentIdx<=size) return 2*currentIdx;
    // if DNE
    else return -1;
}

/**
 * Helper function that returns the index of the right child of a
 * node in the heap. Required for grading purposes! (And it should
 * be useful to you as well).
 *
 * @param currentIdx The index of the current node.
 * @return The index of the right child of the current node.
 */
template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    if (2*currentIdx+1<=size) return 2*currentIdx+1;
    // if DNE
    else return -1;
}

/**
 * Helper function that returns the index of the parent of a node
 * in the heap.
 *
 * @param currentIdx The index of the current node.
 * @return The index of the parent of the current node.
 */
template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    if (currentIdx<=1) return 1;
    else return currentIdx/2;
}

/**
 * Helper function that determines whether a given node has a
 * child.
 *
 * @param currentIdx The index of the current node.
 * @return A boolean indicating whether the current node has a
 *  child or not.
 */
template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    if (2*currentIdx <= size) return true;
    else return false;
}

/**
 * Helper function that returns the index of the child with the
 * highest priority as defined by the higherPriority() functor.
 *
 * For example, if T == int and the left child of the current node
 * has data 5 and the right child of the current node has data 9,
 * this function should return the index of the left child (because
 * the default higherPriority() behaves like operator<).
 *
 * This function assumes that the current node has children.
 *
 * @param currentIdx The index of the current node.
 * @return The index of the highest priority child of this node.
 */
template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if (2*currentIdx==size) return 2*currentIdx;
    else if (higherPriority(_elems[2*currentIdx],_elems[2*currentIdx+1])) 
        return 2*currentIdx;
    else return 2*currentIdx+1;
}

/**
 * Helper function that restores the heap property by sinking a
 * node down the tree as necessary.
 *
 * @param currentIdx The index of the current node that is being
 *  sunk down the tree.
 */
template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
    if (hasAChild(currentIdx)) {
        size_t minChildIndex = maxPriorityChild(currentIdx);
        if (higherPriority(_elems[minChildIndex], _elems[currentIdx])) {
            std::swap(_elems[currentIdx], _elems[minChildIndex]);
            heapifyDown(minChildIndex);
        }
    }
}

/**
 * Helper function that restores the heap property by bubbling a
 * node up the tree as necessary.
 *
 * @param currentIdx The index of the current node that is being
 *  bubbled up the tree.
 */
template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

/**
 * Constructs an empty heap.
 */
template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
    size = 0;
}

/**
 * Constructs a heap from a vector of elements by copying the
 * elements into the heap's storage and then running the buildHeap
 * algorithm.
 *
 * @param elems The elements that should be placed in the heap.
 */
template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    size = elems.size();
    // add items to _elems
    for (size_t i=0; i<size; i++) 
        _elems.push_back(elems[i]);
    //std::cout << "size= " << size << " ";
    //std::cout << "_elems.size()= " << _elems.size() << std::endl;
    for (size_t i=parent(size); i>0; i--)
        heapifyDown(i);
}

/**
 * Removes the element with highest priority according to the
 * higherPriority() functor.
 *
 * @return The element with highest priority in the heap.
 */
template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
    if (empty()) return T();
    else {
        std::swap(_elems[1], _elems[size]);
        T temp = _elems[size];
        size--;
        _elems.pop_back();
        heapifyDown(1);
        return temp;
    }
}

/**
 * Returns, but does not remove, the element with highest priority.
 *
 * @return The highest priority element in the entire heap.
 */
template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    if (empty()) return T();
    else return _elems[root()];
}

/**
 * Inserts the given element into the heap, restoring the heap
 * property after the insert as appropriate.
 *
 * @param elem The element to be inserted.
 */
template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
    _elems.push_back(elem);
    size++;
    heapifyUp(size);
}

/**
 * Determines if the given heap is empty.
 *
 * @return Whether or not there are elements in the heap.
 */
template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return _elems.size()==1;
}
