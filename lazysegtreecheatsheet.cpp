//区間加算　区間和取得
struct S{
    long long value;
    int size;
};
using F = long long;

S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){ return {x.value + f*x.size, x.size}; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

//区間加算　区間和・区間の二乗和 取得
//modを取りたいときはS2,F2をmintにする
struct S2
{
  long long sq_sum;
  long long sum;
  long long len;
};
using F2 =long long;

S2 op2(S2 a,S2 b){
  return{
    a.sq_sum+b.sq_sum,
    a.sum+b.sum,
    a.len+b.len
  };
}
S2 e2(){return {0,0,0};}

S2 mapping2(F2 f, S2 x){
  return {
    //平方和：sq_sum+2*f*sum+f^2*len
    x.sq_sum+2*f*x.sum+f*f*x.len,
    //和：sum+f*len
    x.sum+f*x.len,
    //長さは変わらない
    x.len
  };
}

F2 composition2(F2 f, F2 g){
  return f+g;
}

F2 id2(){
  return 0;
}

// // 区間更新とき 
// S mapping(F f, S x) {
//     if (f == ID) return x; // 未更新ならそのまま
//     return {
//         f * f * x.len, // 全て f になるので平方和は f^2 * len
//         f * x.len,     // 和は f * len
//         x.len
//     };
// }