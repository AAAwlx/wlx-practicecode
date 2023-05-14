#include <iostream>
//使用你的名字替换YOUR_NAME
//#include<gtest/gtest.h>
namespace YOUR_NAME
{
    template <class T>
    // list存储的节点
    // 可以根据你的需要添加适当的成员函数与成员变量
    struct node
    {
        node<T> *prev_;
        node<T> *next_;
        T data_;
        //构造函数
        node(const T &data)
            : data_(data), prev_(nullptr), next_(nullptr){}
        node()
            : prev_(nullptr), next_(nullptr){}
        ~node(){}
    };
    template <class T>
    //迭代器类,(类比指针)
    struct iterator
    {
        typedef node<T> node_;
        typedef iterator<T> iterator_;
        node_ *data_;
        iterator(node_ *data)
            : data_(data){}
        ~iterator(){}
        //迭代到下一个节点
        //++it
        iterator_ &operator++()
        {
            return data_=data_->next_;
        }
        //迭代到前一个节点
        //--it
        iterator_ &operator--()
        {
            return data_=data_->prev_;
        }
        // it++
        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        //it--
        iterator operator--(int)
        {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
        //获得迭代器的值
        T &operator*()
        {
            return data_->data_;
        }
        //获得迭代器对应的指针
        T *operator->()
        {
            return &data_->data_;
        }
        //重载==
        bool operator==(const iterator_ &t)
        {
            return data_=t.data_;
    
        }
        //重载！=
        bool operator!=(const iterator_ &t)
        {
            return data_!=t.data_;
        }

        //**可以添加需要的成员变量与成员函数**
    };

    template <class T>
    class list
    {
    public:
        typedef node<T> node_;
        typedef iterator<T> Iterator;

    private:
        //可以添加你需要的成员变量
        node_ *head_; //头节点,哨兵（不存储有效数据）
        mutable size_t size;
    public:
        //构造函数
        list()//空构造
        {
            head_=new node();
            head_->next_=head_;
            head_->prev_=head_;
        }
        list(int n;const T& value=T())
        {
            head_=new node();
            head_->next_=head_;
            head_->prev_=head_;
            while(n--){
                push_back(value);
            }
        }
        //拷贝构造，要求实现深拷贝
        list(const list<T> &lt)
        {
            head_=new node();
            head_->next_=head_;
            head_->prev_=head_;
            list<T>tmp(It.begin(),It.end());
            swap(tmp);
        }
        template <class inputIterator>
        //迭代器构造
        list(inputIterator begin, inputIterator end)
        {
            head_=new node();
            head_->next_=head_;
            head_->prev_=head_;
            while(begib!=end){
                push_back(*begin);
                ++begin;
            }
        }

        ~list()
        {
           clear();
           delete head_;
           head_=nullptr;
        }
        void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);//交换头指针
		}
        //拷贝赋值
        list<T> &operator=(const list<T> &lt)
        {
            swap(lt);
			return *this;
        }
        //清空list中的数据
        void clear()
        {
            iterator it=begin();
            while (it!=end())
            {
                it=erase(it);
            }
            
        }
        //返回容器中存储的有效节点个数
        size_t size() const
        {
            while(begin()!=end()){
                size++;
            }
            return size;
        }
        //判断是否为空
        bool empty() const
        {
            if(begin()==end()){
                return true;
            }else{
                return false
            }
        }
        //尾插
        void push_back(const T &data)
        {
            insert(end(),data);
        }
        //头插
        void push_front(const T &data)
        {
            insert(begin(),data);
        }
        //尾删
        void pop_back()
        {
            erase(--end());
        }
        //头删
        void pop_front()
        {
            erase(begin());
        }
        //默认新数据添加到pos迭代器的后面,根据back的方向决定插入在pos的前面还是后面
        void  insert(Iterator pos, const T &data, bool back = true)
        {
            node *newnode=new node(data);//创建新节点
            node *cur=pos.node_;
            node *prev=cur->prev_;
            prev->next=newnode;
            newnode->prev_=prev;
            cur->prev_=newnode;
            newnode->next_=cur;
            //return iterator(newnode);
        }
        //删除pos位置的元素
        void erase(Iterator pos)
        {

			assert(pos != end());
            node *cur=pos.node_;
            node *prev=cur->prev_;
            node *next=cur->next_;
            prev->next_=next;
            next->prev_=prev;
            delete cur;
        }

        //获得list第一个有效节点的迭代器
        Iterator begin() const
        {
            return iterator(head_->next_);
        }

        //获得list最后一个节点的下一个位置，可以理解为nullptr
        Iterator end() const
        {
            return iterator(_head);
        }
        //查找data对应的迭代器
        Iterator find(const T &data) const
        {
            for(auto it = list.begin();it!=list.end();++it){
                if(*it==data){
                    return it;
                }
            }
        }
        //获得第一个有效节点
        node_ front() const
        {
            return head_->next_;
        }
        //获得最后一个有效节点
        node_ back() const
        {
            return head_->prev_
        }

   
        //可以添加你需要的成员函数
    };
};