#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cassert>

template <class dataType>
class Array {
public:
    static const int minCap = 4; // Default capacity of an array object

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: Array (constructor)
    //   Description:    Initializes an Array object with the given capacity.
    //   Parameters:     arraySize - capacity of the array (input)
    //   Return Value:   None
    //
    ////////////////////////////////////////////////////////////////////////
    Array(int arraySize = minCap);

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: Array (constructor from dataType array)
    //   Description:    Initializes an Array object with data copied from a dataType array.
    //   Parameters:     A - dataType array to copy from (input)
    //                   num - number of elements to copy (input)
    //   Return Value:   None
    //
    ////////////////////////////////////////////////////////////////////////
    Array(const dataType A[], int num);

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: Array (copy constructor)
    //   Description:    Initializes an Array object by copying from another Array object.
    //   Parameters:     A - Array object to copy from (input)
    //   Return Value:   None
    //
    ////////////////////////////////////////////////////////////////////////
    Array(const Array&);

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: ~Array (destructor)
    //   Description:    Destroys the Array object and reclaims allocated memory.
    //   Parameters:     None
    //   Return Value:   None
    //
    ////////////////////////////////////////////////////////////////////////
    ~Array();

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: getCapacity
    //   Description:    Returns the capacity of the Array object.
    //   Parameters:     None
    //   Return Value:   Capacity of the array (int)
    //
    ////////////////////////////////////////////////////////////////////////
    int getCapacity() const { return capacity; }

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: getNumUsed
    //   Description:    Returns the number of elements in use in the Array object.
    //   Parameters:     None
    //   Return Value:   Number of used elements (int)
    //
    ////////////////////////////////////////////////////////////////////////
    int getNumUsed() const { return numUsed; }

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: operator=
    //   Description:    Assignment operator to copy contents from another Array object.
    //   Parameters:     right - Array object to copy from (input)
    //   Return Value:   Reference to the updated Array object (Array&)
    //
    ////////////////////////////////////////////////////////////////////////
    Array<dataType>& operator=(const Array&);

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: operator[]
    //   Description:    Non-const subscript operator to access and modify elements.
    //   Parameters:     subscript - index of the element to access/modify (input)
    //   Return Value:   Reference to the accessed/modified element (dataType&)
    //
    ////////////////////////////////////////////////////////////////////////
    dataType& operator[](int subscript);

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: operator[]
    //   Description:    Const subscript operator to access elements.
    //   Parameters:     subscript - index of the element to access (input)
    //   Return Value:   Const reference to the accessed element (const dataType&)
    //
    ////////////////////////////////////////////////////////////////////////
    const dataType& operator[](int subscript) const;

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: operator+=
    //   Description:    Operator to append an element to the Array object.
    //   Parameters:     element - element to be appended (input)
    //   Return Value:   Reference to the updated Array object (Array&)
    //
    ////////////////////////////////////////////////////////////////////////
    Array<dataType>& operator+=(const dataType&);

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: operator*
    //   Description:    Dereference operator to access the first element.
    //   Parameters:     None
    //   Return Value:   Value of the first element (dataType)
    //
    ////////////////////////////////////////////////////////////////////////
    dataType operator*() const;

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: operator<< (stream output)
    //   Description:    Overloaded output stream operator to display Array object contents.
    //   Parameters:     output - output stream object (output)
    //                   A - Array object to display (input)
    //   Return Value:   output stream object (ostream&)
    //
    ////////////////////////////////////////////////////////////////////////
    friend std::ostream& operator<<(std::ostream& output, const Array<dataType>& A) {
        output << "[ ";
        for (int i = 0; i < A.getNumUsed(); ++i) {
            if (i != 0) {
                output << ", ";
            }
            output << A[i];
        }
        output << " ]";
        return output;
    }

private:
    int capacity;   // Capacity of the array
    int numUsed;    // Number of elements in use
    dataType *ptr;  // Pointer to the first element of the array
    static const dataType nullValue; // Null value, for defaults and errors

