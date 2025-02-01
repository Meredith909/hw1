#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}


void ULListStr::push_back(const std::string& val){

  if(head_==nullptr&&tail_==nullptr){
    Item* newItem= new Item();
    newItem->first=0;
    newItem->last=0;
    newItem->val[newItem->last]=val;
    newItem->last+=1;
    newItem->prev=nullptr;
    newItem->next=nullptr;
    head_=newItem;
    tail_=newItem;
    size_=1;
  } else if(tail_->last< ARRSIZE){
    tail_->val[tail_->last]=val;
    tail_->last+=1;
    size_+=1;
  }else{
    Item* newItem= new Item();
    newItem->first=0;
    newItem->last=0;
    newItem->val[newItem->last]=val;
    newItem->last+=1;
    newItem->prev=tail_;
    newItem->next=nullptr;
    tail_->next =newItem;
    tail_= newItem;
    size_+=1;
  }
}


void ULListStr::pop_back(){

  if(head_==nullptr&&tail_==nullptr){
    return;
  }

  else{
    tail_->last -=1;
    size_-=1;
    if(tail_->first==tail_->last){
      auto temp=tail_;
      tail_=tail_->prev;
      if(tail_==nullptr){
        head_=nullptr;
      }
      else{
        tail_->next=nullptr;
      }
      delete temp;
    }
  }

}

  /**
   * Adds a new value to the front of the list.
   * If there is room before the 'first' value in
   * the head node add it there, otherwise, 
   * allocate a new head node.
   *   - MUST RUN in O(1)
   */
void ULListStr::push_front(const std::string& val){

  if(head_==nullptr && tail_==nullptr){
    Item* newItem= new Item();
    newItem->first=0;
    newItem->last=0;
    newItem->val[newItem->first]=val;
    newItem->last+=1;
    newItem->prev=nullptr;
    newItem->next=nullptr;
    head_=newItem;
    tail_=newItem;
    size_=1;
  }

  else if(head_->first> 0){
    head_->first-=1;
    head_->val[head_->first]=val;
    size_+=1;
  }

  else{
    Item* newItem= new Item();
    newItem->last=ARRSIZE;
    newItem->first=ARRSIZE-1;
    newItem->val[newItem->first]=val;
    newItem->prev=nullptr;
    newItem->next=head_;
    head_->prev =newItem;
    head_=newItem;
    size_+=1;
  }
}
  /**
   * Removes a value from the front of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_front(){

  if(head_==nullptr&&tail_==nullptr){
    return;
  }
  else{
    head_->first+=1;
    size_-=1;
    if(head_->first==head_->last){
      auto temp=head_;
      head_=head_->next;
      if(head_==nullptr){
        tail_=nullptr;
      }
      else{
      head_->prev=nullptr;
      }
    delete temp;
    }
    return;
  }
}

  /**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */
void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string const & ULListStr::front() const{
  if (empty()) {
    throw std::out_of_range("ULListStr is empty");
  }
  return head_->val[head_->first];
}


std::string const & ULListStr::back() const{
  if(empty()) {
    throw std::out_of_range("ULListStr is empty");
  }
  return tail_->val[tail_->last - 1];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  if(loc >= size_ ){
    return nullptr;
  }
  else{
    Item* currentNode=head_;
    size_t nodeSize=currentNode->last - currentNode->first;
    while(currentNode!=nullptr){
      if(loc<nodeSize){
        return &currentNode->val[currentNode->first+loc];
      }
      loc -= nodeSize;
      currentNode=currentNode->next;
      nodeSize=currentNode->last - currentNode->first;
    }
    return nullptr;
  }
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location in getting loc: "+ std::to_string(loc) + "size: " + std::to_string(size_));
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
