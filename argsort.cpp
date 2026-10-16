//偏角ソート　反時計回り
struct point
{
  ll x,y;
  int id;
};
int argtype(const point &a){
  return a.y<0 ? -1 : a.y>0 ? 1 : a.x<0 ? 1 : a.x>0 ? -1 : 0;
}  

bool argless(const point &a, const point &b){
  int at=argtype(a),bt=argtype(b);
  return at!=bt ? at<bt : a.x*b.y-a.y*b.x>0;
}

//偏角ソート　時計回り
struct point
{
  ll x,y;
  int id;
};
int argtype(const point &a){
  return a.y<0 ? -1 : a.y>0 ? 1 : a.x<0 ? 1 : a.x>0 ? -1 : 0;
}  

bool argless(const point &a, const point &b){
  int at=argtype(a),bt=argtype(b);
  return at!=bt ? at>bt : a.x*b.y-a.y*b.x<0;
}


