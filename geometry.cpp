#include<complex>


namespace geometry{
    using ld=long double;
    using point=complex<ld>;
    const ld eps=1e-9;
    const ld PI=acos(ld(-1));
    inline bool equal(const ld &a,const ld &b){
        return fabs(a-b)<eps;
    }
    //単位ベクトル
    point unitVector(const point &a){
        return a/abs(a);
    }
    //法線ベクトル
    point normalVector(const point &a){
        return a*point(0,1);
    }
    //内積: a*b=|a||b|cosθ
    ld dot(const point &a, const point &b){
        return (a.real()*b.real()+a.imag()*b.imag());
    }
    //外積: a×b=|a||b|sinθ
    ld cross(const point &a, const point &b){
        return (a.real()*b.imag()-a.imag()*b.real());
    }
    //反時計回りに回転(ラジアン)
    point rotate(const point &p, const ld &theta){
        return point(cos(theta)*p.real()-sin(theta)*p.imag(),
                     sin(theta)*p.real()+cos(theta)*p.imag());
    }
    //ラジアンー＞度
    ld radianTodegree(const ld &radian){return radian *180/PI;}
    //度ー＞ラジアン
    ld degreeToradian(const ld &degree){return degree *PI/180;}
    //点の回転方向
    //点aを基準にしてb,cの位置関係
    int ccw(const point &a, point b,point c){
        b-=a,c-=a;
        //反時計回りのときー＞１
        if(cross(b,c)>eps)return 1;
        //時計回りのときー＞－１
        if(cross(b,c)<-eps)return -1;
        //c,a,bがこの順で同一直線上にあるとき
        if(dot(b,c)<0)return 2;
        //a,b,cがこの順で同一直線上にあるとき
        if(norm(b)<norm(c))return -2;
        //cが線分ab上にあるとき
        return 0;
    }
    //Line:直線
    //b-aで直線・線分
    struct Line{
        point a,b;
        Line()=default;
        Line(point a, point b) : a(a),b(b){}
        //ax+by=c
        Line(ld A, ld B, ld C){
            if(equal(A,0)){
                a=point(0,C/B),b=point(1,C/B);
            }else if(equal(B,0)){
                b=point(C/A,0),b=point(C/A,1);//ホントにb⁇
            }else{
                a=point(0,C/B),b=point(C/A,0);
            }
        }
    };
    //線分
    struct Segment : Line{
        Segment()=default;
        Segment(point a, point b):Line(a,b){}
        ld get_dist(){return abs(a-b);}
    };
    //円
    //pが中心の位置ベクトル，rは半径
    struct circle{
        point p;
        ld r;
        circle()=default;
        circle(point p, ld r) : p(p),r(r){};
    };
    //2直線の直交判定 内積0
    bool isOrthogonal(const Line &a, const Line &b){
        return equal(dot(a.b-a.a,b.b-b.a),0);
    }
    //2直線の平行判定 外積0
    bool isParaleel(const Line &a, const Line &b){
        return equal(cross(a.b-a.a,b.b-b.a),0);
    }
    //点cが直線ab上にあるか
    bool isPointOnLine(const point &a,const point &b, const point &c){
        return isParaleel(Line(a,b),Line(a,c));
    }
    //点cが線分ab上にあるか
    bool isPointOnSegment(const point &a, const point &b, const point &c){
        //|a-c|+|c-b|<=|a-b|なら線分上
        return (abs(a-c)+abs(c-b)<abs(a-b)+eps);
    }
    //直線lと点pのキョリ
    ld distanceBetweenLineAndPoint(const Line &l, const point &p){
        return abs(cross(l.b-l.a,p-l.a))/abs(l.b-l.a);
    }
    //線分lと点pのキョリを求める
    //点pから線分lのどこかへの最短距離
    ld distanceBetweenSegmentAndPoint(const Segment &l, const point &p){
        if(dot(l.b-l.a,p-l.a)<eps)return abs(p-l.a);
        if(dot(l.a-l.b,p-l.b)<eps)return abs(p-l.b);
        return abs(cross(l.b-l.a,p-l.a))/abs(l.b-l.a);
    }
    //直線s,tの交点
    point crossPoint(const Line &s, const Line &t){
        ld d1=cross(s.b-s.a,t.b-t.a);
        ld d2=cross(s.b-s.a,s.b-t.a);
        if(equal(abs(d1),0) and equal(abs(d2),0))return t.a;
        return t.a+(t.b-t.a)*(d2/d1);
    }
    //線分s,tの交点
    point crossPoint(const Segment &s,const Segment &t){
        return crossPoint(Line(s),Line(t));
    }
    //線分sと線分tが交差しているか
    //bound:線分の境界を含むか
    bool isIntersect(const Segment &s, const Segment &t, bool bound){
        return ccw(s.a,s.b,t.a)*ccw(s.a,s.b,t.b)<bound and
                ccw(t.a,t.b,s.a)*ccw(t.a,t.b,s.b)<bound;
    }
    //線分s,t間のキョリ
    ld distanceBetweenSegments(const Segment &s,const Segment &t){
        if(isIntersect(s,t,1))return (ld)(0);
        ld ans=distanceBetweenSegmentAndPoint(s,t.a);
        ans=min(ans,distanceBetweenSegmentAndPoint(s,t.b));
        ans=min(ans,distanceBetweenSegmentAndPoint(t,s.a));
        ans=min(ans,distanceBetweenSegmentAndPoint(t,s.b));
        return ans;
    }
    //射影(projection)
    //直線(線分)lに点pから引いた垂線の足を求める
    point projection(const Line &l, const point &p){
        ld t=dot(p-l.a,l.a-l.b)/norm(l.a-l.b);
        return l.a+(l.a-l.b)*t;
    }
    point projection(const Segment &l, const point &p){
        ld t=dot(p-l.a,l.a-l.b)/norm(l.a-l.b);
        return l.a+(l.a-l.b)*t;
    }
    //反射(reflection)
    //直線lを対象軸として点pと線対称の位置にある点
    point reflection(const Line &l, const point &p){
        return p+(projection(l,p)-p)*(ld)2.0;
    }
    //2円の交差判定
    //返り値は共通接戦の数
    int isIntersect(const circle &c1, const circle &c2){
        ld d=abs(c1.p-c2.p);
        //2円が離れているとき
        if(d>c1.r+c2.r+eps)return 4;
        //外接しているとき
        if(equal(d,c1.r+c2.r))return 3;
        //内接しているとき
        if(equal(d,abs(c1.r-c2.r)))return 1;
        //内包しているとき
        if(d<abs(c1.r-c2.r)-eps)return 0;
        return 2;
    }
    //2円の交点
    vector<point> crossPoint(const circle &c1, const circle &c2){
        vector<point>ret;
        int mode=isIntersect(c1,c2);
        //2円の中心間のキョリ
        ld d=abs(c1.p-c2.p);
        //2円が離れているとき
        if(mode==4)return ret;
        //一方の円が他方の円に内包されているとき
        if(mode==0)return ret;
        //2円が外接するとき
        if(mode==3){
            ld t=c1.r/(c1.r+c2.r);
            ret.emplace_back(c1.p+(c2.p-c1.p)*t);
            return ret;
        }
        //内接しているとき
        if(mode==1){
            if(c2.r<c1.r-eps){
                ret.emplace_back(c1.p+(c2.p-c1.p)*(c1.r/d));
            }else{
                ret.emplace_back(c2.p+(c1.p-c2.p)*(c2.r/d));
            }
            return ret;
        }
        //2円が重なるとき
        ld rc1=(c1.r*c1.r+d*d-c2.r*c2.r)/(2*d);
        ld rs1=sqrt(c1.r*c1.r-rc1*rc1);
        if(c1.r-abs(rc1)<eps)rs1=0;
        point e12=(c2.p-c1.p)/abs(c2.p-c1.p);
        ret.emplace_back(c1.p+rc1*e12+rs1*e12*point(0,1));
        ret.emplace_back(c1.p+rc1*e12+rs1*e12*point(0,-1));
        return ret;
    }
    //点pが円cの内部(円周上も含む)に入っているかどうか
    bool isIncircle(const circle &c, const point &p){
        ld d=abs(c.p-p);
        return (equal(d,c.r) or d<c.r-eps);
    }
    //円cと直線lの交点
    vector<point> crossPoint(const circle &c, const Line &l){
        vector<point> ret;
        ld d=distanceBetweenLineAndPoint(l,c.p);
        //交点を持たない
        if(d>c.r+eps)return ret;
        //接する
        point h=projection(l,c.p);
        if(equal(d,c.r)){
            ret.emplace_back(h);
            return ret;
        }
        point e=unitVector(l.b-l.a);
        ld ph=sqrt(c.r*c.r-d*d);
        ret.emplace_back(h-e*ph);
        ret.emplace_back(h+e*ph);
        return ret;
    }
    //点pを通る円cの接線
    //2本あるので接点のみを返す
    vector<point> tangentToCircle(const point &p, const circle &c){
        return crossPoint(c,circle(p,sqrt(norm(c.p-p)-c.r*c.r)));
    }
    //円の共通接線
    vector<Line> tangent(const circle &a, const circle &b){
        vector<Line>ret;
        //2円の中心間のキョリ
        ld g=abs(a.p-b.p);
        if(equal(g,0))return ret;
        point u=unitVector(b.p-a.p);
        point v=rotate(u,PI/2);
        for(int s : {-1,1}){
            ld h=(a.r+b.r*s)/g;
            if(equal(h*h,1)){
                ret.emplace_back(a.p+(h>0 ? u:-u)*a.r,
                                 a.p+(h>0 ? u:-u)*a.r+v);
            }else if(1-h*h>0){
                point U=u*h,W=v*sqrt(1-h*h);
                ret.emplace_back(a.p+(U+W)*a.r,
                                b.p-(U+W)*(b.r*s));
                ret.emplace_back(a.p+(U-W)*a.r,
                                b.p-(U-W)*(b.r*s));
                
            }
        }
        return ret;
    }
    //多角形の面積を求める
    ld polygonArea(const vector<point> &p){
        ld ret=0;
        int n=p.size();
        for(int i=0; i<n-1; i++)ret+=cross(p[i],p[i+1]);
        ret+=cross(p[n-1],p[0]);
        return ret*0.5;
    }
    //凸多角形かどうか
    bool isConvex(const vector<point> &p){
        int n=p.size();
        int now,pre,nxt;
        for(int i=0;i<n;i++){
            pre=(i-1+n)%n;
            nxt=(i+1)%n;
            now=i;
            if(ccw(p[pre],p[now],p[nxt])==-1)return false;
        }
        return true;
    }
    //凸包O(NlogN)
    vector<point> ConvexHull(vector<point> p){
        int n=(int)p.size(),k=0;
        sort(p.begin(),p.end(),[](const point &a, const point &b){
            return (a.real()!=b.real() ? a.real()<b.real() : a.imag()<b.imag());
        });
        vector<point> ch(2*n);
        //一直線上の3点を含める->(<eps)
        //含めない->(<eps)
        for(int i=0; i<n; ch[k++]=p[i++]){
            while(k>=2 and 
                    cross(ch[k-1]-ch[k-2],p[i]-ch[k-1])<eps)k--;
        }
        for(int i=n-2,t=k+1;i>=0;ch[k++]=p[i--]){
            while(k>=t and 
                    cross(ch[k-1]-ch[k-2],p[i]-ch[k-1])<eps)k--;
        }
        ch.resize(k-1);
        return ch;
    }
    //多角形gに点pが含まれているか
    //含まれる：2，辺上にある：1，含まれない:0
    int isContained(const vector<point> &g, const point &p){
        bool in =false;
        int n=(int)g.size();
        for(int i=0;i<n;i++){
            point a=g[i]-p,b=g[(i+1)%n]-p;
            if(imag(a)>imag(b))swap(a,b);
            if(imag(a)<=eps and eps<imag(b) and cross(a,b)<-eps)in=!in;
            if(cross(a,b)==0 and dot(a,b)<=0)return 1;
        }
        return (in ? 2 : 0);
    }
    // 凸多角形pを直線lで切断し、その左側を返す
    vector<point> convexCut(vector<point> p, Line l){
        vector<point> ret;
        int sz=(int)p.size();
        for(int i=0;i<sz;i++){
            point now=p[i];
            point nxt=p[i==sz-1 ? 0 : i+1];
            if(ccw(l.a,l.b,now)!=-1)ret.emplace_back(now);
            if(ccw(l.a,l.b,now)*ccw(l.a,l.b,nxt)<0){
                ret.emplace_back(crossPoint(Line(now,nxt),l));
            }
        }
        return ret;
    }
}

using namespace geometry;