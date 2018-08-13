x = 1000; y =0;
x2 = 0; y2 = 0;
case_n = 1;
X = 1:1:4000;
Y = 1:1:4000;
n = 1;
while(case_n <5 )
switch(case_n)
            case 1          
                x2=x-1;
                y2=y+1;
                
                if x==0 
                    case_n = 2;  
                end;        
            case 2          
                x2=x-1;
                y2=y-1;
                            
                if y==0 
                    case_n = 3;
                end;
            case 3
                x2=x+1;
                y2=y-1;
                if x==0 
                    case_n=4;
                end;
            case 4
                x2=x+1;
                y2=y+1;
                if y==0 
                    case_n=5;                    
                end;
 end;
        error1=abs(x2*x2+y*y-1000*1000);
        error2=abs(x*x+y2*y2-1000*1000);
        error3=abs(x2*x2+y2*y2-1000*1000);

        if (error1<=error3)&&(error1<=error2) 
            x=x2;
        end;
        if((error2<=error1)&&(error2<=error3)) 
            y=y2;         
        end;
        if((error3<=error1)&&(error3<=error2)) 
            x=x2; 
            y=y2; 
        end;
        X(n)=x;
        Y(n)=y;
n = n+1;        
end;

plot(X,Y);