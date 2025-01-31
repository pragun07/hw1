#include <cstddef>
#include <stdexcept>
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

// WRITE YOUR CODE HERE

void ULListStr::push_back(const std::string& val) 
{
  if (!tail_) //when the list is empty need to allocate a new Item
  {
    tail_= new Item();
    head_= tail_;
    tail_->first = 0;
    tail_->last = 1;
    tail_->val[0]=val;
  }
  else if (tail_->last<ARRSIZE) //element can be added at the back
  {
    tail_->val[tail_->last]=val;
    tail_->last++;
  }
  else //no space at the back so need to allocate a new element
  {
    Item* new_item = new Item();
    new_item->val[0]=val;
    new_item->first = 0;
    new_item->last = 1;
    tail_->next = new_item;
    new_item->prev = tail_;
    tail_=new_item;
  }
  //update size after adding an element
  size_++; 
}

void ULListStr::push_front(const std::string& val)
{
  if(!head_) //when the list is empty need to allocate a new Item
  {
    head_= new Item();
    tail_= head_;
    head_->first= ARRSIZE-1;
    head_->last= ARRSIZE;
    head_->val[head_->first]=val;
  }
  else if (head_->first>0) //element can be added at the front
  {
    head_->first--;
    head_->val[head_->first]= val;
  }
  else // no space at the front so allocate a new Item
  {
    Item* new_item= new Item();
    new_item->first= ARRSIZE-1;
    new_item->last=ARRSIZE;
    new_item->val[new_item->first]= val;
    new_item->next= head_;
    head_->prev=new_item;
    head_=new_item;
  }
  //update size after adding a new element
  size_++;
}

void ULListStr::pop_back() 
{
  if(!tail_) //when the list is empty nothing is removed
  {
    return;
  }

  tail_->last--; //removing last element
  size_--; //updating size 

  if(tail_->first == tail_->last) //checking if the Item becomes empty
  {
    //deallocating empty Item and updating tail
    Item* temp_var=tail_;
    tail_=tail_->prev;

    if(tail_)
    {
      tail_->next= nullptr;
    }
    else
    {
      head_=nullptr;
    }
    delete temp_var;
  }
}

void ULListStr::pop_front()
{
  if(!head_) // when the list is empty nothing is removed
  {
    return;
  }
  head_->first++; //removing first element
  size_--; //updating size

  if(head_->first == head_->last) //checking if the Item becomes empty
  {
    //deallocating empty Item and updating head
    Item* temp_var = head_;
    head_=head_->next;
    if(head_)
    {
      head_->prev=nullptr;
    }
    else
    {
      tail_=nullptr;
    }
    delete temp_var;
  }
}

std::string const& ULListStr::back() const 
{
  return tail_->val[tail_->last-1];
}

std::string const& ULListStr::front() const 
{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const 
{
  //return nullptr if index is out of bounds
  if(loc>=size_)
  {
    return nullptr;
  }
  
  Item* current_ptr=head_;
  while(current_ptr)
  {
    size_t element_count=current_ptr->last - current_ptr->first;
    if(loc<element_count) //checking if the index is within this Item
    {
      return &current_ptr->val[current_ptr->first+loc];
    }
    loc=loc-element_count;
    current_ptr=current_ptr->next;
  }
  return nullptr; //if element is not found
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
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
