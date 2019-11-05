public class Testing {
    int height(node r){
        if r is leaf then return 0
        else{
            mh=-1;
            for each child c of r do{
                h=height(c)
                if h>mh then mh=h
            }
        return mh+1
        }
    }

}