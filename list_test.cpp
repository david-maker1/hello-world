#include "list.h"
#include <iostream>
#include <ctime>

void fillFront(List& list, int n){
	int val;
	for (int i = 0; i <= n; i++){
		val = rand() % 30;
		list.push_front(val);
	}
	list.print();
	std::cout << std::endl;
}

void fillBack(List& list, int n){
        int val;
        for (int i = 0; i <= n; i++){
                val = rand() % 30;
                list.push_back(val);
        }
        list.print();
	std::cout << std::endl;

}

void equial_test(List& list1, List& list2){
	list2 = list1;
	std::cout << "equial_test begin" << std::endl;
	list2.print();
	list1[1] = 100;
	std::cout << "New list after changes fo original" << std::endl;
	list2.print();
	std::cout << "equial_test end" << std::endl << std::endl;
}

void pop_front_test(List& list1){
	std::cout << "pop_front_test begin" << std::endl;
	std::cout << "original list" << std::endl;
	list1.print();
	list1.pop_front();
	std::cout << "list after changes" << std::endl;
	list1.print();
	std::cout << "pop_front_test end" << std::endl << std::endl;
}

void pop_back_test(List& list1){
        std::cout << "pop_back_test begin" << std::endl;
        std::cout << "original list" << std::endl;
        list1.print();
        list1.pop_back();
        std::cout << "list after changes" << std::endl;
        list1.print();
	std::cout << "pop_front_test end" << std::endl << std::endl;
}

void del_test(List& list1, int index){
	std::cout << "del_test begin" << std::endl;
        std::cout << "original list" << std::endl;
	list1.print();
	list1.del(index);
	std::cout << "list after changes" << std::endl;
        list1.print();
	std::cout << "del_test end" << std::endl << std::endl;
}



int main(){
	srand(time(NULL));
	List list1, list2, list3;
	fillFront(list1, 10);
	fillBack(list2, 10);
	equial_test(list1, list3);
	list1.clear();
	list2.clear();
	fillFront(list1, 10);
        fillBack(list2, 10);
	pop_front_test(list1);
	pop_back_test(list2);
	del_test(list1, 5);
	return 0;
}

