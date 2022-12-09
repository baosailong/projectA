#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<bits/stdc++.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
using namespace std;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
public slots:
    void start();


private:
    Ui::MainWindow *ui;
};
struct value {
    string name, time;
    int w;
};
struct node {
    value v;
    node* next;
};//head为空域
typedef struct node* nptr;
struct btree {
    btree* lch, * rch, * next;//子节点的lch,rch,nxt都为null
    int height;
    value v;
};
typedef struct btree* bptr;
class AVL {
private:

    bptr findmax(bptr root)
    {
        if (root->rch == NULL)return root;
        else return findmax(root->rch);
    }
    bptr findmin(bptr root)
    {
        if (root->lch == NULL)return root;
        else return findmax(root->lch);
    }
    void nxtDelete(bptr root)//清空 node 的 next
    {
        bptr p = root->next;
        bptr nxt = p->next;
        while (p) {
            free(p);
            p = nxt;
            nxt = nxt->next;//删除后面的节点
        }
    }
    void updateheight(bptr root)
    {
        if (root == NULL)return;
        root->height = treeheight(root);
        updateheight(root->lch);
        updateheight(root->rch);
    }
    bptr treeRotateRight(bptr root) {//右旋
        bptr left = root->lch;
        bptr right = root->rch;
        root->lch = left->rch; // 将将要被抛弃的节点连接为旋转后的 root 的左孩子
        left->rch = root; // 调换父子关系

        if (left != NULL)left->height = treeheight(left);
        if (right != NULL)right->height = treeheight(right);

        return left;//新根
    }
    bptr treeRotateLeft(bptr root) {
        bptr right = root->rch;
        bptr left = root->lch;
        root->rch = right->lch;
        right->lch = root;

        if (left != NULL)left->height = treeheight(left);
        if (right != NULL)right->height = treeheight(right);

        return right;
    }
    bptr treeRebalance(bptr root) {
        int factor = treeGetBalanceFactor(root);
        if (factor > 1 && treeGetBalanceFactor(root->lch) > 0) // LL
        {
            cout << "goLL" << endl;
            return treeRotateRight(root);

        }
        else if (factor > 1 && treeGetBalanceFactor(root->lch) < 0) { //LR
            root->lch = treeRotateLeft(root->lch);
            cout << "goLR" << endl;
            return treeRotateRight(root);
        }
        else if (factor < -1 && treeGetBalanceFactor(root->rch) < 0) // RR
        {
            cout << "goRR" << endl;
            return treeRotateLeft(root);
        }
        else if ((factor < -1 && root->rch != NULL && treeGetBalanceFactor(root->rch) > 0)) { // RL
            root->rch = treeRotateRight(root->rch);
            cout << "goRL" << endl;
            return treeRotateLeft(root);
        }
        else return root;//无事发生
    }//返回新根节点

public:
    bptr Root;
    AVL()
    {
       Root=NULL;
    }
    int treeheight(bptr root)
    {
        if (root == NULL)
            return 0;
        else return max(treeheight(root->lch), treeheight(root->rch)) + 1;
    }
    int treeGetBalanceFactor(bptr root) {
        if (root == NULL)
            return 0;
        else if (root->lch == NULL && root->rch != NULL)return -(root->rch->height);
        else if (root->rch == NULL && root->lch != NULL)return root->lch->height;
        else if (root->rch != NULL && root->lch != NULL)return root->lch->height - root->rch->height;
        else return 0;
    }
    void treeInsert(bptr& rootptr, value v)
    {
        bptr newNode;
        bptr root = rootptr;

        if (root == NULL) {
            newNode = new btree;
            assert(newNode);

            newNode->v = v;
            newNode->lch = newNode->rch = NULL;

            rootptr = newNode;
        }
        else if (root->v.w == v.w) {
            newNode = new btree;
            assert(newNode);
            newNode->v = v;
            root->next = newNode;
            return;
        }
        else {
            if (root->v.w < v.w)
                treeInsert(root->rch, v);
            else
                treeInsert(root->lch, v);
        }
        updateheight(rootptr);
        rootptr = treeRebalance(rootptr);
    }
    void browse(bptr& root)
    {
        if (root == NULL)return;
        browse(root->lch);
        cout << "height:" << root->height << endl;
        cout << "name:" << root->v.name << "  time:" << root->v.time << "   w:" << root->v.w << endl;
        cout << "pointer:";
        if (root->lch == NULL)cout << "lch:NULL" << endl;
        else cout << "lch:" << root->lch->v.w << endl;

        if (root->rch == NULL)cout << "rch:NULL" << endl;
        else cout << "rch:" << root->rch->v.w << endl;

        //if (root->next == NULL)cout << "next:NULL" << endl;
        //else cout << "next" << root->next->v.name << endl;
        cout<<"-----------"<<endl;
        browse(root->rch);
    }
    bptr deletenode(int X, bptr T)
    {
        //X为删除目标的关键字值
        //info为关键字值
        bptr tmp;
        if (T == NULL)
            return NULL;
        else if (X < T->v.w)
        {
            T->lch = deletenode(X, T->lch);
            treeRebalance(T);
        }
        else if (X > T->v.w)
        {
            T->rch = deletenode(X, T->rch);
            treeRebalance(T);
        }
        else
        {
            if (T->lch == NULL && T->rch == NULL)//若目标节点没有为叶子
            {
                delete T;
                return NULL;
            }
            else if (T->rch == NULL)//若目标节点只有左子树
            {
                tmp = T->lch;
                delete T;
                return tmp;
            }
            else if (T->lch == NULL)//若目标节点只有右子树
            {
                tmp = T->rch;
                delete T;
                return tmp;
            }
            else//若目标节点左右都有子树
            {
                if (treeheight(T->lch) > treeheight(T->rch))
                {
                    tmp = findmax(T->lch);//找出参数节点中最大的节点，返回地址
                    T->v = tmp->v;
                    T->lch = deletenode(tmp->v.w, T->lch);
                }
                else
                {
                    tmp = findmin(T->rch);//找出参数节点中最小的节点，返回地址
                    T->v = tmp->v;
                    T->rch = deletenode(tmp->v.w, T->rch);
                }
            }
        }
        T->height = max(treeheight(T->lch), treeheight(T->rch)) + 1;
        return T;
    }
};
class List {
public:
    nptr head, tail;
    List()
    {
        head = new node;
        head->next = tail;
    }
    void list_insert(string n, string t, int w)//名字 时间 权值 尾节点
    {
        tail = new node;
        tail->v.name = n, tail->v.time = t, tail->v.w = w;
        tail = tail->next;
    }
    void list_delete(node* q)//删除节点q的后一个节点,删除第一个提供head
    {
        if (q->next == NULL)exit(-1);
        nptr p = q->next;
        q->next = p->next;
        delete(p);
    }
};

#endif // MAINWINDOW_H
