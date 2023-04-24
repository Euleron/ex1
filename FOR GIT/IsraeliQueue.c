#include "IsraeliQueue.h"
#include <stdlib.h>

#define ZERO 0

 struct IsraeliQueue_t
{
    int m_numOfFriends;
    int m_numOfRivals;
    int m_friendPar;
    int m_rivalPar;
    FriendshipFunction * m_friendshipPtr;
    ComparisonFunction * m_comparisonPtr;
    struct IsraeliQueue_t * m_next;
 };

bool checkIfFriend(IsraeliQueue head,void* item)
{
    if(head->m_numOfFriends>=FRIEND_QUOTA)
    {
        return false;
    }

    while(!(head->m_friendshipPtr)) {

        if ((*head->m_friendshipPtr)(head, item) > head->m_friendPar) {
            return true;
        }
        head->m_friendshipPtr++;
    }
    return false;
}

bool checkIfRival(IsraeliQueue head,void* item)
{
    if(head->m_numOfRivals>=RIVAL_QUOTA)
    {
        return false;
    }
    if(checkIfFriend(head,item))
    {
        return false;
    }
    int sum=0,cnt=0;
    while(head->m_friendshipPtr)
    {
        cnt++;
        sum+=(*head->m_friendshipPtr)(head, item);
        head->m_friendshipPtr++;
    }
    if((sum/cnt)<head->m_rivalPar)
    {
        return true;
    }
    return false;


}

void Dequeue(IsraeliQueue q){
    while(q -> m_next){
        q -> m_numOfFriends = q -> m_next -> m_numOfFriends;
        q -> m_numOfRivals = q -> m_next -> m_numOfRivals;
        q -> m_friendPar = q -> m_next -> m_friendPar;
        q -> m_rivalPar = q -> m_next -> m_rivalPar;
        q = q-> m_next;
    }
    free(q);
}

bool areSame(IsraeliQueue q1, IsraeliQueue q2){
    return (q1 -> m_numOfFriends == q2 -> m_numOfFriends && q1 -> m_numOfRivals == q2 -> m_numOfRivals && q1 -> m_friendPar == q2 -> m_friendPar && q1 -> m_rivalPar == q2 -> m_rivalPar);
}

IsraeliQueue singleClone(IsraeliQueue q){
    IsraeliQueue result = IsraeliQueueCreate(q -> m_friendshipPtr, q -> m_comparisonPtr, q -> m_friendPar, q -> m_rivalPar);
    result -> m_numOfFriends = q -> m_numOfFriends;
    result -> m_numOfRivals = q -> m_numOfRivals;
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
   newQueue->m_numOfFriends=ZERO;
   newQueue-> m_numOfRivals=ZERO;
   newQueue-> m_friendPar= friendTh;
   newQueue-> m_rivalPar=rivalryTh;
   newQueue->m_friendshipPtr=friend;
   newQueue->m_comparisonPtr=comp;
   newQueue-> m_next=NULL;
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
        head -> m_next = q -> m_next;
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
        if(!checkIfFriend(head, item)){
            head = head -> m_next;
            continue;
        }
        IsraeliQueue tempFriend = head;
        while(head){
            if(checkIfRival(head, item)){
                if(change)
                    head -> m_numOfRivals++;
                head = head -> m_next;
                break;
            }
            head = head -> m_next;
            if(head == NULL){
                if(change)
                    tempFriend -> m_numOfFriends++;
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
    int count = 0;
    while(q){
        count++;
        q = q -> m_next;
    }
    return count;
}

void* IsraeliQueueDequeue(IsraeliQueue q){
    if(!q)
        return NULL;
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
        if(qItem ->m_numOfFriends == q ->m_numOfFriends && qItem ->m_numOfRivals == q ->m_numOfRivals && qItem ->m_friendPar == q ->m_friendPar && qItem ->m_rivalPar == q ->m_rivalPar && qItem ->m_friendshipPtr == q ->m_friendshipPtr && qItem ->m_comparisonPtr == q ->m_comparisonPtr && qItem ->m_next == q ->m_next)
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

IsraeliQueue IsraeliQueueMerge(IsraeliQueue* arr,ComparisonFunction compareFunction){
    if(!arr)
        return NULL;
    int histCount = 0;
    IsraeliQueue* arrTemp = arr;
    while(arrTemp){
        histCount++;
        arrTemp++;
    }
    arrTemp = arr;
    int* hist = malloc(histCount*sizeof(int));
    for(int i = 0; i < histCount; i++){
        hist[i] = IsraeliQueueSize(arrTemp);
        arrTemp++;
    }
    IsraeliQueue bigQ = NULL;
    IsraeliQueue temp;
    arrTemp = arr;
    int i = 0;
    while(!arrayExhausted(hist, histCount)){
        while(i < histCount){
            if(hist[i] == 0){
            i++;
            break;
            }
            if(bigQ == NULL){
                bigQ = IsraeliQueueDequeue((arr[i]));
                temp = bigQ;
            }
            else
                temp -> m_next = IsraeliQueueDequeue((arr[i]));
            temp = temp -> m_next;
            hist[i]--;
            i++;
        }
    i = 0;
}