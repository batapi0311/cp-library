//転倒数を求める(※acl必須)
//配列aの値は0からn-1まで
ll inversions(V a, int n){
 ll res = 0;
 fenwick_tree<ll> fwt(n);
 for(int i = 0; i < n; i++){
 	res += i - fwt.sum(0, a[i]);
 	fwt.add(a[i], 1);
 }
 return res;
}