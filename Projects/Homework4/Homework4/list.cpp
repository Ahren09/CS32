void listAll(const MenuItem* m, string path) // two-parameter overload
{
    
    
    const vector<MenuItem*>* ptr=m->menuItems(); //ptr is a pointer to a Set of pointers
    //If the pointer passed in is a null pointer, only print its name
    if(m->name()!="")
    {
        if(path!="")
            path+='/';
        path+=m->name();
        cout<<path<<endl;
    }
    if(!ptr)
    {
        return;
    }
    
    for(vector<MenuItem*>::const_iterator it = ptr->begin(); it!=ptr->end();it++)
    {
        listAll(*it, path);
    }
}
