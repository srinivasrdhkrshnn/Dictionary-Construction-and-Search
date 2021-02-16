/*************************************

STUDENT NAME: K.R.SRINIVAS
INSTITUTION: INDIAN INSTITUTE OF TECHNOLOGY MADRAS
ROLL NUMBER: EE18B136

*************************************/

#include <iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>

using namespace std;

class node
{
   string word;
   string meaning;
   node *left,*right;
   int height;

public:

  node(string word,string meaning)
  {
    this->word=word;
    this->meaning=meaning;
    left=right=NULL;
    height=1;
  }

 void print()
 {
    cout<<endl<<setw(10)<<word<<setw(10)<<meaning<<"\n";
 }

 friend class Dictionary;

};

class Dictionary
{
   node *root;

public:
   Dictionary()
    {
      root=NULL;
    }
 int max(int,int);
 int height(node*);
 node *insert(node *rnode,string word,string meaning);
 void insertIn(string word,string meaning);
 node *rightRotate(node *);
 node *leftRotate(node *);
 int getbalance(node*);
 void inorder();
 void inorderRec(node *);
 void search(string);
 node *search(node *,string);
 void edits(const string& , node *  );
 bool compare(std::pair<int,string> ,std::pair<int,string> );
 int min(int , int , int );
 int editDist(string , string , int , int );
 int min(int ,int );

};

 int Dictionary::max(int a,int b)     //returns max of two numbers
{
 return (a>b)?a:b;
}

 int Dictionary::height(node *nnode)  //returns the height of subtree
{
 if(nnode==NULL) return 0;
 else return nnode->height;
}

 int Dictionary::getbalance(node *n)  //returns the difference in height of subtrees
{
 if(n==NULL) return 0;
 else return (height(n->left)-height(n->right));
}

node* Dictionary::rightRotate(node *y)  //to rotate right about a node and update height accordingly
{
 node *x=y->left;
 node *T=x->right;

 x->right=y;
 y->left=T;

 y->height=max(height(y->left),height(y->right))+1;
 x->height=max(height(x->left),height(x->right))+1;
 return x;
}

node* Dictionary::leftRotate(node *y)   //to rotate left about a node and update height accordingly
{
 node *x=y->right;
 node *T=x->left;

 x->left=y;
 y->right=T;

 y->height=max(height(y->left),height(y->right))+1;
 x->height=max(height(x->left),height(x->right))+1;

 return x;
}

node* Dictionary::insert(node *rnode,string word,string meaning)  //to insert a node in AVL tree
{
  if(rnode==NULL) return new node(word,meaning);

  if(word.compare(rnode->word)<=0) rnode->left=insert(rnode->left,word,meaning);
  else if (word.compare(rnode->word)>0) rnode->right=insert(rnode->right,word,meaning);
  else return rnode;

  rnode->height=1+max(height(rnode->left),height(rnode->right));

  int balance=getbalance(rnode);

  if(balance>1 && (word.compare(rnode->left->word)<=0))
  return rightRotate(rnode);

  if(balance<-1 && (word.compare(rnode->right->word)>0))
  return leftRotate(rnode);

  if(balance>1 && (word.compare(rnode->left->word)>0))
  {
    rnode->left=leftRotate(rnode->left);
    return rightRotate(rnode);
  }

  if(balance<-1 &&(word.compare(rnode->right->word)<=0))
  {
    rnode->right=rightRotate(rnode->right);
    return leftRotate(rnode);
  }

  return rnode;

}

 void Dictionary::inorder()
 {
   inorderRec(root);
 }


 void Dictionary::inorderRec(node *n)  //function to  do inorder traversal of a tree
{
  if(n)
 {
  inorderRec(n->left);
  n->print();
  inorderRec(n->right);
 }
}


 void Dictionary::insertIn(string word,string meaning)
{
 root=insert(root,word,meaning);
}

node * Dictionary::search(node *rnode,string rword) //function to search in AVL/BST tree
{
  if (rnode == NULL || rnode->word ==rword)
       return rnode;

  if (rnode->word < rword)
       return search(rnode->right, rword);

    return search(rnode->left, rword);
}

 int Dictionary:: min(int x,int y)                 //returns minimum of two values
 {
   if(x>y) return y;
   else return x;
 }

 int Dictionary:: min(int x, int y, int z)       //returns minimum of three values
{
    return min(min(x, y), z);
}

