#include <base.hpp>
#include <pmm.hpp>
extern "C" int kernel_start;
extern "C" int kernel_end;
auto PMM::isFree(phys_t addr) -> bool {
    if(addr == 0)
        return false;
    phys_t start = (phys_t)(&kernel_start);
    phys_t end = (phys_t)(&kernel_end);
    if((addr >= start) && (addr < end))
        return false;
    return true;
}
PMM::PMM(phys_t page_size): page_size(page_size), head(nullptr), lowest_page(~0), highest_page(0) {}
void PMM::fill() {
    for(phys_t i=lowest_page; i<highest_page+1; i+=page_size) {
        if(isFree(i))
            *this << i;
    }
}
PMM::~PMM() {}

auto PMM::operator<<(phys_t page) -> PMM & {
    (*this)(page,1);
    return *this;
}
auto PMM::operator>>(phys_t &page) -> PMM & {
    page = (*this, 1);
    return *this;
}

auto PMM::operator,(size_t no_pages) -> phys_t {
    if(head == nullptr)
        panic("No free physical memory is available.");
    if(no_pages == 1) {
        //Simple. Just return the fist page.
        PMM_ent *curr=head;
        head=head->next;
        return curr->val;
    }
    //Now we need to find a free page with n-1 free pages after it
    PMM_ent *curr=head;
    while(curr) {
        //Is curr+n pages free?
        if((curr->val+((no_pages-1)*page_size)) in *this) {
           //We're onto something
           bool notfound=false;
           phys_t i;
           size_t j;
           for(i=curr->val,j=0; j<no_pages; i+=page_size, j++) {
               if(!(i in *this)) {
                   notfound=true;
                   break;
               }
           }
           if(!notfound)
               return curr->val;
        }
        //Not found.
        curr=curr->next;
    }
    panic("Not enough continuous free memory is available.");
}
auto PMM::operator()(phys_t pages, size_t no_pages) -> void {
    for(size_t i=0; i<no_pages; i++, pages+=page_size) {
        PMM_ent *curr=(PMM_ent *)pages;
        curr->next=head;
        curr->val=pages;
        head=curr;
    }
}
auto PMM::operator&&(phys_t page) -> bool {
   PMM_ent *curr = head;
   while(curr) {
       if(curr->val==page)
           return true;
       curr=curr->next;
   }
   return false;
}
auto operator&&(phys_t a, PMM mm) -> bool {
    return mm && a;
}
