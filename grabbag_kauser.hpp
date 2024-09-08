/*
Jameela Kauser
CSE310 Rcitation assignment 1
Description: In this recitation assignment we will build a simple data structure known as a
Grab-Bag. It will then be used to solve a problem.
*/
#include <random>
#include <iostream>
#include <time.h>
using namespace std;
template <typename T> class BagNode
{
    private:
        T item;
        BagNode<T>* next;
    public:
        T getItem()
        {
            return item;
        }
        BagNode<T>* getNext()
        {
            return next;
        }
        void setNext(BagNode<T>* newNext)
        {
            next= newNext;
        }
        BagNode( T item){
            this->item=item;
            next=nullptr;
       }        
};
template <typename T> class GrabBag
{
    private:
        int count;
        unsigned int seed;
        BagNode<T>* front;
        minstd_rand randgen;
        public:
            GrabBag()
            {
                seed= static_cast<unsigned int>( time(NULL) );
                count=0;
                front=nullptr;
                minstd_rand randgen(seed);
            }
            GrabBag(unsigned int s)
            {
                seed=s;
                count=0;
                front=nullptr;
               minstd_rand randgen(seed);
            }
            int getCurrentSize()
            {
                return count;
            }
            bool isEmpty()
            {
                return count==0;
            }
            void add(T item)
            {
              BagNode<T>* nodeNew= new BagNode<T>(item);
              nodeNew->setNext(front);
              front=nodeNew;
              count++;
            }
            T grab()
            {
                if (isEmpty())
                {
                    throw out_of_range("Attempted to grab but bag is empty");
                }
                BagNode<T>* removalNode=front;
                BagNode<T>* pNode=nullptr;
                int removalNodeIndex=randgen()%count;
                if(removalNodeIndex==0)
                {
                    if(count==1)
                    {
                        front=nullptr;
                    }
                    else
                    {
                     front=front->getNext();
                    }
                }
                else
                {
                 for(int i=0; i<removalNodeIndex;i++)
                 {
                    pNode=removalNode;
                    removalNode=removalNode->getNext();
                 }
                }
                T rItem=removalNode->getItem();
                if (pNode!=nullptr)
                {
                    pNode->setNext(removalNode->getNext());
                }
                delete removalNode;
                count--;
                return rItem;
            }
            int getFrequencyOf(T item)
            {
                int freq=0;
                BagNode<T>* checkNode=front;
                while(checkNode != nullptr)
                {
                    if(checkNode->getItem()==item)
                    {
                        freq++;
                    }
                    checkNode=checkNode->getNext();
                }
                return freq;
            }
            void empty()
            {
                BagNode<T>* emptyNode=front;
               
                while(emptyNode != nullptr)
                {
                    BagNode<T>* delNode=emptyNode;
                    emptyNode=emptyNode->getNext();
                    delete delNode;
                }
                front=nullptr;
                count=0;
            }
            ~GrabBag()
            {
                empty();
            }
};