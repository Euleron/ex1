#include "IsraeliQueue.h"
#include <stdlib.h>
#include <string.h>

#define ZERO 0



bool checkIfFriend(IsraeliQueue head,void* item)
{
    if(head -> m_student -> m_numOfFriends >= FRIEND_QUOTA)
    {
        return false;
    }

    while(head -> m_friendshipPtr) {

        if ((*head -> m_friendshipPtr)(head, item) > head -> m_friendPar) {
            return true;
        }
        head -> m_friendshipPtr++;
    }
    return false;
}

bool checkIfRival(IsraeliQueue head,void* item)
{
    if(head -> m_student -> m_numOfRivals >= RIVAL_QUOTA)
    {
        return false;
    }
    if(checkIfFriend(head, item))
    {
        return false;
    }
    int sum=0,cnt=0;
    while(head -> m_friendshipPtr)
    {
        cnt++;
        sum+=(*head -> m_friendshipPtr)(head, item);
        head -> m_friendshipPtr++;
    }
    if((sum/cnt)<(head->m_rivalPar))
    {
        return true;
    }
    return false;
}

void Dequeue(IsraeliQueue q){
    while(q -> m_next){
        q -> m_student -> m_numOfFriends = q -> m_next ->m_student ->  m_numOfFriends;
        q -> m_student -> m_numOfRivals = q -> m_next -> m_student -> m_numOfRivals;
        q -> m_friendPar = q -> m_next -> m_friendPar;
        q -> m_rivalPar = q -> m_next -> m_rivalPar;
        q = q-> m_next;
    }
    free(q);
}

bool areSame(IsraeliQueue q1, IsraeliQueue q2){
    return (q1 ->m_student ->  m_numOfFriends == q2 ->m_student ->  m_numOfFriends && q1 -> m_student -> m_numOfRivals == q2 -> m_student -> m_numOfRivals && q1 -> m_friendPar == q2 -> m_friendPar && q1 -> m_rivalPar == q2 -> m_rivalPar);
}

IsraeliQueue singleClone(IsraeliQueue q){
    IsraeliQueue result = IsraeliQueueCreate(q -> m_friendshipPtr, q -> m_comparisonPtr, q -> m_friendPar, q -> m_rivalPar);
    result -> m_student ->  m_numOfFriends = q -> m_student ->  m_numOfFriends;
    result -> m_student -> m_numOfRivals = q -> m_student -> m_numOfRivals;
    result -> m_next = q -> m_next;
    return result;
}

IsraeliQueue IsraeliQueueCreate(FriendshipFunction * friend, ComparisonFunction comp, int friendTh, int rivalryTh)
{
    struct IsraeliQueue_t* newQueue = malloc(sizeof (*newQueue));
    if(!newQueue)
    {
        return NULL;
    }
    //FriendshipFunction* arrayFriendship= malloc(sizeof(arrayFriendship));
    newQueue -> m_student -> m_numOfFriends = ZERO;
    newQueue -> m_student -> m_numOfRivals = ZERO;
    newQueue -> m_friendPar= friendTh;
    newQueue -> m_rivalPar=rivalryTh;
    newQueue -> m_friendshipPtr=friend;
    newQueue -> m_comparisonPtr=comp;
    newQueue -> m_next=NULL;
    return newQueue;
}

IsraeliQueue IsraeliQueueClone(IsraeliQueue q)
{
    if(!q)
    {
        return NULL;
    }
    IsraeliQueue newQ = IsraeliQueueCreate(q->m_friendshipPtr,q->m_comparisonPtr,q->m_friendPar,q->m_rivalPar);
    IsraeliQueue head = newQ;
    while(q -> m_next){
        head -> m_next = malloc(sizeof (head -> m_next));
        memcpy(head->m_next,q->m_next,sizeof (*q->m_next)); //head=heat->m_next ;
        head = head -> m_next;
        q = q -> m_next;
    }
    return newQ;

}

void IsraeliQueueDestroy(IsraeliQueue head)
{
    while(head)
    {
        IsraeliQueue toDelete=head;
        head=head-> m_next;
        free(toDelete);
    }
}