int Dictionary:: editDist(string str1, string str2, int m, int n) //Dynamic programming code to find edit distance between two strings
{

    int dp[m+1][n+1];
    for (int i=0; i<=m; i++)
    {
      for (int j=0; j<=n; j++)
        {
          if (i==0) dp[i][j] = j;

          else if (j==0) dp[i][j] = i;

          else if (str1[i-1] == str2[j-1])
             dp[i][j] = dp[i-1][j-1];

          else dp[i][j] = 1 + min(dp[i][j-1],dp[i-1][j],dp[i-1][j-1]);
        }
    }
  return dp[m][n];
}

/*bool compare(std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2)

{
  return elem1.second<elem2.second;
}*/

void Dictionary::edits(const string& rword, node *rnode)  //function to suggest appropriate word if wrong word is enterd by the user
 {
   int response;
   queue<node*> Q;
   int min_edit,temp_dist; string match;
   int m=rword.size();

   if(rnode==NULL) return;

   else
   { Q.push(rnode);
     int s=rnode->word.size();
     min_edit=editDist(rword,rnode->word,m,s);
     match=rnode->word;
   }

   while(!Q.empty())
   {
     node *P=Q.front();
     int n= P->word.size();
     temp_dist=editDist(rword,P->word,m,n);
     if(temp_dist<min_edit) { min_edit=temp_dist; match=P->word; }
     Q.pop();

     if(P->left!=NULL) Q.push(P->left);
     if(P->right!=NULL) Q.push(P->right);
   }

   cout<<"\n DID YOU MEAN:\t"<<match<<endl;
   cout<<"\nIF YES ENTER 1 ELSE 0:\t";
   cin>>response;

   if(response==1)

     search(match);

   else

     cout<<"\n\nSorry the entered word could not be found.\n";

  }

void Dictionary::search(string rword)
{

  node *index=search ( root ,rword);

  if(index!=NULL)  index->print();

  else
   {
     edits( rword , root );
   }

   return ;
}


