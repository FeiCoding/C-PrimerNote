#include <iostream>
#include <forward_list>
using namespace std;

using FLI = forward_list<int>;

int main(int argc, char const *argv[])
{
    FLI fl = {1, 2, 3, 4, 5, 6};
    auto prev = fl.before_begin();
    auto cur = fl.begin();
    while(cur != fl.end()){
        if(*cur % 2)                    // 若元素为奇数
            cur = fl.erase_after(prev); // 删除它并移动cur，指向删除元素的后一个元素
        else
        {
            prev = cur; // 移动迭代器，指向下一个元素，prev指向cur之前的元素
            ++cur;
        }
        
    }
    for(auto i : fl){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