IsraeliQueueError IsraeliQueueEnqueueNoChange(IsraeliQueue head, void * item, bool change){
    //HOW DO WE USE ITEM???????????!!!!!
    IsraeliQueue q = (IsraeliQueue)(item);
    if(!head)
    {
        //check with some one what happends if the head is NULL
    }
    while(head){
        //this if runs until we find a friend
        if(!checkIfFriend(head, item)){
            head = head -> m_next;
            continue;
        }
        IsraeliQueue tempFriend = head;
        while(head){
            if(checkIfRival(head, item)){
                if(change) {
                    head -> m_student -> m_numOfRivals++;
                }
                head = head -> m_next;
                break;
            }
            head = head -> m_next;
            if(head == NULL){
                if(change) {
                    tempFriend -> m_student -> m_numOfFriends++;
                }
                IsraeliQueue temp = tempFriend -> m_next;
                tempFriend -> m_next = q;
                q -> m_next = temp;
                return ISRAELIQUEUE_SUCCESS;
            }
        }
    }
    head = q;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue head, void * item)
{
    IsraeliQueueEnqueueNoChange(head, item, true);
}
//should talk about it with noam
//should allocate my own 
IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction friend)
{
    if( !q || !friend)
    {
        return ISRAELIQUEUE_BAD_PARAM;
    }
    while(q->m_friendshipPtr!=NULL)
    {
        q->m_friendshipPtr++;
    }
    q->m_friendshipPtr=friend;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue q, int friendshipTh){
    while(q){
        q -> m_friendPar = friendshipTh;
        q = q -> m_next;
    }
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue q, int rivalryTh){
    while(q){
        q -> m_friendPar = rivalryTh;
        q = q -> m_next;
    }
    return ISRAELIQUEUE_SUCCESS;
}

int IsraeliQueueSize(IsraeliQueue q){
    if(!q)
    {
        return ZERO;
    }
    int count = 0;
    while(q){
        count++;
        q = q -> m_next;
    }
    return count;
}

void* IsraeliQueueDequeue(IsraeliQueue q){
    if(!q) {
        return NULL;
    }
    IsraeliQueue result  = singleClone(q);
    Dequeue(q);
    return result;
}

bool IsraeliQueueContains(IsraeliQueue q, void* item){
    //HOW DO WE USE ITEM???????????!!!!!
    IsraeliQueue qItem = (IsraeliQueue)(item);
    if(!q || !item)
        return false;
    while(q){
        //here i changed the if beacuse we dont need to check if there next is the same. we dont know if they are in the same line
        if(qItem -> m_student -> m_numOfFriends == q -> m_student -> m_numOfFriends &&
        qItem -> m_student -> m_numOfRivals == q -> m_student -> m_numOfRivals &&
        qItem -> m_friendPar == q -> m_friendPar &&
        qItem -> m_rivalPar == q -> m_rivalPar &&
        qItem -> m_friendshipPtr == q -> m_friendshipPtr &&
        qItem -> m_comparisonPtr == q -> m_comparisonPtr )
            return true;
        q = q -> m_next;
    }
    return false;
}

IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue q){
    IsraeliQueue original = IsraeliQueueClone(q);
    IsraeliQueue head = q;
    IsraeliQueue temp = original;
    IsraeliQueue tempInsert;
    int size = IsraeliQueueSize(original);
    int iterations = size;
    while(iterations > 0){
        while(size > 0){
            temp = temp -> m_next;
            size--;
        }
        while(!areSame(head, temp)){
            head = head -> m_next;
        }
        tempInsert = IsraeliQueueDequeue(head);
        IsraeliQueueEnqueueNoChange(q, tempInsert, false);
        head = q;
        temp = original;
        iterations--;
        size = iterations;
    }
}

bool arrayExhausted(int arr [], int n){
    for(int i = 0; i < n; i++)
        if(arr[i] > 0)
            return false;
    return true;
}

int friendshipAverage(IsraeliQueue* arr){
    int count = 0;
    int sum = 0;
    while(arr){
        if((*arr) -> m_friendPar != NULL)
            sum += (*arr) -> m_friendPar;
        count++;
        arr++;
    }
    if(sum % count == 0)
        return sum / count;
    return ((int)(((double)sum) / count)) + 1;
}

