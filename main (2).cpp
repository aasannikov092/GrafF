#include <iostream>
#include <map>
#include <set>
#include <string>
#include <deque>
#include <vector>
using namespace std;

typedef string Vertex;
typedef map< Vertex, int > Spisok;
typedef map< Vertex , Spisok> Help;
struct DFSCallBack //�������������� ��������� ��� ������ DFS//
{
    std::vector <Vertex> Stack;//���� ������� ����� ������������ � ������� ������������ �������������� �����������,������������ � DFS
    Spisok Colors;//����� �������� ����� ������,���������� ��� � ���������� �������� DFS
    Spisok Time;//����� ����� �������� ����� ������ �� ������� ��� ������ DFS
    int T;//������� �������
    void OnBlack(Vertex Top)//����� ����������� Stack(��.14),������������ � ��� ������,����� ������� � DFS �������� � ������
    {
        Stack.push_back(Top);
    }
    void Print()//������� Stack(��. 14)
    {
        while(!Stack.empty())
        {
            cout<<Stack.back()<<" ";
            Stack.pop_back();
        }
        cout<<"\n";
    }
    void GiveC(Vertex Name, int Color)//����� �������� �������(�������� Colors(�� 15)
    {
        Colors.insert(std::make_pair (Name,Color));
    }
    void ChangeC(Vertex Name, int Color)//����� �������� ���� ������� � Colors (�� 15)
    {
        Spisok::iterator it=Colors.find(Name);
        (*it).second=Color;
    }
    int GetC(Vertex Name)//����� �������� ���� ������� � Colors (�� 15)
    {
        Spisok::iterator it=Colors.find(Name);
        return it->second;
    }
    void GiveT(Vertex A)//����� ����������� Time �� 16
    {
        Time.insert(std::make_pair (A,T));
    }
    void Tnull()//����� ���������� T �� 17
    {
        T=0;
    }
    void Tpp()//����� ������������� T �� 1
    {
        ++T;
    }
    Vertex TimeOut()//����� �������� ��� ������� � ���������� �������� � �������� � �� Time �� 16
    {
        Spisok::iterator a=Time.begin();
        for(Spisok::iterator i=Time.begin();i!=Time.end();++i)
        {
            if(a->second<i->second)
            {
                a=i;
            }
        }
        if(a!=Time.end())
        {
            Vertex New=a->first;
            Time.erase(a);
            return New;
        }
        else
        {
        return "End";
        }
    }
    void ErColors()//����� ������������� Colors �� 15
    {
        Colors.clear();
    }
};
/*{
    string Name;
public:

    Vertex(string Num)
    {
        Name=Num;
    };
    string N() const
    {
        return Name;
    };

};

struct Less
{
    bool operator () ( const Vertex & lhc, const Vertex & rhc) const{
        return lhc.N()<rhc.N();
};*/

class GrafF
{
    /*map< Vertex, set< Vertex, Less >  , Less> MyFriend;*/
    Help MyFriend;
//    Spisok DFSColors;
public:
    GrafF(){}

    void GivePair(Vertex A,int fi, Vertex B)//����� ����������� ������������ ����� � ����
    {
        Help::iterator yt=MyFriend.find(A);
        if(yt!=MyFriend.end())
        {
            yt->second.insert(std::make_pair(B,fi));/*����� ��� ������*/
        }
        else
        {
            AddVertex(A);
            Help::iterator rt=MyFriend.find(A);
            rt->second.insert(std::make_pair(B,fi));/* ����� ��������� ������ � � �� ���� ������*/
        }
        Help::iterator it=MyFriend.find(B);
        if(it==MyFriend.end())
        {
          //  it->second.insert(std::make_pair (A,fi));/**/
     /*   }
        else
        {*/
            AddVertex(B);
         /*   Help::iterator bt=MyFriend.find(B);
            bt->second.insert(std::make_pair (A,fi));*/
        }
    };

