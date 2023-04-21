#include "IsraeliQueue.h"
#include<stdlib.h>

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
    while(!(head->m_friendshipPtr))
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
}

IsraeliQueue IsraeliQueueClone(IsraeliQueue q)
{
    if(!q)
    {
        return NULL;
    }
    return IsraeliQueueCreate(q->m_friendshipPtr,q->m_comparisonPtr,q->m_friendPar,q->m_rivalPar);

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

IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue head, void * item)
{
    if(!head)
    {
        //check with some one what happends if the head is NULL
    }
    IsraeliQueue temp=NULL;
    while(head->m_next!=NULL) {
        if(checkIfRival(head,item))
        {
            temp=head;
        }
    }
    while(!(temp->m_next))
    {
        if(checkIfFriend(temp,item))
        {

        }
    }
    head->m_next=item;
}

