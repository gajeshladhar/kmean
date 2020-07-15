
using namespace std;

class KMean
{
  double** X;
  double** Y;
  int* C;
  int batch_size;
  int features;
  int K;
  int first_time=1;
 public: double inertia_;

  public :
    KMean(int K,int features,int batch_size)
    {
        this->K=K;
        this->features=features;
        this->batch_size=batch_size;

        C=new int[batch_size];
        Y=new double*[K];
        for(int i=0;i<K;i++)
        Y[i]=new double[features];
    }

    int* get_C(){
        return C;
    }
    void random_select()
    {   int p;
    cout<<"\n P's :";
        for(int i=0;i<K;i++)
        {
          p=(int)((rand()-100)%batch_size);
          cout<<p<<" ";
          for(int j=0;j<features;j++)
            Y[i][j]=X[p][j];
        }
        cout<<endl;
    }
    void update_C()
    {
        int index;
        double min=__INT32_MAX__;
        double sum=0;
       for(int i=0;i<batch_size;i++)
       {
           for(int j=0;j<K;j++)
           {
               sum=0;
               for(int k=0;k<features;k++)
               {
                   sum+=(X[i][k]-Y[j][k])*(X[i][k]-Y[j][k]);
               }
               if(sqrt(sum)<min)
               {
                   min=sqrt(sum);
                   index=j;
               }
           }
           C[i]=index;
           min=__INT32_MAX__;
           index=0;
           

       } 
    }

    void update_Y()
    {
        double** y=new double*[K];
        for(int i=0;i<K;i++)
        y[i]=new double[features];

        int* count=new int[K];
        for(int i=0;i<K;i++)
        count[i]=0;

        for(int cluster=0;cluster<K;cluster++)
        {
            for(int i=0;i<batch_size;i++)
            {
                if(C[i]==cluster)
                {
                    count[cluster]++;
                    for(int j=0;j<features;j++)
                    y[cluster][j]+=X[i][j];
                }
            }
        }

       for(int cluster=0;cluster<K;cluster++)
        {
            for(int j=0;j<features;j++)
            y[cluster][j]/=count[cluster];
        }
     
    
    Y=y;
    
        
    }

    private : void calculate_inertia(){
        double inertia__=0;
        double temp=0;
        for(int i=0;i<batch_size;i++)
        {
            int cluster=C[i];
            temp=0;
            for(int j=0;j<features;j++)
            temp+=(X[i][j]-Y[cluster][j])*(X[i][j]-Y[cluster][j]);
            inertia__+=sqrt(temp);
            
        }
        this->inertia_=inertia__;
    }

    public : void fit(double** X,int itr)
    {
        this->X=X;
        if(first_time==1)
        {
        first_time=0;
        random_select();
        update_C();
        calculate_inertia();
        cout<<"inertia__"<<inertia_<<endl;
        
        }
        double t;
        for(int i=0;i<itr;i++)
        {
            
            
            update_Y();
            update_C();
            calculate_inertia();
            if(t==inertia_)
            break;

            t=inertia_;

            cout<<"inertia_ :"<<inertia_<<endl;
           

        }
        
    }

    



};