    void AddVertex(Vertex New)//����� ����������� ������� � ����
    {
        Spisok M;
        MyFriend.insert(std::make_pair (New,M));
    };

    void DeleteV(Vertex DieDieDieMyDarling)//����� ��������� �������
    {
        Help::iterator it=MyFriend.find(DieDieDieMyDarling);
        if(it!=MyFriend.end())
        {
            for(Help::iterator i=MyFriend.begin();i!=MyFriend.end();i++)
            {
                Spisok::iterator y=i->second.find(DieDieDieMyDarling);
                if(y!=i->second.end())
                {
                    i->second.erase(y);
                }

            }
           /* for(Spisok::iterator at=it->second.begin();at!=it->second.end();at++)
            {
                Help::iterator yt=MyFriend.find(at->first);
                Spisok::iterator ot=yt->second.find(it->first);
                yt->second.erase(ot);
            }*/
        MyFriend.erase(it);
        }
        else{cout<<"Your wish is not correct";}
    };

    void DeleteR(Vertex Fir, Vertex Sec)//����� ��������� �����
    {
        Help::iterator it=MyFriend.find(Fir);
       // Help::iterator at=MyFriend.find(Sec);
        if(   it!=MyFriend.end() /*)&&( at!=MyFriend.end() )*/  )
        {
            Spisok::iterator yt=it->second.find(Sec);
            if(yt!=it->second.end())
            {
                it->second.erase(yt);
           /*     Spisok::iterator ut=at->second.find(Fir);
                at->second.erase(ut);*/
            }
        }

    };

    void Show()//����� ��������� ����
    {
        for(Help::iterator it=MyFriend.begin();it!=MyFriend.end();it++)
        {
            cout<<it->first<<"->>";
            for(Spisok::iterator ut=it->second.begin();ut!=it->second.end();ut++)
            {
                cout<<ut->first<<"("<<ut->second<<");";
            }
            cout<<"\n";
        }
    };
    void BFS(Vertex K)//����� � ������
    {
        Spisok Colors;
        int k=0;
        for(Help::iterator i=MyFriend.begin();i!=MyFriend.end();i++)
        {
            Colors.insert(std::make_pair (i->first,k));
        }
        deque <Vertex> Familie;
        Spisok::iterator ik=Colors.find(K);
        (*ik).second=1;
        Familie.push_back(K);
        do
        {
            Help::iterator rt=MyFriend.find(Familie.front());
            for(Spisok::iterator kt=rt->second.begin();kt!=rt->second.end();kt++)
            {
                Spisok::iterator q=Colors.find(kt->first);
                if(q->second==0)
                {
                    Familie.push_back(q->first);
                    (*q).second=1;
                }
            }
            Spisok::iterator q=Colors.find( Familie.front() );
            (*q).second=2;
            cout<<Familie.front()<<" ";
            Familie.pop_front();
        }
        while(Familie.size()!=0);
        cout<<"\n";
    };

