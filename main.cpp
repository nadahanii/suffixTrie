#include <iostream>

using namespace std;

struct suffix_node
{
    char item;

    suffix_node *children[26];
    int position;
    suffix_node()
    {
        for(int i=0; i<26; i++)
        {
            this->children[i]=NULL;
        }

        this->position=-1;
    }
};

class SuffixTrie
{
protected:


    suffix_node* root=NULL;

public:



    suffix_node* make_node(char data)
    {

        suffix_node* temp_node = new suffix_node();

        temp_node->item=data;
        return temp_node;
    }



    SuffixTrie (char* text)
    {

        int p=0;
        while(text[p]!='$')
        {
            p++;
        }
        p++; /// size of the entered array of characters

        for(int i=p-1; i>=0; i--)
        {
            int t=p-i;
            char temp[t];
            int r=0;
            for(int j=i; j<p; j++)
            {

                temp[r]=text[j];
                r++;
            }

            root=Insert_at_trie(root,temp,i);
        }


    }

    suffix_node* Insert_at_trie(suffix_node* Root, char* sentence,int index)
    {

        int l=0;
        while(sentence[l]!='$')
        {

            l++;
        }
        l++; /// size of the entered array of characters


        if(Root==NULL)
        {

            suffix_node* new_node=new suffix_node();

            new_node->children[0]=make_node(sentence[0]);
            new_node->children[0]->position=index;
            Root=new_node;

        }
        else
        {


            int c=0;
            int i;
            suffix_node* temp=Root;
            for( i =0 ; i<l ; i++)
            {
                c=0;


                while(temp->children[c]!=NULL)
                {
                    if(temp->children[c]->item==sentence[i])
                    {
                        temp=temp->children[c];
                        c=0;
                        i++;
                    }
                    else
                    {
                        c++;
                    }
                }



                temp->children[c]=make_node(sentence[i]);
                temp= temp->children[c];




            }
            temp->position=index;

        }

        return Root;
    }


    void print_found(suffix_node* current)
    {
        if(current==NULL)
        {
            return;
        }

       for(int i=0;i<26;i++)
       {
           if( current->children[i]!=NULL && current->children[i]->position!=-1)
           {
               cout<<current->children[i]->position<<endl;
           }
           print_found(current->children[i]);


       }


    }


    void Search(char* to_be_found)
    {
        suffix_node* temp_search = root;

        int r=0;
        while(true)
        {
            if(to_be_found[r]!=NULL)
                r++;
            else
                break;
        }

        for(int i=0; i<r; i++)
        {

            int counter=0;
            while(true)
            {


            if(temp_search->children[counter]!=NULL)
            {

                if(temp_search->children[counter]->item==to_be_found[i])
                {
                    temp_search=temp_search->children[counter];

                    break;

                }


            }
            counter++;

                 if(counter==26)
                 {
                     break;
                 }


            }


        }



        print_found(temp_search);

    }


};
int main()
{
    SuffixTrie t("bananabanaba$");
    cout<<"indexes where (ana) is found are: "<<endl;
    t.Search("ana");

    cout<<"indexes where (naba) is found are: "<<endl;
    t.Search("naba");

    return 0;
}
