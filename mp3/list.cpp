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

#include <iostream>

using namespace std;
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    // Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    // Graded in MP3.1
    while (head)
    {
        tail = head->next;
        delete head;
        head = tail;
    }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    //Graded in MP3.1
    ListNode* newStuff = new ListNode(ndata);
    if (head != NULL)
    {
        newStuff->next = head;
        head -> prev = newStuff;
        head = newStuff;
        length++;
    } else
    {
        head = newStuff;
        tail = newStuff;
        length++;
    }
    newStuff = NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    // Graded in MP3.1
    
    ListNode* newStuff = new ListNode(ndata);
    if (tail != NULL)
    {
        tail->next = newStuff;
        newStuff->prev = tail;
        tail = newStuff;
        newStuff = NULL;
        length++;
    } else
    {
        head = newStuff;
        tail = newStuff;
        length++;
    }
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    cout<<head->data<<endl;
    reverse(head, tail);
    cout<<head->data<<endl;
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
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    if(startPoint == endPoint)
        return;

    ListNode* temp = startPoint;
    ListNode * temp2 = startPoint;
    ListNode * temp3 = endPoint->next;
   
    while (temp != temp3)
    {
        temp2 = temp->prev;
        temp->prev = temp->next;
        temp->next = temp2;
        temp = temp->prev;
    }

    temp2 = endPoint->prev;
    
    if (startPoint->next != NULL)
    {
        endPoint ->prev = startPoint->next;
        startPoint->next->next = endPoint;
    } else
        endPoint ->prev = NULL;
    
    if (temp2 != NULL)
    {
        startPoint->next = temp2;
        temp2->prev = startPoint;
    } else
        startPoint ->next = NULL;
    
    temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;
    temp = NULL;
    temp2 = NULL;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
    //don't do anything if it's an empty list or if block size = 1
    if (length <=1 || n == 1)
        return;
    //just do normal reverse if block size is the full length
    if (n == length)
        reverse();
    
    //setup node pointers
    ListNode *temp = head;
    ListNode *new_head = head;
    ListNode *new_tail = NULL;

    //store block size for counter
    int count = n;

    while(temp != NULL)
    {
       if (count==0)
       {
           if (new_head == head)
               head = new_tail;
            reverse(new_head,new_tail);
            count = n;
            new_head = temp;
            new_tail = temp;
       }

       if (temp->next == NULL)
       {
            reverse(new_head,temp);
       }

        /*
        cout<<"[newhead]: "<<new_head<<endl;
        cout<<"[newtail]: "<<new_tail<<endl;
        cout<<"[node]: "<<temp->data<<endl;
        cout<<"[addr]: "<<temp<<endl;
        if(temp->prev != NULL)
        cout<<"[prev]: "<<temp->prev->data<<endl;
        if(temp->next != NULL)
        cout<<"[next]: "<<temp->next->data<<endl;
        cout<<"----------------------"<<endl;
        */
       new_tail = temp;
       temp = temp->next;
       count--;
    }
    
    /*
    ListNode * curr = head;
    ListNode * next;
    ListNode * prev = NULL;
    int count = 0;

    while(curr != NULL && count < n)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    if (next != NULL)
        head ->next = reverseNth(next,n);
    return prev;
    */
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
    if (length == 0)
        return;
    
    int count = 1;

    ListNode * temp = head;
    ListNode * temp2 = head;

    while (temp->next != tail && temp != tail && temp != NULL)
    {
        while (count >0)
        {
            temp2 = temp;
            temp = temp ->next;
            count--;
        }

        temp2->next = temp ->next;
        temp->next->prev = temp2;

        tail -> next = temp;
        temp -> next = NULL;
        temp -> prev = tail;
        tail = temp;

        temp = temp2->next;

        count = 1;
    }

    temp = NULL;
    temp2 = NULL;

    /*
    ListNode* tmp1, *tmp2;
    tmp1 = head;
    tmp2 = tmp1->next;
    cout<<(tmp2->next)<<endl; 
    while (tmp2 != tail)
    {
        tmp1->next = tmp2->next;
        tmp2->next->prev = tmp1;
        tail->next = tmp2;
        tmp2 ->prev = tail;
        tmp2->next = NULL;
        tail = tmp2;
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    */
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

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
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
    if (ret.tail != NULL)
    {
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
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    /// @todo Graded in MP3.2
    ListNode * temp = start;
    int count = splitPoint;
    while (count--){
        temp = temp->next;
    }
    if (temp->prev != NULL)
        temp->prev->next = NULL;
    return temp; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
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
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    /// @todo Graded in MP3.2
    /*
    cout<<"INSIDE MERGE!!"<<endl;
    cout<<"[first]: "<<first<<endl;
    cout<<"[second]: "<<second<<endl;
    ListNode * t1 = first;
    ListNode * t3 = second;
    ListNode * t2 = NULL;

    //continue to compare as long as we're not at the last node of the list merging into
    while (t1->next != NULL)
    {
        //simply move index of first list if no need to insert
        if(t1->data< (t3->data))
        {
            t1 = t1->next;
        }

        else   //insert behind t1
        {
            t2 = t3;

            if (t3->next != NULL)   //move t3 to the next node if not at last node
                t3 = t3->next;

            t2->prev = t1->prev;
            t2->next = t1;
            t1->prev->next = t2;

            if (t2->next != NULL)
                t2->next->prev = t2;
            t1 = t1->prev;
        }

    }

    //reached the end of first list. just append the rest of second list to first list
    t1 ->next= t3;
    t3->prev = t1;

    cout<<"MERGED!!"<<endl; 
    return first;
    */
    ListNode * newList;
    ListNode * newNext;
    ListNode * firstList = first;
    ListNode * secondList = second;
 
    if ( firstList->data < secondList->data )
    {
        newList = firstList;
        firstList = firstList->next;
        head = firstList;
    }
    else
    {
        newList = secondList;
        secondList = secondList->next;
        head = secondList;
    }
 
    while ( firstList != NULL || secondList != NULL )
    {
        if ( secondList == NULL || ( firstList != NULL && firstList->data < secondList->data ))
        {
            newList->next = firstList;
            newNext = newList->next;
            newNext->prev = newList;
 
            newList = newList->next;
 
            firstList = firstList->next;
        }
        else
        {
            newList->next = secondList;
            newNext = newList->next;
            newNext->prev = newList;
 
            newList = newList->next;
            secondList = secondList->next;
        }
    }
 
    // since they're already sorted, all that should be done is to compare
    // the two and put it together.
 
    if ( first->data < second->data)
        return first;
 
    return second;
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
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    if (chainLength==1)
        return start;
    int mid = chainLength/2;
    ListNode *right = split(start,mid);
    ListNode *left = start;
    right = mergesort(right,chainLength-mid);
    start = mergesort(left,mid);
    return merge(right,start); // change me!
}