    template <typename Cb>
    void DFS(Cb & cb,int R)//����� � �������
    {
        cb.ErColors();
        int k=0;
        for(Help::iterator i=MyFriend.begin();i!=MyFriend.end();i++)
        {
            cb.GiveC(i->first,k); //DFSColors.insert(std::make_pair (i->first,k));
        }
        if(R==1)
        {
            for(Help::iterator y=MyFriend.begin();y!=MyFriend.end();y++)
            {
                if(cb.GetC(y->first)==0)
                {
                    DFS_Visit(y->first,cb,R);
                    cout<<"\n";
                }
            }
        }
        else if(R==0)
        {
            Vertex New=cb.TimeOut();
            while(New!="End")
            {
                if(cb.GetC(New)==0)
                {
                    DFS_Visit(New,cb,R);
                    cout<<"\n";
                }
                New=cb.TimeOut();
            }
        }
    };
    template <typename Cb>
    void DFS_Visit(Vertex h, Cb &cb,int R)//��������������� ����� ��� ������ � �������
    {
     /*   Spisok::iterator t=DFSColors.find(h);
        (*t).second=1;*/
        cb.ChangeC(h,1);
        cout<<h<<" ";
        if(R==1){cb.Tpp();}
        Help::iterator r=MyFriend.find(h);
        for(Spisok::iterator i=r->second.begin();i!=r->second.end();i++)
        {
       //     Spisok::iterator u=DFSColors.find(i->first);
            if(cb.GetC(i->first)==0)//u->second==0)
            {
                DFS_Visit(i->first,cb,R);
            }
        }
        cb.ChangeC(h,2);//(*t).second=2;
        if(R==1)
        {
            cb.OnBlack(h);
            cb.Tpp();
            cb.GiveT(h);
        }
    };
    void TGrafF(GrafF& New)//����� ������ �� ������ ����������������� ����
    {
        for(Help::iterator i=MyFriend.begin();i!=MyFriend.end();i++)
        {
            New.AddVertex(i->first);
            for(Spisok::iterator y=i->second.begin();y!=i->second.end();y++)
            {
                New.GivePair(y->first,y->second,i->first);
            }
        }
    };
};






int main()
{
    DFSCallBack Mona;
    GrafF Polikarpovich;
    cout<<"Spisok comand:\n1)GP (Vertex, int Vertex) dobavlyaet v Graf rebro i ego ves;\n 2)GV (Vertex) dobavlyaet Vershinu;\n 3)DV (Vertex) udalyaet vershinu;\n 4)DR (Vertex,Vertex) udalyaet rebro;\n 5)Show vivodit swyazi;\n 6)BFS (Vertex) poisk v shirinu;\n 7)DFS poisk v dlinu;\n 8)Top - topologicheskaya sortitrovka(ne zapuskat bez DFS;\n 11) SCC poisk silnosvyaznih komponent;\n10)End (no comments);\n";
    Vertex Comand="Waiting";
    while(Comand!="End")
    {
        Vertex Apfel;
        cin>>Apfel;
        if(Apfel=="GP")
        {
            Vertex A,B;
            cin>>A;
            int r;
            cin>>r;
            cin>>B;
            Polikarpovich.GivePair(A,r,B);
        }
        else if(Apfel=="GV")
        {
            Vertex A;
            cin>>A;
            Polikarpovich.AddVertex(A);
        }
        else if(Apfel=="DV")
        {
            Vertex A;
            cin>>A;
            Polikarpovich.DeleteV(A);
        }
        else if(Apfel=="DR")
        {
            Vertex A;
            cin>>A;
            Vertex B;
            cin>>B;
            Polikarpovich.DeleteR(A,B);
        }
        else if(Apfel=="Show")
        {
            Polikarpovich.Show();
        }
        else if(Apfel=="BFS")
        {
            Vertex A;
            cin>>A;
            Polikarpovich.BFS(A);
        }
        else if(Apfel=="DFS")
        {
            int y=1;
            Polikarpovich.DFS(Mona,y);
        }
        else if(Apfel=="Top")
        {
            Mona.Print();
        }
        else if(Apfel=="SCC")
        {
            GrafF Next;
            Polikarpovich.TGrafF(Next);
          //  Next.Show();
            //Mona.Tpp();
            Next.DFS(Mona,0);

        }
        else
        {
            Comand=Apfel;
        }
    }
 /*  Vertex Poni="Poni";
    Vertex Pomestie="Pomestie";
    Vertex Gena="Gena";
    Vertex Sin="Sin";
    Polikarpovich.AddVertex(Poni);
    int k=5,t=78;
    Polikarpovich.GivePair(Gena,k,Pomestie);
    Polikarpovich.GivePair(Pomestie,t,Sin);
    Polikarpovich.GivePair(Sin,k,Poni);
    Polikarpovich.BFS(Poni);
    Polikarpovich.DeleteV(Sin);
    Polikarpovich.DFS(Mona);
    Mona.Print();
    Polikarpovich.Show();*/
    return 0;
}
