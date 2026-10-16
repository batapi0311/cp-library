int quadratic_equation(ll a,ll b,ll c){
  //ax^2+bx+c=0
  ll l=0,r=600000001;
  while(abs(l-r)>1){
    ll mid=(l+r)/2;
    if(a*mid*mid+b*mid+c<=0)l=mid;
    else r=mid;
  }
  if(a*l*l+b*l+c==0)return l;
  else return -1;
}