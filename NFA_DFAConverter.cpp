# include"stdafx.h"
# include<iostream> 
# include<map> 
# include<list> 
using namespace std; 
class node; 
int st=1; 
class node 
{ 
        private: 
        multimap<char,int> trans; 
        int name; 
        public: 
        node() 
        { 
                name=0; 
        } 
        node(int names) 
        { 
                name=names; 
        } 
        int getname() 
        { 
                return name; 
        } 
        void insert(int tr,char car) 
        { 
                trans.insert(pair<char,int>(car,tr)); 
        } 
        multimap<char,int>::iterator begin() 
        { 
                return trans.begin(); 
        } 
        multimap<char,int>::iterator end() 
        { 
                return trans.end(); 
        } 
        list<int> find(char c) 
        { 
                list<int> clo; 
                for(multimap<char,int>::iterator it=trans.begin();it!=trans.end();it++) 
                { 
                        if(it->first==c) 
                                clo.push_back(it->second); 
                } 
                return clo; 
        } 
        void erase() 
        { 
                trans.erase(trans.begin(),trans.end()); 
        } 
}; 
list<node> nlist; 
int accnul=1;
class Dfa 
{ 
	friend void display(Dfa);
        private: 
                multimap<char,int> trans; 
                list<node>  nfasum; 
                int name; 
                int pro; 
        public: 
                Dfa() 
                { 
                        name=0; 
                        pro=0; 
                } 
                Dfa(int n) 
                { 
                        name= n; 
                        pro=0; 
                } 
                void insert_maps(list<node> l) 
                { 
                       nfasum=l; 
                } 
				int equate(Dfa n)
				{
					return equate(n.nfasum);
				}
                int equate(list<node>l) //0 no 1 -yes 
                { 
                        int diff=0; 
						/*if(l.empty()||nfasum.empty())
						{
							//cout<<"Returing 0"<<endl;
							if(accnul==1)
							{
								accnul=0;
								return 0;
							}
							else
								return 1;
						}*/
						
                        diff=0;
                        for(list<node>::iterator it=l.begin();it!=l.end();it++) 
                        {  
								diff=0;
                                for(list<node>::iterator j=nfasum.begin();j!=nfasum.end();j++) 
                                { 
										//cout<<"Comparing :: "<<(*it).getname()<<" :: "<<(*j).getname()<<endl;
                                        if((*it).getname()==(*j).getname()) 
                                        { 
												
                                                diff=1;
												break;
                                        } 
                                } 
                                if(diff==0)
								{
									//cout<<"Return 0"<<endl;
									return 0; 
								}
                        } 
						diff=0;
                        for(list<node>::iterator it=nfasum.begin();it!=nfasum.end();it++) 
                        {  
								diff=0;
                                for(list<node>::iterator j=l.begin();j!=l.end();j++) 
                                { 
										//cout<<"Comparing :: "<<(*it).getname()<<" :: "<<(*j).getname()<<endl;
                                        if((*it).getname()==(*j).getname()) 
                                        { 
												
                                                diff=1;
												break;
                                        } 
                                } 
                                if(diff==0)
								{
									//cout<<"Return 0"<<endl;
									return 0; 
								}
                        } 
						//cout<<"Return 1"<<endl;
                        return 1; 
                } 
                void insert(int tr,char car) 
                { 
                        trans.insert(pair<char,int>(car,tr)); 
                } 
                int getpro() 
                { 
                        return pro; 
                } 
                void setpro() 
                { 
                        pro=1; 
						
                } 
                multimap<char,int>::iterator begin() 
                { 
                        return trans.begin(); 
                } 
                int getname() 
                { 
                        return name; 
                } 
                multimap<char,int>::iterator end() 
                { 
                        return trans.end(); 
                } 
                list<int> find(char c) 
                { 
                        list<int> clo; 
                        for(multimap<char,int>::iterator it=trans.begin();it!=trans.end();it++) 
                        { 
                                if(it->first==c) 
                                        clo.push_back(it->second); 
                        } 
                        return clo; 
                } 
                list<node> getnodelist() 
                { 
                        return nfasum; 
                } 
                void erase() 
                { 
                        trans.erase(trans.begin(),trans.end()); 
                } 
                int isEmpty() 
                { 
                        if(nfasum.empty()) 
                        { 
                                return 1; 
                        } 
                        else 
                        { 
                                return 0; 
                        } 
                } 
}; 
list<node> mapnode(list<int> l) 
{ 
        list<node> returns; 
       for(list<int>::iterator it=l.begin();it!=l.end();it++) 
        { 
                int nodename=(*it); 
                for(list<node> ::iterator it2=nlist.begin();it2!=nlist.end();it2++) 
                { 
                        if(it2->getname()==nodename) 
                        { 
                                returns.push_back(*it2); 
                        } 
                } 
        } 
        return returns; 
} 
void display(Dfa n)
{
	cout<<"Node name : " <<n.getname()<<endl;
	for(list<node>::iterator it=n.nfasum.begin();it!=n.nfasum.end();it++)
	{
		cout<<" :::: "<<(*it).getname()<<endl;
	}
}
list<node> Eclosure(node n) 
{ 
       list<int> vals;
	   vals=n.find('$'); 
	   int ll=n.getname();
       vals.push_front(n.getname()); 
		
       return mapnode(vals); 
} 
list<node> Eclosure(list<node> n) 
{ 
        list<node> all; 
        for(list<node>::iterator it=n.begin();it!=n.end();it++) 
        { 
               list<node> for1=Eclosure((*it)); 
               all.insert(all.end(),for1.begin(),for1.end()); 
        } 
        return all; 
} 
list<node> move(node n , char c) 
{ 
        list<int> vals=n.find(c); 
        return mapnode(vals); 
} 
list<node> move(list<node> n,char c) 
{ 
        list<node> all; 
        for(list<node>::iterator it=n.begin();it!=n.end();it++) 
        { 
               list<node> for1=move(*it,c); 
               all.insert(all.end(),for1.begin(),for1.end()); 
        } 
        return all; 
} 
list<node> move(list<node> n,char c[100],int n1) 
{ 
        list<node> all; 
        int i=0; 
        for(int i=0;i<n1;i++) 
        { 
                list<node> for1=move(n,c[i]); 
                all.insert(all.end(),for1.begin(),for1.end()); 
        } 
        return all; 
} 
Dfa createinit(node n) 
{ 
              list<node> init=Eclosure(n); 
			 
              Dfa newnode(st++); 
              newnode.insert_maps(init); 
              return newnode; 
} 
Dfa proceed(Dfa n,char c) 
{ 
       list<node> nlist=n.getnodelist(); 
       Dfa newdfa(st++); 
       list<node> nv=Eclosure(move(nlist,c)); 
       newdfa.insert_maps(nv); 
	   return newdfa;
}           
char getcval(char chars[100],int set,int n)
{
	if(n==set)
		return '^';
	else
		return chars[n];
}
int getnval(int n)
{
	return n;

}
int main() 
{ 
        node *nodes; 
        int n1; 
        cout<<"Enter the Nodes No. ?"<<endl; 
        cin>>n1; 
        nodes=new node[n1]; 
        int charset=0; 
		int glob=1;
        cout<<"Enter the language char ?? " <<endl; 
        cin>>charset; 
        char chars[100]; 
        for(int y=0;y<charset;y++) 
        { 
                cin>>chars[y]; 
        } 
        for(int i=0;i<n1;i++) 
        { 
                cout<<"For Node "<<(i+1)<<" Enter the transitions <char> <int> Enter ^ to exit"<<endl; 
                char val; 
                int n; 
                nodes[i]=(i+1); 
				int yy=0;
                do 
                { 
					
					if(glob==1)
					{
                        cin>>val; 
                        if(val=='^') 
                                break;
						if(val=='~')
						{
							glob=0;
							val='^';
							val=getcval(chars,charset,yy++);
							if(val=='^') 
                                break;
							int n2=getnval((rand())%n1);
							nodes[i].insert(n2,val); 
							cout<<"Test case :" <<val << " " <<n2<<endl;
							
						}
						else
						{
                        cin>>n; 
						
                        nodes[i].insert(n,val); 
						}
					}
					else
					{
						val=getcval(chars,charset,yy++);
						if(val=='^') 
                                break;
						int n2=getnval((rand())%n1);
						nodes[i].insert(n2,val); 
						cout<<"Test case :" <<val << " " <<n2<<endl;
					}
                         
                }while(val!='^'); 
				nlist.push_back(nodes[i]);
        } 
        Dfa root[1000]; 
        int track=0; 
        int i=0; 
        root[0]=createinit(nodes[0]); 
		cout<<"Included :"<<root[0].getname()<<endl;
		display(root[0]);
        int pro=0; 
        do 
        { 
               for(int i=0;i<=track;i++) 
               { 
				   if(root[i].getpro()==0) 
                        { 
                                for(int j=0;j<charset;j++) 
                                { 
										Dfa temp=proceed(root[i],chars[j]); 
										int test=0;
										int pos=0;
										
										for(int k=0;k<=track;k++)
										{
											//cout<<"Comparing :: "<<temp.getname()<<" and "<<root[k].getname()<<endl;
											if(int z=temp.equate(root[k])==0)
											{
												
												test=1;	
												pos=track+1;
											}
											else
											{
												test=0;
												pos=k;
												break;
											}
										}
										if(test==1)
										{
											cout<<"Included :"<<temp.getname()<<endl;
											display(temp);
											root[++track]=temp;				
											
										}
										root[i].insert(root[pos].getname(),chars[j]); 
										
                                } 
								
                        } 
                        root[i].setpro(); 
                } 
                pro=0; 
        } 
        while(pro!=0);  
        for(int i=0;i<=track;i++) 
        { 
                cout<<"Node name: "<<root[i].getname()<<endl; 
                for(multimap<char,int>::iterator it=root[i].begin();it!=root[i].end();it++) 
                { 
                        cout<<it->first<<" ---- > "<<it->second<<endl; 
                } 
        } 
		getchar();
		getchar();
}