    ////////////////////////////////////////////////////////////////////////
    //
    //   Function Name: resize (private member function)
    //   Description:    Resizes the array to the specified new capacity.
    //   Parameters:     newCapacity - new capacity for the array (input)
    //   Return Value:   None
    //
    ////////////////////////////////////////////////////////////////////////
    void resize(int newCapacity);
};

template <class dataType>
const dataType Array<dataType>::nullValue = 0; // Initialize the static member

template <class dataType>
Array<dataType>::Array(int arraySize) : capacity((arraySize >= minCap) ? arraySize : minCap), numUsed(0) {
    ptr = new dataType[capacity]; // Create space for the array
    assert(ptr != nullptr);       // Terminate if memory not allocated
    // Set all unused elements to default values
    for (int i = 0; i < capacity; ++i) {
        ptr[i] = nullValue;
    }
}

template <class dataType>
Array<dataType>::Array(const dataType A[], int num) : capacity((num >= minCap) ? num : minCap), numUsed(num) {
    assert(num > 0);
    ptr = new dataType[capacity]; // Create space for the array
    assert(ptr != nullptr);       // Terminate if memory not allocated
    // Assign all elements to array values
    for (int i = 0; i < num; ++i) {
        ptr[i] = A[i];
    }
    // Initialize unused elements to nullValue
    for (int i = num; i < capacity; ++i) {
        ptr[i] = nullValue;
    }
}

template <class dataType>
Array<dataType>::Array(const Array &A) : capacity(A.capacity), numUsed(A.numUsed) {
    ptr = new dataType[capacity]; // Create space for the array
    assert(ptr != nullptr);       // Terminate if memory not allocated
    // Copy elements from A to this object
    for (int i = 0; i < capacity; ++i) {
        ptr[i] = A.ptr[i];
    }
    // Initialize unused elements to nullValue
    for (int i = numUsed; i < capacity; ++i) {
        ptr[i] = nullValue;
    }
}

template <class dataType>
Array<dataType>::~Array() {
    delete[] ptr; // Reclaim space for the array
}

template <class dataType>
Array<dataType>& Array<dataType>::operator=(const Array &right) {
    if (&right != this) {
        if (capacity != right.capacity) {
            resize(right.capacity); // Resize this object
        }
        numUsed = right.numUsed;
        // Copy elements from right to this object
        for (int i = 0; i < numUsed; ++i) {
            ptr[i] = right.ptr[i];
        }
        // Initialize unused elements to nullValue
        for (int i = numUsed; i < capacity; ++i) {
            ptr[i] = nullValue;
        }
    }
    return *this;
}

template <class dataType>
void Array<dataType>::resize(int newCapacity) {
    dataType *newPtr = new dataType[newCapacity]; // Create space for array copy
    assert(newPtr != nullptr); // Terminate if not allocated
    // Copy old elements to the new array
    for (int i = 0; i < numUsed; ++i) {
        newPtr[i] = ptr[i];
    }
    delete[] ptr;
    ptr = newPtr;
    capacity = newCapacity; // Update the capacity
}

template <class dataType>
dataType& Array<dataType>::operator[](int subscript) {
    assert(subscript >= 0);
    // If subscript is beyond capacity, expand the array
    if (subscript >= capacity) {
        resize(subscript + 1);
    }
    // Update numUsed if subscript is beyond current numUsed
    if (subscript >= numUsed) {
        numUsed = subscript + 1;
    }
    return ptr[subscript];
}

template <class dataType>
const dataType& Array<dataType>::operator[](int subscript) const {
    if (subscript < 0 || subscript >= numUsed) {
        std::cerr << "subscript out of range" << std::endl;
        return nullValue;
    }
    return ptr[subscript];
}

template <class dataType>
Array<dataType>& Array<dataType>::operator+=(const dataType& element) {
    // If there is no space, expand the array
    if (numUsed >= capacity) {
        resize(capacity + 1);
    }
    ptr[numUsed++] = element; // Add the element
    return *this;
}

template <class dataType>
dataType Array<dataType>::operator*() const {
    // Return the first element of the array
    if (numUsed > 0) {
        return ptr[0];
    } else {
        std::cerr << "Array is empty" << std::endl;
        return nullValue;
    }
}

#endif
