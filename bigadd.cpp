#include <iostream>
#include <climits>

using namespace std;

struct nnode {
	unsigned long long num;
	nnode* p_next;
	nnode(): num(0), p_next(nullptr) {}
};

class BigAdd {
private:
	nnode* head;
	void add(nnode*& ptr, unsigned long long num) {
		int carry;
		
		if(ptr == nullptr) {
			ptr = new nnode;
		}
		
		ptr->num += num;
		
		if(ptr->num > LLONG_MAX) {
			carry = 1;
			head->num -= LLONG_MAX;
		}
		else {
			carry = 0;
		}
		
		if(carry != 0) {
			add(ptr->p_next, carry);
		}
	}
public:
	BigAdd(): head(nullptr) {}
	~BigAdd() {
		nnode *prev, *current;
		prev = nullptr;
		current = head;
		
		while(current) {
			prev = current;
			current = current->p_next;
			delete prev;
		}
	}

	void add(BigAdd& num) {
		nnode *it_me, *it_other, *prev_other, *prev_me;
		int carry;

		if(head == nullptr) {
			this->head = num.head;
		}
		else{
			prev_me = nullptr;
			prev_other = nullptr;
			it_me = this->head;
			it_other = num.head;

			carry = 0;

			while(it_me && it_other) {
				it_me->num += it_other->num;
				it_me->num += carry;

				if(it_me->num > LLONG_MAX) {
					carry = 1;
					it_me->num -= LLONG_MAX;
				}
				else {
					carry = 0;
				}
				
				prev_me = it_me;
				it_me = it_me->p_next;
				prev_other = it_other;
				it_other = it_other->p_next;
			}

			if(it_other) {
				prev_me->p_next = it_other;
				prev_other->p_next = nullptr;
				it_me = prev_me->p_next;
			}

			if(it_me == nullptr) {
				prev_me->p_next = new nnode;
				it_me = prev_me->p_next;
			}

			it_me->num += carry;
		}
	}
	
	void add(unsigned long long num) {
		add(head, num);
	}
	
	friend ostream& operator<<(ostream& os, const BigAdd& num) {
		nnode* walker;
		int hop;

		
		os << "\t" << LLONG_MAX << "^0" << " * " << num.head->num << endl;
		hop = 1;
		for(walker = num.head->p_next; walker; walker = walker->p_next) {
			os << "+\t" << LLONG_MAX << "^" << hop << " * " << walker->num << endl;
			hop++;
		}
		return os;
	}
};

int main()
{
	int i;
	BigAdd a;
	
	for(i = 0; i < INT_MAX; i++) {
		a.add(LLONG_MAX);
	}
	
	cout << a;
	return 0;
}