int rivalAverage(IsraeliQueue* arr){
    int count = 0;
    int prod = 1;
    while(arr){
        if((*arr) -> m_rivalPar != NULL)
            prod *= (*arr) -> m_rivalPar;
        count++;
        arr++;
    }
    int attempt = 1;
    bool negative = false;
    if(prod == 0)
        return 0;
    if(prod < 0){
        negative = true;
        prod *= -1;
        if(count % 2 == 0)
            return NULL;
    }
    for (int i = 1; i < prod; i++){
        for(int j = 1; j <= count; j++)
            attempt *= i;
        if(attempt >= prod){
            if(negative)
                return -i;
            else
                return i;
        }
        attempt = 1;
    }
}

FriendshipFunction* mergeFriendships(IsraeliQueue* arr){
    int size = 0;
    int index = 0;
    FriendshipFunction* temp;
    while(arr[index]){
        temp = arr[index] -> m_friendshipPtr;
        while(*temp){
            size++;
            temp++;
        }
        index++;
    }
    if(size == ZERO)
        return NULL;
    FriendshipFunction* result = malloc((size+1) * sizeof(result));
    int count = 0;
    index = 0;
    while(count < size){
        temp = arr[index] -> m_friendshipPtr;
        while(*temp){
            result[count] = temp;
            count++;
            temp++;
        }
        index++;
    }
    result[count] = NULL;
    return result;
}

void IsraeliQueueEndOfLine(IsraeliQueue q, IsraeliQueue enqueue){
    if(!q){
        *q = *enqueue;
        return;
    }
    while(q -> m_next){
        q = q -> m_next;
    }
    q -> m_next = enqueue;
}

IsraeliQueue IsraeliQueueMerge(IsraeliQueue* arr,ComparisonFunction compareFunction){

    // Parameter check.

    if(!arr)
        return NULL;

    // Establishes parameters for new queue.

    int friendshipPar = friendshipAverage(arr);
    int rivalryPar = rivalAverage(arr);
    FriendshipFunction* friends = mergeFriendships(arr);

    IsraeliQueue* arrTemp = arr; //Look through arr without losing original pointer.

    // Establishes size of arr.

    int histCount = 0;
    while(arrTemp){
        histCount++;
        arrTemp++;
    }

    arrTemp = arr;

    // Creates int histogram, indicating how many entries in each queue by order of queues.

    int* hist = malloc(histCount*sizeof(int));
    for(int i = 0; i < histCount; i++){
        hist[i] = IsraeliQueueSize(arrTemp);
        arrTemp++;
    }

    arrTemp = arr;

    // Frees memory of no longer needed friendship functions array of each queue.

    while(arrTemp){
        free((*arrTemp) -> m_friendshipPtr);
        arrTemp++;
    }

    // bigQ is queue to be returned.

    IsraeliQueue bigQ = malloc(sizeof(bigQ));
    bigQ = NULL;
    IsraeliQueue temp;

    // while there are still entries to be enqueued (while i is smaller than index of last queue(skip empty queues,
    // enqueue otherwise) i++)

    int i = 0;
    while(!arrayExhausted(hist, histCount)){
        while(i < histCount){
            if(hist[i] == 0){
                i++;
                break;
            }
            if(bigQ == NULL){
                bigQ = IsraeliQueueDequeue((arr[i]));
                bigQ -> m_student ->  m_numOfFriends = 0;
                bigQ -> m_student -> m_numOfRivals = 0;
                bigQ -> m_friendPar = friendshipPar;
                bigQ -> m_rivalPar = rivalryPar;
                bigQ -> m_friendshipPtr = friends;
                bigQ -> m_comparisonPtr = compareFunction;
                bigQ -> m_next = NULL;
            }
            else{
                temp = IsraeliQueueDequeue((arr[i]));
                temp -> m_student -> m_numOfFriends = 0;
                temp -> m_student -> m_numOfRivals = 0;
                temp -> m_friendPar = friendshipPar;
                temp -> m_rivalPar = rivalryPar;
                temp -> m_friendshipPtr = friends;
                temp -> m_comparisonPtr = compareFunction;
                temp -> m_next = NULL;
                IsraeliQueueEnqueue(bigQ, temp);
            }
            hist[i]--;
            i++;
        }
        i = 0;
    }
    return bigQ;
}