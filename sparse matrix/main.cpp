#include<iostream>
#include<vector>
using namespace std;
class link_list
{
private:
    class node
    {
        friend class link_list;
    private:

        //element node

        int Row;
        int Col;
        int data;
        node * next;
    };

    //initialize

    node *head=nullptr;
    node *tail=nullptr;
    int size=0;

public:
    void insert_LinkList(int row, int col, int value)
    {
        if (head == nullptr)
        {
            add_first(row,col,value);
            return;
        }
        node * tmp=new node;

        tmp->data=value;
        tmp->Row=row;
        tmp->Col=col;

        tmp->next=nullptr;
        tail->next=tmp;
        tail=tmp;
        size++;
    }
    void add_first(int row, int col, int value )
    {
        node *tmp=new node;

        tmp->data=value;
        tmp->Row=row;
        tmp->Col=col;
        if(tail == nullptr)
            tail=tmp;
        head=tmp;
        size++;

    }
    bool delete_LinkList(int row, int col)
    {

        if(head == nullptr )
            return false;
        if( head->Row == row && head->Col == col)
        {
            node *tmp=head;
            head=head->next;
            delete tmp;
            if(head == nullptr )
                tail =nullptr;
        }
        node *tmp = head;
        while (tmp->next != nullptr)
        {
            if( tmp ->next->Col == col && tmp->next->Row == row)
            {
                node * temp = tmp->next;
                tmp->next = tmp->next->next;
                delete temp;
                if(tmp->next == nullptr)
                    tail = tmp;
                return true;
            }
            tmp= tmp->next;
        }

        return false;
    }
    bool search_LinkList(int value)
    {
        node *tmp=head;
        while (tmp != nullptr)
        {
            if(tmp->data == value )
                return true;
            tmp=tmp->next;

        }
        return false;
    }
    void update_LinkList(int row, int col, int value)
    {
        node * tmp=head;
        while ( tmp != nullptr )
        {
            if(tmp ->Col == col && tmp->Row == row )
                tmp->data=value;
            tmp=tmp->next;
        }
    }
    void print_LinkList()
    {
        node *tmp=head;
        while (tmp)
        {
            cout<<tmp->Row<<"\t"<<tmp->Col<<"\t"<<tmp->data<<" "<<endl    ;
            tmp=tmp->next;
        }
        cout<<endl;
    }
    void save_file( )
    {   FILE * fptr;
        fptr = fopen("spars.csv","w");
        if(fptr == nullptr)
        {
            cout<<" Eror for save spars matrix"<<endl;
            return ;
        }
        node * tmp = head;
        while ( tmp )
        {
            fprintf(fptr,"%d","%s","%d","%s","%d",tmp->Row,",",tmp->Col,",",tmp->data);
            tmp = tmp->next;
        }
        fclose(fptr);
    }
    int get_size()
    {
        return size;
    }
};


int main()
{

    link_list object;

    //read csv file

    FILE *csv_file;
    csv_file = fopen("M(10,5).csv", "r");
    vector<int>temp;
    vector<vector<int>>matrix;
    int num;

    //convert 1d vector to 2d

    for(int i=0 ; i < 10 ;++i)
    {
        for(int j=0 ; j < 5 ;++j )
        {
            fscanf(csv_file,"%d,",&num);
            temp.push_back(num);
        }
        matrix.push_back(temp);
        temp.clear();
    }
    fclose(csv_file);

    //insert to link list

    for (int i=0 ;i < int(matrix.size());++i)
    {
        for (int j=0 ;j < int(matrix[i].size());++j)
            if(matrix[i][j] != 0)
                object.insert_LinkList(i,j,matrix[i][j]);
    }

    //Menu

    int option;
    int row,col,value;

    do
    {
        cout<<endl;
        cout<<"  ===========MENU=========="<<endl;
        cout<<"1. Insert Number To Matrix"<<endl;
        cout<<"2. Delete Number From Matrix"<<endl;
        cout<<"3. Search Numbers In Matrix"<<endl;
        cout<<"4. Update Number From Matrix"<<endl;
        cout<<"5. Print  Sparse Matrix"<<endl;
        cout<<"6. Exit"<<endl;
        cin>>option;

        switch (option)
        {
        case 1:
        {
            cout<<"Enter Row & Col & Value"<<endl;
            cin>> row>>col>>value;
            object.insert_LinkList(row,col,value);
            break;
        }
        case 2:
        {
            cout<<"Enter Row & Col"<<endl;
            cin>>row>>col;
            object.delete_LinkList(row,col);
            break;
        }
        case 3:
        {
            cout<<"Enter Value"<<endl;
            cin>>value;
            bool flag=object.search_LinkList(value);
            if(flag == true)
                cout<<"Number Is Exist"<<endl;
            else
                cout<<"Number Isn't Exist"<<endl;
            break;
        }
        case 4:
        {
            cout<<"Enter Row & Col & Value"<<endl;
            cin>> row>>col>>value;
            object.update_LinkList(row,col,value);
            break;
        }
        case 5:
        {   cout<<"ROW"<<"\t"<<"COL"<<"\t"<<"VALUE"<<endl;
            cout<<"_____________________________________________________________________________"<<endl;
            object.print_LinkList();
        }


        }


    }while (option != 6);
    cout<<"You Have Exited! "<<endl<<"save spars File"<<endl;
    object.save_file();

    return 0;
}
