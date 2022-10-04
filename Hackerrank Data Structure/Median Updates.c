#include <stdio.h>

long long koren,a[1100000][10],i,j,k,l,m,n,b,c,d,t,tt,nn;
char ss;

void update(long long);

long long maxx(long long xx, long long yy)
{
if(xx>yy) return xx;
return yy;
}


long long maz(long long mam, long long ind)
{
long long mm;

if(ind == -1) return 0;

if(a[ind][7]==mam)
   {
   if(a[ind][6]>0) 
      {
      a[ind][6]--;
      return 1; 
      }
   
   return 0; 
   }


if(mam<a[ind][7])
  {
  mm=maz(mam,a[ind][0]);
  update(ind);
  return mm;
  }

  mm=maz(mam,a[ind][3]);
  update(ind);
  return mm;

}

long long najdi(long long nn, long long ind)
{

//printf("hladam %lld v %lld\n",nn, ind);

if(nn<=a[ind][1]) return najdi(nn, a[ind][0]);

nn-=a[ind][1];

if(nn<=a[ind][6]) return a[ind][7];

return najdi(nn-a[ind][6],a[ind][3]);
}

void update(long long ind)
{
long long ls;

  ls = a[ind][0];
  if(ls>=0)
  {
  a[ind][1] = a[ls][1]+a[ls][6]+a[ls][4];
  a[ind][2] = 1+maxx(a[ls][2],a[ls][5]);
  
//  printf("update %lld=ind %lld=lh\n",ind, a[ind][2]);
  }
  else
  {
  a[ind][1] = 0;
  a[ind][2] = 0;
  }
  
  ls = a[ind][3];
if(ls>=0)
  {
  a[ind][4] = a[ls][1]+a[ls][6]+a[ls][4];
  a[ind][5] = 1+maxx(a[ls][2],a[ls][5]);
// printf("update %lld=ind %lld=lh\n",ind, a[ind][2]);
 
  }
  else
  {
  a[ind][4] = 0;
  a[ind][5] = 0;
  }


return ;
}


void left_rotation(long long ind)
{
long long bb, cc, dd, ee,oo;

//printf("lava rot %lld=ind\n",ind);

oo = a[ind][8];

ee = a[ind][0];
bb = a[ind][3];
cc = a[bb][0];
dd = a[bb][3];

a[ind][0]=ee;
a[ind][3]=cc;
a[bb][0] = ind;
a[bb][3] = dd;

a[bb][8] = oo;
a[ind][8] = bb;
if(cc>=0) a[cc][8] = ind;


if(oo>=0)
 {
if(a[oo][0]==ind) a[oo][0] = bb;
          else   a[oo][3] = bb;
 }
 else koren=bb;         

update(ind);
update(bb);

return ;
}

void right_rotation(long long ind)
{
long long bb, oo,cc, dd, ee;

//printf("prava rot %lld=ind\n",ind);

oo = a[ind][8];

bb = a[ind][0];
ee = a[bb][0];
cc = a[bb][3];
dd = a[ind][3];

a[ind][0]=cc;
a[ind][3]=dd;
a[bb][0] = ee;
a[bb][3] = ind;

a[bb][8] = oo;
a[ind][8] =bb;
if(cc>=0) a[cc][8] = ind;

if(oo>=0)
{
if(a[oo][0]==ind) a[oo][0] = bb;
           else   a[oo][3] = bb;
}
else koren=bb;

update(ind);
update(bb);

return ;
}



void vyvazuj(long long ind)
{
long long syn;

//if(tt==3 && ind ==2) return;

//printf("vyvazujem %lld\n",ind);

//return;

if(a[ind][2]==a[ind][5]+2)
  {
  syn = a[ind][0];
  
//  printf("tu som %lld %lld\n", ind, syn);
  
  if(a[syn][2]>a[syn][5]) right_rotation(ind);
         else {
//               printf("komplik %lld=tt\n",tt);
               left_rotation(syn);
//if(tt<3)               
               right_rotation(ind);         
              }  
  return ;
  }

  syn = a[ind][3];
  
  if(a[syn][5]>a[syn][2]) left_rotation(ind);
         else {
               right_rotation(syn);
               left_rotation(ind);         
              }  
return ;
}

void vloz(long long mam,long long ind)
{
long long vy;

// printf("%lld=vy %lld %lld\n",a[ind][2]-a[ind][5],a[ind][2],a[ind][5]);
 

if(a[ind][7]==mam)
   {
   a[ind][6]++;
   return;
   }

if(mam<a[ind][7])
  {
  if(a[ind][0]>=0) vloz(mam,a[ind][0]);
       else {
             a[ind][0] = nn;
             a[nn][0] = -1;
             a[nn][1] = 0;
             a[nn][2] = 0;
             a[nn][3]=-1;
             a[nn][4]= 0;
             a[nn][5]= 0;
             a[nn][6]= 1;
             a[nn][7]= mam;
             a[nn][8]= ind;
             
             nn++;       
             }
 
  update(ind);
//  printf("..po update %lld %lld=ph\n",ind,a[ind][5]);
             
  
  vy = a[ind][2] - a[ind][5];
  if(vy>1 || vy <-1) vyvazuj(ind);
  
//  printf("%lld=vy %lld %lld\n",vy,a[ind][2],a[ind][5]);
  
  return;
  }

  if(a[ind][3]>=0) vloz(mam,a[ind][3]);
       else {
             a[ind][3]=nn;
             a[nn][0] = -1;
             a[nn][1] = 0;
             a[nn][2] = 0;
             a[nn][3]=-1;
             a[nn][4]= 0;
             a[nn][5]= 0;
             a[nn][6]= 1;
             a[nn][7]= mam;
             a[nn][8]= ind;
             nn++;       
             }
 
 update(ind);            
  
//  printf("po update %lld %lld=ph\n",ind,a[ind][5]);
  
  vy = a[ind][2] - a[ind][5];

//  printf("%lld=vy %lld %lld\n",vy,a[ind][2],a[ind][5]);

  if(vy>1 || vy <-1) vyvazuj(ind);


return;
}



int main()
{

n=0;
nn=1;
a[0][0]=-1;
a[0][1]=0;
a[0][2]= 0;
a[0][3]=-1;
a[0][4]= 0;
a[0][5]= 0;
a[0][6]= 0;
a[0][7]= -1;
a[0][8]=-1;
koren=0;

scanf("%lld\n",&t);
for(tt=0;tt<t;tt++)
{
scanf("%c %lld\n",&ss,&k);

//printf("zac %c %lld %lld=t\n",ss,k,t);

m=1;

if(ss=='a') 
   {
   vloz(k,koren);  
   n++;
   }

if(ss=='r')
  {
  if(m=maz(k,koren)) n--;
  }

if(m==0 || n==0) printf("Wrong!\n");
  else 
    {
    if(n&1) printf("%lld\n",najdi(n/2+1,koren));
       else 
         {
         i = najdi(n/2,koren)+ najdi(n/2+1,koren);
          
          if(i<0) {printf("-");i = -i;}         
                    
          if((i&1)==0) printf("%lld\n",i/2);
               else  printf("%lld.5\n",i/2);
         }
    }

/*
for(i=0;i<nn;i++)
  printf("%lld=ind, %lld=ls %lld=ps %lld=h %lld=hl %lld=hp %lld=otec\n",i,a[i][0],a[i][3],a[i][7],a[i][2],a[i][5],a[i][8]);
 printf("----- %lld %lld\n",tt,t); 
*/
//if(tt==4) break;

}

return 0;
}