int main()
{

 Dictionary d;
 vector<string> result;


   d.insertIn("abandon"," - To leave someone or something helpless,to giveup");
   d.insertIn("abash"," - ashamed or embarrased");
   d.insertIn("abduct"," - take someone forcefully away");
   d.insertIn("abide"," - to keep a promise");
   d.insertIn("ability"," - the capacity to do something");
   d.insertIn("abnormal"," - not regular or normal");
   d.insertIn("abort"," - to stop something take place");
   d.insertIn("abominable"," - dreadful");
   d.insertIn("accent"," - particular way of pronouncing");
   d.insertIn("archives"," - collection of documents");
   d.insertIn("basilect"," - Sociolinguistics");
   d.insertIn("bilingual"," - Able to speak two languages fluently");
   d.insertIn("borrow"," - To take and use with intention of returning");
   d.insertIn("beneficiary"," - referring to a person or animal that is intended to benefit from the action");
   d.insertIn("canonical"," - Representing a typical exemplar or *realization of a *category.");
   d.insertIn("catachresis"," - The (perceived) erroneous use of a term applied to a concept.");
   d.insertIn("circumstance"," - The state of affairs surrounding and affecting a *situation");
   d.insertIn("coax"," - gently");
   d.insertIn("dash"," - sudden quick movement");
   d.insertIn("decisive"," - absolutely or potentially");
   d.insertIn("delicacy"," - care and sensitivity");
   d.insertIn("drift"," - move slowly without purpose");
   d.insertIn("dwindle"," - decline slowly in number.");
   d.insertIn("enforce"," - implement forcefully and purposefully");
   d.insertIn("envisage"," - contemplate or conceive of as a possibility or a desirable future event");
   d.insertIn("execution"," - killing as an official punishment.");
   d.insertIn("exhaust"," - use up completely");
   d.insertIn("family"," - a group of large people related to each other");
   d.insertIn("fatal"," - causing death");
   d.insertIn("fiction"," - storiesthat are not true");
   d.insertIn("flicker"," - momentarily,just for a moment.");
   d.insertIn("folly"," - a lack of good judgemeny");
   d.insertIn("fringe"," - outer edge of a place , thing or society.");
   d.insertIn("garage"," - place used for keeping/repairing cars.");
   d.insertIn("gaze"," - look at calmly steadily and intentionlly.");
   d.insertIn("grubby"," - dirty");
   d.insertIn("guard"," - watch over so as to protect or control.");
   d.insertIn("grieve"," - suffer or cause pain.");
   d.insertIn("hallucinate"," - see something which is not actually present.");
   d.insertIn("handicap"," - an obstacle to progress.");
   d.insertIn("hesistant"," - reluctant or uncertain.");
   d.insertIn("hooligan"," - violent young troublemaker.");
   d.insertIn("hustle"," - busy activity.");
   d.insertIn("illiterate"," - unable to read or write.");
   d.insertIn("impart"," - communicate information to.");
   d.insertIn("incisive"," - showing clear thought and understanding.");
   d.insertIn("iniquity"," - great injustice.");
   d.insertIn("isolate"," - place apart or alone.");
   d.insertIn("iridescent"," - shimmering with many colours.");
   d.insertIn("jinx","- a person or thing that brings bad luck");
   d.insertIn("jocund"," - cheerful.");
   d.insertIn("jaunt"," - a short trip for pleasure.");
   d.insertIn("juxtapose"," - place close together.");
   d.insertIn("keel"," - a structure running along the base of the ship.");
   d.insertIn("kink"," - a bend or twist in something straight.");
   d.insertIn("kleptomania"," - recurring urge to steal.");
   d.insertIn("knuckle"," - finger joint.");
   d.insertIn("ledger"," - book of financial accounts.");
   d.insertIn("launder"," - wash or iron clothes.");
   d.insertIn("lapse"," - decline in standards");
   d.insertIn("locution"," - a word or a phrase.");
   d.insertIn("mellow"," - pleasantly smooth,lovable.");
   d.insertIn("mutilate"," - severe injure or damage.");
   d.insertIn("penury"," - extreme poverty");
   d.insertIn("overtone"," - a subtle additional quality.");
   d.insertIn("propose"," - put forwar an idea for consideration");
   d.insertIn("rectitude"," - correct behaviour");
   d.insertIn("sceptical"," - not easily convinced having doubts.");
   d.insertIn("satire"," - use of humour to criticise.");
   d.insertIn("salubrious"," - good for health.");
   d.insertIn("prolong"," - cause to last longer.");
   d.insertIn("proscribe"," - forbid");
   d.insertIn("sedulous"," - dedicated and careful.");
   d.insertIn("shun"," - avoid or reject");
   d.insertIn("suffuse"," - spread through or over");
   d.insertIn("traipse"," - walk or move wearily");
   d.insertIn("treat"," - behave towards or deal with a certain way.");
   d.insertIn("viscous"," - thick and sticky");
   d.insertIn("vigilant"," - alert to possible dangers.");
   d.insertIn("vacillate"," - changing your mind.");
   d.insertIn("urge"," - encourage or earnestly ask to do something.");
   d.insertIn("unbidden"," - without having been invited.");
   d.insertIn("wiggle"," - move with short movements from side to side.");
   d.insertIn("woe"," - sorrow or distress");
   d.insertIn("yeoman"," - a man owning house and small area of farmland.");
   d.insertIn("seize"," - take hold of suddenly and forcibly.");
   d.insertIn("semantics"," - study of meaning");
   d.insertIn("rapture"," - great joy");
   d.insertIn("poker"," - a gambling card game.");
   d.insertIn("potable"," - drinkable");
   d.insertIn("overcast"," - cloudy");
   d.insertIn("munificent"," - very generous");
   d.insertIn("junta"," - a group ruling a country after taking power by force.");
   d.insertIn("farrago"," - a confused mixture");
   d.insertIn("embellish"," - decorate");
   d.insertIn("devilry"," - wickedness");
   d.insertIn("diatribe"," - a vehement verbal attack ");
   d.insertIn("criterion"," - a standard by which something may be judged");
   d.insertIn("brash"," - aggresively self confident");
   d.insertIn("brawn"," - physical strength");
   d.insertIn("garish"," - unpleasantly bright and showy.");
   d.insertIn("garrulous"," - very talkative");
   d.insertIn("irk"," - annoy");
   d.insertIn("irresolute"," - uncertain");


 cout<<"DICTIONARY:\n";
 d.inorder();

 string search_word;
 int response;
 cout<<"\n\nEnter any word you want to search:\t";
 cin>>search_word;
 cout<<"\n";
 d.search(search_word);


 return 0;
}





