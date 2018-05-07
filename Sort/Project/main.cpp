/*
 Harun Çatal
 150130034
 Analysis and Algorithms 1
 Homework 2
 */
#include "node.cpp"
#include<string>
#include<vector>

int main(int argc, const char * argv[]) {
    vector<node> myVector;//create vector to keep data
    node myNode;
    int size;
    if(argc==2)//read parameter from user
    {
        size=stoi(argv[1]);//size parameter user will enter
        myNode.readFile(myVector,size);//read file
        clock_t t;
        t = clock();//starting clock
        myNode.quickSort(myVector, 0, myVector.size()-1);//sorting
        t = clock()-t;
        cout<<"Elapsed time : "<<((float)t/CLOCKS_PER_SEC)<<" seconds"<<endl;
        myNode.writeFile(myVector,size);//writing
    }
    else
        cout<< "Please use parameters properly->filename sizeofArray"<<endl;//warning
    return 0;
}
